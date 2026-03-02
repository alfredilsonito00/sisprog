#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
    int a,b;
    int end=0;

    FILE* mem;
    FILE* acc;
    char s[12];

    a = (int)strtol(argv[1], NULL, 16);

    mem = fopen("mem.out","r");
    acc = fopen("acc.out","w");
        
    while(fgets(s, 11, mem)){
        // printf("%s\n", s);

        b = strtol(&s[4], NULL, 16);
        
        // printf("end, b: %04X %04X\n", end, b);
        if(b == a){
            printf("%04X\n", end);
            fprintf(acc, "%04X", end);
            return 0;
        } 
        end = end +2;
    }
            printf("8000");
            fprintf(acc, "8000");


    fclose(mem);
    fclose(acc);

    return 0;
}