#include<stdio.h>

int main(){
    FILE* input;
    char s[12];
    input = fopen("mem.out","r");

    while(fgets(s, 11, input)){
        printf("%s",s);
    }

    fclose(input);

    return 0;
}