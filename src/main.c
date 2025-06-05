/***C Programming Quiz Game***/

#include "include/main.h"


#define ITL     "\e[3m"
#define RED     "\e[31m"
#define GREEN   "\e[32m"
#define YELLOW  "\e[33m"
#define WHITE   "\e[37m"
#define BOLD_ON "\e[1m"
#define BLUE    "\e[96m"
#define OFF     "\e[m"

#define maxBufferQuestion   200
#define maxBufferAnswer     20
#define maxNumber           10   
#define maxDiff             3


struct QnA {
    
    char Questions[maxDiff][maxNumber][maxBufferQuestion];
    char AnswerKey[maxDiff][maxNumber][maxBufferAnswer];
    int numberArray[maxDiff][maxNumber];
    int flag;
    int optionDifficulty;
    int optionSize;
    int optionRandom;
    int choice;
    int numTry;
    int randomSize[maxDiff];
    
};

/********* struct manipulation function *********/
void initQuizQuestions(struct QnA *quiz);
void initArray(struct QnA *quiz);


/************ Utility func prototype ************/
void updateArray(struct QnA **quiz, int pos);
int charToInt(char ch);


/*********** Main Menu func prototype ***********/
void intro();
void clear();
int mainMenu();
void game(struct QnA *quiz);
void mechanicsMenu();
void settingMenu(struct QnA *quiz);
void aboutMenu();



int main() {
    
    clear();


    /*initialize questions once*/
    struct QnA quiz;
    initQuizQuestions(&quiz);
    initArray(&quiz);
    
    quiz.choice = 1;
    quiz.flag = 4;
    quiz.optionDifficulty = 0;
    quiz.optionSize = 10;
    quiz.numTry = 3;

    

    char temp[50];

    intro();
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    
    
    do {
        
        quiz.choice = mainMenu();
        
        switch (quiz.choice) {
            
            case 1: {
              
                game(&quiz);
                
                /*Reset values after game*/
                
                initArray(&quiz);
                quiz.flag = 4;
                quiz.optionDifficulty = 0;
                quiz.optionSize = 10;
                quiz.optionRandom = 0;
                
                break;
                
            }
            case 2: {
                
                clear();
                mechanicsMenu();
                break;
                
            }
            case 3: {
                
                clear();
                settingMenu(&quiz);
                break;
                
            }
            case 4: {
                
                clear();
                aboutMenu();
                break;
                
            }
            default: {
                
                clear();
                printf(BOLD_ON BLUE "\n\n\t\tTHANK YOU FOR PLAYING! SEE YOU NEXT TIME!"OFF);
                getchar();
                return 0;
                
            }
            
        }
        
    } while (quiz.choice > 0 || quiz.choice < 4);
    
    return 0;
}


/**************** DEFINITIONS ******************/


