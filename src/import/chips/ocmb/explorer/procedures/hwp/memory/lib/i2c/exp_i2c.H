/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/ocmb/explorer/procedures/hwp/memory/lib/i2c/exp_i2c.H $ */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2018,2019                        */
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
/// @file exp_i2c.H
/// @brief explorer I2C utility function declarations
///
// *HWP HWP Owner: Andre A. Marin <aamarin@us.ibm.com>
// *HWP HWP Backup: Louis Stermole <stermole@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 2
// *HWP Consumed by: HB:FSP

#ifndef _MSS_EXP_I2C_H_
#define _MSS_EXP_I2C_H_

#include <fapi2.H>
#include <i2c_access.H>

#include <vector>
#include <lib/i2c/exp_i2c_fields.H>
#include <generic/memory/lib/utils/pos.H>
#include <generic/memory/lib/utils/endian_utils.H>
#include <generic/memory/lib/utils/poll.H>

namespace mss
{
namespace exp
{
namespace i2c
{
namespace check
{

///
/// @brief Checks the I2c explorer status codes
/// @param[in] i_target the OCMB target
/// @param[in] i_cmd_id the command ID
/// @param[in] i_data data to check from EXP_FW_STATUS
/// @param[out] o_busy true if explorer returns FW_BUSY status, false otherwise
///
inline fapi2::ReturnCode status_code( const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
                                      const uint8_t i_cmd_id,
                                      const std::vector<uint8_t>& i_data,
                                      bool& o_busy )
{
    // Set o_busy to false just in case we don't make it to where we check it
    o_busy = false;

    // Set to a high number to make sure check for SUCCESS (== 0) isn't a fluke
    uint8_t l_status = ~(0);
    FAPI_TRY( status::get_status_code(i_target, i_data, l_status) );

    // We need to try again if we get a FW_BUSY status, so set the flag
    if (l_status == status_codes::FW_BUSY)
    {
        o_busy = true;
        return fapi2::FAPI2_RC_SUCCESS;
    }

    // Technically many cmds have their own status code decoding..but SUCCESS is always 0.
    // If it's anything else we can just look up the status code
    FAPI_ASSERT( l_status == status_codes::SUCCESS,
                 fapi2::MSS_EXP_I2C_FW_STATUS_CODE_FAILED().
                 set_TARGET(i_target).
                 set_STATUS_CODE(l_status).
                 set_CMD_ID(i_cmd_id),
                 "Status code did not return SUCCESS (%d), received (%d) for %s",
                 status_codes::SUCCESS, l_status, mss::c_str(i_target) );

    return fapi2::FAPI2_RC_SUCCESS;

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Checks the I2c explorer boot stage for FUNTIME_FW
/// @param[in] i_target the OCMB target
/// @param[in] i_data data to check from EXP_FW_STATUS
///
inline fapi2::ReturnCode runtime_boot_stage( const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
        const std::vector<uint8_t>& i_data )
{
    constexpr uint8_t EXPECTED_BOOT_STAGE = boot_stages::RUNTIME_FW;
    uint8_t l_boot_stage = 0;
    FAPI_TRY( status::get_boot_stage(i_target, i_data, l_boot_stage) );

    // Check that Explorer is in the RUNTIME_FW boot stage
    FAPI_ASSERT( (l_boot_stage == EXPECTED_BOOT_STAGE),
                 fapi2::MSS_EXP_I2C_WRONG_BOOT_STAGE().
                 set_TARGET(i_target).
                 set_BOOT_STAGE(l_boot_stage).
                 set_EXPECTED_BOOT_STAGE(EXPECTED_BOOT_STAGE),
                 "FW_STATUS command returned wrong boot stage (0x%01x, expected 0x%01x) for %s",
                 l_boot_stage, EXPECTED_BOOT_STAGE, mss::c_str(i_target) );

    return fapi2::FAPI2_RC_SUCCESS;

fapi_try_exit:
    return fapi2::current_err;
}

}// check

///
/// @brief EXP_FW_STATUS setup helper function - useful for testing
/// @param[out] o_size the size of data
/// @param[out] o_cmd_id the explorer command ID
///
inline void fw_status_setup(size_t& o_size,
                            std::vector<uint8_t>& o_cmd_id)
{
    o_size = FW_STATUS_BYTE_LEN;
    o_cmd_id.clear();
    o_cmd_id.push_back(FW_STATUS);
}

///
/// @brief get EXP_FW_STATUS bytes
/// @param[in] i_target the OCMB target
/// @return FAPI2_RC_SUCCESS iff okay
///
inline fapi2::ReturnCode get_fw_status(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
                                       std::vector<uint8_t>& o_data)
{
    // Retrieve setup data
    size_t l_size = 0;
    std::vector<uint8_t> l_cmd_id;
    fw_status_setup(l_size, l_cmd_id);

    // Get data and check for errors
    FAPI_TRY(fapi2::getI2c(i_target, l_size, l_cmd_id, o_data));
    FAPI_DBG( "status returned ( 5 bytes ) : 0x%.02X 0x%.02X 0x%.02X 0x%.02X 0x%.02X",
              o_data[0], o_data[1] , o_data[2], o_data[3], o_data[4]);
fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief EXP_FW_STATUS
/// @param[in] i_target the OCMB target
/// @return FAPI2_RC_SUCCESS iff okay
///
inline fapi2::ReturnCode fw_status(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target)
{
    constexpr uint64_t NUM_LOOPS = 50;
    // So, why aren't we using the memory team's polling API?
    // This is a base function that will be utilized by the platform code
    // As such, we don't want to pull in more libraries than we need to: it would cause extra dependencies
    // So, we're decomposing the polling library below
    bool l_busy = true;
    uint64_t l_loop = 0;

    // Loop until we max our our loop count or get a doorbell response
    for(; l_loop < NUM_LOOPS && l_busy; ++l_loop)
    {
        std::vector<uint8_t> l_data;
        FAPI_TRY( get_fw_status(i_target, l_data) );
        FAPI_TRY( check::status_code(i_target, FW_STATUS, l_data, l_busy) );
        FAPI_TRY( check::runtime_boot_stage(i_target, l_data) );

        if (l_busy)
        {
            FAPI_INF( "%s reutrned FW_BUSY status. Retrying...", mss::c_str(i_target) );
            FAPI_TRY( fapi2::delay( DELAY_100NS, 200) );
        }
    }

    FAPI_DBG("%s stopped on loop%u/%u. %s",
             mss::c_str(i_target), l_loop, NUM_LOOPS, (l_busy ? "FW_BUSY" : "SUCCESS"));

    // Check that Explorer is not still in FW_BUSY state
    FAPI_ASSERT( !l_busy,
                 fapi2::MSS_EXP_I2C_FW_STATUS_BUSY().
                 set_TARGET(i_target),
                 "Polling timeout on FW_STATUS command (still FW_BUSY) for %s",
                 mss::c_str(i_target) );

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief EXP_FW_BOOT_CONFIG setup
/// @param[in,out] io_data the data to go to boot config
///
inline void boot_config_setup(std::vector<uint8_t>& io_data)

{

    // Need data length as well - boot config can only ever be written
    io_data.insert(io_data.begin(), FW_BOOT_CONFIG_BYTE_LEN);

    // Then add the command
    io_data.insert(io_data.begin(), FW_BOOT_CONFIG);

    // Written commands need to be in the form of (MSB first). Confirmed by hardware characterization team.
    // CMD
    // DATA LEN
    // DATA3
    // DATA2
    // DATA1
    // DATA0
}

///
/// @brief EXP_FW_BOOT_CONFIG
/// @param[in] i_target the OCMB target
/// @param[in] i_data the data to write
/// @return FAPI2_RC_SUCCESS iff okay
///
inline fapi2::ReturnCode boot_config(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
                                     const std::vector<uint8_t>& i_data)
{
    // Retrieve setup data
    std::vector<uint8_t> l_configured_data(i_data);
    boot_config_setup(l_configured_data);

    // Get data and check for errors
    FAPI_TRY(fapi2::putI2c(i_target, l_configured_data));
    FAPI_TRY(fw_status(i_target));

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Checks if the I2C interface returns an ACK
/// @param[in] i_target the OCMB target
/// @return FAPI2_RC_SUCCESS iff okay
///
inline fapi2::ReturnCode is_ready(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target)
{
    // We send a simple but valid command to poll the I2C
    // Arbitrarily send an EXP_FW_STATUS command id
    size_t l_size = 0;
    std::vector<uint8_t> l_cmd_id;
    fw_status_setup(l_size, l_cmd_id);

    // We just ignore the data.  We'll see FAPI2_RC_SUCCESS if
    // the I2C returns an ACK.
    std::vector<uint8_t> l_data;
    return fapi2::getI2c(i_target, l_size, l_cmd_id, l_data);
}

///
/// @brief Helper function for exp_check_for_ready
/// @param[in] i_target the controller
/// @param[in] i_poll_count the number of times to run the fw_status command (default = 50)
/// @param[in] i_delay delay in ns between fw_status command attempts (default = 200ns)
/// @return FAPI2_RC_SUCCESS iff ok
///
inline fapi2::ReturnCode exp_check_for_ready_helper(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
        const uint64_t i_poll_count = DEFAULT_POLL_LIMIT,
        const uint64_t i_delay = 200)
{
    // Using using default parameters from class, with overrides for delay and poll_count
    mss::poll_parameters l_poll_params(DELAY_10NS,
                                       200,
                                       i_delay,
                                       200,
                                       i_poll_count);

    // From MSCC explorer firmware arch spec
    // 4.1.5: After power-up, the Explorer Chip will respond with NACK to all incoming I2C requests
    // from the HOST until the I2C slave interface is ready to receive commands.
    FAPI_ASSERT( mss::poll(i_target, l_poll_params, [i_target]()->bool
    {
        return mss::exp::i2c::is_ready(i_target) == fapi2::FAPI2_RC_SUCCESS;
    }),
    fapi2::MSS_EXP_I2C_POLLING_TIMEOUT().
    set_TARGET(i_target),
    "Failed to see an ACK from I2C -- polling timeout on %s",
    mss::c_str(i_target) );

    // We send the EXP_FW_STATUS command as a sanity check to see if it returns SUCCESS
    FAPI_ASSERT( mss::poll(i_target, l_poll_params, [i_target]()->bool
    {
        return mss::exp::i2c::fw_status(i_target) == fapi2::FAPI2_RC_SUCCESS;
    }),
    fapi2::MSS_EXP_STATUS_POLLING_TIMEOUT().
    set_TARGET(i_target),
    "Failed to see a successful return code -- polling timeout on %s",
    mss::c_str(i_target) );

    return fapi2::FAPI2_RC_SUCCESS;

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Perform a register write operation on the given OCMB chip
/// @param[in] i_target the OCMB target
/// @param[in] i_addr   The translated address on the OCMB chip
/// @param[in] i_data_buffer buffer of data we want to write to the register
/// @return FAPI2_RC_SUCCESS iff okay
///
inline  fapi2::ReturnCode fw_reg_write(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
                                       const uint32_t i_addr,
                                       const fapi2::buffer<uint32_t>& i_data_buffer)
{
    // create byte vector that will hold command bytes in sequence that will do the scom
    std::vector<uint8_t> l_cmd_vector;
    std::vector<uint8_t> l_be_vector;

    uint32_t l_input_data = static_cast<uint32_t>(i_data_buffer);

    // Start building the cmd vector for the write operation
    l_cmd_vector.push_back(FW_REG_WRITE);              // Byte 0 = 0x05 (FW_REG_WRITE)
    l_cmd_vector.push_back(FW_WRITE_REG_DATA_SIZE);    // Byte 1 = 0x08 (FW_SCOM_DATA_SIZE)

    // i_addr and i_data_buffer were converted to LE above so we can
    // write them directly to the cmd_vector in the same order they
    // currently are
    // Byte 2:5 = Address
    forceBE(i_addr, l_be_vector);
    l_cmd_vector.insert(l_cmd_vector.end(), l_be_vector.begin(), l_be_vector.end());

    l_be_vector.clear();
    forceBE(l_input_data, l_be_vector);

    // Byte 6:9 = Data
    l_cmd_vector.insert(l_cmd_vector.end(), l_be_vector.begin(), l_be_vector.end());

    // Use fapi2 putI2c interface to execute command
    FAPI_TRY(fapi2::putI2c(i_target, l_cmd_vector),
             "I2C FW_REG_WRITE op failed to write to 0x%.8X on OCMB w/ fapiPos = 0x%.8X",
             i_addr, mss::fapi_pos(i_target));

    // Check status of operation
    FAPI_TRY(fw_status(i_target),
             "Invalid Status after FW_REG_WRITE operation to 0x%.8X on OCMB w/ fapiPos = 0x%.8X",
             i_addr, mss::fapi_pos(i_target));


fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Perform a register write operation on the given OCMB chip
/// @param[in] i_target the OCMB target
/// @param[in] i_addr   The translated address on the OCMB chip
/// @param[in] o_data_buffer buffer of data we will write the contents of the register to
/// @return FAPI2_RC_SUCCESS iff okay
///
inline fapi2::ReturnCode fw_reg_read(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target,
                                     const uint32_t i_addr,
                                     fapi2::buffer<uint32_t>& o_data_buffer)
{
    // create byte vector that will hold command bytes in sequence that will do the scom
    std::vector<uint8_t> l_cmd_vector;
    std::vector<uint8_t> l_tmp_vector;

    // Flush o_data_buffer w/ all 0's to avoid stale data
    o_data_buffer.flush<0>();

    // Force the address to be BE
    forceBE(i_addr, l_tmp_vector);

    // Build the cmd vector for the Read
    l_cmd_vector.push_back(FW_REG_ADDR_LATCH);         // Byte 0 = 0x03 (FW_REG_ADDR_LATCH)
    l_cmd_vector.push_back(FW_REG_ADDR_LATCH_SIZE);    // Byte 1 = 0x04 (FW_REG_ADDR_LATCH_SIZE)

    // i_addr was converted to BE above so we can write it
    // directly to the cmd_vector in the same order it
    // currently is in
    // Byte 2:5 = Address
    l_cmd_vector.insert(l_cmd_vector.end(), l_tmp_vector.begin(), l_tmp_vector.end());

    // Use fapi2 putI2c interface to execute command
    FAPI_TRY(fapi2::putI2c(i_target, l_cmd_vector),
             "putI2c returned error for FW_REG_ADDR_LATCH operation to 0x%.8X on OCMB w/ fapiPos = 0x%.8X",
             i_addr, mss::fapi_pos(i_target));

    // Check i2c status after operation
    FAPI_TRY(fw_status(i_target),
             "Invalid Status after FW_REG_ADDR_LATCH operation to 0x%.8X on OCMB w/ fapiPos = 0x%.8X",
             i_addr, mss::fapi_pos(i_target));

    // Clear out the tmp_vector because we will re-use as the read buffer
    l_tmp_vector.clear();

    // Clear out cmd vector as i2c op is complete and we must prepare for next
    l_cmd_vector.clear();

    // Cmd vector is a single byte with FW_REG_READ code
    l_cmd_vector.push_back(FW_REG_READ); // Byte 0 = 0x04 (FW_REG_READ)
    l_cmd_vector.push_back(0x4); // Remaining bytes dont matter to HB firmware
    l_cmd_vector.push_back(0x0); // but the hw is expecting something there so
    l_cmd_vector.push_back(0x0); // we should write something
    l_cmd_vector.push_back(0x0);
    l_cmd_vector.push_back(0x0);

    // Use fapi2 getI2c interface to execute command
    FAPI_TRY(fapi2::getI2c(i_target, FW_I2C_SCOM_READ_SIZE,  l_cmd_vector, l_tmp_vector),
             "getI2c returned error for FW_REG_READ operation to 0x%.8X on OCMB w/ fapiPos = 0x%.8X",
             i_addr, mss::fapi_pos(i_target));

    // The first byte returned should be the size of the remaining data
    // We requested FW_REG_ADDR_LATCH_SIZE bytes so that is what we
    // expect to see as the first byte.
    FAPI_ASSERT(  (l_tmp_vector.front() == FW_REG_ADDR_LATCH_SIZE),
                  fapi2::I2C_GET_SCOM_INVALID_READ_SIZE()
                  .set_TARGET(i_target)
                  .set_ADDRESS(i_addr)
                  .set_SIZE_RETURNED(l_tmp_vector[0])
                  .set_SIZE_REQUESTED(FW_REG_ADDR_LATCH_SIZE),
                  "First byte of read data was expected to be 0x%lx but byte read = 0x%x",
                  FW_REG_ADDR_LATCH_SIZE, l_tmp_vector[0] );

    // Check i2c status after operation
    FAPI_TRY(fw_status(i_target),
             "Invalid Status after FW_REG_READ operation to 0x%.8X on OCMB w/ fapiPos = 0x%.8X",
             i_addr, mss::fapi_pos(i_target));

    // Build uint32_t from bytes 1-4 of the returned data. Bytes are
    // returned in BE so no translation neccesary. Faster to just access
    // the 4 bytes and shift than to perform vector operations to pop off front
    // entry and convert vector to uint32.
    o_data_buffer = ( l_tmp_vector[1] << 24 |
                      l_tmp_vector[2] << 16 |
                      l_tmp_vector[3] << 8 |
                      l_tmp_vector[4]);
fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Perform a register write operation on the given OCMB chip
/// @param[in] i_addr   The raw address that needs to be translated to IBM scom addr
/// @param[in] i_side   LHS or RHS of the IBM i2c scom. IBM addresses expect 64 bits of
///                     data returned from them so we must have a LHS and a RHS which is offset
///                     by 4 bytes. This is because the OCMB is a 32 bit architecture
/// @return uint32 of translated address
///
inline uint32_t trans_ibm_i2c_scom_addr(const uint32_t i_addr,
                                        const addrSide i_side)
{
    return (i_side == LHS) ?
           ((LAST_THREE_BYTES_MASK & i_addr) << OCMB_ADDR_SHIFT) | IBM_SCOM_OFFSET_LHS | OCMB_UNCACHED_OFFSET :
           ((LAST_THREE_BYTES_MASK & i_addr) << OCMB_ADDR_SHIFT) | IBM_SCOM_OFFSET_RHS | OCMB_UNCACHED_OFFSET ;
}

///
/// @brief Perform a register write operation on the given OCMB chip
/// @param[in] i_addr   The raw address that needs to be translated to Microchip scom addr
/// @return uint32 of translated address
///
inline uint32_t trans_micro_i2c_scom_addr(const uint32_t i_addr)
{
    return (i_addr | OCMB_UNCACHED_OFFSET) ;
}

///
/// @brief Issue the DOWNLOAD command to the given OCMB chip
/// @param[in] i_target the OCMB target
/// @return FAPI2_RC_SUCCESS iff okay
///
inline  fapi2::ReturnCode fw_download(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target)
{
    // create byte vector that will hold command bytes in sequence that will do the scom
    std::vector<uint8_t> l_download_cmd;
    std::vector<uint8_t> l_status_data;
    uint8_t              l_boot_stage = 0;

    // Read status to get the current boot_stage
    FAPI_TRY(get_fw_status(i_target, l_status_data));

    // Extract the boot_stage value
    FAPI_TRY(status::get_boot_stage(i_target, l_status_data, l_boot_stage));

    // Check that we are in the BOOT_ROM or FW_UPGRADE stage of booting.
    // The FW_DOWNLOAD command can only be sent in one of these modes
    // (see table 13-1, pboot flowchart in FW arch doc for more info)
    FAPI_ASSERT(((l_boot_stage == BOOT_ROM_STAGE) ||
                 (l_boot_stage == FW_UPGRADE_MODE)),
                fapi2::MSS_EXP_I2C_FW_DOWNLOAD_INVALID_STATE().
                set_TARGET(i_target).
                set_BOOT_STAGE(l_boot_stage).
                set_STATUS_DATA(l_status_data),
                "Invalid boot stage[0x%02x] for FW_DOWNLOAD command on %s",
                l_boot_stage, mss::c_str(i_target));

    // Start building the cmd vector for the write operation
    // Byte 0 = 0x06 (FW_DOWNLOAD)
    l_download_cmd.push_back(FW_DOWNLOAD);

    // Use fapi2 putI2c interface to execute command
    FAPI_TRY(fapi2::putI2c(i_target, l_download_cmd),
             "I2C FW_DOWNLOAD op failed to send FW_DOWNLOAD cmd to %s",
             mss::c_str(i_target));

    // NOTE: The EXP_FW_STATUS command will not work after sending the
    //       EXP_FW_DOWNLOAD because we will be in TWI mode from this point on.

fapi_try_exit:
    return fapi2::current_err;
}


}// i2c
}// exp
}// mss

#endif
