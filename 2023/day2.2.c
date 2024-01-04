/*
*   Advent of Code Challenge - Day 2 - Part Two
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "day2.h"

#include "../utils.h"

int main(void)
{
    char* data = NULL;
    int data_size = getDayInput(2, &data);
    if (data_size == -1)
        return 1;

    const Bag bag = bag_create(12, 13, 14);

    int sum = 0;
    for (char* ptr = strtok(data, "\n"); ptr != NULL; ptr = strtok(NULL, "\n"))
    {
        int game_id = 0;
        sscanf(ptr, "Game %d:", &game_id);

        Game* game = game_create(game_id);

        char* start = ptr + 5 + digits_in_number(game_id) + 1;
        do
        {
            int red_cubes = 0;
            int green_cubes = 0;
            int blue_cubes = 0;

            do
            {
                char color[10];
                int quantity = 0;
                sscanf(start, " %d %s", &quantity, color);

                switch (get_color_by_name(color))
                {
                    case RED:
                        red_cubes += quantity;
                        break;
                    case GREEN:
                        green_cubes += quantity;
                        break;
                    case BLUE:
                        blue_cubes += quantity;
                        break;
                    default:
                    {
                        printf("Invalid color: %s -> %s\n", color, ptr);

                        game_destroy(game);
                        return -1;
                    }
                }

                start += 1 + digits_in_number(quantity) + 1 + strlen(color);
            } while (start[-1] == ',');

            game_result_add(game, red_cubes, green_cubes, blue_cubes);
        } while (start[-1] == ';');
        
        int red_cubes = 0;
        int green_cubes = 0;
        int blue_cubes = 0;

        for (GameResult* result = game->results; result != NULL; result = result->next)
        {
            if (result->red_cubes > red_cubes)
                red_cubes = result->red_cubes;

            if (result->green_cubes > green_cubes)
                green_cubes = result->green_cubes;

            if (result->blue_cubes > blue_cubes)
                blue_cubes = result->blue_cubes;
        }

        sum += red_cubes * green_cubes * blue_cubes;

        game_destroy(game);
        game = NULL;
    }

    printf("\nSum of all the cube set power's: %d\n", sum);

    free(data);

    return 0;
}