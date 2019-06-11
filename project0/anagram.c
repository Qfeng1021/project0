#include "anagram.h"
#include <string.h>
//Qianyi Feng, 951439892, CIS 415 Project 0
//This is my own work except the partition() and quick_sort() function.
//Citation: Quick sort function referenced from: https://www.cnblogs.com/onepixel/articles/7674659.html

char *strlwr(char *word)
{
    if(word != NULL)
    {
        char *input = (char *)malloc(sizeof(char)*255);
        strcpy(input, word);
        int i = 0;
        for(i = 0; i < strlen(word); i++)
        {
            if(isupper(*(word + i)))
            {
                *(input + i) = tolower(*(word + i));
            }
        }
        return input;
    }
    return NULL;
}

int partition(char **str, int low, int high)
{
    int pivot = low;
    int i = pivot + 1;
    int m = 0;
    for (m = i; m <= high; m++)
    {
        if (*(*str + m) < *(*str + pivot))
        {
            char temp = *(*str + m);
            *(*str + m) = *(*str + i);
            *(*str + i) = temp;
            i = i + 1;
        }
    }
    char temp = *(*str + pivot);
    *(*str + pivot) = *(*str + i-1);
    *(*str + i-1) = temp;
    return i-1;
}


void quick_sort(char **str, int start, int end)
{
    int pos;
    if (start < end)
    {
        pos = partition(str, start, end);
        quick_sort(str, start, pos - 1);
        quick_sort(str, pos + 1, end);
    }
}

struct StringList *MallocSList(char *word)
{
    char *data = (char *)malloc(sizeof(char)*255);
    strcpy(data, word);
    struct StringList *newNode = (struct StringList *)malloc(sizeof(struct StringList));
    if(data == NULL)
    {
        printf("%s\n", "Cannot allocate space.");
        exit(-1);
    }
    newNode->Next = NULL;
    newNode->Word = data;
    return newNode;
}

void AppendSList(struct StringList **head, struct StringList *node)
{
    if(*head == NULL)
    {
        *head = node;
    }
    else
    {
        struct StringList *tail = *head;
        while(tail->Next != NULL)
        {
            tail = tail->Next;
        }
        tail->Next = node;
    }
}

void FreeSList(struct StringList **node)
{
    struct StringList *cur = *node;
    while(cur != NULL)
    {
        struct StringList *tmp = cur;
        cur = cur->Next;
        free(tmp->Word);
    }
    node = NULL;
}


void PrintSList(FILE *file, struct StringList *node)
{
    while(node != NULL)
    {
        if(file != NULL)
            {
                fprintf(file, "\t%s\n", node->Word);
            }
        else
        {
            printf("\t%s\n", node->Word);
        }
        node = node->Next;
    }
}


int SListCount(struct StringList *node)
{
    int length = 0;
    struct StringList *tail = node;
    while(tail->Next != NULL)
    {
        tail = tail->Next;
        length += 1;
    }
    return length;
}

struct AnagramList* MallocAList(char *word)
{
    char *data = (char *)malloc(sizeof(char)*255);
    strcpy(data, word);
    struct AnagramList *newNode = (struct AnagramList *)malloc(sizeof(struct AnagramList));
    if(NULL == data || NULL == newNode)
    {
        printf("%s\n", "Cannot allocate space.");
        exit(-1);
    }
    newNode->Next = NULL;
    newNode->Words = MallocSList(data);
    char *ana = strlwr(data);
    quick_sort(&ana, 0, strlen(ana) - 1);
    newNode->Anagram = ana;
    return newNode;
};

void AddWordAList(struct AnagramList **node, char *word)
{
    char data[255] = {0};
    memcpy(data, word, strlen(word) - 1);
    char *ana = strlwr(data);
    quick_sort(&ana, 0, strlen(ana) - 1);
    if(*node == NULL)
    {
        *node = MallocAList(word);
    }
    else
    {
        struct AnagramList *tail = *node;
        if (strcmp(tail->Anagram, ana) == 0)
        {
            AppendSList(&(tail->Words), MallocSList(data));
            free(ana);
            return;
        }
        else
        {
            while(tail->Next != NULL)
            {
                tail = tail->Next;
                if(strcmp(tail->Anagram, ana) == 0)
                {
                    AppendSList(&(tail->Words), MallocSList(data));
                    free(ana);
                    return;
                }
        }
        tail->Next = MallocAList(data);
        }
    }
    free(ana);
}

void FreeAList(struct AnagramList **node)
{
    struct AnagramList *cur = *node;
    while(cur != NULL)
    {
        struct AnagramList *tmp = cur;
        cur = cur->Next;
        FreeSList(&tmp->Words);
        free(tmp->Anagram);
        free(tmp);
    }
    node = NULL;
}





void PrintAList(FILE *file, struct AnagramList *node)
{
    while(node->Next != NULL)
    {
        if(SListCount(node->Words) > 1)
        {
            if(file != NULL)
            {
                fprintf(file, "%s:%i\n", node->Anagram, SListCount(node->Words));
            }
            else
            {
                printf("%s:%i\n", node->Anagram, SListCount(node->Words));
            }
            PrintSList(file, node->Words);
        }
        node = node->Next;
    }
}
