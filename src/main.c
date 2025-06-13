#ifndef __PLATFORM_NATIVE__
  #include <Arduino.h>
  #include "../include/initial.h"
#endif
#include "../include/variables.h"
#include "../include/uart.h"

extern struct sUART sU;
extern struct sDecode sD;


#ifndef __PLATFORM_NATIVE__
  ISR(USART_RXC_vect)				// PRZERWANIE przy odebraniu znaku
  {
    char uart_status = DecodeUart(UDR);
    if(uart_status == 1)
    {
      QueueUart();
      uart_status = 0;
    }
  }
#endif

int main()
{
  
  #ifndef __PLATFORM_NATIVE__
    SPI_MasterInit();
    IoInit();
    UartInit();
  #endif
  
  while(1)
  {

  }
  return 0;

}