#ifndef _AMRNB_ROM_H_
#define _AMRNB_ROM_H_

/*
 * definition of modes for codec
 */
enum Mode { MR475 = 0,
            MR515,
            MR59,
            MR67,
            MR74,
            MR795,
            MR102,
            MR122,
            MRDTX,
            N_MODES     /* number of (SPC) modes */
};

#define M               10    /* Order of LP filter */
#define MP1             (M+1) /* Order of LP filter + 1 */
#define L_WINDOW        240   /* Window size in LP analysis */
#define L_NEXT          40    /* Overhead in LP analysis */
#define LTPG_MEM_SIZE   5     /* number of stored past LTP coding gains + 1 */
#define N_FRAME         7     /* old pitch gains in average calculation */
#define DTX_HIST_SIZE   8     /* DTX history size */
#define L_TOTAL         320   /* Total size of speech buffer. */
#define L_FRAME         160   /* Frame size */
#define L_FRAME_BY2     80    /* Frame size divided by 2 */
#define L_SUBFR         40    /* Subframe size */
#define L_CODE          40    /* codevector length */
#define PIT_MAX         143   /* Maximum pitch lag */
#define PIT_MIN         20    /* Minimum pitch lag */
#define PIT_MIN_MR122   18    /* Minimum pitch lag (MR122 mode) */
#define L_INTERPOL      (10+1)/* Length of filter for interpolation */
#define NPRED           4     /* number of prediction taps */
#define SHARPMIN        0     /* Minimum value of pitch sharpening */
#define MAX_PRM_SIZE    57    /* max. num. of params */
#define L_INTER_SRCH    4     /* Length of filter for CL LTP search interpolation */
#define GP_CLIP         0.95F /* Pitch gain clipping */
#define UP_SAMP_MAX     6
#define NB_TRACK        5     /* number of tracks */
#define NB_TRACK_MR102  4     /* number of tracks mode mr102 */
#define STEP            5     /* codebook step size */
#define STEP_MR102      4     /* codebook step size mode mr102 */
#define NC              M/2   /* Order of LP filter divided by 2 */

/* vad */
#define COMPLEN               9        /* Number of sub-bands used by VAD */
#define L_ENERGYHIST          60
#define L_CBGAINHIST          7
#define MIN_ENERGY            -14336   /* 14 Q10 */
#define MIN_ENERGY_MR122      -2381    /* 14 / (20*log10(2)) Q10 */
#define PN_INITIAL_SEED       0x70816958L /* Pseudo noise generator seed value  */
#define MIN_16                (Word16)-32768
#define MAX_16                (Word16)0x7fff
#define MAX_32                (Word32)0x7fffffffL
#define EXPCONST              5243     /* 0.16 in Q15 */
#define DTX_MAX_EMPTY_THRESH  50
#define DTX_ELAPSED_FRAMES_THRESH (24 + 7 -1)
#define LSF_GAP               205      /* Minimum distance between LSF after quantization; 50 Hz = 205 */
#define LSP_PRED_FAC_MR122    21299    /* MR122 LSP prediction factor (0.65 Q15) */
#define POS_CODE              8191
#define NEG_CODE              8191
#define NMAX                  9        /* largest N used in median calculation */
#define MEAN_ENER_MR122       783741L  /* 36/(20*log10(2)) (Q17) */
#define SHARPMAX              13017    /* Maximum value of pitch sharpening */
#define FRAMEENERGYLIMIT      17578    /* 150 */
#define LOWERNOISELIMIT       20       /*  5 */
#define UPPERNOISELIMIT       1953     /* 50 */
#define AZ_SIZE               (4*M+4)  /* Size of array of LP filters in 4 subfr.s */
#define AGC_FAC               29491    /* Factor for automatic gain control 0.9 */
#define PHDGAINMEMSIZE        5
#define PHDTHR1LTP            9830     /* 0.6 in Q14 */
#define PHDTHR2LTP            14746    /* 0.9 in Q14 */
#define ONFACTPLUS1           16384    /* 2.0 in Q13 */
#define ONLENGTH              2
#define DTX_HANG_CONST        7        /* yields eight frames of SP HANGOVER */

#endif
