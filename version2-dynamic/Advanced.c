/* Advanced.c
Assignment 4

Date      Author      Notes
2/17/25   Yan Li      Initial version
4/4/25    Yan Li      Initial upload to GitHub
*/

#include "Advanced.h"
#include <stdio.h>
#include <assert.h>

/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H) {
        assert(image != NULL);     // Ensure the image pointer is valid
        assert(image->R != NULL);  // Ensure the R channel pointer is valid
        assert(image->G != NULL);  // Ensure the G channel pointer is valid
        assert(image->B != NULL);  // Ensure the B channel pointer is valid

        // Ensure crop starts within image bounds
        if (x < 0) x = 0;
        if (y < 0) y = 0;

        // Adjust crop width and height to fit within the image
        if (x + W > ImageWidth(image)) W = ImageWidth(image) - x;
        if (y + H > ImageHeight(image)) H = ImageHeight(image) - y;

        // Create a new cropped image with the adjusted dimensions
        Image *temp = CreateImage(W, H);
        assert(temp != NULL); // Ensure memory allocation succeeded

	      // Copy pixels from the original image to the cropped image
    	  for (int newY = 0; newY < H; newY++) {
        	      for (int newX = 0; newX < W; newX++) {
            		        SetPixelR(temp, newX, newY, GetPixelR(image, x + newX, y + newY));
            		        SetPixelG(temp, newX, newY, GetPixelG(image, x + newX, y + newY));
            		        SetPixelB(temp, newX, newY, GetPixelB(image, x + newX, y + newY));
        	      }
    	  }

	      DeleteImage(image);
 	      return temp;
}

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight) {
	      assert(image != NULL);     // Ensure the image pointer is valid
        assert(image->R != NULL);  // Ensure the R channel pointer is valid
        assert(image->G != NULL);  // Ensure the G channel pointer is valid
        assert(image->B != NULL);  // Ensure the B channel pointer is valid
        assert(newWidth > 0 && newHeight > 0);  // Ensure new dimensions are positive

        unsigned int oldWidth = ImageWidth(image);
        unsigned int oldHeight = ImageHeight(image);

        // Compute scale factors
        double scaleX = (double)oldWidth / newWidth;
        double scaleY = (double)oldHeight / newHeight;

        // Create a new image with the target dimensions
        Image *temp = CreateImage(newWidth, newHeight);
        assert(temp != NULL); // Ensure memory allocation succeeded

	      for (int y = 0; y < newHeight; y++) {
	              for (int x = 0; x < newWidth; x++) {
            		        int srcX = (int)(x * scaleX);
            		        int srcY = (int)(y * scaleY);

            		        SetPixelR(temp, x, y, GetPixelR(image, srcX, srcY));
            		        SetPixelG(temp, x, y, GetPixelG(image, srcX, srcY));
            		        SetPixelB(temp, x, y, GetPixelB(image, srcX, srcY));
        	      }
    	  }

        DeleteImage(image);
        return temp;
}

/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image) {
	      assert(image != NULL);
        assert(watermark_image != NULL);
        assert(image->R != NULL);
        assert(image->G != NULL);
        assert(image->B != NULL);

	      for (int y = 0; y < ImageHeight(image); y++) {
	              for (int x = 0; x < ImageWidth(image); x++) {
            		        // Get watermark pixel (using modulo for tiling)
            		        int wm_x = x % ImageWidth(watermark_image);
            		        int wm_y = y % ImageHeight(watermark_image);

            		        int wm_r = GetPixelR(watermark_image, wm_x, wm_y);
            		        int wm_g = GetPixelG(watermark_image, wm_x, wm_y);
            		        int wm_b = GetPixelB(watermark_image, wm_x, wm_y);

            		        // If watermark pixel is black (0,0,0), apply the effect
            		        if (wm_r == 0 && wm_g == 0 && wm_b == 0) {
                		            int new_r = GetPixelR(image, x, y) * 1.45;
                		        int new_g = GetPixelG(image, x, y) * 1.45;
                		        int new_b = GetPixelB(image, x, y) * 1.45;

                		        // Clamp values to avoid overflow
                		        SetPixelR(image, x, y, new_r > 255 ? 255 : new_r);
                		        SetPixelG(image, x, y, new_g > 255 ? 255 : new_g);
                		        SetPixelB(image, x, y, new_b > 255 ? 255 : new_b);
            		        }
        	      }
    	  }
	      watermark_image = NULL;
        return image;
}

/* Rotate by 90 */
Image *RotateBy90(Image *image, int rotateDirection) {
	      assert(image != NULL);
        assert(image->R != NULL);
        assert(image->G != NULL);
        assert(image->B != NULL);
        assert(rotateDirection == 0 || rotateDirection == 1);

    	  Image *temp = CreateImage(ImageHeight(image), ImageWidth(image));

    	  for (int y = 0; y < ImageHeight(image); y++) {
        	      for (int x = 0; x < ImageWidth(image); x++) {
            		        char r = GetPixelR(image, x, y);
            		        char g = GetPixelG(image, x, y);
            		        char b = GetPixelB(image, x, y);
            		        if (rotateDirection == 0) { // Clockwise
                		            SetPixelR(temp, ImageHeight(image) - 1 - y, x, r);
                		            SetPixelG(temp, ImageHeight(image) - 1 - y, x, g);
	                	            SetPixelB(temp, ImageHeight(image) - 1 - y, x, b);
        	    	        } else { // Counterclockwise
                		            SetPixelR(temp, y, ImageWidth(image) - 1 - x, r);
                		            SetPixelG(temp, y, ImageWidth(image) - 1 - x, g);
                		            SetPixelB(temp, y, ImageWidth(image) - 1 - x, b);
            		        }
        	      }
   	    }

        DeleteImage(image);
        return temp;
}
