#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <xxhash.h>
#include <math.h>

#define MAX_WORD_LEN 20
#define HASH_TABLE_SIZE 200000
#define BLUE "\033[0;34m"
#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define RESET "\033[0;37m"


struct HashTable
{
  char* key;
  XXH64_hash_t hash;
  struct HashTable* next;
};

struct HashTable* hashTable[HASH_TABLE_SIZE];

XXH64_hash_t getHash(char* key)
{
  return XXH64(key, strlen(key), 0);
}

void insertWord(char* key)
{
  XXH64_hash_t hash = getHash(key);
  int index = hash % HASH_TABLE_SIZE;
  struct HashTable* entry = hashTable[index];
  while(entry)
  {
        if(strcmp(entry->key,key)==0)
        {
            return;
        }
        entry = entry->next;
  }

  entry = (struct HashTable*) malloc(sizeof(struct HashTable));
  entry->key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  strcpy(entry->key, key);
  entry->hash = hash;
  entry->next = hashTable[index]; //previous head
  hashTable[index] = entry; //new head
}

int LevenshteinDistance(char* s, char* t)
{
    int m = strlen(s);
    int n = strlen(t);
    int d[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
    {
        d[i][0] = i;
    }
    for (int j = 0; j <= n; j++)
    {
        d[0][j] = j;
    }
    for (int j = 1; j <= n; j++)
    {
        for (int i = 1; i <= m; i++)
        {
            if (s[i - 1] == t[j - 1])
            {
                d[i][j] = d[i - 1][j - 1];
            }
            else
            {
                d[i][j] = 1 + fmin(d[i - 1][j], fmin(d[i][j - 1], d[i - 1][j - 1]));
            }
        }
    }
    return d[m][n];
}

int main()
{

    FILE *fp = fopen("dict.txt", "r");
    if (!fp)
    {
        printf(RED"Error opening file\n"RESET);
        exit(1);
    }

    char word[MAX_WORD_LEN];
    char buffer[MAX_WORD_LEN];

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        sscanf(buffer, "%s", word);
        insertWord(word);
    }
    fclose(fp);

    // Prompt the user for a word
    char input[MAX_WORD_LEN];
    printf(BLUE"\n                        SPELLCHECKER\n--------------------------------------------------------------\n");
    printf("Enter a word: "RESET);
    scanf("%s", input);

    int exists = 0;

    XXH64_hash_t input_hash = getHash(input);
    int index = input_hash % HASH_TABLE_SIZE;
    struct HashTable* entry = hashTable[index];

    while (entry)
    {
        if (strcmp(entry->key,input)==0)
        {
            exists = 1;
            break;
        }

        entry = entry->next;
    }

    if (exists)
    {
        printf(CYAN"The word is spelled correctly.\n"RESET);
    } 

    else
    {
        printf(RED"The word is spelled incorrectly.\n\n"RESET);
        printf(BLUE"Did you mean:\n"RESET);

        int min_distance = MAX_WORD_LEN;
        int closest_words_count = 0;
        char closest_words[10][MAX_WORD_LEN];  // for storing 10 closest word

        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            entry = hashTable[i];
            while (entry)
            {
                int distance = LevenshteinDistance(input, entry->key);
                if (distance < min_distance)
                {
                    closest_words_count = 1;  // resetting closest words array
                    min_distance = distance;
                    strcpy(closest_words[0], entry->key);
                }
                else if (distance == min_distance)
                {
                    if (closest_words_count < 10)
                    {
                        strcpy(closest_words[closest_words_count], entry->key);
                        closest_words_count++;
                    }
                }
                entry = entry->next;
            }
        }

        for(int i=0; i<closest_words_count; i++)
        {
            printf("%s, ", closest_words[i]);
        }

        printf("\n");
    }
    printf("--------------------------------------------------------------\n");
    getchar();
    return 0;
}