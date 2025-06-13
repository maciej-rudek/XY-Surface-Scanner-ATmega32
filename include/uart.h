#ifndef _UART_H_
#define _UART_H_

#define POS 16
#define END_SYMBOL 13 // 13

#define REQ_NON 0

#define REQ_SYM4 4

#define REQ_DAC1 1
#define REQ_DAC2 2
#define REQ_DAC3 3
#define REQ_DAC4 4
#define REQ_DAC5 5
#define REQ_DAC6 6
#define REQ_DAC7 7
#define REQ_DAC8 8


#define REQ_SYM5 5

#define REQ_ADC1 11
#define REQ_ADC2 12
#define REQ_ADC3 13
#define REQ_ADC4 14

#define REQ_IDN 100
#define REQ_TIME1 21
#define REQ_TIME2 22
#define REQ_TIME3 23
#define REQ_TIME4 24

struct sUART{
    unsigned char buf [POS];
    char req [POS];
    char count; // old A
} ;

struct sDecode{
    char buf [POS];
    char quest;
    float var; // old A
} ;

extern struct sUART sU;
extern struct sDecode sD;

void Uart_Send( char tekst[]);
char DecodeUart(char cUDR);
char DecodeRequest();

#endif