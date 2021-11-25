#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#define N 3

int main(){

    char importantWords[N][100] = {"jvn", "ogmj","kjgegov"};
    char placerPart[1000]= "the person who shot the victim was $ he lives in $  and has a blue $";

    int len;
    /*for (int i = 0 ; i < 3; ++i) {
        for (int j = 0 ; importantWords[i][j] != NULL ; ++j) {
            printf("%c",importantWords[i][j]);
        }
        printf("\n");
    }
*/
    char finalText[1000];
    int k = 0, l = 0;
    for (int i = 0 ; placerPart[i] != NULL ; ++i) {
        if (placerPart[i] != '$'){
            finalText[k++] = placerPart[i];
        }
        else if (placerPart[i] == '$'){
            for (int j = 0 ; importantWords[l][j] != NULL && l < N ; ++j) {
                finalText[k++] = importantWords[l][j];
            }
            l++;
        }
    }
    finalText[k] = '\0';

    /*for (int i = 0 ; finalText[i] != NULL ; ++i) {
        printf("%c" ,finalText[i]);
    }*/

    FILE *filePointer;
    filePointer = fopen("placerDecryptedText.txt","w");
    if (!filePointer){
        printf("Failed to open the file!");
        exit(0);
    }
    for (int i = 0 ; finalText[i] != NULL ; ++i) {
        fprintf(filePointer,"%c", finalText[i]);
    }
    fclose(filePointer);

}