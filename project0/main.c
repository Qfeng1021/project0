#include <stdio.h>
#include <stdlib.h>
#include "anagram.h"

//Qianyi Feng, 951439892, CIS 415 Project 0
//This is my own work.
int main(int argc, char *argv[])
{
    clock_t start, stop;
    double duration;
    char buff[255] = {0};
    start = clock();
    struct AnagramList *analist = NULL;
    if(argc == 1)
    {
        while(fgets(buff, 255, stdin) != NULL)
        {
            AddWordAList(&analist, buff);
        }
        PrintAList(NULL, analist);
    }
    else if(argc == 2)
    {
        FILE *fin = NULL;
        fin = fopen(argv[1], "r");
        if(fin != NULL)
        {
            while(fgets(buff, 255, fin) != NULL)
            {
                AddWordAList(&analist, buff);
            }
            PrintAList(NULL, analist);
            fclose(fin);
        }
    }
    else if(argc == 3)
    {
        FILE *fin = NULL;
        FILE *fout = NULL;
        fin = fopen(argv[1], "r");
        fout = fopen(argv[2], "w+");
        if(fin != NULL && fout != NULL)
        {
            while(fgets(buff, 255, fin) != NULL)
            {
                AddWordAList(&analist, buff);
            }
            PrintAList(fout, analist);
        }
        if(fin != NULL)
        {
            fclose(fin);
        }
        if(fout != NULL)
        {
            fclose(fout);
        }
    }
    FreeAList(&analist);
    stop = clock();
    duration = (double)(stop - start)/CLOCKS_PER_SEC;
    printf("Time: %f\n", duration);
    return 0;
}
