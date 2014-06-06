#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <typedef.h>
#include <enc_if.h>
#include <dec_if.h>

#define AMR_MAGIC_NUMBER "#!AMR-WB\n"
#define BUF_SIZE (2*1024*1024)


static const int TIMES = 10;
static const int SAMPLES_PER_FRAME = 320;

extern const UWord8 block_size[];

double timediff(const struct timespec* start, const struct timespec* end) {
    static const double nano = 1000000000.0;
    double s = ((double)start->tv_sec) * nano + (double)start->tv_nsec;
    double e = ((double)end->tv_sec) * nano + (double)end->tv_nsec;
    return (e-s)/nano;
}


int main(int argc, const char* argv[]) {
    FILE* amrwb = fopen("standard_amrwb.awb", "r");
    if (NULL == amrwb) exit(1);
    //unsigned char buf_amr[BUF_SIZE];
    //unsigned char buf_pcm[BUF_SIZE];
    unsigned char* buf_amr = malloc(BUF_SIZE);
    unsigned char* buf_pcm = malloc(BUF_SIZE);
    char magic[sizeof(AMR_MAGIC_NUMBER)];
    fread(magic, sizeof(char), strlen(AMR_MAGIC_NUMBER), amrwb);
    int buf_amr_size = fread(buf_amr, sizeof(char), BUF_SIZE, amrwb);
    int amr_frame_size = block_size[(buf_amr[0] >> 3) & 0x0F];
    int frame_count = buf_amr_size / amr_frame_size;
    int buf_pcm_size = frame_count*SAMPLES_PER_FRAME*sizeof(int16_t);
    fclose(amrwb);

    struct timespec time_start,time_end;
    double time;

    clock_gettime(CLOCK_REALTIME, &time_start);
    for (int i=0; i < TIMES; i++) {
        unsigned char* frame = &buf_amr[0];
        int16_t* speech = (int16_t*)&buf_pcm[0];
        WB_dec_if_state destate;
        D_IF_init(&destate);
        while ((frame - &buf_amr[0]) < buf_amr_size) {
            D_IF_decode(&destate, frame, speech, 0);
            frame += block_size[frame[0]>> 3 & 0x0F];
            speech += SAMPLES_PER_FRAME;
        }
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    time = timediff(&time_start, &time_end);
    //printf("time: %lf\n", time);
    printf("%s decode: %lf frames per 20ms\n", argv[0], frame_count*TIMES/time/50);

    clock_gettime(CLOCK_REALTIME, &time_start);
    for (int i = 0; i < TIMES; i++) {
        int req_mode = 7;
        unsigned char* frame = &buf_amr[0];
        int16_t* speech = (int16_t*)&buf_pcm[0];
        int dtx = 0;
        WB_enc_if_state enstate;
        E_IF_init(&enstate);
        while ((speech - (int16_t*)&buf_pcm[0]) < buf_pcm_size) {
            int byte_counter = E_IF_encode(&enstate, req_mode, speech, frame, dtx);
            speech += SAMPLES_PER_FRAME;
            frame += block_size[req_mode];
        }
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    time = timediff(&time_start, &time_end);
    printf("%s encode: %lf frames per 20ms\n", argv[0], frame_count*TIMES/time/50);
    free(buf_amr);
    free(buf_pcm);
    return 0;
}
