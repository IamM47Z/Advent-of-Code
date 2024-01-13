/*
*   Advent of Code Challenge - Day 3
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "../utils.h"

bool hasNeighbourSymbol(const char* buffer, const int l, const int c, const int num_digits, const int num_lines, const int num_cols)
{
    const char default_value = '.';

    for (int i = 0; i < num_digits; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            const int line = l + j;
            if (line < 0)
                continue;

            if (line > num_lines)
                break;

            for (int k = -1; k < 2; ++k)
            {
                const int col = c + k + i;
                if (col < 0)
                    continue;

                if (col > num_cols)
                    break;

                const char value = buffer[(num_cols + 1) * line + col];
                if (!ispunct(value))
                    continue;

                if (value != default_value)
                    return true;
            }
        }
    }

    return false;
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

        const int num_digits = getNumDigits(curr, curr_size);
        if (num_digits == 0 || !hasNeighbourSymbol(data, l, c, num_digits, num_lines, num_cols))
        {
            ++c;
            continue;
        }

        sum += getNumber(curr, num_digits);

        printf("Adding %d from %dx%d with %d digits.\n", getNumber(curr, num_digits), l + 1, c + 1, num_digits);

        c += num_digits;
    }

    printf("\nSum of all of the part numbers in the engine schematic: %d\n", sum);

    free(data);

    return 0;
}