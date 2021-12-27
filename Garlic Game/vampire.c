#include "names.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    //
    //Takes number of players as an input and checks if it is valid
    //

    char input[1];
    printf("Number of players: ");
    scanf("%s", input);
    for (unsigned long i = 0; i < strlen(input); i++) {
        if (input[i] != 48 && input[i] != 49 && input[i] != 50 && input[i] != 51 && input[i] != 52
            && input[i] != 53 && input[i] != 54 && input[i] != 55 && input[i] != 56
            && input[i] != 57) {
            fprintf(stderr, "Invalid number of players. \n");
            return 0;
        }
    }
    if (atoi(input) < 2 || atoi(input) > 10) {
        fprintf(stderr, "Invalid number of players. \n");
        return 0;
    }

    //
    //Takes random seed as an input and checks if it is valid
    //

    char seed[1];
    printf("Random Seed: ");
    scanf("%s", seed);
    for (unsigned long i = 0; i < strlen(seed); i++) {
        if (seed[i] != 48 && seed[i] != 49 && seed[i] != 50 && seed[i] != 51 && seed[i] != 52
            && seed[i] != 53 && seed[i] != 54 && seed[i] != 55 && seed[i] != 56 && seed[i] != 57) {
            fprintf(stderr, "Invalid random seed. \n");
            return 0;
        }
    }
    int int_seed = atoi(seed);
    if (int_seed < 0 || int_seed > 32767) {
        fprintf(stderr, "Invalid number of players. \n");
        return 0;
    }

    //
    //Sets inital variables for the while loop which plays the garlic game
    //Starts by assigning each player a roll and keeping track of who has the worst roll while also watching out for midnight rolls
    //Then after that loop the program states who had the lowest roll and subtracts a life
    //Finaly the loop checks to see if someone has won, exits if someone has and continues if someone hasn't
    //

    bool winner = 0;
    int winner_index = 11;
    int min = 13;
    int one;
    int two;
    int round = 1;
    int loser = 0;
    int num_alive = atoi(input);
    int lives[atoi(input)];
    for (int y = 0; y < atoi(input); y++) {
        lives[y] = 3;
    }
    srandom(int_seed);
    while (!winner) {
        printf("Round %d\n", round);
        for (int x = 0; x < atoi(input); x++) {
            if (lives[x] > 0) {
                printf(" - %s ", names[x]);
                one = random() % 6;
                two = random() % 6;
                printf("Rolls %s\n", rolls[one][two]);
                if (one + two < min) {
                    min = one + two;
                    loser = x;
                }
                if (one + two == 10) {
                    if (x != 0) {
                        lives[x - 1]++;
                    }
                    if (x != atoi(input) - 1) {
                        lives[x + 1]++;
                        x++;
                    }
                }
            }
        }
        printf("%s is forced to eat garlic!\n", names[loser]);
        lives[loser] -= 1;
        if (lives[loser] > 1) {
            printf("%s has %d lives remaining.\n", names[(loser)], lives[loser]);
        } else if (lives[loser] > 0) {
            printf("%s has %d life remaining.\n", names[(loser)], lives[loser]);
        } else {
            printf("%s has died\n", names[loser]);
        }
        for (int z = 0; z < atoi(input); z++) {
            if (lives[z] < 1) {
                num_alive--;
            } else {
                winner_index = z;
            }
        }
        if (num_alive == 1) {
            printf("%s wins the Garlic Game\n", names[winner_index]);
            winner = 1;
        }
        min = 13;
        num_alive = atoi(input);
        round++;
    }
    return 0;
}
