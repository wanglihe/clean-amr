#include <stdio.h>
#include <stdlib.h>
#include <typedef.h>
#include <interf_enc.h>

static const char* pass = "pass";
static const char* fail = "fail";

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

int main() {
    for (int i = 0; i < 5; i++) {
        const char* result = (size[i][0] == size[i][1] ? pass:fail);
        printf("%s size: %lu, %s\n", name[i], size[i][0], result);
        if (result == fail) {
            exit(1);
        }
    }
    int dtx = 0;
    void* enstate = Encoder_Interface_init(dtx);
    srand(0);
    for (int i=0; i < 1024; i++) {
        int req_mode = 7;
        short speech[160];
        for (int j = 0; j < 160; j++) {
           speech[j] = (short) rand();
        }
        unsigned char serial_data[32];
        int byte_counter = Encoder_Interface_Encode(enstate, req_mode, speech, serial_data, 0);
        printf("test times: %d, bytes: %d\n", i, byte_counter);
    }
    Encoder_Interface_exit(enstate);
    return 0;
}
