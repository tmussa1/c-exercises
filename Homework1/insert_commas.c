#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHARACTERS 100

int is_all_digits(char str[MAX_CHARACTERS]);
void insertCommas();

int main() {
    insertCommas();
    return 0;
}

/**
 * Inserts a comma delimiter for big numbers
 */
void insertCommas(){

    char buffer[MAX_CHARACTERS];
    char result[MAX_CHARACTERS];

    printf("Number?");
    scanf("%s", buffer); // Read in upto 100 digits
    int length = (int) strlen(buffer);

    if(is_all_digits(buffer)){
        int modLength = length % 3;
        int index = 0, resultIndex = 0;
        while(index <= length){
            if(index != length && index != 0) {
                if (
                        (((index > modLength)
                         && (((((modLength + index - 2) % 3 == 0) && modLength == 1) // Insert comma if remainder is 1
                             || (((modLength + index - 1) % 3 == 0) && modLength == 2) // Insert comma if remainder is 2
                             || (index % 3 == 0 && modLength == 0)))) // Insert comma if remainder is 0
                         || (index == modLength))) {
                    result[resultIndex++] = ',';
                }
            }
            result[resultIndex++] = buffer[index++]; // Increment buffer's index after reading in
        }
    }

    printf("%s", result);
    printf("\n");
}
/**
 * Checks if a string contains all digits
 * @param str
 * @return
 */
int is_all_digits( char str[MAX_CHARACTERS] )
{
    int	pos;
    pos = 0;
    while( str[pos] != '\n' && str[pos] != '\0'){
        if ( ! isdigit(str[pos]) )
            return 0;
        pos++;
    }
    return 1;
}