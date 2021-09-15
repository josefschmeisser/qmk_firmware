// Copyright 2020-2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* GD32VF103 */
#include_next <mcuconf.h>

#undef GD32_I2C_USE_I2C0
#define GD32_I2C_USE_I2C0 TRUE

#undef GD32_PWM_USE_ADVANCED
#define GD32_PWM_USE_ADVANCED TRUE

#undef GD32_PWM_USE_TIM0
#define GD32_PWM_USE_TIM0 TRUE

#undef GD32_SERIAL_USE_USART2
#define GD32_SERIAL_USE_USART2 TRUE
