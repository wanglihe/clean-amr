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
 * interf_dec.c
 *
 *
 * Project:
 *     AMR Floating-Point Codec
 *
 * Contains:
 *    This module provides means to conversion from 3GPP bitstream to AMR
 *    parameters
 */

/*
 * include files
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "typedef.h"
#include "interf_dec.h"
#include "interf_rom.h"

/*
 * DecoderMMS
 *
 *
 * Parameters:
 *    param             O: AMR parameters
 *    stream            I: input bitstream
 *    frame_type        O: frame type
 *    speech_mode       O: speech mode in DTX
 *
 * Function:
 *    AMR file storage format frame to decoder parameters
 *
 * Returns:
 *    mode              used mode
 */
enum Mode DecoderMMS( Word16 *param, UWord8 *stream, enum RXFrameType
                      *frame_type, enum Mode *speech_mode, Word16 *q_bit )
{
   enum Mode mode;
   Word32 j;
   Word16 *mask;


   memset( param, 0, PRMNO_MR122 <<1 );
   *q_bit = 0x01 & (*stream >> 2);
   mode = 0x0F & (*stream >> 3);
   stream++;

   if ( mode == MRDTX ) {
      mask = order_MRDTX;

      for ( j = 1; j < 36; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }

      /* get SID type bit */

      *frame_type = RX_SID_FIRST;
      if (*stream & 0x80)
         *frame_type = RX_SID_UPDATE;

      /* since there is update, use it */
      /* *frame_type = RX_SID_UPDATE; */

      /* speech mode indicator */
	  *speech_mode = (*stream >> 4) & 0x07;
	  *speech_mode = ((*speech_mode & 0x0001) << 2) | (*speech_mode & 0x0002) | ((*speech_mode & 0x0004) >> 2);

   }
   else if ( mode == 15 ) {
      *frame_type = RX_NO_DATA;
   }
   else if ( mode == MR475 ) {
      mask = order_MR475;

      for ( j = 1; j < 96; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR515 ) {
      mask = order_MR515;

      for ( j = 1; j < 104; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR59 ) {
      mask = order_MR59;

      for ( j = 1; j < 119; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR67 ) {
      mask = order_MR67;

      for ( j = 1; j < 135; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR74 ) {
      mask = order_MR74;

      for ( j = 1; j < 149; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR795 ) {
      mask = order_MR795;

      for ( j = 1; j < 160; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR102 ) {
      mask = order_MR102;

      for ( j = 1; j < 205; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR122 ) {
      mask = order_MR122;

      for ( j = 1; j < 245; j++ ) {
         if ( *stream & 0x80 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream <<= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else
      *frame_type = RX_SPEECH_BAD;
   return mode;
}

/*
 * Decoder_Interface_reset
 *
 *
 * Parameters:
 *    st                O: state struct
 *
 * Function:
 *    Reset homing frame counter
 *
 * Returns:
 *    void
 */
void Decoder_Interface_reset( dec_interface_State *st )
{
   st->reset_flag_old = 1;
   st->prev_ft = RX_SPEECH_GOOD;
   st->prev_mode = MR475;   /* minimum bitrate */
}


/*
 * Decoder_Interface_init
 *
 *
 * Parameters:
 *    void
 *
 * Function:
 *    Allocates state memory and initializes state memory
 *
 * Returns:
 *    success           : pointer to structure
 *    failure           : NULL
 */
void Decoder_Interface_init(dec_interface_State* state)
{
   Speech_Decode_Frame_init(&state->decoder_State);
   Decoder_Interface_reset(state);
}

/*
 * Decoder_Interface_Decode
 *
 *
 * Parameters:
 *    st                B: state structure
 *    bits              I: bit stream
 *    synth             O: synthesized speech
 *    bfi               I: bad frame indicator
 *
 * Function:
 *    Decode bit stream to synthesized speech
 *
 * Returns:
 *    Void
 */
void Decoder_Interface_Decode(dec_interface_State* state, UWord8 *bits, Word16 *synth, int bfi) {
   enum Mode mode;   /* AMR mode */

   enum Mode speech_mode = MR475;   /* speech mode */

   Word16 prm[PRMNO_MR122];   /* AMR parameters */

   enum RXFrameType frame_type;   /* frame type */

   const Word16 *homing;   /* pointer to homing frame */
   Word16 homingSize;   /* frame size for homing frame */
   Word32 i;   /* counter */
   Word32 resetFlag = 1;   /* homing frame */

   Word16 q_bit;

   /*
    * extract mode information and frametype,
    * octets to parameters
    */
   mode = DecoderMMS( prm, bits, &frame_type, &speech_mode, &q_bit );
   if (!bfi)	bfi = 1 - q_bit;

   if ( bfi == 1 ) {
      if ( mode <= MR122 ) {
         frame_type = RX_SPEECH_BAD;
      }
      else if ( frame_type != RX_NO_DATA ) {
         frame_type = RX_SID_BAD;
         mode = state->prev_mode;
      }
   } else {
       if ( frame_type == RX_SID_FIRST || frame_type == RX_SID_UPDATE) {
           mode = speech_mode;
       }
       else if ( frame_type == RX_NO_DATA ) {
           mode = state->prev_mode;
       }
       /*
        * if no mode information
        * guess one from the previous frame
        */
       if ( frame_type == RX_SPEECH_BAD ) {
          mode = state->prev_mode;
          if ( state->prev_ft >= RX_SID_FIRST ) {
             frame_type = RX_SID_BAD;
          }
       }
   }

   /* test for homing frame */
   if ( state->reset_flag_old == 1 ) {
      switch ( mode ) {
         case MR122:
            homing = dhf_MR122;
            homingSize = 18;
            break;

         case MR102:
            homing = dhf_MR102;
            homingSize = 12;
            break;

         case MR795:
            homing = dhf_MR795;
            homingSize = 8;
            break;

         case MR74:
            homing = dhf_MR74;
            homingSize = 7;
            break;

         case MR67:
            homing = dhf_MR67;
            homingSize = 7;
            break;

         case MR59:
            homing = dhf_MR59;
            homingSize = 7;
            break;

         case MR515:
            homing = dhf_MR515;
            homingSize = 7;
            break;

         case MR475:
            homing = dhf_MR475;
            homingSize = 7;
            break;

         default:
            homing = NULL;
            homingSize = 0;
            break;
      }

      for ( i = 0; i < homingSize; i++ ) {
         resetFlag = prm[i] ^ homing[i];

         if ( resetFlag )
            break;
      }
   }

   if ( ( resetFlag == 0 ) && ( state->reset_flag_old != 0 ) ) {
      for ( i = 0; i < 160; i++ ) {
         synth[i] = EHF_MASK;
      }
   }
   else
      Speech_Decode_Frame(&state->decoder_State, mode, prm, frame_type, synth );

   if ( state->reset_flag_old == 0 ) {
      /* check whole frame */
      switch ( mode ) {
         case MR122:
            homing = dhf_MR122;
            homingSize = PRMNO_MR122;
            break;

         case MR102:
            homing = dhf_MR102;
            homingSize = PRMNO_MR102;
            break;

         case MR795:
            homing = dhf_MR795;
            homingSize = PRMNO_MR795;
            break;

         case MR74:
            homing = dhf_MR74;
            homingSize = PRMNO_MR74;
            break;

         case MR67:
            homing = dhf_MR67;
            homingSize = PRMNO_MR67;
            break;

         case MR59:
            homing = dhf_MR59;
            homingSize = PRMNO_MR59;
            break;

         case MR515:
            homing = dhf_MR515;
            homingSize = PRMNO_MR515;
            break;

         case MR475:
            homing = dhf_MR475;
            homingSize = PRMNO_MR475;
            break;

         default:
            homing = NULL;
            homingSize = 0;
      }

      for ( i = 0; i < homingSize; i++ ) {
         resetFlag = prm[i] ^ homing[i];

         if ( resetFlag )
            break;
      }
   }

   /* reset decoder if current frame is a homing frame */
   if ( resetFlag == 0 ) {
      Speech_Decode_Frame_reset(&state->decoder_State );
   }
   state->reset_flag_old = !resetFlag;
   state->prev_ft = frame_type;
   state->prev_mode = mode;
}
