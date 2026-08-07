#include <stdint.h>
#include "helpers.h"
#include <math.h>


typedef struct {
    uint8_t rgbtBlue;
    uint8_t rgbtGreen;
    uint8_t rgbtRed;
} __attribute__((__packed__)) RGBTRIPLE;

void grayscale(int height, int width, RGBTRIPLE image[height][width]);
void sepia(int height, int width, RGBTRIPLE image[height][width]);
void reflect(int height, int width, RGBTRIPLE image[height][width]);
void blur(int height, int width, RGBTRIPLE image[height][width]);




void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int gray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = gray;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r = image[i][j].rgbtRed, g = image[i][j].rgbtGreen, b = image[i][j].rgbtBlue;
            int sR = round(.393 * r + .769 * g + .189 * b);
            int sG = round(.349 * r + .686 * g + .168 * b);
            int sB = round(.272 * r + .534 * g + .131 * b);
            image[i][j].rgbtRed = (sR > 255) ? 255 : sR;
            image[i][j].rgbtGreen = (sG > 255) ? 255 : sG;
            image[i][j].rgbtBlue = (sB > 255) ? 255 : sB;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) copy[i][j] = image[i][j];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int tR = 0, tG = 0, tB = 0;
            float count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        tR += copy[ni][nj].rgbtRed; tG += copy[ni][nj].rgbtGreen; tB += copy[ni][nj].rgbtBlue; count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(tR / count);
            image[i][j].rgbtGreen = round(tG / count);
            image[i][j].rgbtBlue = round(tB / count);
        }
    }
}

