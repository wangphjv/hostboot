/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/usr/mmio/test/mmiotest.H $                                */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2011,2019                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#include <cxxtest/TestSuite.H>
#include <errl/errlmanager.H>
#include <errl/errlentry.H>
#include <limits.h>
#include <devicefw/driverif.H>
#include "../mmio.H"
#include <targeting/common/utilFilter.H>
#include <explorer_scom_addresses.H>
#include <exp_oc_regs.H>
#include <sys/mmio.h>
#include <utils/chipids.H>

#define SCOM2MMIO_ADDR(_ADDR) (EXPLR_IB_MMIO_OFFSET | (_ADDR << 3))
#define CNFG2MMIO_ADDR(_ADDR) (EXPLR_IB_CONFIG_OFFSET | _ADDR)
#define BYTESWAP64(_DATA) (__builtin_bswap64(_DATA))

static const uint64_t EXPLR_IB_CONFIG_OFFSET = 0x0000000000000000ull;
static const uint64_t EXPLR_IB_MMIO_OFFSET   = 0x0000000100000000ull; // 4GB

// NOTE: changing this address requires changes
//       to src/build/simics/standalone.simics
static const uint64_t EXPLR_INVALID_SCOM_ADDR =
                            EXPLR_TP_MB_UNIT_TOP_TRACE_TRDATA_CONFIG_0;


class MmioTest : public CxxTest::TestSuite
{
  public:

