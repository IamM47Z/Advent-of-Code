#pragma once

#include <math.h>
#include <stdio.h>
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

int digits_in_number(const int number)
{
    return number == 0 ? 1 : (log10(number) + 1);
}