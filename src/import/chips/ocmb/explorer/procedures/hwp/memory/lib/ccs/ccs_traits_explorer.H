/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/ocmb/explorer/procedures/hwp/memory/lib/ccs/ccs_traits_explorer.H $ */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2015,2019                        */
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

///
/// @file ccs_traits_nimbus.H
/// @brief Run and manage the CCS engine
///
// *HWP HWP Owner: Matthew Hickman <Matthew.Hickman@ibm.com>
// *HWP HWP Backup: Stephen Glancy <sglancy@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 3
// *HWP Consumed by: HB:FSP

#ifndef _MSS_CCS_TRAITS_EXP_H_
#define _MSS_CCS_TRAITS_EXP_H_

#include <fapi2.H>
#include <explorer_scom_addresses.H>
#include <explorer_scom_addresses_fld.H>
#include <lib/shared/exp_consts.H>
#include <generic/memory/lib/utils/shared/mss_generic_consts.H>
#include <generic/memory/lib/mss_generic_attribute_getters.H>
#include <generic/memory/lib/ccs/ccs_traits.H>

///
/// @class ccsTraits
/// @brief Explorer CCS Engine traits
///
template<>
class ccsTraits<mss::mc_type::EXPLORER>
{
    public:
        static constexpr fapi2::TargetType PORT_TARGET_TYPE = fapi2::TARGET_TYPE_MEM_PORT;
        static constexpr uint64_t MODEQ_REG = EXPLR_MCBIST_CCS_MODEQ;
        static constexpr uint64_t MCB_CNTL_REG = EXPLR_MCBIST_MCB_CNTLQ;
        static constexpr uint64_t CNTLQ_REG = EXPLR_MCBIST_CCS_CNTLQ;
        static constexpr uint64_t STATQ_REG = EXPLR_MCBIST_CCS_STATQ;

        static constexpr uint64_t PORTS_PER_MC_TARGET = mss::exp::MAX_PORT_PER_OCMB;
        static constexpr uint64_t CCS_MAX_DIMM_PER_PORT = mss::exp::MAX_DIMM_PER_PORT;
        static constexpr uint64_t CCS_MAX_MRANK_PER_PORT = mss::exp::MAX_MRANK_PER_PORT;
        static constexpr uint64_t CCS_MAX_RANK_PER_DIMM = mss::exp::MAX_RANK_PER_DIMM;
        static constexpr uint64_t CCS_MAX_RANKS_DIMM1 = mss::exp::MAX_RANKS_DIMM1;

        static constexpr uint64_t NTTM_READ_DELAY = 0x40;
        static constexpr uint64_t NTTM_MODE_FORCE_READ = 33;


        // Command Pass Disable Delay Time for Explorer - really a JEDEC timing
        static constexpr uint64_t TIMING_TCPDED = 4;

        enum
        {
            // Non address values that are needed for helper functions

            // ODT values used for beautification
            // Attribute locations
            ATTR_ODT_DIMM0_R0 = 0,
            ATTR_ODT_DIMM0_R1 = 1,
            ATTR_ODT_DIMM1_R0 = 4,
            ATTR_ODT_DIMM1_R1 = 5,

            // Right justified output - makes it so we can use insertFromRight
            CCS_ODT_DIMM0_R0 = 4,
            CCS_ODT_DIMM0_R1 = 5,
            CCS_ODT_DIMM1_R0 = 6,
            CCS_ODT_DIMM1_R1 = 7,

            // Default ODT cycle length is 5 - one for the preamble and 4 for the data
            DEFAULT_ODT_CYCLE_LEN = 5,

