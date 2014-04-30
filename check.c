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
    int *enstate = Encoder_Interface_init(dtx);
    Encoder_Interface_exit(enstate);
    return 0;
}
