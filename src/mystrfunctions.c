#include "../include/mystrfunctions.h"

/* return length excluding terminating null */
int mystrlen(const char* s) {
    const char *p = s;
    while (*p) ++p;
    return (int)(p - s);
}

/* copy src into dest, return number of chars copied (excluding null) */
int mystrcpy(char* dest, const char* src) {
    char *d = dest;
    const char *s = src;
    while ((*d++ = *s++)) {}
    return mystrlen(dest);
}

/* copy up to n characters, ensure null termination */
int mystrncpy(char* dest, const char* src, int n) {
    int i = 0;
    while (i < n && src[i]) { dest[i] = src[i]; ++i; }
    while (i < n) { dest[i++] = '\0'; }
    dest[n-1] = '\0'; /* ensure last is null (defensive) */
    return mystrlen(dest);
}

/* append src to dest (dest must have enough space), return length of dest */
int mystrcat(char* dest, const char* src) {
    int dlen = mystrlen(dest);
    int i = 0;
    while (src[i]) {
        dest[dlen + i] = src[i];
        ++i;
    }
    dest[dlen + i] = '\0';
    return mystrlen(dest);
}
