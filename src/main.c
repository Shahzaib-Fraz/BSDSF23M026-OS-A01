#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main(void) {
    printf("--- Testing String Functions ---\n");
    char buf[128];

    buf[0] = '\0';
    mystrcpy(buf, "Hello");
    printf("mystrcpy -> %s (len=%d)\n", buf, mystrlen(buf));

    mystrncpy(buf, "ABCDEFG", 5);
    printf("mystrncpy(n=5) -> %s (len=%d)\n", buf, mystrlen(buf));

    buf[0] = '\0';
    mystrcpy(buf, "Hi");
    mystrcat(buf, " there");
    printf("mystrcat -> %s (len=%d)\n", buf, mystrlen(buf));

    printf("\n--- Testing File Functions ---\n");
    const char *fname = "testfile.txt";
    FILE *f = fopen(fname, "w");
    if (!f) { perror("fopen"); return 1; }
    fprintf(f, "Hello world\nThis is a test\nSearch me\nAnother line with Search\n");
    fclose(f);

    f = fopen(fname, "r");
    if (!f) { perror("fopen read"); return 1; }

    int lines, words, chars;
    if (wordCount(f, &lines, &words, &chars) == 0) {
        printf("wordCount: lines=%d words=%d chars=%d\n", lines, words, chars);
    } else {
        printf("wordCount failed\n");
    }

    char **matches = NULL;
    int n = mygrep(f, "Search", &matches);
    if (n >= 0) {
        printf("mygrep found %d matches:\n", n);
        for (int i = 0; i < n; ++i) {
            printf("  %s", matches[i]);
            free(matches[i]);
        }
        free(matches);
    } else {
        printf("mygrep failed\n");
    }
    fclose(f);

    return 0;
}
