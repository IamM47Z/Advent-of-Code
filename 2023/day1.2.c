/*
*   Advent of Code Challenge - Day 1 - Part Two
*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "../utils.h"

char* digits_spelled[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int getDigit(const char* ptr_data)
{
    if (isdigit(ptr_data[0]))
        return ptr_data[0] - 0x30;

    const int data_size = strlen(ptr_data);
    for (int i = 0; i < 9; i++)
    {
        char* digit = digits_spelled[i];
        int digit_len = strlen(digit);
        if (data_size < digit_len)
            continue;

        if (memcmp(digit, ptr_data, digit_len) != 0)
            continue;

        return i + 1;
    }

    return -1;
}

int searchDigit(const char* data, const int data_size, const bool reverseSearch)
{
    for (int i = 0; i < data_size; i++)
    {
        const char* ptr_data = data + (reverseSearch ? (data_size - (i + 1)) : i);
        int digit = getDigit(ptr_data);
        if (digit == -1)
            continue;
        
        return digit;
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
    for (char* ptr_line = strtok(data, "\n"); ptr_line != NULL; ptr_line = strtok(NULL, "\n"))
    {
        const int size = strlen(ptr_line);

        const int first_digit = searchDigit(ptr_line, size, false);
        const int last_digit = searchDigit(ptr_line, size, true);

        if (first_digit == -1 || last_digit == -1)
        {
            printf("Invalid input: %s\n", ptr_line);
            return 1;
        }

        const int number = first_digit * 10 + last_digit;
        sum += number;

        printf("Calibration value: %d\n", number);
    }

    printf("\nSum of all calibration values: %d\n", sum);

    free(data);

    return 0;
}