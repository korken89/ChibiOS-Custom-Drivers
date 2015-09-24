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
 * @file    STM32/epwm_lld.c
 * @brief   STM32 EPWM subsystem low level driver header.
 *
 * @addtogroup EPWM
 * @{
 */

#include "hal.h"
#include "epwm.h"

#if HAL_USE_EPWM || defined(__DOXYGEN__)


/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   EPWMD1 driver identifier.
 * @note    The driver EPWMD1 allocates the complex timer TIM1 when enabled.
 */
#if STM32_EPWM_USE_TIM1 || defined(__DOXYGEN__)
EPWMDriver EPWMD1;
#endif

/**
 * @brief   EPWMD2 driver identifier.
 * @note    The driver EPWMD2 allocates the timer TIM2 when enabled.
 */
#if STM32_EPWM_USE_TIM2 || defined(__DOXYGEN__)
EPWMDriver EPWMD2;
#endif

/**
 * @brief   EPWMD3 driver identifier.
 * @note    The driver EPWMD3 allocates the timer TIM3 when enabled.
 */
#if STM32_EPWM_USE_TIM3 || defined(__DOXYGEN__)
EPWMDriver EPWMD3;
#endif

/**
 * @brief   EPWMD4 driver identifier.
 * @note    The driver EPWMD4 allocates the timer TIM4 when enabled.
 */
#if STM32_EPWM_USE_TIM4 || defined(__DOXYGEN__)
EPWMDriver EPWMD4;
#endif

/**
 * @brief   EPWMD5 driver identifier.
 * @note    The driver EPWMD5 allocates the timer TIM5 when enabled.
 */
#if STM32_EPWM_USE_TIM5 || defined(__DOXYGEN__)
EPWMDriver EPWMD5;
#endif

/**
 * @brief   EPWMD8 driver identifier.
 * @note    The driver EPWMD8 allocates the timer TIM8 when enabled.
 */
#if STM32_EPWM_USE_TIM8 || defined(__DOXYGEN__)
EPWMDriver EPWMD8;
#endif

/**
 * @brief   EPWMD9 driver identifier.
 * @note    The driver EPWMD9 allocates the timer TIM9 when enabled.
 */
#if STM32_EPWM_USE_TIM9 || defined(__DOXYGEN__)
EPWMDriver EPWMD9;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level EPWM driver initialization.
 *
 * @notapi
 */
void epwm_lld_init(void) {

#if STM32_EPWM_USE_TIM1
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD1);
  EPWMD1.channels = STM32_TIM1_CHANNELS;
  EPWMD1.tim = STM32_TIM1;
#endif

#if STM32_EPWM_USE_TIM2
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD2);
  EPWMD2.channels = STM32_TIM2_CHANNELS;
  EPWMD2.tim = STM32_TIM2;
#endif

#if STM32_EPWM_USE_TIM3
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD3);
  EPWMD3.channels = STM32_TIM3_CHANNELS;
  EPWMD3.tim = STM32_TIM3;
#endif

#if STM32_EPWM_USE_TIM4
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD4);
  EPWMD4.channels = STM32_TIM4_CHANNELS;
  EPWMD4.tim = STM32_TIM4;
#endif

#if STM32_EPWM_USE_TIM5
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD5);
  EPWMD5.channels = STM32_TIM5_CHANNELS;
  EPWMD5.tim = STM32_TIM5;
#endif

#if STM32_EPWM_USE_TIM8
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD8);
  EPWMD8.channels = STM32_TIM8_CHANNELS;
  EPWMD8.tim = STM32_TIM8;
#endif

#if STM32_EPWM_USE_TIM9
  /* Driver initialization.*/
  epwmObjectInit(&EPWMD9);
  EPWMD9.channels = STM32_TIM9_CHANNELS;
  EPWMD9.tim = STM32_TIM9;
#endif
}

/**
 * @brief   Configures and activates the EPWM peripheral.
 * @note    Starting a driver that is already in the @p EPWM_READY state
 *          disables all the active channels.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 *
 * @notapi
 */
