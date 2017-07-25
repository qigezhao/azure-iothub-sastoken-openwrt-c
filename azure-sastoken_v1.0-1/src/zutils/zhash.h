/*
 * zhash.h
 *
 *  Created on: Jul 25, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#ifndef ZHASH_H_
#define ZHASH_H_

int zSha256(char *input, unsigned int inputLength, char *output);
int zHashHMAC(const char *algo,
		const char *key, unsigned int keyLength,
		char *input, unsigned int inputLength,
		char *output, unsigned int *outputLength);

#endif /* ZHASH_H_ */
