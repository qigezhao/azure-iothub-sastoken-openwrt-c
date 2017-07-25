/*
 * msAzureSASToken.h
 *
 *  Created on: Jul 24, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#ifndef MSAZURESASTOKEN_H_
#define MSAZURESASTOKEN_H_

char *msAzureIothubSASToken(const char *resourceUri, char *policyName,
		const char *sasKey, unsigned long expiry);

#endif /* MSAZURESASTOKEN_H_ */
