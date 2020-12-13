#include <vector>
#include <iostream>
#include <string>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <stdexcept>
#include "prototypes.h"

void SaveImg(char *filename, std::vector<char> image, int width, int height)
{
  stbi_write_bmp(filename, width, height, 1, image.data());
}

void Dessiner(int PID1, int PID2)
{
    int width=100;
    int height=100;
    char filename[11]="Damier.bmp";
    char Case[5];
    int PID,PPID;
    printf("PID1=%d PID2=%d\n",PID1, PID2);
    
    std::vector<char> image;
    image.resize(width * height);
    for (int it=0; it < width*height ;it++) 
    {
        image[it] = 128; //Gris
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            sprintf(Case,"%4d", i+100*j);
            if (GetPIDnPPIDfromFile(&PID, &PPID, Case)!=-1) //Case occupée GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName);
                {
                    if (PPID==PID1) image[j * width + i] = 0;//noir
                    if (PPID==PID2) image[j * width + i] = 255;//blanc
                }  
        }
    }
    SaveImg(filename, image, width, height);
}

