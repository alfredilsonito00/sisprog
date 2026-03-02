#include<stdio.h>

int main(){
    int n;
    int i;
    int num;

    FILE* output;
    output = fopen("mem.out", "w");

    printf("Quantidade de valores:\n");

    scanf("%d", &n);
    
    for(i=0; i<n; i++){
        scanf("%04x", &num);
        // printf("%04X %04X\n\n", i*2,num);
        fprintf(output, "%04X %04X\n", i*2, num);
    }

    printf("Valores salvos na memoria.\n");

    fclose(output);

    return 0;
}