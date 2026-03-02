#include<stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int a,b;
    int end=0;
    int aux;

    char s[11];

    short int termina=0;

    FILE* acc;
    FILE* mem;
    
    acc = fopen("acc.out", "r");
    mem = fopen("mem.out", "a+");
    
    fscanf(acc, "%04X", &a);
        
    while(fgets(s, 11, mem)){    
        end++;
    }   

    printf("%d\n", argc);

    for(int i=0; i<argc; i++){
        b = (int)strtol(argv[i+1], NULL, 16);
        aux = 0XFFFF&(0XFFFF - b +1); // mesma coisa de fazer a-b,

        
        if((0XFFFF&(a+aux))<0X8000){
            fprintf(mem, "%04X %04X\n", end*2, b);
            end++;
        } else {
            printf("%04X", (end-1)*2);
            return 0;
        }
    }

    return 0;
}