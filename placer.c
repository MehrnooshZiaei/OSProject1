#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#define PARENT_WITH_PLACER "/tmp/parentWithPlacer"
#define FINDER_WITH_PLACER "/tmp/finderWithPlacer"
#define RESULT "/tmp/result"

int main(){

    /*
    char importantWords[N][100] = {"jvn", "ogmj","kjgegov"};
    char placerPart[1000]= "the person who shot the victim was $ he lives in $  and has a blue $";
    */
   //char importantWords[N][100];
   char placerPart[1000];
   char impWord[1000];

   //pipe between finder and placer - fdFP
    //char *finderWithPlacer = "/tmp/finderWithPlacer";
    //mkfifo(finderWithPlacer, 0666);
    //pipe result - fdR
    //char *result = "/tmp/result";

    int fdFP, fdPP, fdR;

    fdFP = open(FINDER_WITH_PLACER,O_RDONLY);
    int en = read(fdFP,impWord,sizeof(impWord));
    impWord[en] = '\0';
    close(fdFP);

    //printf("%s\n",impWord);

    int count = 0;
    for(int i = 0 ; impWord[i] != NULL; i++){
        if (impWord[i] == ',')
        {
            count++;
        }
        
    }

    char importantWords[count+1][100];

    int temp = 0, j = 0;
    for (int i = 0 ; i < count+1 ; ++i) {
        for (j = 0; impWord[temp] != ',' && impWord[temp] != NULL ; ++j,++temp) {
            importantWords[i][j] = impWord[temp];
            //printf("%c\n",importantWords[i][j]);
        }
        temp++;
        importantWords[i][j] = '\0';
    }

    /*for(int i = 0; i < count+1 ; i++){
        for(int j = 0; j < strlen(importantWords[i]) ; j++){
            printf("%c",importantWords[i][j]);
        }
        printf("\n");
    }*/

    fdPP = open(PARENT_WITH_PLACER,O_RDONLY);
    int end = read(fdPP, placerPart,sizeof(placerPart));
    placerPart[end] = '\0';
    //int len;
    /*for (int i = 0 ; i < 3; ++i) {
        for (int j = 0 ; importantWords[i][j] != NULL ; ++j) {
            printf("%c",importantWords[i][j]);
        }
        printf("\n");
    }
*/

    //printf("%s\n",placerPart);

    char finalText[1000];
    int k = 0, l = 0;
    for (int i = 0 ; placerPart[i] != NULL ; ++i) {
        if (placerPart[i] != '$'){
            finalText[k++] = placerPart[i];
        }
        else if (placerPart[i] == '$'){
            for (int j = 0 ; importantWords[l][j] != NULL && l < count+1 ; ++j) {
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

    fdR = open(RESULT,O_WRONLY);
    write(fdR,finalText,strlen(finalText)+1);
    close(fdR);
}