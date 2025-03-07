/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/generic/memory/lib/utils/shared/mss_generic_consts.H $ */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2018,2019                        */
/* [+] Evan Lojewski                                                      */
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
/// @file mss_generic_consts.H
/// @brief Common constants to be shared
///

// *HWP HWP Owner: Andre Marin <aamarin@us.ibm.com>
// *HWP HWP Backup: Louis Stermole <stermole@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 3
// *HWP Consumed by: HB:FSP

#ifndef _MSS_GENERIC_CONSTS_H_
#define _MSS_GENERIC_CONSTS_H_

#include <cstdint>

namespace mss
{

///
/// @brief Common constants
///
enum common_consts
{
    DEFAULT_POLL_LIMIT = 50,  ///< the number of poll attempts in the event we can't calculate another
    MEMCMP_EQUAL = 0,         ///< Equal comparison value for memcmp
    BAD_BITS_RANKS = 4,       ///< Bad bit attribute's number of ranks
    BAD_DQ_BYTE_COUNT = 10,      ///< Bad bit attribute's number of byte
    ATTR_RANK0 = 0, ///< Attribute index for rank0
    ATTR_RANK1 = 1, ///< Attribute index for rank1
    ATTR_RANK2 = 2, ///< Attribute index for rank2
    ATTR_RANK3 = 3, ///< Attribute index for rank3
};

///
/// @brief Common mcbist constants
///
enum mcbist_common_consts
{
    CYCLES_PER_CMD  = 4,      ///< Best case cycles per MCBIST command
    MAX_RANK_PER_DIMM = 4,

    BYTES_PER_GB = 1000000000,      ///< Multiplier to go from GB to B
    T_PER_MT     = 1000000,         ///< Multiplier to go from MT/s to T/s

    // Number of double words in...
    NUM_DW_IN_128B = 16,
    NUM_DW_IN_64B = 8,

    BG_SCRUB_IN_HOURS       = 12,
    CMD_TIMEBASE            = 8192,     ///< Represents the timebase multiplier for the MCBIST inter cmd gap
    MAX_CMD_GAP             = 4095,     ///< Represents the maximum (non-multplied) time for MCBIST inter cmd gap


    // MCBIST polling constant for actual HW
    // The specific value here is not important, only that it is very large to avoid polling timeouts,
    // but not to avoid any actual hardware timeouts
    // Note: ~0 is not used as that would cause MCBIST to never timeout even if the hardware is in an infinite loop
    // You can't get greater than ~0, so you'd never timeout
    // TODO RTC:166340 - Clean up MCBIST polling
    OVERLY_LARGE_NUMBER_OF_POLLS = 5000000000000,
};

///
/// @brief Common timings
///
enum common_timings
{
    DELAY_1NS               = 1,
    DELAY_10NS              = 10 ,      ///< general purpose 10  ns delay for HW mode
    DELAY_100NS             = 100,      ///< general purpose 100 ns delay for HW mode
    DELAY_1US               = 1000,     ///< general purpose 1 usec delay for HW mode
    DELAY_10US              = 10000,    ///< general purpose 1 usec delay for HW mode
    DELAY_100US             = 100000,   ///< general purpose 100 usec delay for HW mode
    DELAY_1MS               = 1000000,  ///< general purpose 1 ms delay for HW mode
};

///
/// @brief Common conversions
///
enum conversions
{
    CONVERT_PS_IN_A_NS      = 1000,     ///< 1000 pico in an nano
    CONVERT_PS_IN_A_US      = 1000000,  ///< 1000000 picos in a micro
    MHZ_TO_KHZ              = 1000,
    SEC_IN_HOUR             = 60 * 60,  ///< seconds in an hour, used for scrub times
    NIBBLES_PER_BYTE = 2,
    BITS_PER_NIBBLE = 4,
    BITS_PER_BYTE = 8,

