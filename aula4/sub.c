#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int a,b;
    int end1, end2;
    int i=0;
    int aux;

    FILE* input;
    FILE* output;

    input = fopen("mem.out", "r");
    output = fopen("acc.out", "w");


    end1 = (int)strtol(argv[1], NULL, 16);
    end2 = (int)strtol(argv[2], NULL, 16);

    if(end2<end1){
        aux = end1;
        end1= end2;
        end2= aux;
    }
    
    for(; i<end1/2; i++){
        fscanf(input, "%04X %04X", &aux, &b);
    }

    fscanf(input, "%04X %04X",&aux, &a);

    for(i++; i<end2/2;i++){
        fscanf(input, "%04X %04X",&aux, &b);
    }
    
    fscanf(input, "%04X %04X",&aux, &b);

    b = 0XFFFF&(0XFFFF - b +1); // mesma coisa de fazer a-b,
    
    printf("%04X", (a+b)&0XFFFF);
    fprintf(output, "%04X", (a+b)&0XFFFF);

    return 0;
}