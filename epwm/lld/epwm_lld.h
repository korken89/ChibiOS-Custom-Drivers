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
 * @file    STM32/epwm_lld.h
 * @brief   STM32 EPWM subsystem low level driver header.
 *
 * @addtogroup EPWM
 * @{
 */

#ifndef _EPWM_LLD_H_
#define _EPWM_LLD_H_

#if HAL_USE_EPWM || defined(__DOXYGEN__)

#include "stm32_tim.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Number of EPWM channels per EPWM driver.
 */
#define EPWM_CHANNELS                            STM32_TIM_MAX_CHANNELS

/**
 * @name    STM32-specific EPWM complementary output mode macros
 * @{
 */
/**
 * @brief   Complementary output modes mask.
 * @note    This is an STM32-specific setting.
 */
#define EPWM_COMPLEMENTARY_OUTPUT_MASK           0xF0

/**
 * @brief   Complementary output not driven.
 * @note    This is an STM32-specific setting.
 */
#define EPWM_COMPLEMENTARY_OUTPUT_DISABLED       0x00

/**
 * @brief   Complementary output, active is logic level one.
 * @note    This is an STM32-specific setting.
 * @note    This setting is only available if the configuration option
 *          @p STM32_EPWM_USE_ADVANCED is set to TRUE and only for advanced
 *          timers TIM1 and TIM8.
 */
#define EPWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH    0x10

/**
 * @brief   Complementary output, active is logic level zero.
 * @note    This is an STM32-specific setting.
 * @note    This setting is only available if the configuration option
 *          @p STM32_EPWM_USE_ADVANCED is set to TRUE and only for advanced
 *          timers TIM1 and TIM8.
 */
#define EPWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW     0x20
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   EPWMD1 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD1 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM1) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM1                  FALSE
#endif

/**
 * @brief   EPWMD2 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD2 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM2) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM2                  FALSE
#endif

/**
 * @brief   EPWMD3 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD3 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM3) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM3                  FALSE
#endif

/**
 * @brief   EPWMD4 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD4 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM4) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM4                  FALSE
#endif

/**
 * @brief   EPWMD5 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD5 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM5) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM5                  FALSE
#endif

/**
 * @brief   EPWMD8 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD8 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM8) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM8                  FALSE
#endif

/**
 * @brief   EPWMD9 driver enable switch.
 * @details If set to @p TRUE the support for EPWMD9 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_EPWM_USE_TIM9) || defined(__DOXYGEN__)
#define STM32_EPWM_USE_TIM9                  FALSE
#endif

/** @} */

/*===========================================================================*/
/* Configuration checks.                                                     */
/*===========================================================================*/

#if STM32_EPWM_USE_TIM1 && !STM32_HAS_TIM1
#error "TIM1 not present in the selected device"
#endif

#if STM32_EPWM_USE_TIM2 && !STM32_HAS_TIM2
#error "TIM2 not present in the selected device"
#endif

#if STM32_EPWM_USE_TIM3 && !STM32_HAS_TIM3
#error "TIM3 not present in the selected device"
#endif

#if STM32_EPWM_USE_TIM4 && !STM32_HAS_TIM4
#error "TIM4 not present in the selected device"
#endif

#if STM32_EPWM_USE_TIM5 && !STM32_HAS_TIM5
#error "TIM5 not present in the selected device"
#endif

#if STM32_EPWM_USE_TIM8 && !STM32_HAS_TIM8
#error "TIM8 not present in the selected device"
#endif

#if STM32_EPWM_USE_TIM9 && !STM32_HAS_TIM9
#error "TIM9 not present in the selected device"
#endif

#if !STM32_EPWM_USE_TIM1 && !STM32_EPWM_USE_TIM2 &&                           \
    !STM32_EPWM_USE_TIM3 && !STM32_EPWM_USE_TIM4 &&                           \
    !STM32_EPWM_USE_TIM5 && !STM32_EPWM_USE_TIM8 &&                           \
    !STM32_EPWM_USE_TIM9
#error "EPWM driver activated but no TIM peripheral assigned"
#endif

#if STM32_EPWM_USE_ADVANCED && !STM32_EPWM_USE_TIM1 && !STM32_EPWM_USE_TIM8
#error "advanced mode selected but no advanced timer assigned"
#endif

/* Checks on allocation of TIMx units.*/
#if STM32_EPWM_USE_TIM1
#if defined(STM32_TIM1_IS_USED)
#error "EPWMD1 requires TIM1 but the timer is already used"
#else
#define STM32_TIM1_IS_USED
#endif
#endif

#if STM32_EPWM_USE_TIM2
#if defined(STM32_TIM2_IS_USED)
#error "EPWMD2 requires TIM2 but the timer is already used"
#else
#define STM32_TIM2_IS_USED
#endif
#endif

#if STM32_EPWM_USE_TIM3
#if defined(STM32_TIM3_IS_USED)
#error "EPWMD3 requires TIM3 but the timer is already used"
#else
#define STM32_TIM3_IS_USED
#endif
#endif

