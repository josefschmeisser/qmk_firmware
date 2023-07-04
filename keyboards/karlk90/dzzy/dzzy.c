// Copyright 2020-2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include <hal.h>
#include <string.h>

void keyboard_post_init_user(void) {
#if defined(__riscv)
    // Free B4 pin.
    AFIO->MAPR |= AFIO_PCF0_SWJ_CFG_NOJNTRST;
#endif
    // Customise these values to desired behaviour
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse=true;
}

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputLow(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
/* We deliberatly choose "slower" push pull pins,
 * those are fast enough but with lower driving currents
 * should produce less EMI noise on the lines. */
#if defined(__riscv)
        /* This is actually implemented as a 2MHZ PP output. */
        palSetLineMode(row_pins[i], PAL_MODE_UNCONNECTED);
#else
        palSetLineMode(row_pins[i], (PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_LOWEST));
#endif
        writePinLow(row_pins[i]);
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    writePinHigh(row_pins[current_row]);
    while (readPin(row_pins[current_row]) != 1)
        ;

    current_matrix[current_row] = (matrix_row_t)palReadGroup(GPIOA, 0x3F, 0);

    writePinLow(row_pins[current_row]);

    /* Wait until col pins are high again or timer expired. */
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + MS2RTC(REALTIME_COUNTER_CLOCK, 5);
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if (palReadGroup(GPIOA, 0x3F, 0) == 0) {
            break;
        }
    }
}
