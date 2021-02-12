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

#include "cram.h"
#include <gb/gb.h>

UINT8 cram_check_init() {
    if (*(UINT8*)0xA000 != 0x18) {
        return 0;
    }
    if (*(UINT8*)0xA001 != 0x06) {
        return 0;
    }
    if (*(UINT8*)0xA002 != 0xBA) {
        return 0;
    }
    if (*(UINT8*)0xA003 != 0xDA) {
        return 0;
    }
    if (*(UINT8*)0xA004 != 0x55) {
        return 0;
    }
    return 1;
}

void cram_init() {
    UINT8 *addr;

    ENABLE_RAM_MBC3;

    SWITCH_RAM_MBC3(0);
    if (cram_check_init()) {
        return;
    }

    // Cartridge RAM does not start with the expected sequence, this means
    // that it contains garbage. Let's zero-initialize it.

    *(UINT8*)0xA000 = 0x18;
    *(UINT8*)0xA001 = 0x06;
    *(UINT8*)0xA002 = 0xBA;
    *(UINT8*)0xA003 = 0xDA;
    *(UINT8*)0xA004 = 0x55;
    addr = 0xA005;
    while (addr <= 0xBFFF) {
        *addr = 0x00;
        addr++;
    }

    SWITCH_RAM_MBC3(1);
    addr = 0xA000;
    while (addr <= 0xBFFF) {
        *addr = 0x00;
        addr++;
    }

    SWITCH_RAM_MBC3(2);
    addr = 0xA000;
    while (addr <= 0xBFFF) {
        *addr = 0x00;
        addr++;
    }

    SWITCH_RAM_MBC3(3);
    addr = 0xA000;
    while (addr <= 0xBFFF) {
        *addr = 0x00;
        addr++;
    }
}