void game(struct QnA *quiz) {
    
    clear();
    srand(time(NULL));
    
    
    int randScore = 0;
    
    int points[3] = {0, 0, 0};
    int maxScore = quiz->optionSize;
    int random = 0;
    int choice = 1;
    int pos = 0;

    char tmpLine[50];
    char answer[50];
    
    // assign 30 for full random
    if (quiz->optionRandom == 1) {
        
        maxScore = 30;
        
    }
    
    // check tries
    if (quiz->numTry == 0) {
        
        printf(BOLD_ON RED "\n\n\t\tYOU HAVE EXCEEDED YOUR NUMBER OF ATTEMPTS! EXIT APP TO TRY AGAIN!\n\n\t\t" OFF );
        printf(ITL"Enter any to exit...");
        fgets (tmpLine, sizeof(tmpLine), stdin);
        return;
        
    }
    
    
    
    while ( quiz->optionDifficulty < 4 && choice == 1 ) {
        
        
        if (quiz->optionRandom == 1) {
            
            printf (BOLD_ON BLUE "\t\t\t\t\t\tRANDOM MODE"OFF);
            
        }
        
        printf (BOLD_ON GREEN"\n\n\t\t\t\t\t\tTries: %d\t\tPoints: %d\n"OFF,quiz->numTry, randScore);
        
        for ( int number = 1 ; number <= maxScore ; number++ ) {
            
            // randomize questions
            
            if (maxScore < 30) {
                
                pos = (rand() % quiz->optionSize);
                random = quiz->numberArray[quiz->optionDifficulty][pos];
                
            }
            else {
                
                R1:
                quiz->optionDifficulty = (rand() % 3);
                
                if (quiz->randomSize[quiz->optionDifficulty] == 0) {
                    
                    // prevent access or randomization error
                    goto R1;
                    
                }
                
                pos = (rand() % quiz->randomSize[quiz->optionDifficulty]);
                random = quiz->numberArray[quiz->optionDifficulty][pos];
                
                
                
            }
            
            
            
            
            QUIZ:
            switch (quiz->optionDifficulty) {
                
                case 0: {
                    
                    printf (BOLD_ON BLUE "\n\n\t\t=============================== EASY ROUND ================================\n"OFF);
                    break;
                    
                }
                case 1: {
                    
                    printf (BOLD_ON BLUE "\n\n\t\t============================= MODERATE ROUND ==============================\n"OFF);
                    break;
                    
                }
                default: {
                    
                    printf (BOLD_ON BLUE "\n\n\t\t=============================== HARD ROUND ================================\n"OFF);
                    break;
                    
                }
                
            }
            
            printf (YELLOW BOLD_ON"\n\n\t\tProblem Number %d: "OFF, number);
            printf(BOLD_ON BLUE"%s"OFF, quiz->Questions[quiz->optionDifficulty][random]);
            
            
            printf (BOLD_ON RED"\n\n\t\tE. Exit Game" OFF);
            printf ("\n\t\tAnswer: ");
            fgets(answer, sizeof(answer), stdin);
            answer[strcspn(answer, "\n")] = 0;
            
            
            
            clear();
            
            
            
            if (strlen(answer) > 1 || (toupper(answer[0]) < 'A' || toupper(answer[0]) > 'E')) {
                
                printf(RED BOLD_ON"\n\n\t\tInvalid answer, please answer again.\n");
                goto QUIZ;
                
            }
            else if(toupper(answer[0]) == 'E') {
                
                quiz->numTry--;
                return;
                
            }
            else if (toupper(answer[0]) == quiz->AnswerKey[quiz->optionDifficulty][random][0]) {
                
                if (quiz->optionRandom == 1) {
                    
                    randScore++;
                    printf (BOLD_ON BLUE "\t\t\t\t\t\tRANDOM MODE"OFF);
                    printf (GREEN BOLD_ON "\n\n\t\tCorrect! +1\t\t\tTries: %d\t\t\tPoints: %d\n"OFF,quiz->numTry, randScore);
                    
                }
                else {
                    
                    points[quiz->optionDifficulty]++;
                    printf (GREEN BOLD_ON "\n\n\t\tCorrect! +1\t\t\tTries: %d\t\t\tPoints: %d\n"OFF,quiz->numTry, points[quiz->optionDifficulty]);
                    
                }
                
            }
            else {
                
                if (quiz->optionRandom == 1) {
                    
                    printf (BOLD_ON BLUE "\t\t\t\t\t\tRANDOM MODE"OFF);
                    printf (RED BOLD_ON "\n\n\t\tIncorrect!"OFF);
                    printf (BOLD_ON GREEN "\t\t\tTries: %d\t\t\tPoints: %d\n"OFF,quiz->numTry, randScore);
                    printf ("\t\tThe correct answer was "BOLD_ON BLUE"%s" OFF, quiz->AnswerKey[quiz->optionDifficulty][random]);
                    
                }
                else {
                    
                    printf (RED BOLD_ON"\n\n\t\tIncorrect!"OFF);
                    printf (BOLD_ON GREEN"\t\t\tTries: %d\t\t\tPoints: %d\n"OFF,quiz->numTry, points[quiz->optionDifficulty]);
                    printf ("\t\tThe correct answer was "BOLD_ON BLUE"%s" OFF, quiz->AnswerKey[quiz->optionDifficulty][random]);
                    
                }
                
                
            }
            
            
            
            // update array and reduce size for randomization
            updateArray(&quiz, pos);
            
            if (quiz->optionRandom != 1) {
                
                quiz->optionSize--;
                
            }
            else {
                
                quiz->randomSize[quiz->optionDifficulty]--;
                
            }
            
            
        }
        
        
        
        if (quiz->optionRandom == 1) {
            
            
            if (randScore < round(maxScore * 0.7)) {
                
                printf (BOLD_ON"\n\n\t\tYour score is %d/%d." RED "You have failed\n\n\t\tExiting..."OFF, randScore, maxScore);
                printf (ITL"\n\t\tEnter any to continue..."OFF);
                fgets (tmpLine, sizeof(tmpLine), stdin);
                quiz->numTry--;
                return;                
                
            }
            else {
                
                printf (BOLD_ON"\n\n\t\tYour score is %d/%d." GREEN " You have passed! Congratulations"OFF, randScore, maxScore);
                printf("\n\n\t\tYou have successfully completed the quiz!\n\n");
                printf(OFF ITL"\n\t\tEnter to return to main menu."OFF);
                
                fgets (tmpLine, sizeof(tmpLine), stdin);
                quiz->numTry--;
                return;
                
            }
            
            
        }
        
        
        
        
        // check for passing score
        if (points[quiz->optionDifficulty] < round(maxScore * 0.7)) {
            
            printf (BOLD_ON"\n\n\t\tYour score is %d/%d." RED "You have failed\n\n\t\tExiting..."OFF, points[quiz->optionDifficulty], maxScore);
            printf (ITL"\n\t\tEnter any to continue..."OFF);
            fgets (tmpLine, sizeof(tmpLine), stdin);
            quiz->numTry--;
            return;
            
        }
        else {
            
            printf (BOLD_ON"\n\n\t\tYour score is %d/%d." GREEN " You have passed! Congratulations"OFF, points[quiz->optionDifficulty], maxScore);
            
        }
        
        
        // continue difficulty
        if (quiz->flag > 0 & quiz->flag < 4 ){
            
            printf("\n\n\t\tYou have successfully completed the quiz!\n\n");
            printf(OFF ITL"\n\t\tEnter to return to main menu."OFF);
            
            fgets (tmpLine, sizeof(tmpLine), stdin);
            quiz->numTry--;
            return;
            
        }
        else if (quiz->flag == 4) {
            
            switch (quiz->optionDifficulty) {
                
                case 0: {
                    
                    C0:
                    printf("\n\n\t\tProceed to Moderate Difficulty?\n\n\t\t[1] YES\n\t\t[2] NO\n\t\tSelect [1,2]: ");
                    fgets (tmpLine, sizeof(tmpLine), stdin);
                    tmpLine[strcspn(tmpLine, "\n")] = 0;
                    
                    if (strlen(tmpLine) > 1 || tmpLine[0] < '1' || tmpLine[0] > '2' || tmpLine[0] == ' '|| tmpLine[0] == '\0') {
                        
                        clear();
                        printf(BOLD_ON RED"\n\n\t\tInvalid selection.\n\n"OFF);
                        goto C0;
                        
                    }
                    
                    break;
                    
                }
                case 1: {
                    
                    C1:
                    printf("\n\n\t\tProceed to Hard Difficulty?\n\n\t\t[1] YES\n\t\t[2] NO\n\t\tSelect [1,2]: ");
                    fgets (tmpLine, sizeof(tmpLine), stdin);
                    tmpLine[strcspn(tmpLine, "\n")] = 0;
                    
                    if (strlen(tmpLine) > 1 || tmpLine[0] < '1' || tmpLine[0] > '2' || tmpLine[0] == ' '|| tmpLine[0] == '\0') {
                        
                        clear();
                        printf(BOLD_ON RED"\n\n\t\tInvalid selection.\n\n"OFF);
                        goto C1;
                        
                    }
                    
                    break;
                    
                }
                default: {
                    
                    int total = points[0] + points[1] + points[2];
                    printf("\n\n\t\tYou have successfully completed the quiz! Your scores are the following:\n\n");
                    printf("\n\t\tEASY LEVEL: %d/10\n\t\tMODERATE LEVEL: %d/10\n\t\tHARD LEVEL: %d/10\n\t\tTOTAL POINTS: %d/30\n\n", points[0], points[1], points[2], total);
                    printf(OFF ITL"\n\t\tEnter to return to main menu."OFF);
                    
                    // accept temp line
                    fgets (tmpLine, sizeof(tmpLine), stdin);
                    quiz->numTry--;
                    return;
                    
                }
            }
        }
        
        // update counters
        clear();
        quiz->optionSize = 10;
        quiz->optionDifficulty++;
    }
}

