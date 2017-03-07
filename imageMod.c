//
// imageMod.c
// Lab 10 Final Project
//
// Created by Scott Stoudt on 12/2/15.
// Copyright © 2015 Scott Stoudt. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

void greyscale(int, int, Image *, Image *);
void onlyRed(int, int, Image *, Image *);
void onlyBlue(int, int, Image *, Image *);
void onlyGreen(int, int, Image*, Image *);
void negate(int, int, Image *, Image *);
void sepia(int, int, Image *, Image *);
void flipVert(int, int, Image *, Image *);
void flipHoriz(int, int, Image *, Image *);
void reduceColors(int, int, int, int, int, Image *, Image *); 
void pixelate(int, int, Image *, Image *);
void tintNshade(int, int, float, Image *, Image *);

int red, blue, green, average, cVal, cVal2, redVal, greenVal, blueVal;
float tsVal;

int main(){
  
  Image *original, *modified, *imageInput;
  int choice = -1;
  int imageSelection = -1;
  tsVal = -1;
  redVal = -1;
  greenVal = -1;
  blueVal = -1;
  
  original = imageRead("sunset.ppm");
  //original = imageRead("parrot.ppm");
  modified = imageRead("sunset.ppm");
  //modified = imageRead("parrot.ppm");
  
  int width = imageWidth(original);
  int height = imageHeight(original);

  while(choice != 0){
    printf("Please select the modification you would like to perform:\n");
    printf("To end the program, enter 0\n");
    printf("(1) Black and White (Greyscale)\n(2) Keep Red\n(3) Keep Blue\n(4) Keep Green\n(5) Negate\n(6) Sepia\n(7) Vertical Flip\n(8) Horizontal Flip\n(9) Tint or Shade\n(10) Reduce Colors\n(11) Pixelate\n");
    
    scanf("%d", &choice);
    if(choice == 0)
      exit(0);

    printf("Would you like start a new modification or add to the previously modified image?\n(1)New Modification\n(2)Add to Previously Modified Image\n");
    scanf("%d", &imageSelection);
    
    if(imageSelection == 1)
      imageInput = imageCopy(original);
    else if(imageSelection == 2)
      imageInput = imageCopy(modified);
    else
      printf("Not a valid command...\n");
 
    if(choice == 1)
      greyscale(width, height, imageInput, modified);
    else if(choice == 2)
      onlyRed(width, height, imageInput, modified);
    else if(choice == 3)
      onlyBlue(width, height, imageInput, modified);
    else if(choice == 4)
      onlyGreen(width, height, imageInput, modified);
    else if(choice == 5)
      negate(width, height, imageInput, modified);
    else if(choice == 6)
      sepia(width, height, imageInput, modified);
    else if(choice == 7)
      flipVert(width, height, imageInput, modified);
    else if(choice == 8)
      flipHoriz(width, height, imageInput, modified);
    else if(choice == 9){
      while(tsVal < 0 || tsVal > 2){
	printf("Please enter a decimal value 0-2:\n 0 = Full Shade\n 2 = Full Tint\n");
	scanf("%f", &tsVal);
	if(tsVal < 0 || tsVal > 2)
	  printf("Invalid value!\n");
      }
      tintNshade(width, height, tsVal, imageInput, modified);
      tsVal = -1;
    }
    else if(choice == 10){
      while(redVal < 0 || redVal > 255){
	printf("Enter a red reduction value 0-255: ");
	scanf("%d", &redVal);
	if(redVal < 0 || redVal > 255)
	  printf("Invalid value!\n");
      }
      while(greenVal < 0 || greenVal > 255){
	printf("Enter a green reduction value 0-255: ");
	scanf("%d", &greenVal);
	if(greenVal < 0 || greenVal > 255)
	  printf("Invalid value!\n");
      }
      while(blueVal < 0 || blueVal > 255){
	printf("Enter a blue reduction value 0-255: ");
	scanf("%d", &blueVal);
	if(blueVal < 0 || blueVal > 255)
	  printf("Invalid value!\n");
      }
      reduceColors(width, height, redVal, greenVal, blueVal, imageInput, modified);
      redVal = -1;
      greenVal = -1;
      blueVal = -1;
    }
    else if(choice == 11)
      pixelate(width, height, imageInput, modified);
    else
      printf("Not a valid command...\n");
  }
}

void greyscale(int width, int height, Image *original, Image *modified){

  for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){
	
	red = imageGetPixel(original, c, r, 0);
	green = imageGetPixel(original, c, r, 1);
	blue = imageGetPixel(original, c, r, 2);
	
	average = (red+green+blue)/3;
	
        imageSetPixel(modified, c, r, chan, average);
	
      }
    }
  }
  imageWrite(modified, "newSunset.ppm");
  
}

