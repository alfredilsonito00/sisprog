#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    int a, b;
    int aux;
    int end=0;

    char s [11];
    FILE * acc;
    FILE * mem;

    acc = fopen("acc.out", "r");
    mem = fopen("mem.out", "a+");
    
    fscanf(acc, "%04X", &a);
    b = (int)strtol(argv[1], NULL, 16);
    // scanf("%04X", &b);
    
    aux = 0XFFFF&(0XFFFF - b +1); // mesma coisa de fazer a-b,

    
    if((0XFFFF&(a+aux))<0X8000) {
        printf("%X %X %d", a+aux,0XFFFF&(a+aux), (0XFFFF&(a+aux))<0X8000 );
        while(fgets(s, 11, mem)){
            end++;
        }
        fprintf(mem, "%04X %04X\n", end*2, b);
    }
    
    fclose(acc);
    fclose(mem);

    return 0;
}