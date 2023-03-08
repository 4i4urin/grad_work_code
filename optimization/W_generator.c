#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define MEAS_POW2    12
#define MEAS_NUM     (1 << MEAS_POW2) // Number of ADC measurements
#define PI 3.1415926535897932384626433832795
#define IS_FULL      0

int main() {
    uint16_t in_print = 0;
    uint16_t base  = 1 << (MEAS_POW2 - 1);
    printf("static const t_complex_s8 table_fft_arr[%d] = {\n\t", 
                    (IS_FULL) ? MEAS_NUM >> 1 : MEAS_NUM >> 2);
    for (uint16_t group_size = 0; group_size < base; group_size++)
    {
        int8_t A = cos(PI * group_size / base) * 100;
        int8_t B = -sin(PI * group_size / base) * 100;
        int16_t A_16 = A << 6;
        int16_t B_16 = B << 6;
        A = A_16 / 100;
        B = B_16 / 100;
        if (base == MEAS_NUM >> 1)
        {
            if (IS_FULL == 1)
                printf("{%4d, %4d}, ", A, B);
            else if (group_size < MEAS_NUM >> 2)
                printf("{%4d, %4d}, ", A, B);
            else 
                break;
            in_print += 1;
        }
        if (in_print % 3 == 0)
            printf("\n    ");
    }
    printf("\n};\n");
    printf("\n\narr size = %d\n", in_print);
    return 0;
}
