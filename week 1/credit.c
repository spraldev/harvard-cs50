#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long creditnum = get_long("Number: ");
    int count = 0;

    long tempnum = creditnum;

    while (tempnum > 0)
    {
        tempnum = tempnum / 10;
        count++;
    }

    int sum = 0;
    long newcreditnum = creditnum;

    for (int i = 0; i < count; i++)
    {
        if ((i % 2) != 0)
        {
            int digit = ((newcreditnum % 10) * 2);
            newcreditnum = newcreditnum / 10;
            if (digit > 9)
            {
                sum += digit % 10;
                sum += digit / 10;

                continue;
            }

            sum += digit;
        }
        else
        {
            int digit = (newcreditnum % 10);
            sum += digit;
            newcreditnum = newcreditnum / 10;
        }
    }


    if (!((sum % 10) == 0))
    {
        printf("INVALID\n");
        return 0;
    }

    long firstdigi = creditnum;

    while (firstdigi >= 100)
    {
        firstdigi = firstdigi / 10;
    }

    if ((count == 15) && ((firstdigi == 37) || (firstdigi == 34)))
    {
        printf("AMEX\n");
        return 0;
    }

    if ((count == 16) && ((firstdigi == 51) || (firstdigi == 52) || (firstdigi == 53) ||
                          (firstdigi == 54) || (firstdigi == 55)))
    {
        printf("MASTERCARD\n");
        return 0;
    }

    long sinfirstdigi = creditnum;

    while (sinfirstdigi >= 10)
    {
        sinfirstdigi = sinfirstdigi / 10;
    }


    if (((count == 13) || (count == 16)) && ((sinfirstdigi == 4)))
    {
        printf("VISA\n");
        return 0;
    }

    printf("INVALID\n");
    return 0;
}
