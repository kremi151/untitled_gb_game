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

#include <stdio.h>
#include <gb/gb.h>

#include "mountain_tiles.h"
#include "mountain_map.h"

// Workaround to work on FunkyBoy
#define PARALLAX_LYC_BEGIN 0x01

int scroll = 0;

void vblank() {}

void intr_lyc() {
    //move_bkg(LYC_REG, 0);
    //LYC_REG = (LYC_REG + 2) % 0x64;

    if (LYC_REG == PARALLAX_LYC_BEGIN) {
        // Clouds
        move_bkg(scroll, 0);
        LYC_REG = 0x28;
    } else if (LYC_REG == 0x28) {
        // Mountains
        move_bkg(scroll/2, 0);
        LYC_REG = 0x70;
    } else if (LYC_REG == 0x70) {
        // Grass
        move_bkg(scroll, 0);
        LYC_REG = PARALLAX_LYC_BEGIN;
    }
}

int main () {
    set_bkg_data(0, 12, MountainTiles);
    set_bkg_tiles(0, 0, MountainsMapWidth, MountainsMapHeight, MountainsMap);

    STAT_REG = 0x45;
    LYC_REG = PARALLAX_LYC_BEGIN;

    disable_interrupts();
    add_LCD(intr_lyc);
    add_VBL(vblank);
    enable_interrupts();

    set_interrupts(VBL_IFLAG | LCD_IFLAG);

    SHOW_BKG;
    DISPLAY_ON;

    /*int c = 0;
    font_init();
    while (c++ < 19) {
        printf("Greetings planet!\n");
    }*/


    while (1) {
        //c = 0;
        //printf("a");
        wait_vbl_done();
        scroll++;
        //printf("b");
        move_bkg(scroll, 0);
    }
}