/**
 * This file deletes all occurences of the second array's characters
 * from the first character array
 */

#include <stdio.h>
#include <string.h>

char * delete_chars(char original[], char what_to_delete[]);
char * delete_chars_ptr(char original[], char what_to_delete[]);

int main()
{

    char original[] = "aabbccddefpout";
    char what_to_delete[]= "dbat";

    delete_chars_ptr(original, what_to_delete);
    delete_chars(original, what_to_delete);

    return 0;
}

/**
 * Deletes a character by shifting to the left using
 * indexes
 * @param original
 * @param what_to_delete
 * @return
 */
char * delete_chars(char original[], char what_to_delete[]){
    size_t org_size = strlen(original), to_delete_size = strlen(what_to_delete);

    for(int i = org_size - 1; i >= 0; i--){
        for(int j = 0; j < to_delete_size; j++){

            char c = what_to_delete[j];

            if(original[i] == c){

                original[i] = original[i+1];

                for(int k = i; k < org_size; k++)
                {
                    original[k] = original[k + 1];
                }
                org_size--;
                j--;
            }
        }
    }

    printf("%s with index \n", original);

    return original;
}

/**
 * Deletes a character by shifting to the left
 * using pointer arithmetic
 * @param original
 * @param what_to_delete
 * @return
 */
char * delete_chars_ptr(char original[], char what_to_delete[]){
    size_t org_size = strlen(original), to_delete_size = strlen(what_to_delete);

    for(int i = org_size - 1; i >= 0; i--){
        for(int j = 0; j < to_delete_size; j++){

            char c = *(what_to_delete + j);

            if(original[i] == c){

                *(original + i) = *(original + i);

                for(int k = i; k < org_size; k++)
                {
                    *(original + k) = *(original + k + 1);
                }
                org_size--;
                j--;
            }
        }
    }

    printf("%s with pointer\n", original);

    return original;
}