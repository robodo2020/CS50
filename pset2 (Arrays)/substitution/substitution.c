#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>



//Get key
int main(int argc, char *argv[])
{
//validate the key
    //string GetKey = "";   //在使用string時直接這樣就好 不用string[]會報錯
    string GetKey = argv[1];
    if (argc == 2)
    {
        //string GetKey = argv[1];
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;//告知電腦this program did not succeed
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
        string EncryptText = get_string("plaintext:");  //欲輸入字為hello
        int len = strlen(EncryptText);          //這兩行搞死我QQ
        char CipherText[len];                   //這兩行搞死我QQ
        for (int s = 0; s <= len; s++)          //為什麼s<len就會使output有問題-->string儲存時會自動加上\0,而char的沒有 才會造成問題
        {
            //處理大寫
            if (isupper(EncryptText[s]))
            {
                for (int m = 0; m < 26; m++)      
                {
                    if (toupper(EncryptText[s]) == original[m])//if Encrypt[0]  h, =original的 7
                    {
                        CipherText[s] = toupper(GetKey[m]);
                        //printf("%c",CipherText[s]);
                        break;
                    }        
                }
            }
            //處理小寫
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
            //處理數字&標點符號
            else
            {
                CipherText[s]  = EncryptText[s];
            }
        }
        printf("ciphertext:%s\n", CipherText);
        return 0;
    }
}






