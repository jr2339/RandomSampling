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
    if(argc < 4){
        perror("We need more arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    else if(argc > 4){
        perror("Too many arguments");
        exit(1);//if the nunber is not 0, not access to error
    }
    
    int Ratio =atoi(argv[1]);
    //int min = atoi(argv[2]);
    //int max = atoi(argv[2]);
    const char *inputName = argv[2];  //input.ppm
    const char *outputName = argv[3]; //output.ppm
    
    Buffer *buffer;
    
    /************************************************************************************************/
    

    for(int max=58; max<1000000001; max++) {
      
        buffer = ImageRead(inputName,Ratio,max);
        ImageWrite(buffer, outputName);
        
        double stastic_ave =0.0;
        double temp =0.0;
        for (int i=0; i<20; i++) {
            temp = ave(inputName,Ratio,max);
            stastic_ave += temp;
        }
        stastic_ave = stastic_ave/20;
        stastic_ave = ave(inputName,Ratio,max);
        printf("Ration: %d, Span: %d, Ave: %f\n",Ratio,max,stastic_ave);
    }

    
    return 0;
}

