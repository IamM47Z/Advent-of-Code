/*
*   Advent of Code Challenge - Day 1
*/
#include <stdio.h>
#include <ctype.h>

#include "../utils.h"

int main(void)
{
    char* data = NULL;
    int data_size = getDayInput(1, &data);
    if (data_size == -1)
        return 1;
    
    int max_elf = 0, max_elf_id = 0;
    int current_elf = 0, current_elf_id = 0;
    for (char* current = data; data + data_size > current; )
    {
        if (!isdigit(current[0]))
        {
            if (current_elf > max_elf)
            {
                max_elf = current_elf;
                max_elf_id = current_elf_id;
            }

            current++;
            current_elf = 0;
            current_elf_id++;
            continue;
        }

        current_elf += atoi(current);

        int size = 1;
        while (current[size++] != '\n');
        
        current += size;
    }

    printf("The Elf with the most Calories is %d with %d Calories!\n", max_elf_id + 1, max_elf);

    free(data);

    return 0;
}