int mainMenu() {
    
    char choice[50] = {'1'};
    
    
    clear();
    MENU:
    
    if ((choice[0] < '1' || choice[0] > '5' ) || strlen(choice) > 1 || choice[0] == ' ') {
        
        printf(BOLD_ON  BLUE"\n\n\n\n\n\n\n              ________  ___  ___  ___  ________          ________  ________  _____ ______   _______                                     ");
        printf(             "\n             |\\   __  \\|\\  \\|\\  \\|\\  \\|\\_____  \\        |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\                 ");
        printf(             "\n             \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\|___/  /|       \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|      ");
        printf(             "\n              \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\   /  / /        \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__       ");
        printf(             "\n               \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ /  /_/__        \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ ");
        printf(             "\n                \\ \\_____  \\ \\_______\\ \\__\\\\________\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\        ");
        printf(             "\n                 \\|___| \\__\\|_______|\\|__|\\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|                    ");
        printf(             "\n                       \\|__|                                                                                                     \n\n"OFF);
        printf(BOLD_ON RED"                        PLEASE SELECT A VALID OPTION\n"OFF);
        
    }
    else {
        
        printf(BOLD_ON  BLUE"\n\n\n\n\n\n\n              ________  ___  ___  ___  ________          ________  ________  _____ ______   _______                                     ");
        printf(             "\n             |\\   __  \\|\\  \\|\\  \\|\\  \\|\\_____  \\        |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\                 ");
        printf(             "\n             \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\|___/  /|       \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|      ");
        printf(             "\n              \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\   /  / /        \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__       ");
        printf(             "\n               \\ \\  \\\\\\  \\ \\  \\\\\\  \\ \\  \\ /  /_/__        \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ ");
        printf(             "\n                 \\ \\_____  \\ \\_______\\ \\__\\\\________\\       \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\        ");
        printf(             "\n                 \\|___| \\__\\|_______|\\|__|\\|_______|        \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|                    ");
        printf(             "\n                       \\|__|                                                                                                     \n\n\n"OFF);
        
    }
    
    printf(BOLD_ON  BLUE"                                   [1] Play game   \n");
    printf(             "                                   [2] Mechanics   \n");
    printf(             "                                   [3] Setting     \n");
    printf(             "                                   [4] About       \n");
    printf(             "                                   [5] Exit        \n"OFF);
    printf(             "                                   Select: ");
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    if ((choice[0] < '1' || choice[0] > '5' ) || strlen(choice) > 1 || choice[0] == ' ') {
        
        clear();
        goto MENU;
        
    }
    
    
    if (choice[0] != '5') {
        
        return charToInt(choice[0]);
        
    }
    
    return 5;
    
}

