//
//  main.c
//  Graphics
//
//  Created by jr2339 on 10/18/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"

int main(int argc, const char * argv[]) {
    if(argc < 6){
        perror("We need more arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if(argc > 6){
        perror("Too many arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    int Ratio =atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);
    const char *inputName = argv[4];  //input.ppm
    const char *outputName = argv[5]; //output.ppm
    
    Buffer *buffer;
    
    /************************************************************************************************/
    
    buffer = ImageRead(inputName,Ratio,min,max);
    ImageWrite(buffer, outputName);
    
    return 0;
}

