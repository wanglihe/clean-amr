#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <typedef.h>
#include <interf_enc.h>
#include <interf_dec.h>


#define AMR_MAGIC_NUMBER "#!AMR\n"
#define BUF_SIZE (2*1024*1024)

static short block_size[16]={ 12, 13, 15, 17, 19, 20, 26, 31, 5, 0, 0, 0, 0, 0, 0, 0 };
static const int TIMES = 1;
static const int SAMPLES_PER_FRAME = 160;

double timediff(const struct timespec* start, const struct timespec* end) {
    static const double nano = 1000000000.0;
    double s = ((double)start->tv_sec) * nano + (double)start->tv_nsec;
    double e = ((double)end->tv_sec) * nano + (double)end->tv_nsec;
    return (e-s)/nano;
}

int main(int argc, const char* argv[]) {
    int i,j;
    int dtx = 0;
    void* enstate = Encoder_Interface_init(dtx);
    void* destate = Decoder_Interface_init();
    unsigned char* buf_amr = malloc(BUF_SIZE);
    unsigned char* buf_pcm = malloc(BUF_SIZE);

    FILE* amrnb = fopen("standard_amrnb.amr", "r");
    if (NULL == amrnb) exit(1);
    char magic[sizeof(AMR_MAGIC_NUMBER)];
    fread(magic, sizeof(char), strlen(AMR_MAGIC_NUMBER), amrnb);
    int buf_amr_size = fread(buf_amr, sizeof(char), BUF_SIZE, amrnb);
    int amr_frame_size = block_size[(buf_amr[0] >> 3) & 0x0F]+1;
    int frame_count = buf_amr_size / amr_frame_size;
    int buf_pcm_size = frame_count*SAMPLES_PER_FRAME*sizeof(Word16);
    printf("buf_amr_size: %d,  amr_frame_size: %d, frame_count: %d, buf_pcm_size: %d\n", buf_amr_size,  amr_frame_size, frame_count, buf_pcm_size);

    struct timespec time_start,time_end;
    double time;

    clock_gettime(CLOCK_REALTIME, &time_start);
    for (i=0; i < TIMES; i++) {
        unsigned char* frame = &buf_amr[0];
        Word16* speech = (Word16*)&buf_pcm[0];
        while ((frame - &buf_amr[0]) < buf_amr_size) {
            //printf("frame: %ld speech: %ld\n", (frame - &buf_amr[0]), (speech - (Word16*)&buf_pcm[0]));
            Decoder_Interface_Decode(destate, frame, speech, 0);
            frame += block_size[(frame[0] >> 3) & 0x000F]+1;
            speech += SAMPLES_PER_FRAME;
        }
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    time = timediff(&time_start, &time_end);
    //printf("time: %lf\n", time);
    printf("%s decode: %lf frames per 20ms\n", argv[0], frame_count*TIMES/time/50);

    clock_gettime(CLOCK_REALTIME, &time_start);
    for (i = 0; i < TIMES; i++) {
        int req_mode = 7;
        unsigned char* frame = &buf_amr[0];
        Word16* speech = (Word16*)&buf_pcm[0];
        int dtx = 0;
        while ((speech - (Word16*)&buf_pcm[0]) < buf_pcm_size) {
            //printf("frame: %ld speech: %ld\n", (frame - &buf_amr[0]), (speech - (Word16*)&buf_pcm[0]));
            int byte_counter = Encoder_Interface_Encode(enstate, req_mode, speech, frame, 0);
            speech += SAMPLES_PER_FRAME;
            //frame += block_size[req_mode];
            frame += byte_counter;
            //frame += 32;
        }
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    time = timediff(&time_start, &time_end);
    printf("%s encode: %lf frames per 20ms\n", argv[0], frame_count*TIMES/time/50);

    Encoder_Interface_exit(enstate);
    Decoder_Interface_exit(destate);
    free(buf_amr);
    free(buf_pcm);
    fclose(amrnb);
    return 0;
}

