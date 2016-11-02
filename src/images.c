/*
 * images.c
 *
 *  Created on: 2 nov. 2016
 *      Author: Acer
 */

#include "images.h"
#include "costume_image.h"
#include "avans_image.h"
#include "avans2_image.h"
#include "test_image.h"

IMAGE_DATA getCurrentImage() {
	return *propertyCurrentImage(0);
}

IMAGE_DATA *propertyCurrentImage(IMAGE_DATA *address){
	static IMAGE_DATA *data;

	//check if used as a setter
	if (address != 0){
		//set address and load an image
		data = address;
		nextImage();
	}

	return data;
}

void setCurrentImage(IMAGE_DATA *newImage){
	IMAGE_DATA * currentImage = propertyCurrentImage(0);
	currentImage->image = newImage->image;
	currentImage->width = newImage->width;
	currentImage->height = newImage->height;
}

void nextImage() {
	static char counter;

	switch (counter) {
	case 0:
		setCurrentImage(&avans_image);
		break;
	case 1:
		setCurrentImage(&avans2_image);
		break;
	default:
		setCurrentImage(&avans_image);
		counter = 0;
		break;
	}

	counter++;
}

