//REF: LAB09 SEP 2019-2 AVR-CODE
/***************************************************
 * This is a I2C library for the MSP430F5529.
 *
 * It can provide basic I2C communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 ****************************************************/

/*
Name: I2C.c
Author: Fernando Hurtado, Felipe Rubio
Version: 1.0
Date: 30-06-2021
Comments:
    - Implementacion de comunicacion I2C
*/

// includes
#include <I2C/I2C.h>
#include <msp430.h>
#include <stdint.h>

// Config I2C
void i2cConfig(uint8_t slaveAddress)
{
	// Rellenar con la configuración necesaria
    P4SEL |= BIT1 + BIT2;
    UCB1CTL1 |= UCSWRST;
    UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
    UCB1CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK
    UCB1BR0 = 3;                              // fSCL = SMCLK/3 = ~400kHz
    UCB1BR1 = 0;
	i2cSlaveSet(slaveAddress);
	UCB1CTL1 &= ~UCSWRST;

}

// Set Slave Adress
void i2cSlaveSet(uint8_t slaveAddress)
{
    UCB1I2CSA = slaveAddress;
}

// Set transmit: Write
void i2cSetWriteMode()
{	
    UCB1CTL1 |= UCTR;
}

// Set Transmit: READ
void i2CSetReadMode()
{
    UCB1CTL1 &= ~UCTR;
}

// Send a start condition
void i2cSendStart()
{
    UCB1CTL1 |= UCTXSTT;
}


// Send a stop condition
void i2cSendStop()
{
    UCB1CTL1 |= UCTXSTP;
}


// Waits for the previous operation to finish
void i2cWaitForComplete()
{
    while (!(UCB1IFG & UCTXIFG));
}


// Transmits one byte over the bus to a slave
// (Can be either an address or a value.)
void i2cSendByte(unsigned char data)
{
    UCB1TXBUF = data;
}




// Receives one byte from a slave
// (Always a value; master has no address.)
// Send an ACK if you expect more data, NAK if not.
void i2cReceiveByte(bool sendAnACK)
{
    if (sendAnACK) {
        UCB1CTL1 &= ~UCTXNACK;
    } else {
        UCB1CTL1 |= UCTXNACK;
    }

    while((UCB1IFG & UCRXIFG)==0);
}


// It is possible to *not* call this function after a call to
// i2cReceiveByte() if you are not interested in the actual value.
unsigned char i2cGetReceivedByte(void)
{
    uint8_t received = 0;
    received = UCB1RXBUF;
    return received;
}
