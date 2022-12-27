// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// create the global buffer
unsigned long *global_buffer = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool load(const char *dictionary)
{
    // directing the hash-table-pointers into NULL
    for (int i = 0; i < N; i ++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // create the simulators of the first symbol of the linked strings
    int symulator[N];
    for (int i = 0; i < N; i ++)
    {
        symulator[i] = i;
    }

    // create the array of the counters for the linked lists
    int counter[N];
    for (int i = 0; i < N; i ++)
    {
        counter[i] = 0;
    }

    // create the global counter
    unsigned long global_counter = 0;

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // hashing the first letter of the word
        int first_letter = hash(word);

        // locating the new word into the correct linked string
        for (int i = 0; i < N; i ++)
        {
            // if the first letter of the word is the same as the name of the linked string
            if (first_letter == symulator[i])
            {
                // create the block of memory for the new node and pointing the temporary pointer to it
                node *n = malloc(sizeof(node));
                if (!n)
                {
                    fclose(file);
                    return false;
                }

                // put the word into the address of the memory where the word-pointer points (where the word has to be)
                // put the NULL into the address where the next-pointer points (where the address of the next node has to be)
                else
                {
                    strcpy(n -> word, word);
                    n -> next = NULL;
                }

                // redirecting the pointer of the hashtable to the address where the temporary pointer points
                if (!hashtable[i])
                {
                    // if the hashtable does not exist
                    hashtable[i] = n;

                    // increase the number of counters by one
                    counter[i] ++;
                    global_counter ++;
                }

                // if the hashtable exists
                else
                {
                    for (node *ptr = hashtable[i]; ptr != NULL; ptr = ptr -> next)
                    {
                        if (!ptr -> next)
                        {
                            // pointing the temporary next-pointer into the adress where the new node exists
                            ptr -> next = n;

                            // increase the number of counters by one
                            counter[i] ++;
                            global_counter ++;

                            // getting off the loop
                            break;
                        }
                    }
                }
            }

            // getting off the loop if the word located into the correct linked string
            if (first_letter == symulator[i])
            {
                break;
            }
        }
    }

    // the control of the 26 created linked strings
    for (int i = 0; i < N; i ++ )
    {
        if (hashtable[i])
        {
            {
                int jjj = 0;
                for (node *ptr = hashtable[i]; ptr != NULL; ptr = ptr -> next)
                {
                    jjj ++ ;
                }
            }
        }
    }

    // returning the value of global_counter to global_buffer
    global_buffer = malloc(sizeof(unsigned long));
    *global_buffer = global_counter;

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
unsigned int size(void)
{
    // creating the pointer to the global buffer
    unsigned long *number_of_words;

    // if the global buffer does not exist
    if (!global_buffer)
    {
        return 0;
    }

    // if the global buffer exists
    else
    {
        // pointing the pointer to the adress where the global buffer exists
        number_of_words = global_buffer;

        // return the information is situated into the addreess the pointer points to
        return *number_of_words;
    }
}

// Returns true if word is in dictionary else false !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool check(const char *word)
{
    //create the simulators of the first symbol of the linked strings
    int symulator[N];
    for (int i = 0; i < N; i ++)
    {
        symulator[i] = i;
    }

    // if the word does not exist
    if (!word)
    {
        return false;
    }

    // defining the length of the word to be checked
    int strlen_word = strlen(word);

    // hashing the first letter of the word
    int first_letter = hash(word);

    // setting the counter of the strings
    int iii = 0;

    // define the correct linked string
    while (first_letter != symulator[iii])
    {
        iii ++ ;
    }

    // creating the temporary pointer and pointing it to the start of the correct linked string
    node *ptr3 = hashtable[iii];

    if (!hashtable[iii])
    {
        return false;
    }

    // Going to the adress pointed by (*ptr).word and pointing it by he pointer *alphabet_word   ./speller texts/austen.txt
    char *alphabet_word = ptr3 -> word;

    // create the main bool valye
    int main_bool_value = 0;

    // creating the STOP-POINT
    stop: ;

    // shifting the pointer and crossing the dictionary and looking for the word of the same length  ./speller dictionaries/small1 texts/cat.txt
    while (strlen_word != strlen(alphabet_word))
    {
        // shifting the temporary pointer into the address of the memory where the next next node is located
        ptr3 = ptr3 -> next;

        if (ptr3)
        {
            // shifting the alphabet_word pointer into the adress where the word of the next node is located
            alphabet_word = ptr3 -> word;
        }
        else
        {
            // we have reached the end of the linked string and did not find the same word in the dictionary
            return false;
        }
    }

    // the comparison of the words's letter
    for (int i = 0; i < strlen_word; i ++ )
    {
        // if the same number letters of the alphabet-word and the word to be checked are different and it is NOT the end of the linked list
        if (tolower(word[i]) != alphabet_word[i] && ptr3 -> next != NULL)
        {
            // shifting the pointer to the adress of the next node
            ptr3 = ptr3 -> next;

            // pointing the alphabet_word pointer to the address where the word of the next node is located
            alphabet_word = ptr3 -> word;

            // getting off the loop
            break;
        }

        // if the same number letters of the alphabet-word and the word to be checked are different and it is the end of the linked list
        else if (tolower(word[i]) != alphabet_word[i] && word[i + 1] == '\0' && ptr3 -> next == NULL)
        {
            // the word to be checked is absent in the dictionary
            main_bool_value = 1;
            break;
        }

        // if the current letters of the alphabet_word and the word to be checked are the same and the next symbol is '\0' (the current word is the last)
        else if (tolower(word[i]) == alphabet_word[i] && word[i + 1] == '\0')
        {
            // the word to be checked is in the dictionary
            main_bool_value = 2;
            break;
        }
    }

    if (main_bool_value == 0)
    {
        goto stop;
    }

    if (main_bool_value == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Unloads dictionary from memory, returning true if successful else false !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool unload(void)
{
    // making free the memory has given for the global buffer
    if (global_buffer)
    {
        free(global_buffer);
    }

    // Create the 1-st temporary pointer
    node *pts2 = NULL;

    // create the main bool value (if there is no any hashtable[i] - it gets the meaning 'false')
    bool main_bool_value_2 = false;

    // free the main part of the memory
    for(int i = 0; i < N; i ++)
    {
        if (hashtable[i])
        {
            //pointing the 1-st temporary pointer into the adress of the start of the current linked list
            pts2 = hashtable[i];

            // define the number of the deleted nodes
            unsigned long number_of_deleted_nodes = 0;

            // making memory free
            while (pts2 != NULL)
            {
                // creating the 2-nd temporary pointer and directing it into the address of the next node of the linked string
                node *c = pts2 -> next;

                // making free memory of the previous node of the hashtable
                free(pts2);
                number_of_deleted_nodes ++ ;

                // pointing the 1-st temporary pointer into the adress where the 2-nd tempoprary pointer points (into the adress of the next node)
                pts2 = c;
            }

            // the any hashtable[i] exists, the anloading of the hashtable has become
            main_bool_value_2 = true;
        }
    }

    if (main_bool_value_2 == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}



