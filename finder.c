#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#define PARENT_WITH_FINDER "/tmp/parentWithFinder"
#define DECODER_WITH_FINDER "/tmp/decoderWithFinder"
#define FINDER_WITH_PLACER "/tmp/finderWithPlacer"

int main(){

    //pipe between parent and finder process - fdPF
    //char *parentWithFinder = "/tmp/parentWithFinder";
    //mkfifo(parentWithFinder, 0666);
    //pipe between decoder and finder - fdDF
    //char *decoderWithFinder = "/tmp/decoderWithFinder";
    //mkfifo(decoderWithFinder, 0666);
    //pipe between finder and placer - fdFP
    //char *finderWithPlacer = "/tmp/finderWithPlacer";
    //mkfifo(finderWithPlacer, 0666);

    char decoderDecrypt[1000], finderPart[1000];
    int fdPF, fdDF, fdFP;

    fdPF = open(PARENT_WITH_FINDER,O_RDONLY);
    int last1 = read(fdPF,finderPart,sizeof(finderPart));
    finderPart[last1] = '\0';
    close(fdPF);

    fdDF = open(DECODER_WITH_FINDER, O_RDONLY);
    int last2 = read(fdDF,decoderDecrypt,sizeof(decoderDecrypt));
    decoderDecrypt[last2] = '\0';
    close(fdDF);

    //printf("%s\n",finderPart);
    //printf("%s\n",decoderDecrypt);

    /*char decoderDecrypt[1000] = "vjvnogmjkvvognmjkgvjgjgjmjkgjoionjmiejkgvigdgkjgegovnmkjegjokgvej";
    char finderPart[1000]= "1 3$4 4$45 7$";*/

    int countSign = 0;
    for (int i = 0 ; finderPart[i] != NULL ; ++i) {
        if(finderPart[i] == '$')countSign++;
    }

    //printf("%d",countSign);

    char *ptr = finderPart;

    int importantNums[countSign][2];

    int val = 0;
    int counter = 0;
    while (*ptr){
        if(isdigit(*ptr)){
            val = (int)strtol(ptr,&ptr,10);
            counter++;
            //printf("%d\n",val);
        }else{
            ptr++;
        }
        if(counter%2 == 1) importantNums[((counter+1)/2)-1][0]=val;
        else importantNums[(counter/2)-1][1] = val;
    }

    /*for (int i = 0 ; i < countSign ; ++i) {
        for (int j = 0 ; j < 2 ; ++j) {
            printf("%d ", importantNums[i][j]);
        }
        printf("\n");
    }*/

    char importantWords[countSign][100];

    for (int i = 0 ;  i < countSign ; ++i) {
        int k = 0;
        int len = importantNums[i][0]+importantNums[i][1];
        for (int j = importantNums[i][0] ; j < len ; ++j) {
            //k++;
            importantWords[i][k++] = decoderDecrypt[j];
            //printf("%c\n",importantWords[i][k]);
        }
        importantWords[i][k] = '\0';
    }

    char importantWord[1000];
    int temp = 0;
    for(int i = 0 ; i < countSign ; i++){
        for(int j = 0; importantWords[i][j] != NULL;j++){
            importantWord[temp++] = importantWords[i][j];
        }
        if (i != countSign - 1){
            importantWord[temp++] = ',';
        }
    }
    importantWord[temp] = '\0';

    //printf("%s\n",importantWord);

    /*for (int i = 0 ; i < countSign ; ++i) {
        //j < importantNums[i][1]
        for (int j = 0 ; importantWord[i][j] != NULL ; ++j) {
            printf("%c",imsportantWords[i][j]);
        }
        printf("\n");
    }*/

    FILE *filePointer;
    filePointer = fopen("finderImportantWords.txt","w");
    if (!filePointer){
        printf("Failed to open the file!");
        exit(0);
    }
    for(int i = 0; importantWord[i] != NULL ; i++){
        if (importantWord[i] != ','){
            fprintf(filePointer,"%c",importantWord[i]);
        }
        else if (importantWord[i] == ','){
            fprintf(filePointer,"\n",importantWord[i]);
        }
        
    }
    /*for (int i = 0 ; i < countSign ; ++i) {
        for (int j = 0 ; j < importantNums[i][1] ; ++j) {
            fprintf(filePointer,"%c",importantWords[i][j]);
        }
        fprintf(filePointer,"\n");
    }*/
    fclose(filePointer);

    fdFP = open(FINDER_WITH_PLACER,O_WRONLY);
    write(fdFP, importantWord,strlen(importantWord)+1);
    close(fdFP);


}