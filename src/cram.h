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

#ifndef CRAM_H
#define CRAM_H

#define CRAM_BANK0_IS_TIME_SET *(unsigned char *)0xA005


#define ENABLE_RAM_MBC3 \
  *(unsigned char *)0x0000 = 0x0A

#define DISABLE_RAM_MBC3 \
  *(unsigned char *)0x0000 = 0x00

#define SWITCH_RAM_MBC3(b) \
  *(unsigned char *)0x4000 = (b)


void cram_init();

#endif