/*
 *===================================================================
 *  3GPP AMR Wideband Floating-point Speech Codec
 *===================================================================
 */
#ifndef DEC_IF_H
#define DEC_IF_H

#include "typedef.h"
#include "dec_main.h"

#define NB_SERIAL_MAX   61    /* max serial size      */
#define L_FRAME16k      320   /* Frame size at 16kHz  */

#define _good_frame  0
#define _bad_frame   1
#define _lost_frame  2
#define _no_frame    3

typedef struct
{
   Word16 reset_flag_old;     /* previous was homing frame  */
   Word16 prev_ft;            /* previous frame type        */
   Word16 prev_mode;          /* previous mode              */
   Decoder_State decoder_state;       /* Points decoder state       */
} WB_dec_if_state;

void D_IF_decode(WB_dec_if_state* s, UWord8 *bits, Word16 *synth, Word32 bfi);
void D_IF_init(WB_dec_if_state* state);

#endif
