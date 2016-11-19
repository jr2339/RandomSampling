//
//  Image.h
//  Graphics
//
//  Created by jr2339 on 10/18/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>



typedef struct Image{
    int width;
    int height;
    int magic_number;
    u_char *pixel;
    int maxval;
}Image;



typedef struct Box{
    int r_sum;
    int g_sum;
    int b_sum;
    //double r_average;
    //double g_average;
    //double b_average;
    int count;
}Box;


typedef struct Buffer{
    int width;
    int height;
    int magic_number;
    int maxval;
    union{
        Box *box;
    };
}Buffer;








int readMagicNumber(FILE *fp);
long int readHeader(FILE *f_source, Buffer *buffer, int *source_width,int *source_height);
Buffer *ImageRead(const char *filename);
void ImageWrite(Buffer *buffer, const char *filename,int format);

#endif /* Image_h */
