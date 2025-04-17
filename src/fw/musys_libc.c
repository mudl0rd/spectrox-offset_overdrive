#include "musys_libc.h"
#include <stdint.h>
#include <windows.h>

float musys_invsqrtf(float x)
{
    union { float f; uint32_t u; } y = { x };
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
}
float musys_sqrtf(float n) { return 1 / musys_invsqrtf(n); }

float musys_sinf(float a)
{
    static float const a0 = +1.91059300966915117e-31f;
    static float const a1 = +1.00086760103908896f;
    static float const a2 = -1.21276126894734565e-2f;
    static float const a3 = -1.38078780785773762e-1f;
    static float const a4 = -2.67353392911981221e-2f;
    static float const a5 = +2.08026600266304389e-2f;
    static float const a6 = -3.03996055049204407e-3f;
    static float const a7 = +1.38235642404333740e-4f;
    return a0 + a * (a1 + a * (a2 + a * (a3 + a * (a4 + a * (a5 + a * (a6 + a * a7))))));
}

float musys_cosf(float a)
{
    static float const a0 = +1.00238601909309722f;
    static float const a1 = -3.81919947353040024e-2f;
    static float const a2 = -3.94382342128062756e-1f;
    static float const a3 = -1.18134036025221444e-1f;
    static float const a4 = +1.07123798512170878e-1f;
    static float const a5 = -1.86637164165180873e-2f;
    static float const a6 = +9.90140908664079833e-4f;
    static float const a7 = -5.23022132118824778e-14f;
    return a0 + a * (a1 + a * (a2 + a * (a3 + a * (a4 + a * (a5 + a * (a6 + a * a7))))));
}

void musys_sincosf(float fRadian, float* fSin, float* fCos)
{
    *fSin = musys_sinf(fRadian);
    *fCos = musys_cosf(fRadian);
}

void* musys_memset(void* s, int c, size_t sz) {
    unsigned char* p = (unsigned char*)s;

    while (sz--)
        *p++ = (unsigned char)c;
    return s;
}

float musys_tanf(float radians)
{
    float rr = radians * radians;
    float a = 9.5168091e-03f;
    a *= rr;
    a += 2.900525e-03f;
    a *= rr;
    a += 2.45650893e-02f;
    a *= rr;
    a += 5.33740603e-02f;
    a *= rr;
    a += 1.333923995e-01f;
    a *= rr;
    a += 3.333314036e-01f;
    a *= rr;
    a += 1.0f;
    a *= radians;
    return a;
}

int seed = 123456789;

void musys_srand(int s)
{
    seed = s;
}

int musys_rand()
{
    seed = seed * 0x343fd + 0x269ec3;
    return ((seed >> 16) & 0x7fff);
}

float
musys_exp(float a)
{
    union { float f; int i; } u, v;
    u.i = (int)(6051102 * a + 1056478197);
    v.i = (int)(1056478197 - 6051102 * a);
    return u.f / v.f;
}

#define log2      0.693147180559945309417232121458176568f
float
musys_log(float a)
{
    union { float f; int i; } u = { a };
    return (u.i - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
}


float musys_exp2f(float x) { return musys_exp(log2 * x); }
float musys_log2f(float x) { return musys_log(x) / log2; }

float
musys_powf(float a, float b)
{
    int flipped = 0, e;
    float f, r = 1.0f;
    if (b < 0) {
        flipped = 1;
        b = -b;
    }

    e = (int)b;
    f = musys_exp(b - e);

    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }

    r *= f;
    return flipped ? 1.0f / r : r;
}

float musys_roundf(float x) { return (float)((x >= 0.0f) ? musys_floorf(x + 0.5f) : musys_ceilf(x - 0.5f)); }
float musys_floorf(float x) { return (float)((x >= 0.0f) ? (int)x : (int)(x - 0.9999999999999999f)); }
float musys_ceilf(float x) { return (float)((x < 0) ? (int)x : ((int)x) + 1); }


