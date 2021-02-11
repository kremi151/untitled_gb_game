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
#include "sprite_tiles.h"

// Workaround to work on FunkyBoy
#define PARALLAX_LYC_BEGIN 0x01

#define SPRITE_BIRD 0

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
    char birdY = 60;
    unsigned char birdState = 0;

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
        switch (joypad()) {
            case J_UP:
                if (birdY > 16) {
                    birdY--;
                }
                break;
            case J_DOWN:
                if (birdY < 100) {
                    birdY++;
                }
                break;
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
        move_bkg(scroll, 0);
    }
}
