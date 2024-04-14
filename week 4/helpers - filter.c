#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for (int j =0; j < width; j++) {
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen;
            int avg = (int) ((sum / 3) + 0.5);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(j < width/2) {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - j - 1];
                image[i][width - j - 1] = temp;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float rAvg = 0;
            float bAvg = 0;
            float gAvg = 0;
            int counter = 0;

             for (int k = -1; k <= 1; k++) {
                for (int c = -1; c <= 1; c++) {
                    if(((i+k) >= 0) && ((i+k) < height) && ((j+c) >= 0) && ((j+c) < width)) {
                        rAvg += copy[i+k][j+c].rgbtRed;
                        bAvg += copy[i+k][j+c].rgbtBlue;
                        gAvg += copy[i+k][j+c].rgbtGreen;

                        counter++;
                    }
                }
            }



            rAvg = round((float)rAvg / counter);
            bAvg = round((float)bAvg / counter);
            gAvg = round((float)gAvg / counter);

            image[i][j].rgbtRed = (int) rAvg;
            image[i][j].rgbtBlue = (int) bAvg;
            image[i][j].rgbtGreen = (int) gAvg;
        }
    }


}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

     for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int gxred = 0;
            int gxgreen = 0;
            int gxblue = 0;

            int gyred = 0;
            int gygreen = 0;
            int gyblue = 0;

            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};




            for (int k = -1; k <= 1; k++) {
                for (int c = -1; c <= 1; c++) {
                    if(((i+k) >= 0) && ((i+k) < height) && ((j+c) >= 0) && ((j+c) < width)) {
                        gxred += copy[i+k][j+c].rgbtRed * Gx[k+1][c+1];
                        gxblue += copy[i+k][j+c].rgbtBlue * Gx[k+1][c+1];
                        gxgreen += copy[i+k][j+c].rgbtGreen * Gx[k+1][c+1];

                        gyred += copy[i+k][j+c].rgbtRed * Gy[k+1][c+1];
                        gyblue += copy[i+k][j+c].rgbtBlue * Gy[k+1][c+1];
                        gygreen += copy[i+k][j+c].rgbtGreen * Gy[k+1][c+1];
                    }
                }
            }



            int blue = round(sqrt(gxblue * gxblue + gyblue * gyblue));
            int green = round(sqrt(gxgreen * gxgreen + gygreen * gygreen));
            int red = round(sqrt(gxred * gxred + gyred * gyred));


            image[i][j].rgbtRed = (red > 255) ? 255 : red;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;


        }
    }
    return;
}
