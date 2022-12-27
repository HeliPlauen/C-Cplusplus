#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

unsigned long long get_unsigned_long_long();
bool digit_check(char key[]);
int strln(char s[]);
unsigned long long multipl(unsigned long long Num1, unsigned long long Num2);
unsigned long long get_intermediate_numbers(unsigned long long Number, int length);
int number_length(unsigned long long Number);
int decimal(unsigned long long Number, int length);
int check_length_number(unsigned long long Number);
void check_ADBC(int Number);

// creating the global variables
int COUNT_5 = 0;
int COUNT_8 = 0;
int COUNT_9 = 0;


// creating the main function
int main(void)
{
    // getting data from user
    printf("Input the 1-st number X: ");
    unsigned long long NUMBERS_1 = get_unsigned_long_long();
    printf("Input the 2-nd number Y: ");
    unsigned long long NUMBERS_2 = get_unsigned_long_long();

    // getting result of the multiplying
    unsigned long long MULTIPLY = multipl(NUMBERS_1, NUMBERS_2);
    printf("THE RESULT X*Y IS: %llu\n", MULTIPLY);
    printf("CHECKING X*Y: %llu\n", NUMBERS_1 * NUMBERS_2);
    printf("We have gotten 5 for times: %i\n", COUNT_5);
    printf("We have gotten 8 for times: %i\n", COUNT_8);
    printf("We have gotten 9 for times: %i\n", COUNT_9);
}


/* creating the subsidiary functions
The subsidiary functions legend:
 - string - is string;
 - Number, length - is an integer */


// the function getting data from user +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long long get_unsigned_long_long()
{
    char string[80];
    while (true)
    {
        scanf("%s", string);
        if (digit_check(string))
        {
            unsigned long long Number = strtoull(string, 0, 0);
            return Number;
        }
    }
}


// the function checking if only digits in string (future positive long long integer) ++++++++++++++++++++++++++++++++++++++++++++
bool digit_check(char string[])
{
    for (int i = 0; i < strln(string); i++)
    {
        if (!isdigit(string[i]))
        {
            return false;
        }
    }
    return true;
}


// the function getting the length of the string ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int strln(char string[])
{
    int i = 0;
    while (string[i] != '\0')
    {
        i ++ ;
    }
    return i;
}


// the recursion-function creating the multiply function +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long long multipl(unsigned long long Num1, unsigned long long Num2)
{
    // checking if the numbers are not zero
    if (Num1 == 0 || Num2 == 0)
    {
        return 0;
    }

    // checking if the inpued integers have length 1
    if (number_length(Num1) == 1 && number_length(Num2) == 1)
    {
        return Num1 * Num2;
    }

    // checking if the 1-st and the 2-nd multypliers are the degree of 2
    int length_Number_1 = check_length_number(Num1);
    int length_Number_2 = check_length_number(Num2);

    // checking the INPUT-numbers if these ones have the same lengths
    if (length_Number_1 > length_Number_2)
    {
        length_Number_2 = length_Number_1;
    }
    else if (length_Number_1 < length_Number_2)
    {
        length_Number_1 = length_Number_2;
    }

    // getting the INTERMADEATE-numbers for the elenents
    int decim_1 = decimal(Num1, length_Number_1);
    unsigned long long A = get_intermediate_numbers(Num1, length_Number_1);
    unsigned long long B = Num1 - A * decim_1;
    int decim_2 = decimal(Num2, length_Number_2);
    unsigned long long C = get_intermediate_numbers(Num2, length_Number_2);
    unsigned long long D = Num2 - C * decim_2;

    // getting the final values
    unsigned long long AC = multipl(A, C);
    unsigned long long BD = multipl(B, D);
    unsigned long long First = A + B;
    unsigned long long Second = C + D;
    unsigned long long ADBC = multipl(First, Second) - AC - BD;

    // checking if the ad * bc is equal to the values we are looking for
    check_ADBC(ADBC);

    // getting the result
    unsigned long long XY = AC * decim_1 * decim_1 + ADBC * decim_1 + BD;

    // returning the result to the main function
    return XY;
}


// the function getting the intermediate numbers ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long long get_intermediate_numbers(unsigned long long Number, int length)
{
    if (Number == 0)
    {
        return 0;
    }
    unsigned long long Intermed = Number;
    int i = 0;
    while (i != length / 2)
    {
        Intermed /= 10;
        i ++ ;
    }
    return Intermed;
}


// the function getting the length of the number ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int number_length(unsigned long long Number)
{
    if (Number == 0)
    {
        return 0;
    }
    int i = 0;
    while (Number != 0)
    {
        Number /= 10;
        i ++ ;
    }
    return i;
}


// the function getting the decimal divisor +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int decimal(unsigned long long Number, int length)
{
    int i = 0;
    int decimal = 1;
    if (length != 0)
    {
        while (i != length / 2)
        {
            Number /= 10;
            decimal *= 10;
            i ++ ;
        }
    }
    return decimal;
}


// the function checking if the multyplier is the degree of 2 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int check_length_number(unsigned long long Number)
{
    if (Number == 0)
    {
        return 0;
    }
    int length_Num = number_length(Number);
    float control = number_length(Number);
    int j = 0;
    while (control >= 2)
    {
        while (control >= 2)
        {
            control /= 2;
        }
        if (control != 1)
        {
            j ++ ;
            length_Num = number_length(Number) + j;
            control = number_length(Number) + j;
        }
    }
    return length_Num;
}


// the function checking if the ad * bc is equal to the values we are looking for !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void check_ADBC(int Number)
{
    if (Number == 5)
    {
        COUNT_5 ++ ;
    }
    if (Number == 8)
    {
        COUNT_8 ++ ;
    }
    if (Number == 9)
    {
        COUNT_9 ++ ;
    }
}



