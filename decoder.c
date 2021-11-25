#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


void removeSpaces(char *str){
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ' && str[i] != '\n')
            str[count++] = str[i];
    str[count] = '\0';
}

//when you get input, the semi-colon should be entered after Enter
//Enter + semicolon to make a file
int main(){

    char decoderPart[10000] = "sgskldjghssldkjghdsgdg dgjghdglflkgjfbghdsfda \ndhgdbdlskjhgbdglhdsbg";
    /*printf("Enter the encrypted text (press ';' at the end of text)\n");
    scanf("%[^;]s", decoderPart);
    //printf("Before : %s\n",decoderPart);*/



    removeSpaces(decoderPart);
    int len = 0;
    for (int k = 0 ; decoderPart[k] != NULL ; ++k) {
       len++;
    }
    //printf("%d", len);
    for (int j = 0 ; j < len ; ++j) {
        if (isupper(decoderPart[j])){
            //decoderPart[j] = char(int(decoderPart[j]-65+3)%26 +65);
            int temp = decoderPart[j] - '0';
            temp+=48;
            temp = (temp - 65 + 3)%26 +65;
            temp -= 48;
            decoderPart[j] = temp + '0';
        }
        else{
            //decoderPart[j] = char(int(decoderPart[j]-97+3)%26 + 97);
            int temp = decoderPart[j] - '0';
            temp +=48;
            temp = (temp - 97 + 3)%26 +97;
            temp -=48;
            decoderPart[j] = temp + '0';
        }
    }
    //printf("After : %s\n",decoderPart);
    
    FILE *filePointer;
    filePointer = fopen("decoderDecrypt.txt","w");

    if (!filePointer){
        printf("Failed to open the file!");
        exit(0);
    }
    for (int k = 0; decoderPart[k] != NULL ; k++){
        fprintf(filePointer,"%c",decoderPart[k]);
    }
    
    fclose(filePointer);

}