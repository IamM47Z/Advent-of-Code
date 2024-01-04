/*
*   Advent of Code Challenge - Day 1
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "../utils.h"

int searchDigit(const char* data, const int data_size, const bool reverseSearch)
{
    for (int i = 0; i < data_size; i++)
    {
        const int index = reverseSearch ? (data_size - (i + 1)) : i;

        const char c = data[index];
        if (!isdigit(c))
            continue;

        return c - 0x30;
    }

    return -1;
}

int main(void)
{
    char* data = NULL;
    int data_size = getDayInput(1, &data);
    if (data_size == -1)
        return 1;
    
    int sum = 0;
    for (char* ptr = strtok(data, "\n"); ptr != NULL; ptr = strtok(NULL, "\n"))
    {
        const int size = strlen(ptr);

        const int first_digit = searchDigit(ptr, size, false);
        const int last_digit = searchDigit(ptr, size, true);

        const int number = first_digit * 10 + last_digit;
        sum += number;

        printf("Calibration value: %d\n", number);
    }

    printf("\nSum of all calibration values: %d\n", sum);

    free(data);

    return 0;
}