/*
 * sha_code.h
 *
 *  Created on: 23 oct. 2013
 *      Author: sanchez
 */

#ifndef SHA_CODE_H_
#define SHA_CODE_H_

#include <openssl/sha.h>
#include <openssl/evp.h>

typedef unsigned char byte;

void sha256_hash_string (byte hash[SHA256_DIGEST_LENGTH], char outputBuffer[65]);

int sha256_file(char *path, char outputBuffer[65]);

#endif /* SHA_CODE_H_ */