void updateArray(struct QnA **quiz, int pos) {
    
    if ((*quiz)->optionRandom != 1) {
        
        for (int i = pos; i < (*quiz)->optionSize; i++) {
            
            if (i == (*quiz)->optionSize - 1) {
                
                (*quiz)->numberArray[(*quiz)->optionDifficulty][i] = 0;
            }
                
            else {
                
                (*quiz)->numberArray[(*quiz)->optionDifficulty][i] = (*quiz)->numberArray[(*quiz)->optionDifficulty][i + 1];
                
            }
            
        }        
    }
    else {
        
        for (int i = pos; i < (*quiz)->randomSize[(*quiz)->optionDifficulty]; i++) {
            
            if (i == (*quiz)->randomSize[(*quiz)->optionDifficulty] - 1) {
                
                (*quiz)->numberArray[(*quiz)->optionDifficulty][i] = 0;
            }
                
            else {
                
                (*quiz)->numberArray[(*quiz)->optionDifficulty][i] = (*quiz)->numberArray[(*quiz)->optionDifficulty][i + 1];
                
            }
            
        }        
        
    }
    
}

void clear() {
    
    #ifdef _WIN32
        system("cls");
    #elif __linux__ 
        system("clear");
    #endif
    
}

void intro() {
    
    printf(BOLD_ON BLUE "\n\n\n\t\t\t\tWELCOME TO C QUIZ GAME!"
                        "\n\n\t\tAn Interactive C Game for C Programming Beginners!"
                        "\n\n\t\tPlease head to Mechanics to learn more."OFF
           OFF ITL GREEN"\n\n\t\tEnter any to continue to Main Menu...");
    
}

void aboutMenu() {
    
    // to catch extra chars from input since they are cleared after function execution
    char tempLine[20];
    
    printf(BOLD_ON GREEN"\n\n\t\tA Quiz Game for C Programming Beginners!\n\n\n"OFF);

    printf(BLUE"\n\n\t\tThis Original C Quiz game is brought to you by:\n\n\t\tLuke Walter Say, BSCPE - 1\n\n\t\t");
    printf(BLUE"\n\t\tBig thanks to game testers: \n\t\t1. Mark Loue Pepito\n\t\t2. Jean Ron Cordova\n\t\t3. Arjee Paragele\n\t\t4. Ethnan Palma"OFF);
    printf(BOLD_ON GREEN"\n\n\t\tFun fact: code has more than a thousand lines!"OFF ITL"\n\n\t\tEnter any to return...\n\t\t"OFF);
    fgets(tempLine, sizeof(tempLine), stdin);
    
}

