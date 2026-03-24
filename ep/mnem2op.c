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
    printf("teste atoi: %d %s\n", atoi(s), s);
    return -1;
    // return NULL;
}

int isNum(char* s) {
    printf("in isNum: %s\n", s);
    if(s[0]== '/'|| s[0] == '='){
        s++;
    } else return 0;
    printf("in isNum: %s\n", s);
    for(int i=0; i<3 && s!="\0"; i++){
        printf("isNum char: %d %c %d %d\n", i, s[i], '0'<=s[i], s[i]<='9');
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

    // printf("%s\n", argv[1]);
    //primeiro passo
    while(fgets(buffer, 100, input)){
        // printf("buffer: %send:%04X\n",buffer, end);
        token = strtok(buffer, " ");
        inst = getInstruction(token);
        // printf("analise: %d %d %d %c\n",(inst == NULL), !(token[0]=='\n'), !(token[0]=='K'), token[0]);
        if(inst == NULL && !(token[0]=='\n') && !(token[0]=='K') ){
            // if(strcmp("@",token) == 0 ){
            printf("entra: %s %04X\n", token, end);
            if('@'==token[0]){
                token = strtok(NULL, " ");
                end = getNum(token);
                end-=2;
                // printf("end mudado: %04X\n", end);
                // if(end == NULL){

                // }
                // printf("@ found\n");
            } else {
                simbolos[i] = malloc(strlen(token) + 1);
                strcpy(simbolos[i],token);
                enderecos[i]= end;
                // printf("novo simbolo: %04X %s\n", i, token);
                i++;
            }
        }
        end+=2;
    }

    int n = i+1;// número de mnemonicos achados

    printf("simbolos: \n");
    for(int j=0; j<i; j++){
        printf("%04X %s\n", enderecos[j], simbolos[j]);
    }
    // printf("enderecos: \n");
    // for(int j=0; j<i; j++){
    //     printf("%04X %04X\n",j, enderecos[j]);
    // }

    rewind(input);
    end=0;
    printf("i: %d\n", i);
    // segundo passo
    while(fgets(buffer, 100,input)){
        token = strtok(buffer, " ");
        printf("buffer: %s\n", buffer);
        // printf("token: %d\n", token);
        // printf("newToken: %d %s\n", &newToken, &newToken[0]);
        inst = getInstruction(token);
        if(inst == NULL){
            printf("NULL: %s %d %d %s\n", token, strcmp("@",token), strcmp("K",token), buffer);
            if('@'==token[0]){
                token = strtok(NULL, " ");
                end = getNum(token);
                // if(end == NULL){
                    
                end-=2;
                // }
                // printf("@ found\n");
            } else if ('K'==token[0] ){
                token = strtok(NULL, " ");
                int num = getNum(token);
                // printf("%04X %04X\n", end, getNum(token));
                fprintf(output,"%04X %04X\n", end, getNum(token));
                // printf("%04X %04X\n", end, getNum(token));
                // printf("K found \n");

            } else if('\n' ==token[0]){
                end-=2; // basicamente anula o acrescimo de end
            } else {
                token = strtok(NULL, " ");
                inst = getInstruction(token);
                if(inst == NULL) {

                    token = strtok(NULL, " ");
                    strcpy(op, token);
                    
                    fprintf(output, "%04X %04X\n", end, getNum(op));
                    printf("%04X %04X\n", end, getNum(op));
                
                    printf("isNum: %d\n", isNum(op));
                    token[strcspn(token, "\n")] = '\0'; // tira o \n 
                }   else {
                    printf("not null but with mneumonic: %s\n", inst);
                    token = strtok(NULL, " ");
                    strcpy(op, token);
                    printf("isNum: %d\n", isNum(op));
                    token[strcspn(token, "\n")] = '\0'; // tira o \n 
                    if(!isNum(op)){
                        for(int j=0; j<i; j++){
                            printf("procurando na tabela %s %s %d %04X\n", token, simbolos[j], strcmp(token, simbolos[j]), enderecos[j]);
                            if(strcmp(token, simbolos[j])==0) {
                                fprintf(output, "%04X %s%03X\n", end, inst, enderecos[j]);
                                printf("%04X %s%03X\n", end, inst, enderecos[j]);
                            }
                        }
                    } else {
                    
                        // printf("op obtido:%s\n", op);
                        op[4] = '\0';
                        // op++;
                        printf("op obtido:%s\n", op);
                        printf("tamanho op: %d\n",strlen(op));
                        printf("%04X %s%03X\n", end, inst, getNum(op));
                        fprintf(output,"%04X %s%03X\n", end, inst, getNum(op));
                    }
                
                }
                // if(!isNum(op)){ // basicamente quero que ele detecte se trata-se de mnemonico ou de absoluto
                //     for(int j=0; j<i; j++){
                    //         printf("procurando na tabela %s %s %d %04X\n", token, simbolos[j], strcmp(token, simbolos[j]), enderecos[j]);
                //         if(strcmp(token, simbolos[j])==0) {
                //             fprintf(output, "%04X %s%03X\n", end, inst, enderecos[j]);
                //             printf("%04X %s%03X\n", end, inst, enderecos[j]);
                //             break;
                //         }
                //     }
                // } else {
                    
                //     op[3] = '\0';
                //     printf("tamanho op: %d\n",strlen(op));
                //     printf("op obtido:%s\n", op);
                //     printf("%04X %s%s\n", end, inst, op);
                //     fprintf(output,"%04X %s%s\n", end, inst, op);
                // }
                
                // simbolos[i] = token;
                
                // printf("novo simbolo: %04X %s\n", i, token);
                // printf("antigos:\n");
                // for(int j=0; j<i; j++){
                    //     printf("%04X %s\n",j, simbolos[j]);
                // }

            }

        } else {
            printf("not null: %s\n", inst);
            token = strtok(NULL, " ");
            strcpy(op, token);
            printf("isNum: %d\n", isNum(op));
            token[strcspn(token, "\n")] = '\0'; // tira o \n 
            if(!isNum(op)){
                for(int j=0; j<i; j++){
                    printf("procurando na tabela %s %s %d %04X\n", token, simbolos[j], strcmp(token, simbolos[j]), enderecos[j]);
                    if(strcmp(token, simbolos[j])==0) {
                        fprintf(output, "%04X %s%03X\n", end, inst, enderecos[j]);
                        printf("%04X %s%03X\n", end, inst, enderecos[j]);
                    }
                }
            } else {

                // printf("op obtido:%s\n", op);
                op[4] = '\0';
                // op++;
                printf("op obtido:%s\n", op);
                printf("tamanho op: %d\n",strlen(op));
                printf("%04X %s%03X\n", end, inst, getNum(op));
                fprintf(output,"%04X %s%03X\n", end, inst, getNum(op));
            }
        
        }

        end+=2;
        // free(newToken);
        // printf("newToken: %d %d\n", &newToken, newToken[0]);
    }

}