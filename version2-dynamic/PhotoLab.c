/* PhotoLab.c
Assignment 4

Date      Author      Notes
3/4/25    Yan Li      Initial version
4/3/25    Yan Li      Initial upload to GitHub
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"
#include "Constants.h"
#include "Test.h"

void PrintMenu();

int main() {
	#ifdef DEBUG
		    AutoTest();
	#else
	// Function Parameters
	// ColorFilter() Parameters
	int target_r, target_g, target_b, threshold;
        int factor_r, factor_g, factor_b;

	// Border() Parameters
	int border_width;
       	char color[SLEN];

	// Pixelate() Parameters
	int block_size;

	// Shift() Parameters
	int shift_x, shift_y;

	// Crop() Parameters
	int crop_x, crop_y, crop_width, crop_height;

	// Resize() Parameters
	int resize_width, resize_height;

	// Watermark() Parameters
	char watermark_fname[SLEN] = "watermark_template";  // Default watermark file
        Image *watermark_image = LoadImage(watermark_fname); // Load watermark

	// Rotate() Parameters
	int direction;

	Image *image = NULL; // Pointer to hold the image
        int option;           // User input option
        char fname[SLEN];     // File name

        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);

	while (option != EXIT) {
        if (option == 1) {
			        if (image) {
				            DeleteImage(image);
				            printf("Please input the file name to load: ");
                    scanf("%75s", fname);
                    image = LoadImage(fname);
			        } else {
                    printf("Please input the file name to load: ");
                    scanf("%75s", fname);
				            image = LoadImage(fname);
              }
		    }
	      //  menu item 2 - 10 requires image is loaded first
		    else if (option >= 2 && option <= 17) {
	            if (!image) {
				      printf("No image is read.\n");
			  }
			  switch(option) {
				      case 2:
                    printf("Please input the file name to save: ");
                    scanf("%75s", fname);
                    SaveImage(fname, image);
                    printf("\"Save Image\" operation is done!\n");
                    break;
              case 3:
                    image = BlackNWhite(image);
                    printf("\"Black & White\" operation is done!\n");
                    break;
              case 4:
                    image = Negative(image);
                    printf("\"Negative\" operation is done!\n");
                    break;
              case 5:
                    printf("Enter Red component for the target color: ");
                    scanf("%d", &target_r);
                    printf("Enter Green component for the target color: ");
                    scanf("%d", &target_g);
                    printf("Enter Blue component for the target color: ");
                    scanf("%d", &target_b);
                    printf("Enter threshold for the color difference: ");
                    scanf("%d", &threshold);
                    printf("Enter value for Red component in the target color: ");
                    scanf("%d", &factor_r);
                    printf("Enter value for Green component in the target color: ");
                    scanf("%d", &factor_g);
                    printf("Enter value for Blue component in the target color: ");
                    scanf("%d", &factor_b);
                    image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                    printf("\"Color Filter\" operation is done!\n");
                    break;
				      case 6:
                    image = Edge(image);
                    printf("\"Edge\" operation is done!\n");
                    break;
              case 7:
                    image = Shuffle(image);
                    printf("\"Shuffle\" operation is done!\n");
                    break;
              case 8:
                    image = VFlip(image);
                    printf("\"VFlip\" operation is done!\n");
                    break;
              case 9:
                    image = HMirror(image);
                    printf("\"HMirror\" operation is done!\n");
                    break;
              case 10:
                    printf("Enter border width: ");
                    scanf("%d", &border_width);
                    printf("Enter border color: ");
                    scanf("%s", color);
                    image = AddBorder(image, color, border_width);
                    printf("\"Border\" operation is done!\n");
                    break;
              case 11:
                    printf("Enter pixelate block size: ");
                    scanf("%d", &block_size);
                    image = Pixelate(image, block_size);
                    printf("\"Pixelate\" operation is done!\n");
                    break;
              case 12:
                    printf("Enter shift X and Y values: ");
                    scanf("%d %d", &shift_x, &shift_y);
                    image = Shift(image, shift_x, shift_y);
                    printf("\"Shift\" operation is done!\n");
                    break;
              case 13:
					          printf("Please enter the X offset value: ");
					          scanf("%d", &crop_x);
					          printf("Please enter the Y offset value: ");
					          scanf("%d", &crop_y);
					          printf("Please input the crop width: ");
					          scanf("%d", &crop_width);
					          printf("Please input the crop height: ");
					          scanf("%d", &crop_height);
					          image = Crop(image, crop_x, crop_y, crop_width, crop_height);
                    printf("\"Crop\" operation is done!\n");
                    break;
				      case 14:
                    printf("Please input the new image width: ");
                    scanf("%d", &resize_width);
					          printf("Please input the new image height: ");
					          scanf("%d", &resize_height);
                    image = Resize(image, resize_width, resize_height);
                    printf("\"Resize\" operation is done!\n");
                    break;
              case 15:
                    image = Watermark(image, watermark_image);  // Apply watermark
                    printf("\"Watermark\" operation is done!\n");
                    DeleteImage(watermark_image);  // Free watermark image memory
                    watermark_image = NULL;
					          break;
              case 16:
                    printf("Please input the direction of rotation (0:clockwise, 1:counterclockwise): ");
                    scanf("%d", &direction);
                    image = RotateBy90(image, direction);
                    printf("\"RotateBy90\" operation is done!\n");
                    break;
              case 17: { 
                    int result = AutoTest();
					          if (result != 0) {
						              printf("AutoTest failed, error code %d.\n", result);
					          } else {
						              printf("AutoTest finished successfully.\n");
					          }
                    break;
					          }  
              default:
					          break;
			        }
	      } else {
			        printf("Invalid selection!");
		    }
		    PrintMenu();
		    printf("Please make your choice: ");
		    scanf("%d", &option);
	}
	if (image)
       	DeleteImage(image);
	if(watermark_image)
		    DeleteImage(watermark_image);
	printf("You exit the program.\n");
	return 0;
	#endif
}

void PrintMenu() {
      printf("\n----------------------------\n");
      printf(" 1: Load a PPM image\n");
      printf(" 2: Save an image in PPM and JPEG format\n");
      printf(" 3: Change a color image to Black & White\n");
      printf(" 4: Make a negative of an image\n");
      printf(" 5: Color filter an image\n");
      printf(" 6: Sketch the edge of an image\n");
      printf(" 7: Shuffle an image\n");
      printf(" 8: Flip an image vertically\n");
      printf(" 9: Mirror an image horizontally\n");
      printf("10: Add border to an image\n");
      printf("11: Pixelate an image\n");
      printf("12: Shift an image\n");
      printf("13: Crop an image\n");
      printf("14: Resize an image\n");
      printf("15: Add Watermark to an image\n");
      printf("16: Rotate an image by 90 degree\n");
	    printf("17: Test all functions\n");
	    printf("18: Exit\n");
}
