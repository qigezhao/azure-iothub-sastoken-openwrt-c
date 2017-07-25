/*
 * msAzureSASToken.c
 *
 * device-to-cloud messages: (/devices/{deviceId}/messages/events)
 *
 * Policy Names:
 * iothubowner: Policy with all permissions.
 * service: Policy with ServiceConnect permissions.
 * device: Policy with DeviceConnect permissions.
 * registryRead: Policy with RegistryRead permissions.
 * registryReadWrite: Policy with RegistryRead and RegistryWrite permissions.
 *
 * ShareAccessSignature sig={signature-string}&se={expiry}&skn={policy-name}&sr={URL-encoded-resourceURI}
 *
 * {signature-string}: urlEncode(base64(HMACSha256(urlEncode(uri)+"\n"+expery, key)))
 * {expery}: seconds since "1970-01-01 00:00:00"
 * {policy-name}:
 * {URL-encoded-resourceURI}:
 *
 *  Created on: Jul 24, 2017
 *      Author: Qige <qigezhao@gmail.com>
 */

#include <stdio.h>
#include <string.h>

#include "msAzureSASToken.h"
#include "msAzureSASTokenUtil.h"


char *msAzureIothubSASToken(const char *uri, char *policyName,
		const char *sasKey, unsigned long expiry)
{
	static char sasToken[CONF_SASTOKEN_SIZE] = { 0 };

	unsigned long expirySince1970 = iothubExpiry(expiry);

	// XXX: signature-string: P85NiR4wkzt38L1yNY1RkEBpWTuOg7h4m5o%2BpPBwg50%3D
	expirySince1970 = 1501568074; // DEBUG USE ONLY
	printf("SASToken> (debug) expiry = %ld\n", expirySince1970);

	char sigRef[CONF_URI_SIZE] = { 0 };
	snprintf(sigRef, sizeof(sigRef), "%s", iothubSigRef(uri));

	snprintf(sasToken, sizeof(sasToken), "SharedAccessSignature sig=%s&se=%ld&skn=%s&sr=%s",
			iothubSignature(sigRef, sasKey, expirySince1970), expirySince1970,
			policyName, sigRef);
	return sasToken;
}

// sample data
// uri: "arn-mqtt.azure-devices.net"
// key: "dev24"
// expiry: 1501568074
// calc > signature-string: P85NiR4wkzt38L1yNY1RkEBpWTuOg7h4m5o%2BpPBwg50%3D
int main(int argc, char *argv[])
{
	char domain[] = "arn-mqtt.azure-devices.net";
	char key[] = "dev24";
	int expiry = 3600 * 24; // valid in next 24h
	char iothubSASToken[CONF_CACHE_SIZE] = { 0 };

	snprintf(iothubSASToken, sizeof(iothubSASToken), "%s",
			msAzureIothubSASToken(domain, "iothubowner", key, expiry));

	printf("Microsoft Azure IotHub SASToken (%d bytes)\n[%s]\n\n",
			(unsigned int ) strlen(iothubSASToken), iothubSASToken);


	char endpoint[] = "myhub.azure-devices.cn/devices/device1";
	char policyName[] = "device";
	char policyKey[] = "...";

	snprintf(iothubSASToken, sizeof(iothubSASToken), "%s",
			msAzureIothubSASToken(endpoint, policyName, policyKey, 60));
	printf("Microsoft Azure IotHub SASToken (%d bytes)\n[%s]\n\n",
			(unsigned int) strlen(iothubSASToken), iothubSASToken);
	return 0;
}
