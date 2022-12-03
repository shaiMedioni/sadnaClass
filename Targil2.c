//-------------   INCLUDES ----------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//------------ PROTOTYPES -------------------
int* hammingDdistance(const char** const * parrPP, int*);
void search(const char** pWord, const char** next_word, const char** const * parrPP, int** pRes, int* pSize);
int* compute_distance(const char *s1, const char *s2);


////------------ M A I N  -------------------
int  main()
{
    char * arrP1[] = { "father", "mother", NULL };
    char * arrP2[] = { "sister", "brother", "grandfather", NULL };
    char * arrP3[] = { "grandmother", NULL };
    char * arrP4[] = { "uncle", "aunt", NULL };
    char ** arrPP[] = { arrP1, arrP2, arrP3, arrP4 , NULL };
    int size, i;

    int* res = hammingDdistance(arrPP, &size);
    for (i = 0; i < size; i++ )
        printf("%5d", *(res + i));
    return 0;
}


//--------------------------   METHODS  -------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
//  Find  all match string by length for current string
//  Input:
//         pWord -- pointer to current string
//         next_word   -- pointer to next string
//         parrPP   --
//         pRes -- pointer to result distance array
//         pSize -- pointer to length of result distance array
//  Output:
//         pointer to fisrst max value  in source array
//---------------------------------------------------------------------------------------------------------------
void search(const char** pWord, const char** next_word, const char** const * parrPP, int** pRes, int* pSize)
{
    while (*parrPP)
    {
        // Go over array of pointers to string
        while (*next_word)
        {
            if (strlen(*pWord) == strlen(*next_word))
            {
                *pRes = (int*)realloc(*pRes, ++(*pSize) * sizeof(int));
                *(*pRes + *pSize - 1) = *compute_distance(*pWord, *next_word);
            }
            next_word++;
        }
        next_word = *++parrPP;    // pointer to next array of pointers to string
    }
}


//---------------------------------------------------------------------------------------------------------------
//  Calculate hamming ddistance for 2 strings
//  Input:
//         s1 -- pointer to first  string
//         s2 -- pointer to second string
//  Output:
//         hamming ddistance for 2 strings
//---------------------------------------------------------------------------------------------------------------
int* compute_distance(const char *s1, const char *s2)
{
    int *count = (int*)malloc(sizeof(int));
    *count = 0;
    while (*s1)
        *count += *s1++ != *s2++;
    return count;
}

//---------------------------------------------------------------------------------------------------------------
// Calculate hamming ddistance for all strings in source structure
//  Input:
//         parrPP --
//  Output:
//         pointer to result distance array
//---------------------------------------------------------------------------------------------------------------
int* hammingDdistance(const char** const * parrPP, int* size)
{
    int* res = NULL;

    *size = 0;

    // Go over array of pointers to arrays of pointers to string
    while (*parrPP)
    {
        const char** parrP = *parrPP;    // pointer to any array of pointers to string
        // Go over array of pointers to string
        while (*parrP)
        {
            search(parrP, parrP + 1, parrPP, &res, size);
            parrP++;
        }
        parrPP++;
    }

    return res;
}