            // CCS MODEQ
            STOP_ON_ERR = EXPLR_MCBIST_CCS_MODEQ_STOP_ON_ERR,
            UE_DISABLE = EXPLR_MCBIST_CCS_MODEQ_UE_DISABLE,
            DATA_COMPARE_BURST_SEL = EXPLR_MCBIST_CCS_MODEQ_DATA_COMPARE_BURST_SEL,
            DATA_COMPARE_BURST_SEL_LEN = EXPLR_MCBIST_CCS_MODEQ_DATA_COMPARE_BURST_SEL_LEN,
            DDR_CAL_TIMEOUT_CNT = EXPLR_MCBIST_CCS_MODEQ_DDR_CAL_TIMEOUT_CNT,
            DDR_CAL_TIMEOUT_CNT_LEN = EXPLR_MCBIST_CCS_MODEQ_DDR_CAL_TIMEOUT_CNT_LEN,
            CFG_PARITY_AFTER_CMD = EXPLR_MCBIST_CCS_MODEQ_CFG_PARITY_AFTER_CMD,
            COPY_CKE_TO_SPARE_CKE = EXPLR_MCBIST_CCS_MODEQ_COPY_CKE_TO_SPARE_CKE,
            DISABLE_ECC_ARRAY_CHK = EXPLR_MCBIST_CCS_MODEQ_DISABLE_ECC_ARRAY_CHK,
            DISABLE_ECC_ARRAY_CORRECTION = EXPLR_MCBIST_CCS_MODEQ_DISABLE_ECC_ARRAY_CORRECTION,
            CFG_DGEN_FIXED_MODE = EXPLR_MCBIST_CCS_MODEQ_CFG_DGEN_FIXED_MODE,
            DDR_CAL_TIMEOUT_CNT_MULT = EXPLR_MCBIST_CCS_MODEQ_DDR_CAL_TIMEOUT_CNT_MULT,
            DDR_CAL_TIMEOUT_CNT_MULT_LEN = EXPLR_MCBIST_CCS_MODEQ_DDR_CAL_TIMEOUT_CNT_MULT_LEN,
            IDLE_PAT_ADDRESS_0_13 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ADDRESS_0_13,
            IDLE_PAT_ADDRESS_0_13_LEN = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ADDRESS_0_13_LEN,
            IDLE_PAT_ADDRESS_17 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ADDRESS_17,
            IDLE_PAT_BANK_GROUP_1 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_BANK_GROUP_1,
            IDLE_PAT_BANK_0_1 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_BANK_0_1,
            IDLE_PAT_BANK_0_1_LEN = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_BANK_0_1_LEN,
            IDLE_PAT_BANK_GROUP_0 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_BANK_GROUP_0,
            IDLE_PAT_ACTN = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ACTN,
            IDLE_PAT_ADDRESS_16 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ADDRESS_16,
            IDLE_PAT_ADDRESS_15 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ADDRESS_15,
            IDLE_PAT_ADDRESS_14 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_ADDRESS_14,
            NTTM_MODE = EXPLR_MCBIST_CCS_MODEQ_NTTM_MODE,
            NTTM_RW_DATA_DLY = EXPLR_MCBIST_CCS_MODEQ_NTTM_RW_DATA_DLY,
            NTTM_RW_DATA_DLY_LEN = EXPLR_MCBIST_CCS_MODEQ_NTTM_RW_DATA_DLY_LEN,
            IDLE_PAT_BANK_2 = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_BANK_2,
            DDR_PARITY_ENABLE = EXPLR_MCBIST_CCS_MODEQ_DDR_PARITY_ENABLE,
            IDLE_PAT_PARITY = EXPLR_MCBIST_CCS_MODEQ_IDLE_PAT_PARITY,

            // CCS CNTL
            CCS_START = EXPLR_MCBIST_CCS_CNTLQ_START,
            CCS_STOP = EXPLR_MCBIST_CCS_CNTLQ_STOP,

            // CCS STATQ
            CCS_IN_PROGRESS = EXPLR_MCBIST_CCS_STATQ_IP,

