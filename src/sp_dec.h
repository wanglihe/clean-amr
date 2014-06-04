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
 * sp_enc.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Defines interface to AMR encoder
 *
 */
#ifndef _SP_DEC_H_
#define _SP_DEC_H_

#include "typedef.h"
#include "amrnb_rom.h"

/*
 * definition of enumerated types
 */

/* Declaration recieved frame types */
enum RXFrameType { RX_SPEECH_GOOD = 0,
                   RX_SPEECH_DEGRADED,
                   RX_ONSET,
                   RX_SPEECH_BAD,
                   RX_SID_FIRST,
                   RX_SID_UPDATE,
                   RX_SID_BAD,
                   RX_NO_DATA,
                   RX_N_FRAMETYPES     /* number of frame types */
};

/*
 * Declare structure types
 */
enum DTXStateType
{
   SPEECH = 0, DTX, DTX_MUTE
};

/*
 * Decoder memory structure
 */
typedef struct
{
   /* history vector of past synthesis speech energy */
   Word32 frameEnergyHist[L_ENERGYHIST];


   /* state flags */
   Word16 bgHangover;   /* counter; number of frames after last speech frame */


}Bgn_scdState;
typedef struct
{
   Word32 hangCount;   /* counter; */
   /* history vector of past synthesis speech energy */
   Word32 cbGainHistory[L_CBGAINHIST];
   Word16 hangVar;   /* counter; */

}Cb_gain_averageState;
typedef struct
{
   Word32 lsp_meanSave[M];   /* Averaged LSPs saved for efficiency  */


}lsp_avgState;
typedef struct
{
   Word32 past_r_q[M];   /* Past quantized prediction error, Q15 */
   Word32 past_lsf_q[M];   /* Past dequantized lsfs, Q15 */


}D_plsfState;
typedef struct
{
   Word32 pbuf[5];
   Word32 past_gain_pit;
   Word32 prev_gp;


}ec_gain_pitchState;
typedef struct
{
   Word32 gbuf[5];
   Word32 past_gain_code;
   Word32 prev_gc;


}ec_gain_codeState;
typedef struct
{
   /*
    * normal MA predictor memory, Q10
    * (contains 20*log10(quaErr))
    */
   Word32 past_qua_en[4];


   /*
    * MA predictor memory for MR122 mode, Q10
    * (contains log2(quaErr))
    */
   Word32 past_qua_en_MR122[4];


}dec_gc_predState;
typedef struct
{
   Word32 gainMem[PHDGAINMEMSIZE];
   Word32 prevCbGain;
   Word32 prevState;
   Word16 lockFull;
   Word16 onset;


}ph_dispState;
typedef struct
{
   enum DTXStateType dtxGlobalState;   /* contains previous state */

   Word32 log_en;
   Word32 old_log_en;
   Word32 pn_seed_rx;
   Word32 lsp[M];
   Word32 lsp_old[M];
   Word32 lsf_hist[M * DTX_HIST_SIZE];
   Word32 lsf_hist_mean[M * DTX_HIST_SIZE];
   Word32 log_en_hist[DTX_HIST_SIZE];
   Word32 true_sid_period_inv;
   Word16 since_last_sid;
   Word16 lsf_hist_ptr;
   Word16 log_pg_mean;
   Word16 log_en_hist_ptr;
   Word16 log_en_adjust;
   Word16 dtxHangoverCount;
   Word16 decAnaElapsedCount;
   Word16 sid_frame;
   Word16 valid_data;
   Word16 dtxHangoverAdded;


   /* updated in main decoder */
   Word16 data_updated;   /* marker to know if CNI data is ever renewed */


}dtx_decState;
typedef struct
{
   Word32 past_gain;


}agcState;
typedef struct
{
   /* Excitation vector */
   Word32 old_exc[L_SUBFR + PIT_MAX + L_INTERPOL];
   UWord16 exc;
   Word32 lsp_old[M];


   /* Filter's memory */
   Word32 mem_syn[M];


   /* pitch sharpening */
   Word32 sharp;
   Word32 old_T0;


   /* Variable holding received ltpLag, used in background noise and BFI */
   Word32 T0_lagBuff;


   /* Variables for the source characteristic detector (SCD) */
   Word32 inBackgroundNoise;
   Word32 voicedHangover;
   Word32 ltpGainHistory[9];


   /* Memories for bad frame handling */
   Word32 excEnergyHist[9];
   Word16 prev_bf;
   Word16 prev_pdf;
   Word16 state;
   Word16 nodataSeed;


   Bgn_scdState background_state;
   Cb_gain_averageState Cb_gain_averState;
   lsp_avgState lsp_avg_st;
   D_plsfState lsfState;
   ec_gain_pitchState ec_gain_p_st;
   ec_gain_codeState ec_gain_c_st;
   dec_gc_predState pred_state;
   ph_dispState ph_disp_st;
   dtx_decState dtxDecoderState;
}Decoder_amrState;
typedef struct
{
   Word32 res2[L_SUBFR];
   Word32 mem_syn_pst[M];
   Word32 synth_buf[M + L_FRAME];
   Word32 preemph_state_mem_pre;
   agcState agc_state;
}Post_FilterState;
typedef struct
{
   Word32 y2_hi;
   Word32 y2_lo;
   Word32 y1_hi;
   Word32 y1_lo;
   Word32 x0;
   Word32 x1;


}Post_ProcessState;
typedef struct
{
   Decoder_amrState decoder_amrState;
   Post_FilterState post_state;
   Post_ProcessState postHP_state;
}Speech_Decode_FrameState;

/*
 * Function prototypes
 */

/*
 * initialize one instance of the speech decoder
 */
void Speech_Decode_Frame_init(Speech_Decode_FrameState* state);

/*
 * Decodes one frame from encoded parameters
 */
void Speech_Decode_Frame(Speech_Decode_FrameState* state, enum Mode mode, short *serial,
                   enum RXFrameType frame_type, short *synth);

/*
 * reset speech decoder
 */
int Speech_Decode_Frame_reset(Speech_Decode_FrameState* state);

#endif

