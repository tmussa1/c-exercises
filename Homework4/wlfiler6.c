#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"wl.h"

#define NUM_CHARACTERS 26

struct link {
    char * word;
    int value;
    struct link * next;
};

// TODO - remove unused files, use short notation for struct, ask about iterator, make functions shorter
// TODO - read guideline

struct link hash_table [NUM_CHARACTERS];
int current_row;
struct link * current_link;

struct * find_node(char str[])
{

    if(strlen(str) == 0) {
        return NULL;
    }

    char first_letter = str[0];
    int index = first_letter - 'a';

    if(index >= NUM_CHARACTERS){
        return NULL:
    }

    struct link * linkp = hash_table[index].next, * prev = NULL;

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

void init_table()
{

    int i = 0;

    while(i < NUM_CHARACTERS) {
        hash_table[i++].next = NULL;
    }

    current_row = 0;
}

int	in_table(char str[])
{
    struct link * node = find_node(linkp, str);

    return  node != NULL ? strcmp(node->word, str) == 0 ? YES : NO : NO;
}


int	insert(char str[], int value)
{

    if(strlen(str) == 0){
        return NO;
    }

    char * newstr;
    struct link * newlink;

    newstr = malloc(1 + strlen(str));

    if(newstr == NULL){
        return NO;
    }

    strcpy(newstr, str);
    newlink = malloc(sizeof (struct link));

    if(newlink == NULL){
        free(newstr);
        return NO;
    }

    newlink->word = newstr;
    newlink->value = value;

    struct link * node = find_node(linkp, str);

    if(node == NULL) {

        char first_letter = str[0];
        int index = first_letter - 'a';

        if(index >= NUM_CHARACTERS){
            return NO:
        }

        hash_table[index].next = newlink;

    } else {

        newlink->next = node->next;
        node->next = newlink;
    }

    return YES;
}

int	lookup(char str[]) {

    struct link * node = find_node(linkp, str);

    return  node != NULL ? strcmp(node->word, str) == 0 ? node->value : 0 : 0;
}

int	update(char str[], int value)
{

    struct link * node = find_node(linkp, str);

    if(strcmp(node->word, str) == 0) {
        node->value = value;
        return YES;
    }

    return NO;
}


char * firstword()
{
    current_row = 0;
    current_link = hash_table[current_row].next;

    return nextword();
}

char * nextword()
{

    char * retval;

    if(current_row >= NUM_CHARACTERS){
        return NULL;
    }

    while(current_link == NULL && current_row < NUM_CHARACTERS){
        current_link = hash_table[current_row++]->next;
    }

    if(current_link == NULL){
        return NULL;
    }

    retval = current_link->value;
    current_link = current_link->next;

    return retval;
}

int	word_delete(char [])
{

}