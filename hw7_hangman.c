/*
Team members: Yash Waghmare and Somil Ajmera
extra suggestions added: 1-added hints after three errors
                         2-added an extra level
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // for call to time() in srand(time(NULL))

#define DEBUG 1 // 1-development mode, prints more info; 0 - user mode, prints less
#define MAX_WRONG 6
#define BUFFER 1024

int play_session(int level, int win, int lose);
void stickman(int errors);

int main()
{
    int level;
    char enter;
    int win = 0;
    int lose = 0;
    if (DEBUG == 1)
    {
        srand(1); // the same sequence of random numbers will be generated for each run
    }
    else
    {
        srand(time(NULL)); // a different sequence of random numbers will be generated with each run
    }

    printf("Choose difficulty level (exit the game: 0, easy: 1, medium: 2, hard: 3, insane asylum: 4): ");
    scanf("%d%c", &level, &enter);
    while (level != 0)
    {
        play_session(level, win, lose);
        printf("Choose difficulty level (exit the game: 0, easy: 1, medium: 2, hard: 3, insane asylum: 4): ");
        scanf("%d%c", &level, &enter);
    }
    printf("\nThank you for playing our game! Goodbye!");
    return 0;
}

int play_session(int level, int win, int lose)
{

    int errors = 0; // to store no of errors user made in the current game.
    char current_letter = '\0';
    char letters_used[BUFFER] = {'\0'}; // stores used letters
    int lines = 0;                    // used to stores no of lines the text files have
    int index_of_letters_used = -1;                   //all the counts used are for arithmitic calculations and manipulations
    char hidden_word[BUFFER];         //stores the hidden word
    int ct = 0;
    char replace_char[BUFFER] = {0}; // used to store dashes and replaced later with char if guessed rightly
    char enter2 = 0;                 /*this is used to store the extra \n that user enters so it doesn't cause
                     any problems in the code */
    int again = 0;
    int hint_used = 0;

    FILE *txt_file;

    if (txt_file == NULL)
    {
        printf("File could not be open\n");
        return 0;
    }

    if (level == 1)
    {
        txt_file = fopen("easy.txt", "r");
        printf("Loading file: easy.txt\n");
    }
    else if (level == 2)
    {
        txt_file = fopen("medium.txt", "r");
        printf("Loading file: medium.txt\n");
    }
    else if (level == 3)
    {
        txt_file = fopen("hard.txt", "r");
        printf("Loading file: hard.txt\n");
    }
    else if (level == 4)
    {
        txt_file = fopen("insane_asylum.txt", "r"); //added an extra level
        printf("Loading file: insane_asylum.txt\n\n # BEWARE! PLAY IT AT YOUR OWN RISK! #\n\n");
    }

    fscanf(txt_file, "%d", &lines);
    int r;
    r = 1+(rand() % (lines)); // random number generator
    while (!feof(txt_file) && ct < r)
    {
        fscanf(txt_file, "%s", hidden_word);
        ct++;
    }
    printf("-----hidden word: |%s|", hidden_word);
    for (int i = 0; i < strlen(hidden_word); i++) // loop used to fill in blanks in the array
    {
        replace_char[i] = '-';
    }

    while (errors <= 6)
    {
        int count2 = 0; // specially placed here so both counts become zero as loop is iterated
        int not_blanks = 0;
        int count = 0;

        printf("\n\n\n\n\n\n\n\n\nLevel: %d\n\n", level);
        stickman(errors); // used to print the stick man figure
        printf("Used letter: ");
        letters_used[index_of_letters_used] = current_letter; //storing current letter in the array
        index_of_letters_used++;
        for (int i = 0; i < strlen(letters_used); i++)
        {
            printf("%c", letters_used[i]);
        }
        printf("\nNumber of bad guesses: %d (out of 6)\n", errors);
        for (int i = 0; i < strlen(hidden_word); i++) //used to print letters guessed from the hidden word
        {
            printf("%c", replace_char[i]);
            if (replace_char[i] != '-')
            {
                not_blanks++;
            }
        }
        if (errors == 3) //to give an hint when three errors are done by the user
        {
            hint_used++;
            if (hint_used == 1) //so it only prints it once
            {
                for (int k = 0; k <= strlen(hidden_word); k++)
                {
                    if (replace_char[k] == '-')
                    {
                        printf("\n(Hint): One of the missing letter is '%c'", hidden_word[k]);
                        break;
                    }
                }
            }
        }
        if (not_blanks == strlen(replace_char)) // used to check if all words are guessed or not
        {
            printf("\n\nYou won!\n\n");
            printf("Do you want to play again?(0 No,1 yes) ");
            scanf("%d%c", &again, &enter2);
            win++;
            break;
        }
        if (errors == 6) // use to check if no of errors has reached 6
        {
            printf("\n\nSorry. You lost. Better luck next time\nThe word was: %s\n\n", hidden_word);
            printf("Do you want to play again? (0-No, 1-yes) ");
            scanf(" %d%c", &again, &enter2);
            lose++;
            break;
        }
        printf("\nEnter a letter: ");
        scanf("%c%c", &current_letter, &enter2);

        for (int i = 0; i < strlen(hidden_word); i++) //start of the main checking area
        {
            if (hidden_word[i] == current_letter)
            {
                replace_char[i] = current_letter; // to replace the blanks with correctly guessed words
            }
            else if (hidden_word[i] != current_letter)
            {
                count2++;
            }
        }
        for (int i = 0; i < strlen(hidden_word); i++)//second checking area for repeated correct guesses
        {
            for (int j = 0; j < strlen(letters_used); j++)
            {
                if (letters_used[j] == hidden_word[i] && hidden_word[i] == current_letter)
                {
                    count++;
                }
            }
        }
        if (count != 0){ //done to increase errors by one if correct guesses repeated more than once
            errors++;
        }
        count2 = count2 / strlen(hidden_word); /*what I had in mind:if no words are replaced then count2
                                                 and string length will be the same so count2 equal to one*/
        if (count2 == 1)
        {
            errors = count2 + errors;   // error is increased by one
        }
    }

    if (again == 1)
    {
        play_session(level, win, lose);
    }
    else if (again == 0)
    {
        printf("\n****************************\n");
        printf("*  Session score:   %d/  %d  *\n", win, (win + lose));
        printf("****************************\n\n");
    }
    fclose(txt_file);
    //no return statement as no need
}

void stickman(int errors) //stick man print function
{
    if (errors == 0)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("-------------\n");
    }
    else if (errors == 1)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("-------------\n");
    }
    else if (errors == 2)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|     |\n");
        printf("|     |\n");
        printf("|\n");
        printf("-------------\n");
    }
    else if (errors == 3)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\n");
        printf("|     |\n");
        printf("|\n");
        printf("-------------\n");
    }
    else if (errors == 4)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\\\n");
        printf("|     |\n");
        printf("|\n");
        printf("-------------\n");
    }
    else if (errors == 5)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\\\n");
        printf("|     |\n");
        printf("|    /\n");
        printf("-------------\n");
    }
    else if (errors == 6)
    {
        printf("------|\n");
        printf("|     |\n");
        printf("|     O\n");
        printf("|     |\n");
        printf("|    /|\\\n");
        printf("|     |\n");
        printf("|    / \\\n");
        printf("-------------\n");
    }
}