    /**
     * @brief Test MMIO calls
     */
    void testExplrMMIO(void)
    {
        TS_INFO("testExplrMMIO> Start" );        

        errlHndl_t l_err = nullptr;
        uint32_t regdata4 = 0;
        size_t op_size = 0;
        uint64_t l_buffer64;

        // Get OCMB target, return if there is no OCMB
        TARGETING::TargetHandle_t   explr_target = nullptr;
        TARGETING::TargetHandleList ocmb_target_list;
        TARGETING::getAllChips(ocmb_target_list, TARGETING::TYPE_OCMB_CHIP);
        if (ocmb_target_list.size() == 0)
        {
            TS_INFO("testExplrMMIO> No OCMB targets found.  Exiting.");
            return;
        }
        explr_target = ocmb_target_list[0];
        if(explr_target->getAttr<TARGETING::ATTR_CHIP_ID>() !=
                                                 POWER_CHIPID::EXPLORER_16)
        {
            TS_INFO("testExplrMMIO> No explorer targets found.  Exiting.");
            return;
        }

        // valid read from config space register
        op_size = sizeof(regdata4);
        l_err = DeviceFW::deviceRead(
                          explr_target,
                          &regdata4,
                          op_size,
                          DEVICE_MMIO_ADDRESS(
                              CNFG2MMIO_ADDR(EXPLR_OC_O0MBIT_O0DID_LSB),
                              op_size));
        if(l_err != nullptr)
        {
            errlCommit(l_err, CXXTEST_COMP_ID);
            TS_FAIL("testExplrMMIO> Error for config read, RC=0x%04X",
                    ERRL_GETRC_SAFE(l_err));
        }

        // valid write to config space register
        op_size = sizeof(regdata4);
        l_err = DeviceFW::deviceWrite(
                          explr_target,
                          &regdata4,
                          op_size,
                          DEVICE_MMIO_ADDRESS(
                              CNFG2MMIO_ADDR(EXPLR_OC_O0CCD_LSB),
                              op_size));
        if(l_err != nullptr)
        {
            errlCommit(l_err, CXXTEST_COMP_ID);
            TS_FAIL("testExplrMMIO> Error for config write, RC=0x%04X",
                    ERRL_GETRC_SAFE(l_err));
        }

        // 1st valid write to SCOM register (also sets up
        // tests for forcing HW read/write failures)
        // Set the PCB error bits (8:10) to binary 100, which means
        // 'invalid address'
        // NOTE: must byteswap to little endian before writing
        uint64_t GIF2PCB_INVALID_SCOM_ADDR_ERROR = 0x0080000000000000ull;
        l_buffer64 = BYTESWAP64(GIF2PCB_INVALID_SCOM_ADDR_ERROR);
        op_size = sizeof(l_buffer64);
        l_err = DeviceFW::deviceWrite(
                          explr_target,
                          &l_buffer64,
                          op_size,
                          DEVICE_MMIO_ADDRESS(
                             SCOM2MMIO_ADDR(
                                 EXPLR_TP_MB_UNIT_TOP_GIF2PCB_ERROR_REG),
                             op_size));
        if(l_err != nullptr)
        {
            errlCommit(l_err, CXXTEST_COMP_ID);
            TS_FAIL("testExplrMMIO> Error for gif2pcb write, RC=0x%04X",
                    ERRL_GETRC_SAFE(l_err));
            return;
        }

        // 2nd valid write to SCOM register (also sets up
        // tests for forcing HW read/write failures)
        // This register should contain a copy of the GIF2PCB error register
        // starting at bit 32
        // NOTE: must byteswap to little endian before writing data
        uint64_t PIB2GIF_INVALID_SCOM_ADDR_ERROR =
                        0x0000000000000000ull |
                        ((GIF2PCB_INVALID_SCOM_ADDR_ERROR &
                          0xffffc00000000000ull) >> 32);
        l_buffer64 = BYTESWAP64(PIB2GIF_INVALID_SCOM_ADDR_ERROR);
        op_size = sizeof(l_buffer64);
        l_err = DeviceFW::deviceWrite(
                          explr_target,
                          &l_buffer64,
                          op_size,
                          DEVICE_MMIO_ADDRESS(
                                SCOM2MMIO_ADDR(
                                    EXPLR_TP_MB_UNIT_TOP_PIB2GIF_ERROR_REG),
                                op_size));

        if(l_err != nullptr)
        {
            errlCommit(l_err, CXXTEST_COMP_ID);
            TS_FAIL("testExplrMMIO> Error for pib2gif write, RC=0x%04X",
                    ERRL_GETRC_SAFE(l_err));
            return;
        }

#if 0 //@fixme - RTC:211487
        // Write to an "invalid" scom address.  Should
        // return with failure (now that we've set up the error regs).
        // NOTE: Also, writing MMIO_OCMB_UE_DETECTED to this register
        //       sets up the following read to the same register
        //       to fail.
        l_buffer64 = MMIO_OCMB_UE_DETECTED;
        op_size = sizeof(l_buffer64);
        l_err = DeviceFW::deviceWrite(
                          explr_target,
                          &l_buffer64,
                          op_size,
                          DEVICE_MMIO_ADDRESS(
                              SCOM2MMIO_ADDR(EXPLR_INVALID_SCOM_ADDR),
                              op_size));

        if(l_err == nullptr)
        {
            TS_FAIL("testExplrMMIO> "
                    "did not recieve expected failure on mmio write");
            return;
        }
        else
        {
            TS_INFO("testExplrMMIO> recieved expected failure on mmio write");
            errlCommit(l_err, CXXTEST_COMP_ID);
        }

        // Read from an "invalid" scom address.  Should
        // return with failure (now that we've se up the error regs).
        op_size = sizeof(l_buffer64);
        l_err = DeviceFW::deviceRead(
                          explr_target,
                          &l_buffer64,
                          op_size,
                          DEVICE_MMIO_ADDRESS(
                              SCOM2MMIO_ADDR(EXPLR_INVALID_SCOM_ADDR),
                              op_size));
        if(l_err == nullptr)
        {
            TS_INFO("testExplrMMIO> data read from invalid address: 0x%016llx",
                    l_buffer64);
            TS_FAIL("testExplrMMIO> "
                    "did not recieve expected failure on mmio read");
        }
        else
        {
            TS_INFO("testExplrMMIO> recieved expected failure on mmio read");
            errlCommit(l_err, CXXTEST_COMP_ID);
        }
#endif //@fixme - RTC:211487

        TS_INFO("testExplrMMIO> Done");
    };
};
