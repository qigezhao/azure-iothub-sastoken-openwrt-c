/*
 * zhash.c
 *
 *  Created on: Jul 25, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#include <stdio.h>
#include <string.h>

#include <openssl/opensslconf.h>
#include <openssl/sha.h>
#include <openssl/opensslv.h>
#include <openssl/hmac.h>

int zSha256(char *input, unsigned int inputLength, char *output)
{
	int i = 0;
	unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

	SHA256((unsigned char *) input, inputLength, hash);

	for(i = 0; i < SHA256_DIGEST_LENGTH; i ++)
	{
		sprintf(output + (i * 2), "%02x", hash[i]);
	}

	//printf("raw> [%s]\n", output);
	return 0;
}

// learn from:
// "http://blog.csdn.net/yasi_xi/article/details/9066003"
// "http://blog.csdn.net/zzhongcy/article/details/45823845"
int zHashHMAC(const char *algo,
		const char *key, unsigned int keyLength,
		char *input, unsigned int inputLength,
		char *output, unsigned int *outputLength)
{
	const EVP_MD *engine = NULL;

	if (strcasecmp("sha512", algo) == 0)
	{
		engine = EVP_sha512(); // 64 bytes
	}
	else if (strcasecmp("sha256", algo) == 0)
	{
		engine = EVP_sha256(); // 32 bytes
	}
	else if (strcasecmp("sha1", algo) == 0)
	{
		engine = EVP_sha1(); // 20 bytes
	}
	else if (strcasecmp("md5", algo) == 0)
	{
		engine = EVP_md5(); // 16 bytes
	}
	else if (strcasecmp("sha224", algo) == 0)
	{
		engine = EVP_sha224(); // 28 bytes
	}
	else if (strcasecmp("sha384", algo) == 0)
	{
		engine = EVP_sha384(); // 49 bytes
	}
	else {
		printf("zHMACEncode> (error) Algorithm %s is not supported.\n", algo);
		return -1;
	}

	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);

	HMAC_Init_ex(&ctx, key, strlen(key), engine, NULL);
	HMAC_Update(&ctx, (unsigned char *) input, inputLength);

	HMAC_Final(&ctx, (unsigned char *) output, outputLength);
	HMAC_CTX_cleanup(&ctx);

	return 0;
}
