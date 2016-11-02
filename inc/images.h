/*
 * images.h
 *
 *  Created on: 2 nov. 2016
 *      Author: Acer
 */

#ifndef IMAGES_H_
#define IMAGES_H_

typedef struct{
	const unsigned char *image;
	unsigned char height;
	unsigned char width;
} IMAGE_DATA;

IMAGE_DATA getCurrentImage();
IMAGE_DATA *propertyCurrentImage(IMAGE_DATA *address);
void nextImage(void);
void setCurrentImage(IMAGE_DATA *newImage);

#endif /* IMAGES_H_ */
