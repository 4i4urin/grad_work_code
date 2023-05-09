/*
 * fft_table.h
 *
 *  Created on: 5 апр. 2023 г.
 *      Author: shishel
 */

#ifndef FFT_TABLE_H_
#define FFT_TABLE_H_

/* All this can be changed to
 * t_complex_s8.re     =  cos(PI * group_size / base) * 100;
 * t_complex_s8.im     = -sin(PI * group_size / base) * 100;
 */


#if (FFT_DATA_NUM == 64)
	static const t_complex_s8 table_fft_arr[16] = {
			{  64,    0}, {  63,   -5}, {  62,  -12},
			{  60,  -18}, {  58,  -24}, {  56,  -30},
			{  53,  -35}, {  49,  -40}, {  44,  -44},
			{  40,  -49}, {  35,  -53}, {  30,  -56},
			{  24,  -58}, {  18,  -60}, {  12,  -62},
			{   5,  -63}
	};

#elif (FFT_DATA_NUM == 1024)
	static const t_complex_s8 table_fft_arr[256] = {
		{  64,    0}, {  63,    0}, {  63,    0},
	    {  63,    0}, {  63,   -1}, {  63,   -1},
	    {  63,   -1}, {  63,   -2}, {  63,   -2},
	    {  63,   -3}, {  63,   -3}, {  63,   -3},
	    {  63,   -4}, {  63,   -4}, {  63,   -5},
	    {  63,   -5}, {  63,   -5}, {  63,   -6},
		{  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -8}, {  63,   -8},
	    {  62,   -8}, {  62,   -9}, {  62,   -9},
	    {  62,  -10}, {  62,  -10}, {  62,  -10},
	    {  62,  -11}, {  62,  -11}, {  62,  -12},
	    {  62,  -12}, {  62,  -12}, {  62,  -13},
	    {  62,  -13}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -15}, {  61,  -15},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -17}, {  61,  -17}, {  60,  -17},
	    {  60,  -18}, {  60,  -18}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -19},
	    {  60,  -20}, {  60,  -21}, {  60,  -21},
	    {  59,  -21}, {  59,  -21}, {  59,  -22},
	    {  59,  -22}, {  59,  -23}, {  58,  -23},
	    {  58,  -23}, {  58,  -24}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -25},
	    {  58,  -26}, {  57,  -26}, {  57,  -26},
	    {  57,  -26}, {  57,  -27}, {  56,  -27},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -29}, {  56,  -29}, {  56,  -30},
	    {  55,  -30}, {  55,  -30}, {  55,  -30},
	    {  55,  -31}, {  55,  -31}, {  55,  -32},
	    {  55,  -32}, {  54,  -32}, {  54,  -32},
	    {  54,  -33}, {  53,  -33}, {  53,  -33},
	    {  53,  -34}, {  53,  -34}, {  53,  -35},
	    {  53,  -35}, {  52,  -35}, {  52,  -35},
	    {  52,  -36}, {  51,  -36}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  50,  -38}, {  50,  -38}, {  50,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -40}, {  48,  -40},
	    {  48,  -40}, {  48,  -40}, {  48,  -41},
	    {  48,  -41}, {  47,  -42}, {  47,  -42},
	    {  47,  -42}, {  46,  -42}, {  46,  -43},
	    {  46,  -43}, {  46,  -43}, {  46,  -44},
	    {  45,  -44}, {  45,  -44}, {  44,  -44},
	    {  44,  -45}, {  44,  -45}, {  44,  -46},
	    {  43,  -46}, {  43,  -46}, {  43,  -46},
	    {  42,  -46}, {  42,  -47}, {  42,  -47},
	    {  42,  -47}, {  41,  -48}, {  41,  -48},
	    {  40,  -48}, {  40,  -48}, {  40,  -48},
	    {  40,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -49}, {  39,  -49}, {  39,  -50},
	    {  38,  -50}, {  38,  -50}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  36,  -51}, {  36,  -52}, {  35,  -52},
	    {  35,  -52}, {  35,  -53}, {  35,  -53},
	    {  34,  -53}, {  34,  -53}, {  33,  -53},
	    {  33,  -53}, {  33,  -54}, {  32,  -54},
	    {  32,  -54}, {  32,  -55}, {  32,  -55},
	    {  31,  -55}, {  31,  -55}, {  30,  -55},
	    {  30,  -55}, {  30,  -55}, {  30,  -56},
	    {  29,  -56}, {  29,  -56}, {  28,  -56},
	    {  28,  -56}, {  28,  -56}, {  27,  -56},
	    {  27,  -57}, {  26,  -57}, {  26,  -57},
	    {  26,  -57}, {  26,  -58}, {  25,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  23,  -58}, {  23,  -58},
	    {  23,  -59}, {  22,  -59}, {  22,  -59},
	    {  21,  -59}, {  21,  -59}, {  21,  -60},
	    {  21,  -60}, {  20,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  19,  -60},
	    {  18,  -60}, {  18,  -60}, {  17,  -60},
	    {  17,  -61}, {  17,  -61}, {  16,  -61},
	    {  16,  -61}, {  16,  -61}, {  15,  -61},
	    {  15,  -62}, {  14,  -62}, {  14,  -62},
	    {  14,  -62}, {  13,  -62}, {  13,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  11,  -62}, {  11,  -62}, {  10,  -62},
	    {  10,  -62}, {  10,  -62}, {   9,  -62},
	    {   9,  -62}, {   8,  -62}, {   8,  -63},
	    {   8,  -63}, {   7,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   6,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   4,  -63}, {   4,  -63}, {   3,  -63},
	    {   3,  -63}, {   3,  -63}, {   2,  -63},
	    {   2,  -63}, {   1,  -63}, {   1,  -63},
	    {   1,  -63}, {   0,  -63}, {   0,  -63},
	    {   0,  -63},
	};

