/***************************************************
 *This is a USART2 library for the MSP430.
 *
 * It can provide basic USART2 (serial) communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 * 
 * 
 * 
 * FOR STUDENTS:
 * 
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper code
 * and complete these functions.
 * 
 * 
 * Hint 1: We do not expect you to write the most performant or exceptionally
 * well-engineered code, but it should work. If in doubt, sacrifice speed for
 * reliability. 
 * 
 ****************************************************/


// includes
#include <msp430.h>
#include <string.h>

#include <USART2/USART2.h>



// The initialisation function. Call it once from your main() program before
// issuing any USART2 commands with the functions below!
//
// Call it at any time to change the USART2 communication parameters.
//
// Returns zero in case of success, non-zero for errors.
uint8_t USART2_Init(struct USART2_configuration config)
{
    // You can recycle your previous code. But remember, this time you are
    // supposed to configure interrupts! Maybe you]ll have to extend it a little bit?

    P4SEL |= BIT4 + BIT5;

    // UCA1STAT |= UCLISTEN;
    // Reiniciar modulo uart en msp
    UCA1CTL1 |= UCSWRST;

    uint8_t flag = 0;

    switch (config.baudrate)
    {
    case 1200: UCA1CTL1 |= UCSSEL0; UCA1BR0 = 27; UCA1BR1 = 0; UCA1MCTL |= UCBRS1; break;
    case 2400: UCA1CTL1 |= UCSSEL0; UCA1BR0 = 13; UCA1BR1 = 0; UCA1MCTL |= UCBRS1+UCBRS2; break;
    case 4800: UCA1CTL1 |= UCSSEL0; UCA1BR0 = 6; UCA1BR1 = 0; UCA1MCTL |= UCBRS0+UCBRS1+UCBRS2; break;
    case 9600: UCA1CTL1 |= UCSSEL1; UCA1BR0 = 109; UCA1BR1 = 0; UCA1MCTL |= UCBRS0; break;
    case 19200: UCA1CTL1 |= UCSSEL1; UCA1BR0 = 54; UCA1BR1 = 0; break;
    case 57600: UCA1CTL1 |= UCSSEL1; UCA1BR0 = 18; UCA1BR1 = 0; UCA1MCTL |= UCBRS0+UCBRS1; break;
    case 115200: UCA1CTL1 |= UCSSEL1; UCA1BR0 = 9; UCA1BR1 = 0; UCA1MCTL |= UCBRS2+UCBRS1; break;
    default:
        flag |= BIT3;
        break;
    }

    switch (config.databits)
    {
    case 5: break;
    case 6: break;
    case 7: UCA1CTL0 |= UC7BIT; break;
    case 8: UCA1CTL0 &= ~UC7BIT; break;
    default:
        flag |= BIT2;
        break;
    }

    switch (config.parity)
    {
    case 'N': UCA1CTL0 &= ~UCPEN; break;
    case 'E': UCA1CTL0 |= UCPEN; UCA1CTL0 |= UCPAR; break;
    case 'O': UCA1CTL0 |= UCPEN; UCA1CTL0 &= ~UCPAR; break;
    default:
        flag |= BIT1;
        break;
    }

    switch (config.stopbits)
    {
    case 1: UCA1CTL0 &= ~UCSPB; break;
    case 2: UCA1CTL0 |= UCSPB; break;
    default:
        flag |= BIT0;
        break;
    }

    UCA1CTL1 &= ~UCSWRST;

    if (!flag) return 0;
    else return 1;
}



// Transmits a single character
void USART2_Transmit_char(uint8_t data)
{
    // A nice hint: With interrupts, you can send bytes whenever the register UCA1TXBUF
    // is free. And there is an interrupt called UCTXIFG that *tells you*
    // whenever UCA1TXBUF is free.
    // This requires you to have some bytes in the buffer that you would like to
    // send, of course. You have a buffer, don't you?
    while (!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = data;
}



// Transmits a given string
void USART2_Transmit_String(char* string)
{
    int len = strlen(string);
    unsigned int i;
    for (i = 0; i < len; i++)
    {
        USART2_Transmit_char(string[i]);
    }
}



// Receives a single character.
char USART2_Receive_char(void)
{
    // A nice hint: With interrupts, your microcontroller can inform you whenever
    // a character comes in. There is an interrupt called UCRXIFG for that.
    // If such an interrupt would fill a buffer with the received data, this
    // function here could return you one character from this buffer. You would no
    // longer need to 'wait for the byte to arrive', but could just fetch it out
    // of this buffer at any later point. And of course you've got a buffer,
    // right?
    // If the buffer is actually empty, you could maybe return a 0 or so to
    // indicate that to the user?
    while (!(UCA1IFG & UCRXIFG));
    char data = UCA1RXBUF;
    return data;
}


// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART2_Receive_String(char* buffer, uint8_t bufflen)
{
    // Your previous code might need little adaptions here. As a nice hint: A
    // string consists of many characters. If a user gives you a buffer to fill
    // for him, and you have a buffer full of already received characters...
    unsigned int i;
    char nextchar;
    for (i = 0; i < bufflen / sizeof(char); i++)
    {
        nextchar = USART2_Receive_char();
        if (nextchar == '\n') break;
        else buffer[i] = nextchar;
    }
    return i * sizeof(char);
} 

