#ifndef __PLATFORM_NATIVE__
	#include <Arduino.h>
#endif
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include "../include/variables.h"
#include "../include/uart.h"

#define ID "MR_001a"

struct sUART sU;
struct sDecode sD;


char DecodeUart(char cUDR);
char DecodeRequest();

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


char DecodeRequest()
{
  char ret = 0;
  if(0==strncmp(sU.req,"*IDN?",5)) 
	  { 
      ret = 1;
      Uart_Send(ID);
	  }
    if(0==strncmp(sU.req,"DAC1",4))
    { 
      ret = 2;
      sD.quest = (sU.req[4]=='?') ? 'a' : 'x' ;

      if(sU.req[4]==' ')
      { 
        char i = 0;
        do
          { 
            sD.buf[i]=sU.req[i+5]; 
            i++; 
          }while(sU.req[i]!=13);
        
          sscanf(sD.buf, "%f", &sD.var );
    }
		  // if(zapytanie==1)
			// { 
      //   sprintf( temp, "%d", m_PGA );
		  //   Uart_Send(temp);
			// }
	    }
  return ret;
}