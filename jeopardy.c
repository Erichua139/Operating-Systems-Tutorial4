/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];

    // Input buffer and and commands
    char buffer[BUFFER_LEN] = {0};
    char cur_player[BUFFER_LEN] = "";
    char cur_cat[BUFFER_LEN] = "";
    int cur_amnt = 0;
    char ans[BUFFER_LEN];
    char *tokens;
    tokens = (char*) malloc(100 * sizeof(float));

    // Display the game introduction and initialize the questions
    printf("Welcome to Jeopardy! This game has four players competeing against eachother to answer trivia questions.\n");
    printf("There are three catorgories and four questions in each. The player with the highest score at the end wins.\n");
    initialize_game();

    // Prompt for players names and intialize each player in the array
    printf("Enter the name of each player\n");
    for (int x = 0; x < NUM_PLAYERS; x++)
    {
        printf("Player %d:", (x + 1));
        scanf(" %s", players[x].name);
        players[x].score = 0;
    }

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        display_categories();
        // Getting starting player
        printf("Please enter the next players name.\n (If you do not know decide in a game of rock paper scissors)\n");
        scanf(" %s", cur_player);
        //Replace once player.c is finished
        // if(player_exists(players,NUM_PLAYERS,cur_player)==true)
        if (true)
        {
            while (1)
            {
                printf("Enter the catorgory that you choose:");
                scanf(" %s", cur_cat);
                printf("Enter the dollar amount that you choose:");
                scanf(" %d", &cur_amnt);
                //replcae once questions.c is finished
                // if (already_answered(cur_cat, cur_amnt) == false)
                if (true)
                {
                    break;
                }
                else
                {
                    printf("Question has been answered / Invalid input\n");
                }
            }
            display_question(cur_cat, cur_amnt);
            printf("Remeber to answer the question with either \"what is\" or with \"who is\"\n");
            scanf(" %[^\n]s", ans);
            //Stuck here. Cannont figure out how to get the token passed back to main.
            tokenize((char *)ans, &tokens);
            printf(&tokens);
        }
        else
        {
            printf("Invalid Input\n");
        }

        // Execute the game until all questions are answered
        break;
        // Display the final results and exit
    }
    free (tokens);
    return EXIT_SUCCESS;
}
// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens)
{
    char *str;

    if((str = strtok(input, "")) != NULL)
        if(strcmp(str, "who") != 0 && strcmp(str, "what") != 0 )
            return;

    if((str = strtok(NULL, "")) != NULL)
        if(strcmp(str, "is") != 0)
            return;

    *tokens = strtok(NULL, "\n");
}
