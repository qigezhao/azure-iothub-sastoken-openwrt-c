/*
 * zconvert.h
 *
 *  Created on: Jul 24, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#ifndef ZCONVERT_H_
#define ZCONVERT_H_

// wrapper of php url encode/decode
int zUrlDecode(char *url, unsigned int urlLength);
int zUrlEncode(char const *url, unsigned int length,
		char *urlEncoded, unsigned int *urlLength);

// wrapper of openssl BIO_f_base64
int zBase64Encode(char *input, unsigned int inputLength,
		char *output, unsigned int outputLength);
int zBase64Decode(char *input, unsigned int inputLength,
		char *output, unsigned int outputLength);

#endif /* ZCONVERT_H_ */