void onlyRed(int width, int height, Image *original, Image *modified){
  
  for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){
	
	red = imageGetPixel(original, c, r, chan);
	
	if(chan == 0)
	  imageSetPixel(modified, c, r, chan, red);
	else
	  imageSetPixel(modified, c, r, chan, 0);
	
      }
    }
  }
  imageWrite(modified, "newSunset.ppm");
  
}

void onlyBlue(int width, int height, Image *original, Image *modified){

  for(int r=0; r<height; r++){
   for(int c=0; c<width; c++){
     for(int chan=0; chan<3; chan++){
	
	blue = imageGetPixel(original, c, r, chan);
	
	if(chan == 2)
	  imageSetPixel(modified, c, r, chan, blue);
	else
	  imageSetPixel(modified, c, r, chan, 0);

      }
    }
  }
  imageWrite(modified, "newSunset.ppm");
}

void onlyGreen(int width, int height, Image *original, Image *modified){

   for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){
	
	green = imageGetPixel(original, c, r, chan);
	
	if(chan == 1)
	  imageSetPixel(modified, c, r, chan, green);
	else
	  imageSetPixel(modified, c, r, chan, 0);

      }
    }
  }
  imageWrite(modified, "newSunset.ppm");

}

void negate(int width, int height, Image *original, Image *modified){

  for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){

	cVal = imageGetPixel(original, c, r, chan);

	imageSetPixel(modified, c, r, chan, 255-cVal);

      }
    }
  }
  imageWrite(modified, "newSunset.ppm");

}

void sepia(int width, int height, Image *original, Image *modified){

  for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){
	
	red = imageGetPixel(original, c, r, 0);
	green = imageGetPixel(original, c, r, 1);
	blue = imageGetPixel(original, c, r, 2);

	average = (red+green+blue)/3;
	int total;
	
	if(chan == 0)
	  total = average + 30;
	else if(chan == 1)
	  total = average;
	else
	  total = average - 40;

	if(total < 0)
	  total = 0;
	else if(total > 255)
	  total = 255;

	imageSetPixel(modified, c, r, chan, total);

      }
    }
  }
  imageWrite(modified, "newSunset.ppm");


}

void flipVert(int width, int height, Image *original, Image *modified){

  for(int r=0; r<height/2; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){

	cVal = imageGetPixel(original, c, r, chan);
	cVal2 = imageGetPixel(original, c, height-1-r, chan);
	
        imageSetPixel(modified, c, r, chan, cVal2);
	imageSetPixel(modified, c, height-1-r, chan, cVal);

      }
    }
  }
  imageWrite(modified, "newSunset.ppm");

}

void flipHoriz(int width, int height, Image *original, Image *modified){

    for(int r=0; r<height; r++){
      for(int c=0; c<width/2; c++){
	for(int chan=0; chan<3; chan++){

	cVal = imageGetPixel(original, c, r, chan);
	cVal2 = imageGetPixel(original, width-1-c, r, chan);
	
        imageSetPixel(modified, c, r, chan, cVal2);
	imageSetPixel(modified, width-1- c, r, chan, cVal);

      }
    }
  }
  imageWrite(modified, "newSunset.ppm");

}

void reduceColors(int width, int height, int redVal, int greenVal, int blueVal, Image *original, Image *modified){
  
  for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){
	cVal = imageGetPixel(original, c, r, chan);

	if(chan == 0)
	  cVal2 = cVal-redVal;
	else if(chan == 1)
	  cVal2 = cVal-greenVal;
	else
	  cVal2 = cVal-blueVal;
       
	if(cVal2 < 0)
	  cVal2 = 0;	  

	imageSetPixel(modified, c, r, chan, cVal2);
      }
    }
  }
  imageWrite(modified, "newSunset.ppm");

}

void pixelate(int width, int height, Image *original, Image *modified){
  
  for(int r=4; r<height-4; r+=9){
    for(int c=4; c<width-4; c+=9){
      for(int chan=0; chan<3; chan++){

	cVal = imageGetPixel(original, c, r, chan);

	for(int rr=r-4; rr<=r+4; rr++)
	  for(int cc=c-4; cc<=c+4; cc++)
	    imageSetPixel(modified, cc, rr, chan, cVal);
	
      }
    }
  }
  imageWrite(modified, "newSunset.ppm");
}

void tintNshade(int width, int height, float tsVal, Image *original, Image *modified){
  for(int r=0; r<height; r++){
    for(int c=0; c<width; c++){
      for(int chan=0; chan<3; chan++){
	cVal = imageGetPixel(original, c, r, chan);
	cVal2 = cVal * tsVal;

	if(cVal2 > 255)
	  cVal2 = 255;
	  
	imageSetPixel(modified, c, r, chan, cVal2);
      }
    }
  }
  imageWrite(modified, "newSunset.ppm");

}
