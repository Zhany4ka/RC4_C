#include <stdio.h>
#include <string.h>

#define N 256

void swap(unsigned char *a, unsigned char *b) {
    unsigned char t = *a;
    *a = *b;
    *b = t;
}

void rc4(unsigned char *plaintext, unsigned char *ciphertext, int length, unsigned char *key, int keylength) {
    unsigned char S[N], T[N];
    int i, j = 0, k = 0;

    for (i = 0; i < N; i++) {
        S[i] = i;
        T[i] = key[i % keylength];
    }

    for (i = 0; i < N; i++) {
        j = (j + S[i] + T[i]) % N;
        swap(&S[i], &S[j]);
    }

    i = j = 0;
    for (k = 0; k < length; k++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        ciphertext[k] = plaintext[k] ^ S[(S[i] + S[j]) % N];
    }
}

void rc4_decrypt(unsigned char *ciphertext, unsigned char *plaintext, int length, unsigned char *key, int keylength) {
    rc4(ciphertext, plaintext, length, key, keylength);
}

int main() {
    unsigned char plaintext[] = "This is a plaintext message.";
    unsigned char ciphertext[strlen((char *)plaintext)];
    unsigned char decryptedtext[strlen((char *)plaintext)];
    unsigned char key[] = "Key";
    int length = strlen((char *)plaintext);

    rc4(plaintext, ciphertext, length, key, strlen((char *)key));

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    rc4_decrypt(ciphertext, decryptedtext, length, key, strlen((char *)key));

    printf("Decryptedtext: %s\n", decryptedtext);

    return 0;
}
