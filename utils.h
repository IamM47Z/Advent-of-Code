#pragma once

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int getDayInput(const int day, char** ptr_output)
{
    char filename[12];
    snprintf(filename, 12, "day%d.input", day);

    FILE * ptr_file = fopen(filename, "r");
    if (!ptr_file)
        return -1;

    fseek(ptr_file, 0, SEEK_END);

    long size = ftell(ptr_file);

    rewind(ptr_file);

    char* output = (char*)malloc(sizeof(char) * size);
    if (!output)
    {
        fclose(ptr_file);
        return -1;
    }

    fread(output, 1, size, ptr_file);

    fclose(ptr_file);

    *ptr_output = output;
    return size;
}

int digitsInNumber(const int number)
{
    return number == 0 ? 1 : (log10(number) + 1);
}

int getNumLines(const char* buffer, const int size)
{
    int num = 0;

    for (int i = 0; i < size; i++)
        num += (buffer[i] == '\n');
    
    return ++num;
}

int getNumCols(const char* buffer, const int size)
{
    for (int i = 0; i < size; i++)
        if (buffer[i] == '\n')
            return i;
    
    return -1;
}

int getNumDigits(const char* buffer, const int size)
{
    int num = 0;

    while (num < size && isdigit(buffer[num]))
        ++num;
    
    return num;
}

int getNumber(const char* buffer, const int size)
{
    int num = 0;

    for (int i = 0; i < size; ++i)
    {
        const int curr = buffer[i] - 0x30;
        num += curr * pow(10, (size - i - 1));
    }

    return num;
}