#elif (FFT_DATA_NUM == 2048)
	static const t_complex_s8 table_fft_arr[512] = {
		{  64,    0}, {  63,    0}, {  63,    0},
	    {  63,    0}, {  63,    0}, {  63,    0},
	    {  63,    0}, {  63,   -1}, {  63,   -1},
	    {  63,   -1}, {  63,   -1}, {  63,   -1},
	    {  63,   -1}, {  63,   -1}, {  63,   -2},
	    {  63,   -2}, {  63,   -2}, {  63,   -3},
		{  63,   -3}, {  63,   -3}, {  63,   -3},
	    {  63,   -3}, {  63,   -3}, {  63,   -4},
	    {  63,   -4}, {  63,   -4}, {  63,   -4},
	    {  63,   -5}, {  63,   -5}, {  63,   -5},
	    {  63,   -5}, {  63,   -5}, {  63,   -5},
	    {  63,   -6}, {  63,   -6}, {  63,   -6},
	    {  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -8}, {  63,   -8},
	    {  63,   -8}, {  63,   -8}, {  62,   -8},
	    {  62,   -8}, {  62,   -8}, {  62,   -9},
	    {  62,   -9}, {  62,   -9}, {  62,  -10},
	    {  62,  -10}, {  62,  -10}, {  62,  -10},
	    {  62,  -10}, {  62,  -10}, {  62,  -11},
	    {  62,  -11}, {  62,  -11}, {  62,  -11},
	    {  62,  -12}, {  62,  -12}, {  62,  -12},
	    {  62,  -12}, {  62,  -12}, {  62,  -12},
	    {  62,  -13}, {  62,  -13}, {  62,  -13},
	    {  62,  -13}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -15}, {  62,  -15},
	    {  61,  -15}, {  61,  -15}, {  61,  -16},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -17}, {  61,  -17}, {  61,  -17},
	    {  60,  -17}, {  60,  -17}, {  60,  -17},
	    {  60,  -18}, {  60,  -18}, {  60,  -18},
	    {  60,  -18}, {  60,  -19}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -20},
	    {  60,  -20}, {  60,  -20}, {  60,  -21},
	    {  60,  -21}, {  60,  -21}, {  60,  -21},
	    {  59,  -21}, {  59,  -21}, {  59,  -21},
	    {  59,  -22}, {  59,  -22}, {  59,  -22},
	    {  59,  -22}, {  59,  -23}, {  59,  -23},
	    {  58,  -23}, {  58,  -23}, {  58,  -23},
	    {  58,  -23}, {  58,  -23}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -24},
	    {  58,  -25}, {  58,  -25}, {  58,  -25},
	    {  58,  -26}, {  58,  -26}, {  57,  -26},
	    {  57,  -26}, {  57,  -26}, {  57,  -26},
	    {  57,  -26}, {  57,  -27}, {  57,  -27},
	    {  57,  -27}, {  56,  -27}, {  56,  -28},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -29}, {  56,  -29}, {  56,  -29},
	    {  56,  -29}, {  56,  -30}, {  56,  -30},
	    {  55,  -30}, {  55,  -30}, {  55,  -30},
	    {  55,  -30}, {  55,  -30}, {  55,  -31},
	    {  55,  -31}, {  55,  -31}, {  55,  -31},
	    {  55,  -32}, {  55,  -32}, {  55,  -32},
	    {  55,  -32}, {  54,  -32}, {  54,  -32},
	    {  54,  -32}, {  54,  -32}, {  54,  -33},
	    {  54,  -33}, {  53,  -33}, {  53,  -33},
	    {  53,  -33}, {  53,  -33}, {  53,  -33},
	    {  53,  -34}, {  53,  -34}, {  53,  -34},
	    {  53,  -34}, {  53,  -35}, {  53,  -35},
		{  53,  -35}, {  52,  -35}, {  52,  -35},
	    {  52,  -35}, {  52,  -35}, {  52,  -35},
	    {  52,  -36}, {  51,  -36}, {  51,  -36},
	    {  51,  -36}, {  51,  -37}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  50,  -38}, {  50,  -38}, {  50,  -38},
	    {  50,  -38}, {  50,  -39}, {  50,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -40}, {  49,  -40},
	    {  49,  -40}, {  48,  -40}, {  48,  -40},
	    {  48,  -40}, {  48,  -40}, {  48,  -40},
	    {  48,  -41}, {  48,  -41}, {  48,  -41},
	    {  48,  -41}, {  48,  -42}, {  47,  -42},
	    {  47,  -42}, {  47,  -42}, {  47,  -42},
	    {  47,  -42}, {  46,  -42}, {  46,  -42},
	    {  46,  -42}, {  46,  -43}, {  46,  -43},
	    {  46,  -43}, {  46,  -43}, {  46,  -43},
	    {  46,  -44}, {  46,  -44}, {  45,  -44},
	    {  45,  -44}, {  45,  -44}, {  45,  -44},
	    {  44,  -44}, {  44,  -44}, {  44,  -44},
	    {  44,  -45}, {  44,  -45}, {  44,  -45},
	    {  44,  -45}, {  44,  -46}, {  44,  -46},
	    {  43,  -46}, {  43,  -46}, {  43,  -46},
	    {  43,  -46}, {  43,  -46}, {  42,  -46},
	    {  42,  -46}, {  42,  -46}, {  42,  -47},
	    {  42,  -47}, {  42,  -47}, {  42,  -47},
	    {  42,  -47}, {  42,  -48}, {  41,  -48},
	    {  41,  -48}, {  41,  -48}, {  41,  -48},
	    {  40,  -48}, {  40,  -48}, {  40,  -48},
	    {  40,  -48}, {  40,  -48}, {  40,  -49},
	    {  40,  -49}, {  40,  -49}, {  39,  -49},
	    {  39,  -49}, {  39,  -49}, {  39,  -49},
		{  39,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -50}, {  39,  -50}, {  38,  -50},
	    {  38,  -50}, {  38,  -50}, {  38,  -50},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  36,  -51},
	    {  36,  -51}, {  36,  -51}, {  36,  -52},
	    {  35,  -52}, {  35,  -52}, {  35,  -52},
	    {  35,  -52}, {  35,  -52}, {  35,  -53},
	    {  35,  -53}, {  35,  -53}, {  34,  -53},
	    {  34,  -53}, {  34,  -53}, {  34,  -53},
	    {  33,  -53}, {  33,  -53}, {  33,  -53},
	    {  33,  -53}, {  33,  -53}, {  33,  -54},
	    {  33,  -54}, {  32,  -54}, {  32,  -54},
	    {  32,  -54}, {  32,  -54}, {  32,  -55},
	    {  32,  -55}, {  32,  -55}, {  32,  -55},
	    {  31,  -55}, {  31,  -55}, {  31,  -55},
	    {  31,  -55}, {  30,  -55}, {  30,  -55},
	    {  30,  -55}, {  30,  -55}, {  30,  -55},
	    {  30,  -56}, {  30,  -56}, {  29,  -56},
	    {  29,  -56}, {  29,  -56}, {  29,  -56},
	    {  28,  -56}, {  28,  -56}, {  28,  -56},
	    {  28,  -56}, {  28,  -56}, {  28,  -56},
	    {  28,  -56}, {  27,  -56}, {  27,  -57},
	    {  27,  -57}, {  27,  -57}, {  26,  -57},
	    {  26,  -57}, {  26,  -57}, {  26,  -57},
	    {  26,  -57}, {  26,  -58}, {  26,  -58},
	    {  25,  -58}, {  25,  -58}, {  25,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  23,  -58}, {  23,  -58},
	    {  23,  -58}, {  23,  -58}, {  23,  -58},
	    {  23,  -59}, {  23,  -59}, {  22,  -59},
	    {  22,  -59}, {  22,  -59}, {  22,  -59},
	    {  21,  -59}, {  21,  -59}, {  21,  -59},
	    {  21,  -60}, {  21,  -60}, {  21,  -60},
	    {  21,  -60}, {  20,  -60}, {  20,  -60},
	    {  20,  -60}, {  19,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  18,  -60},
	    {  18,  -60}, {  18,  -60}, {  18,  -60},
	    {  17,  -60}, {  17,  -60}, {  17,  -60},
	    {  17,  -61}, {  17,  -61}, {  17,  -61},
	    {  16,  -61}, {  16,  -61}, {  16,  -61},
	    {  16,  -61}, {  16,  -61}, {  16,  -61},
	    {  16,  -61}, {  15,  -61}, {  15,  -61},
	    {  15,  -62}, {  15,  -62}, {  14,  -62},
	    {  14,  -62}, {  14,  -62}, {  14,  -62},
	    {  14,  -62}, {  14,  -62}, {  13,  -62},
	    {  13,  -62}, {  13,  -62}, {  13,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  11,  -62}, {  11,  -62}, {  11,  -62},
	    {  11,  -62}, {  10,  -62}, {  10,  -62},
	    {  10,  -62}, {  10,  -62}, {  10,  -62},
	    {  10,  -62}, {   9,  -62}, {   9,  -62},
	    {   9,  -62}, {   8,  -62}, {   8,  -62},
	    {   8,  -62}, {   8,  -63}, {   8,  -63},
	    {   8,  -63}, {   8,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   7,  -63},
	    {   6,  -63}, {   6,  -63}, {   6,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   4,  -63}, {   4,  -63}, {   4,  -63},
		{   4,  -63}, {   3,  -63}, {   3,  -63},
	    {   3,  -63}, {   3,  -63}, {   3,  -63},
	    {   3,  -63}, {   2,  -63}, {   2,  -63},
	    {   2,  -63}, {   1,  -63}, {   1,  -63},
	    {   1,  -63}, {   1,  -63}, {   1,  -63},
	    {   1,  -63}, {   1,  -63}, {   0,  -63},
	    {   0,  -63}, {   0,  -63}, {   0,  -63},
	    {   0,  -63}, {   0,  -63},
	};



