#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>



//Get key
int main(int argc, char *argv[])
{
//validate the key
    //string GetKey = "";  
    string GetKey = argv[1];
    if (argc == 2)
    {
        //string GetKey = argv[1];
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;//this program did not succeed
    }
    
        
    //check key length
    if (strlen(GetKey) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    //check for non-alphabetic characters
    bool CheckNon = false;
    for (int i = 0; i < strlen(GetKey); i++)
    {
        if (isalpha(GetKey[i]))
        {
            CheckNon = true;
        }
        else
        {
            CheckNon = false;
            printf("Usage: ./substitution key 1\n");
            return 1;
        }
            
    }

    bool duplicate = false;
    //check for repeat alphabetic
    if (CheckNon == true)
    {
        int num = 0;
        for (char c = 'a'; c <= 'z'; c++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (tolower(GetKey[j]) == c)
                {
                    num++;
                    break;
                }
            }
        }
        
        if (num == 26)
        {
            duplicate = true;
        }
        else
        {
            printf("Usage: ./substitution key 1\n");
            duplicate = false;
            return 1;
        }
    }
    
    
    //Encipher
    string original = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (duplicate == true)
    {
        string EncryptText = get_string("plaintext:");  
        int len = strlen(EncryptText);          
        char CipherText[len];                   
        for (int s = 0; s <= len; s++)         
        {
            //deal with Upper Case
            if (isupper(EncryptText[s]))
            {
                for (int m = 0; m < 26; m++)      
                {
                    if (toupper(EncryptText[s]) == original[m])
                    {
                        CipherText[s] = toupper(GetKey[m]);
                        //printf("%c",CipherText[s]);
                        break;
                    }        
                }
            }
            // deal with Lower Case
            else if (islower(EncryptText[s]))
            {
                for (int m = 0; m < 26; m++)      
                {
                    if ((EncryptText[s]) == tolower(original[m]))//if Encrypt[0]  h, =original的 7
                    {
                        CipherText[s] = tolower(GetKey[m]);
                        break; 
                    }        
                }
            }
            //deal with number & symbol
            else
            {
                CipherText[s]  = EncryptText[s];
            }
        }
        printf("ciphertext:%s\n", CipherText);
        return 0;
    }
}






