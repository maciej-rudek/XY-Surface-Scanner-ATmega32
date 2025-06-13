#include <unity.h>
#include "../include/variables.h" // Potrzebne dla POS, END_SYMBOL
#include "../include/uart.h"   // Dołącz nagłówek z deklaracjami
#include <stdio.h>
#include <string.h>


void setUp(void) {
}

void tearDown(void) {
    // clean stuff up here
    sD.var = 0;
    sD.quest = 0;
    for (size_t i = 0;  i < POS; i++)
    {
        sU.buf[i] = 0;
        sU.req[i] = 0;
        sU.count = 0;

        sD.buf[i] = 0;
    }
    
}
void test_DecodeUart_single(){
    char result = 0;
    result = DecodeUart('x');

    TEST_ASSERT_EQUAL(0, result); 
    TEST_ASSERT_EQUAL('x', sU.buf[0]); 
    TEST_ASSERT_EQUAL(1, sU.count); 
}

void test_DecodeUart_full() {

    char result = 0;
    
    for(int i = 0; i < 16-1; ++i) 
    {
        result = DecodeUart('a' + i);
        TEST_ASSERT_EQUAL(0, result); 
        TEST_ASSERT_EQUAL('a' + i, sU.buf[i]); 
        TEST_ASSERT_EQUAL(i+1, sU.count); 
        
    }

    // END of buffor:
    result = DecodeUart(END_SYMBOL);
    TEST_ASSERT_EQUAL(1, result); 
    for(int i = 0; i < 16; ++i) 
    {
        TEST_ASSERT_EQUAL(0, sU.buf[i]); 
    }
    TEST_ASSERT_EQUAL(END_SYMBOL, sU.req[15]);


}

void test_QueueUart_DAC1()
{
    char result = 0;
    strcpy(sU.req, "DAC1 121\xD"); 

    result = QueueUart();
    TEST_ASSERT_EQUAL(REQ_DAC1, result);
    TEST_ASSERT_EQUAL('x', sD.quest);
}

void test_QueueUart_DAC1_send()
{
    char result = 0;
    strcpy(sU.req, "DAC1 3.14\xD"); 

    result = QueueUart();
    TEST_ASSERT_EQUAL('3', sD.buf[0]);
    TEST_ASSERT_EQUAL('.', sD.buf[1]);
    TEST_ASSERT_EQUAL('1', sD.buf[2]);
    TEST_ASSERT_EQUAL('4', sD.buf[3]);
    TEST_ASSERT_EQUAL('\xD', sD.buf[4]);
    TEST_ASSERT_EQUAL(3.14, sD.var);
}


void test_QueueUart_DAC1_check()
{
    char result = 0;
    strcpy(sU.req, "DAC1? ---\xD"); 

    result = QueueUart();
    TEST_ASSERT_EQUAL('3', sD.buf[0]); // 3.14159
    TEST_ASSERT_EQUAL('.', sD.buf[1]);
    TEST_ASSERT_EQUAL('1', sD.buf[2]);
    TEST_ASSERT_EQUAL('4', sD.buf[3]);
    TEST_ASSERT_EQUAL('1', sD.buf[4]);
    TEST_ASSERT_EQUAL('5', sD.buf[5]);
    TEST_ASSERT_EQUAL('9', sD.buf[6]);
    TEST_ASSERT_EQUAL('0', sD.buf[7]);
}

int main( int argc, char **argv) {
     //pio test -e uTest -vvv
    UNITY_BEGIN();
    tearDown();
    RUN_TEST(test_DecodeUart_single);
    tearDown();
    RUN_TEST(test_DecodeUart_full);
    tearDown();
    RUN_TEST(test_QueueUart_DAC1);
    tearDown();
    RUN_TEST(test_QueueUart_DAC1_send);
    tearDown();
    RUN_TEST(test_QueueUart_DAC1_check);

    UNITY_END();
    return 0; // Dodano return dla main
}