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

#include "tiles/mountain.h"
#include "maps/mountain.h"
#include "tiles/sprite.h"
#include "rtc.h"

// Workaround to work on FunkyBoy
#define PARALLAX_LYC_BEGIN 0x00

#define SPRITE_BIRD 0

#define BIRD_MIN_DEPTH 16
#define BIRD_MAX_DEPTH 100

#define IS_NIGHT_TIME \
RTC_VALUE <= 6 || RTC_VALUE >= 18

#define PALETTE_NIGHT_TIME 0b11111001
#define PALETTE_DAY_TIME 0b11100100

#define TIME_CHECK_COOLDOWN 50

int scroll = 0;

void vblank() {}

void intr_lyc() {
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

int scene_mountains() {
    UINT8 birdY = 60;
    UINT8 birdState = 0;
    UINT8 vblanksSinceCheckedTime = TIME_CHECK_COOLDOWN;
    UINT8 keys;

    set_bkg_data(0, 12, MountainTiles);
    set_bkg_tiles(0, 0, MountainsMapWidth, MountainsMapHeight, MountainsMap);

    SPRITES_8x8;
    set_sprite_data(0, 3, SpriteTiles);
    set_sprite_tile(SPRITE_BIRD, 0);

    STAT_REG = 0x45;
    LYC_REG = PARALLAX_LYC_BEGIN;

    disable_interrupts();
    add_LCD(intr_lyc);
    add_VBL(vblank);
    enable_interrupts();

    set_interrupts(VBL_IFLAG | LCD_IFLAG);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        if (vblanksSinceCheckedTime == TIME_CHECK_COOLDOWN) {
            RTC_SELECT_HOURS;
            if (IS_NIGHT_TIME) {
                *(UINT8*)0xFF47 = PALETTE_NIGHT_TIME;
            } else {
                *(UINT8*)0xFF47 = PALETTE_DAY_TIME;
            }
        }
        keys = joypad();
        if (keys & J_UP) {
            if (birdY > BIRD_MIN_DEPTH) {
                birdY--;
            }
        } else if (keys & J_DOWN) {
            if (birdY < BIRD_MAX_DEPTH) {
                birdY++;
            }
        } else if (birdState % 4 == 0 && birdY < BIRD_MAX_DEPTH) {
            birdY++;
        }
        birdState++;
        if (birdState == 90) {
            set_sprite_tile(SPRITE_BIRD, 1);
        } else if (birdState == 100) {
            set_sprite_tile(SPRITE_BIRD, 2);
        } else if (birdState == 110) {
            set_sprite_tile(SPRITE_BIRD, 1);
        } else if (birdState == 120) {
            set_sprite_tile(SPRITE_BIRD, 0);
            birdState = 0;
        }
        move_sprite(SPRITE_BIRD, 75, birdY);
        wait_vbl_done();
        scroll++;
        vblanksSinceCheckedTime++;
        move_bkg(scroll, 0);
    }
}
