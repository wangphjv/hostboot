/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/chips/ocmb/explorer/procedures/hwp/memory/lib/power_thermal/exp_throttle_traits.H $ */
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
/// @file exp_throttle_traits.H
/// @brief throttle API
///

// *HWP HWP Owner: Andre Marin <aamarin@us.ibm.com>
// *HWP HWP Backup: Louis Stermole <stermole@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 3
// *HWP Consumed by: FSP:HB

#ifndef _MSS_EXP_THROTTLE_TRAITS_
#define _MSS_EXP_THROTTLE_TRAITS_

#include <fapi2.H>
#include <generic/memory/lib/utils/power_thermal/gen_throttle_traits.H>

namespace mss
{
namespace power_thermal
{

///
/// @class Traits and policy class for throttle code - specialization for the Explorer mc type
///
template<>
class throttle_traits<mss::mc_type::EXPLORER>
{
    public:
        //////////////////////////////////////////////////////////////
        // Target types
        //////////////////////////////////////////////////////////////
        static constexpr fapi2::TargetType MC_TARGET_TYPE = fapi2::TARGET_TYPE_OCMB_CHIP;
        static constexpr fapi2::TargetType PORT_TARGET_TYPE = fapi2::TARGET_TYPE_MEM_PORT;

        //////////////////////////////////////////////////////////////
        // Traits values
        //////////////////////////////////////////////////////////////
        // MIN_UTIL is  in c%
        static const uint64_t MIN_UTIL = 2500;
        // IDLE_UTIL is  in c%
        static const uint64_t IDLE_UTIL = 0;
        // Minimum throttle allowed for the port and or slot. If we set to 0, we brick the port
        static const uint64_t  MIN_THROTTLE = 1;

        enum size_of_attrs : size_t
        {
            // Thermal power (OCMB+DRAM)
            SIZE_OF_THERMAL_LIMIT_ATTR = 25,
            SIZE_OF_THERMAL_SLOPE_ATTR = 50,
            SIZE_OF_THERMAL_INTERCEPT_ATTR = 50,

            // Power (PMIC)
            SIZE_OF_CURRENT_CURVE_WITH_LIMIT_ATTR = 25,
        };

        enum default_power
        {
            //Values are the worst case defaults for power curves
            //They are the default/ catch-all values from the power curve attributes
            //Shouldn't be used if system is set up correctly and attributes are available
            //This will throttle the DIMMs to ~76% dram data bus utilization
            //(using the mrw regulator power limit of 1700 cW and thermal power limit here of 1940 cW).
            // TODO: Need to fill the right value. The current value is from Nimbus
            // Thermal power (OCMB+DRAM)
            TOTAL_SLOPE = 0x44C,
            TOTAL_INT = 0x44C,
            THERMAL_LIMIT = 0x794,

            // Power (PMIC)
            POWER_SLOPE = 0x41A,
            POWER_INT = 0x384,
            POWER_LIMIT = 0x794,

        };

        enum
        {
            PORTS_PER_MC = 1,
            DIMMS_PER_PORT = 2,
        };

        //Bit positions for different section of the attribute
        //first 32 bits are the encoding, second are for values
        enum DECODE_BUFFER_POS
        {
            ENCODING_START = 0,
            ENCODING_LENGTH = 32,

            // Thermal total power (OCMB+DRAM)
            THERMAL_START = 32,
            THERMAL_LENGTH = 16,

            // Current power (PMIC)
            POWER_LIMIT_START = 32,
            POWER_LIMIT_LENGTH = 8,
            POWER_SLOPE_START = 40,
            POWER_SLOPE_LENGTH = 12,
            POWER_INTERCEPT_START = 52,
            POWER_INTERCEPT_LENGTH = 12,
        };

        //Positions and lengths of the encodings
        enum ATTR_DECODE_INFO
        {
            DIMM_SIZE_START = 0,
            DIMM_SIZE_LEN = 4,

            DRAM_GEN_START = 4,
            DRAM_GEN_LEN = 2,

            DIMM_TYPE_START = 6,
            DIMM_TYPE_LEN = 3,

            DRAM_WIDTH_START = 9,
            DRAM_WIDTH_LEN = 3,

            DRAM_DENSITY_START = 12,
            DRAM_DENSITY_LEN = 3,

            DRAM_STACK_TYPE_START = 15,
            DRAM_STACK_TYPE_LEN = 2,

            DRAM_MFGID_START = 17,
            DRAM_MFGID_LEN = 3,

            DIMM_MODULE_HEIGHT_START = 20,
            DIMM_MODULE_HEIGHT_LEN = 2,

            // Invalid for Explorer but compile will fail without them
            DIMMS_PER_PORT_START = 0,
            DIMMS_PER_PORT_LEN = 1,
        };

        // Definition is in chip folder
        static const std::vector< std::pair<uint8_t , uint8_t> > DIMM_TYPE_MAP;

};
}//power_thermal
}// mss


#endif
