// Copyright 2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "spi_master.h"

static pin_t       row_pins[MATRIX_ROWS] = {GP28, GP27, GP26, GP22, GP21, GP20, GP19, GP18};
static const pin_t latch_pin             = GP3;

void matrix_init_custom(void) {
    // SPI Matrix
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN);
    writePinHigh(SPI_MATRIX_CHIP_SELECT_PIN);

    spi_init();
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN, false, 0, SPI_MATRIX_DIVISOR);
    setPinOutput(latch_pin);
    writePinLow(latch_pin);

    for (int row = 0; row < MATRIX_ROWS; row++) {
        setPinOutput(row_pins[row]);
        writePinLow(row_pins[row]);
    }
}

/**
 * @brief Helper function to wait until a pin  has reached the wanted target
 * state. This only works for Push-Pull pins with enabled input stage.
 */
static void __time_critical_func(write_and_wait_for_pin)(pin_t pin, uint8_t target_state) {
    writePin(pin, target_state);
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + MS2RTC(REALTIME_COUNTER_CLOCK, 20);
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if (readPin(pin) == target_state) {
            return;
        }
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[MATRIX_ROWS]) {
    matrix_row_t input_matrix[MATRIX_ROWS] = {0};

    for (int row = 0; row < MATRIX_ROWS; row++) {
        write_and_wait_for_pin(row_pins[row], 1);
        write_and_wait_for_pin(latch_pin, 1);
        write_and_wait_for_pin(latch_pin, 0);
        write_and_wait_for_pin(row_pins[row], 0);
        spiSelect(&SPI_DRIVER);
        spiReceive(&SPI_DRIVER, sizeof(matrix_row_t), &input_matrix[row]);
        spiUnselect(&SPI_DRIVER);
    }

    // Check if we've changed, return the last-read data
    bool changed = memcmp(current_matrix, input_matrix, sizeof(input_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, input_matrix, sizeof(input_matrix));
    }
    return changed;
}
