#include <iostream>
using namespace std;

#include "InfInt.h"

InfInt multipl(InfInt Num1, InfInt Num2);
InfInt get_intermediate_numbers(InfInt Number, int length);
int number_length(InfInt Number);
int decimal(InfInt Number, int length);
int check_length_number(InfInt Number);
void check_ADBC(InfInt Number);

// creating the global variables
int COUNT_45 = 0;
int COUNT_9 = 0;
int COUNT_8 = 0;


// creating the main function
int main()
{
    // getting data from user
    InfInt NUMBERS_1 = "34215432964249374812219364786397";
    InfInt NUMBERS_2 = "94541964835273822784327848699719";
    cout << "Input the 1-st number X: " << NUMBERS_1 << endl;
    cout << "Input the 2-nd number Y: " << NUMBERS_2 << endl;

    // getting result of the multiplying
    InfInt MULTIPLY_2 = NUMBERS_1 * NUMBERS_2;
    cout << "CHECKING X*Y: " << MULTIPLY_2 << endl;
    InfInt MULTIPLY = multipl(NUMBERS_1, NUMBERS_2);
    cout << "THE RESULT X*Y IS: " << MULTIPLY << endl;
    cout << "We have gotten 45 for times: " << COUNT_45 << endl;
    cout << "We have gotten 9 for times: " << COUNT_9 << endl;
    cout << "We have gotten 8 for times: " << COUNT_8 << endl;
    
    return 0;
}


/* creating the subsidiary functions
The subsidiary functions legend:
 - string - is string;
 - Number, length - is an integer */


// the recursion-function creating the multiply function +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
InfInt multipl(InfInt Num1, InfInt Num2)
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
    InfInt A = get_intermediate_numbers(Num1, length_Number_1);
    InfInt B = Num1 - A * decim_1;
    int decim_2 = decimal(Num2, length_Number_2);
    InfInt C = get_intermediate_numbers(Num2, length_Number_2);
    InfInt D = Num2 - C * decim_2;

    // getting the final values
    InfInt AC = multipl(A, C);
    InfInt BD = multipl(B, D);
    InfInt First = A + B;
    InfInt Second = C + D;
    InfInt ADBC = multipl(First, Second) - AC - BD;

    // checking if the ad * bc is equal to the values we are looking for
    check_ADBC(ADBC);

    // getting the result
    InfInt XY = AC * decim_1 * decim_1 + ADBC * decim_1 + BD;

    // returning the result to the main function
    return XY;
}


// the function getting the intermediate numbers ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
InfInt get_intermediate_numbers(InfInt Number, int length)
{
    if (Number == 0)
    {
        return 0;
    }
    InfInt Intermed = Number;
    int i = 0;
    while (i != length / 2)
    {
        Intermed /= 10;
        i ++ ;
    }
    return Intermed;
}


// the function getting the length of the number ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int number_length(InfInt Number)
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
int decimal(InfInt Number, int length)
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
int check_length_number(InfInt Number)
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
void check_ADBC(InfInt Number)
{
    if (Number == 45)
    {
        COUNT_45 ++ ;
    }
    if (Number == 9)
    {
        COUNT_9 ++ ;
    }
    if (Number == 8)
    {
        COUNT_8 ++ ;
    }
}



