/**
 * @author Konstantin Luebeck (University of Tuebingen, Embedded Systems)
 */

#include "read_png.h"

int read_rgb_png(int**** image, const char* png_path, int* height, int* width) {

    // check if file exists
    if(access(png_path, F_OK) == -1) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_rgb_png] ERROR: File '%s' does not exist.\n", png_path);
        #endif
        return 1;
    }


    FILE *png_file = fopen(png_path, "r");


    #ifdef PNG_DEBUG
    printf("[read_rgb_png] INFO: Opening '%s'\n", png_path);
    #endif

    // check if opening the file was successful
    if(png_file == 0) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_rgb_png] ERROR: Could not open file '%s'.\n", png_path);
        #endif
        return 1;
    }


    png_structp png;
    png_infop png_info;
    char png_header[8];

    png_byte color_type;
    png_byte bit_depth;

    png_bytep* row_pointers;
    int row_bytes;

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(png == 0) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_rgb_png] ERROR: png_create_read_struct.\n");
        #endif
        return 1;
    }

    fread(png_header, 1, 8, png_file);

    png_info = png_create_info_struct(png);

    if(png_info == 0) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_rgb_png] ERROR: png_create_info_struct.\n");
        #endif
        return 1;
    }
   
    if(setjmp(png_jmpbuf(png))) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_rgb_png] ERROR: setjmp.\n");
        #endif
        return 1;
    }

    // get information on PNG
    png_init_io(png, png_file);
    png_set_sig_bytes(png, 8);
    png_read_info(png, png_info);

    (*width) = png_get_image_width(png, png_info);
    (*height) = png_get_image_height(png, png_info);

    color_type = png_get_color_type(png, png_info);
    bit_depth = png_get_bit_depth(png, png_info);

    row_bytes = png_get_rowbytes(png, png_info);

    #ifdef PNG_DEBUG
    printf("[read_rgb_png] INFO: Dimensions: %dx%d\n", (*width), (*height));
    printf("[read_rgb_png] INFO: Color type: %d\n", color_type);
    printf("[read_rgb_png] INFO: Bit depth: %d\n", bit_depth);
    #endif

    png_read_update_info(png, png_info);

    if(setjmp(png_jmpbuf(png))) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_rgb_png] ERROR: setjmp.\n");
        #endif
        return 1;
    }

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));

    int x, y;

    (*image) = (int***) malloc(sizeof(int**) * (*width));
    for(x = 0; x < (*width); x++) {

        (*image)[x] = (int**) malloc(sizeof(int*) * (*height));
        
        for(y = 0; y < (*height); y ++) {
            (*image)[x][y] = (int*) malloc(sizeof(int) * 3);
        }
    }


    for(y = 0; y < (*height); y++) {
        row_pointers[y] = (png_byte*) malloc(row_bytes);
    }

    png_read_image(png, row_pointers);

    int x_byte;

    // store data into image 
    for(y = 0; y < (*height); y++) {
        x = 0;
        for(x_byte = 0; x_byte < row_bytes; x_byte+=3) {
            (*image)[x][y][0] = (int) row_pointers[y][x_byte];
            (*image)[x][y][1] = (int) row_pointers[y][x_byte+1];
            (*image)[x][y][2] = (int) row_pointers[y][x_byte+2];
            x++;
        }
    }

    fclose(png_file);

    for(y = 0; y < (*height); y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    return 0;
}

int read_grayscale_png(int*** image, const char* png_path, int* height, int* width) {

    // check if file exists
    if(access(png_path, F_OK) == -1) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_grayscale_png] ERROR: File '%s' does not exist.\n", png_path);
        #endif
        return 1;
    }


    FILE *png_file = fopen(png_path, "r");


    #ifdef PNG_DEBUG
    printf("[read_grayscale_png] INFO: Opening '%s'\n", png_path);
    #endif

    // check if opening the file was successful
    if(png_file == 0) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_grayscale_png] ERROR: Could not open file '%s'.\n", png_path);
        #endif
        return 1;
    }


    png_structp png;
    png_infop png_info;
    char png_header[8];

    png_byte color_type;
    png_byte bit_depth;

    png_bytep* row_pointers;
    int row_bytes;

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(png == 0) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_grayscale_png] ERROR: png_create_read_struct.\n");
        #endif
        return 1;
    }

    fread(png_header, 1, 8, png_file);

    png_info = png_create_info_struct(png);

    if(png_info == 0) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_grayscale_png] ERROR: png_create_info_struct.\n");
        #endif
        return 1;
    }
   
    if(setjmp(png_jmpbuf(png))) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_grayscale_png] ERROR: setjmp.\n");
        #endif
        return 1;
    }

    // get information on PNG
    png_init_io(png, png_file);
    png_set_sig_bytes(png, 8);
    png_read_info(png, png_info);

    (*width) = png_get_image_width(png, png_info);
    (*height) = png_get_image_height(png, png_info);

    color_type = png_get_color_type(png, png_info);
    bit_depth = png_get_bit_depth(png, png_info);

    row_bytes = png_get_rowbytes(png, png_info);

    #ifdef PNG_DEBUG
    printf("[read_grayscale_png] INFO: Dimensions: %dx%d\n", (*width), (*height));
    printf("[read_grayscale_png] INFO: Color type: %d\n", color_type);
    printf("[read_grayscale_png] INFO: Bit depth: %d\n", bit_depth);
    #endif

    png_read_update_info(png, png_info);

    if(setjmp(png_jmpbuf(png))) {
        #ifdef PNG_DEBUG
        fprintf(stderr, "[read_grayscale_png] ERROR: setjmp.\n");
        #endif
        return 1;
    }

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));

    int x, y;

    (*image) = (int**) malloc(sizeof(int**) * (*width));
    for(x = 0; x < (*width); x++) {

        (*image)[x] = (int*) malloc(sizeof(int*) * (*height));
        
    }


    for(y = 0; y < (*height); y++) {
        row_pointers[y] = (png_byte*) malloc(row_bytes);
    }

    png_read_image(png, row_pointers);

    // store data into image 
    for(y = 0; y < (*height); y++) {
        for(x = 0; x < row_bytes; x++) {
            (*image)[x][y] = (int) row_pointers[y][x];
        }
    }

    fclose(png_file);

    for(y = 0; y < (*height); y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    return 0;

}


