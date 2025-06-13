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

struct Time_variables{
    char point; // time in point quisition
    char step; // time between point to point movement
    char retour; // retour TIP time to  next line
    char position; // time to move tip to position
} ;

struct Scan_variables{
    char scan; // 0 - stop, 1 - start, 2 - reset
    char mode; // 0 - line to line, 1 - snake, 2 - sinus
    char oX; // start position x
    char oY; // start position y
    char points; // resolution picture 
    // char lines; // resolution picture
} ;


extern struct DAC_variables sDAC;
extern struct ADC_variables sADC;
extern struct Time_variables sTIME;
extern struct Scan_variables sSCAN;

#endif // VARIABLES_H_