#elif (FFT_DATA_NUM == 4096)
	static const t_complex_s8 table_fft_arr[1024] = {
		{  64,    0}, {  63,    0}, {  63,    0},
	    {  63,    0}, {  63,    0}, {  63,    0},
	    {  63,    0}, {  63,    0}, {  63,    0},
	    {  63,    0}, {  63,    0}, {  63,    0},
		{  63,    0}, {  63,    0}, {  63,   -1},
	    {  63,   -1}, {  63,   -1}, {  63,   -1},
	    {  63,   -1}, {  63,   -1}, {  63,   -1},
	    {  63,   -1}, {  63,   -1}, {  63,   -1},
	    {  63,   -1}, {  63,   -1}, {  63,   -1},
	    {  63,   -2}, {  63,   -2}, {  63,   -2},
	    {  63,   -2}, {  63,   -2}, {  63,   -2},
	    {  63,   -3}, {  63,   -3}, {  63,   -3},
	    {  63,   -3}, {  63,   -3}, {  63,   -3},
	    {  63,   -3}, {  63,   -3}, {  63,   -3},
	    {  63,   -3}, {  63,   -3}, {  63,   -3},
	    {  63,   -3}, {  63,   -4}, {  63,   -4},
	    {  63,   -4}, {  63,   -4}, {  63,   -4},
	    {  63,   -4}, {  63,   -4}, {  63,   -5},
	    {  63,   -5}, {  63,   -5}, {  63,   -5},
	    {  63,   -5}, {  63,   -5}, {  63,   -5},
	    {  63,   -5}, {  63,   -5}, {  63,   -5},
	    {  63,   -5}, {  63,   -5}, {  63,   -5},
	    {  63,   -6}, {  63,   -6}, {  63,   -6},
	    {  63,   -6}, {  63,   -6}, {  63,   -6},
	    {  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -7}, {  63,   -7},
	    {  63,   -7}, {  63,   -8}, {  63,   -8},
	    {  63,   -8}, {  63,   -8}, {  63,   -8},
	    {  63,   -8}, {  63,   -8}, {  63,   -8},
	    {  62,   -8}, {  62,   -8}, {  62,   -8},
	    {  62,   -8}, {  62,   -8}, {  62,   -8},
	    {  62,   -9}, {  62,   -9}, {  62,   -9},
	    {  62,   -9}, {  62,   -9}, {  62,   -9},
	    {  62,  -10}, {  62,  -10}, {  62,  -10},
	    {  62,  -10}, {  62,  -10}, {  62,  -10},
	    {  62,  -10}, {  62,  -10}, {  62,  -10},
	    {  62,  -10}, {  62,  -10}, {  62,  -10},
	    {  62,  -10}, {  62,  -11}, {  62,  -11},
	    {  62,  -11}, {  62,  -11}, {  62,  -11},
	    {  62,  -11}, {  62,  -11}, {  62,  -12},
	    {  62,  -12}, {  62,  -12}, {  62,  -12},
	    {  62,  -12}, {  62,  -12}, {  62,  -12},
	    {  62,  -12}, {  62,  -12}, {  62,  -12},
	    {  62,  -12}, {  62,  -12}, {  62,  -12},
	    {  62,  -13}, {  62,  -13}, {  62,  -13},
	    {  62,  -13}, {  62,  -13}, {  62,  -13},
	    {  62,  -13}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -14}, {  62,  -14},
	    {  62,  -14}, {  62,  -14}, {  62,  -15},
	    {  62,  -15}, {  62,  -15}, {  61,  -15},
	    {  61,  -15}, {  61,  -15}, {  61,  -15},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -16}, {  61,  -16}, {  61,  -16},
	    {  61,  -16}, {  61,  -16}, {  61,  -17},
	    {  61,  -17}, {  61,  -17}, {  61,  -17},
	    {  61,  -17}, {  61,  -17}, {  61,  -17},
	    {  60,  -17}, {  60,  -17}, {  60,  -17},
	    {  60,  -17}, {  60,  -17}, {  60,  -17},
	    {  60,  -18}, {  60,  -18}, {  60,  -18},
	    {  60,  -18}, {  60,  -18}, {  60,  -18},
	    {  60,  -18}, {  60,  -19}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -19},
	    {  60,  -19}, {  60,  -19}, {  60,  -19},
	    {  60,  -20}, {  60,  -20}, {  60,  -20},
	    {  60,  -20}, {  60,  -20}, {  60,  -20},
	    {  60,  -20}, {  60,  -21}, {  60,  -21},
	    {  60,  -21}, {  60,  -21}, {  60,  -21},
	    {  60,  -21}, {  60,  -21}, {  59,  -21},
	    {  59,  -21}, {  59,  -21}, {  59,  -21},
	    {  59,  -21}, {  59,  -21}, {  59,  -21},
	    {  59,  -22}, {  59,  -22}, {  59,  -22},
	    {  59,  -22}, {  59,  -22}, {  59,  -22},
	    {  59,  -22}, {  59,  -23}, {  59,  -23},
	    {  59,  -23}, {  59,  -23}, {  59,  -23},
	    {  58,  -23}, {  58,  -23}, {  58,  -23},
	    {  58,  -23}, {  58,  -23}, {  58,  -23},
	    {  58,  -23}, {  58,  -23}, {  58,  -23},
	    {  58,  -24}, {  58,  -24}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -24},
	    {  58,  -24}, {  58,  -24}, {  58,  -25},
	    {  58,  -25}, {  58,  -25}, {  58,  -25},
	    {  58,  -25}, {  58,  -25}, {  58,  -25},
	    {  58,  -26}, {  58,  -26}, {  58,  -26},
	    {  57,  -26}, {  57,  -26}, {  57,  -26},
	    {  57,  -26}, {  57,  -26}, {  57,  -26},
	    {  57,  -26}, {  57,  -26}, {  57,  -26},
	    {  57,  -26}, {  57,  -26}, {  57,  -27},
	    {  57,  -27}, {  57,  -27}, {  57,  -27},
	    {  57,  -27}, {  56,  -27}, {  56,  -27},
	    {  56,  -27}, {  56,  -28}, {  56,  -28},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -28}, {  56,  -28}, {  56,  -28},
	    {  56,  -29}, {  56,  -29}, {  56,  -29},
	    {  56,  -29}, {  56,  -29}, {  56,  -29},
	    {  56,  -29}, {  56,  -30}, {  56,  -30},
	    {  56,  -30}, {  56,  -30}, {  55,  -30},
	    {  55,  -30}, {  55,  -30}, {  55,  -30},
	    {  55,  -30}, {  55,  -30}, {  55,  -30},
	    {  55,  -30}, {  55,  -30}, {  55,  -30},
	    {  55,  -30}, {  55,  -31}, {  55,  -31},
	    {  55,  -31}, {  55,  -31}, {  55,  -31},
	    {  55,  -31}, {  55,  -31}, {  55,  -31},
	    {  55,  -32}, {  55,  -32}, {  55,  -32},
	    {  55,  -32}, {  55,  -32}, {  55,  -32},
	    {  55,  -32}, {  55,  -32}, {  54,  -32},
	    {  54,  -32}, {  54,  -32}, {  54,  -32},
	    {  54,  -32}, {  54,  -32}, {  54,  -32},
	    {  54,  -33}, {  54,  -33}, {  54,  -33},
	    {  54,  -33}, {  54,  -33}, {  53,  -33},
	    {  53,  -33}, {  53,  -33}, {  53,  -33},
	    {  53,  -33}, {  53,  -33}, {  53,  -33},
	    {  53,  -33}, {  53,  -33}, {  53,  -33},
	    {  53,  -34}, {  53,  -34}, {  53,  -34},
	    {  53,  -34}, {  53,  -34}, {  53,  -34},
	    {  53,  -34}, {  53,  -34}, {  53,  -35},
	    {  53,  -35}, {  53,  -35}, {  53,  -35},
	    {  53,  -35}, {  53,  -35}, {  52,  -35},
	    {  52,  -35}, {  52,  -35}, {  52,  -35},
	    {  52,  -35}, {  52,  -35}, {  52,  -35},
	    {  52,  -35}, {  52,  -35}, {  52,  -35},
	    {  52,  -36}, {  52,  -36}, {  51,  -36},
	    {  51,  -36}, {  51,  -36}, {  51,  -36},
	    {  51,  -36}, {  51,  -36}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  51,  -37}, {  51,  -37}, {  51,  -37},
	    {  50,  -38}, {  50,  -38}, {  50,  -38},
	    {  50,  -38}, {  50,  -38}, {  50,  -38},
	    {  50,  -38}, {  50,  -38}, {  50,  -39},
	    {  50,  -39}, {  50,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -39}, {  49,  -39},
	    {  49,  -39}, {  49,  -40}, {  49,  -40},
	    {  49,  -40}, {  49,  -40}, {  49,  -40},
	    {  49,  -40}, {  49,  -40}, {  48,  -40},
	    {  48,  -40}, {  48,  -40}, {  48,  -40},
	    {  48,  -40}, {  48,  -40}, {  48,  -40},
	    {  48,  -40}, {  48,  -40}, {  48,  -40},
	    {  48,  -41}, {  48,  -41}, {  48,  -41},
	    {  48,  -41}, {  48,  -41}, {  48,  -41},
	    {  48,  -41}, {  48,  -41}, {  48,  -42},
	    {  48,  -42}, {  47,  -42}, {  47,  -42},
	    {  47,  -42}, {  47,  -42}, {  47,  -42},
	    {  47,  -42}, {  47,  -42}, {  47,  -42},
	    {  47,  -42}, {  46,  -42}, {  46,  -42},
	    {  46,  -42}, {  46,  -42}, {  46,  -42},
	    {  46,  -42}, {  46,  -42}, {  46,  -43},
	    {  46,  -43}, {  46,  -43}, {  46,  -43},
	    {  46,  -43}, {  46,  -43}, {  46,  -43},
	    {  46,  -43}, {  46,  -43}, {  46,  -44},
		{  46,  -44}, {  46,  -44}, {  46,  -44},
	    {  45,  -44}, {  45,  -44}, {  45,  -44},
	    {  45,  -44}, {  45,  -44}, {  45,  -44},
	    {  45,  -44}, {  45,  -44}, {  45,  -44},
	    {  44,  -44}, {  44,  -44}, {  44,  -44},
	    {  44,  -44}, {  44,  -44}, {  44,  -45},
	    {  44,  -45}, {  44,  -45}, {  44,  -45},
	    {  44,  -45}, {  44,  -45}, {  44,  -45},
	    {  44,  -45}, {  44,  -45}, {  44,  -46},
	    {  44,  -46}, {  44,  -46}, {  44,  -46},
	    {  43,  -46}, {  43,  -46}, {  43,  -46},
	    {  43,  -46}, {  43,  -46}, {  43,  -46},
	    {  43,  -46}, {  43,  -46}, {  43,  -46},
	    {  42,  -46}, {  42,  -46}, {  42,  -46},
	    {  42,  -46}, {  42,  -46}, {  42,  -46},
	    {  42,  -46}, {  42,  -47}, {  42,  -47},
	    {  42,  -47}, {  42,  -47}, {  42,  -47},
	    {  42,  -47}, {  42,  -47}, {  42,  -47},
	    {  42,  -47}, {  42,  -48}, {  42,  -48},
	    {  41,  -48}, {  41,  -48}, {  41,  -48},
	    {  41,  -48}, {  41,  -48}, {  41,  -48},
	    {  41,  -48}, {  41,  -48}, {  40,  -48},
	    {  40,  -48}, {  40,  -48}, {  40,  -48},
	    {  40,  -48}, {  40,  -48}, {  40,  -48},
	    {  40,  -48}, {  40,  -48}, {  40,  -48},
	    {  40,  -49}, {  40,  -49}, {  40,  -49},
	    {  40,  -49}, {  40,  -49}, {  40,  -49},
	    {  40,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -49}, {  39,  -49}, {  39,  -49},
	    {  39,  -50}, {  39,  -50}, {  39,  -50},
	    {  38,  -50}, {  38,  -50}, {  38,  -50},
	    {  38,  -50}, {  38,  -50}, {  38,  -50},
		{  38,  -50}, {  38,  -50}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  37,  -51}, {  37,  -51}, {  37,  -51},
	    {  36,  -51}, {  36,  -51}, {  36,  -51},
	    {  36,  -51}, {  36,  -51}, {  36,  -51},
	    {  36,  -52}, {  36,  -52}, {  35,  -52},
	    {  35,  -52}, {  35,  -52}, {  35,  -52},
	    {  35,  -52}, {  35,  -52}, {  35,  -52},
	    {  35,  -52}, {  35,  -52}, {  35,  -52},
	    {  35,  -53}, {  35,  -53}, {  35,  -53},
	    {  35,  -53}, {  35,  -53}, {  35,  -53},
	    {  34,  -53}, {  34,  -53}, {  34,  -53},
	    {  34,  -53}, {  34,  -53}, {  34,  -53},
	    {  34,  -53}, {  34,  -53}, {  33,  -53},
	    {  33,  -53}, {  33,  -53}, {  33,  -53},
	    {  33,  -53}, {  33,  -53}, {  33,  -53},
	    {  33,  -53}, {  33,  -53}, {  33,  -53},
	    {  33,  -54}, {  33,  -54}, {  33,  -54},
	    {  33,  -54}, {  33,  -54}, {  32,  -54},
	    {  32,  -54}, {  32,  -54}, {  32,  -54},
		{  32,  -54}, {  32,  -54}, {  32,  -54},
	    {  32,  -55}, {  32,  -55}, {  32,  -55},
	    {  32,  -55}, {  32,  -55}, {  32,  -55},
	    {  32,  -55}, {  32,  -55}, {  31,  -55},
	    {  31,  -55}, {  31,  -55}, {  31,  -55},
	    {  31,  -55}, {  31,  -55}, {  31,  -55},
	    {  31,  -55}, {  30,  -55}, {  30,  -55},
	    {  30,  -55}, {  30,  -55}, {  30,  -55},
	    {  30,  -55}, {  30,  -55}, {  30,  -55},
	    {  30,  -55}, {  30,  -55}, {  30,  -55},
	    {  30,  -56}, {  30,  -56}, {  30,  -56},
	    {  30,  -56}, {  29,  -56}, {  29,  -56},
	    {  29,  -56}, {  29,  -56}, {  29,  -56},
	    {  29,  -56}, {  29,  -56}, {  28,  -56},
	    {  28,  -56}, {  28,  -56}, {  28,  -56},
	    {  28,  -56}, {  28,  -56}, {  28,  -56},
	    {  28,  -56}, {  28,  -56}, {  28,  -56},
	    {  28,  -56}, {  28,  -56}, {  28,  -56},
	    {  28,  -56}, {  27,  -56}, {  27,  -56},
	    {  27,  -56}, {  27,  -57}, {  27,  -57},
		{  27,  -57}, {  27,  -57}, {  27,  -57},
	    {  26,  -57}, {  26,  -57}, {  26,  -57},
	    {  26,  -57}, {  26,  -57}, {  26,  -57},
	    {  26,  -57}, {  26,  -57}, {  26,  -57},
	    {  26,  -57}, {  26,  -57}, {  26,  -58},
	    {  26,  -58}, {  26,  -58}, {  25,  -58},
	    {  25,  -58}, {  25,  -58}, {  25,  -58},
	    {  25,  -58}, {  25,  -58}, {  25,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  24,  -58}, {  24,  -58},
	    {  24,  -58}, {  24,  -58}, {  23,  -58},
	    {  23,  -58}, {  23,  -58}, {  23,  -58},
	    {  23,  -58}, {  23,  -58}, {  23,  -58},
	    {  23,  -58}, {  23,  -58}, {  23,  -59},
	    {  23,  -59}, {  23,  -59}, {  23,  -59},
	    {  23,  -59}, {  22,  -59}, {  22,  -59},
	    {  22,  -59}, {  22,  -59}, {  22,  -59},
	    {  22,  -59}, {  22,  -59}, {  21,  -59},
	    {  21,  -59}, {  21,  -59}, {  21,  -59},
	    {  21,  -59}, {  21,  -59}, {  21,  -59},
	    {  21,  -60}, {  21,  -60}, {  21,  -60},
		{  21,  -60}, {  21,  -60}, {  21,  -60},
	    {  21,  -60}, {  20,  -60}, {  20,  -60},
	    {  20,  -60}, {  20,  -60}, {  20,  -60},
	    {  20,  -60}, {  20,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  19,  -60},
	    {  19,  -60}, {  19,  -60}, {  19,  -60},
	    {  19,  -60}, {  18,  -60}, {  18,  -60},
	    {  18,  -60}, {  18,  -60}, {  18,  -60},
	    {  18,  -60}, {  18,  -60}, {  17,  -60},
	    {  17,  -60}, {  17,  -60}, {  17,  -60},
	    {  17,  -60}, {  17,  -60}, {  17,  -61},
	    {  17,  -61}, {  17,  -61}, {  17,  -61},
	    {  17,  -61}, {  17,  -61}, {  17,  -61},
	    {  16,  -61}, {  16,  -61}, {  16,  -61},
	    {  16,  -61}, {  16,  -61}, {  16,  -61},
	    {  16,  -61}, {  16,  -61}, {  16,  -61},
	    {  16,  -61}, {  16,  -61}, {  16,  -61},
	    {  16,  -61}, {  16,  -61}, {  15,  -61},
		{  15,  -61}, {  15,  -61}, {  15,  -61},
	    {  15,  -62}, {  15,  -62}, {  15,  -62},
	    {  14,  -62}, {  14,  -62}, {  14,  -62},
	    {  14,  -62}, {  14,  -62}, {  14,  -62},
	    {  14,  -62}, {  14,  -62}, {  14,  -62},
	    {  14,  -62}, {  14,  -62}, {  14,  -62},
	    {  14,  -62}, {  13,  -62}, {  13,  -62},
	    {  13,  -62}, {  13,  -62}, {  13,  -62},
	    {  13,  -62}, {  13,  -62}, {  12,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  12,  -62}, {  12,  -62}, {  12,  -62},
	    {  11,  -62}, {  11,  -62}, {  11,  -62},
	    {  11,  -62}, {  11,  -62}, {  11,  -62},
	    {  11,  -62}, {  10,  -62}, {  10,  -62},
	    {  10,  -62}, {  10,  -62}, {  10,  -62},
	    {  10,  -62}, {  10,  -62}, {  10,  -62},
	    {  10,  -62}, {  10,  -62}, {  10,  -62},
	    {  10,  -62}, {  10,  -62}, {   9,  -62},
	    {   9,  -62}, {   9,  -62}, {   9,  -62},
	    {   9,  -62}, {   9,  -62}, {   8,  -62},
	    {   8,  -62}, {   8,  -62}, {   8,  -62},
		{   8,  -62}, {   8,  -62}, {   8,  -63},
	    {   8,  -63}, {   8,  -63}, {   8,  -63},
	    {   8,  -63}, {   8,  -63}, {   8,  -63},
	    {   8,  -63}, {   7,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   7,  -63},
	    {   7,  -63}, {   7,  -63}, {   6,  -63},
	    {   6,  -63}, {   6,  -63}, {   6,  -63},
	    {   6,  -63}, {   6,  -63}, {   5,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   5,  -63}, {   5,  -63}, {   5,  -63},
	    {   4,  -63}, {   4,  -63}, {   4,  -63},
	    {   4,  -63}, {   4,  -63}, {   4,  -63},
	    {   4,  -63}, {   3,  -63}, {   3,  -63},
	    {   3,  -63}, {   3,  -63}, {   3,  -63},
	    {   3,  -63}, {   3,  -63}, {   3,  -63},
		{   3,  -63}, {   3,  -63}, {   3,  -63},
	    {   3,  -63}, {   3,  -63}, {   2,  -63},
	    {   2,  -63}, {   2,  -63}, {   2,  -63},
	    {   2,  -63}, {   2,  -63}, {   1,  -63},
	    {   1,  -63}, {   1,  -63}, {   1,  -63},
	    {   1,  -63}, {   1,  -63}, {   1,  -63},
	    {   1,  -63}, {   1,  -63}, {   1,  -63},
	    {   1,  -63}, {   1,  -63}, {   1,  -63},
	    {   0,  -63}, {   0,  -63}, {   0,  -63},
	    {   0,  -63}, {   0,  -63}, {   0,  -63},
	    {   0,  -63}, {   0,  -63}, {   0,  -63},
	    {   0,  -63}, {   0,  -63}, {   0,  -63},
	    {   0,  -63},
	};

#endif

#endif /* FFT_TABLE_H_ */
