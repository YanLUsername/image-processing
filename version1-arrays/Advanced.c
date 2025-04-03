/* Advanced.c
Assignment 3

Date      Author      Notes
2/17/25   Yan Li      Initial version
4/3/25    Yan Li      Initial upload to GitHub
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Advanced.h"
#include "Constants.h"

#define M_PI 3.14159265358979323846

/* Create a fisheye image W24 */
void FishEye(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double base_factor, double k, double scaling_factor) {	
	unsigned char outR[WIDTH][HEIGHT] = {0};
    	unsigned char outG[WIDTH][HEIGHT] = {0};
    	unsigned char outB[WIDTH][HEIGHT] = {0};

    	int centerX = WIDTH / 2;
    	int centerY = HEIGHT / 2;

    	for (int y = 0; y < HEIGHT; y++) {
        	for (int x = 0; x < WIDTH; x++) {
            		// Calculate normalize
            		double dx = (x - centerX) / (double) centerX;
            		double dy = (y - centerY) / (double) centerY;
            		double radius = sqrt(dx * dx + dy * dy);

            		// Calculate distortion
            		double distortion = (1.0 + k * radius * radius);

            		// Apply fisheye
            		double theta = atan2(dy, dx);
            		double newRadius = (radius * base_factor) / (distortion * scaling_factor);

            		// Convert back to coordinates
            		int srcX = (int)(centerX + (newRadius * cos(theta) * centerX));
            		int srcY = (int)(centerY + (newRadius * sin(theta) * centerY));

            		// Check if within bounds
            		if (srcX >= 0 && srcX < WIDTH && srcY >= 0 && srcY < HEIGHT) {
                		outR[x][y] = R[srcX][srcY];
                		outG[x][y] = G[srcX][srcY];
                		outB[x][y] = B[srcX][srcY];
            		} else {
                		outR[x][y] = 0;
                		outG[x][y] = 0;
                		outB[x][y] = 0;
            		}
        	}
    	}

    	for (int y = 0; y < HEIGHT; y++) {
        	for (int x = 0; x < WIDTH; x++) {
            		R[x][y] = outR[x][y];
            		G[x][y] = outG[x][y];
            		B[x][y] = outB[x][y];
        	}
    	}
}

/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits) {
    	for (int y = 0; y < HEIGHT; y++) {
        	for (int x = 0; x < WIDTH; x++) {
        	    	// Masks
            		unsigned char maskR = ~((1 << rbits) - 1);
            		unsigned char maskG = ~((1 << gbits) - 1);
            		unsigned char maskB = ~((1 << bbits) - 1);

            		// Apply posterization
            		R[x][y] = (R[x][y] & maskR) | ((1 << (rbits - 1)) - 1);
            		G[x][y] = (G[x][y] & maskG) | ((1 << (gbits - 1)) - 1);
            		B[x][y] = (B[x][y] & maskB) | ((1 << (bbits - 1)) - 1);
        	}
    	}
}

/* rotate and zoom the image */
void Rotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double Angle, double ScaleFactor,  int CenterX, int CenterY) {
	// Temporary arrays
	unsigned char newR[WIDTH][HEIGHT] = {0};
    	unsigned char newG[WIDTH][HEIGHT] = {0};
    	unsigned char newB[WIDTH][HEIGHT] = {0};

    	// Angle to radians
    	double rad = Angle * M_PI / 180.0;
    	double cosTheta = cos(rad) / ScaleFactor;
    	double sinTheta = sin(rad) / ScaleFactor;

    	for (int y = 0; y < HEIGHT; y++) {
        	for (int x = 0; x < WIDTH; x++) {
            		// Apply inverse
            		int sourceX = (int)(cosTheta * (x - CenterX) + sinTheta * (y - CenterY) + CenterX);
            		int sourceY = (int)(-sinTheta * (x - CenterX) + cosTheta * (y - CenterY) + CenterY);

            		// Check bounds
            		if (sourceX >= 0 && sourceX < WIDTH && sourceY >= 0 && sourceY < HEIGHT) {
                		newR[x][y] = R[sourceX][sourceY];
                		newG[x][y] = G[sourceX][sourceY];
                		newB[x][y] = B[sourceX][sourceY];
            		} else {
                		// Assign black color to out of bounds
                		newR[x][y] = 0;
                		newG[x][y] = 0;
                		newB[x][y] = 0;
            		}
        	}
    	}

    	for (int y = 0; y < HEIGHT; y++) {
        	for (int x = 0; x < WIDTH; x++) {
           		R[x][y] = newR[x][y];
            		G[x][y] = newG[x][y];
            		B[x][y] = newB[x][y];
        	}
    	}
}

/* motion blur */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        for (int x = 0; x < WIDTH - 1; x++) {
                for (int y = 0; y < HEIGHT; y++) {
                        // Reset average
			double avgR = 0;
			double avgG = 0;
			double avgB = 0;

                        for (int k = 1; k <= ((WIDTH - x) > 40 ? BlurAmount : WIDTH - x - 1); k++) {
        			// Find average
				avgR = avgR + R[x + k][y];
                                avgG = avgG + G[x + k][y];
                                avgB = avgB + B[x + k][y];
                        }

			double Divide = ((WIDTH - x) > 40) ? BlurAmount : (WIDTH - x - 1);
                	R[x][y] = R[x][y] / 2.0 + ((avgR / Divide) / 2);
			G[x][y] = G[x][y] / 2.0 + ((avgG / Divide) / 2);
			B[x][y] = B[x][y] / 2.0 + ((avgB / Divide) / 2);
                }
        }
}
