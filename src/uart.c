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


char DecodeUart(char cUDR);
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

char DecodeFloat(char sym_pos, float *variable )
{
  sD.quest = (sU.req[sym_pos]=='?') ? '?' : 'x' ;

  if(sD.quest=='?')
  { 
    sprintf( sD.buf, "%f", *variable );
    Uart_Send(sD.buf);
  }
  else
  {
    char i = 0;
    do
      { 
        sD.buf[i]=sU.req[i + 1 + sym_pos]; 
        i++; 
      }while(sU.req[i] != END_SYMBOL);
    
      sscanf(sD.buf, "%f", &sD.var );
      variable = &sD.var;
  }
  return 0;
}

char DecodeChar(char sym_pos, char *variable )
{
  sD.quest = (sU.req[sym_pos]=='?') ? '?' : 'x' ;

  if(sD.quest=='?')
  { 
    sprintf( sD.buf, "%c", *variable );
    Uart_Send(sD.buf);
  }
  else
  {
    char i = 0;
    do
      { 
        sD.buf[i]=sU.req[i + 1 + sym_pos]; 
        i++; 
      }while(sU.req[i] != END_SYMBOL);
    
      sscanf(sD.buf, "%c", &sD.cvar );
      variable = &sD.cvar;
  }
  return 0;
}

char DecodeInst()
{
  if (0 == strncmp(sU.req,"*IDN",REQ_SYM4)) return REQ_IDN;
  if (0 == strncmp(sU.req,"DAC1",REQ_SYM4)) return REQ_DAC1;
  if (0 == strncmp(sU.req,"DAC2",REQ_SYM4)) return REQ_DAC2;

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
      sDAC.DAC1 = 3.14159;
      DecodeFloat(REQ_SYM4, &sDAC.DAC1);
    break;
  
    default:
      Uart_Send(WHATISTHAT);
    break;
  }

  return instr;
}