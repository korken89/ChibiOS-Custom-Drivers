/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    epwm.h
 * @brief   EPWM Driver macros and structures.
 *
 * @addtogroup EPWM
 * @{
 */

#ifndef _EPWM_H_
#define _EPWM_H_

#if (HAL_USE_EPWM == TRUE) || defined(__DOXYGEN__)


/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    EPWM output mode macros
 * @{
 */
/**
 * @brief   Standard output modes mask.
 */
#define EPWM_OUTPUT_MASK                         0x0FU

/**
 * @brief   Output not driven, callback only.
 */
#define EPWM_OUTPUT_DISABLED                     0x00U

/**
 * @brief   Positive EPWM logic, active is logic level one.
 */
#define EPWM_OUTPUT_ACTIVE_HIGH                  0x01U

/**
 * @brief   Inverse EPWM logic, active is logic level zero.
 */
#define EPWM_OUTPUT_ACTIVE_LOW                   0x02U
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  EPWM_UNINIT = 0,                   /**< Not initialized.                   */
  EPWM_STOP = 1,                     /**< Stopped.                           */
  EPWM_READY = 2                     /**< Ready.                             */
} epwmstate_t;

/**
 * @brief   Type of a structure representing a EPWM driver.
 */
typedef struct EPWMDriver EPWMDriver; 

#include "epwm_lld.h"

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Changes the period the EPWM peripheral.
 * @details This function changes the period of a EPWM unit that has already
 *          been activated using @p epwmStart().
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 * @post    The EPWM unit period is changed to the new value.
 * @note    If a period is specified that is shorter than the pulse width
 *          programmed in one of the channels then the behavior is not
 *          guaranteed.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] value     new cycle time in ticks
 *
 * @iclass
 */
#define epwmChangePeriodI(epwmp, value) {                                     \
  (epwmp)->period = (value);                                                  \
  epwm_lld_change_period(epwmp, value);                                       \
}

/**
 * @brief   Enables a EPWM channel.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 * @post    The channel is active using the specified configuration.
 * @note    Depending on the hardware implementation this function has
 *          effect starting on the next cycle (recommended implementation)
 *          or immediately (fallback implementation).
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] channel   EPWM channel identifier (0...channels-1)
 * @param[in] width     EPWM pulse width as clock pulses number
 *
 * @iclass
 */
#define epwmEnableChannelI(epwmp, channel, width) do {                        \
  (epwmp)->enabled |= ((epwmchnmsk_t)1U << (epwmchnmsk_t)(channel));          \
  epwm_lld_enable_channel(epwmp, channel, width);                             \
} while (false)

/**
 * @brief   Disables a EPWM channel.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 * @post    The channel is disabled and its output line returned to the
 *          idle state.
 * @note    Depending on the hardware implementation this function has
 *          effect starting on the next cycle (recommended implementation)
 *          or immediately (fallback implementation).
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] channel   EPWM channel identifier (0...channels-1)
 *
 * @iclass
 */
#define epwmDisableChannelI(epwmp, channel) do {                              \
  (epwmp)->enabled &= ~((epwmchnmsk_t)1U << (epwmchnmsk_t)(channel));         \
  epwm_lld_disable_channel(epwmp, channel);                                   \
} while (false)

/**
 * @brief   Returns a EPWM channel status.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] channel   EPWM channel identifier (0...channels-1)
 *
 * @iclass
 */
#define epwmIsChannelEnabledI(epwmp, channel)                                 \
  (((epwmp)->enabled & ((epwmchnmsk_t)1U << (epwmchnmsk_t)(channel))) != 0U)

/**
 * @brief   Sends pulses when in one-pulse mode.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 *
 * @iclass
 */
#define epwmSendPulsesI(epwmp) do {                                           \
  epwm_lld_send_pulses(epwmp);                                                \
} while (false)

/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void epwmInit(void);
  void epwmObjectInit(EPWMDriver *epwmp);
  void epwmStart(EPWMDriver *epwmp, const EPWMConfig *config);
  void epwmStop(EPWMDriver *epwmp);
  void epwmChangePeriod(EPWMDriver *epwmp, epwmcnt_t period);
  void epwmEnableChannel(EPWMDriver *epwmp,
                        epwmchannel_t channel,
                        epwmcnt_t width);
  void epwmDisableChannel(EPWMDriver *epwmp, epwmchannel_t channel);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_EPWM == TRUE */

#endif /* _EPWM_H_ */

/** @} */
