/*
 * zconvert.c
 *
 *  Created on: Jul 24, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include "php_url.h"
#include "zconvert.h"


int zUrlEncode(char const *url, unsigned int urlLength,
		char *urlEncoded, unsigned int *urlEncodedLength)
{
	return php_url_encode(url, urlLength, urlEncoded, urlEncodedLength);
}
int zUrlDecode(char *urlEncoded, unsigned int urlLength)
{
	return php_url_decode(urlEncoded, urlLength);
}

int zBase64Encode(char *input, unsigned int inputLength,
		char *output, unsigned int outputLength)
{
	int ret = 0;
	BIO *b64 = NULL, *bmem = NULL;
	BUF_MEM *bptr = NULL;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, input, inputLength); // encode
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);
	if (bptr->length > outputLength)
	{
		printf("> (error) buffer is not enough\n");
		BIO_free_all(b64);
		ret = -1;
	} else {
		outputLength = bptr->length;
		memcpy(output, bptr->data, bptr->length - 1); // remove last "\n"
	}

	BIO_free_all(b64);
	return ret;
}

int zBase64Decode(char *input, unsigned int inputLength,
		char *output, unsigned int outputLength)
{
	int ret = 0, len = 0;
	BIO *b64 = NULL, *bmem = NULL;
	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf(input, inputLength);
	bmem = BIO_push(b64, bmem);
	len = BIO_read(bmem, output, outputLength);
	if (len <= 0)
	{
		ret = -1;
	} else {
		output[len] = '\0';
	}
	BIO_free_all(bmem);
	return ret;
}
