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
    tokens = (char *)malloc(100 * sizeof(float));
    int count = 0;
    bool cat_flag = false, val_flag = false;

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

        if (count == (NUM_CATEGORIES*NUM_QUESTIONS))
        {
            break;
        }
        // Call functions from the questions and players source files
        display_categories();
        // Getting starting player
        printf("Please enter the next players name.\n (If you do not know decide in a game of rock paper scissors)\n");
        scanf(" %s", cur_player);
        if (player_exists(players, NUM_PLAYERS, cur_player) == true)
        {
            while (1)
            {
                cat_flag = false;
                val_flag = false;
                printf("Enter the catorgory that you choose:");
                scanf(" %s", cur_cat);
                printf("Enter the dollar amount that you choose:");
                scanf(" %d", &cur_amnt);
                // Check if valid category
                for (int i = 0; i < NUM_CATEGORIES; i++)
                {
                    if (strcasecmp(cur_cat, questions[i][0].category) == 0)
                    {
                        cat_flag = true;
                        break;
                    }
                }
                if (cur_amnt == 100 || cur_amnt == 200 || cur_amnt == 300 || cur_amnt == 400)
                {
                    val_flag = true;
                }
                if (already_answered(cur_cat, cur_amnt) == false && val_flag == true && cat_flag == true)
                {
                    display_question(cur_cat, cur_amnt);
                    printf("Remember to answer the question with either \"what is\" or with \"who is\" and keep the answer as one word (ex Who is JohnDoe)\n");
                    scanf(" %[^\n]s", ans);
                    tokenize(ans, &tokens);
                    if (valid_answer(cur_cat, cur_amnt, tokens) == true)
                    {
                        printf("Correct!\n");
                        printf("Player %s gains %d points \n", cur_player, cur_amnt);
                        update_score(players, NUM_PLAYERS, cur_player, cur_amnt);
                        count++;
                        break;
                    }
                    else
                    {
                        count++;
                        break;
                    }
                }
                else
                {
                    printf("Question has been answered / Invalid input\n");
                }
            }

            
        }
        else
        {
            printf("Invalid Input\n");
        }

        // Execute the game until all questions are answered
        // Display the final results and exit
    }
    printf("Thank you for playing!\n Tallying the scores...");
    show_results(players, NUM_PLAYERS);
    return EXIT_SUCCESS;
}
// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens)
{
    char *str;

    if ((str = strtok(input, " ")) != NULL)
        if (strcmp(str, "who") != 0 && strcmp(str, "what") != 0)
            return;

    if ((str = strtok(NULL, " ")) != NULL)
        if (strcmp(str, "is") != 0)
            return;

    str = strtok(NULL, " ");
    *tokens = str;
}
void show_results(player *players, int num_players)
{
    int winner;
    int high_score = -1;
    for (int i = 0; i < num_players; i++)
    {
        if (players[i].score > high_score)
        {
            high_score = players[i].score;
            winner = i;
        }
    }

    printf("Scores: \n");
    for (int i = 0; i < num_players; i++)
    {
        printf("%s: %d\n", players[i].name, players[i].score);
    }
    printf("The Winner is : %s !", players[winner].name);
}