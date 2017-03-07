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
    if(argc < 5){
        perror("We need more arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if(argc > 5){
        perror("Too many arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    
    int Ratio =atoi(argv[1]);
    //int min = atoi(argv[2]);
    int max = atoi(argv[2]);
    const char *inputName = argv[3];  //input.ppm
    const char *outputName = argv[4]; //output.ppm
    
    Buffer *buffer;
    
    /************************************************************************************************/
    
    buffer = ImageRead(inputName,Ratio,max);
    ImageWrite(buffer, outputName);
    
    double stastic_ave =0.0;
    double temp =0.0;
    for (int i=0; i<10; i++) {
        temp = ave(inputName,Ratio,max);
        stastic_ave += temp;
    }
    stastic_ave = stastic_ave/10;
    printf("the stastic_average count is %f\n",stastic_ave);
    
    return 0;
}

