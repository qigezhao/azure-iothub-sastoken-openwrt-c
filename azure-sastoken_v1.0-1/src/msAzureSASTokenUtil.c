/*
 * msAzureSASTokenUtil.c
 *
 *  Created on: Jul 25, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "zutils/zconvert.h"
#include "zutils/zhash.h"
#include "msAzureSASTokenUtil.h"

// Microsoft Azure IotHub SASToken
// HMAC-SHA256 with {KEY} ({URL-encoded-resourceURL}+"\n"+{expiry}),
// base64 encode, and URLEncode again
char *iothubSignature(char *sigRef, const char *sasKey, unsigned long expiry)
{
	static char signature[CONF_SASTOKEN_SIZE] = { 0 };

	unsigned int bufferLength;
	char buffer1[CONF_CACHE_SIZE], buffer2[CONF_CACHE_SIZE];

	bufferLength = sizeof(buffer1);

	memset(buffer1, 0, sizeof(buffer1));
	snprintf(buffer1, sizeof(buffer1), "%s\n%ld", sigRef, expiry);

	memset(buffer2, 0, sizeof(buffer2));
	zHashHMAC("sha256", sasKey, strlen(sasKey),
			buffer1, strlen(buffer1), buffer2, &bufferLength);

	memset(buffer1, 0, sizeof(buffer1));
	zBase64Encode(buffer2, strlen(buffer2), buffer1, sizeof(buffer1));

	memset(buffer2, 0, sizeof(buffer2));
	zUrlEncode(buffer1, strlen(buffer1), buffer2, &bufferLength);

	snprintf(signature, sizeof(signature), "%s", buffer2);
	printf("SASToken: signature-string = %s\n", signature);
	return signature; // {signature-string}
}

unsigned long iothubExpiry(unsigned long expirySecFromNow)
{
	unsigned long expiry = time((time_t *) NULL); // current time
	if (expirySecFromNow > 0)
	{
		expiry += expirySecFromNow;
	}
	return expiry;
}

char *iothubDevUrlEncoded(const char *uri)
{
	static char uriEncoded[CONF_URI_SIZE] = { 0 };
	unsigned int uriEncodedLength = sizeof(uriEncoded);

	zUrlEncode(uri, strlen(uri), uriEncoded, &uriEncodedLength);

	return uriEncoded; // {URL-encoded-resourceURL}
}


char *iothubSigRef(const char *uri)
{
	return iothubDevUrlEncoded(uri);
}

