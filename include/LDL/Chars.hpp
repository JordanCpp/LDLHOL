/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef LDL_Chars_hpp
#define LDL_Chars_hpp

size_t LDL_CharsLength(const char* source);
char* LDL_CharsCopy(char* to, const char* from);
size_t LDL_CharsCopy(char* dst, const char* src, size_t siz);
size_t LDL_CharsConcat(char* dst, const char* src, size_t dsize);
int LDL_CharsCompare(const char* s1, const char* s2);
bool LDL_CharsEqual(const char* s1, const char* s2);

#ifdef LDL_IMPLEMENTATION
size_t LDL_CharsLength(const char* source)
{
	size_t i = 0;

	while (source[i] != '\0')
	{
		i++;
	}

	return i;
}

//https://github.com/openbsd/src/blob/master/lib/libc/string/strcpy.c
char* LDL_CharsCopy(char* to, const char* from)
{
	char* save = to;

	for (; (*to = *from) != '\0'; ++from, ++to);
	return(save);
}

//https://github.com/openbsd/src/blob/master/lib/libc/string/strlcpy.c
size_t LDL_CharsCopy(char* dst, const char* src, size_t siz)
{
	char* d = dst;
	const char* s = src;

	size_t n = siz;
	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}
	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return (s - src - 1);	/* count does not include NUL */
}

//https://github.com/openbsd/src/blob/master/lib/libc/string/strlcat.c
size_t LDL_CharsConcat(char* dst, const char* src, size_t dsize)
{
	const char* odst = dst;
	const char* osrc = src;
	size_t n = dsize;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end. */
	while (n-- != 0 && *dst != '\0')
		dst++;
	dlen = dst - odst;
	n = dsize - dlen;

	if (n-- == 0)
		return(dlen + LDL_CharsLength(src));
	while (*src != '\0') {
		if (n != 0) {
			*dst++ = *src;
			n--;
		}
		src++;
	}
	*dst = '\0';

	return (dlen + (src - osrc));	/* count does not include NULL */
}

//https://github.com/openbsd/src/blob/master/lib/libc/string/strcmp.c
int LDL_CharsCompare(const char* s1, const char* s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char*)s1 - *(unsigned char*)--s2);
}

bool LDL_CharsEqual(const char* s1, const char* s2)
{
	return (LDL_CharsCompare(s1, s2) == 0);
}

#endif

#endif
