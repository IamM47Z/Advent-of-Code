/*
*   Advent of Code Challenge - Day 2
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
        
        if (game_is_valid(game, bag))
        {
            printf("Adding game with id: %d\n", game->id);
            sum += game->id;
        }

        game_destroy(game);
        game = NULL;
    }

    printf("\nSum of all the game id's: %d\n", sum);

    free(data);

    return 0;
}