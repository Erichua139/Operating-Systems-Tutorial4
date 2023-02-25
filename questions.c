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
#include "questions.h"

question questions[NUM_CATEGORIES][NUM_QUESTIONS];

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    // Movies category
    questions[0][0] = (question){"movies", "What 1975 movie had a mechanical shark named Bruce?", "Jaws", 100, false};
    questions[0][1] = (question){"movies", "Who played the character Gandalf in The Lord of the Rings movies?", "IanMcKellen", 200, false};
    questions[0][2] = (question){"movies", "What was the first feature-length animated movie ever released?", "SnowWhiteandtheSevenDwarfs", 300, false};
    questions[0][3] = (question){"movies", "Which movie won the Academy Award for Best Picture in 2020?", "Parasite", 400, false};

    // Sports category
    questions[1][0] = (question){"sports", "Which country won the first FIFA World Cup in 1930?", "Uruguay", 100, false};
    questions[1][1] = (question){"sports", "Which NBA player has won the most championships?", "BillRussell", 200, false};
    questions[1][2] = (question){"sports", "What country is the origin of the martial art known as karate?", "Japan", 300, false};
    questions[1][3] = (question){"sports", "Who won the Super Bowl in 2021?", "TampaBayBuccaneers", 400, false};

    // Science category
    questions[2][0] = (question){"science", "What is the smallest planet in our solar system?", "Mercury", 100, false};
    questions[2][1] = (question){"science", "What is the hardest substance in the human body?", "Toothenamel", 200, false};
    questions[2][2] = (question){"science", "What is the smallest unit of measurement in the metric system?", "Millimeter", 300, false};
    questions[2][3] = (question){"science", "What is the name of the process by which plants convert light into energy?", "Photosynthesis", 400, false};

    // History category
    questions[3][0] = (question){"history", "Who was the first president of the United States?", "GeorgeWashington", 100, false};
    questions[3][1] = (question){"history", "What year did World War I end?", "1918", 200, false};
    questions[3][2] = (question){"history", "Which ancient civilization built the Machu Picchu complex in Peru?", "Inca", 300, false};
    questions[3][3] = (question){"history", "Who assassinated Abraham Lincoln?", "JohnWilkesBooth", 400, false};
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // Print the categories

    printf("\nCATERGORIES\n");
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        printf("%-15s", questions[i][0].category);
    }
    printf("\n\n");

    // Print the questions and their values
    for (int j = 0; j < NUM_QUESTIONS; j++)
    {
        for (int i = 0; i < NUM_CATEGORIES; i++)
        {
            if (questions[i][j].answered == true)
            {
                printf("%-15s", "X");
            }
            else
            {
                printf("%-15d", questions[i][j].value);
            }
        }
        printf("\n\n");
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    int val;
    for (int i = 0; i < 50; i++)
        printf("*");
    printf("\n");
    printf("%-15s%-15d", category, value);
    printf("\n");
    switch (value)
    {
    case 100:
        val = 0;
        break;
    case 200:
        val = 1;
        break;
    case 300:
        val = 2;
        break;
    case 400:
        val = 3;
        break;
    }
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        if (strcmp(questions[i][val].category, category) == 0)
        {
            printf("%s", questions[i][val].question);
            printf("\n");
            return;
        }
    }
    printf("Could not find that category, Try again.");
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    int val,cat;
    switch (value)
    {
    case 100:
        val = 0;
        break;
    case 200:
        val = 1;
        break;
    case 300:
        val = 2;
        break;
    case 400:
        val = 3;
        break;
    }
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        if (strcmp(questions[i][val].category, category) == 0)
        {
            cat = i;
            if (strcasecmp(questions[i][val].answer, answer) == 0)
            {
                questions[i][val].answered = true;
                return true;
            }
        }
    }
    printf("Incorrect!\n The answer was ");
    printf(questions[cat][val].answer);
    printf("\n");
    questions[cat][val].answered = true;
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    int val;
    switch (value)
    {
    case 100:
        val = 0;
        break;
    case 200:
        val = 1;
        break;
    case 300:
        val = 2;
        break;
    case 400:
        val = 3;
        break;
    }
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        if (strcmp(questions[i][val].category, category) == 0)
        {
            if (questions[i][val].answered == true)
            {
                return true;
            }
        }
    }
    return false;
}