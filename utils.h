#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getDayInput(int day, char** ptr_output)
{
    char filename[12];
    snprintf(filename, 12, "day%d.input", day);

    FILE * ptr_file = fopen(filename, "r");
    if (!ptr_file)
        return -1;

    fseek(ptr_file, 0, SEEK_END);

    long size = ftell(ptr_file);

    rewind(ptr_file);

    *ptr_output = (char*)malloc(sizeof(char) * size);
    if (!*ptr_output)
    {
        fclose(ptr_file);
        return -1;
    }

    fread(*ptr_output, 1, size, ptr_file);

    fclose(ptr_file);

    return size;
}