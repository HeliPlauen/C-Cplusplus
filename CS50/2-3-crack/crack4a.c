#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int strln(char *s);
char *get_salt(char *s);
bool str_compare(char *s, char *t);
int main (int argc, char *argv[])
{
    // if the number of arguments is not two
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    //creating the string for argv
    int len_argv = strln(argv[1]);
    char code_1[len_argv + 1];

    // if the 2 argument exists
    if (argv[1])
    {
        for (int i = 0; i <= len_argv; i ++)
        {
            code_1[i] = argv[1][i];
        }
        printf("%s\n", code_1);
    }

    // creating the text for coding it by the salt
    char text[] = "AAAA";
    char symbol_1, symbol_2, symbol_3, symbol_4;

    // creating salt
    char *salt = get_salt(code_1);
    printf("%s\n", salt);

    //if the salt does not exist
    if (!salt)
    {
        return 1;
    }

    // creating the 4-th loop
    do
    {
        // creating the 3-rd loop
        do
        {
            // creating the 2-nd loop
            do
            {

                // creating the 1-st loop
                do
                {

                    // if the 1-st and the 2-nd symbols of the password are a large or small letters
                    if ((isupper(text[0]) || islower(text[0])) && (isupper(text[1]) || islower(text[1]))
                    && (isupper(text[2]) || islower(text[2])) && (isupper(text[3]) || islower(text[3])))
                    {
                        //coding the text by salt
                        char *code_2 = crypt(text, salt);

                        if (!code_2)
                        {
                            return 1;
                        }

                        // if code_1 and code_2 are the same
                        if (str_compare(code_1, code_2))
                        {
                            printf("%s, %s\n", code_2, text);
                            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1We have fount the password!!!\n");
                            printf("The password is: %s\n", text);

                            // if we have found our password
                            return 0;
                        }
                    }

                    // if the 1-st symbol is not a letter
                    else if (!isalpha(text[0]))
                    {
                        text[0] = 'a' - 1;
                    }

                    // creating the temporary char
                    symbol_1 = text[0] + 1;

                    // shifting the symbol by one in the ASCII table
                    text[0] = symbol_1;
                }
                while (text[0] <= 'z');

                // if the second letter is ont a letter
                if (!isalpha(text[1]))
                {
                    text[1] = 'a' - 1;
                }

                // getting ready for the searching with the next text[1]
                text[0] = 'A';

                // creating the temporary char for the 2-d loop
                symbol_2 = text[1] + 1;

                // shifting the symbol by one in the ASCII table
                text[1] = symbol_2;
            }
            while (text[1] <= 'z');

            // if the second letter is ont a letter
            if (!isalpha(text[2]))
            {
                text[2] = 'a' - 1;
            }

            // getting ready for the searching with the next text[1]
            text[0] = 'A';
            text[1] = 'A';

            // creating the temporary char for the 3-d loop
            symbol_3 = text[2] + 1;

            // shifting the symbol by one in the ASCII table
            text[2] = symbol_3;
        }
        while (text[2] <= 'z');

        // if the second letter is ont a letter
        if (!isalpha(text[3]))
        {
            text[3] = 'a' - 1;
        }

        // getting ready for the searching with the next text[1]
        text[0] = 'A';
        text[1] = 'A';
        text[2] = 'A';

        // creating the temporary char for the 4-th loop
        symbol_4 = text[3] + 1;

        // shifting the symbol by one in the ASCII table
        text[3] = symbol_4;
    }
    while (text[3] <= 'z');

    printf("We have NOT found the password\n");

    // if it was no emergensy exit
    return 0;
}


// strlen
int strln(char *s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        i++;
    }
    return i;
}

// getting funtion creating salt
char *get_salt(char *s)
{
    char *t = malloc(sizeof(char) * 3);

    // filling salt by characters
    for (int i = 0; i < 2; i++)
    {
        t[i] = s[i];
    }

    // gettting the last string elenent
    t[2] = '\0';

    // returning the salt to main
    return t;
}

// the sub-program comparing the code_1 and the code_2
bool str_compare(char *s, char *t)
{
    // defying the lengths of the hashed passwords
    int length_s = strln(s);
    int length_t = strln(t);

    // if the lengths of the hashed passwords are different
    if (length_s != length_t)
    {
        return false;
    }

    // if the symbols of the hashed vpasswords are different
    for (int i = 0; i < length_s; i++)
    {
        if (s[i] != t[i])
        {
            return false;
        }
    }

    // if suxess
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s, %s\n", s, t);
    return true;
}

