#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"wl.h"

/**
 *	wordlist table module version 6
 *
 *	functions are:
 *			init_table()	- set up this module
 *			in_table(str)	- sees if word is in table
 *			insert(str,val) - insert value into table
 *			lookup(str)	- retrieve value
 *			update(str,val) - update value in table
 *			firstword()	- return first word in table
 *			nextword()	- return next word in table
 */

#define ARRAY_SIZE 26


/**
 * LinkedList for storing words and their frequency
 */
struct link {
    char * word;
    int value;
    struct link * next;
};

typedef struct link LINK;

static LINK hash_table [ARRAY_SIZE];
static int current_row;
static LINK * current_link;

/**
 * Initializes the table
 */
void init_table()
{

    int i = 0;

    // Set all next pointers and values to null
    while(i < ARRAY_SIZE){
        hash_table[i].word = NULL;
        hash_table[i].value = 0;
        hash_table[i++].next = NULL;
    }
}

/**
 * AN auxiliary function that checks if the first letter is a valid
 * small letter character
 * @param str
 * @return YES or NO
 */
static int validate_string(char str[])
{
    if(strlen(str) == 0){
        return NO;
    }

    char first_letter = str[0];

    if(first_letter < 'a' || first_letter > 'z'){
        return NO;
    }

    return YES;
}

/**
 * Returns the node before the node containing the word
 * @param str
 * @return LINK
 */
static LINK * find_previous_node(char str[])
{

    if(validate_string(str)){

        int index = str[0] - 'a';

        LINK * linkp = hash_table[index].next, * prev = &hash_table[index];

        while(linkp != NULL) {

            if(strcmp(linkp->word, str) == 0) {
                return prev; // Found it
            }
            else if(strcmp(linkp->word, str) > 0) {
                return NULL; // Exit early
            }

            prev = linkp;
            linkp = linkp->next;
        }
    }

    return NULL;
}

/**
 * Returns the node containing word
 * @param str
 * @return LINK
 */
static LINK * find_node(char str[])
{

    if(validate_string(str)) {

        int index = str[0] - 'a';

        LINK * linkp = hash_table[index].next;

        // Traverse the table to find node
        while (linkp != NULL) {
            if (strcmp(linkp->word, str) == 0) {
                return linkp;
            } else if (strcmp(linkp->word, str) > 0) {
                return NULL; // Exit early
            }

            linkp = linkp->next;
        }
    }

    return NULL;
}

/**
 * Checks if a word is in the table
 * @param str
 * @return YES or NO
 */
int	in_table(char str[])
{
    LINK * node = find_node(str);

    return  node != NULL ? YES : NO;
}

/**
 * Initializes new node
 * @param str
 * @param value
 * @return LINK
 */
LINK * intialize_new_link(char str[], int value)
{
    LINK * newlink;

    char * newstr = malloc(1 + strlen(str));

    if(newstr == NULL){
        return NULL;
    }

    strcpy(newstr, str);
    newlink = malloc(sizeof (LINK));

    // Deallocate memory if malloc fails
    if(newlink == NULL){
        free(newstr);
        return NULL;
    }

    // Copy word and its value
    newlink->word = newstr;
    newlink->value = value;

    return newlink;
}

/**
 * Finds the correct position to insert a word
 * @param str
 * @return LINK
 */
static LINK * find_correct_position(char str[])
{
    char first_letter = str[0];
    int index = first_letter - 'a';

    LINK * node = hash_table[index].next, * prev = &hash_table[index];

    while(node){

        // Correct position to insert word
        if(strcmp(node->word, str) > 0){
            break;
        }

        prev = node;
        node = node->next;
    }

    return prev;
};

/**
 * Inserts word to the correct position in sorted order
 * @param str
 * @param value
 * @return YES or NO
 */
int	insert(char str[], int value)
{

    if(validate_string(str)){

        // Initialize the node
        LINK * newlink = intialize_new_link(str, value);

        if(newlink == NULL) {
            return NO;
        }

        // Correct position in sorted order
        // Will be inserted first com first serve when there are duplicates
        LINK * prev = find_correct_position(str);

        newlink->next = prev->next;
        prev->next = newlink;

        return YES;
    }

    return NO;
}

/**
 * Returns the value associated with a word
 * @param str
 * @return value
 */
int	lookup(char str[])
{
    // Find the node if exists
    LINK * node = find_node(str);

    return node != NULL ? node->value : 0;
}


/**
 * Updates with new value if the node is found
 * @param str
 * @param value
 * @return YES or NO
 */
int	update(char str[], int value)
{

    LINK * node = find_node(str);

    // Updates with new value if the node is found
    if(strcmp(node->word, str) == 0) {
        node->value = value;
        return YES;
    }

    return NO;
}


/**
 * Resets the word to the first one in the table
 * @return char pointer
 */
char * firstword()
{
    current_row = 0;
    current_link = hash_table[current_row++].next;

    return nextword();
}

/**
 * Traverses the entire table
 * @return char pointer
 */
char * nextword()
{

    char * retval;

    while(current_link == NULL && current_row < ARRAY_SIZE){
        current_link = hash_table[current_row++].next;
    }

    if(current_link == NULL){
        return NULL;
    }

    // Keep return value
    retval = current_link->word;
    current_link = current_link->next;

    return retval;
}

/**
 * Deletes a word from the table
 * @return YES or NO
 */
int	word_delete(char str[])
{

    // Finds the previous node
    LINK * prev = find_previous_node(str);

    // The next node is the node containing the word
    LINK * node = prev->next;

    if(node == NULL){
        return NO;
    }

    // Works even if prev is the head pointer
    // Sets prev->next to null if prev was head
    prev->next = node->next;

    free(node->word);
    free(node); // Free up memory

    return YES;
}