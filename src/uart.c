#ifndef __PLATFORM_NATIVE__
	#include <Arduino.h>
#endif
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include "../include/variables.h"
#include "../include/uart.h"

struct sUART sU;
struct sDecode sD;
struct DAC_variables sDAC;
struct ADC_variables sADC;


void Uart_Send( char tekst[]);
char DecodeUart(char cUDR);
void ProcesBuffer(char sym_pos);
char DecodeVariable(char sym_pos, void *variable, const char *format );
char DecodeInst();
char QueueUart();

void Uart_Send(  char tekst[] )
{
  #ifndef __PLATFORM_NATIVE__
    unsigned char i;
      UCSRB = 0x18;
      i=0;
      while ( tekst[i] )
      { while ( !( UCSRA & (1<<UDRE)) );
        UDR = tekst[i];  
        i++;
      }
    while ( !( UCSRA & (1<<UDRE)) );
    UDR = 10;
    while ( !( UCSRA & (1<<UDRE)) );
    UDR = 13;
    while ( !( UCSRA & (1<<UDRE)) );
    UCSRB = 0x98;
  #endif
}


char DecodeUart(char cUDR)
{
    sU.buf[sU.count] = cUDR;

    if (sU.buf[sU.count] == END_SYMBOL)
    {
      for(char i = 0; i < POS; ++i)
      {
        sU.req[i] = sU.buf[i];
        sU.buf[i] = 0;
      }
      sU.count = 0;
      return(1);
    }
    else{
      sU.count++;
      sU.count = sU.count % POS;
      return(0);
    }
}


void ProcesBuffer(char sym_pos)
{
  char i = 0;
    do
      { 
        sD.buf[i]=sU.req[i + 1 + sym_pos]; 
        i++; 
      }while(sU.req[i] != END_SYMBOL);
}

char DecodeVariable(char sym_pos, void *variable, const char *format )
{
  sD.quest = (sU.req[sym_pos]=='?') ? '?' : 'x' ;

  if(sD.quest=='?')
  { 
    if(format == "%f")
    {
      sprintf( sD.buf, format,  *((float*)variable ));
    }
    if(format == "%c")
    {
      sprintf( sD.buf, format,  *((char*)variable ));
    }
    
    Uart_Send(sD.buf);
  }
  else
  {
    ProcesBuffer(sym_pos);
    if(format == "%f")
    {
      sscanf(sD.buf, format, &sD.var );
      variable = &sD.var;
    }
    if(format == "%c")
    {
      sscanf(sD.buf, format, &sD.cvar );
      variable = &sD.cvar;
    }
  }
  return 0;
}

char DecodeInst()
{
  if (0 == strncmp(sU.req,"*IDN",REQ_SYM4)) return REQ_IDN;
  
  if (0 == strncmp(sU.req,"DAC1",REQ_SYM4)) return REQ_DAC1;
  if (0 == strncmp(sU.req,"DAC2",REQ_SYM4)) return REQ_DAC2;
  if (0 == strncmp(sU.req,"DAC3",REQ_SYM4)) return REQ_DAC3;
  if (0 == strncmp(sU.req,"DAC4",REQ_SYM4)) return REQ_DAC4;
  if (0 == strncmp(sU.req,"DAC5",REQ_SYM4)) return REQ_DAC5;
  if (0 == strncmp(sU.req,"DAC6",REQ_SYM4)) return REQ_DAC6;
  if (0 == strncmp(sU.req,"DAC7",REQ_SYM4)) return REQ_DAC7;
  if (0 == strncmp(sU.req,"DAC8",REQ_SYM4)) return REQ_DAC8;

  if (0 == strncmp(sU.req,"ADC1",REQ_SYM4)) return REQ_ADC1;
  if (0 == strncmp(sU.req,"ADC2",REQ_SYM4)) return REQ_ADC2;
  if (0 == strncmp(sU.req,"ADC3",REQ_SYM4)) return REQ_ADC3;
  if (0 == strncmp(sU.req,"ADC4",REQ_SYM4)) return REQ_ADC4;
}

char QueueUart()
{
  char instr = DecodeInst();

  switch (instr)
  {
    case REQ_IDN:
      Uart_Send(ID);
    break;
  
    case REQ_DAC1:
      DecodeVariable(REQ_SYM4, &sDAC.DAC1, "%f");
    break;

    case REQ_DAC2:
      DecodeVariable(REQ_SYM4, &sDAC.DAC2, "%f");
    break;

    case REQ_DAC3:
      DecodeVariable(REQ_SYM4, &sDAC.DAC3, "%f");
    break;

    case REQ_DAC4:
      DecodeVariable(REQ_SYM4, &sDAC.DAC4, "%f");
    break;

    case REQ_ADC1:
      DecodeVariable(REQ_SYM4, &sADC.ADC1, "%f");
    break;

    case REQ_ADC2:
      DecodeVariable(REQ_SYM4, &sADC.ADC2, "%f");
    break;

    case REQ_ADC3:
      DecodeVariable(REQ_SYM4, &sADC.ADC3, "%f");
    break;

    case REQ_ADC4:
      DecodeVariable(REQ_SYM4, &sADC.ADC4, "%f");
    break;
  
    default:
      Uart_Send(WHATISTHAT);
    break;
  }

  return instr;
}