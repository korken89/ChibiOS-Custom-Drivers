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
 * @file    epwm.c
 * @brief   EPWM Driver code.
 *
 * @addtogroup EPWM
 * @{
 */

#include "hal.h"
#include "epwm.h"

#if (HAL_USE_EPWM == TRUE) || defined(__DOXYGEN__)


/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   EPWM Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void epwmInit(void) {

  epwm_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p EPWMDriver structure.
 *
 * @param[out] epwmp    pointer to a @p EPWMDriver object
 *
 * @init
 */
void epwmObjectInit(EPWMDriver *epwmp) {

  epwmp->state    = EPWM_STOP;
  epwmp->config   = NULL;
  epwmp->enabled  = 0;
  epwmp->channels = 0;
#if defined(EPWM_DRIVER_EXT_INIT_HOOK)
  EPWM_DRIVER_EXT_INIT_HOOK(epwmp);
#endif
}

/**
 * @brief   Configures and activates the EPWM peripheral.
 * @note    Starting a driver that is already in the @p EPWM_READY state
 *          disables all the active channels.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] config    pointer to a @p EPWMConfig object
 *
 * @api
 */
void epwmStart(EPWMDriver *epwmp, const EPWMConfig *config) {

  osalDbgCheck((epwmp != NULL) && (config != NULL));

  osalSysLock();
  osalDbgAssert((epwmp->state == EPWM_STOP) || (epwmp->state == EPWM_READY),
                "invalid state");
  epwmp->config = config;
  epwmp->period = config->period;
  epwm_lld_start(epwmp);
  epwmp->enabled = 0;
  epwmp->state = EPWM_READY;
  osalSysUnlock();
}

/**
 * @brief   Deactivates the EPWM peripheral.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 *
 * @api
 */
void epwmStop(EPWMDriver *epwmp) {

  osalDbgCheck(epwmp != NULL);

  osalSysLock();
  osalDbgAssert((epwmp->state == EPWM_STOP) || (epwmp->state == EPWM_READY),
                "invalid state");
  epwm_lld_stop(epwmp);
  epwmp->enabled = 0;
  epwmp->state   = EPWM_STOP;
  osalSysUnlock();
}

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
 * @param[in] period    new cycle time in ticks
 *
 * @api
 */
void epwmChangePeriod(EPWMDriver *epwmp, epwmcnt_t period) {

  osalDbgCheck(epwmp != NULL);

  osalSysLock();
  osalDbgAssert(epwmp->state == EPWM_READY, "invalid state");
  epwmChangePeriodI(epwmp, period);
  osalSysUnlock();
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
 * @api
 */
void epwmEnableChannel(EPWMDriver *epwmp,
                      epwmchannel_t channel,
                      epwmcnt_t width) {

  osalDbgCheck((epwmp != NULL) && (channel < epwmp->channels));

  osalSysLock();

  osalDbgAssert(epwmp->state == EPWM_READY, "not ready");

  epwmEnableChannelI(epwmp, channel, width);

  osalSysUnlock();
}

/**
 * @brief   Disables a EPWM channel and its notification.
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
 * @api
 */
void epwmDisableChannel(EPWMDriver *epwmp, epwmchannel_t channel) {

  osalDbgCheck((epwmp != NULL) && (channel < epwmp->channels));

  osalSysLock();

  osalDbgAssert(epwmp->state == EPWM_READY, "not ready");

  epwmDisableChannelI(epwmp, channel);

  osalSysUnlock();
}

/**
 * @brief   Sends pulses when in one-pulse mode.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 *
 * @api
 */
void epwmSendPulses(EPWMDriver *epwmp) {
  osalDbgCheck(epwmp != NULL);

  osalSysLock();

  osalDbgAssert(epwmp->state == EPWM_READY, "not ready");
  osalDbgAssert(epwmp->config->operating_mode == EPWM_OPM_MODE, "not OPM");

  epwmSendPulsesI(epwmp);

  osalSysUnlock();
}

#endif /* HAL_USE_EPWM == TRUE */

/** @} */
