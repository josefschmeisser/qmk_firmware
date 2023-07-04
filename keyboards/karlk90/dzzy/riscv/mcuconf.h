// Copyright 2020-2023 Stefan Kerkmann (@karlk90)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef GD32_SPI_USE_SPI1
#define GD32_SPI_USE_SPI1 TRUE
