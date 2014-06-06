#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <typedef.h>
#include <enc_if.h>
#include <dec_if.h>


#define AMR_MAGIC_NUMBER "#!AMR-WB\n"
#define BUF_SIZE (2*1024*1024)

extern const UWord8 block_size[];
static const int TIMES = 10;
static const int SAMPLES_PER_FRAME = 320;

double timediff(const struct timespec* start, const struct timespec* end) {
    static const double nano = 1000000000.0;
    double s = ((double)start->tv_sec) * nano + (double)start->tv_nsec;
    double e = ((double)end->tv_sec) * nano + (double)end->tv_nsec;
    return (e-s)/nano;
}

int main(int argc, const char* argv[]) {
    int i,j;
    int dtx = 0;
    unsigned char* buf_amr = malloc(BUF_SIZE);
    unsigned char* buf_pcm = malloc(BUF_SIZE);

    FILE* amrnb = fopen("standard_amrwb.awb", "r");
    if (NULL == amrnb) exit(1);
    char magic[sizeof(AMR_MAGIC_NUMBER)];
    fread(magic, sizeof(char), strlen(AMR_MAGIC_NUMBER), amrnb);
    int buf_amr_size = fread(buf_amr, sizeof(char), BUF_SIZE, amrnb);
    int amr_frame_size = block_size[(buf_amr[0] >> 3) & 0x0F];
    int frame_count = buf_amr_size / amr_frame_size;
    int buf_pcm_size = frame_count*SAMPLES_PER_FRAME*sizeof(Word16);
    /*printf("buf_amr_size: %d,  amr_frame_size: %d, frame_count: %d, buf_pcm_size: %d\n", buf_amr_size,  amr_frame_size, frame_count, buf_pcm_size);*/
    fclose(amrnb);

    struct timespec time_start,time_end;
    double time;

    clock_gettime(CLOCK_REALTIME, &time_start);
    for (i=0; i < TIMES; i++) {
        unsigned char* frame = &buf_amr[0];
        Word16* speech = (Word16*)&buf_pcm[0];
        void* destate = D_IF_init();
        while ((frame - &buf_amr[0]) < buf_amr_size) {
            /*printf("frame: %ld speech: %ld\n", (frame - &buf_amr[0]), (speech - (Word16*)&buf_pcm[0]));*/
            D_IF_decode(destate, frame, speech, 0);
            frame += block_size[(frame[0] >> 3) & 0x000F];
            speech += SAMPLES_PER_FRAME;
        }
        D_IF_exit(destate);
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    time = timediff(&time_start, &time_end);
    /*printf("time: %lf\n", time);*/
    printf("%s decode: %lf frames per 20ms\n", argv[0], frame_count*TIMES/time/50);

    clock_gettime(CLOCK_REALTIME, &time_start);
    for (i = 0; i < TIMES; i++) {
        int req_mode = 7;
        unsigned char* frame = &buf_amr[0];
        Word16* speech = (Word16*)&buf_pcm[0];
        int dtx = 0;
        void* enstate = E_IF_init();
        while ((speech - (Word16*)&buf_pcm[0]) < buf_pcm_size) {
            /*printf("frame: %ld speech: %ld\n", (frame - &buf_amr[0]), (speech - (Word16*)&buf_pcm[0]));*/
            int byte_counter = E_IF_encode(enstate, req_mode, speech, frame, 0);
            speech += SAMPLES_PER_FRAME;
            /*frame += block_size[req_mode];*/
            frame += byte_counter;
            /*frame += 61;*/
        }
        E_IF_exit(enstate);
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    time = timediff(&time_start, &time_end);
    printf("%s encode: %lf frames per 20ms\n", argv[0], frame_count*TIMES/time/50);

    free(buf_amr);
    free(buf_pcm);
    return 0;
}


