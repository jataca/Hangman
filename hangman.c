#include <stdio.h>
#include <stdlib.h>
#include "stages.h"
#include <string.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

char * openFile(){
    srand(time(NULL));
    char buff[255];
    FILE *fp;
    fp = fopen("/usr/share/dict/words", "r");
    fscanf(fp, "%s", buff);
    char correctWord[255];

    int count = 0;
    while (fscanf(fp, "%s", buff) != EOF){
        count++;
        int randomNumber = rand() % count;
        if (randomNumber == 0)
            strcpy(correctWord, buff);
    }
    fclose(fp);
    size_t cwLen = strlen(correctWord);

    char * pointer = &correctWord[0];

    size_t pLen = strlen(pointer);

    return pointer;
}

bool displayWord(char charArray[], size_t len, char lettersGuessedCorrectly[]){
    bool didPlayerWin = true;
    for (int i = 0; i < len; i++){
        bool displayLetter = false;
        for (int j = 0; j < 27; j++){
            if (charArray[i] == lettersGuessedCorrectly[j])
                displayLetter = true;
        }
        if (displayLetter == true)
            printf("%c", charArray[i]);
        else{
            didPlayerWin = false;
            printf("*");
        }
    }
    puts("\n");
    return false;
}

bool checkLetter(char charArray[], size_t len, char guessedLetter[]){
    for (int i = 0; i < len; i++){
        if (guessedLetter[0] == charArray[i]){
            return true;
        }
    }
    return false;
}

bool playGame(char charArray[], size_t len){
    char lettersGuessedCorrectly[27] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',};
    char guessedLetter[2];
    int count = 0;
    int roundNumber = 1;
    while(roundNumber < 8){
        bool didPlayerWin = displayWord(charArray, len, lettersGuessedCorrectly);
        switch(roundNumber){
            case 1:
                drawStage1();
                break;
            case 2:
                drawStage2();
                break;
            case 3:
                drawStage3();
                break;
            case 4:
                drawStage4();
                break;
            case 5:
                drawStage5();
                break;
            case 6:
                drawStage6();
                break;
            case 7:
                drawStage7();
                puts("Last Chance!\n");
                break;
        }
        if (didPlayerWin == true)
            return true;

        scanf("%s", guessedLetter);
        bool guess = checkLetter(charArray, len, guessedLetter);
        if (guess == false){
            roundNumber++;
        }
        else{
            lettersGuessedCorrectly[count] = guessedLetter[0];
            count++;
        }
        if (didPlayerWin == true)
            return true;
    }

    printf("The word was %s\n", charArray);
    return false;
}

int main(){
    bool didPlayerWin = false;
    char * newWord = openFile();
    size_t len = strlen(newWord);
    char charArray[len];
    strcpy(charArray, newWord);
    didPlayerWin = playGame(charArray, len);
    if (didPlayerWin == true)
        puts("CONGRATULATIONS!!! YOU WON!!!!!\n");
    else
        puts("Sorry, you lost");
    return 0;
}
