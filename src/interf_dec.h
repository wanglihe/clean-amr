/*
 * ===================================================================
 *  TS 26.104
 *  REL-5 V5.4.0 2004-03
 *  REL-6 V6.1.0 2004-03
 *  3GPP AMR Floating-point Speech Codec
 * ===================================================================
 *
 */

/*
 * interf_dec.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Defines interface to AMR decoder
 *
 */

#ifndef _interf_dec_h_
#define _interf_dec_h_

#include "sp_dec.h"

/*
 * definition of constants
 */
#define EHF_MASK 0x0008 /* encoder homing frame pattern */
typedef struct {
   int reset_flag_old;   /* previous was homing frame */
   enum RXFrameType prev_ft;   /* previous frame type */
   enum Mode prev_mode;   /* previous mode */
   Speech_Decode_FrameState decoder_State;   /* Points decoder state */
}dec_interface_State;

/*
 * Function prototypes
 */
/*
 * Conversion from packed bitstream to endoded parameters
 * Decoding parameters to speech
 */
void Decoder_Interface_Decode(dec_interface_State* state, unsigned char *bits, short *synth, int bfi);

/*
 * Reserve and init. memory
 */
void Decoder_Interface_init(dec_interface_State* state);

#endif

