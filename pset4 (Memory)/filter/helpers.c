#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue =  round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtRed = image[i][j].rgbtBlue;
        }
    }
    return;
}

void swap(RGBTRIPLE *front, RGBTRIPLE *end)
{
    RGBTRIPLE temp;
    temp = *front;
    *front = *end;
    *end = temp;
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int reverse = width - 1;
        for (int j = 0; j < width; j++)
        {
            swap(&image[i][j], &image[i][reverse]);

            if (j == reverse || j == reverse - 1)
            {
                break;
            }

            reverse--;
        }
    }
    return;
}

float checkcornerside(int *i, int *j, int *newH, int *newW) 
{
    // check the 4 corner of one image
    if ((*i == 1 && *j == 1) || (*i == 1 && *j == *newW - 2) || (*i == *newH - 2 && *j == 1) || (*i == *newH - 2 && *j == *newW - 2))
    {
        return 4.0;
    }
    //check the 4 side(left, right, top, down) of one image
    else if ((*i == 1 && (*j > 1 && *j < *newW - 2)) || (*i == *newH - 2 && (*j > 1 && *j < *newW - 2)) || (*j == 1 && (*i > 1
             && *i < *newH - 2)) || (*j == *newW - 2 && (*i > 1 && *i < *newH - 2)))
    {
        return 6.0;
    }
    //the remaining one
    else
    {
        return 9.0;
    }
}

//make the ege become 0
void zerocornerside(int newH, int newW, RGBTRIPLE temp[newH][newW])
{
    for (int j = 0; j < newW; j++)
    {
        temp[0][j].rgbtBlue = temp[0][j].rgbtGreen = temp[0][j].rgbtRed = 0; //deal with up
        temp[newH - 1][j].rgbtBlue = temp[newH - 1][j].rgbtGreen = temp[newH - 1][j].rgbtRed = 0;//deal with down
    }
    //deal with left and right
    for (int i = 0; i < newH; i++)
    {
        temp[i][0].rgbtBlue = temp[i][0].rgbtGreen = temp[i][0].rgbtRed = 0; //left
        temp[i][newW - 1].rgbtBlue = temp[i][newW - 1].rgbtGreen = temp[i][newW - 1].rgbtRed = 0; //right
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int newH = height + 2;
    int newW = width + 2;
    RGBTRIPLE temp[newH][newW];

    //temp[newH][newW] = *putcenter(height, width, image);
    //put old image in the center of temp
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            temp[i][j] = image[i - 1][j - 1];
        }
    }

    //make the ege become 0
    zerocornerside(newH, newW, temp);

    //blur algorithm
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            float rgbtBlue, rgbtGreen, rgbtRed;
            rgbtBlue = rgbtGreen = rgbtRed = 0.0;
            float avg = checkcornerside(&i, &j, &newH, &newW);
            for (int k = -1; k <= 1; k++)
            {
                rgbtBlue += (temp[i + k][j - 1].rgbtBlue + temp[i + k][j].rgbtBlue + temp[i + k][j + 1].rgbtBlue);
                rgbtRed += (temp[i + k][j - 1].rgbtRed + temp[i + k][j].rgbtRed + temp[i + k][j + 1].rgbtRed);
                rgbtGreen += (temp[i + k][j - 1].rgbtGreen + temp[i + k][j].rgbtGreen + temp[i + k][j + 1].rgbtGreen);
            }

            image[i - 1][j - 1].rgbtBlue = round(rgbtBlue / avg);
            image[i - 1][j - 1].rgbtRed = round(rgbtRed / avg);
            image[i - 1][j - 1].rgbtGreen = round(rgbtGreen / avg);
        }
    }
    return;
}

////////////////////////////////////// Detect edges //////////////////////////////

//Use Sobel operator algorithm to deal with the 9 grid
int SobelCal(int i, int j, int newH, int newW, RGBTRIPLE temp[newH][newW], int a)
{
    float Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float Gnum = 0.0;


    for (int m = -1; m <= 1; m++)
    {
        for (int n = -1; n <= 1; n++)
        {
            if (a == 1)
            {
                Gnum += temp[i + m][j + n].rgbtBlue * Gx[1 + m][1 + n];
            }
            else if (a == 2)
            {
                Gnum += temp[i + m][j + n].rgbtGreen * Gx[1 + m][1 + n];
            }
            else if (a == 3)
            {
                Gnum += temp[i + m][j + n].rgbtRed * Gx[1 + m][1 + n];
            }
            else if (a == 4)
            {
                Gnum += temp[i + m][j + n].rgbtBlue * Gy[1 + m][1 + n];
            }
            else if (a == 5)
            {
                Gnum += temp[i + m][j + n].rgbtGreen * Gy[1 + m][1 + n];
            }
            else if (a == 6)
            {
                Gnum += temp[i + m][j + n].rgbtRed * Gy[1 + m][1 + n];
            }
        }
    }
    return Gnum;
}

//integrate and output the final RGB value
float GValueCal(float GxRGB, float GyRGB)
{
    float GValue = 0.0;
    GValue = sqrt(GxRGB * GxRGB + GyRGB * GyRGB);
    if (GValue > 255)
    {
        return 255;
    }
    else if (GValue < 0)
    {
        return 0;
    }
    else
    {
        return GValue;
    }
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int newH = height + 2;
    int newW = width + 2;
    RGBTRIPLE temp[newH][newW];

    //put old image inside temp
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            temp[i][j] = image[i - 1][j - 1];
        }
    }

    zerocornerside(newH, newW, temp);

    //edge detection algorithm calculation
    float GxRed, GyRed, GxBlue, GyBlue, GxGreen, GyGreen;
    GxRed = GyRed = GxBlue  = GyBlue = GxGreen = GyGreen  = 0.0;
    int a = 0;  //1 for GxBlue, 2 for GxGreen, 3 for GxRed, 4 for GyBlue, 5 for GyGreen, 6 for GyRed
    for (int i = 1; i < newH - 1; i++)
    {
        for (int j = 1; j < newW - 1; j++)
        {
            //deal with blue
            a = 1;
            GxBlue = SobelCal(i, j, newH, newW, temp, a);
            a = 4;
            GyBlue = SobelCal(i, j, newH, newW, temp, a);
            image[i - 1][j - 1].rgbtBlue = round(GValueCal(GxBlue, GyBlue));

            //deal with green
            a = 2;
            GxGreen = SobelCal(i, j, newH, newW, temp, a);
            a = 5;
            GyGreen = SobelCal(i, j, newH, newW, temp, a);
            image[i - 1][j - 1].rgbtGreen = round(GValueCal(GxGreen, GyGreen));

            //deal with red
            a = 3;
            GxRed = SobelCal(i, j, newH, newW, temp, a);
            a = 6;
            GyRed = SobelCal(i, j, newH, newW, temp, a);
            image[i - 1][j - 1].rgbtRed = round(GValueCal(GxRed, GyRed));
            a = 0;
        }
    }
    return;
}
