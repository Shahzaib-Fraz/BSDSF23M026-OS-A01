#include "../include/myfilefunctions.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Count lines, words and chars. A simple word definition: sequence separated by whitespace */
int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (!file || !lines || !words || !chars) return -1;
    rewind(file);
    int ln = 0, wd = 0, ch = 0;
    int in_word = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        ++ch;
        if (c == '\n') ++ln;
        if (isspace(c)) {
            in_word = 0;
        } else {
            if (!in_word) { ++wd; in_word = 1; }
        }
    }
    *lines = ln;
    *words = wd;
    *chars = ch;
    return 0;
}

/* mygrep: find lines containing search_str, return matches array (dynamically allocated).
 * matches will point to an array of char*; each char* is malloc'd.
 * Caller must free each matches[i] and free(matches).
 */
int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (!fp || !search_str || !matches) return -1;
    rewind(fp);
    size_t cap = 8;
    size_t count = 0;
    char **arr = malloc(cap * sizeof(char*));
    if (!arr) return -1;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    /* use POSIX getline if available; otherwise fallback */
#ifdef _GNU_SOURCE
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, search_str)) {
            if (count >= cap) {
                cap *= 2;
                char **tmp = realloc(arr, cap * sizeof(char*));
                if (!tmp) { free(line); for (size_t i=0;i<count;++i) free(arr[i]); free(arr); return -1; }
                arr = tmp;
            }
            arr[count++] = strdup(line);
        }
    }
    free(line);
#else
    /* portable fallback */
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, search_str)) {
            if (count >= cap) {
                cap *= 2;
                char **tmp = realloc(arr, cap * sizeof(char*));
                if (!tmp) { for (size_t i=0;i<count;++i) free(arr[i]); free(arr); return -1; }
                arr = tmp;
            }
            arr[count++] = strdup(buffer);
        }
    }
#endif

    *matches = arr;
    return (int)count;
}
