//
//  main.c
//  Graphics
//
//  Created by jr2339 on 10/18/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image.h"

int main(int argc, const char * argv[]) {
    if(argc < 4){
        perror("We need more arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if(argc > 4){
        perror("Too many arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    int Ratio =atoi(argv[1]); 
    const char *inputName = argv[2];  //input.ppm
    const char *outputName = argv[3]; //output.ppm
    
    Buffer *buffer;
    
    /************************************************************************************************/
    
    buffer = ImageRead(inputName,Ratio);
    ImageWrite(buffer, outputName);
    
    return 0;
}