    // Used by exp_decoder.C for dA to cA
    DECI_TO_CENTI = 10,
};

enum generic_sizes
{
    NUM_MAX_FREQS = 5,             ///< Used for ATTR_MAX_ALLOWED_DIMM_FREQ
    MARK_STORE_COUNT = 8,          ///< Elements in a VPD mark/store array
};

///
/// @brief FFDC generic codes
///
enum generic_ffdc_codes
{
    // Starting at 0x1%%% to avoid
    // any collisions with values
    // from controller specific ffdc codes
    SET_ATTR_DIMM_TYPE = 0x1000,
    SET_ATTR_DRAM_GEN = 0x1001,
    SET_ATTR_HYBRID = 0x1002,
    SET_ATTR_HYBRID_MEDIA = 0x1003,
    SET_ATTR_MASTER_RANKS = 0x1004,
    SET_ATTR_RANKS_CONFIGED  = 0x1005,
    GET_FIELD = 0x1006,
    READ_SPD_FIELD = 0x1007,
    BASE_CFG_PARAM_SELECT = 0x1008,
    DIMM_MODULE_PARAM_SELECT = 0x1009,
    BASE_CFG_FACTORY = 0x100A,
    DIMM_MODULE_FACTORY = 0x100B,
    GET_TAAMIN = 0x100C,
    GET_TCKMIN = 0x100D,
    GET_TCKMAX = 0x100E,
    GET_TIMEBASES_FTB = 0x100F,
    GET_TIMEBASES_MTB = 0x1010,
    GET_SUPPORTED_REV = 0x1011,
    TRASMIN = 0x1012,
    TRCMIN = 0x1013,
    TRFC1MIN = 0x1014,
    TRFC2MIN = 0x1015,
    TRFC4MIN = 0x1016,
    TFAWMIN = 0x1017,
    TWTR_S_MIN = 0x1018,
    TWRMIN = 0x1019,
    TWTR_L_MIN = 0x101A,
    DEVICE_TYPE = 0x101B,
    BASE_MODULE_TYPE = 0x101C,
    BAD_SPD_DATA = 0x101D,
    SET_FIELD = 0x101E,
    SELECT_SUPPORTED_FREQ = 0x101F,
    FREQ_SCOREBOARD_REMOVE_FREQS_ABOVE_LIMIT = 0x1020,
    FREQ_SCOREBOARD_REMOVE_FREQS_ABOVE_LIMIT_VECTOR = 0x1021,
    FREQ_SCOREBOARD_REMOVE_FREQS_NOT_ON_LIST = 0x1022,
    FREQ_SCOREBOARD_MAX_SUPPORTED_FREQ = 0x1023,
    FREQ_SCOREBOARD_SUPPORTED_FREQS = 0x1024,
    LIMIT_FREQ_BY_VPD = 0x1025,
    SET_DIMM_TYPE = 0x1026,
    SET_DRAM_GEN = 0x1027,
    SET_HYBRID = 0x1028,
    SET_HYBRID_MEDIA = 0x1029,
    SET_MRANKS = 0x102A,
    SET_HOST_TO_DDR_SPEED_RATIO = 0x102B,
    SET_ATTR_HOST_TO_DDR_SPEED_RATIO = 0x102C,
    CCS_INST_CONFIGURE_RANK = 0x102D,
    SET_DIMM_RANKS_CNFG = 0x1039,
    DDIMM_RAWCARD_DECODE = 0x103a,
    INIT_RANK_INFO = 0x103B,
    BIAS_PMIC_FROM_SPD = 0x103C,
    SET_DRAM_WIDTH = 0x1040,

