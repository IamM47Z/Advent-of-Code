/*
*   Advent of Code Challenge - Day 2 - Part Two
*/
#include <stdio.h>
#include <ctype.h>

#include "../utils.h"

int getSymbolScore(char symbol)
{
    switch (symbol)
    {
        case 'A':
        case 'X':
            return 1;
        case 'B':
        case 'Y':
            return 2;
        case 'C':
        case 'Z':
            return 3;
        default:
            break;
    }

    return 0;
}

int getWinnerScore(int loser_score)
{
    return (loser_score % 3) + 1;
}

int getLoserScore(int winner_score)
{
    return ((winner_score + 1) % 3) + 1;
}

int getDuelScore(char* duel)
{
    int opponent_score = getSymbolScore(duel[0]);
    if (opponent_score == 0)
        return 0;

    int my_score = 0;
    switch(duel[2])
    {
        case 'X':
            my_score = getLoserScore(opponent_score);
            break;
        case 'Y':
            my_score = opponent_score + 3;
            break;
        case 'Z':
            my_score = getWinnerScore(opponent_score) + 6;
            break;
        default:
            return 0;
    }

    return my_score;
}

int main(void)
{
    char* data = NULL;
    int data_size = getDayInput(2, &data);
    if (data_size == -1)
        return 1;

    int total_score = 0;
    for (char* current = data; data + data_size > current; current += 4)
        total_score += getDuelScore(current);

    printf("Your total score in the tournament was %d!\n", total_score);

    free(data);

    return 0;
}