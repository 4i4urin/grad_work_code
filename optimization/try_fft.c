#include "try_fft.h"

#include "fft_table.h"

int main(void)
{
	
	complex adc_vals[MEAS_NUM] = { 0 };
	complex scratch[MEAS_NUM]  = { 0 };
	s32 abs_arr[MEAS_NUM] = { 0 };

	if ( read_arr_file(adc_vals, MEAS_NUM, "spi.txt") == NULL )
		exit_code(E_ERR_FILE_READ, "ERROR: file read");

	//show_array(adc_vals, MEAS_NUM);
	//print_vector("Orig", adc_vals, MEAS_NUM);
    fft( adc_vals, MEAS_NUM, scratch );
    //print_vector(" FFT", adc_vals, MEAS_NUM);
    for (u16 i = 0; i < MEAS_NUM; i++)
    	abs_arr[i] = abs_2(adc_vals[i].Re, adc_vals[i].Im);

    // show_array(abs_arr, MEAS_NUM);
    out_array_file(abs_arr, MEAS_NUM, "res_fft_c.txt");

	return 0;
}

s32 abs_2(s32 x, s32 y)
{
	return sqrt(pow(y, 2) + pow(x, 2));
}

void fft( complex *v, int n, complex *tmp )
{
    if(n <= 1) 			/* otherwise, do nothing and return */
        return;

    int k, m;
    complex z, w, *vo, *ve;

    ve = tmp; vo = tmp + n / 2;

    for(k = 0; k < n / 2; k++) 
    {
        ve[k] = v[2 * k];
        vo[k] = v[2 * k + 1];
    }
    fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
    for(m = 0; m < n / 2; m++) 
    {
    	w = fft_table(n, m, MEAS_NUM);
    	if (w.Im == 0 && w.Re == 0)
    		exit_code(E_ERR_FFT_DIM, "ERROR: FFT DIMENTION");

        z.Re = (w.Re * vo[m].Re - w.Im * vo[m].Im) / 1000;	/* Re(w*vo[m]) */
        z.Im = (w.Re * vo[m].Im + w.Im * vo[m].Re) / 1000;	/* Im(w*vo[m]) */
        v[m].Re         = ve[m].Re + z.Re;
        v[m].Im         = ve[m].Im + z.Im;
        v[m + n / 2].Re = ve[m].Re - z.Re;
        v[m + n / 2].Im = ve[m].Im - z.Im;
        /* DEBUG
        if (   v[m].Re >= 500000  || v[m + n / 2].Re >= 500000
        	|| v[m].Re <= -500000 || v[m + n / 2].Re <= -500000)
        	printf("v[m] = {%d, %d}\nv[m+n/2] = {%d, %d}\nn = %d\nm = %d\n",
        			v[m].Re, v[m].Im, v[m + n / 2].Re, v[m + n / 2].Im, n, m);
        */
    }
}

/* Print a vector of complexes as ordered pairs. */
static void print_vector( const char *title, complex *x, int n)
{
    int i;
    printf("%s (dim = %d):\n", title, n);

    for(i = 0; i < n; i++ ) 
        printf(" %5d,\t%5d\n", x[i].Re, x[i].Im);

    putchar('\n');
    return;
}


u16 reverse(u16 byte)
{
	byte = ( ((byte & 0xaaaa) >> 1) | ((byte & 0x5555) << 1) );
	byte = ( ((byte & 0xcccc) >> 2) | ((byte & 0x3333) << 2) );
	byte = ( ((byte & 0xf0f0) >> 4) | ((byte & 0x0f0f) << 4) );
	return ((byte >> 8) | (byte << 8));
}


void exit_code(e_errors ex_code, const char* pmsg_to_usr)
{
	printf("%s\n", pmsg_to_usr);
	exit(ex_code);
}


void show_array(s32* parr, u16 arr_size)
{
	for (u16 i = 0; i < arr_size; i++)
		printf("%d\n", parr[i]);
}


complex* read_arr_file(complex* parr, u16 arr_size, char* pfile_name)
{
	FILE* f = fopen(pfile_name, "r");

	if (f == NULL)
		exit_code(E_ERR_FILE_OPEN, "ERROR: file open");

	for (u16 i = 0; i < arr_size; i++)
	{
		parr[i].Im = 0;
		if (fscanf(f, "%d", &parr[i].Re) == EOF)
			return NULL;
	}

	if ( fclose(f) )
		exit_code(E_ERR_FILE_CLOSE, "ERROR: file close");

	return parr;
}

void out_array_file(s32* parr, u16 arr_size, const char* pfile_name)
{
	FILE* f = fopen(pfile_name, "w");

	if (f == NULL)
		exit_code(E_ERR_FILE_OPEN, "ERROR: file open");

	for (u16 i = 0; i < arr_size; i++)
		fprintf(f, "%d\n", parr[i]);

	if ( fclose(f) )
		exit_code(E_ERR_FILE_CLOSE, "ERROR: file close");
}