    SET_SI_VREF_DRAM_WR = 0x1041,
    SET_SI_MC_RCV_IMP_DQ_DQS = 0x1042,
    SET_SI_MC_DRV_IMP_DQ_DQS_PULL_UP = 0x1043,
    SET_SI_MC_DRV_IMP_DQ_DQS_PULL_DOWN = 0x1044,
    SET_SI_MC_DRV_SLEW_RATE_DQ_DQS = 0x1045,
    SET_SI_MC_DRV_IMP_CMD_ADDR = 0x10466,
    SET_SI_MC_DRV_SLEW_RATE_CMD_ADDR = 0x1047,
    SET_SI_MC_DRV_IMP_CLK = 0x1048,
    SET_SI_MC_DRV_SLEW_RATE_CLK = 0x1049,
    SET_SI_MC_RCV_IMP_ALERT_N = 0x1050,
    SET_SI_DRAM_RTT_NOM = 0x1051,
    SET_SI_DRAM_RTT_WR = 0x1052,
    SET_SI_DRAM_RTT_PARK = 0x1053,
    SET_SI_DRAM_PREAMBLE = 0x1054,
    SET_SI_MC_DRV_EQ_DQ_DQS = 0x1055,
    SET_SI_DRAM_DRV_IMP_DQ_DQS = 0x1056,
    SET_SI_VREF_DQ_TRAIN_RANGE = 0x1057,
    SET_SI_VREF_DQ_TRAIN_VALUE = 0x1058,
    SET_SI_ODT_WR = 0x1059,
    SET_SI_ODT_RD = 0x1060,
    SET_SI_GEARDOWN_MODE = 0x1061,
    PRE_DATA_ENGINE_CTOR = 0x1062,
    SET_DRAM_GEN_METADATA = 0x1063,
    SET_DIMM_TYPE_METADATA = 0x1064,
    SET_DIMM_POS_METADATA = 0x1065,
    SET_LOGICAL_RANKS = 0x1066,
    SET_PRIM_STACK_TYPE = 0x1067,
    SET_DIMM_SIZE = 0x1068,
    SET_PRIM_BUS_WIDTH = 0x1069,
    SET_PRIM_DIE_COUNT = 0x1070,
    SET_DRAM_DENSITY = 0x1071,
    SET_SI_RD_VREF_DQ = 0x1075,
    SET_CAC_DELAY_A = 0x1076,
    SET_CAC_DELAY_B = 0x1077,
    EFD_CA_LATENCY_MODE = 0x1080,
    EFD_CA_PL_MODE = 0x1081,


    // Power thermal functions
    POWER_LIMIT = 0x1072,
    SLOPE = 0x1073,
    INTERCEPT = 0x1074,
};

///
/// @brief Supported proc types
/// @note Processor types by system generation and sub numbering
///
enum class proc_type
{
    NIMBUS  = 0x0900,
    CUMULUS = 0x0901,
    AXONE   = 0x0902,
};

///
/// @brief Supported memory controller types
///
enum class mc_type
{
    NIMBUS   = 0,
    CENTAUR  = 1,
    EXPLORER = 2,
};

///
/// @brief JEDEC supported DDR speeds
/// @note Includes DDR4 and DDR5 only
///
enum ddr_dimm_speeds
{
    // Supported frequencies
    DIMM_SPEED_1600 = 1600,
    DIMM_SPEED_1866 = 1866,
    DIMM_SPEED_2133 = 2133,
    DIMM_SPEED_2400 = 2400,
    DIMM_SPEED_2666 = 2666,
    DIMM_SPEED_2933 = 2933,
    DIMM_SPEED_3200 = 3200,
    DIMM_SPEED_3600 = 3600,
    DIMM_SPEED_4000 = 4000,
    DIMM_SPEED_4400 = 4400,
    DIMM_SPEED_4800 = 4800,

