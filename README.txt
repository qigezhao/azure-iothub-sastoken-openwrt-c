Microsoft Azure IoTHub SASToken
-------------------------------
It cost me 2 days to dig out the real function calls.

1. It depends on libopenssl, and need "-lcrypto" when compiling;
2. It calls "url encode", "HMACSha256", "base64 encode";
3. It reads in "resource uri", "key", "policy name", return with format:
  "SharedAccessSignature sig={signature-string}&se={expiry}&skn={policy-name}&sr={RL-encoded-resourceURI}";
    {URL-encoded-resourceURI} urlEncode(resourceUri)
    {signature-string}        urlEncode(resourceUri) -> +"\n"+expiry -> HMACSha256(key) -> base64Encode() -> urlEncode()
    {expiry}                  seconds since "1970-01-01 00:00:00"
    {policy-name}             "iothubowner", "service", "device", "registryRead", "registryReadWrite"

4. It's a OpenWrt package;
5. I seperate all encode/decode/hash parts into "zutils".

Good luck and have fun!
by Qige <qigezhao@gmail.com>
2017.07.25
