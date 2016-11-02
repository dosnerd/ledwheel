/*
 * timeRecorder.h
 *
 *  Created on: 25 okt. 2016
 *      Author: Acer
 */

#ifndef TIMERECORDER_H_
#define TIMERECORDER_H_

void timeRecorderInit(int);

void timeRecorderStart(void);

void timeRecorderStop(void);

void timeRecorderReset(void);

int timeRecorderValue(void);


#endif /* TIMERECORDER_H_ */