void mechanicsMenu() {
    
    char choice[20];
    
    M1:
    
    clear();
    printf(BOLD_ON BLUE"\n\n\t\tTHE C QUIZ GAME:\n\n");
    
    printf( BOLD_ON GREEN   "\t\t-> There will be three difficulties:\n"
                            "\t\t   1. EASY\n\t\t   2. MODERATE\n\t\t   3. HARD\n"
                            "\t\t-> Each difficulty round will have 10 questions.\n"
                            "\t\t-> Each correct answer will give 1 point.\n\n");
    
    printf(YELLOW           "\t\t[1] Continue\n\t\t[2] Main Menu\n\n\t\t"OFF);
    printf(BOLD_ON          "INPUT: "OFF);
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    
    if (strlen(choice) > 1) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto M1;
        
    }
    else if (choice[0] == '1') {
        
        goto M2;
        
    }
    else if (choice[0] == '2') {
        
        return;
        
    }
    else {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto M1;
        
    }
  

    
    M2:
    
    clear();
    printf(BOLD_ON BLUE"\n\n\t\tTHE C QUIZ GAME:\n"OFF);
    
    printf(BOLD_ON GREEN"\n\t\t-> You may modify how many questions you want to answer,\n"
                        "\t\t   or at which difficulty you would want to play.\n"
                        "\t\t-> You may also choose full random and it will override them\n"
                        "\t\t-> The passing score will always be 70%%.\n"
                        "\t\t-> All modifications are restored to default upon exiting or completing quiz.\n\n");
                        
    printf(YELLOW       "\n\t\t[1] Continue\n\t\t[2] Back\n\n\t\t"OFF);
    printf(BOLD_ON      "INPUT: ");
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    if (strlen(choice) > 1) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto M2;
        
    }
    else if (choice[0] == '1') {
        
        goto M3;
        
    }
    else if (choice[0] == '2') {
        
        goto M1;
        
    }
    else {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto M2;
        
    }
    
    
    M3:
    
    clear();
    
    
    printf(BOLD_ON BLUE"\n\n\t\tTHE C QUIZ GAME:\n"OFF);
    
    printf(BOLD_ON GREEN"\n\t\t-> Questions will shuffle but will never change.\n"
                        "\t\t-> You will have 3 tries for the quiz.\n"
                        "\t\t-> Exiting or completing the quiz consumes a try.\n"
                        "\t\t-> You will not be allowed to play again at 0 tries.\n\n");
    
    printf(YELLOW       "\n\n\t\t[1] Back\n\t\t[2] Main Menu\n\n\t\t"OFF);
    printf(BOLD_ON"INPUT: ");
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    if (strlen(choice) > 1) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto M3;
        
    }
    else if (choice[0] == '1') {
        
        goto M2;        
        
    }
    else if (choice[0] == '2') {
        
        return;
        
    }
    else {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto M3;
        
    }
}

