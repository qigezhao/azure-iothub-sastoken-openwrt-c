/*
 * php_url.h
 *
 * Modified by: Qige <qigezhao@gmail.com> 2017.07.25
 */

#ifndef PHP_URL_H_
#define PHP_URL_H_

int php_url_decode(char *str, unsigned int len);
int php_url_encode(char const *s, unsigned int len, char *url_enc, unsigned int *new_length);

#endif /* PHP_URL_H_ */
