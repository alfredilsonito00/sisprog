#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

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

int findRot(int end, int i, int j, int k, int enderecosJump[], int enderecosRot[], int enderecosSub[]) {
    char* rot ="\0";

    for(int a=0; a<i; a++){
        // printf("loop jump: %d %03X end: %03X\n", a, enderecosJump[a], end);
        // if(enderecosJump[a] == end){printf("encontrou rotulo em jump: %02d", a); return ("%s%02d", "JUMP", a);}
        if(enderecosJump[a] == end){printf("JUMP%02d  ", a); return 0;}
    }
    
    for(int a=0; a<j; a++){
        // printf("loop sub: %d %03X end: %03X\n", a, enderecosSub[a], end);
        // if(enderecosSub[a] == end) {printf("encontrou rotulo em sub: %02d", a); ("%s%02d", "SUB", a);}
        if(enderecosSub[a] == end) {printf("SUB%02d   ", a);return 0;}
    }

    for(int a=0; a<k; a++){
        // printf("loop Rotulos: %d %03X end: %03X\n", a, enderecosRot[a], end);
        // if(enderecosRot[a] == end) {printf("encontrou rotulo em Rot: %02d", a);return ("%s%02d", "ROT", a);}
        if(enderecosRot[a] == end) {printf("ROT%02d   ", a);return 0;}
    }

    return -1;
}

int main(int argc, char* argv []){
    int end =0xFFFF + 2;
    int newEnd =0;
    char* token; // string
    char* inst;
    char* rotule;

    int i=0;    
    int enderecosJump[100];
    
    int j=0;    
    int enderecosRot[100];

    int k=0;    
    int enderecosSub[100];

    char buffer[100];
    FILE* input;
    FILE* output;

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");



    while(fgets(buffer, 100, input)){
        token = strtok(buffer, " ");

        newEnd = strtol(token, NULL, 16);
        
        if(newEnd-end> 2 || end-newEnd >2){
            // printf("@ /%04X\n",newEnd);
        }

        // se estiver na área de dados
        if(!(newEnd>0x02FF)){
            token = strtok(NULL, "\n");
            inst = getInstruction(token);
            if(token[0] == '0' ||token[0] == '1' ||token[0] == '2'){
                token++;
                enderecosJump[i] = strtol(token, NULL, 16);
                // printf("token: %s\n", token);
                // printf("JP%02d: %04X\n", i, strtol(token, NULL, 16));
                i++;
            } else if(token[0] == 'A'){
                token++;
                enderecosSub[j] = strtol(token, NULL, 16);
                // printf("token: %s\n", token);
                // printf("SUB%02d: %04X\n", j, strtol(token, NULL, 16));
                j++;
                
            } else {
                token++;
            }
            // printf("%s /%s\n", inst, token);
        } else {
            token++;
            enderecosRot[k] = strtol(token, NULL, 16);
            // printf("token: %s\n", token);
            // printf("VARIAVEL%02d: %04X\n", k, strtol(token, NULL, 16));
            k++;
        }

        end = newEnd;
    }

    rewind(input);
    
    end =0xFFFF + 2;
    
    // printf("antes da ordenacao:\n");
    for(int a=0; a<i; a++){
        // printf("JUMP%02X: %04X\n", a, enderecosJump[a]);
    }
    for(int a=0; a<j; a++){
        // printf("SUB%02X: %04X\n", a, enderecosSub[a]);
    }
    for(int a=0; a<k; a++){
        // printf("ROT%02X: %04X\n", a, enderecosRot[a]);
    }
    
    qsort(enderecosJump, i, sizeof(int), comp);
    qsort(enderecosRot, j, sizeof(int), comp);
    qsort(enderecosSub, k, sizeof(int), comp);
    
    // printf("depois da ordenacao:\n");
    for(int a=0; a<i; a++){
        // printf("JUMP%02X: %04X\n", a, enderecosJump[a]);
    }
    for(int a=0; a<j; a++){
        // printf("SUB%02X: %04X\n", a, enderecosSub[a]);
    }
    for(int a=0; a<k; a++){
        // printf("ROT%02X: %04X\n", a, enderecosRot[a]);
    }


    // printf("\n\n");
    
    
    while(fgets(buffer, 100, input)){
        token = strtok(buffer, " ");
        
        newEnd = strtol(token, NULL, 16);
        
        if(newEnd-end> 2 || end-newEnd >2){
            printf("@ /%04X\n",newEnd);
        }

        // se estiver na área de dados
        if(newEnd>0x02FF){
            if(findRot(strtol(token, NULL, 16), i, j, k, enderecosJump, enderecosRot, enderecosSub)== -1){
                printf("   ");
            };
            token = strtok(NULL, "\n");
            printf("K /%s\n",token);
        } else {
            if(findRot(strtol(token, NULL, 16), i, j, k, enderecosJump, enderecosRot, enderecosSub)== -1) {
                printf("        ");
            }
            token = strtok(NULL, "\n");
            inst = getInstruction(token);
            token++;

            printf("%s ", inst, token);
            if(findRot(strtol(token, NULL, 16), i, j, k, enderecosJump, enderecosRot, enderecosSub) == -1){
                printf("/%s", token);    
            }
            printf("\n");

        }

        end = newEnd;
    }
}