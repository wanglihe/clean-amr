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
#ifndef _SP_ENC_H
#define _SP_ENC_H

/*
 * include files
 */

#include "typedef.h"
#include "amrnb_rom.h"

/*
 * Definition of structures used in encoding process
 */
typedef struct
{
   Float32 y2;
   Float32 y1;
   Float32 x0;
   Float32 x1;

}Pre_ProcessState;

#ifdef VAD2

/* Defines for VAD2 */
#define	FRM_LEN1		80
#define	DELAY0			24
#define	FFT_LEN1		128

#define	UPDATE_CNT_THLD1	50

#define	INIT_FRAMES		4

#define	CNE_SM_FAC1		0.1
#define	CEE_SM_FAC1		0.55

#define	HYSTER_CNT_THLD1	6	/* forced update constants... */
#define	HIGH_ALPHA1		0.9
#define	LOW_ALPHA1		0.7
#define	ALPHA_RANGE1		(HIGH_ALPHA1-LOW_ALPHA1)

#define NORM_ENRG		(4.0)	/* account for div by 2 by the HPF */
#define	MIN_CHAN_ENRG		(0.0625 / NORM_ENRG)
#define	INE			(16.0 / NORM_ENRG)
#define	NOISE_FLOOR		(1.0 / NORM_ENRG)

#define	PRE_EMP_FAC1		(-0.8)

#define	NUM_CHAN		16
#define	LO_CHAN			0
#define	HI_CHAN			15
#define	UPDATE_THLD		35

#define	SINE_START_CHAN		2
#define	P2A_THRESH		10.0
#define	DEV_THLD1		28.0

/* Defines for the FFT function */
#define	SIZE			128
#define	SIZE_BY_TWO		64
#define	NUM_STAGE		6

#define	PI			3.141592653589793

#define	TRUE			1
#define	FALSE			0

/* Macros */
#define	min(a,b)		((a)<(b)?(a):(b))
#define	max(a,b)		((a)>(b)?(a):(b))
#define	square(a)		((a)*(a))

/* structures */
typedef struct
{
  Float32 pre_emp_mem;
  Word16  update_cnt;
  Word16  hyster_cnt;
  Word16  last_update_cnt;
  Float32 ch_enrg_long_db[NUM_CHAN];
  Word32  Lframe_cnt;
  Float32 ch_enrg[NUM_CHAN];
  Float32 ch_noise[NUM_CHAN];
  Float32 tsnr;
  Word16  hangover;
  Word16  burstcount;
  Word16  fupdate_flag;
  Float32 negSNRvar;
  Float32 negSNRbias;
  Float32 R0;
  Float32 Rmax;
  Word16  LTP_flag;
}vadState;
#else
typedef struct
{
   Float32 bckr_est[COMPLEN];   /* background noise estimate */
   Float32 ave_level[COMPLEN];


   /* averaged input components for stationary estimation */
   Float32 old_level[COMPLEN];   /* input levels of the previous frame */
   Float32 sub_level[COMPLEN];


   /* input levels calculated at the end of a frame (lookahead) */
   Float32 a_data5[3][2];   /* memory for the filter bank */
   Float32 a_data3[5];   /* memory for the filter bank */
   Float32 best_corr_hp;   /* FIP filtered value */


   /* counts length of a speech burst incl HO addition */
   Float32 corr_hp_fast;   /* filtered value */
   Word32 vadreg;   /* flags for intermediate VAD decisions */
   Word32 pitch;   /* flags for pitch detection */
   Word32 oldlag_count, oldlag;   /* variables for pitch detection */
   Word32 complex_high;   /* flags for complex detection */
   Word32 complex_low;   /* flags for complex detection */
   Word32 complex_warning;   /* complex background warning */
   Word32 tone;   /* flags for tone detection */
   Word16 burst_count;   /* counts length of a speech burst */
   Word16 hang_count;   /* hangover counter */
   Word16 stat_count;   /* stationary counter */
   Word16 complex_hang_count;   /* complex hangover counter, used by VAD */
   Word16 complex_hang_timer;   /* hangover initiator, used by CAD */
   Word16 speech_vad_decision;   /* final decision */
   Word16 sp_burst_count;


}vadState;
#endif
#define DTX_HIST_SIZE 8
#define DTX_ELAPSED_FRAMES_THRESH (24 + 7 -1)
#define DTX_HANG_CONST 7   /* yields eight frames of SP HANGOVER */
typedef struct
{
   Float32 lsp_hist[M * DTX_HIST_SIZE];
   Float32 log_en_hist[DTX_HIST_SIZE];
   Word32 init_lsf_vq_index;
   Word16 hist_ptr;
   Word16 log_en_index;
   Word16 lsp_index[3];


   /* DTX handler stuff */
   Word16 dtxHangoverCount;
   Word16 decAnaElapsedCount;


}dtx_encState;
typedef struct
{
   /* gain history */
   Float32 gp[N_FRAME];


   /* counters */
   Word16 count;


}tonStabState;
typedef struct
{
   Word32 past_qua_en[4];


   /* normal MA predictor memory, (contains 20*log10(qua_err)) */
}enc_gc_predState;

