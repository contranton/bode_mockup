//REF: base code LAB08-SPI SEP:2019-II
//REF: MSP-EXP432P401R_Software_Examples_windows - HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735
//REF SPI: MSP430F55xx_Code_Examples - MSP430F55xx_uscia0_spi_09

/*
Name: SPI.c
Author: Fernando Hurtado, Felipe Rubio
Version: 1.0
Date: 30-06-2021
Comments:
    - Implementacion de comunicacion SPI
*/

#include <msp430.h>

#include "SPI.h"


void SPI_Master_Init(void)
{
    //Rellenar aquí: configurar puertos GPIO (Ver datasheet del Boostek pack) y
    //configurar periférico con protocolo SPI (Ver User's Guide)

    //pag 87 msp430 data sheet
    //RST PIN
    P7DIR |= BIT4;
    P7OUT |= BIT4;

    //PS PIN
    P2DIR |= BIT6;
    P2OUT &= ~BIT6;

    //RS PIN
    P8DIR |= BIT2;
    P8OUT &= ~BIT2;

    //MOSI & CLOCK PINS
    P3SEL |= BIT0 + BIT2;

    /* Put state machine in reset */
    UCB0CTL1 = UCSWRST;

    /* Set USCI_B0 to master mode SPI mode      */
    UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;

    UCB0CTL1 |= UCSSEL_2; // SMCLK

    UCB0BR0 |= 0x00; // /2 Baud Rate
    UCB0BR1 = 0; //

    //UCB0MCTL = 0; // No modulation
    UCB0CTL1 &= ~UCSWRST; // *Initialize USCI state machine*

}


void SPI_Master_transmit_char(uint8_t data, bool commandmode)
{
    //Rellenar con estado del puerto RS/CS
    //HINT: revisar macros wc y wd en archivo "SPI_implement_me.h"

    //Rellenar con acciÃ³n para transmitir


    if (commandmode==true){
        P8OUT &= ~BIT2;
    }
    else{
        P8OUT |= BIT2;
    }

    while ((UCB0IFG & UCTXIFG) == 0); // wait for transfer to complete
    UCB0TXBUF = data;    // writ

}