    // Max/Mins for specific generations here
    DDR4_MIN_SPEED = 1600,
    DDR4_MAX_SPEED = 3200,
    DDR5_MIN_SPEED = 3200,
    DDR5_MAX_SPEED = 4800,
};

enum states
{
    LOW = 0,
    HIGH = 1,
    START = 1,
    STOP = 0,
    START_N = 0,
    STOP_N = 1,
    ON = 1,
    OFF = 0,
    ON_N = 0,
    OFF_N = 1,
    YES = 1,
    NO = 0,
    YES_N = 0,
    NO_N = 1,
    // Uses "_" in the name for INVALID as INVALID is defined as a macro in the
    // FSP code. If we just use INVALID as an enum name, then the preprocessor
    // compile phase changes it to be the macro.
    _INVALID_ = 0xFF,
    NO_CHIP_SELECT_ACTIVE = 0xFF,
};


enum port_select
{
    // Port selects for MCBIST and CCS
    // Select for 1 port
    PORT0            = 0b1000,
    PORT1            = 0b0100,
    PORT2            = 0b0010,
    PORT3            = 0b0001,
    // Selects for 2 port combinations
    PORT01           = PORT0 | PORT1,
    PORT02           = PORT0 | PORT2,
    PORT03           = PORT0 | PORT3,
    PORT12           = PORT1 | PORT2,
    PORT13           = PORT1 | PORT3,
    PORT23           = PORT2 | PORT3,
    // Selects for 3 port combinations
    PORT012          = PORT0 | PORT1 | PORT2,
    PORT013          = PORT0 | PORT1 | PORT3,
    PORT023          = PORT0 | PORT2 | PORT3,
    PORT123          = PORT1 | PORT2 | PORT3,
    // Select all
    PORT0123         = PORT0 | PORT1 | PORT2 | PORT3,
    // Maybe a better name for disabling all
    PORT_NONE        = 0b0000,
};

enum dimm_select
{
    // Dimm selects for MCBIST and CCS
    // Select for 1 dimm
    DIMM0            = 0b10,
    DIMM1            = 0b01,
    // Selects for 2 dimm combinations
    DIMM01           = DIMM0 | DIMM1,
    // Maybe a better name for disabling all
    DIMM_NONE        = 0b00,
};

namespace mcbist
{

enum broadcast_timebase
{
    // Number of 1024 2:1 cycle timebases to wait starting MCBIST
    // for SRQs to get synced for broadcast mode
    TB_COUNT_2     = 0b0000001,
    TB_COUNT_4     = 0b0000011,
    TB_COUNT_8     = 0b0000111,
    TB_COUNT_16    = 0b0001111,
    TB_COUNT_32    = 0b0011111,
    TB_COUNT_64    = 0b0111111,
    TB_COUNT_128   = 0b1111111,
};

enum rmw_address
{
    // 32B block addresses into the maint portion of the rmw buffer
    DW0            = 0b111110000,
    DW1            = 0b111110001,
    DW2            = 0b111110010,
    DW3            = 0b111110011,
    DW4            = 0b111110100,
    DW5            = 0b111110101,
    DW6            = 0b111110110,
    DW7            = 0b111110111,
    DW8            = 0b111111000,
    DW9            = 0b111111001,
    DWA            = 0b111111010,
    DWB            = 0b111111011,
    DWC            = 0b111111100,
    DWD            = 0b111111101,
    DWE            = 0b111111110,
    DWF            = 0b111111111,
};

enum data_rotate_mode
{
    // MCBIST data rotate modes refer to register MCBDRCR bits 0:3
    ROTATE_0_BITS  = 0b0000,
    ROTATE_1_BITS  = 0b0001,
    ROTATE_2_BITS  = 0b0010,
    ROTATE_3_BITS  = 0b0011,
    ROTATE_4_BITS  = 0b0100,
    ROTATE_5_BITS  = 0b0101,
    ROTATE_6_BITS  = 0b0110,
    ROTATE_7_BITS  = 0b0111,
    ROTATE_8_BITS  = 0b1000,
    ROTATE_9_BITS  = 0b1001,
    ROTATE_10_BITS = 0b1010,
    ROTATE_11_BITS = 0b1011,
    ROTATE_12_BITS = 0b1100,
    ROTATE_13_BITS = 0b1101,
    ROTATE_14_BITS = 0b1110,
    ROTATE_15_BITS = 0b1111,
};

enum data_seed_mode
{
    // MCBIST data seed modes refer to register MCBDRCR bits 21:22
    ALL_UNIQUE        = 0b00,
    REPEAT_SEED_0     = 0b01,
    REPEAT_SEED_1     = 0b10,
    REPEAT_SEED_2     = 0b11,
};

enum data_mode
{
    // MCBIST test data modes
    FIXED_DATA_MODE   = 0b000,
    RAND_FWD_MODE     = 0b001,
    RAND_REV_MODE     = 0b010,
    RAND_FWD_MAINT    = 0b011,
    RAND_REV_MAINT    = 0b100,
    DATA_EQ_ADDR      = 0b101,
    ROTATE_LEFT_MODE  = 0b110,
    ROTATE_RIGHT_MODE = 0b111,
};

// 0:3  Operation Type
enum op_type
{
    WRITE            = 0b0000, // fast, with no concurrent traffic
    READ             = 0b0001, // fast, with no concurrent traffic
    READ_WRITE       = 0b0010,
    WRITE_READ       = 0b0011,
    READ_WRITE_READ  = 0b0100,
    READ_WRITE_WRITE = 0b0101,
    RAND_SEQ         = 0b0110,
    READ_READ_WRITE  = 0b1000,
    SCRUB_RRWR       = 0b1001,
    STEER_RW         = 0b1010,
    ALTER            = 0b1011, // (W)
    DISPLAY          = 0b1100, // (R, slow)
    CCS_EXECUTE      = 0b1111,

