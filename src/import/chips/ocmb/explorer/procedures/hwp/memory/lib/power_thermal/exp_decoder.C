/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/ocmb/explorer/procedures/hwp/memory/lib/power_thermal/exp_decoder.C $ */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2019                             */
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
/// @file exp_decoder.C
/// @brief Decode MSS_MRW_PWR_CURVE_SLOPE, PWR_CURVE_INTERCEPT, and THERMAL_POWER_LIMIT
///
// *HWP HWP Owner: Louis Stermole <stermole@us.ibm.com>
// *HWP HWP Backup: Andre Marin <aamarin@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 3
// *HWP Consumed by: FSP:HB

#include <lib/shared/exp_defaults.H>
// fapi2
#include <fapi2.H>
#include <vector>
#include <utility>

#include <lib/shared/exp_consts.H>
#include <lib/power_thermal/exp_decoder.H>
#include <generic/memory/lib/utils/find.H>
#include <generic/memory/lib/utils/c_str.H>
#include <generic/memory/lib/utils/dimm/kind.H>
#include <generic/memory/lib/utils/count_dimm.H>
#include <generic/memory/lib/utils/power_thermal/gen_decoder.H>

namespace mss
{
namespace power_thermal
{

const std::vector< std::pair<uint8_t , uint8_t> > throttle_traits<mss::mc_type::EXPLORER>::DIMM_TYPE_MAP =
{
    {fapi2::ENUM_ATTR_MEM_EFF_DIMM_TYPE_RDIMM, 0b00},
    {fapi2::ENUM_ATTR_MEM_EFF_DIMM_TYPE_UDIMM, 0b01},
    {fapi2::ENUM_ATTR_MEM_EFF_DIMM_TYPE_LRDIMM, 0b10},
    {fapi2::ENUM_ATTR_MEM_EFF_DIMM_TYPE_DDIMM, 0b11},
    {ANY_TYPE, 0b111}
};

///
/// @brief Finds a value for the power curve slope attributes by matching the generated hashes
/// @param[in] i_slope vector of generated key-values from POWER_CURVE_SLOPE
/// @return fapi2::ReturnCode FAPI2_RC_SUCCESS iff the encoding was successful
/// @note populates iv_vddr_slope, iv_total_slop
///
template<>
fapi2::ReturnCode decoder<mss::mc_type::EXPLORER>::find_slope (
    const std::vector< const std::vector<uint64_t>* >& i_slope)
{
    using TT = throttle_traits<mss::mc_type::EXPLORER>;

    // For explorer, two attribute are used to get slope (i_slope[0], i_slope[1])
    //   ATTR_MSS_MRW_OCMB_THERMAL_MEMORY_PWR_SLOPE is for thermal power slope
    //   ATTR_MSS_MRW_OCMB_CURRENT_CURVE_WITH_LIMIT is for power slope
    FAPI_ASSERT(i_slope.size() == 2,
                fapi2::MSS_POWER_THERMAL_ATTR_VECTORS_INCORRECT()
                .set_FUNCTION(SLOPE)
                .set_INPUT_SIZE(i_slope.size())
                .set_EXPECTED_SIZE(2),
                "The attributes vectors size is incorrect for find_slope input:%d, expected:%d",
                i_slope.size(),
                2);

    // To get thermal power slope
    get_power_thermal_value<TT::THERMAL_START, TT::THERMAL_LENGTH, SLOPE>(
        *i_slope[0],
        "ATTR_MSS_MRW_OCMB_THERMAL_MEMORY_PWR_SLOPE",
        iv_total_slope);

    // To get power slope
    get_power_thermal_value<TT::POWER_SLOPE_START, TT::POWER_SLOPE_LENGTH, SLOPE>(
        *i_slope[1],
        "ATTR_MSS_MRW_OCMB_CURRENT_CURVE_WITH_LIMIT",
        iv_vddr_slope);

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Finds a value for power curve intercept attributes by matching the generated hashes
/// @param[in] i_intercept vector of generated key-values for ATTR_MSS_MRW_POWER_CURVE_INTERCEPT
/// @return fapi2::ReturnCode FAPI2_RC_SUCCESS iff the encoding was successful
/// @note populates iv_vddr_intercept, iv_total_intercept
///
template<>
fapi2::ReturnCode decoder<mss::mc_type::EXPLORER>::find_intercept (
    const std::vector< const std::vector<uint64_t>* >& i_intercept)
{
    using TT = throttle_traits<mss::mc_type::EXPLORER>;

    // For explorer, two attribute are used to get slope (i_slope[0], i_slope[1])
    //   ATTR_MSS_MRW_OCMB_POWER_INTERCEPT is for thermal power intercept
    //   ATTR_MSS_MRW_OCMB_CURRENT_CURVE_WITH_LIMIT is for power intercept
    FAPI_ASSERT(i_intercept.size() == 2,
                fapi2::MSS_POWER_THERMAL_ATTR_VECTORS_INCORRECT()
                .set_FUNCTION(INTERCEPT)
                .set_INPUT_SIZE(i_intercept.size())
                .set_EXPECTED_SIZE(2),
                "The attributes vectors size is incorrect for find_intercept input:%d, expected:%d",
                i_intercept.size(),
                2);

    // To get thermal power intercept
    get_power_thermal_value<TT::THERMAL_START, TT::THERMAL_LENGTH, INTERCEPT>(
        *i_intercept[0],
        "ATTR_MSS_MRW_OCMB_POWER_INTERCEPT",
        iv_total_intercept);

    // To get power intercept
    get_power_thermal_value<TT::POWER_INTERCEPT_START, TT::POWER_INTERCEPT_LENGTH, INTERCEPT>(
        *i_intercept[1],
        "ATTR_MSS_MRW_OCMB_CURRENT_CURVE_WITH_LIMIT",
        iv_vddr_intercept);

fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief Finds a value from ATTR_MSS_MRW_THERMAL_MEMORY_POWER_LIMIT and stores in iv variable
/// @param[in] i_thermal_limits is a vector of the generated values from ATTR_MSS_MRW_THERMAL_POWER_LIMIT
/// @return fapi2::ReturnCode FAPI2_RC_SUCCESS iff the encoding was successful
/// @note populates thermal_power_limit.
///
template<>
fapi2::ReturnCode decoder<mss::mc_type::EXPLORER>::find_thermal_power_limit (
    const std::vector< const std::vector<uint64_t>* >& i_thermal_limits)
{
    using TT = throttle_traits<mss::mc_type::EXPLORER>;

    // For explorer, two attribute are used to get slope (i_slope[0], i_slope[1])
    //   ATTR_MSS_MRW_OCMB_THERMAL_MEMORY_POWER_LIMIT is for thermal power limit
    //   ATTR_MSS_MRW_OCMB_CURRENT_CURVE_WITH_LIMIT is for power limit
    FAPI_ASSERT(i_thermal_limits.size() == 2,
                fapi2::MSS_POWER_THERMAL_ATTR_VECTORS_INCORRECT()
                .set_FUNCTION(INTERCEPT)
                .set_INPUT_SIZE(i_thermal_limits.size())
                .set_EXPECTED_SIZE(2),
                "The attributes vectors size is incorrect for find_thermal_power_limit input:%d, expected:%d",
                i_thermal_limits.size(),
                2);

    // To get thermal power limit
    get_power_thermal_value<TT::THERMAL_START, TT::THERMAL_LENGTH, POWER_LIMIT>(
        *i_thermal_limits[0],
        "ATTR_MSS_MRW_OCMB_THERMAL_MEMORY_POWER_LIMIT",
        iv_thermal_power_limit);

    // To get power intercept
    get_power_thermal_value<TT::POWER_LIMIT_START, TT::POWER_LIMIT_LENGTH, POWER_LIMIT>(
        *i_thermal_limits[1],
        "ATTR_MSS_MRW_OCMB_CURRENT_CURVE_WITH_LIMIT",
        iv_power_limit);

fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief find the power curve attributes for each dimm on an MCS target
/// @param[in] i_targets vector of MCS targets on which dimm attrs will be set
/// @param[in] i_slope vector of generated hashes for encoding and values for MSS_MRW_POWER_SLOPE
/// @param[in] i_intercept vector of generated hashes for encoding and values for MSS_MRW_POWER_INTERCEPT
/// @param[in] i_thermal_power_limit vector of generated hashes for encoding and values for MSS_MRW_THERMAL_MEMORY_POWER_LIMIT
/// @param[out] o_vddr_slope the VDDR power curve slope for each dimm
/// @param[out] o_vddr_int the VDDR power curve intercept for each dimm
/// @param[out] o_total_slope the VDDR+VPP power curve slope for each dimm
/// @param[out] o_total_int the VDDR+VPP power curve intercept for each dimm
/// @param[out] o_thermal_power the thermal power limit for the dimm
/// @return FAPI2_RC_SUCCESS iff ok
/// @note used to set power curve attributes in calling function
/// @note decodes the attribute "encoding" to get the vddr and vddr/vpp power curves for a dimm
///
fapi2::ReturnCode get_power_attrs (const mss::throttle_type i_throttle_type,
                                   const fapi2::Target<fapi2::TARGET_TYPE_MEM_PORT>& i_port,
                                   const std::vector< uint64_t >& i_slope,
                                   const std::vector< uint64_t >& i_intercept,
                                   const std::vector< uint64_t >& i_thermal_power_limit,
                                   const std::vector< uint64_t >& i_current_curve_with_limit,
                                   uint16_t o_slope [throttle_traits<>::DIMMS_PER_PORT],
                                   uint16_t o_intercept [throttle_traits<>::DIMMS_PER_PORT],
                                   uint32_t o_limit [throttle_traits<>::DIMMS_PER_PORT])
{
    using TT = throttle_traits<mss::mc_type::EXPLORER>;

    for (const auto& l_dimm : find_targets <fapi2::TARGET_TYPE_DIMM> (i_port))
    {
        const auto l_dimm_pos = mss::index (l_dimm);
        mss::dimm::kind<> l_kind (l_dimm);
        mss::power_thermal::decoder<> l_decoder(l_kind);

        FAPI_TRY( l_decoder.generate_encoding(), "%s Error in get_power_attrs", mss::c_str(l_dimm) );

        // The first entry into these arrays must be valid
        // If we don't find any values, the attributes aren't found so go with some defaults
        if (i_slope.empty() || i_slope[0] == 0)
        {
            FAPI_INF("%s ATTR_MSS_MRW_OCMB_PWR_SLOPE not found!!", mss::c_str(l_dimm));

            o_slope[l_dimm_pos] =
                (i_throttle_type == mss::throttle_type::POWER) ? TT::POWER_SLOPE : TT::TOTAL_SLOPE;
        }
        else
        {
            const std::vector< const std::vector<uint64_t>* > l_slope {&i_slope, &i_current_curve_with_limit};

            FAPI_TRY( l_decoder.find_slope(l_slope), "%s Error in get_power_attrs", mss::c_str(l_dimm) );

            o_slope[l_dimm_pos] =
                (i_throttle_type == mss::throttle_type::POWER) ? l_decoder.iv_vddr_slope : l_decoder.iv_total_slope;
        }

        if (i_intercept.empty() || i_intercept[0] == 0)
        {
            FAPI_INF("%s ATTR_MSS_MRW_OCMB_PWR_INTERCEPT not found!!", mss::c_str(l_dimm));

            o_intercept[l_dimm_pos] =
                (i_throttle_type == mss::throttle_type::POWER) ? TT::POWER_INT : TT::TOTAL_INT;
        }
        else
        {
            const std::vector< const std::vector<uint64_t>* > l_intercept {&i_intercept, &i_current_curve_with_limit};

            FAPI_TRY( l_decoder.find_intercept(l_intercept), "%s Error in get_power_attrs", mss::c_str(l_dimm) );

            o_intercept[l_dimm_pos] =
                (i_throttle_type == mss::throttle_type::POWER) ? l_decoder.iv_vddr_intercept : l_decoder.iv_total_intercept;
        }

        if (i_thermal_power_limit.empty() || i_thermal_power_limit[0] == 0)
        {
            FAPI_INF("%s ATTR_MSS_MRW_OCMB_THERMAL_MEMORY_POWER_LIMIT not found!!", mss::c_str(l_dimm));

            // The unit of limit and intercept is cA but limit is dA in mss::throttle_type::POWER
            // So we need to transfer them to the same unit
            o_limit[l_dimm_pos] =
                (i_throttle_type == mss::throttle_type::POWER) ? TT::POWER_LIMIT * DECI_TO_CENTI : TT::THERMAL_LIMIT;
        }
        else
        {
            std::vector< const std::vector<uint64_t>* > l_thermal_power_limit {&i_thermal_power_limit, &i_current_curve_with_limit};

            FAPI_TRY( l_decoder.find_thermal_power_limit(l_thermal_power_limit),
                      "%s Error in get_power_attrs", mss::c_str(l_dimm) );
            // The unit of limit and intercept is cA but limit is dA in mss::throttle_type::POWER
            // So we need to transfer them to the same unit
            o_limit[l_dimm_pos] =
                (i_throttle_type == mss::throttle_type::POWER) ? l_decoder.iv_power_limit * DECI_TO_CENTI :
                l_decoder.iv_thermal_power_limit;
        }
    }

fapi_try_exit:
    return fapi2::current_err;
}

} //ns power_thermal
} // ns mss
