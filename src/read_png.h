/**
 * @brief reads a png file and stores it into an integer array
 *
 * @author Konstantin Luebeck (University of Tuebingen, Embedded Systems)
 */

#ifndef READ_PNG_H
#define READ_PNG_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <png.h>

/**
 * @brief read a rgb png file and stores it into a 3-dimensional (X,Y and R,G,B) int array
 *
 * @param image 3D-array which contains the image data (will be allocated inside)
 * [x][y][rgb] [0] = red, [1] = green, [2] = blue
 * @param png_path full path to the png image file which should be read
 * @param width
 * @param height
 *
 * @return 0 == success, 1 == error
 */
int read_rgb_png(int**** image, const char* png_path, int* width, int* height);

/**
 * @brief read a rgb png file and stores it into a 2-dimensional (X,Y) int array
 *
 * @param image 3D-array which contains the image data (will be allocated inside)
 * [x][y]
 * @param png_path full path to the png image file which should be read
 * @param width
 * @param height
 *
 * @return 0 == success, 1 == error
 */
int read_grayscale_png(int*** image, const char* png_path, int* width, int* height);

#endif // READ_PNG_H