            // ARR0
            ARR0_DDR_ADDRESS_0_13 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_0_13,
            ARR0_DDR_ADDRESS_0_13_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_0_13_LEN,
            ARR0_DDR_ADDRESS_0_9 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_0_13, // Useful for rd/wr cmds
            ARR0_DDR_ADDRESS_0_9_LEN = 10, // CA bits are 9:0, total length of 10
            ARR0_DDR_ADDRESS_10 = 10, // ADR10 is the 10th bit from the left in Nimbus ARR0
            ARR0_DDR_ADDRESS_17 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_17,
            ARR0_DDR_BANK_GROUP_1 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_BANK_GROUP_1,
            ARR0_DDR_RESETN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_RESETN,
            ARR0_DDR_BANK_0_1 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_BANK_0_1,
            ARR0_DDR_BANK_0_1_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_BANK_0_1_LEN,
            ARR0_DDR_BANK_GROUP_0 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_BANK_GROUP_0,
            ARR0_DDR_ACTN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ACTN,
            ARR0_DDR_ADDRESS_16 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_16,
            ARR0_DDR_ADDRESS_15 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_15,
            ARR0_DDR_ADDRESS_14 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ADDRESS_14,
            ARR0_DDR_CKE = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CKE,
            ARR0_DDR_CKE_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CKE_LEN,
            ARR0_DDR_CSN_0_1 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CSN_0_1,
            ARR0_DDR_CSN_0_1_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CSN_0_1_LEN,
            ARR0_DDR_CID_0_1 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CID_0_1,
            ARR0_DDR_CID_0_1_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CID_0_1_LEN,
            ARR0_DDR_CSN_2_3 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CSN_2_3,
            ARR0_DDR_CSN_2_3_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CSN_2_3_LEN,
            ARR0_DDR_CID_2 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CID_2,
            ARR0_DDR_ODT = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ODT,
            ARR0_DDR_ODT_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_ODT_LEN,
            ARR0_DDR_CAL_TYPE = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CAL_TYPE,
            ARR0_DDR_CAL_TYPE_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_CAL_TYPE_LEN,
            ARR0_DDR_PARITY = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_PARITY,
            ARR0_DDR_BANK_2 = EXPLR_MCBIST_CCS_INST_ARR0_00_DDR_BANK_2,
            ARR0_LOOP_BREAK_MODE = EXPLR_MCBIST_CCS_INST_ARR0_00_LOOP_BREAK_MODE,
            ARR0_LOOP_BREAK_MODE_LEN = EXPLR_MCBIST_CCS_INST_ARR0_00_LOOP_BREAK_MODE_LEN,

            // ARR1
            ARR1_IDLES = EXPLR_MCBIST_CCS_INST_ARR1_00_IDLES,
            ARR1_IDLES_LEN = EXPLR_MCBIST_CCS_INST_ARR1_00_IDLES_LEN,
            ARR1_REPEAT_CMD_CNT = EXPLR_MCBIST_CCS_INST_ARR1_00_REPEAT_CMD_CNT,
            ARR1_REPEAT_CMD_CNT_LEN = EXPLR_MCBIST_CCS_INST_ARR1_00_REPEAT_CMD_CNT_LEN,
            ARR1_READ_OR_WRITE_DATA = EXPLR_MCBIST_CCS_INST_ARR1_00_READ_OR_WRITE_DATA,
            ARR1_READ_OR_WRITE_DATA_LEN = EXPLR_MCBIST_CCS_INST_ARR1_00_READ_OR_WRITE_DATA_LEN,
            ARR1_READ_COMPARE_REQUIRED = EXPLR_MCBIST_CCS_INST_ARR1_00_READ_COMPARE_REQUIRED,
            ARR1_DDR_CAL_RANK = EXPLR_MCBIST_CCS_INST_ARR1_00_DDR_CAL_RANK,
            ARR1_DDR_CAL_RANK_LEN = EXPLR_MCBIST_CCS_INST_ARR1_00_DDR_CAL_RANK_LEN,
            ARR1_DDR_CALIBRATION_ENABLE = EXPLR_MCBIST_CCS_INST_ARR1_00_DDR_CALIBRATION_ENABLE,
            ARR1_END = EXPLR_MCBIST_CCS_INST_ARR1_00_END,
            ARR1_GOTO_CMD = EXPLR_MCBIST_CCS_INST_ARR1_00_GOTO_CMD,
            ARR1_GOTO_CMD_LEN = EXPLR_MCBIST_CCS_INST_ARR1_00_GOTO_CMD_LEN,

