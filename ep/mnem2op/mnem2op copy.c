#include<stdio.h>
#include<string.h>

char* getInstruction(char* s, char* arg) {
    if(s == "JP") return "0";
    if(s == "JZ") return "1";
    if(s == "JN") return "2";
    if(s == "LV") return "3";
    if(s == "AD") return "4";
    if(s == "SB") return "5";
    if(s == "ML") return "6";
    if(s == "DV") return "7";
    if(s == "LD") return "8";
    if(s == "MM") return "9";
    if(s == "SC") return "A";
    if(s == "RS") return "B";
    if(s == "HM") return "C";
    if(s == "GD") return "D";
    if(s == "PD") return "E";
    if(s == "SO") return "F";
}

int getNum(char* s) {
    if(s[0] == '=') {
        s++;
        printf("%s", s);
    } else if(s[0] == '/') {
        
    }
}

int main(int argc, char* argv []){
    int end =0;
    char* x;
    char op[4];
    char code[3];
    char buffer[100];
    char line[5];
    FILE* input;

    input = fopen(argv[1], "r");


    while(fgets(buffer, 100,input)){
        if(buffer[0] == '@'){
            // fscanf(input,"%s %s", &op, &x);
            printf("%s %s", op, x);
            end = getNum(x);
        } else if (buffer[0] == 'K') {

        }
    }



    fscanf(input, "%s ", &code); // captura o mnemonico

    // line = getInstruction(code, op);

    printf("%04X ");

    printf("%s\n", buffer);
    fgets(buffer, 100,input);

    printf("%s", &buffer);

}