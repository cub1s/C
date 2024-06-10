#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *parse_file(FILE *fptr);
int selection_sort(int *unsorted, int size);
int bubble_sort(int *nptr, int size);
int write_file(int *nptr);
double timer(char method[], int *nptr);

int nchar = 100000;
int size;

int main(int argc, char *argv[])
{
    char *errorMessage = "Incorrect usage. Proper use syntax is \'sort [file] [method]\nValid sorting methods are: [selection] [bubble]\n";
    // ensure only one arg given during launch - exit if not
    if (argc != 3)
    {
        printf("%s", errorMessage);
        return 1;
    }
    // create file pointer and read file
    FILE *fptr = fopen(argv[1], "r");
    // ensure file is valid
    if (fptr == NULL)
    {
        printf("File path does not exist! Make sure it is in the same directory as this program, or specify the full path.\n");
        return 1;
    }
    int *nptr = parse_file(fptr);
    // if pointer return is NULL, exit and return failure
    if (nptr == NULL)
    {
        return 1;
    }
    // time and run selected sort method
    double runt = timer(argv[2], nptr);
    if (runt == 400)
    {
        printf("%s", errorMessage);
        return 1;
    }
    printf("Sort finished in: %f secs\n", runt);
    // write array to file - exit if it returns 1
    if (write_file(nptr))
    {
        return 2;
    }
    // close file pointer, clean up allocated space, and return success
    fclose(fptr);
    free(nptr);
    return 0;
}

int *parse_file(FILE *fptr)
{
    // assign space for string
    char raw[nchar];
    // assign characters from file to string using fgets
    fgets(raw, nchar, fptr);
    int length = strlen(raw);
    // print length of array
    printf("raw len: %d\n", length);
    // create pointer and assign space for int storage
    int *nptr = malloc(sizeof(int) * length);
    // if memory allocation returns NULL pointer,
    // return function NULL - this will be used to
    // exit program in emergency
    if (nptr == NULL)
    {
        return NULL;
    }
    // use strtok to get pointer to first chars of file
    // delimiting based on ","
    char *num = strtok(raw, ",");
    // iterate over raw
    for (int i = 0; i < length; i++)
    {
        if (num == NULL)
        {
            break;
        }
        else
        {
            size++;
            // convert string to integer
            int parsed_int = atoi(num);
            // add integer to array
            nptr[i] = parsed_int;
            // using NULL for strtok here moves pointer to
            // next delimited char
            num = strtok(NULL, ",");
        }
    }
    // return pointer for string
    if (nptr == NULL)
    {
        return NULL;
    }
    else
    {
        return nptr;
    }
}

int selection_sort(int *nptr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int smallest_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (nptr[smallest_idx] > nptr[j])
            {
                smallest_idx = j;
            }
        }
        int tmp = nptr[i];
        nptr[i] = nptr[smallest_idx];
        nptr[smallest_idx] = tmp;
    }
    return 0;
}

int bubble_sort(int *nptr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (nptr[j] > nptr[j + 1])
            {
                int tmp = nptr[j];
                nptr[j] = nptr[j + 1];
                nptr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
    return 0;
}

double timer(char method[], int *nptr)
{
    double runt;
    time_t t;
    t = clock();
    // maybe make this a switch statement when more sorting methods implemented?
    if (!strcmp(method, "selection"))
    {
        // sort array
        selection_sort(nptr, size);
    }
    else if (!strcmp(method, "bubble"))
    {
        bubble_sort(nptr, size);
    }
    else
    {
        return 400;
    }
    t = clock() - t;
    // calculate function run time
    runt = ((double)t) / CLOCKS_PER_SEC;
    return runt;
}

int write_file(int *nptr)
{
    FILE *fptr = fopen("sorted.csv", "w");
    if (fptr == NULL)
    {
        printf("ERROR: Could not write file.");
        return 1;
    }
    for (int i = 0; i < size; i++)
    {
        if (i != size - 1)
        {
            fprintf(fptr, "%i,", nptr[i]);
        }
        else
        {
            fprintf(fptr, "%i", nptr[i]);
        }
    }
    fclose(fptr);
    return 0;
}
