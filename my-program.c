#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
char c;
char token[1024];
int num;
int symbol;
FILE *fp;

int main(int argc, char *argv[]){
    fp = fopen(argv[1], "r");
    while(1){
        symbol = -1;
        getC();
        if(c == EOF)
            break;
        clearToken();
        while(isSpace()) getC();
        if(isalpha(c)){
            while(isalpha(c)||isdigit(c)){
                catToken();
                getC();
            }
            retract();
            int resultValue = reserver();
            if(resultValue == 0)
                symbol = 0;
            else
                symbol = resultValue;
        }
        else if(isdigit(c)){
            while(isdigit(c)){
                catToken();
                getC();
            }
            retract();
            num = transNum();
            symbol = 7;
        }
        else if(isColon()){
            getC();
            if(isEqu())
                symbol = 14;
            else{
                retract();
                symbol = 8;
            }
        }
        else if(isPlus()){
            symbol = 9;
        }
        else if(isStar()){
            symbol = 10;
        }
        else if(isLpar()){
            symbol = 12;
        }
        else if(isRpar()){
            symbol = 13;
        }
        else if(isComma()){
            symbol = 11;
        }
        else{
            myError();
        }
        switch(symbol){
            case 0 : printf("Ident(%s)\n", token); break;
            case 1 : printf("Begin\n"); break;
            case 2 : printf("End\n"); break;
            case 3 : printf("For\n"); break;
            case 4 : printf("If\n"); break;
            case 5 : printf("Then\n"); break;
            case 6 : printf("Else\n"); break;
            case 7 : printf("Int(%d)\n", num); break;
            case 8 : printf("Colon\n"); break;
            case 9 : printf("Plus\n"); break;
            case 10 : printf("Star\n"); break;
            case 11 : printf("Comma\n"); break;
            case 12 : printf("LParenthesis\n"); break;
            case 13 : printf("RParenthesis\n"); break;
            case 14 : printf("Assign\n"); break;
        }
        if(c == EOF)
            break;
    }
    fclose(fp);
    return 0;
}

void getC(){
    c = fgetc(fp);
    return;
}

void clearToken(){
    memset(token,'\0',sizeof(token));
    return;
}

int isColon(){
    if(c == ':')
        return 1;
    return 0;
}

int isComma(){
    if(c == ',')
        return 1;
    return 0;
}

int isEqu(){
    if(c == '=')
        return 1;
    return 0;
}

int isPlus(){
    if(c == '+')
        return 1;
    return 0;
}

int isStar(){
    if(c == '*')
        return 1;
    return 0;
}

int isLpar(){
    if(c == '(')
        return 1;
    return 0;
}

int isRpar(){
    if(c == ')')
        return 1;
    return 0;
}

void catToken(){
    int len = strlen(token);
    token[len] = c;
    return;
}

void retract(){
    fseek(fp,-1,SEEK_CUR);
    return;
}

int reserver(){
    if(strcmp(token,"BEGIN") == 0)
        return 1;
    else if(strcmp(token, "END") == 0)
        return 2;
    else if(strcmp(token, "FOR") == 0)
        return 3;
    else if(strcmp(token, "IF") == 0)
        return 4;
    else if(strcmp(token, "THEN") == 0)
        return 5;
    else if(strcmp(token, "ELSE") == 0)
        return 6;
    else
        return 0;
}

int transNum(){
    int result = atoi(token);
    return result;
}

void myError(){
    //printf("%d\n", strlen(token));
    if(strlen(token) > 0 || (int)c != -1)
        printf("Unknown\n");
    fclose(fp);
    exit(0);
}

int isSpace(){
    if(c == ' ' || c == '\t' || c == '\n' || c == '\r')
        return 1;
    return 0;
}
