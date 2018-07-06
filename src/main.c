/**
 * @brief example program on how to read RGB and grayscale PNGs 
 *
 * @author Konstantin Luebeck (University of Tuebingen, Embedded Systems)
 */

#include <stdio.h>
#include "read_png.h"

void usage() {
    printf("SYNTAX:\nread_png PATH_TO_PNG RGB\n\n");
    printf("\tPATH_TO_PNG: path to png file\n");
    printf("\tRGB: 1 = rgb png, 0 = grayscale png\n");
}

int main(int argc, char** argv) {

    // check if an input argument was provided
    if(argc != 3) {
        fprintf(stderr, "ERROR: No path to PNG file and/or color type provided.\n");
        usage();
        return 1;
    }

    int color_type = atoi(argv[2]);

    int width;
    int height;

    if(color_type == 0) {

        int** image;

        read_grayscale_png(&image, argv[1], &width, &height);

        int x, y;

        for(y = 0; y < height; y++) {
            for(x = 0; x < width; x++) {
                printf("%02x ", image[x][y]);
            }
            printf("\n");
        }

        for(x = 0; x < width; x++) {
            free(image[x]);
        }
        free(image);

    } else if(color_type == 1) {
    
        int*** image;

        read_rgb_png(&image, argv[1], &width, &height);

        int x, y;

        for(y = 0; y < height; y++) {
            for(x = 0; x < width; x++) {
                printf("%02x ", image[x][y][0]);
                printf("%02x ", image[x][y][1]);
                printf("%02x ", image[x][y][2]);
            }
            printf("\n");
        }

        for(x = 0; x < width; x++) {
            for(y = 0; y < width; y++) {
                free(image[x][y]);
            }
            free(image[x]);
        }
        free(image);
    }

    
    return 0;
}
