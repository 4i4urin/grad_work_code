#include "try_fft.h"

#include "fft_table.h"

int main(void)
{
	
	t_complex adc_vals[MEAS_NUM] = { 0 };
	t_complex scratch[MEAS_NUM]  = { 0 };
	s32 abs_arr[MEAS_NUM / 2] = { 0 };

	if ( read_arr_file(adc_vals, MEAS_NUM, "music.txt") == NULL )
		exit_code(E_ERR_FILE_READ, "ERROR: file read");

	//show_array(adc_vals, MEAS_NUM);
	//shuffle_arr_fft(adc_vals, MEAS_NUM);
    fft( adc_vals, MEAS_NUM, scratch );

    for (u16 i = 0; i < MEAS_NUM / 2; i++)
    	abs_arr[i] = ABS(adc_vals[i].re, adc_vals[i].im);

    // show_array(abs_arr, MEAS_NUM);
    out_array_file(abs_arr, MEAS_NUM / 2, "res_fft_c.txt");

	return 0;
}

void fft( t_complex *v, int n, t_complex *tmp )
{
    if(n <= 1) 			/* otherwise, do nothing and return */
        return;

    int k, m;
    t_complex z, *vo, *ve;
    t_complex_s8 const *pw;

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
    	pw = fft_table(n, m, MEAS_NUM);
    	if (pw == NULL)
    		exit_code(E_ERR_FFT_DIM, "ERROR: FFT DIMENTION");

        z.re = ((s16)pw->re * vo[m].re - (s16)pw->im * vo[m].im) / 100;	/* re(w*vo[m]) */
        z.im = ((s16)pw->re * vo[m].im + (s16)pw->im * vo[m].re) / 100;	/* im(w*vo[m]) */

        v[m].re         = ve[m].re + z.re;
        v[m].im         = ve[m].im + z.im;

        v[m + n / 2].re = ve[m].re - z.re;
        v[m + n / 2].im = ve[m].im - z.im;
        /* DEBUG */
        // if (   v[m].re >= 500000  || v[m + n / 2].re >= 500000
        // 	|| v[m].re <= -500000 || v[m + n / 2].re <= -500000)
        // {
        // 	printf("v[m] = {%d, %d}\nv[m+n/2] = {%d, %d}\nn = %d\nm = %d\n",
        // 			v[m].re, v[m].im, v[m + n / 2].re, v[m + n / 2].im, n, m);
        // 	printf("W.re = %d\nW.im = %d\n\n", w.re, w.im);
        // 	printf("z.re = %d\nz.im = %d\n\n", z.re, z.im);
 		// }       	
    }
}


void shuffle_arr_fft(t_complex* tmp, u16 arr_size)
{
	u8 shift = 0; // 16 bit in uint16_t
	for (shift; (shift < 16) && ((arr_size - 1) >> shift); shift++) {};

		// 16 bit in uint16_t
	shift = 16 - shift;

	t_complex swap = {0, 0};
	for (u16 i = 0; i < arr_size / 2; i++)
	{
		if (i == reverse(i) >> shift)
			continue;

		swap = tmp[i];
		tmp[i] = tmp[reverse(i) >> shift];
		tmp[reverse(i) >> shift] = swap;
	}
}


/* Print a vector of complexes as ordered pairs. */
static void print_vector( const char *title, t_complex *x, int n)
{
    int i;
    printf("%s (dim = %d):\n", title, n);

    for(i = 0; i < n; i++ ) 
        printf(" %5d,\t%5d\n", x[i].re, x[i].im);

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


t_complex* read_arr_file(t_complex* parr, u16 arr_size, char* pfile_name)
{
	FILE* f = fopen(pfile_name, "r");

	if (f == NULL)
		exit_code(E_ERR_FILE_OPEN, "ERROR: file open");

	for (u16 i = 0; i < arr_size; i++)
	{
		parr[i].im = 0;
		if (fscanf(f, "%hd", &parr[i].re) == EOF)
			return NULL;
		parr[i].re >>= 4;
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
