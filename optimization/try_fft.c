#include "try_fft.h"


int main(void)
{
	
	u16 adc_vals[MEAS_NUM] = { 0 };

	if ( read_arr_file(adc_vals, MEAS_NUM, "spi.txt") == NULL )
		exit_code(E_ERR_FILE_READ, "ERROR: file read");
	
	show_array(adc_vals, MEAS_NUM);

	return 0;
}


void exit_code(e_errors ex_code, const char* pmsg_to_usr)
{
	printf("%s\n", pmsg_to_usr);
	exit(ex_code);
}


void show_array(u16* parr, u16 arr_size)
{
	for (u16 i = 0; i < arr_size; i++)
		printf("%hu\n", parr[i]);
}


u16* read_arr_file(u16* parr, u16 arr_size, char* pfile_name)
{
	FILE* f = fopen(pfile_name, "r");

	if (f == NULL)
		exit_code(E_ERR_FILE_OPEN, "ERROR: file open");

	for (u16 i = 0; i < arr_size; i++)
		if (fscanf(f, "%hu", &parr[i]) == EOF)
			return NULL;

	if ( fclose(f) )
		exit_code(E_ERR_FILE_CLOSE, "ERROR: file close");

	return parr;
}
