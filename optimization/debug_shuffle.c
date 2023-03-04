#include <stdio.h>
#include <stdint.h>

#define SWAP(A, B) A ^= B; B ^= A; A ^= B;
#define MEAS_POW2   6
#define MEAS_NUM 	1 << MEAS_POW2
#define REVERS_SHIFT 16 - MEAS_POW2

void show_array(uint16_t* parr, uint16_t arr_size);
uint16_t reverse(uint16_t bytem, uint8_t shift);

int main(void)
{
	uint16_t  arr[MEAS_NUM] = { 0 };
	for (int i = 0; i < MEAS_NUM; i++)
		arr[i] = i;

	show_array(arr, MEAS_NUM);
	putchar('\n');

	uint16_t rev_arr[MEAS_NUM] = { 0 };
	for (int i = 0; i < MEAS_NUM; i++)
		rev_arr[i] = reverse(i, REVERS_SHIFT);

	show_array(rev_arr, MEAS_NUM);
	return 0;
}

uint16_t reverse(uint16_t byte, uint8_t shift)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ((byte >> 8) | (byte << 8)) >> shift;
}



void show_array(uint16_t* parr, uint16_t arr_size)
{
	for (uint16_t i = 0; i < arr_size; i++)
		printf("%d\n", parr[i]);
}
