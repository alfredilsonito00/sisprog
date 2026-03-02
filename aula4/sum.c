#include <stdio.h>
#include <stdlib.h>

int main(){
    int a,b;
    int end1, end2;
    int i=0;
    int aux;

    FILE* input;

    input = fopen("mem.out", "r");

    scanf("%04x", &end1);
    scanf("%04x", &end2);

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

    printf("%04X", a+b);

    return 0;
}