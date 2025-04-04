/* Movie.c
Assignment 5

Date      Author      Notes
3/23/25   Yan Li      Initial version
4/4/25    Yan Li      Initial upload to GitHub
*/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(void)
{
	Movie *movie = (Movie *)malloc(sizeof(Movie));
        assert(movie != NULL);

        movie->Frames = CreateImageList();
        assert(movie->Frames != NULL);

        return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie)
{
	assert(movie != NULL);

        if (movie->Frames != NULL) {
                DeleteImageList(movie->Frames);
        }

        free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie)
{
	assert(movie != NULL);
        assert(movie->Frames != NULL);

        IENTRY *entry = movie->Frames->First;

        while (entry != NULL) {
                YUVImage *yuv = (YUVImage *)entry->image;
                assert(yuv != NULL);

                Image *rgb = CreateImage(yuv->W, yuv->H);
                assert(rgb != NULL);

                for (unsigned int y = 0; y < yuv->H; y++) {
                        for (unsigned int x = 0; x < yuv->W; x++) {
                                int Y = GetPixelY(yuv, x, y);
                                int U = GetPixelU(yuv, x, y);
                                int V = GetPixelV(yuv, x, y);

                                int C = Y - 16;
                                int D = U - 128;
                                int E = V - 128;

                                int R = (298 * C + 409 * E + 128) >> 8;
                                int G = (298 * C - 100 * D - 208 * E + 128) >> 8;
                                int B = (298 * C + 516 * D + 128) >> 8;

                                if (R < 0) R = 0;
                                if (R > 255) R = 255;
                                if (G < 0) G = 0;
                                if (G > 255) G = 255;
                                if (B < 0) B = 0;
                                if (B > 255) B = 255;

                                SetPixelR(rgb, x, y, (unsigned char)R);
                                SetPixelG(rgb, x, y, (unsigned char)G);
                                SetPixelB(rgb, x, y, (unsigned char)B);
                        }
                }

                DeleteYUVImage(yuv);
                entry->image = (void *)rgb;

                entry = entry->Next;
        }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie)
{
	assert(movie != NULL);
        assert(movie->Frames != NULL);

        IENTRY *entry = movie->Frames->First;

        while (entry != NULL) {
                Image *rgb = (Image *)entry->image;
                assert(rgb != NULL);

                YUVImage *yuv = CreateYUVImage(rgb->W, rgb->H);
                assert(yuv != NULL);

                for (unsigned int y = 0; y < rgb->H; y++) {
                        for (unsigned int x = 0; x < rgb->W; x++) {
                                int R = GetPixelR(rgb, x, y);
                                int G = GetPixelG(rgb, x, y);
                                int B = GetPixelB(rgb, x, y);

                                int Y = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16;
                                int U = ((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128;
                                int V = ((112 * R - 94 * G - 18 * B + 128) >> 8) + 128;

                                if (Y < 0) Y = 0;
                                if (Y > 255) Y = 255;
                                if (U < 0) U = 0;
                                if (U > 255) U = 255;
                                if (V < 0) V = 0;
                                if (V > 255) V = 255;

                                SetPixelY(yuv, x, y, (unsigned char)Y);
                                SetPixelU(yuv, x, y, (unsigned char)U);
                                SetPixelV(yuv, x, y, (unsigned char)V);
                        }
                }

                DeleteImage(rgb);
                entry->image = (void *)yuv;

                entry = entry->Next;
        }
}

/* EOF */
