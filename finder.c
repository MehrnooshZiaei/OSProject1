#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main(){

    char decoderDecrypt[1000] = "vjvnogmjkvvognmjkgvjgjgjmjkgjoionjmiejkgvigdgkjgegovnmkjegjokgvej";
    char finderPart[1000]= "1 3$4 4$45 7$";

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

    for (int i = 0 ; i < countSign ; ++i) {
        for (int j = 0 ; j < importantNums[i][1] ; ++j) {
            fprintf(filePointer,"%c",importantWords[i][j]);
        }
        fprintf(filePointer,"\n");
    }
    fclose(filePointer);

}