#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#define PARENT_WITH_DECODER "/tmp/parentWithDecoder"
#define PARENT_WITH_FINDER "/tmp/parentWithFinder"
#define PARENT_WITH_PLACER "/tmp/parentWithPlacer"
#define DECODER_WITH_FINDER "/tmp/decoderWithFinder"
#define FINDER_WITH_PLACER "/tmp/finderWithPlacer"
#define RESULT "/tmp/result"


int main(){

    //pipe between parent and decoder process - fdPD
    //char *parentWithDecoder = "/tmp/parentWithDecoder";
    mkfifo(PARENT_WITH_DECODER, 0666);
    //pipe between parent and finder process - fdPF
    //char *parentWithFinder = "/tmp/parentWithFinder";
    mkfifo(PARENT_WITH_FINDER, 0666);
    //pipe between parent and placer process - fdPP
    //char *parentWithPlacer = "/tmp/parentWithPlacer";
    mknod(PARENT_WITH_PLACER , 0666,0);
    //pipe between decoder and finder - fdDF
    //char *decoderWithFinder = "/tmp/decoderWithFinder";
    mknod(DECODER_WITH_FINDER, 0666,0);
    //pipe between finder and placer - fdFP
    //char *finderWithPlacer = "/tmp/finderWithPlacer";
    mkfifo(FINDER_WITH_PLACER, 0666);
    //pipe result - fdR
    //char *result = "/tmp/result";
    mkfifo(RESULT, 0666);

    int fdPD, fdPF, fdPP, fdDF, fdFP, fdR;

    //Biderectional pipe for placer process [0-read,1-write]
    int fd1[2];
	int fd2[2];

    //Create two-way pips in order to exchange information between processe main and C 
	pipe(fd1);
	pipe(fd2);
	

    /*fdPD = open(parentWithDecoder,O_WRONLY);
    fdPF = open(parentWithDecoder, O_WRONLY);
    fdPP = open(parentWithPlacer, O_WRONLY);*/


    char *args[] = {"./decoder","./finder", "./placer",NULL};
    char encryptedText[10000];

    //create process A
    if (fork() == 0){
        
        //Decoder
        execvp(args[0],args);
        exit(0);
    }
    //create process B
    else if(fork() == 0){
        
        //Finder
        execvp(args[1],args);
        exit(0);
    }
    //create process C
    else if (fork() == 0){
        
        //Placer
        execvp(args[2], args);
        sleep(1);
        exit(0);
        /*
        char finalText[1000];

        fdR = open(RESULT,O_RDONLY);
        int last = read(fdR,finalText,sizeof(finalText));
        finalText[last]='\0';
        close(fdR);

        printf("%s\n",finalText);

        close(fd2[0]);
		write(fd2[1] , finalText , strlen(finalText)+1);
        */

        /*

        char finalText[1000];
        fdR = open(RESULT,O_RDONLY);
        int last = read(fdR,finalText,sizeof(finalText));
        finalText[last]='\0';

        close(fd2[0]);
		write(fd2[1] , finalText , strlen(finalText)+1);*/
    
        //exit(0);
    }

    /*
The input can have new line and you should end 
the input by a semi-colon(;) when you use this code
*/
    //char encryptedText[10000];

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
    

    fdPD = open(PARENT_WITH_DECODER,O_WRONLY);
    write(fdPD, decoderPart, strlen(decoderPart)+1);
    close(fdPD);

    fdPF = open(PARENT_WITH_FINDER, O_WRONLY);
    write(fdPF, finderPart, strlen(finderPart)+1);
    close(fdPF);

    fdPP = open(PARENT_WITH_PLACER,O_WRONLY);
    write(fdPP,placerPart,strlen(placerPart)+1);
    close(fdPP);


    char finalText[1000];
    fdR = open(RESULT,O_RDONLY);
    int l = read(fdR,finalText,sizeof(finalText));
    finalText[l] = '\0';
    close(fdR);

    for(int i = 0; finalText[i] != NULL; i++){
        printf("%c",finalText[i]);
    } 
    
    printf("\n");
	printf("End of the main process.\n");


    /*close(fd1[0]);
	write(fd1[1] , placerPart ,strlen(placerPart)+1);*/

    /*fdPP = open(PARENT_WITH_PLACER,O_WRONLY);
    write(fdPP,placerPart,strlen(placerPart)+1);*/

    //Send placer part to process C
    
	/*close(fd1[0]);
	write(fd1[1] , placerPart ,sizeof(placerPart));

    char finalText[1000];

    close(fd2[1]);
	int end = read(fd2[0] , finalText , sizeof(finalText));
    finalText[end] = '\0';*/

    /*char finalText[1000];

    for(int i = 0; finalText[i] != NULL ; i++){
        printf("%c",finalText[i]);
    }*/
    //wait(NULL);

//error
    /*char finalResult[1000];

    close(fd2[1]);
	int end = read(fd2[0] , finalResult, sizeof(finalResult));
    finalResult[end] = '\0';

    for(int i = 0; finalResult[i] != NULL ; i++){
        printf("%c",finalResult[i]);
    }

    printf("\n");
	printf("End of the main process.\n");*/

//TRUE
/*
    char finalText[1000];
    fdR = open(RESULT,O_RDONLY);
    int l = read(fdR,finalText,sizeof(finalText));
    finalText[l] = '\0';
    close(fdR);

    for(int i = 0; finalText[i] != NULL; i++){
        printf("%c",finalText[i]);
    } 
    printf("\n");
	printf("End main process.\n");

*/



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
    printf("decoder : %s\n",decoderPart);
    printf("finder : %s\n",finderPart);
    printf("placer : %s\n",placerPart);
    */

}