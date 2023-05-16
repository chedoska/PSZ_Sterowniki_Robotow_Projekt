#ifndef INC_BALL_SOUND_H_
#define INC_BALL_SOUND_H_

#define SAMPLE_NUMBER 4000
#define PI_CONST_SOUND 3.1415926

#include "math.h"
#include "gyroscope.h"

uint32_t sound_wav[SAMPLE_NUMBER];

void generateSineWave(uint32_t frequency, uint32_t amplitude, uint32_t timer_frequency);
void addSineWaveAt(uint32_t frequency, uint32_t amplitude, uint32_t timer_frequency, uint32_t begin, uint32_t end);

#endif /* INC_BALL_SOUND_H_ */
