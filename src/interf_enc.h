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
 * interf_enc.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Defines interface to AMR encoder
 *
 */

#ifndef _interf_enc_h_
#define _interf_enc_h_

/*
 * include files
 */
#include"sp_enc.h"

/*
 * Declare structure types
 */
/* Declaration transmitted frame types */
enum TXFrameType { TX_SPEECH_GOOD = 0,
                   TX_SID_FIRST,
                   TX_SID_UPDATE,
                   TX_NO_DATA,
                   TX_SPEECH_DEGRADED,
                   TX_SPEECH_BAD,
                   TX_SID_BAD,
                   TX_ONSET,
                   TX_N_FRAMETYPES     /* number of frame types */
};

/* Declaration of interface structure */
typedef struct
{
   Word16 sid_update_counter;   /* Number of frames since last SID */
   Word16 sid_handover_debt;   /* Number of extra SID_UPD frames to schedule */
   Word32 dtx;
   enum TXFrameType prev_ft;   /* Type of the previous frame */
   Speech_Encode_FrameState encoderState;   /* Encoder state structure */
} enc_interface_State;

/*
 * Function prototypes
 */
/*
 * Encodes one frame of speech
 * Returns packed octets
 */
int Encoder_Interface_Encode(enc_interface_State* state, enum Mode mode, short *speech,

      unsigned char *serial,  /* max size 31 bytes */

      int forceSpeech );   /* use speech mode */

/*
 * Reserve and init. memory
 */
void Encoder_Interface_init(enc_interface_State* state, int dtx);

#endif
