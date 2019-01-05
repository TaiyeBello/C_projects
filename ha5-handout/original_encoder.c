#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"

struct document {
    int id;
    double data[N];
    char encoded;
    char *str;
};

int count(char* input) {
  int position = 0;
  int counter = 0;
  if (input == NULL) {
    return counter;
  }
  while (input[position] != '\0') {
    if (input[position] == '\n') {
      return counter;
    }
    counter++;
    position++;
  }
  return 0;
}

void encode(struct document *doc)
{
    size_t q = 0;
    for (q = 0; q < count(doc->str); q++) {
        if (doc->encoded)
            return;
        doc->str[q] = doc->str[q] * 2;
    }
    doc->encoded = 1;
}

/*
 * Compute aggregate information about documents describing [REDACTED] and
 * encodes the body string using [REDACTED] algorithm.
 */
double analyze(struct document *os)
{
    int i = 0, j = 0;
    double average = 0.0;
    FILE *file = fopen("output.txt", "w");

    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            average += os[i].data[j] / M;
            encode(&os[i]);
        }
    }
    for (i = 0; i < M; i++) {
        fprintf(file, "%s\n", os[i].str);
    }
    fclose(file);
    return average;
}

static struct document *setupDocuments()
{
    int i = 0, j = 0;
    struct document *os = malloc(sizeof(struct document) * M);
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            os[i].data[j] = TEST_DATA[i][j];
        }
        os[i].str = TEST_STRINGS[i];
        os[i].id = i;
        os[i].encoded = 0;
    }
    return os;
}

int main(int argc, char **argv)
{
    double res;
    struct document *os;
    os = setupDocuments();
    res = analyze(os);
    printf("%f\n",res);
    return 0;
}