void settingMenu(struct QnA *quiz) {
    
    /***************************************************************
    This submenu modifies the specific difficulty and number of items
    ***************************************************************/
    
    
    char choice[50];
    
    clear();
    setting:
    
    
    printf(BOLD_ON BLUE"\n\n\t\tYou can modify what specific difficulty you want to take on");
    printf("\n\t\tThere are only 3 difficulties and 10 maximum items you can modify, \n\t\tas well as the choice to randomize everything."OFF);
    printf(BOLD_ON RED"\n\t\tRandomize has the highest priority when chosen and will override other settings."OFF);
    printf(BOLD_ON "\n\n\t\tSELECT SETTING TO MODIFY: \n\t\t"YELLOW"[1] Difficulty\n\t\t[2] # of Items\n\t\t[3] Randomize\n\t\t[4] Main Menu"OFF BOLD_ON"\n\n\t\tINPUT: "OFF);
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    if(strlen(choice) > 1) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto setting;
        
    }
    else if(choice[0] == '1') {
        
        clear();
        goto SDiff;
        
    }
    else if(choice[0] == '2') {
        
        clear();
        goto SItems; 
        
    }
    else if(choice[0] == '3') {
        
        clear();
        goto SRand; 
        
    }
    else if (choice[0] == '4') {
        
        clear();
        return;
        
    }
    else{
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto setting;
        
    }
    
    
    SDiff:
    
    printf(BOLD_ON BLUE"\n\n\t\tDIFFICULTY: \n\t\t"OFF BOLD_ON YELLOW"[1] Easy\n\t\t[2] Moderate\n\t\t[3] Hard"OFF BOLD_ON"\n\n\t\tINPUT:"OFF);
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    if (strlen(choice) > 1) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        quiz->flag = 4;
        goto SDiff;
        
    }
    else if (choice[0] == '1') {
        
        quiz->optionDifficulty = 0;
        quiz->flag = 0;
        
    }
    else if (choice[0] == '2') {
        
        quiz->optionDifficulty = 1;
        quiz->flag = 1;
        
    }
    else if (choice[0] == '3') {
        
        quiz->optionDifficulty = 2;
        quiz->flag = 2;
        
    }
    else {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        quiz->flag = 4;
        goto SDiff;
        
    }
    
    clear();
    goto setting;
    
    SItems:
    
    
    printf(BOLD_ON BLUE"\n\n\t\tNUMBER OF ITEMS \n\n\t\t"OFF"INPUT: ");
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    if (strlen(choice) > 2) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid input. Please input at the set range [1 - 10]"OFF);
        goto SItems;
        
    }
    else if((choice[0] > '0' && choice[0] <= '9') && choice[1] == '\0') {
        
        quiz->optionSize = charToInt(choice[0]);
        
    }
    else if ((choice[0] > '0' && choice[0] <= '9') && choice[1] == '0') {
        
        if (charToInt(choice[0]) * 10 == 10) {
            
            quiz->optionSize = 10;
            
        }
        else {
            
            clear();
            printf(BOLD_ON RED"\t\tInvalid input. Please input at the set range [1 - 10]"OFF);
            goto SItems;
            
        }
        
    }
    else {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid input. Please input at the set range [1 - 10]"OFF);
        goto SItems;
        
    }
    
    
    clear();
    goto setting;
    
    
    SRand:
    printf(BOLD_ON BLUE"\n\n\t\tRandomize Every Question from EASY TO HARD"OFF BOLD_ON YELLOW"\n\n\t\t[1]Activate\n\t\t[2]Back\n\n\t\t"OFF"INPUT: ");
    
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = 0;
    
    if (strlen(choice) > 1) {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto SRand;
        
    }
    else if (choice[0] == '1') {
        
        quiz->optionRandom = 1;
        
    }
    else if (choice[0] == '2'){
        
        clear();
        goto setting;
        
    }
    else {
        
        clear();
        printf(BOLD_ON RED"\t\tInvalid choice. Please select from the listed choices"OFF);
        goto SRand;
        
    }
    
    clear();
    goto setting;
    
}

void initArray(struct QnA *quiz) {
    
    for (int i = 0; i < 3; i++) {
        
        quiz->randomSize[i] = 10;
        
        for (int j = 0; j < 10; j++) {
            
            quiz->numberArray[i][j] = j; 
            
        }
        
    }
    
    
}