    // if bits 9:11 (Data Mode bits)  = 000  (bits 4:8 used to specify which subtest to go to)
    // Refresh only cmd if bits 9:11 (Data Mode bits) /= 000
    GOTO_SUBTEST_N = 0b0111,
};


enum test_type
{
    USER_MODE = 0,
    CENSHMOO = 1,
    SUREFAIL = 2,
    MEMWRITE = 3,
    MEMREAD = 4,
    CBR_REFRESH = 5,
    MCBIST_SHORT = 6,
    SHORT_SEQ = 7,
    DELTA_I = 8,
    DELTA_I_LOOP = 9,
    SHORT_RAND = 10,
    LONG1 = 11,
    BUS_TAT = 12,
    SIMPLE_FIX = 13,
    SIMPLE_RAND = 14,
    SIMPLE_RAND_2W = 15,
    SIMPLE_RAND_FIXD = 16,
    SIMPLE_RA_RD_WR = 17,
    SIMPLE_RA_RD_R = 18,
    SIMPLE_RA_FD_R = 19,
    SIMPLE_RA_FD_R_INF = 20,
    SIMPLE_SA_FD_R = 21,
    SIMPLE_RA_FD_W = 22,
    INFINITE = 23,
    WR_ONLY = 24,
    W_ONLY = 25,
    R_ONLY = 26,
    W_ONLY_RAND = 27,
    R_ONLY_RAND = 28,
    R_ONLY_MULTI = 29,
    SHORT = 30,
    SIMPLE_RAND_BARI = 31,
    W_R_INFINITE = 32,
    W_R_RAND_INFINITE = 33,
    R_INFINITE1 = 34,
    R_INFINITE_RF = 35,
    MARCH = 36,
    SIMPLE_FIX_RF = 37,
    SHMOO_STRESS = 38,
    SIMPLE_RAND_RA = 39,
    SIMPLE_FIX_RA = 40,
    SIMPLE_FIX_RF_RA = 41,
    TEST_RR = 42,
    TEST_RF = 43,
    W_ONLY_INFINITE_RAND = 44,
    MCB_2D_CUP_SEQ = 45,
    MCB_2D_CUP_RAND = 46,
    SHMOO_STRESS_INFINITE = 47,
    HYNIX_1_COL = 48,
    RMWFIX = 49,
    RMWFIX_I = 50,
    W_INFINITE = 51,
    R_INFINITE = 52,
};


} // namespace mcbist

///
/// @brief Supported DIMM speed equality deliberations
///
enum class speed_equality : uint8_t
{
    NOT_EQUAL_DIMM_SPEEDS = 0, ///< denotes all DIMMs don't have the same speed
    EQUAL_DIMM_SPEEDS = 1, ///< denotes all DIMMs have the same speed
};

namespace spd
{

///
/// @brief SPD revisions - not tied any particular module
///
enum rev : uint8_t
{
    V0_0 = 0x00, ///< represents Rev 0.0
    V1_0 = 0x10, ///< represents Rev 1.0
    V1_1 = 0x11, ///< represents Rev 1.1
    V1_2 = 0x12, ///< represents Rev 1.2

