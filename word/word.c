#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

int main()
{
        int pos;
        int counter;
        int mlength;
        int input;

        char *longest = NULL;
        char *line = NULL;
        size_t len = 0;

        pos = 0;

        counter=mlength=input=0;
        getline(&line, &len, stdin);
        while (line[pos] != 0) {        
            if (line[pos] == '\n' || line[pos] == ' ') {
                if (input > mlength) {
                    counter=pos-input;

                    if(input > mlength*2) {
                        longest = realloc(longest, input*2);
                    }
                    mlength = input;
                    
                    strncpy(longest, line+counter, mlength);
                }
                input = 0;
            } else {
                input++;
            }
            
            if (line[pos] == '\n') {
                getline(&line, &len, stdin);                            
                pos=0;
                input++;
            }
            ++pos;
    }

        line[mlength+1] = 0;

        printf("%d characters in longest word: %s\n", mlength, longest);
        free(line);
        free(longest);

        return 0;
}