void initQuizQuestions(struct QnA *quiz) {
    
    // Initialize Easy Questions and Answers
    strcpy(quiz->Questions[0][0], "What symbol represents the format specifier? \n\n\t\tA. $\n\t\tB. %\n\t\tC. &\n\t\tD. #");
    strcpy(quiz->Questions[0][1], "What symbol is used at the start of preprocessor directives? \n\n\t\tA. $\n\t\tB. %\n\t\tC. &\n\t\tD. #");
    strcpy(quiz->Questions[0][2], "This function is used to output to the screen \n\n\t\tA. scanf()\n\t\tB. printf()\n\t\tC. main()\n\t\tD. return");
    strcpy(quiz->Questions[0][3], "What is this '&' operator called? \n\n\t\tA. arithmetic\n\t\tB. identifyer\n\t\tC. addressof\n\t\tD. pointer");
    strcpy(quiz->Questions[0][4], "What is the result of the expression 5 + 2 * 3 \n\n\t\tA. 11\n\t\tB. 21\n\t\tC. 15\n\t\tD. 12");
    strcpy(quiz->Questions[0][5], "What is the result of the expression 3 % 2 + 3? \n\n\t\tA. 5\n\t\tB. 4\n\t\tC. 3\n\t\tD. 2");
    strcpy(quiz->Questions[0][6], "What function takes in user inputs? \n\n\t\tA. scanf()\n\t\tB. printf()\n\t\tC. main()\n\t\tD. return");
    strcpy(quiz->Questions[0][7], "These are mathematical operators used in programming. \n\n\t\tA. arithmetic\n\t\tB. identifyer\n\t\tC. address\n\t\tD. pointer");
    strcpy(quiz->Questions[0][8], "What data type is appropriate for whole numbers? \n\n\t\tA. float\n\t\tB. void\n\t\tC. char\n\t\tD. int");
    strcpy(quiz->Questions[0][9], "What is the result of the expression (int)5 / 2 + 3 * 3? \n\n\t\tA. 12\n\t\tB. 13\n\t\tC. 14\n\t\tD. 11");
    
    strcpy(quiz->AnswerKey[0][0], "B. %");
    strcpy(quiz->AnswerKey[0][1], "D. #");
    strcpy(quiz->AnswerKey[0][2], "B. printf()");
    strcpy(quiz->AnswerKey[0][3], "C. address");
    strcpy(quiz->AnswerKey[0][4], "A. 11");
    strcpy(quiz->AnswerKey[0][5], "B. 4");
    strcpy(quiz->AnswerKey[0][6], "A. scanf()");
    strcpy(quiz->AnswerKey[0][7], "A. arithmetic");
    strcpy(quiz->AnswerKey[0][8], "D. int");
    strcpy(quiz->AnswerKey[0][9], "D. 11");
    
    // initialize Moderate Questions and Answers
    strcpy(quiz->Questions[1][0], "Which keyword is used to prevent any changes in the variable within a C program? \n\n\t\tA. define\n\t\tB. int\n\t\tC. const\n\t\tD. volatile");
    strcpy(quiz->Questions[1][1], "What is an example of iteration in C? \n\n\t\tA. for\n\t\tB. while\n\t\tC. do-while\n\t\tD. All of the mentioned");
    strcpy(quiz->Questions[1][2], "Which of the following operator has the highest precedence? \n\n\t\tA. ()\n\t\tB. sizeof\n\t\tC. *\n\t\tD. +");
    strcpy(quiz->Questions[1][3], "What is the result of this 2 + 4 + 3 * 5 / 3 - 5? \n\n\t\tA. 7\n\t\tB. 6\n\t\tC. 10\n\t\tD. 9");
    strcpy(quiz->Questions[1][4], "Associativity of an operator is _________. \n\n\t\tA. Right to Left\n\t\tB. Left to Right\n\t\tC. Random\n\t\tD. Both");
    strcpy(quiz->Questions[1][5], "A global variable is declared _________ the function \n\n\t\tA. Outside\n\t\tB. Inside\n\t\tC. in Any of\n\t\tD. Anywhere in");
    strcpy(quiz->Questions[1][6], "scanf() is a predefined function in ________ header file. \n\n\t\tA. stdlib.h\n\t\tB. ctype.h\n\t\tC. stdio.h\n\t\tD. stdarg.h");
    strcpy(quiz->Questions[1][7], "All keywords in C are in _______. \n\n\t\tA. Lowercase\n\t\tB. Uppercase\n\t\tC. CamelCase\n\t\tD. None of the mentioned");
    strcpy(quiz->Questions[1][8], "What does %d signify in the printf or scanf function? \n\n\t\tA. Double data type\n\t\tB. Integer Format specifier\n\t\tC. Dynamic Allocation\n\t\tD. Directory Path");
    strcpy(quiz->Questions[1][9], "What data type should you use to store a character in C? \n\n\t\tA. double\n\t\tB. float\n\t\tC. char\n\t\tD. int");

    strcpy(quiz->AnswerKey[1][0], "C. const");
    strcpy(quiz->AnswerKey[1][1], "D. All of the mentioned");
    strcpy(quiz->AnswerKey[1][2], "A. ()");
    strcpy(quiz->AnswerKey[1][3], "B. 6");
    strcpy(quiz->AnswerKey[1][4], "D. Both");
    strcpy(quiz->AnswerKey[1][5], "A. Outside");
    strcpy(quiz->AnswerKey[1][6], "C. stdio.h");
    strcpy(quiz->AnswerKey[1][7], "A. Lowercase");
    strcpy(quiz->AnswerKey[1][8], "B. Integer Format specifier");
    strcpy(quiz->AnswerKey[1][9], "C. char");
    
    // initialize Hard Questions and Answers
    strcpy(quiz->Questions[2][0], "WHAT IS THE OUTPUT OF THIS CODE?\n\n\t\tvoid main(){\n\t\tint a = 4, b = 10;\n\t\tprintf(\"%d\", b % a)\n\t\t} \n\n\t\tA. 5\n\t\tB. 4\n\t\tC. 3\n\t\tD. 2");
    strcpy(quiz->Questions[2][1], "WHAT IS THE OUTPUT OF THIS CODE?\n\n\t\tvoid main(){\n\t\tint x = 45, y = 5;\n\t\twhile (x <= 30)\n\t\t{\n\t\tprintf(\"%d\", x %% y)\n\t\t}\n\t\tprintf(\"%d\", x / y);\n\t\t}\n\n\t\tA. 6\n\t\tB. 7\n\t\tC. 9\n\t\tD. 4");
    strcpy(quiz->Questions[2][2], "WHAT IS THE OUTPUT OF THIS CODE?\n\n\t\tvoid main(){\n\t\tchar letter = \'T\';\n\t\t{\n\t\tint a = 10;\n\t\tprintf(\"%d\", a % 2);\n\t\t}\n\t\tprintf(\"%c\", T)\n\t\t} \n\n\t\tA. T10\n\t\tB. T5\n\t\tC. 10T\n\t\tD. 0T");
    strcpy(quiz->Questions[2][3], "Given an int arr[5] = {22, 32, 1, 0, 4} and a pointer int *ptr = arr, what is the\n\t\tvalue of ptr[3] + 12? \n\n\t\tA. 13\n\t\tB. 10\n\t\tC. 34\n\t\tD. 12");
    strcpy(quiz->Questions[2][4], "WHAT IS THE OUTPUT OF THIS CODE?\n\n\t\t#include <stdio.h> \n\n\t\tint main() {\n\t\tprintf(\"%d\", 7 / 2);\n\t\treturn 0;\n\t\t} \n\n\t\tA. 3.5\n\t\tB. 3\n\t\tC. 4\n\t\tD. Error");
    strcpy(quiz->Questions[2][5], "There are 3 case convention. Which of the following is the camel case? \n\n\t\tA. myVar\n\t\tB. MyVar\n\t\tC. my_var\n\t\tD. none of the above");
    strcpy(quiz->Questions[2][6], "Suppose that arr1[3] = {4, 6, 1} and arr2[3] = {5, 7, 8}, \n\n\t\twhat is the result of arr1[2] / arr2[2] - arr1[0]? \n\n\t\tA. 5\n\t\tB. -1\n\t\tC. -3\n\t\tD. -4");
    strcpy(quiz->Questions[2][7], "What is the result if int A = 10 and A *= 10 - 10?\n\n\t\tA. 90\n\t\tB. 60\n\t\tC. 20\n\t\tD. 0");
    strcpy(quiz->Questions[2][8], "If a one-dimensional array requires a single loop to traverse, how many loops does a four-dimensional array require? \n\n\t\tA. 2\n\t\tB. 3\n\t\tC. 4\n\t\tD. 5");
    strcpy(quiz->Questions[2][9], "WHAT IS THE OUTPUT OF THIS CODE?\n\n\t\tvoid main()\n\t\t{\n\t\tint a = 5;\n\t\ta += 3 * 1;\n\t\tprintf(\"%d\", a - 2);\n\t\t}\n\n\t\tA. 2\n\t\tB. 4\n\t\tC. 6\n\t\tD. 8");

    strcpy(quiz->AnswerKey[2][0], "D. 2");
    strcpy(quiz->AnswerKey[2][1], "C. 9");
    strcpy(quiz->AnswerKey[2][2], "D. 0T");
    strcpy(quiz->AnswerKey[2][3], "D. 12");
    strcpy(quiz->AnswerKey[2][4], "B. 3");
    strcpy(quiz->AnswerKey[2][5], "A. myVar");
    strcpy(quiz->AnswerKey[2][6], "D. -4");
    strcpy(quiz->AnswerKey[2][7], "D. 0");
    strcpy(quiz->AnswerKey[2][8], "C. 4");
    strcpy(quiz->AnswerKey[2][9], "C. 6");

}

int charToInt(char ch) {
    switch(ch){
        
        case '1': {
            
            return 1;
            
        }
        case '2': {
            
            return 2;
            
        }
        case '3': {
            
            return 3;
            
        }
        case '4': {
            
            return 4;
            
        }
        case '5': {
            
            return 5;
            
        }
        case '6': {
            
            return 6;
            
        }
        case '7': {
            
            return 7;
            
        }
        case '8': {
            
            return 8;
            
        }
        case '9': {
            
            return 9;
            
        }
        case '0': {
            
            return 0;
            
        }
        default: {
            
            return -1;
            
        }
        
    }
    
    return -1;
    
}
