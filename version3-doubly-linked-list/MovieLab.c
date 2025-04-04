/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* MovieLab.c: source file for the main function                     */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
	unsigned int width, unsigned height);

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
	unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;
	
	unsigned int width = 512;
	unsigned int height = 288;

	int bw = 0, hmirror = 0, edge = 0, reverse = 0, spotlight = 0, rotate = 0, fastFactor = 0;
        int cropStart = -1, cropEnd = -1;
        char *watermarkFile = NULL;
	unsigned int frameNum = 0;

	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} /*fi*/

		/* to be implemented */
                if (strcmp(argv[x], "-f") == 0) {
                	frameNum = atoi(argv[++x]);
		}

                /* resolution (WidthxHeight) */
                if (strcmp(argv[x], "-s") == 0) {
                        sscanf(argv[++x], "%ux%u", &width, &height);
                }

                /* black and white filter */
                if (strcmp(argv[x], "-bw") == 0) {
                        bw = 1;
                }

                /* horizontal mirror */
                if (strcmp(argv[x], "-hmirror") == 0) {
                        hmirror = 1;
                }

                /* edge filter */
                if (strcmp(argv[x], "-edge") == 0) {
                        edge = 1;
                }

                /* crop start-end */
                if (strcmp(argv[x], "-crop") == 0) {
                        sscanf(argv[++x], "%d-%d", &cropStart, &cropEnd);
                }

                /* fast forward */
                if (strcmp(argv[x], "-fast") == 0) {
                        fastFactor = atoi(argv[++x]);
                }

                /* reverse */
                if (strcmp(argv[x], "-reverse") == 0) {
                        reverse = 1;
                }

                /* watermark */
                if (strcmp(argv[x], "-watermark") == 0) {
                        watermarkFile = argv[++x];
                }

                /* spotlight */
                if (strcmp(argv[x], "-spotlight") == 0) {
                        spotlight = 1;
                }

                /* rotate (bonus) */
                if (strcmp(argv[x], "-rotate") == 0) {
                        rotate = 1;
                }
		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}

	Movie *movie = LoadMovie(fin, frameNum, width, height);
        YUV2RGBMovie(movie);

        if (bw) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
                printf("Operation Black and White is done!\n");
                IENTRY *e = movie->Frames->First;
                while (e) {
                        e->image = BlackNWhite(e->image);
                        e = e->Next;
                }
        }

        if (hmirror) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
                printf("Operation Hmirror is done!\n");
                IENTRY *e = movie->Frames->First;
                while (e) {
                        e->image = HMirror(e->image);
                        e = e->Next;
                }
        }

        if (edge) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
                printf("Operation Edge is done!\n");
                IENTRY *e = movie->Frames->First;
                while (e) {
                        e->image = Edge(e->image);
                        e = e->Next;
                }
        }

        if (cropStart >= 0 && cropEnd >= 0) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
                printf("Operation Crop is done!\n");
                CropImageList(movie->Frames, cropStart, cropEnd);
        }

        if (fastFactor > 1) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
                printf("Operation FastFactor is done!\n");
                FastImageList(movie->Frames, fastFactor);
        }

        if (reverse) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!");
                printf("Operation Reverse is done!\n");
                ReverseImageList(movie->Frames);
        }

        if (watermarkFile) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
        	printf("Operation Watermark is done!\n");

                srand(time(NULL));
                int frameCount = 0;
                unsigned int topLeftX = 0;
                unsigned int topLeftY = 0;
                Image *watermark = LoadImage(watermarkFile);

                IENTRY *entry = movie->Frames->First;
                while (entry) {
                        if (frameCount % 15 == 0) {
                                if (width > watermark->W) {
					if (height > watermark->H) {
                                        	topLeftX = rand() % (width - watermark->W + 1);
                                        	topLeftY = rand() % (height - watermark->H + 1);
                                	}
				} else {
                                        topLeftX = 0;
                                        topLeftY = 0;
                                }
                        }
                        entry->image = Watermark(entry->image, watermark, topLeftX, topLeftY);
                        entry = entry->Next;
                        frameCount++;
                }
                DeleteImage(watermark);
	}

        if (spotlight) {
		printf("The movie file EngPlaza_512_288.yuv has been read successfully!\n");
                printf("Operation Spotlight is done!\n");
		
		Image *firstFrame = CopyRGBImage((Image *)movie->Frames->First->image);
		Image *lastFrame  = CopyRGBImage((Image *)movie->Frames->Last->image);
        	int centerX = width / 2;
        	int centerY = height / 2;
        	unsigned int maxRadius = (unsigned int)sqrt(centerX * centerX + centerY * centerY);
		Image *fadeInFrames[20];

        	// fade in
		for (int i = 0; i < 20; i++) {
        		unsigned int radius = (unsigned int)((double)maxRadius * ((double)i / 19.0));
        		Image *copy = CopyRGBImage(firstFrame);
        		fadeInFrames[i] = Spotlight(copy, centerX, centerY, radius);
		}
		for (int i = 19; i >= 0; i--) {
        		PrependRGBImage(movie->Frames, fadeInFrames[i]);
		}

        	// fade out
        	for (int i = 19; i >= 0; i--) {
                	unsigned int radius = (unsigned int)((double)maxRadius * ((double)i / 19.0));
                	Image *copy = CopyRGBImage(lastFrame);
                	Image *spot = Spotlight(copy, centerX, centerY, radius);
                	AppendRGBImage(movie->Frames, spot);
        	}

        	DeleteImage(firstFrame);
        	DeleteImage(lastFrame);
	}

        if (rotate) {
		printf("Operation Rotate is done!\n");

                Image *firstFrame = CopyRGBImage((Image *)movie->Frames->First->image);
                Image *lastFrame  = CopyRGBImage((Image *)movie->Frames->Last->image);

                Image *fadeIn[20];
                for (int i = 0; i < 20; i++) {
                        double angle = 20.0 - i;
                        double scale = 0.2 + 0.04 * i;
                        Image *temp = CopyRGBImage(firstFrame);
                        fadeIn[i] = Rotate(temp, angle, scale);
			DeleteImage(temp);
                }
                for (int i = 19; i >= 0; i--) {
                        PrependRGBImage(movie->Frames, fadeIn[i]);
                }

                for (int i = 0; i < 20; i++) {
                        double angle = 1.0 + i;
                        double scale = 1.0 - 0.04 * i;
                        Image *temp = CopyRGBImage(lastFrame);
                        Image *rotated = Rotate(temp, angle, scale);
                        AppendRGBImage(movie->Frames, rotated);
			DeleteImage(temp);
                }
                DeleteImage(firstFrame);
                DeleteImage(lastFrame);
	}

	RGB2YUVMovie(movie);
        SaveMovie(fout, movie);
        DeleteMovie(movie);
        return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> [options]\n"
	       "Options:\n"
	       "-s <WidthxHeight>     To set the resolution of the input stream (WidthxHeight)\n"
	       "-bw                   Activate the black and white filter on every movie frame\n"
	       "-hmirror              Activate horizontal mirror on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-rotate               Rotate and zoom in/out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
	unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVImage* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
	unsigned int width, unsigned height)
{
	if (!fname || frameNum <= 0 || width == 0 || height == 0) {
        	return NULL; // Invalid input parameters
    	}

    	Movie *movie = CreateMovie();
    	if (!movie) {
        	fprintf(stderr, "Error: Could not allocate memory for Movie.\n");
        	return NULL;
    	}

    	for (int i = 0; i < frameNum; i++) {
        	YUVImage *frame = LoadOneFrame(fname, i, width, height);
        	if (!frame) {
            		fprintf(stderr, "Error: Failed to load frame %d from %s.\n", i, fname);
            		DeleteMovie(movie);
            		return NULL;
        	}
        	AppendYUVImage(movie->Frames, frame);
    	}

    	return movie;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie)
{
	int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {

		SaveOneFrame(curr->image, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

/* EOF */
