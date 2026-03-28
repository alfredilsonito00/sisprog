#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* getInstruction(char* s) {
    if(strcmp("JP", s) == 0) return "0";
    if(strcmp("JZ", s) == 0) return "1";
    if(strcmp("JN", s) == 0) return "2";
    if(strcmp("LV", s) == 0) return "3";
    if(strcmp("AD", s) == 0) return "4";
    if(strcmp("SB", s) == 0) return "5";
    if(strcmp("ML", s) == 0) return "6";
    if(strcmp("DV", s) == 0) return "7";
    if(strcmp("LD", s) == 0) return "8";
    if(strcmp("MM", s) == 0) return "9";
    if(strcmp("SC", s) == 0) return "A";
    if(strcmp("RS", s) == 0) return "B";
    if(strcmp("HM", s) == 0) return "C";
    if(strcmp("GD", s) == 0) return "D";
    if(strcmp("PD", s) == 0) return "E";
    if(strcmp("SO", s) == 0) return "F";
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

int isNum(char* s) {
    if(s[0]== '='){
        s++;
        for(int i=0; i<3 && s[i]!='\0'; i++){
            if(!('0'<=s[i] && s[i]<='9')) return 0;
        }
    } else if(s[0] == '/'){
        s++;
        for(int i=0; i<3 && s[i]!='\0'; i++){
            if(!('0'<=s[i] && s[i]<='9') && !(('A'<=s[i] && s[i]<='F'))) return 0;
        }
    } else return 0;

    return 1;
}

int main(int argc, char* argv []){
    int end =0;
    char* token; // string
    char * inst;

    char * simbolos[200];
    int enderecos[200];
    int i=0;

    char op[10];
    char code[3];
    char buffer[100];
    char line[5];
    FILE* input;
    FILE* output;

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    //primeiro passo
    while(fgets(buffer, 100, input)){
        token = strtok(buffer, " ");
        inst = getInstruction(token);
        if(inst == NULL && !(token[0]=='K') ){
            if('@'==token[0]){
                token = strtok(NULL, " ");
                end = getNum(token);
                end-=2;
            } else if ('\n'==token[0]){
                end-=2;
            } else {
                simbolos[i] = malloc(strlen(token) + 1);
                strcpy(simbolos[i],token);
                enderecos[i]= end;
                i++;
            }
        }
        end+=2;
    }

    // printf("simbolos:\n");
    for(int j=0; j<i; j++){
        // printf("%04X %s\n", enderecos[j], simbolos[j]);
        
    }
    // printf("\n\n");

    rewind(input);
    end=0;

    // segundo passo
    while(fgets(buffer, 100,input)){
        token = strtok(buffer, " ");
        inst = getInstruction(token);
        if(inst == NULL){
            if('@'==token[0]){
                token = strtok(NULL, " ");
                end = getNum(token);
                
                end-=2;
            } else if ('K'==token[0] ){
                token = strtok(NULL, " ");
                int num = getNum(token);
                printf("%04X %04X\n", end, getNum(token));
                
            } else if('\n' ==token[0]){
                end-=2; // basicamente anula o acrescimo de endereco se encontrar uma linha nova sem nada
            } else {
                token = strtok(NULL, " ");
                inst = getInstruction(token);
                if(inst == NULL) {
                    
                    token = strtok(NULL, " ");
                    strcpy(op, token);
                    
                    printf( "%04X %04X\n", end, getNum(op));
                    
                    token[strcspn(token, "\n")] = '\0'; // tira o \n 
                }   else {
                    token = strtok(NULL, " ");
                    token[strcspn(token, "\n")] = '\0'; // tira o \n 
                    strcpy(op, token);
                    if(!isNum(op)){
                        for(int j=0; j<i; j++){
                            if(strcmp(token, simbolos[j])==0) {
                                printf( "%04X %s%03X\n", end, inst, enderecos[j]);
                            }
                        }
                    } else {
                        op[4] = '\0';
                        printf("%04X %s%03X\n", end, inst, getNum(op));
                    }
                
                }
            }

        } else {
            token = strtok(NULL, " ");
            strcpy(op, token);
            token[strcspn(token, "\n")] = '\0'; // tira o \n 
            if(!isNum(op)){
                for(int j=0; j<i; j++){
                    if(strcmp(token, simbolos[j])==0) {
                        printf( "%04X %s%03X\n", end, inst, enderecos[j]);
                    }
                }
            } else {

                op[4] = '\0';
                printf("%04X %s%03X\n", end, inst, getNum(op));
            }
        
        }

        end+=2;
    }

}