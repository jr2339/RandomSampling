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
#include <time.h>

typedef struct Image{
    int width;
    int height;
    int magic_number;
    u_char *pixel;
    int maxval;
}Image;


typedef struct Box{
    int r;
    int g;
    int b;
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
long int readHeader(FILE *f_source, Buffer *buffer, int *source_width,int *source_height,int Ratio);
Buffer *ImageRead(const char *filename,int Ratio,int max);
void ImageWrite(Buffer *buffer, const char *filename);
double ave(const char *filename,int Ratio,int max);
#endif /* Image_h */