#if STM32_EPWM_USE_TIM4
#if defined(STM32_TIM4_IS_USED)
#error "EPWMD4 requires TIM4 but the timer is already used"
#else
#define STM32_TIM4_IS_USED
#endif
#endif

#if STM32_EPWM_USE_TIM5
#if defined(STM32_TIM5_IS_USED)
#error "EPWMD5 requires TIM5 but the timer is already used"
#else
#define STM32_TIM5_IS_USED
#endif
#endif

#if STM32_EPWM_USE_TIM8
#if defined(STM32_TIM8_IS_USED)
#error "EPWMD8 requires TIM8 but the timer is already used"
#else
#define STM32_TIM8_IS_USED
#endif
#endif

#if STM32_EPWM_USE_TIM9
#if defined(STM32_TIM9_IS_USED)
#error "EPWMD9 requires TIM9 but the timer is already used"
#else
#define STM32_TIM9_IS_USED
#endif
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a EPWM mode.
 */
typedef uint32_t epwmmode_t;

/**
 * @brief   Type of a EPWM channel.
 */
typedef uint8_t epwmchannel_t;

/**
 * @brief   Type of a channels mask.
 */
typedef uint32_t epwmchnmsk_t;

/**
 * @brief   Type of a EPWM counter.
 */
typedef uint32_t epwmcnt_t;

/**
 * @brief   Type of a EPWM driver channel configuration structure.
 */
typedef struct {
  /**
   * @brief Channel active logic level.
   */
  epwmmode_t                 mode;
} EPWMChannelConfig;

/**
 * @brief   PWM or OPM selector
 */
typedef enum {
  EPWM_PWM_MODE = 0,
  EPWM_OPM_MODE
} epwmoperatingmode_t;

/**
 * @brief   Type of a EPWM driver configuration structure.
 */
typedef struct {
  /**
   * @brief   Timer clock in Hz.
   * @note    The low level can use assertions in order to catch invalid
   *          frequency specifications.
   */
  uint32_t                  frequency;
  /**
   * @brief   EPWM period in ticks.
   * @note    The low level can use assertions in order to catch invalid
   *          period specifications.
   */
  epwmcnt_t                  period;
  /**
   * @brief   Channels configurations, normal or inverted.
   */
  EPWMChannelConfig          channels[EPWM_CHANNELS];
  /**
   * @brief   Selector for the mode, PWM or OPM.
   */
  epwmoperatingmode_t        operating_mode;
} EPWMConfig;

/**
 * @brief   Structure representing a EPWM driver.
 */
struct EPWMDriver {
  /**
   * @brief Driver state.
   */
  epwmstate_t                state;
  /**
   * @brief Current driver configuration data.
   */
  const EPWMConfig           *config;
  /**
   * @brief   Current EPWM period in ticks, also the stop in one-pulse mode.
   */
  epwmcnt_t                  period;
  /**
   * @brief   Mask of the enabled channels.
   */
  epwmchnmsk_t               enabled;
  /**
   * @brief   Number of channels in this instance.
   */
  epwmchannel_t              channels;
  /**
   * @brief Timer base clock.  */
  uint32_t                  clock;
  /**
   * @brief Pointer to the TIMx registers block.
   */
  stm32_tim_t               *tim;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Changes the period the EPWM peripheral.
 * @details This function changes the period of a EPWM unit that has already
 *          been activated using @p epwmStart().
 * @pre     The EPWM unit must have been activated using @p epwmStart().
 * @post    The EPWM unit period is changed to the new value.
 * @note    The function has effect at the next cycle start.
 * @note    If a period is specified that is shorter than the pulse width
 *          programmed in one of the channels then the behavior is not
 *          guaranteed.
 *
 * @param[in] epwmp      pointer to a @p EPWMDriver object
 * @param[in] period    new cycle time in ticks
 *
 * @notapi
 */
#define epwm_lld_change_period(epwmp, period)                                 \
  ((epwmp)->tim->ARR = ((period) - 1))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_EPWM_USE_TIM1 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD1;
#endif

#if STM32_EPWM_USE_TIM2 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD2;
#endif

#if STM32_EPWM_USE_TIM3 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD3;
#endif

#if STM32_EPWM_USE_TIM4 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD4;
#endif

#if STM32_EPWM_USE_TIM5 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD5;
#endif

#if STM32_EPWM_USE_TIM8 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD8;
#endif

#if STM32_EPWM_USE_TIM9 && !defined(__DOXYGEN__)
extern EPWMDriver EPWMD9;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void epwm_lld_init(void);
  void epwm_lld_start(EPWMDriver *epwmp);
  void epwm_lld_stop(EPWMDriver *epwmp);
  void epwm_lld_enable_channel(EPWMDriver *epwmp,
                              epwmchannel_t channel,
                              epwmcnt_t width);
  void epwm_lld_disable_channel(EPWMDriver *epwmp, epwmchannel_t channel);
  void epwm_lld_send_pulses(EPWMDriver *epwmp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_EPWM */

#endif /* _EPWM_LLD_H_ */

/** @} */