typedef struct
{
   Float32 prev_alpha;   /* previous adaptor output, */
   Float32 prev_gc;   /* previous code gain, */
   Float32 ltpg_mem[LTPG_MEM_SIZE];   /* LTP coding gain history, */
   Word16 onset;   /* onset state, */


   /* (ltpg_mem[0] not used for history) */
}gain_adaptState;
typedef struct
{

   Float32 sf0_target_en;
   Float32 sf0_coeff[5];
   Word32 sf0_gcode0_exp;
   Word32 sf0_gcode0_fra;
   Word16 *gain_idx_ptr;


   enc_gc_predState gc_predSt;
   enc_gc_predState gc_predUncSt;
   gain_adaptState adaptSt;
}gainQuantState;
typedef struct
{
   Word32 T0_prev_subframe;   /* integer pitch lag of previous sub-frame */


}Pitch_frState;
typedef struct
{
   Pitch_frState pitchSt;
}clLtpState;
typedef struct
{
   Float32 ada_w;
   Word32 old_T0_med;
   Word16 wght_flg;


}pitchOLWghtState;
typedef struct
{
   Float32 past_rq[M];   /* Past quantized prediction error */


}Q_plsfState;
typedef struct
{
   /* Past LSPs */
   Float32 lsp_old[M];
   Float32 lsp_old_q[M];


   /* Quantization state */
   Q_plsfState qSt;
}lspState;
typedef struct
{
   Float32 old_A[M + 1];   /* Last A(z) for case of unstable filter */


}LevinsonState;
typedef struct
{
   LevinsonState LevinsonSt;
}lpcState;
typedef struct
{
   /* Speech vector */
   Float32 old_speech[L_TOTAL];
   Float32 *p_window, *p_window_12k2;
   UWord16 speech;
   UWord16 new_speech;   /* Global variable */


   /* Weight speech vector */
   Float32 old_wsp[L_FRAME + PIT_MAX];
   UWord16 wsp;


   /* OL LTP states */
   Word32 old_lags[5];
   Float32 ol_gain_flg[2];


   /* Excitation vector */
   Float32 old_exc[L_FRAME + PIT_MAX + L_INTERPOL];
   UWord16 exc;


   /* Zero vector */
   Float32 ai_zero[L_SUBFR + MP1];
   UWord16 zero;


   /* Impulse response vector */
   UWord16 h1;
   Float32 hvec[L_SUBFR * 2];


   /* Substates */
   lpcState lpcSt;
   lspState lspSt;
   clLtpState clLtpSt;
   gainQuantState gainQuantSt;
   pitchOLWghtState pitchOLWghtSt;
   tonStabState tonStabSt;
   vadState vadSt;

   Word32 dtx;


   dtx_encState dtxEncSt;

   /* Filter's memory */
   Float32 mem_syn[M], mem_w0[M], mem_w[M];
   Float32 mem_err[M + L_SUBFR];
   UWord16 error;
   Float32 sharp;
}cod_amrState;
typedef struct
{
   cod_amrState cod_amr_state;
   Pre_ProcessState pre_state;
   Word32 dtx;
}Speech_Encode_FrameState;

/*
 * Function prototypes
 */

/*
 * initialize one instance of the speech encoder
 * Stores pointer to filter status struct in *st. This pointer has to
 * be passed to Speech_Encode_Frame in each call.
 * returns 0 on success
 */
void Speech_Encode_Frame_init (Speech_Encode_FrameState* state, int dtx);
/*
 * reset speech encoder (i.e. set state memory to zero)
 * returns 0 on success
 */
int Speech_Encode_Frame_reset(Speech_Encode_FrameState *state, int dtx);

/*
 * Encodes one speech frame
 * Returns analysis parameters
 */
void Speech_Encode_Frame(Speech_Encode_FrameState *state, enum Mode mode, short *newSpeech,
                   short *prm, enum Mode *usedMode);

#endif
