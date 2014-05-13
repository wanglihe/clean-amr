/*
 *===================================================================
 *  3GPP AMR Wideband Floating-point Speech Codec
 *===================================================================
 */
#ifndef WB_E_IF_H
#define WB_E_IF_H

#include "typedef.h"
#include "enc_main.h"

#define L_FRAME16k   320   /* Frame size at 16kHz  */
#define NB_SERIAL_MAX 61   /* max serial size      */

typedef struct
{
   Word16 sid_update_counter;   /* Number of frames since last SID */
   Word16 sid_handover_debt;    /* Number of extra SID_UPD frames to schedule */
   Word16 prev_ft;              /* Type of the previous frame */
   Coder_State encoder_state;   /* Points encoder state structure */
} WB_enc_if_state;

int E_IF_encode(WB_enc_if_state *s, Word16 mode, Word16 *speech,
                UWord8 *serial, Word16 dtx);
void E_IF_init(WB_enc_if_state* state);

#endif
