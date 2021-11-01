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

// TODO - remove unused files, ask about iterator, make functions shorter
// TODO - read guideline, ask if returning prev is a good approach, write readme
// TODO - what if non-small letter is somewhere there not as a first character
// TODO - get rid of strcmp in all places

LINK hash_table [ARRAY_SIZE];
int current_row;
LINK * current_link;

/**
 * Auxiliary function to find a node in LinkedList
 * Returns the node before where the node is to be found if
 * node is not found
 * @param str
 * @return LINK
 */
LINK * find_node(char str[])
{
    // Error checking for empty string
    if(strlen(str) == 0) {
        return NULL;
    }

    char first_letter = str[0];
    int index = first_letter - 'a';

    // Only one of the 26 characters are handled
    if(index >= ARRAY_SIZE){
        return NULL:
    }

    LINK * linkp = hash_table[index].next, * prev = NULL;

    // Return the previous node to what we are looking
    // for if the node doesn't exist
    while(linkp != NULL) {
        if(strcmp(linkp->word, str) == 0) {
            return linkp;
        } else if(strcmp(linkp->word, str) > 0) {
            return prev;
        }
        prev = linkp;
        linkp = linkp->next;
    }

    return NULL;
}

/**
 * Initializes the list
 */
void init_table()
{

    int i = 0;

    // Set all next pointers to null
    while(i < ARRAY_SIZE) {
        hash_table[i++].next = NULL;
    }

    // Reset current row
    current_row = 0;
}

/**
 * Looks for a word in the table
 * @param str
 * @return YES or NO
 */
int	in_table(char str[])
{
    // Find the node if exists
    LINK * node = find_node(linkp, str);

    // Return the found node if it exists and
    // contains the right value
    return  node != NULL ? strcmp(node->word, str) == 0 ? YES : NO : NO;
}

/**
 * Auxiliary function to insert a word
 * at the beginning of a list when list is null
 * @param str
 */
void insert_in_the_beginning(char str[])
{

    char first_letter = str[0];
    int index = first_letter - 'a';

    // Check if character is small cap
    if(index >= ARRAY_SIZE){
        return NO:
    }

    // Insert it
    hash_table[index].next = newlink;
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

    newlink->word = newstr;
    newlink->value = value;

    return newlink;
}

/**
 * Insert a string in a correct position of a sorted order
 * @param str
 * @param value
 * @return YES or NO
 */
int	insert(char str[], int value)
{

    if(strlen(str) == 0){
        return NO;
    }

    // Initialize the node
    LINK * newlink = intialize_new_link(str, value);

    if(newlink == NULL) {
        return NO;
    }

    LINK * node = find_node(linkp, str);

    // Insert it in the beginning if the list is empty
    // Or in the correct sorted position
    if(node == NULL) {
        insert_in_the_beginning(str);
    } else {
        newlink->next = node->next;
        node->next = newlink;
    }

    return YES;
}

/**
 * Looks up the value associated with a word
 * @param str
 * @return value
 */
int	lookup(char str[]) {

    // Find the node if exists
    LINK * node = find_node(linkp, str);

    // Another check is needed to see if the
    // found node is correct one
    return  node != NULL ? strcmp(node->word, str) == 0 ? node->value : 0 : 0;
}

/**
 * Updates with new value if the node is found
 * @param str
 * @param value
 * @return YES or NO
 */
int	update(char str[], int value)
{

    LINK * node = find_node(linkp, str);

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
    current_link = hash_table[current_row].next;

    return nextword();
}

/**
 * Traverses the entire table
 * @return char pointer
 */
char * nextword()
{

    char * retval;

    if(current_row >= ARRAY_SIZE){
        return NULL;
    }

    // Find the first non-empty list
    while(current_link == NULL && current_row < ARRAY_SIZE){
        current_link = hash_table[current_row++]->next;
    }

    // The entire list is empty
    if(current_link == NULL){
        return NULL;
    }

    // Return value
    retval = current_link->value;
    current_link = current_link->next;

    return retval;
}

/**
 * Auxiliary function to find previous node
 * @param str
 * @return LINK
 */
LINK * find_previous_node(char str[]) {

    char first_letter = str[0];
    int index = first_letter - 'a';

    if(index >= ARRAY_SIZE){
        return NULL;
    }

    // Iterators
    LINK * linkp = hash_table[index].next, * prev = NULL;

    // Returns previous if found
    while(linkp != NULL) {
        if(strcmp(linkp->word, str) == 0) {
            return prev;
        }

        // Previous is trailing one step behind
        prev = linkp;
        linkp = linkp->next;
    }

    return NULL;
}

/**
 * Deletes a word from the table
 * @return YES or NO
 */
int	word_delete(char [] str)
{

    LINK * node = find_node(str);

    if(node != NULL && strcmp(node->word, str) == 0){

        // Finds the previous node
        LINK * prev = find_previous_node(str);

        // Works even if prev is the head pointer
        // Sets prev->next to null if prev was head
        prev->next = node->next;
        free(node->word);
        free(node);

        return YES;
    }

    return NO;
}