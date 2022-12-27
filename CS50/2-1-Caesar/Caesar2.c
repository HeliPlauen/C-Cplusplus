#include <stdio.h>
#include <cs50.h>
#include <string.h>

//The main code
bool contr(string argv[]);
int conv1(string argv[]);
void conv2(string msg, int sum);
int main(int argc, string argv[])
{     
    if (argc != 2)
    {
        printf("Please, input the key (the positive value)!!! (Usage: ./caesar key)\n");
        return 1;
    }
    else
    {   
        contr(argv);
        if (contr(argv) == false)
        {      
            printf("Please, input the key (the positive value)!!! (Usage: ./caesar key)\n"); 
            return 1;       
        } 
        else
        {
            int sum = conv1(argv); 
            string msg = get_string("Input the message: ");                       
            conv2(msg, sum); 
        }  
    }     
}

//Control of the input data
bool contr(string argv[])
{
    int i = 0;
    int x = strlen(argv[1]);    
    if (argv[1][0] > '0' && argv[1][0] < '9')
    {
        do
        {
            if (i == x)
            {
                return false;
            }  
            if (i == x - 1)
            {
                return true;
            }  
            {
                i++;
            }  
        }   
        while (argv[1][i] > '0' && argv[1][i] < '9');
        return false; 
    }
    else
    {
        return false; 
    }

}
    
//The key konvertation from string to integer 
int conv1(string argv[])
{      
    int x = strlen(argv[1]);
    int arr2[x];
    int sum = 0;
    int mltp = 1;
    for (int i = 0; i < x; i++)
    {
        mltp*=10;
    }
    for (int i = 0; i < x; i++)
    {
        arr2[i] = (int) argv[1][i] - '0';
        mltp/=10;
        sum = sum + mltp*arr2[i];                                      
    }    
    return sum; 
}

//Coding the message        
void conv2(string msg, int sum)
{
    printf("ciphertext: ");
    for (int j = 0, k = strlen(msg); j < k; j++)
    {
        if (msg[j] >= 'a' && msg[j] <= 'z')
        {           
            printf("%c", ('a' + (msg[j] + sum - 'a')%26));
        }
        else if (msg[j] >= 'A' && msg[j] <= 'Z')
        {           
            printf("%c", ('A' + (msg[j] + sum - 'A')%26));
        }
        else
        {
            printf("%c", msg[j]);
        }
    }
    printf("\n");
}