void epwm_lld_start(EPWMDriver *epwmp) {
  uint32_t psc;
  uint32_t ccer;

  if (epwmp->state == EPWM_STOP) {
    /* Clock activation and timer reset.*/
#if STM32_EPWM_USE_TIM1
    if (&EPWMD1 == epwmp) {
      rccEnableTIM1(FALSE);
      rccResetTIM1();
#if defined(STM32_TIM1CLK)
      epwmp->clock = STM32_TIM1CLK;
#else
      epwmp->clock = STM32_TIMCLK2;
#endif
    }
#endif

#if STM32_EPWM_USE_TIM2
    if (&EPWMD2 == epwmp) {
      rccEnableTIM2(FALSE);
      rccResetTIM2();
#if defined(STM32_TIM2CLK)
      epwmp->clock = STM32_TIM2CLK;
#else
      epwmp->clock = STM32_TIMCLK1;
#endif
    }
#endif

#if STM32_EPWM_USE_TIM3
    if (&EPWMD3 == epwmp) {
      rccEnableTIM3(FALSE);
      rccResetTIM3();
#if defined(STM32_TIM3CLK)
      epwmp->clock = STM32_TIM3CLK;
#else
      epwmp->clock = STM32_TIMCLK1;
#endif
    }
#endif

#if STM32_EPWM_USE_TIM4
    if (&EPWMD4 == epwmp) {
      rccEnableTIM4(FALSE);
      rccResetTIM4();
#if defined(STM32_TIM4CLK)
      epwmp->clock = STM32_TIM4CLK;
#else
      epwmp->clock = STM32_TIMCLK1;
#endif
    }
#endif

#if STM32_EPWM_USE_TIM5
    if (&EPWMD5 == epwmp) {
      rccEnableTIM5(FALSE);
      rccResetTIM5();
#if defined(STM32_TIM5CLK)
      epwmp->clock = STM32_TIM5CLK;
#else
      epwmp->clock = STM32_TIMCLK1;
#endif
    }
#endif

#if STM32_EPWM_USE_TIM8
    if (&EPWMD8 == epwmp) {
      rccEnableTIM8(FALSE);
      rccResetTIM8();
#if defined(STM32_TIM8CLK)
      epwmp->clock = STM32_TIM8CLK;
#else
      epwmp->clock = STM32_TIMCLK2;
#endif
    }
#endif

#if STM32_EPWM_USE_TIM9
    if (&EPWMD9 == epwmp) {
      rccEnableTIM9(FALSE);
      rccResetTIM9();
#if defined(STM32_TIM9CLK)
      epwmp->clock = STM32_TIM9CLK;
#else
      epwmp->clock = STM32_TIMCLK2;
#endif
    }
#endif
    if (epwmp->config->operating_mode == EPWM_PWM_MODE) {
      /* All channels configured in PWM1 mode with preload enabled and will
         stay that way until the driver is stopped. */
      epwmp->tim->CCMR1 = STM32_TIM_CCMR1_OC1M(6) | STM32_TIM_CCMR1_OC1PE |
                          STM32_TIM_CCMR1_OC2M(6) | STM32_TIM_CCMR1_OC2PE;
      epwmp->tim->CCMR2 = STM32_TIM_CCMR2_OC3M(6) | STM32_TIM_CCMR2_OC3PE |
                          STM32_TIM_CCMR2_OC4M(6) | STM32_TIM_CCMR2_OC4PE;
#if STM32_TIM_MAX_CHANNELS > 4
      epwmp->tim->CCMR3 = STM32_TIM_CCMR3_OC5M(6) | STM32_TIM_CCMR3_OC5PE |
                          STM32_TIM_CCMR3_OC6M(6) | STM32_TIM_CCMR3_OC6PE;
#endif
    }
    else {
      /* All channels configured in PWM2 mode for the one-pulse mode to
         function properly. */
      epwmp->tim->CCMR1 = STM32_TIM_CCMR1_OC1M(7) | STM32_TIM_CCMR1_OC2M(7);
      epwmp->tim->CCMR2 = STM32_TIM_CCMR2_OC3M(7) | STM32_TIM_CCMR2_OC4M(7);
#if STM32_TIM_MAX_CHANNELS > 4
      epwmp->tim->CCMR3 = STM32_TIM_CCMR3_OC5M(7) | STM32_TIM_CCMR3_OC6M(7);
#endif

    }
  }
  else {
    /* Driver re-configuration scenario, it must be stopped first.*/
    epwmp->tim->CR1    = 0;                  /* Timer disabled.              */
    epwmp->tim->CCR[0] = 0;                  /* Comparator 1 disabled.       */
    epwmp->tim->CCR[1] = 0;                  /* Comparator 2 disabled.       */
    epwmp->tim->CCR[2] = 0;                  /* Comparator 3 disabled.       */
    epwmp->tim->CCR[3] = 0;                  /* Comparator 4 disabled.       */
#if STM32_TIM_MAX_CHANNELS > 4
    if (epwmp->channels > 4) {
      epwmp->tim->CCXR[0] = 0;               /* Comparator 5 disabled.       */
      epwmp->tim->CCXR[1] = 0;               /* Comparator 6 disabled.       */
    }
#endif
    epwmp->tim->CNT  = 0;                    /* Counter reset to zero.       */
  }

  /* Timer configuration.*/
  psc = (epwmp->clock / epwmp->config->frequency) - 1;
  osalDbgAssert((psc <= 0xFFFF) &&
                ((psc + 1) * epwmp->config->frequency) == epwmp->clock,
                "invalid frequency");
  epwmp->tim->PSC  = psc;
  epwmp->tim->ARR  = epwmp->period - 1;
  epwmp->tim->CR2  = 0;

  /* Output enables and polarities setup.*/
  ccer = 0;
  switch (epwmp->config->channels[0].mode & EPWM_OUTPUT_MASK) {
  case EPWM_OUTPUT_ACTIVE_LOW:
    ccer |= STM32_TIM_CCER_CC1P;
  case EPWM_OUTPUT_ACTIVE_HIGH:
    ccer |= STM32_TIM_CCER_CC1E;
  default:
    ;
  }
  switch (epwmp->config->channels[1].mode & EPWM_OUTPUT_MASK) {
  case EPWM_OUTPUT_ACTIVE_LOW:
    ccer |= STM32_TIM_CCER_CC2P;
  case EPWM_OUTPUT_ACTIVE_HIGH:
    ccer |= STM32_TIM_CCER_CC2E;
  default:
    ;
  }
  switch (epwmp->config->channels[2].mode & EPWM_OUTPUT_MASK) {
  case EPWM_OUTPUT_ACTIVE_LOW:
    ccer |= STM32_TIM_CCER_CC3P;
  case EPWM_OUTPUT_ACTIVE_HIGH:
    ccer |= STM32_TIM_CCER_CC3E;
  default:
    ;
  }
  switch (epwmp->config->channels[3].mode & EPWM_OUTPUT_MASK) {
  case EPWM_OUTPUT_ACTIVE_LOW:
    ccer |= STM32_TIM_CCER_CC4P;
  case EPWM_OUTPUT_ACTIVE_HIGH:
    ccer |= STM32_TIM_CCER_CC4E;
  default:
    ;
  }

  epwmp->tim->CCER  = ccer;
  epwmp->tim->EGR   = STM32_TIM_EGR_UG;         /* Update event.             */
  epwmp->tim->SR    = 0;                        /* Clear pending IRQs.       */
  epwmp->tim->DIER  = ~STM32_TIM_DIER_IRQ_MASK; /* DMA-related DIER settings.*/

#if STM32_EPWM_USE_TIM1 || STM32_EPWM_USE_TIM8
  epwmp->tim->BDTR  = STM32_TIM_BDTR_MOE;
#endif

  if (epwmp->config->operating_mode == EPWM_PWM_MODE) {
    /* Timer configured and started.*/
    epwmp->tim->CR1 = STM32_TIM_CR1_ARPE | STM32_TIM_CR1_URS |
                      STM32_TIM_CR1_CEN;
  }
  else {
    /* Timer is not started. OPM requires the timer to be started at the same
       time as the values are set up. */
    epwmp->tim->CR1 = 0;
  }
}

