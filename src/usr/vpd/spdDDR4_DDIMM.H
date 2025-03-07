/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/usr/vpd/spdDDR4_DDIMM.H $                                 */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2013,2019                        */
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
#ifndef __SPDDDR4_DDIMM_H
#define __SPDDDR4_DDIMM_H

/**
 * @file spdDDR4_DDIMM.H
 *
 * @brief Provides the DDR4 field information for DDIMM
 *
 */

// ----------------------------------------------
// Includes
// ----------------------------------------------
#include "spd.H"

namespace SPD
{

/**
 * @brief Pre-defined lookup table for DDR4 keywords and the
 *      information needed to read that data from the SPD data.
 */
const KeywordData ddr4DDIMMData[] =
{
    // ----------------------------------------------------------------------------------
    // NOTE: This list must remain an ordered list! The Keyword must be in numerical
    //       order (values defined in spdenums.H) to allow efficient searching, a unit
    //       test enforces this.
    // ----------------------------------------------------------------------------------
    // Bit order for each byte is [7:0] as defined by the JEDEC spec (little endian)
    //
    // For multi-byte fields, the offset specifies the byte that is placed at offset 0 in
    // the output buffer.
    // - If SpecialCase=false then the next byte in SPD is placed at the next offset in
    //   the output buffer until complete. Any bitmask/shift only affects the byte at
    //   offset 0
    // - If SpecialCase=true then spd.C handles the field in a custom way (e.g. working
    //   backwards through SPD bytes).
    // Typically for a 2-byte field consisting of (LSB,MSB), the offset points to MSB and
    // it is a SpecialCase where spd.C first copies the MSB to the output buffer then
    // copies the previous byte (LSB) to the output buffer (big endian).
    // ------------------------------------------------------------------------------------------
    // Keyword                          offset  size    Bitmsk  Shift  Spec  Writ-  Mod
    //                                                          Number Case  able   Spec
    // ------------------------------------------------------------------------------------------
    //
    // Normal fields supported on both DDR3 and DDR4
    { SPD_BYTES_TOTAL,                  0x00,   0x01,   0x70,   0x04, false, false, ALL },
    { SPD_BYTES_USED,                   0x00,   0x01,   0x0F,   0x00, false, false, ALL },
    { SPD_MAJOR_REVISION,               0x01,   0x01,   0xF0,   0x04, false, false, ALL },
    { SPD_MINOR_REVISION,               0x01,   0x01,   0x0F,   0x00, false, false, ALL },
    { BASIC_MEMORY_TYPE,                0x02,   0x01,   0x00,   0x00, false, false, ALL },
    { CUSTOM,                           0x03,   0x01,   0x80,   0x07, false, false, ALL },
    { MODULE_TYPE,                      0x03,   0x01,   0x0F,   0x00, false, false, ALL },
    { DENSITY,                          0x04,   0x01,   0x0F,   0x00, false, false, ALL },
    { ROW_ADDRESS,                      0x05,   0x01,   0x38,   0x03, false, false, ALL },
    { COL_ADDRESS,                      0x05,   0x01,   0x07,   0x00, false, false, ALL },
    { MODULE_RANKS,                     0x0c,   0x01,   0x38,   0x03, false, false, ALL },
    { MODULE_DRAM_WIDTH,                0x0c,   0x01,   0x07,   0x00, false, false, ALL },
    { MODULE_MEMORY_BUS_WIDTH,          0x0d,   0x01,   0x1f,   0x00, false, false, ALL },
    { MODULE_MEMORY_BUS_WIDTH_EXT,      0x0d,   0x01,   0x18,   0x03, false, false, ALL },
    { MODULE_MEMORY_BUS_WIDTH_PRI,      0x0d,   0x01,   0x07,   0x00, false, false, ALL },
    { TCK_MIN,                          0x12,   0x01,   0x00,   0x00, false, false, ALL },
    { MIN_CAS_LATENCY,                  0x18,   0x01,   0x00,   0x00, false, false, ALL },
    { TRCD_MIN,                         0x19,   0x01,   0x00,   0x00, false, false, ALL },
    { TRP_MIN,                          0x1a,   0x01,   0x00,   0x00, false, false, ALL },
    { TRC_MIN,                          0x1b,   0x02,   0xF0,   0x04, true,  false, ALL },
    { TRAS_MIN,                         0x1b,   0x02,   0x0F,   0x00, false, false, ALL },
    { TFAW_MIN,                         0x24,   0x02,   0x0F,   0x00, false, false, ALL },
    { SDRAM_OPTIONAL_FEATURES,          0x07,   0x01,   0x00,   0x00, false, false, ALL },
    { SDRAM_THERMAL_REFRESH_OPTIONS,    0x08,   0x01,   0x00,   0x00, false, false, ALL },
    { MODULE_THERMAL_SENSOR,            0x0e,   0x01,   0x00,   0x00, false, false, ALL },
    { THERMAL_SENSOR_PRESENT,           0x0e,   0x01,   0x80,   0x07, false, false, ALL },
    { SDRAM_DEVICE_TYPE       ,         0x06,   0x01,   0x80,   0x07, false, false, ALL },
    { SDRAM_DIE_COUNT,                  0x06,   0x01,   0x70,   0x04, false, false, ALL },
    { SDRAM_DEVICE_TYPE_SIGNAL_LOADING, 0x06,   0x01,   0x03,   0x00, false, false, ALL },
    { TCKMIN_FINE_OFFSET,               0x7d,   0x01,   0x00,   0x00, false, false, ALL },
    { TAAMIN_FINE_OFFSET,               0x7b,   0x01,   0x00,   0x00, false, false, ALL },
    { TRCDMIN_FINE_OFFSET,              0x7a,   0x01,   0x00,   0x00, false, false, ALL },
    { TRPMIN_FINE_OFFSET,               0x79,   0x01,   0x00,   0x00, false, false, ALL },
    { TRCMIN_FINE_OFFSET,               0x78,   0x01,   0x00,   0x00, false, false, ALL },
    // Note - All data below 128 is common across all DDR4 DIMMs, except DDIMM
    { MODULE_SERIAL_NUMBER,             0x205,  0x04,   0x00,   0x00, false, false, ALL },
    { MODULE_PART_NUMBER,               0x209,  0x30,   0x00,   0x00, false, false, ALL },
    // Normal fields supported on DDR4 only
    { BANK_GROUP_BITS,                  0x04,   0x01,   0xC0,   0x06, false, false, ALL },
    { BANK_ADDRESS_BITS_DDR4,           0x04,   0x01,   0x30,   0x04, false, false, ALL },
    { MODULE_NOMINAL_VOLTAGE_DDR4,      0x0b,   0x01,   0x3F,   0x00, false, false, ALL },
    { TIMEBASES_MTB,                    0x11,   0x01,   0x0C,   0x02, false, false, ALL },
    { TIMEBASES_FTB,                    0x11,   0x01,   0x03,   0x00, false, false, ALL },
    { TCK_MAX,                          0x13,   0x01,   0x00,   0x00, false, false, ALL },
    { CAS_LATENCIES_SUPPORTED_DDR4,     0x17,   0x04,   0x00,   0x00, true,  false, ALL },
    { TRFC1_MIN,                        0x1f,   0x02,   0x00,   0x00, true,  false, ALL },
    { TRFC2_MIN,                        0x21,   0x02,   0x00,   0x00, true,  false, ALL },
    { TRFC4_MIN,                        0x23,   0x02,   0x00,   0x00, true,  false, ALL },
    { TRRDS_MIN,                        0x26,   0x01,   0x00,   0x00, false, false, ALL },
    { TRRDL_MIN,                        0x27,   0x01,   0x00,   0x00, false, false, ALL },
    { TCCDL_MIN,                        0x28,   0x01,   0x00,   0x00, false, false, ALL },
    { CONNECTOR_SDRAM_MAP,              0x3C,   0x12,   0x00,   0x00, false, false, ALL },
    { TCCDL_FINE_OFFSET,                0x75,   0x01,   0x00,   0x00, false, false, ALL },
    { TRRDL_FINE_OFFSET,                0x76,   0x01,   0x00,   0x00, false, false, ALL },
    { TRRDS_FINE_OFFSET,                0x77,   0x01,   0x00,   0x00, false, false, ALL },
    { TCKMAX_FINE_OFFSET,               0x7c,   0x01,   0x00,   0x00, false, false, ALL },
    { BASE_CONFIG_CRC,                  0x7f,   0x02,   0x00,   0x00, true,  false, ALL },
    // Module Specific fields supported on DDR4 only
    { ENTIRE_SPD,                       0x00,   0x200,   0x00,   0x00, false, false, ALL },
    //---------------------------------------------------------------------------------------
};


}; // end SPD namespace

#endif  // __SPDDDR4_DDR4_H
