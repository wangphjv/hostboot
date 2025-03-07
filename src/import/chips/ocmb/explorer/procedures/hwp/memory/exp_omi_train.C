/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/ocmb/explorer/procedures/hwp/memory/exp_omi_train.C $ */
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
/// @file exp_omi_train.C
/// @brief Contains the explorer OMI train
///
// *HWP HWP Owner: Andre Marin <aamarin@us.ibm.com>
// *HWP HWP Backup: Stephen Glancy <sglancy@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 3
// *HWP Consumed by: Memory

#include <fapi2.H>
#include <generic/memory/lib/utils/c_str.H>
#include <lib/omi/exp_omi_utils.H>
#include <lib/i2c/exp_i2c.H>
#include <exp_omi_train.H>
#include <generic/memory/mss_git_data_helper.H>

extern "C"
{

    ///
    /// @brief Trains the OCMB link
    /// @param[in] i_target the OCMB target to operate on
    /// @return FAPI2_RC_SUCCESS iff ok
    ///
    fapi2::ReturnCode exp_omi_train(const fapi2::Target<fapi2::TARGET_TYPE_OCMB_CHIP>& i_target)
    {
        mss::display_git_commit_info("exp_omi_train");

        std::vector<uint8_t> l_data;

        // Gets the data setup
        FAPI_TRY(mss::exp::omi::train::setup_fw_boot_config(i_target, l_data));

        // Issues the command and checks for completion
        // Note: the status check also checks for the OMI training completion, so after we run this command, we're good to go
        FAPI_TRY(mss::exp::i2c::boot_config(i_target, l_data));

    fapi_try_exit:
        return fapi2::current_err;
    }
}