/**
 * @brief   Deactivates the EPWM peripheral.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 *
 * @notapi
 */
void epwm_lld_stop(EPWMDriver *epwmp) {

  /* If in ready state then disables the EPWM clock.*/
  if (epwmp->state == EPWM_READY) {
    epwmp->tim->CR1  = 0;                    /* Timer disabled.              */
    epwmp->tim->DIER = 0;                    /* All IRQs disabled.           */
    epwmp->tim->SR   = 0;                    /* Clear eventual pending IRQs. */
#if STM32_EPWM_USE_TIM1 || STM32_EPWM_USE_TIM8
    epwmp->tim->BDTR  = 0;
#endif

#if STM32_EPWM_USE_TIM1
    if (&EPWMD1 == epwmp) {
      rccDisableTIM1(FALSE);
    }
#endif

#if STM32_EPWM_USE_TIM2
    if (&EPWMD2 == epwmp) {
      rccDisableTIM2(FALSE);
    }
#endif

#if STM32_EPWM_USE_TIM3
    if (&EPWMD3 == epwmp) {
      rccDisableTIM3(FALSE);
    }
#endif

#if STM32_EPWM_USE_TIM4
    if (&EPWMD4 == epwmp) {
      rccDisableTIM4(FALSE);
    }
#endif

#if STM32_EPWM_USE_TIM5
    if (&EPWMD5 == epwmp) {
      rccDisableTIM5(FALSE);
    }
#endif

#if STM32_EPWM_USE_TIM8
    if (&EPWMD8 == epwmp) {
      rccDisableTIM8(FALSE);
    }
#endif

#if STM32_EPWM_USE_TIM9
    if (&EPWMD9 == epwmp) {
      rccDisableTIM9(FALSE);
    }
#endif
  }
}

