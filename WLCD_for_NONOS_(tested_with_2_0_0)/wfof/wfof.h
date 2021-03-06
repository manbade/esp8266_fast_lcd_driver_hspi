/*
 * Created by Martin Winkelhofer 02,03,04,11/2016
 * W-Dimension / wdim / wdim0 / winkelhofer.m@gmail.com / https://github.com/wdim0
 *    _____ __          ____         ______         __
 *   / __(_) /__ ___   / __ \___    / __/ /__ ____ / /
 *  / _// / / -_|_-<  / /_/ / _ \  / _// / _ `(_-</ _ \
 * /_/ /_/_/\__/___/  \____/_//_/ /_/ /_/\_,_/___/_//_/
 *
 * System for compiling binary data of files in specific directory (wfof/content) as a part of
 * program data -> will be written to Flash memory + system of functions for reading it.
 * v2.01 (11/2016)
 *
 * This file is part of WFOF - W-Dimension's Files On Flash for ESP8266.
 *
 * WFOF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WFOF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WFOF. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __WFOF_H__
#define __WFOF_H__

#include <c_types.h>
//#include <xtensa/config/core-isa.h> //to know XCHAL_INSTROM0_PADDR

//==== main config of WFOF

/* WFOF has no config. Your main interaction with it will consist of these steps:
 * 1] copy all files you need into some directory (wfof/content)
 * 2] run wfof_gen.exe tool for generating wfof_data.h and wfof_idxs.h files
 * 3] include wfof.h and wfof_idxs.h in your code
 * 4] use wfof_* functions to retrieve binary data of your files
 */

//====

#define WFOF_VERSION			"v2.01" //11/2016

typedef struct {
	const uint32_t Offs;
	const uint32_t Size;
	const char* Name;
} wfof_file_struct;

typedef struct {
	const uint8_t FilesCnt;   //max 254 files (index 255 reserved for WFOF_INVALID_INDEX)
	const uint8_t AlignBytes; //1/2/4 - wfof_file_struct .Offs is related to this
	const wfof_file_struct Files[];
} wfof_ftab_struct;

#define WFOF_INVALID_INDEX		255

//#define WFOF_SPIFLASH_OFFS	XCHAL_INSTROM0_PADDR //offset where SPI FLASH is mapped on ESP8266 - for ESP8266 it's 0x40200000
//not used anymore, but leaved here to keep know-how

//---- provided functions

int8_t ICACHE_FLASH_ATTR wfof_get_file_info(char* FName, uint8_t* RetFileIndex, uint32_t* RetSize); //0 on success and -1 on failure
//You can also use constants defined in "wfof_idxs.h" if you know the name of file exactly to save time
//
uint32_t ICACHE_FLASH_ATTR wfof_get_file_data(uint8_t FileIndex, uint8_t* RetBuf, uint32_t Offs, uint32_t Bytes); //returns number of bytes that were really read
uint32_t /*ICACHE_FLASH_ATTR*/ wfof_get_file_data_fast(uint8_t FileIndex, uint32_t* RetBuf, uint32_t Offs, uint32_t Bytes); //returns number of bytes that were really read ! RetBuf must be 4-bytes aligned array and Offs must be multiples of 4
//
int8_t ICACHE_FLASH_ATTR wfof_find_char_pos(uint8_t FileIndex, uint32_t Offs, char Ch, uint32_t* RetPos); //0 on success and fills RetPos or returns -1 on failure

//----

#endif
