#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

/*
The input can not have new line when you use this commented code
*/
    /*char encryptedText[10000];
    fgets(encryptedText, 10000, stdin);

    char *decoderPart = NULL;
    char *finderPart = NULL;
    char *placerPart = NULL;

    char *token = strtok(encryptedText,"###");

    decoderPart = token;
    
    int i = 0;
    while (token != NULL){
    	if ( i == 1 ){finderPart = token; i++;}
 	    else if ( i == 3) {placerPart = token;i++;}
 	    printf("%s\n",token);
 	    i++;
 	    token = strtok(NULL,"###");
    }*/
/*
The input can have new line and you should end 
the input by a semi-colon(;) when you use this code
*/
    char encryptedText[10000];

    printf("Enter the encrypted text (press ';' at the end of text)\n");
    scanf("%[^;]s", encryptedText);

    //printf("%s\n",encryptedText);

    char *decoderPart = NULL;
    char *finderPart = NULL;
    char *placerPart = NULL;

    char *token = strtok(encryptedText,"###");
    decoderPart = token;

    int i = 0;
    while (token != NULL){
        if ( i == 1 ){finderPart = token; i++;}
        else if ( i == 3) {placerPart = token;i++;}
        //printf("%s\n",token);
        i++;
        token = strtok(NULL,"###");
    }

    /*
    printf("decoder : %s\n",decoderPart);
    printf("finder : %s\n",finderPart);
    printf("placer : %s\n",placerPart);
    */

}