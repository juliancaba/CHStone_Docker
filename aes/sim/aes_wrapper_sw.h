#ifndef AES_H
#define AES_H

#define N 16

void encrypt_wrapper (int statemt[N], int key[N], int AESType);
void decrypt_wrapper (int statemt[N], int key[N], int AESType);

#endif
