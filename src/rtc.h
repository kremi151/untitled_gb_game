/**
 * Untitled Game Boy game
 * Copyright (C) 2021  kremi151 (Michel Kremer)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef RTC_H
#define RTC_H

#include "cram.h"

#define RTC_SELECT_SECONDS SWITCH_RAM_MBC3(0x08)
#define RTC_SELECT_MINUTES SWITCH_RAM_MBC3(0x09)
#define RTC_SELECT_HOURS SWITCH_RAM_MBC3(0x0A)
#define RTC_SELECT_DAY_LOWER SWITCH_RAM_MBC3(0x0B)
#define RTC_SELECT_DAY_UPPER SWITCH_RAM_MBC3(0x0C)

#define RTC_VALUE *(UINT8*)0xA000

#define RTC_LATCH_TIME \
RTC_VALUE |= 0b01000000

#define RTC_UNLATCH_TIME \
RTC_VALUE &= 0b10111111

#endif