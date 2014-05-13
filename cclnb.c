#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typedef.h>
#include <interf_enc.h>
#include <interf_dec.h>

static const char* pass = "pass";
static const char* fail = "fail";

#define AMR_MAGIC_NUMBER "#!AMR\n"

static const char* name[] = {"Word8", "UWord8", "Word16", "Word32", "Float32",
    "Float64"};

static const unsigned long size[][2] = {
    {sizeof(Word8), 1},
    {sizeof(UWord8), 1},
    {sizeof(Word16), 2},
    {sizeof(Word32), 4},
    {sizeof(Float32), 4},
    {sizeof(Float64), 8}
};

static short block_size[16]={ 12, 13, 15, 17, 19, 20, 26, 31, 5, 0, 0, 0, 0, 0, 0, 0 };

int main() {
    int i,j;
    for (i = 0; i < 6; i++) {
        const char* result = (size[i][0] == size[i][1] ? pass:fail);
        printf("%s size: %lu, %s\n", name[i], size[i][0], result);
        if (result == fail) {
            exit(1);
        }
    }
    int dtx = 0;
    enc_interface_State enstate;
    Encoder_Interface_init(&enstate, dtx);
    dec_interface_State destate;
    Decoder_Interface_init(&destate);

    FILE* pcm_orig = fopen("cclnb.orig", "wb");
    FILE* amrnb = fopen("cclnb.amrnb", "wb");
    FILE* pcm_back = fopen("cclnb.back", "wb");
    if (NULL == pcm_orig) exit(1);
    if (NULL == amrnb) exit(1);
    if (NULL == pcm_back) exit(1);
    fwrite(AMR_MAGIC_NUMBER, sizeof(char), strlen(AMR_MAGIC_NUMBER), amrnb);
    srand(0);
    for (i=0; i < 10240; i++) {
        int req_mode = 7;
        short speech[160];
        for (j = 0; j < 160; j++) {
           speech[j] = (short) rand();
        }
        fwrite(speech, sizeof(short int), 160, pcm_orig);
        unsigned char serial_data[32];
        int byte_counter = Encoder_Interface_Encode(&enstate, req_mode, speech, serial_data, 0);
        fwrite(serial_data, sizeof(char), byte_counter, amrnb);
        /*printf("test times: %d, bytes: %d\n", i, byte_counter);*/
        enum Mode dec_mode = (serial_data[0] >> 3) & 0x000F;
        int read_size = block_size[dec_mode];
        Decoder_Interface_Decode(&destate, serial_data, speech, 0);
        fwrite(speech, sizeof(short int), 160, pcm_back);
        /*printf("test times: %d, bytes: %d\n", i, read_size);*/
    }
    fclose(pcm_orig);
    fclose(amrnb);
    fclose(pcm_back);
    return 0;
}