            // CCS array constants
            CCS_ARRAY_LEN = 32,
            CCS_ARR0_START = EXPLR_MCBIST_CCS_INST_ARR0_00,
            CCS_ARR1_START = EXPLR_MCBIST_CCS_INST_ARR1_00,
        };

        ///
        /// @brief Enums for CCS return codes
        ///
        enum
        {
            // Success is defined as done-bit set, no others.
            STAT_QUERY_SUCCESS   = 0x4000000000000000,

            // Bit positions 3:5
            STAT_ERR_MASK        = 0x1800000000000000,
            STAT_READ_MISCOMPARE = 0x1000000000000000,
            STAT_UE_SUE          = 0x0800000000000000,

            // If the fail type isn't one of these, we're hung
            STAT_HUNG = 0x0ull,
        };


        // CSN Regular Settings
        static constexpr std::pair<uint64_t, uint64_t> CS_N[mss::MAX_RANK_PER_DIMM] =
        {
            // CS0 L, CS1 H, CID0-> L => Rank 0
            { 0b01, 0b00 },

            // CS0 L, CS1 H, CID0-> H => Rank 1
            { 0b01, 0b11 },

            // CS0 H, CS1 L, CID0-> L => Rank 2
            { 0b10, 0b00 },

            // CS0 H, CS1 L, CID0-> H => Rank 3
            { 0b10, 0b11 },
        };


        // CSN Setup for Dual Direct Mode
        // For DIMM0 .first is the CSN_0_1 setting, .second is the CSN_2_3 setting.
        // For DIMM1 .first is the CSN_2_3 setting, .second is the CSN_0_1 setting.
        static constexpr std::pair<uint64_t, uint64_t> CS_ND[mss::MAX_RANK_PER_DIMM] =
        {
            // CS0 L CS1 H => CS2 => H CS3 => H Rank 0
            { 0b01, 0b11 },

            // CS0 H CS1 L => CS2 => H CS3 => H Rank 1
            { 0b10, 0b11 },

            // CS0 H CS1 H => CS2 => L CS3 => H Rank 2
            { 0b11, 0b01 },

            // CS0 H CS1 H => CS2 => H CS3 => L Rank 3
            { 0b11, 0b10 },
        };

        ///
        /// @brief Gets the attribute for checking our rank configuration
        /// @param[in] i_target the port target on which to operate
        /// @param[out] o_ranks the rank data
        /// @return SUCCESS iff the code executes successfully
        ///
        static fapi2::ReturnCode get_rank_config_attr(const fapi2::Target<fapi2::TARGET_TYPE_MEM_PORT>& i_target,
                uint8_t (&o_array)[2])
        {
            return mss::attr::get_num_master_ranks_per_dimm(i_target, o_array);
        }

        ///
        /// @brief Gets the attribute for checking our rank configuration
        /// @param[in] i_target the port target on which to operate
        /// @param[out] o_ranks the rank data
        /// @return The fully setup nimbus error
        ///
        static fapi2::EXP_CCS_HUNG_TRYING_TO_STOP setup_trying_to_stop_err(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>&
                i_target)
        {
            return fapi2::EXP_CCS_HUNG_TRYING_TO_STOP().set_MC_TARGET(i_target);
        }

        // Lab values
        static constexpr uint64_t LAB_MRS_CMD = 0x000008F000000000;
};

#endif
