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

#include "scene_set_time.h"
#include <stdio.h>
#include <gb/gb.h>
#include "cram.h"
#include "rtc.h"

#define KEY_PRESS_COOLDOWN 10

void scene_set_time_draw(UINT8 selected, UINT8 hrs, UINT8 mins, UINT8 secs) {
    font_init();

    printf("Please set the time\n\n");
    if (hrs < 10) {
        printf("0");
    }
    printf("%d:", hrs);
    if (mins < 10) {
        printf("0");
    }
    printf("%d:", mins);
    if (secs < 10) {
        printf("0");
    }
    printf("%d\n", secs);

    if (selected == 0) {
        printf(" ^\n\n");
    } else if (selected == 1) {
        printf("    ^\n\n");
    } else if (selected == 2) {
        printf("       ^\n\n");
    }

    printf("Press START to save\n");
}

int scene_set_time() {
    UINT8 hrs, mins, secs;
    UINT8 selectionMode = 2;
    UINT16 vblanksPassed = 0;
    UINT8 looping = 1;

    RTC_SELECT_DAY_UPPER;
    RTC_LATCH_TIME;

    RTC_SELECT_SECONDS;
    secs = RTC_VALUE;

    RTC_SELECT_MINUTES;
    mins = RTC_VALUE;

    RTC_SELECT_HOURS;
    hrs = RTC_VALUE;

    scene_set_time_draw(selectionMode, hrs, mins, secs);

    while (looping) {
        if (vblanksPassed >= KEY_PRESS_COOLDOWN) {
            switch (joypad()) {
                case J_RIGHT:
                    vblanksPassed = 0;
                    selectionMode = (selectionMode + 1) % 3;
                    scene_set_time_draw(selectionMode, hrs, mins, secs);
                    break;
                case J_LEFT:
                    vblanksPassed = 0;
                    if (selectionMode == 0) {
                        selectionMode = 2;
                    } else {
                        selectionMode--;
                    }
                    scene_set_time_draw(selectionMode, hrs, mins, secs);
                    break;
                case J_UP:
                    vblanksPassed = 0;
                    switch (selectionMode) {
                        case 0:
                            hrs = (hrs + 1) % 24;
                            break;
                        case 1:
                            mins = (mins + 1) % 60;
                            break;
                        case 2:
                            secs = (secs + 1) % 60;
                            break;
                    }
                    scene_set_time_draw(selectionMode, hrs, mins, secs);
                    break;
                case J_DOWN:
                    vblanksPassed = 0;
                    switch (selectionMode) {
                        case 0:
                            if (hrs == 0) {
                                hrs = 23;
                            } else {
                                hrs--;
                            }
                            break;
                        case 1:
                            if (mins == 0) {
                                mins = 59;
                            } else {
                                mins--;
                            }
                            break;
                        case 2:
                            if (secs == 0) {
                                secs = 59;
                            } else {
                                secs--;
                            }
                            break;
                    }
                    scene_set_time_draw(selectionMode, hrs, mins, secs);
                    break;
                case J_START:
                    looping = 0;
                    break;
            }
        }
        wait_vbl_done();
        vblanksPassed++;
    }

    RTC_SELECT_SECONDS;
    RTC_VALUE = secs;

    RTC_SELECT_MINUTES;
    RTC_VALUE = mins;

    RTC_SELECT_HOURS;
    RTC_VALUE = hrs;

    RTC_SELECT_DAY_UPPER;
    RTC_UNLATCH_TIME;

    SWITCH_RAM_MBC3(0);
    CRAM_BANK0_IS_TIME_SET = 1;

    return 0;
}
