/*
 *===================================================================
 *  3GPP AMR Wideband Floating-point Speech Codec
 *===================================================================
 */
#ifndef ENC_H
#define ENC_H

#include "typedef.h"

Word16 E_MAIN_init(Coder_State* st);
void E_MAIN_reset(Coder_State* cod_state, Word16 reset_all);
Word16 E_MAIN_encode(Word16 * mode, Word16 input_sp[], Word16 prms[],
                     Coder_State* st, Word16 allow_dtx);
#endif

