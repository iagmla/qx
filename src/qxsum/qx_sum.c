#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "qx.c"

int main(int argc, char *argv[]) {
    char *infile_name = argv[1];
    if (access(infile_name, F_OK) == -1 ) {
        printf("%s: No such file or directory\n", infile_name);
        exit(1);
    }
    uint8_t digest[32];
    qx_hash_file(infile_name, digest);
    for (int i = 0; i < 32; i++) {
        printf("%02X", digest[i]);
    }
    printf("    %s\n", infile_name);
}
