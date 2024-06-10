#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generator(void);

int main(void)
{
    if (generator())
    {
        return 2;
    }
    return 0;
}

int generator(void)
{
    FILE *fptr = fopen("rand.csv", "w");
    if (fptr == NULL)
    {
        printf("ERROR: Could not write file.");
        return 1;
    }
    int n = 10000;
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < n; i++)
    {
        int r = rand() % 5000;
        if (i != n - 1)
        {
            fprintf(fptr, "%i,", r);
        }
        else
        {
            fprintf(fptr, "%i", r);
        }
    }
    fclose(fptr);
    return 0;
}