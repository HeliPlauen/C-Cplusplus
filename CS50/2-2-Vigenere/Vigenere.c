#include <stdio.h>
#include <cs50.h>
#include <string.h>

//The main code
bool contr(string argv[]);
int conv1(string argv[], int t);
void conv2(string s, int z, int veg[]);
int main(int argc, string argv[])
{     
    if (argc != 2)
    {
        printf("Please, input the keyword!!! (Usage: ./vigenere key)\n");
        return 1;        
    }
    else
    {   
        contr(argv);
        if (contr(argv) == false)
        {      
            printf("Please, input the keyword!!! (Usage: ./vigenere key)\n");
            return 1;                   
        } 
        else
        {   
            string s = get_string("Input the message: ");             
            int z = strlen(argv[1]);                                                                      
            int veg[z];
            for (int t = 0; t < z; t++)
            {                
                veg[t] = conv1(argv, t);                                                                                           
            }
            conv2(s, z, veg);
        }
    }
}
            

//Control of the input data
bool contr(string argv[])
{
    int i = 0;
    int x = strlen(argv[1]);    
    if ((argv[1][0] >= 'a' && argv[1][0] <= 'z') || (argv[1][0] >= 'A' && argv[1][0] <= 'Z'))
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
        while ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z'));
        return false; 
    }
    else
    {
        return false; 
    }

}
    
//The key konvertation to local keys
int conv1(string argv[], int t)
{      
    int shift; 
    int value = (int) argv[1][t]; 
    if (value >= 'A' && value <= 'Z')
    {
        shift = value - 'A';
    }
    else
    {
        shift = value - 'a';
    }        
        return shift;
} 

//Coding the message
void conv2(string s, int z, int veg[])
{    
    int n = strlen(s);
    char s2[n];            
    for (int i = 0; i < n; i++)
    {
        s2[i] = s[i];                
    }
    int shift[z];
    for (int i = 0; i < z; i++)
    {
        shift[i] = veg[i];        
    }    
    printf("ciphertext: ");
    int s3[n];
    int x[n];
    int newval[n];
    char newval2[n];
    int k = 0;
    for (int i = 0; i < n; i++)
    {   
        s3[i] = (int) s2[i];  
        k = k%z;              
        x[i] = s3[i] + shift[k];                 
        if ((s2[i] >= 'a' && s2[i] <= 'z' && x[i] <= 122) || (s2[i] >= 'A' && s2[i] <= 'Z' && x[i] <= 90))
        {
            newval[i] = x[i];
            k++;
        }
        else if ((s2[i] >= 'a' && s2[i] <= 'z' && x[i] > 122) || (s2[i] >= 'A' && s2[i] <= 'Z' && x[i] > 90))
        {
            newval[i] = x[i] - 26;
            k++;
        }                 
        else
        {               
            newval[i] = s3[i];            
        }
        newval2[i] = (char) newval[i];        
        printf("%c", newval2[i]);                    
    }    
    printf("\n");               
}
