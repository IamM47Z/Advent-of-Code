/*
*   Advent of Code Challenge - Day 3 - Part Two
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "../utils.h"

const char* getNumStart(const char* buffer, const char* start)
{
    while (buffer > start && isdigit(buffer[-1]))
        --buffer;
    
    return buffer;
}

int getGearRatio(const char* buffer, const int l, const int c, const int num_lines, const int num_cols)
{
    int num = 0;
    int mult = 1;

    for (int j = -1; j < 2; ++j)
    {
        const int line = l + j;
        if (line < 0)
            continue;

        if (line > num_lines)
            break;

        bool found = false;
        for (int k = -1; k < 2; ++k)
        {
            const int col = c + k;
            if (col < 0)
                continue;

            if (col > num_cols)
                break;

            const char* elem = &buffer[(num_cols + 1) * line + col];
            if (!isdigit(*elem))
            {
                found = false;
                continue;
            }

            if (found)
                continue;

            const char* start = getNumStart(elem, buffer);
            const int num_digits = getNumDigits(start, num_cols - col - (elem - start));
            const int number = getNumber(start, num_digits);

            mult *= number;
                
            found = true;
            ++num;
        }
    }

    return num == 2 ? mult : -1;
}


int main(void)
{
    char* data = NULL;
    int data_size = getDayInput(3, &data);
    if (data_size == -1)
        return 1;

    const int num_lines = getNumLines(data, data_size);
    const int num_cols = getNumCols(data, data_size);

    printf("Size: %dx%d\n", num_lines, num_cols);

    int sum = 0;
    for (int l = 0, c = 0; l < num_lines;)
    {
        if (c > num_cols)
        {
            c = 0;
            ++l;
            continue;
        }

        const char* curr = &data[(num_cols + 1) * l + c];
        const int curr_size = num_cols - c;

        if (*curr != '*')
        {
            ++c;
            continue;
        }

        const int ratio = getGearRatio(data, l, c, num_lines, num_cols);
        if (ratio != -1)
        {
            printf("Adding %d from %dx%d.\n", ratio, l + 1, c + 1);
            sum += ratio;
        }

        ++c;
    }

    printf("\nSum of all of the gear rations in the engine schematic: %d\n", sum);

    free(data);

    return 0;
}