#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* getInstruction(char* s) {
    if('0' == s[0]) return "JP";
    if('1' == s[0]) return "JZ";
    if('2' == s[0]) return "JN";
    if('3' == s[0]) return "LV";
    if('4' == s[0]) return "AD";
    if('5' == s[0]) return "SB";
    if('6' == s[0]) return "ML";
    if('7' == s[0]) return "DV";
    if('8' == s[0]) return "LD";
    if('9' == s[0]) return "MM";
    if('A' == s[0]) return "SC";
    if('B' == s[0]) return "RS";
    if('C' == s[0]) return "HM";
    if('D' == s[0]) return "GD";
    if('E' == s[0]) return "PD";
    if('F' == s[0]) return "SO";
    return NULL;
}

int getNum(char* s) {
    if(s[0] == '=') {
        s++;
    
        return atoi(s);
    } else if(s[0] == '/') {
        s++;
        return strtol(s, NULL, 16);
    }
    return -1;
}

int main(int argc, char* argv []){
    int end =0xFFFF + 2;
    int newEnd =0;
    char* token; // string
    char* inst;

    int i=0;

    char buffer[100];
    FILE* input;
    FILE* output;

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");



    while(fgets(buffer, 100, input)){
        token = strtok(buffer, " ");

        newEnd = strtol(token, NULL, 16);
        
        if(newEnd-end> 2 || end-newEnd >2){
            printf("@ /%04X\n",newEnd);
        }

        // se estiver na área de dados
        if(newEnd>0x02FF){
            token = strtok(NULL, "\n");
            printf("K /%s\n",token);
        } else {
            token = strtok(NULL, "\n");
            inst = getInstruction(token);
            token++;
            printf("%s /%s\n", inst, token);
        }

        end = newEnd;
    }
}