float musys_remainder(float x, float y) {
    return x - (musys_roundf(x / y) * y);
}


float musys_copy_sign(float x, float y) {
    int ix, iy;
    ix = *(int*)&x;
    iy = *(int*)&y;

    ix &= 0x7fffffff;
    ix |= iy & 0x80000000;
    return *(float*)&ix;
}

float musys_fmodf(float x, float y) {
    float result;
    y = musys_fabsf(y);
    result = musys_remainder(musys_fabsf(x), y);
    if (musys_sign(result)) result += y;
    return musys_copy_sign(result, x);
}


union header {
    struct {
        size_t size;
        unsigned is_available;
        union header* next;
    } s;
    char _align[32];
};
typedef union header header_t;

void* musys_realloc(void* ptr, size_t size)
{
    void* ret;
    header_t* header;

    header = (header_t*)ptr - 1;
    if (ptr == NULL)
        return (musys_alloc(size));
    else if (size == 0) {
        musys_free(ptr);
        return (NULL);
    }
    if (header->s.size >= size)
        return (ptr);
    ret = musys_alloc(size);
    if (ret != NULL) {
        musys_memcpy(ret, ptr, header->s.size);
        musys_free(ptr);
    }
    return (ret);
}

void* musys_calloc(size_t number, size_t size)
{
    size_t check;
    void* ret;

    check = size * number;
    if (number == 0 || size == 0 || check / size != number)
        return (NULL);
    ret = musys_alloc(number * size);
    if (ret == NULL)
        return (NULL);
    musys_memset(ret, 0, number * size);
    return (ret);
}

int	musys_memcmp(const void* s1, const void* s2, size_t n)
{
    unsigned char* str1;
    unsigned char* str2;
    size_t			i;

    i = 0;
    str1 = (unsigned char*)s1;
    str2 = (unsigned char*)s2;
    while (i < n)
    {
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
        i++;
    }
    return (0);
}

HANDLE getHeap() {
    return GetProcessHeap();
}

void* musys_alloc(size_t bytes) {
    return HeapAlloc(getHeap(), 0, bytes);
}

void musys_free(void* ptr) {
    HeapFree(getHeap(), 0, ptr);
}

void* musys_memcpy(void* dst, const void* src, size_t count)
{
    count--; do { ((char*)dst)[count] = ((char*)src)[count]; } while (count--); return dst;
}

void* musys_memmove(void* dest, const void* src, size_t n)
{
    uint8_t* from = (uint8_t*)src;
    uint8_t* to = (uint8_t*)dest;

    if (from == to || n == 0)
        return dest;
    if (to > from && to - from < (int)n) {
        int i;
        for (i = n - 1; i >= 0; i--)
            to[i] = from[i];
        return dest;
    }
    if (from > to && from - to < (int)n) {
        size_t i;
        for (i = 0; i < n; i++)
            to[i] = from[i];
        return dest;
    }
    musys_memcpy(dest, src, n);
    return dest;
}

char* musys_strcat(char* a, const char* b)
{
    char* ret = a;
    while (*a)
        a++;
    while ((*a++ = *b++)) {}
    return ret;
}

char* musys_strcpy(char* dest, const char* src)
{
    char* wrk = dest;
    while ((*wrk++ = *src++));
    return dest;
}

char* musys_strjoin(char* s1, char* s2)
{
    char* new_str;
    size_t	len;

    if (!s1 || !s2)
        return (NULL);
    len = musys_strlen(s1) + musys_strlen(s2);
    new_str = (char*)musys_alloc(sizeof(char) * (len + 1));
    musys_memmove(new_str, s1, musys_strlen(s1));
    musys_memmove(new_str + musys_strlen(s1), s2, musys_strlen(s2));
    new_str[len] = '\0';
    return (new_str);
}


size_t	musys_strlen(const char* s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}
