//
//  Image.c
//  Graphics
//
//  Created by jr2339 on 10/18/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#include "Image.h"
#define RationInWidth 4
#define RationInHeight 4
int readMagicNumber(FILE *fp) {
    int magic_number;
    if (!fscanf(fp, "P%d\n", &magic_number)){
        fprintf(stderr,"file is not in PPM format, we can't read it");
        exit(1);
    }
    return magic_number;
}
/**************************************************************************************************************
 **************************************************************************************************************/
void skip_comments(FILE *f_source){
    char ch;
    /*skip the comments*/
    ch = getc(f_source); // ch is int
    /*
     gets the next character (an unsigned char) from the specified
     stream and advances the position indicator for the stream.
     */
    while(ch =='#'){
        do{
            ch=getc(f_source);
        }
        while(ch!='\n'); //read to the end of the line
        ch=getc(f_source);
    }
    if(!isdigit(ch)){
        fprintf(stderr,"can't read header information from PPM format\n");
    }
    else{
        ungetc(ch, f_source); //put that digital back
    }
}
/**************************************************************************************************************
 **************************************************************************************************************/
// readPPMHeader help us to detemine which format is our source image

long int readHeader(FILE *f_source, Buffer *buffer, int *source_width,int *source_height){
    
    //int source_width,source_height,
    int source_maxval;
     skip_comments(f_source);
    //read the width, height,amd maximum value for a pixel
    fscanf(f_source, "%d %d %d ",source_width,source_height,&source_maxval);
    
    buffer->width = *source_width/RationInWidth;
    buffer->height = *source_height/RationInHeight;
    buffer->maxval = source_maxval;

    if(buffer->maxval >= 65336 ||buffer->maxval <= 0){
        fprintf(stderr,"image is not ture-color(8byte), read failed\n");
        exit(1);
    }
    return ftell(f_source);
}

/**************************************************************************************************************
 **************************************************************************************************************/

Buffer *ImageRead(const char *filename){
    FILE *f_source = fopen(filename,"r");
    if(!f_source){
        fprintf(stderr,"can't open file for reading \n");
        exit(1);
    }
    
    int source_width,source_height;

    Buffer *buffer = (Buffer *)malloc(sizeof(Buffer));
  
    if(!buffer){
        fprintf(stderr,"Can't allocate memory for new image");
        exit(1);
    }
    buffer->magic_number = readMagicNumber(f_source);
    long int header_length = readHeader(f_source,buffer,&source_width,&source_height);
    int size = source_width*source_height;
    buffer->box = (Box *)malloc(sizeof(Box)*size);
    *buffer->box = (Box){};
    
    if(buffer->magic_number==6){
        unsigned char c ;//init
        int index = rand()%10;
        fseek(f_source,3*index, SEEK_CUR);
        while (index < size) {     //Dr.plamer tola me should be the origianl size of image
            int x = ((index%source_width)/(RationInWidth));  //col_index in buffer
            int y = ((index/source_width)/(RationInHeight)); // row_index in buffer
            
            //printf("%d\n",index);
            
            fread(&c, 1, 1, f_source);
            buffer->box[y*buffer->width+x].r_sum += c;
            fread(&c, 1, 1, f_source);
            buffer->box[y*buffer->width+x].g_sum += c;
            fread(&c, 1, 1, f_source);
            buffer->box[y*buffer->width+x].b_sum += c;
            
            buffer->box[y*buffer->width+x].count++;


            int jump = rand()%10;
            

            fseek(f_source,3*jump, SEEK_CUR);
            index += 1 + jump;
        }

    }
   
    int buffer_size = buffer->width*buffer->height;
    
    for (int i=0; i<buffer_size; i++) {
        
        if (buffer->box[i].count != 0) {
            buffer->box[i].r_sum = (buffer->box[i].r_sum)/(buffer->box[i].count);
            buffer->box[i].g_sum = (buffer->box[i].g_sum)/(buffer->box[i].count);
            buffer->box[i].b_sum = (buffer->box[i].b_sum)/(buffer->box[i].count);
        }
        else{
            //if we didn't simple at this box, we choose the first one.
            unsigned char c ;//init
            int x = (i%buffer->width)*RationInWidth;  //col_index in buffer
            int y = (i/buffer->width)*RationInHeight; // row_index in buffer
            fseek(f_source, header_length+(y*source_width+x)*3, SEEK_SET);
            fread(&c, 1, 1, f_source);
            buffer->box[i].r_sum = c;
            fread(&c, 1, 1, f_source);
            buffer->box[i].g_sum = c;
            fread(&c, 1, 1, f_source);
            buffer->box[i].b_sum = c;
            
        }
        printf("the count at %d is %d\n",i,buffer->box[i].count);
        
    }
   

    return buffer;
}
/**************************************************************************************************************
 **************************************************************************************************************/
void ImageWrite(Buffer *buffer, const char *filename,int format){
    int size = buffer->width * buffer->height;
    printf("buffer width is %d, buffer heught is %d\n",buffer->width,buffer->height);
    FILE *f_des = fopen(filename, "w");
    if (!f_des){
        fprintf(stderr,"cannot open file for writing");
    }
    unsigned char ch;
    if(format==6){
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,buffer->width, buffer->height, buffer->maxval);
        for(int i=0; i<size;i++){
            ch=buffer->box[i].r_sum;
            fwrite(&ch, 1, 1, f_des);
            ch=buffer->box[i].g_sum;
            fwrite(&ch, 1, 1, f_des);
            ch=buffer->box[i].b_sum;
            fwrite(&ch, 1, 1, f_des);
            
        }
    }
    fclose(f_des);
    
    
}











