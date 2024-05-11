#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include "common/common.c"
#include "hash/qx.c"

void usage() {
    printf("qxcrypt v0.0.1 - by KryptoMagick\n\n");
    printf("Algorithms:\n***********\nqx         256 bit\n\n");
    printf("Usage:\nqxcrypt -e <input file> <output file>\n");
    printf("qxcrypt -d <input file> <output file>\n");
}

int main(int argc, char *argv[]) {
    int kdf_iters = 100000;

    char *encrypt_symbol = "-e";
    char *decrypt_symbol = "-d";

    if (argc != 4) {
        usage();
        return 0;
    }

    FILE *infile, *outfile;
    char *infile_name, *outfile_name;
    char *mode = argv[1];
    infile_name = argv[2];
    outfile_name = argv[3];
    if (access(infile_name, F_OK) == -1 ) {
        printf("%s not found\n", infile_name);
        exit(1);
    }
    infile = fopen(infile_name, "rb");
    fseek(infile, 0, SEEK_END);
    long fsize = ftell(infile);
    fclose(infile);
    struct termios tp, save;
    tcgetattr(STDIN_FILENO, &tp);
    save = tp;
    tp.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp);

    unsigned char * passphrase[256];
    printf("Enter secret key passphrase: ");
    scanf("%s", passphrase);
    tcsetattr(STDIN_FILENO, TCSANOW, &save);
    uint8_t key[32];
    qx_kdf(passphrase, strlen((char*)passphrase), key, kdf_iters);

    if (strcmp(mode, encrypt_symbol) == 0) {
        qx_crypt(infile_name, outfile_name, key);
    }
    else if (strcmp(mode, decrypt_symbol) == 0) {
        qx_crypt(infile_name, outfile_name, key);
    }
    printf("\n");
    return 0;
}

