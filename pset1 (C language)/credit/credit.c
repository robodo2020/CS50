# include <stdio.h>
# include <cs50.h>
# include <math.h>

int main(void)
{
// for user enter number
    long number;

    do
    {
        number = get_long("Number:");
    }
    while (number < 0);

// for checking algorithm digits
    //calculate digit
    int digit = 1;
    long Calculatedigit = number;

    while (Calculatedigit / 10 > 0)
    {
        Calculatedigit = Calculatedigit / 10;
        digit = digit + 1;
    }
    //printf("%d\n", digit);
    
    //check if digit fit credit card digit
    if (digit == 13 || digit == 15 || digit == 16)
    {
        if (number / 10000000000000 == 34 || number / 10000000000000 == 37 || number / 1000000000000 == 4 || number / 1000000000000000 == 4 
            || number / 100000000000000 == 51 || number / 100000000000000 == 52 || number / 100000000000000 == 53 
            || number / 100000000000000 == 54 || number / 100000000000000 == 55)
        {
            int digitArray[digit];

            //save each digit into array
            for (int i = 0; i < digit; i++)
            {
                digitArray[i] = number % 10;
                number = number / 10;
                //printf("%d,", digitArray[i]);
            }

            int even = 0;

            for (int j = 1; j < digit; j = j + 2)
            {
                even = even + (2 * digitArray[j] / 10) + (2 * digitArray[j] % 10);
            }
            //printf("%d\n", even);
            
            int odd = 0;
            for (int k = 0; k < digit; k = k + 2)
            {
                odd = odd + digitArray[k];
                //printf("%d,",digitArray[k]);
            }
            //printf("%d\n", odd);
            int checksum = 0;
            checksum = odd + even;
            if (checksum % 10  == 0)
            {
                if (digit == 15)
                {
                    printf("AMEX\n");
                }
                else if (digit == 13)
                {
                    printf("VISA\n");
                }
                else if (digit == 16 && digitArray[15] == 4)
                {
                    printf("VISA\n");
                }
                else if (digit == 16 && digitArray[15] == 5)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }


    }
    else
    {
        printf("INVALID\n");
    }
}
