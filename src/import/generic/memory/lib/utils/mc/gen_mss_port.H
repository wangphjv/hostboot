/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/import/generic/memory/lib/utils/mc/gen_mss_port.H $       */
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
/// @file gen_mss_port.H
/// @brief Code to support ports
///
// *HWP HWP Owner: Stephen Glancy <sglancy@us.ibm.com>
// *HWP HWP Backup: Andre Marin <aamarin@us.ibm.com>
// *HWP Team: Memory
// *HWP Level: 3
// *HWP Consumed by: HB:FSP


#ifndef _GEN_MSS_PORT_H_
#define _GEN_MSS_PORT_H_

#include <fapi2.H>
#include <generic/memory/lib/mss_generic_attribute_getters.H>
#include <generic/memory/lib/utils/shared/mss_generic_consts.H>
#include <generic/memory/lib/utils/mc/gen_mss_port_traits.H>
#include <generic/memory/lib/utils/scom.H>
#include <generic/memory/lib/utils/c_str.H>

namespace mss
{

///
/// @brief ATTR_MSS_MVPD_FWMS getter declare
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @param[in] const ref to the fapi2::Target<fapi2::TargetType>
/// @param[out] uint32_t* memory to store the value
/// @return fapi2::ReturnCode - FAPI2_RC_SUCCESS iff get is OK
/// @note  Mark store records from MPVD Lx
/// keyword
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T>
inline fapi2::ReturnCode mvpd_fwms(const fapi2::Target< T>& i_target, uint32_t (&o_array)[MARK_STORE_COUNT]);

///
/// @brief Enable power management
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode enable_power_management( const fapi2::Target<T>& i_target )
{
    //Enable Power management based off of mrw_power_control_requested
    FAPI_INF("%s Enable Power min max domains", mss::c_str(i_target));

    bool is_pwr_cntrl = true;
    fapi2::buffer<uint64_t> l_data;
    uint8_t  l_pwr_cntrl = 0;

    // Get the value from attribute and write it to scom register
    FAPI_TRY(fapi2::getScom(i_target, TT::MBARPC0Q_REG, l_data));
    FAPI_TRY(FAPI_ATTR_GET(fapi2::ATTR_MSS_MRW_POWER_CONTROL_REQUESTED, fapi2::Target<fapi2::TARGET_TYPE_SYSTEM>(),
                           l_pwr_cntrl));

    is_pwr_cntrl = ((l_pwr_cntrl == fapi2::ENUM_ATTR_MSS_MRW_POWER_CONTROL_REQUESTED_POWER_DOWN)
                    || (l_pwr_cntrl == fapi2::ENUM_ATTR_MSS_MRW_IDLE_POWER_CONTROL_REQUESTED_PD_AND_STR)
                    || (l_pwr_cntrl == fapi2::ENUM_ATTR_MSS_MRW_IDLE_POWER_CONTROL_REQUESTED_PD_AND_STR_CLK_STOP));

    l_data.writeBit< TT::CFG_MIN_MAX_DOMAINS_ENABLE>(is_pwr_cntrl);
    FAPI_TRY( fapi2::putScom(i_target, TT::MBARPC0Q_REG, l_data) );


fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief Set the IML init complete bit
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_state the state
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode change_iml_complete( const fapi2::Target<T>& i_target, states i_state )
{
    fapi2::buffer<uint64_t> l_data;

    FAPI_DBG("Change the IML init complete bit to high for %s %s", (i_state == HIGH ? "high" : "low"),
             mss::c_str(i_target));
    FAPI_TRY( mss::getScom(i_target, TT::FARB6Q_REG, l_data) );
    l_data.writeBit<TT::CFG_INIT_COMPLETE>(i_state);
    FAPI_TRY( mss::putScom(i_target, TT::FARB6Q_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Read the read ECC Control register
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[out] o_buffer the buffer to write the register data into
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode read_recr_register( const fapi2::Target<T>& i_target, fapi2::buffer<uint64_t>& o_buffer )
{
    FAPI_TRY( mss::getScom(i_target, TT::ECC_REG, o_buffer) );

    FAPI_INF( "Read ECC Control register is 0x%016lx for %s", uint64_t(o_buffer), mss::c_str(i_target) );

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Write to RECR register
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_buffer the buffer that holds the register data to write
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode write_recr_register( const fapi2::Target<T>& i_target, const fapi2::buffer<uint64_t>& i_buffer )
{
    FAPI_INF( "Change Read ECC Control register to 0x%016lx for %s",  i_buffer, mss::c_str(i_target) );

    FAPI_TRY( mss::putScom(i_target, TT::ECC_REG, i_buffer) );

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Get the tce correction enable value from RECR
/// @tparam MC the memory controller type
/// @tparam TT the class traits for the port
/// @param[in] i_data the data buffer containing the RECR register
/// @param[out] o_value TCE_CORRECTION_ENABLE value (on or off)
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, typename TT = portTraits<MC> >
void get_tce_correction( const fapi2::buffer<uint64_t>& i_data, mss::states& o_value )
{
    o_value = i_data.template getBit<TT::RECR_TCE_CORRECTION>() ? mss::states::ON : mss::states::OFF;

    FAPI_INF( "TCE_CORRECTION_ENABLE: %lu", o_value );
}

///
/// @brief Sets tce correction enable in buffer
/// @tparam MC the memory controller type
/// @tparam TT the class traits for the port
/// @param[in,out] io_data the target data buffer
/// @param[in] i_value TCE_CORRECTION_ENABLE value (on or off) to set
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, typename TT = portTraits<MC> >
void set_tce_correction( fapi2::buffer<uint64_t>& io_data, const mss::states i_value )
{
    FAPI_INF( "Set TCE_CORRECTION_ENABLE to %lu", i_value);

    io_data.template writeBit<TT::RECR_TCE_CORRECTION>(i_value);
}

///
/// @brief Setup TCE correction
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode setup_tce_correction (const fapi2::Target<T>& i_target)
{
    constexpr uint64_t MNFG_REPAIRS_DISABLED_ATTR = 56;
    fapi2::buffer<uint64_t> l_data;
    fapi2::buffer<uint64_t> l_mnfg_buffer;
    mss::states l_state = mss::OFF;

    FAPI_TRY( mss::read_recr_register(i_target, l_data ), "%s: Failed read_recr_register", mss::c_str(i_target));

    // Check for manufacturing disable dram repair flag to disable TCE correction
    FAPI_TRY( FAPI_ATTR_GET(fapi2::ATTR_MNFG_FLAGS, fapi2::Target<fapi2::TARGET_TYPE_SYSTEM>(), l_mnfg_buffer),
              "%s: Failed mnfg_flags check", mss::c_str(i_target) );
    l_state = ( l_mnfg_buffer.getBit<MNFG_REPAIRS_DISABLED_ATTR>() ) ? mss::OFF : mss::ON;
    mss::set_tce_correction(l_data, l_state);

    FAPI_TRY( mss::write_recr_register(i_target, l_data), "%s: Failed write_recr_register", mss::c_str(i_target));

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Change the state of the port_fail_disable bit
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_state the state
/// @return FAPI2_RC_SUCCESS if and only if ok
/// @note Disable Port Fail after recurring RCD errors.
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode change_port_fail_disable( const fapi2::Target<T>& i_target, states i_state )
{
    fapi2::buffer<uint64_t> l_data;

    FAPI_DBG("Change port fail disable to %s %s", (i_state == HIGH ? "high" : "low"), mss::c_str(i_target));
    FAPI_TRY( mss::getScom(i_target, TT::FARB0Q_REG, l_data) );
    l_data.writeBit<TT::PORT_FAIL_DISABLE>(i_state);
    FAPI_TRY( mss::putScom(i_target, TT::FARB0Q_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief Change the state of the dfi init start bit
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_state the state
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode change_dfi_init_start( const fapi2::Target<T>& i_target, states i_state )
{
    fapi2::buffer<uint64_t> l_data;

    FAPI_DBG("Change rcd recovery disable to %s %s", (i_state == HIGH ? "high" : "low"), mss::c_str(i_target));
    FAPI_TRY( mss::getScom(i_target, TT::FARB0Q_REG, l_data) );
    l_data.writeBit<TT::DFI_INIT_START>(i_state);
    FAPI_TRY( mss::putScom(i_target, TT::FARB0Q_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief Change the state of the addr_mux_sel bit
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_state the state
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode change_addr_mux_sel( const fapi2::Target<T>& i_target, states i_state )
{
    fapi2::buffer<uint64_t> l_data;

    FAPI_DBG("Change addr_mux_sel to %s %s", (i_state == HIGH ? "high" : "low"), mss::c_str(i_target));
    FAPI_TRY( mss::getScom(i_target, TT::FARB5Q_REG, l_data) );
    l_data.writeBit<TT::CFG_CCS_ADDR_MUX_SEL>(i_state);
    FAPI_TRY( mss::putScom(i_target, TT::FARB5Q_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief Change the state of the force_str bit
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_state the state
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode change_force_str( const fapi2::Target<T>& i_target, const states i_state );


///
/// @brief Change the state of the MC Refresh enable bit
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @param[in] i_state the state
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode change_refresh_enable( const fapi2::Target<T>& i_target, states i_state )
{
    fapi2::buffer<uint64_t> l_data;

    FAPI_DBG("Change refresh enable to %s %s", (i_state == HIGH ? "high" : "low"), mss::c_str(i_target));
    FAPI_TRY( mss::getScom(i_target, TT::REFRESH_REG, l_data) );
    l_data.writeBit<TT::REFRESH_ENABLE>(i_state);
    FAPI_TRY( mss::putScom(i_target, TT::REFRESH_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}


///
/// @brief Enable periodic zq cal
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode enable_zq_cal( const fapi2::Target<T>& i_target )
{
    fapi2::buffer<uint64_t> l_data;

    FAPI_DBG("Enable periodic zq cal for %s", mss::c_str(i_target));
    FAPI_TRY( mss::getScom(i_target, TT::FARB9Q_REG, l_data) );
    l_data.writeBit<TT::CFG_ZQ_PER_CAL_ENABLE>(mss::HIGH);
    FAPI_TRY( mss::putScom(i_target, TT::FARB9Q_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Enable Read ECC checking
/// @tparam MC the memory controller type
/// @tparam T the fapi2 target type of the target
/// @tparam TT the class traits for the port
/// @param[in] i_target the target
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode enable_read_ecc( const fapi2::Target<T>& i_target )
{
    fapi2::buffer<uint64_t> l_data;

    uint8_t l_sim = 0;
    FAPI_TRY( FAPI_ATTR_GET(fapi2::ATTR_IS_SIMULATION, fapi2::Target<fapi2::TARGET_TYPE_SYSTEM>(), l_sim) );

    FAPI_DBG("Enable Read ECC %s", mss::c_str(i_target));

    FAPI_TRY( mss::getScom(i_target, TT::ECC_REG, l_data) );
    l_data.clearBit<TT::ECC_CHECK_DISABLE>();
    l_data.clearBit<TT::ECC_CORRECT_DISABLE>();

    // VBU tests assume good ECC and we don't have good ECC (since we're not writing everything)
    // so we can't run with address checking. Disable address checking in sim.
    l_data.writeBit<TT::ECC_USE_ADDR_HASH>(l_sim ? 0 : 1);

    // The preferred operating mode is 11 (INVERT_DATA_TOGGLE_CHECKS)   which stores data complemented
    // (because most bits are '0', and the dram bus pulls up, so transmitting 1s is least power)  but
    // still flips the inversion of check bits to aid RAS. Per Brad Michael 12/15
    // Leave un-inverted for sim. This allows the DIMM loader to write 0's and effect good ECC
    l_data.insertFromRight<TT::RECR_MBSECCQ_DATA_INVERSION, TT::RECR_MBSECCQ_DATA_INVERSION_LEN>(l_sim ? 0b00 : 0b11);

    // bits: 60 MBSTRQ_CFG_MAINT_RCE_WITH_CE
    // cfg_maint_rce_with_ce - not implemented. Need to investigate if needed for nimbus.

    FAPI_TRY( mss::putScom(i_target, TT::ECC_REG, l_data) );

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Apply mark store bits from module VPD
/// @tparam MC the memory controller type
/// @tparam T, the fapi2 target type of the target
/// @tparam TT, the class traits for the port
/// @param[in] i_target A target representing a port
/// @return FAPI2_RC_SUCCESS if and only if ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
fapi2::ReturnCode apply_mark_store( const fapi2::Target<T>& i_target )
{
    FAPI_INF("Enable marks from MVPD %s", mss::c_str(i_target));

    uint32_t l_fwms[MARK_STORE_COUNT];

    FAPI_TRY( mss::mvpd_fwms<MC>(i_target, l_fwms) );

    for (size_t l_mark = 0; l_mark < MARK_STORE_COUNT; ++l_mark)
    {
        if (l_fwms[l_mark] != 0)
        {
            fapi2::buffer<uint64_t> l_fwms_data;
            // This assumes the attribute contents are in the same format as the register fields,
            // ending just before the EXIT_1 bit
            l_fwms_data.insertFromRight < TT::FWMS0_MARK, TT::FWMS0_EXIT_1 - TT::FWMS0_MARK + 1 > (l_fwms[l_mark]);
            FAPI_TRY( mss::putScom(i_target, TT::FWMS_REG + l_mark, l_fwms_data) );
        }
    }

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Configures the write reorder queue bit
/// @tparam MC the memory controller type
/// @tparam T, the mc
/// @tparam TT, the class traits for the port
/// @param[in] i_target the target to effect
/// @param[in] i_state to set the bit too
/// @return FAPI2_RC_SUCCSS iff ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
inline fapi2::ReturnCode configure_wrq(const fapi2::Target<T>& i_target,
                                       const mss::states i_state)
{
    // Loops through all port targets, hitting all the registers
    for( const auto& l_port : mss::find_targets<TT::PORT_TYPE>(i_target) )
    {
        fapi2::buffer<uint64_t> l_data;

        // Gets the reg
        FAPI_TRY(mss::getScom(l_port, TT::WRQ_REG, l_data), "%s failed to getScom from WRQ0Q", mss::c_str(l_port));

        // Sets the bit
        l_data.writeBit<TT::WRQ_FIFO_MODE>(i_state == mss::states::ON);

        // Sets the regs
        FAPI_TRY(mss::putScom(l_port, TT::WRQ_REG, l_data), "%s failed to putScom to WRQ0Q", mss::c_str(l_port));
    }

    // In case we don't have any port's
    return fapi2::FAPI2_RC_SUCCESS;

fapi_try_exit:
    return fapi2::current_err;
}

///
/// @brief Configures the read reorder queue bit
/// @tparam MC the memory controller type
/// @tparam T, the mc
/// @tparam TT, the class traits for the port
/// @param[in] i_target the target to effect
/// @param[in] i_state to set the bit too
/// @return FAPI2_RC_SUCCSS iff ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
inline fapi2::ReturnCode configure_rrq(const fapi2::Target<T>& i_target, const mss::states i_state)
{
    // Loops through all port targets, hitting all the registers
    for( const auto& l_port : mss::find_targets<TT::PORT_TYPE>(i_target) )
    {
        fapi2::buffer<uint64_t> l_data;

        // Gets the reg
        FAPI_TRY(mss::getScom(l_port, TT::RRQ_REG, l_data), "%s failed to getScom from RRQ0Q", mss::c_str(l_port));

        // Sets the bit
        l_data.writeBit<TT::RRQ_FIFO_MODE>(i_state == mss::states::ON);

        // Sets the regs
        FAPI_TRY(mss::putScom(l_port, TT::RRQ_REG, l_data), "%s failed to putScom to RRQ0Q", mss::c_str(l_port));
    }

    // In case we don't have any port's
    return fapi2::FAPI2_RC_SUCCESS;

fapi_try_exit:
    return fapi2::current_err;
}


/// @brief Get the attributes for the reorder queue setting
/// @tparam MC the memory controller type
/// @tparam T, the mc
/// @param[in] const ref to the mc target
/// @param[out] uint8_t& reference to store the value
/// @return fapi2::ReturnCode - FAPI2_RC_SUCCESS iff get is OK
/// @note  Contains the settings for write/read reorder queue
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T >
inline fapi2::ReturnCode reorder_queue_setting(const fapi2::Target<T>& i_target, uint8_t& o_value);

///
/// @brief Resets the write/read reorder queue values - needs to be called after MCBIST execution
/// @tparam MC the memory controller type
/// @tparam T, the mc
/// @tparam TT, the class traits for the port
/// @param[in] i_target the target to effect
/// @return FAPI2_RC_SUCCSS iff ok
///
template< mss::mc_type MC = DEFAULT_MC_TYPE, fapi2::TargetType T, typename TT = portTraits<MC> >
inline fapi2::ReturnCode reset_reorder_queue_settings(const fapi2::Target<T>& i_target)
{
    uint8_t l_reorder_queue = 0;
    FAPI_TRY(reorder_queue_setting<MC>(i_target, l_reorder_queue));

    // Changes the reorder queue settings
    {
        // Two settings are FIFO and REORDER.  FIFO is a 1 in the registers, while reorder is a 0 state
        const mss::states l_state = ((l_reorder_queue == fapi2::ENUM_ATTR_MSS_REORDER_QUEUE_SETTING_FIFO) ?
                                     mss::states::ON : mss::states::OFF);
        FAPI_TRY(configure_rrq(i_target, l_state), "%s failed to reset read reorder queue settings", mss::c_str(i_target));
        FAPI_TRY(configure_wrq(i_target, l_state), "%s failed to reset read reorder queue settings", mss::c_str(i_target));
    }


fapi_try_exit:
    return fapi2::current_err;
}


}// ns mss

#endif
