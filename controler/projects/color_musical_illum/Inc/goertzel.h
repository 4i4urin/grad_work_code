/*
 * goertzel.h
 *
 *  Created on: 5 may 2024 г.
 *      Author: shishel
 */

#ifndef GOERTZEL_H
#define GOERTZEL_H


u8* goertzel_arr(
    const u8* pin_vect, const u16 in_vect_len,
    const u16* freq_index, const u8 freq_index_len, u8* res);



#endif /* GOERTZEL_H */
