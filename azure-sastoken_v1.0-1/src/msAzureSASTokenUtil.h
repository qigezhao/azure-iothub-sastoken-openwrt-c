/*
 * msAzureSASTokenUtil.h
 *
 *  Created on: Jul 25, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#ifndef MSAZURESASTOKENUTIL_H_
#define MSAZURESASTOKENUTIL_H_

#define CONF_SHA256_SIZE		33
#define CONF_URI_SIZE			256
#define CONF_CACHE_SIZE			256
#define CONF_SASTOKEN_SIZE		256

char *iothubSignature(char *sigRef, const char *sasKey, unsigned long expiry);
char *iothubDevUrlEncoded(const char *deviceId);
char *iothubSigRef(const char *uri);
unsigned long iothubExpiry(unsigned long expirySecFromNow);

#endif /* MSAZURESASTOKENUTIL_H_ */
