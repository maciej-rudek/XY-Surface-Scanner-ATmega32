#ifndef VARIABLES_H_
#define VARIABLES_H_

struct DAC_variables{
    float DAC1;
    float DAC2;
    float DAC3;
    float DAC4;
    float DAC5;
    float DAC6;
    float DAC7;
    float DAC8;
} ;

struct ADC_variables{
    float ADC1;
    float ADC2;
    float ADC3;
    float ADC4;
} ;


extern struct DAC_variables sDAC;
extern struct ADC_variables sADC;


#endif