#include <stdio.h>
#include <stdint.h>

#define SWAP(A, B) A ^= B; B ^= A; A ^= B;

uint16_t* shuffle_arr_fft(uint16_t* tmp, uint16_t arr_size);
void show_array(uint16_t* parr, uint16_t arr_size);
uint16_t reverse(uint16_t byte);

int main(void)
{
	uint16_t  arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
					  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
					  20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
					  30, 31 };
	show_array(arr, 32);
	uint16_t* pshufl_arr = shuffle_arr_fft(arr, 32);
	putchar('\n');
	show_array(pshufl_arr, 32);
	return 0;
}

uint16_t reverse(uint16_t byte)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ((byte >> 8) | (byte << 8));
}

uint16_t* shuffle_arr_fft(uint16_t* tmp, uint16_t arr_size)
{
	int shift = 0; // 16 bit in uint16_t
	for (shift; (shift < 16) && ((arr_size - 1) >> shift); shift++) {};

		// 16 bit in uint16_t
	shift = 16 - shift;

	for (uint16_t i = 0; i < arr_size / 2; i++)
	{
		if (i == reverse(i) >> shift)
			continue;
		SWAP(tmp[i], tmp[reverse(i) >> shift]);
	}

	return tmp;
}


void show_array(uint16_t* parr, uint16_t arr_size)
{
	for (uint16_t i = 0; i < arr_size; i++)
		printf("%d\n", parr[i]);
}