/**
 * @brief   Enables a EPWM channel.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 * @post    The channel is active using the specified configuration.
 * @note    The function has effect at the next cycle start.
 * @note    Channel notification is not enabled.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] channel   EPWM channel identifier (0...channels-1)
 * @param[in] width     EPWM pulse width as clock pulses number
 *
 * @notapi
 */
void epwm_lld_enable_channel(EPWMDriver *epwmp,
                            epwmchannel_t channel,
                            epwmcnt_t width) {

  if (epwmp->config->operating_mode == EPWM_PWM_MODE) {
    /* Changing channel duty cycle on the fly in PWM mode. */
#if STM32_TIM_MAX_CHANNELS <= 4
    epwmp->tim->CCR[channel] = width;
#else
    if (channel <= 4)
      epwmp->tim->CCR[channel] = width;
    else
      epwmp->tim->CCXR[channel - 4] = width;
#endif
  }
  else {
    /* Calculate the new values for the pulse mode. */
#if STM32_TIM_MAX_CHANNELS <= 4
    epwmp->tim->CCR[channel] = epwmp->tim->ARR - width;
#else
    if (channel <= 4)
      epwmp->tim->CCR[channel] = epwmp->tim->ARR - width;
    else
      epwmp->tim->CCXR[channel - 4] = epwmp->tim->ARR - width;
#endif
  }
}

/**
 * @brief   Disables a EPWM channel and its notification.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 * @post    The channel is disabled and its output line returned to the
 *          idle state.
 * @note    The function has effect at the next cycle start.
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 * @param[in] channel   EPWM channel identifier (0...channels-1)
 *
 * @notapi
 */
void epwm_lld_disable_channel(EPWMDriver *epwmp, epwmchannel_t channel) {

#if STM32_TIM_MAX_CHANNELS <= 4
  epwmp->tim->CCR[channel] = 0;
#else
  if (channel <= 4) {
    epwmp->tim->CCR[channel] = 0;
  }
  else
    epwmp->tim->CCXR[channel - 4] = 0;
#endif
}

/**
 * @brief   When in one-pulse mode, start the timer to send the pulses.
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 *
 * @param[in] epwmp     pointer to a @p EPWMDriver object
 *
 * @notapi
 */
void epwm_lld_send_pulses(EPWMDriver *epwmp) {

  if (epwmp->config->operating_mode == EPWM_OPM_MODE) {
    epwmp->tim->CR1 = STM32_TIM_CR1_CEN | STM32_TIM_CR1_OPM;
  }
}

#endif /* HAL_USE_EPWM */

/** @} */
