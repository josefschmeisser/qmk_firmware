// Copyright 2023 Stefan Kerkmann (@Karlk90)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

// SPI configuration
#define SPI_MATRIX_CHIP_SELECT_PIN GP1
#define SPI_MATRIX_LATCH_PIN GP3
#define SPI_MATRIX_DIVISOR 16
#define SPI_DRIVER SPID0
#define SPI_MISO_PIN GP0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3

// LED configuration
#define LED_NUM_LOCK_PIN GP17
#define LED_CAPS_LOCK_PIN GP16
#define LED_SCROLL_LOCK_PIN GP15
#define LED_PIN_ON_STATE 0

// Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed
#define DEBOUNCE 5

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
