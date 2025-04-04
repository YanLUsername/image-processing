/* MovieLab.c
Assignment 5

Date      Author      Notes
3/23/25   Yan Li      Initial version
4/4/25    Yan Li      Initial upload to GitHub
*/

#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include "string.h"
#include "math.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Black and White */
Image *BlackNWhite(Image *image)
{
	assert(image);
        for (int y = 0; y < ImageHeight(image); y++) {
                for (int x = 0; x < ImageWidth(image); x++) {
                        int temp = ((GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3);
                        SetPixelR(image, x, y, temp);
                        SetPixelG(image, x, y, temp);
                        SetPixelB(image, x, y, temp);
                }
        }
        return image;
}

/* Mirror image horizontal  */
Image *HMirror(Image *image) {
	assert(image);
        for (int y = 0; y < ImageHeight(image); y++) {
                for (int x = 0; x < ImageWidth(image) / 2; x++) {
                        SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
                        SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
                        SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
                }
        }
        return image;
}

/* Edge detection */
Image *Edge(Image *image) {
	assert(image);
        Image *temp = CreateImage(ImageWidth(image), ImageHeight(image));
        assert(temp);

        int x;
	int y;
	int a;
	int b;

        memcpy(temp->R, image->R, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        memcpy(temp->G, image->G, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        memcpy(temp->B, image->B, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));

        for (y = 1; y < ImageHeight(image) - 1; y++) {
                for (x = 1; x < ImageWidth(image) - 1; x++) {
                        int tempR = 0;
			int tempG = 0;
			int tempB = 0;
                        
			for (a = -1; a <= 1; a++) {
                                for (b = -1; b <= 1; b++) {
                                        tempR += (GetPixelR(temp, x, y) - GetPixelR(temp, x + b, y + a));
                                        tempG += (GetPixelG(temp, x, y) - GetPixelG(temp, x + b, y + a));
                                        tempB += (GetPixelB(temp, x, y) - GetPixelB(temp, x + b, y + a));
                                }
                        }
                        SetPixelR(image, x, y, (tempR > 255) ? 255 : (tempR < 0) ? 0 : tempR);
                        SetPixelG(image, x, y, (tempG > 255) ? 255 : (tempG < 0) ? 0 : tempG);
                        SetPixelB(image, x, y, (tempB > 255) ? 255 : (tempB < 0) ? 0 : tempB);
                }
        }
        
	for (x = 0; x < ImageWidth(image); x++) {
                y = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);

                y = (ImageHeight(image) - 1);
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }
        
	for (y = 0; y < ImageHeight(image); y++) {
                x = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);

                x = (ImageWidth(image) - 1);
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }

        DeleteImage(temp);
        temp = NULL;
        return image;
}

/* Add a watermark to an image */
Image *Watermark(Image *image, const Image *watermark,
	 unsigned int topLeftX, unsigned int topLeftY)
{
        assert(image != NULL);
        assert(watermark != NULL);
	
        for (int y = 0; y < watermark->H; y++) {
                for (int x = 0; x < watermark->W; x++) {
                        unsigned char watermarkR = GetPixelR(watermark, x, y);
                        unsigned char watermarkG = GetPixelG(watermark, x, y);
                        unsigned char watermarkB = GetPixelB(watermark, x, y);

                        unsigned char imageR = GetPixelR(image, topLeftX + x, topLeftY + y);
                        unsigned char imageG = GetPixelG(image, topLeftX + x, topLeftY + y);
                        unsigned char imageB = GetPixelB(image, topLeftX + x, topLeftY + y);

                        unsigned char newR = (imageR / 2) + (watermarkR / 2);
                        unsigned char newG = (imageG / 2) + (watermarkG / 2);
                        unsigned char newB = (imageB / 2) + (watermarkB / 2);

                        SetPixelR(image, topLeftX + x, topLeftY + y, newR);
                        SetPixelG(image, topLeftX + x, topLeftY + y, newG);
                        SetPixelB(image, topLeftX + x, topLeftY + y, newB);
                }
        }
        return image;
}

/* Spotlight */
Image *Spotlight(Image *image, int centerX, int centerY, unsigned int radius)
{
	assert(image != NULL);

        for (unsigned int y = 0; y < image->H; y++) {
                for (unsigned int x = 0; x < image->W; x++) {
                        int distX = x - centerX;
                        int distY = y - centerY;
                        double distance = sqrt(distX * distX + distY * distY);
                        if (distance > radius) {
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }
        }
        return image;
}

/* Rotate and zoom an image */
Image *Rotate(Image *image, double Angle, double ScaleFactor)
{
	assert(image != NULL);
        assert(ScaleFactor > 0.0);

        Image *newImage = CreateImage(image->W, image->H);

        for (unsigned int y = 0; y < image->H; y++) {
                for (unsigned int x = 0; x < image->W; x++) {
                        double offsetX = x - (image->W / 2.0);
                        double offsetY = y - (image->H / 2.0);

                        double originalX = (cos(-Angle * M_PI / 180.0) * offsetX + sin(-Angle * M_PI / 180.0) * offsetY) / ScaleFactor + (image->W / 2.0);
                        double originalY = (-sin(-Angle * M_PI / 180.0) * offsetX + cos(-Angle * M_PI / 180.0) * offsetY) / ScaleFactor + (image->H / 2.0);

                        if (originalX >= 0 && originalX < image->W && originalY >= 0 && originalY < image->H) {
                                unsigned char R = GetPixelR(image, (unsigned int)originalX, (unsigned int)originalY);
                                unsigned char G = GetPixelG(image, (unsigned int)originalX, (unsigned int)originalY);
                                unsigned char B = GetPixelB(image, (unsigned int)originalX, (unsigned int)originalY);

                                SetPixelR(newImage, x, y, R);
                                SetPixelG(newImage, x, y, G);
                                SetPixelB(newImage, x, y, B);
                        } else {
                                SetPixelR(newImage, x, y, 0);
                                SetPixelG(newImage, x, y, 0);
                                SetPixelB(newImage, x, y, 0);
                        }
                }
        }
        return newImage;
}
/* EOF */
