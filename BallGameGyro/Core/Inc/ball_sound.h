#ifndef INC_BALL_SOUND_H_
#define INC_BALL_SOUND_H_

#define TIMER_FREQUENCY 20000
#define MAX_AMPLITUDE 4000
#define SAMPLE_NUMBER 6300
#define PI_CONST_SOUND 3.1415926

#include "math.h"
#include "gyroscope.h"

uint32_t sound_wav[SAMPLE_NUMBER];

void generateSineWave(uint32_t frequency, uint32_t amplitude, uint32_t timer_frequency);
void addSineWaveAt(uint32_t frequency, uint32_t amplitude, uint32_t timer_frequency, uint32_t begin, uint32_t end);
void initMelody_1();
void initMelody_2();

#endif /* INC_BALL_SOUND_H_ */