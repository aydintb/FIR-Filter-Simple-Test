// FIR Filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
	This is a very simple C++ implementation of a floating point FIR filter.
 */

#include <iostream>
#include <assert.h>
#include <math.h>
#include <time.h>


/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 0.1 Hz

* 0 Hz - 0.005 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = 3.666895709039202 dB

* 0.01 Hz - 0.05 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = -41.09174091632818 dB

*/

#define SAMPLEFILTER_TAP_NUM 27

typedef struct {
  double history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
} SampleFilter;

//void SampleFilter_init(SampleFilter* f);
//void SampleFilter_put(SampleFilter* f, double input);
//double SampleFilter_get(SampleFilter* f);


static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
  -255,
  -260,
  -312,
  -288,
  -144,
  153,
  616,
  1233,
  1963,
  2739,
  3474,
  4081,
  4481,
  4620,
  4481,
  4081,
  3474,
  2739,
  1963,
  1233,
  616,
  153,
  -144,
  -288,
  -312,
  -260,
  -255
};

void SampleFilter_init(SampleFilter* f) {
  int i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void SampleFilter_put(SampleFilter* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == SAMPLEFILTER_TAP_NUM)
    f->last_index = 0;
}

int SampleFilter_get(SampleFilter* f) {
  long long acc = 0;
  int index = f->last_index, i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long long)f->history[index] * filter_taps[i];
  };
  return acc >> 16;
}


int _tmain(int argc, _TCHAR* argv[])
{
	SampleFilter sf;

	SampleFilter_init(&sf);

	srand(time(0));
	for (int i = 0; i < SAMPLEFILTER_TAP_NUM; i++)
	{
		//float random = ((float) rand()) / (float) RAND_MAX;
		//SampleFilter_put(&sf, random);
		SampleFilter_put(&sf, rand());

		int result = SampleFilter_get(&sf);
		
		printf("%i\r\n", result);
	}

	
	return 0;
}

