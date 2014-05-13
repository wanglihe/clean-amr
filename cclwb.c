#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typedef.h>
#include <enc_if.h>
#include <dec_if.h>

static const char* pass = "pass";
static const char* fail = "fail";

#define AMR_MAGIC_NUMBER "#!AMR-WB\n"

static const char* name[] = {"Word8", "UWord8", "Word16", "UWrod16", "Word32", "Float32",
    "Float64"};

static const unsigned long size[][2] = {
    {sizeof(Word8), 1},
    {sizeof(UWord8), 1},
    {sizeof(Word16), 2},
    {sizeof(UWord16), 2},
    {sizeof(Word32), 4},
    {sizeof(Float32), 4},
    {sizeof(Float64), 8}
};

extern const UWord8 block_size[];

int main() {
    int i,j;
    for (i = 0; i < 7; i++) {
        const char* result = (size[i][0] == size[i][1] ? pass:fail);
        printf("%s size: %lu, %s\n", name[i], size[i][0], result);
        if (result == fail) {
            exit(1);
        }
    }
    int dtx = 0;
    WB_enc_if_state enstate;
    E_IF_init(&enstate);
    void* destate = D_IF_init();

    FILE* pcm_orig = fopen("cclwb.orig", "wb");
    FILE* amrwb = fopen("cclwb.amrwb", "wb");
    FILE* pcm_back = fopen("cclwb.back", "wb");
    if (NULL == pcm_orig) exit(1);
    if (NULL == amrwb) exit(1);
    if (NULL == pcm_back) exit(1);
    fwrite(AMR_MAGIC_NUMBER, sizeof(char), strlen(AMR_MAGIC_NUMBER), amrwb);
    srand(0);
    for (i=0; i < 10240; i++) {
        int req_mode = 8;
        short speech[320];
        for (j = 0; j < 320; j++) {
           speech[j] = (short) rand();
        }
        fwrite(speech, sizeof(short int), 320, pcm_orig);
        unsigned char serial_data[61];
        int byte_counter = E_IF_encode(&enstate, req_mode, speech, serial_data, dtx);
        fwrite(serial_data, sizeof(char), byte_counter, amrwb);
        /*printf("test times: %d, bytes: %d\n", i, byte_counter);*/
        Word16 dec_mode = (serial_data[0] >> 3) & 0x0F;
        int read_size = block_size[dec_mode];
        D_IF_decode(destate, serial_data, speech, 0);
        fwrite(speech, sizeof(short int), 320, pcm_back);
        /*printf("test times: %d, bytes: %d\n", i, read_size);*/
    }
    D_IF_exit(destate);
    fclose(pcm_orig);
    fclose(amrwb);
    fclose(pcm_back);
    return 0;
}
