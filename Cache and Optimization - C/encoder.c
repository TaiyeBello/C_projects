/* Taiye Bello bello067 */
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
  if (input == NULL) {
    return 0;
  }
  int length = strlen(input);
  for(int i =0;i<length;i++){
	if(input[i] == '\n'){
		return i;
	}
  }  
  return 0;
}

void encode(struct document *doc)
{
    int a = count(doc->str);
    if(doc->encoded){
	return;
    }
    size_t q =0;
    size_t x = (a/8)*8;
    for (; q < x; q+=8) {
       	doc->str[q] <<= 1;
	doc->str[q+1] <<= 1;
	doc->str[q+2] <<= 1;
	doc->str[q+3] <<= 1;
	doc->str[q+4] <<= 1;
	doc->str[q+5] <<= 1;
	doc->str[q+6] <<= 1;
	doc->str[q+7] <<= 1;
    }
    for(; q<a; q++){
	doc->str[q] <<=1;
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

    /*for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            average += os[i].data[j] / M;
            encode(&os[i]);
        }
    }*/
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            average += os[i].data[j] / M;
            
        }
	encode(&os[i]);
    }
    int x = (M/4)*4;
    for (i = 0; i < x; i+=4) {
        fprintf(file, "%s\n%s\n%s\n%s\n", os[i].str, os[i+1].str, os[i+2].str, os[i+3].str);
    }
    for(;i < M;i++){
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