    // These module revisions can vary independently
    // so we track the largest decoded revision here.
    GEN_SEC_MAX = V1_1,
    RDIMM_MAX = V1_1,
    LRDIMM_MAX = V1_2,
    DDIMM_MAX = V0_0,
};

///
/// @brief SPD module parameters
/// @note helps distinguish SPD decoder sections
///
enum parameters
{
    UNINITIALIZED,
    BASE_CNFG,
    RDIMM_MODULE,
    LRDIMM_MODULE,
    NVDIMM_MODULE,
    DDIMM_MODULE,
};

///
/// @brief DRAM generation selector
/// @note values set to SPD settings
///
enum device_type
{
    DDR4 = 0x0c,
};

///
/// @brief DIMM type selector
/// @note values set to SPD settings
///
enum dimm_type
{
    RDIMM = 0b0001,
    LRDIMM = 0b0100,
    DDIMM = 0b1010,
    SORDIMM = 0b1000,
    MINIRDIMM = 0b0101,
};

enum guard_band : uint16_t
{
    // Used for caclulating spd timing values - from JEDEC rounding algorithm
    // Correction factor is 1% (for DDR3) or 2.5% (for DDR4)
    // when doing integer math, we add-in the inverse correction factor
    // Formula used for derivation:
    // Guardband = 1000 * (1000* correction_factor) - 1
    INVERSE_DDR4_CORRECTION_FACTOR = 974, ///< DDR4 correction factor
};

}// spd

namespace efd
{


///
/// @brief EFD Module identifier
/// @note helps distinguish the EFD identifier
///
enum id
{
    DDR4_CUSTOM_MICROCHIP = 0x11,
};

}//efd

///
/// @brief DIMM nibble mask
/// @note nibble0: 4 high bits, nibble1: 4 low bits
///
enum nibble_mask
{
    MASK_NIBBLE0 = 0xf0,
    MASK_NIBBLE1 = 0x0f,
};

///
/// @brief throttle_type used to set bulk_pwr_throttls to run POWER or THERMAL throttling
/// @note OCC will be using the POWER option
///
enum class throttle_type
{
    POWER = 0,
    THERMAL = 1,
};



///
/// @brief Trait classes for mc_type
/// @tparam MC the mc_type
///
template< mc_type MC >
class mcTypeTraits;

///
/// @brief Trait classes for mc_type - NIMBUS specialization
///
template< >
struct mcTypeTraits<mc_type::NIMBUS>
{
    enum
    {
        MC_PER_MODULE = 2,
        MCS_PER_MC = 2,
        MCS_PER_PROC = MC_PER_MODULE * MCS_PER_MC,
        PORTS_PER_MCBIST = 4,
        PORTS_PER_MCS = 2,
        DIMMS_PER_PORT = 2,
        DIMMS_PER_MCS = PORTS_PER_MCS * DIMMS_PER_PORT,
        DIMMS_PER_MCBIST = PORTS_PER_MCBIST * DIMMS_PER_PORT,
    };
};

///
/// @brief Trait classes for mc_type - EXPLORER specialization
///
template< >
struct mcTypeTraits<mc_type::EXPLORER>
{
    enum
    {
        MC_PER_PROC = 2,
        MI_PER_MC = 2,
        MCC_PER_MI = 2,
        OMI_PER_MCC = 2,
        OCMB_PER_OMI = 1,
        PORTS_PER_OCMB = 1,
        DIMMS_PER_PORT = 2,
    };
};

}// mss

#endif
