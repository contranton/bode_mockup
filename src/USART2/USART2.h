/***************************************************
 * This is a USART library for the MSP430F5529
 *
 * It can provide basic USART (serial) communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 * 
 * 
 * 
 * FOR STUDENTS:
 * 
 * This file has an incomplete struct definition. Add definitions for its
 * members! Check the other files and the lab description to find out which
 * parameters and what ranges are needed.
 * 
 ****************************************************/

#ifndef _USART2_IMPLEMENT_ME_H_
#define _USART2_IMPLEMENT_ME_H_

#include <stdint.h>

/* You can use it, but it isn't mandatory*/
struct USART2_configuration
{
    uint16_t baudrate;
    uint8_t databits;
    uint8_t parity;
    uint8_t stopbits;
};


// Call once to initialise USART communication
uint8_t USART2_Init(struct USART2_configuration config);

// Transmits a single character
void USART2_Transmit_char(uint8_t data);

// Transmits a given string
void USART2_Transmit_String(char* string);

// Receives a single character
char USART2_Receive_char(void);

// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART2_Receive_String(char* buffer, uint8_t bufflen);

#endif // _USART_IMPLEMENT_ME_H_
