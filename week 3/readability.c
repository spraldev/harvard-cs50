#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *text = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0; i < strlen(text) + 1; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        if (isspace(text[i]) || text[i] == '\0')
        {
            words++;
        }
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentences++;
        }
    }

    float l = (100 / (float)words) * letters;
    float s = (100 / (float)words) * sentences;

    float score = round(0.0588 * l - 0.296 * s - 15.8);

    if (score > 16)
    {
        printf("Grade 16+\n");
    }
    else if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)score);
    }
}
