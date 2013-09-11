#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int tcp_flags(int flags) {
    int i, j, result, mask = 0x1FF;
    
    if (flags > mask) {
        printf("Invalid entry");
        return 1;
    }
    printf("\nFlags: ");
    if (flags & 0x0100) {
        printf("NC");
    }
    if (flags & 0x0080) {
        printf(" CWR");
    }
    if (flags & 0x0040) {
        printf(" ECE");
    }
    if (flags & 0x0020) {
        printf(" URG");
    }
    if (flags & 0x0010) {
        printf(" ACK");
    }
    if (flags & 0x0008) {
        printf(" PSH");
    }
    if (flags & 0x0004) {
        printf(" RST");
    }
    if (flags & 0x0002) {
        printf(" SYN");
    }
    if (flags & 0x0001) {
        printf(" FIN");
    }
    printf("\n");
    return 0;
}


int print_bits(char c)
{
    int i,j;
    char charBits[8], *bitSeries;
    for (i=0, j=7; i < 8;i++, j--) {
        if ((c >> i) & 1) {
            charBits[j] = '1';
        } else {
            charBits[j] = '0';
        }
    }
    charBits[8] = '\0';
    printf("The bit series is: %s\n", charBits);
    return 0;
}


int print_bits_EC(unsigned char* ptr, size_t len)
{
    int i = 0, j, k = 0;
    char c, charBits[8];
    printf("Following is the bit sequence for your input\n");
    while (ptr[k]) {
        printf("Char: %c \t",ptr[k]);
        c = ptr[k++];
        print_bits(c);
    }
    printf("\n");
    return 0;
}

int split_short(unsigned short byte)
{
    unsigned short first=0, second=0;
    unsigned short fbyte = 0xff00, sbyte = 0x00ff;
    first = byte & fbyte;
    second = byte & sbyte;
    printf("\nFirst:%u\nSecond:%u\n", first, second);
}


int main()
{
    int i = 1;
    int flags;
    size_t len;
    unsigned char c, *ptr;
    //1.2.2 - prints bits for a character.
    c = 'a';
    print_bits(c);
    printf("\n\n");
    //1.2.3 - print bits for arbitrary data.
    ptr = (char *)malloc(50*sizeof(char));
    ptr = "arbitraryData";
    len = strlen(ptr);
    print_bits_EC(ptr, len);
    printf("\n\n");
    //1.2.4 - split unsigned short.
    unsigned short byte = 24000;
    split_short(byte);
    printf("\n\n");
}
