#ifndef _MUSYSLIBC_H_
#define _MUSYSLIBC_H_

#include <stdint.h>
#include <stdio.h>

#ifndef M_PI
#   define M_PI 3.1415926535897932384626433832
#endif

#ifdef __cplusplus
extern "C" {
#endif
	float musys_sinf(const float x);
	float musys_cosf(const float x);
	float musys_tanf(const float x);
	float musys_sqrtf(float n);
	float musys_invsqrtf(float x);
#define musys_fabsf(x) ((x) > 0 ? (x) : -(x))
#define musys_sign(x) ((x) >= 0 ? 1 : -1)
	float musys_log(float a);
	float musys_exp(float a);
	float musys_exp2f(float x);
	float musys_log2f(float x);
	float musys_powf(float a, float b);
	float musys_roundf(float x);
	float musys_floorf(float x);
	float musys_ceilf(float x);
	float musys_fmodf(float x, float y);
	void musys_sincosf(float fRadian, float* fSin, float* fCos);
	void* musys_memcpy(void* dst, const void* src, size_t count);
	int	musys_memcmp(const void* s1, const void* s2, size_t n);
	void* musys_memset(void* s, int c, size_t sz);
	void* musys_memmove(void* dest, const void* src, size_t n);
	void* musys_realloc(void* ptr, size_t size);
	size_t	musys_strlen(const char* s);
	char* musys_strcat(char* a, const char* b);
	char* musys_strcpy(char* dest, const char* src);
	char* musys_strjoin(char* s1, char* s2);
	void* musys_calloc(size_t number, size_t size);
	void* musys_alloc(size_t bytes);
	void musys_free(void* ptr);
	int musys_rand();
	void musys_srand(int s);

#ifdef __cplusplus
}
#endif

#endif
