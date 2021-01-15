
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* fileName ="output.hex";
unsigned short initialLoadOffset = 0x0000;
unsigned char defaultByteCount = 0x10;
unsigned char dataSource[] = { 0x12, 0x34, 0x80, 0x00, 0x80, 0x08 };//{0x02, 0x33, 0x7A};
int dataCount = 6;

int main(int argc, char* argv[]) {
    FILE* pf = fopen(fileName, "w");
    int left = dataCount;
    unsigned short address = initialLoadOffset;
    unsigned char* pSource = dataSource;
    unsigned char checksum;

    while (left > 0) {
        int byteCount = defaultByteCount < left ? defaultByteCount: left;
        fprintf(pf, ":%02X%04X%02X", byteCount, address, 0x0);
        checksum = 0;

        checksum += byteCount;
        checksum += address / 0x100;
        checksum += address & 0xFF;

        for(int idx = 0; idx < byteCount; ++idx){
            fprintf(pf, "%02X", *pSource);
            checksum += *pSource;
            ++pSource;
            --left;
        }
        fprintf(pf, "%02X", (unsigned char) ~checksum + 1);
    }
    fprintf(pf,"\n");

    fprintf(pf, ":00000001FF\n");

    fclose(pf);
}
