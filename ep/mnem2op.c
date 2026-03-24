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
    // return NULL;
}

int isNum(char* s) {
    if(s[0]== '/'|| s[0] == '='){
        s++;
    } else return 0;
    for(int i=0; i<3 && s!="\0"; i++){
        if(!('0'<=s[i] && s[i]<='9')) return 0;
    }

    return 1;
}

int main(int argc, char* argv []){
    int end =0;
    char* token; // string
    // char ** newToken= malloc(10* sizeof(char* ));
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
    output = fopen("teste.txt", "w");

    //primeiro passo
    while(fgets(buffer, 100, input)){
        token = strtok(buffer, " ");
        inst = getInstruction(token);
        if(inst == NULL && !(token[0]=='\n') && !(token[0]=='K') ){
            // if(strcmp("@",token) == 0 ){
            if('@'==token[0]){
                token = strtok(NULL, " ");
                end = getNum(token);
                end-=2;
                // if(end == NULL){

                // }
            } else {
                simbolos[i] = malloc(strlen(token) + 1);
                strcpy(simbolos[i],token);
                enderecos[i]= end;
                i++;
            }
        }
        end+=2;
    }

    int n = i+1;// número de mnemonicos achados

    for(int j=0; j<i; j++){
    }
    // for(int j=0; j<i; j++){
    // }

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
                // if(end == NULL){
                    
                end-=2;
                // }
            } else if ('K'==token[0] ){
                token = strtok(NULL, " ");
                int num = getNum(token);
                fprintf(output,"%04X %04X\n", end, getNum(token));

            } else if('\n' ==token[0]){
                end-=2; // basicamente anula o acrescimo de end
            } else {
                token = strtok(NULL, " ");
                inst = getInstruction(token);
                if(inst == NULL) {

                    token = strtok(NULL, " ");
                    strcpy(op, token);
                    
                    fprintf(output, "%04X %04X\n", end, getNum(op));
                
                    token[strcspn(token, "\n")] = '\0'; // tira o \n 
                }   else {
                    token = strtok(NULL, " ");
                    strcpy(op, token);
                    token[strcspn(token, "\n")] = '\0'; // tira o \n 
                    if(!isNum(op)){
                        for(int j=0; j<i; j++){
                            if(strcmp(token, simbolos[j])==0) {
                                fprintf(output, "%04X %s%03X\n", end, inst, enderecos[j]);
                            }
                        }
                    } else {
                    
                        op[4] = '\0';
                        // op++;
                        fprintf(output,"%04X %s%03X\n", end, inst, getNum(op));
                    }
                
                }
                // if(!isNum(op)){ // basicamente quero que ele detecte se trata-se de mnemonico ou de absoluto
                //     for(int j=0; j<i; j++){
                //         if(strcmp(token, simbolos[j])==0) {
                //             fprintf(output, "%04X %s%03X\n", end, inst, enderecos[j]);
                //             break;
                //         }
                //     }
                // } else {
                    
                //     op[3] = '\0';
                //     fprintf(output,"%04X %s%s\n", end, inst, op);
                // }
                
                // simbolos[i] = token;
                
                // for(int j=0; j<i; j++){
                // }

            }

        } else {
            token = strtok(NULL, " ");
            strcpy(op, token);
            token[strcspn(token, "\n")] = '\0'; // tira o \n 
            if(!isNum(op)){
                for(int j=0; j<i; j++){
                    if(strcmp(token, simbolos[j])==0) {
                        fprintf(output, "%04X %s%03X\n", end, inst, enderecos[j]);
                    }
                }
            } else {

                op[4] = '\0';
                // op++;
                fprintf(output,"%04X %s%03X\n", end, inst, getNum(op));
            }
        
        }

        end+=2;
        // free(newToken);
    }

}