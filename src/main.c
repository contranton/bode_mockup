

////***************************////////////
////*******LIBRARIES***********////////////
////***************************////////////

#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "USART/USART.h"
#include "USART2/USART2.h"
#include "I2C/I2C.h"
#include "SPI/SPI.h"
#include "display/testroutines.h"
#include "display/ST7735_commands.h"
#include "display/graphic_shapes.h"


void bode(int, int);
int actual_bode[6] = {0,0,0,0,0,0};
int recent_bode[6] = {0,0,0,0,0,0};

/** The main function */
int main(void)
{
    //Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    //Display initialization and SPI communication
    SPI_Master_Init();
    ST7735_init();

    //paint the screen black
    fillScreen(ST7735_BLACK);

    //Initialize all bands to 0
    bode(1,0);
    bode(2,0);
    bode(3,0);
    bode(4,0);
    bode(5,0);
    bode(6,0);

    __delay_cycles(2000000);

    //Raise first band to 50%.
    bode(1,50);
    __delay_cycles(2000000);

    //Raise first band to 75%.
    bode(1,75);
    __delay_cycles(2000000);

    //Raise second band to 40%.
    bode(2,40);
    __delay_cycles(2000000);

    //Raise third band to 90%.
    bode(3,90);
    __delay_cycles(2000000);

    //Raise fifth band to 50%.
    bode(5,50);
    __delay_cycles(2000000);

    //Raise sixth band to 75%.
    bode(6,75);
    __delay_cycles(2000000);

    //Lower fifth band to 10%.
    bode(5,10);
}

void bode(int banda, int percentage)
{
    recent_bode[banda-1] = actual_bode[banda-1];
    actual_bode[banda-1] = percentage;

    switch(banda){
    case 1:
        //To Erase lines
        drawLine(0, 0, recent_bode[0]*TFT_WIDTH/100, 5, ST7735_BLACK);
        drawLine(recent_bode[0]*TFT_WIDTH/100, 5, recent_bode[0]*TFT_WIDTH/100, TFT_HEIGHT/6-5, ST7735_BLACK);
        drawLine(recent_bode[0]*TFT_WIDTH/100, TFT_HEIGHT/6-5, recent_bode[1]*TFT_WIDTH/100, TFT_HEIGHT/6+5, ST7735_BLACK);

        //To Print lines
        drawLine(0, 0, actual_bode[0]*TFT_WIDTH/100, 5, ST7735_WHITE);
        drawLine(actual_bode[0]*TFT_WIDTH/100, 0+5, actual_bode[0]*TFT_WIDTH/100, TFT_HEIGHT/6-5, ST7735_WHITE);
        drawLine(actual_bode[0]*TFT_WIDTH/100, TFT_HEIGHT/6-5, actual_bode[1]*TFT_WIDTH/100, TFT_HEIGHT/6+5, ST7735_WHITE);
        break;
    case 2:

        drawLine(actual_bode[0]*TFT_WIDTH/100, TFT_HEIGHT/6-5, recent_bode[1]*TFT_WIDTH/100, TFT_HEIGHT/6+5, ST7735_BLACK);
        drawLine(recent_bode[1]*TFT_WIDTH/100, TFT_HEIGHT/6+5, recent_bode[1]*TFT_WIDTH/100, 2*TFT_HEIGHT/6-5, ST7735_BLACK);
        drawLine(recent_bode[1]*TFT_WIDTH/100, 2*TFT_HEIGHT/6-5, recent_bode[2]*TFT_WIDTH/100, 2*TFT_HEIGHT/6+5, ST7735_BLACK);

        drawLine(actual_bode[0]*TFT_WIDTH/100, TFT_HEIGHT/6-5, actual_bode[1]*TFT_WIDTH/100, TFT_HEIGHT/6+5, ST7735_WHITE);
        drawLine(actual_bode[1]*TFT_WIDTH/100, TFT_HEIGHT/6+5, actual_bode[1]*TFT_WIDTH/100, 2*TFT_HEIGHT/6-5, ST7735_WHITE);
        drawLine(actual_bode[1]*TFT_WIDTH/100, 2*TFT_HEIGHT/6-5, actual_bode[2]*TFT_WIDTH/100, 2*TFT_HEIGHT/6+5, ST7735_WHITE);

        break;

    case 3:
        drawLine(actual_bode[1]*TFT_WIDTH/100, 2*TFT_HEIGHT/6-5, recent_bode[2]*TFT_WIDTH/100, 2*TFT_HEIGHT/6+5, ST7735_BLACK);
        drawLine(recent_bode[2]*TFT_WIDTH/100, 2*TFT_HEIGHT/6+5, recent_bode[2]*TFT_WIDTH/100, 3*TFT_HEIGHT/6-5, ST7735_BLACK);
        drawLine(recent_bode[2]*TFT_WIDTH/100, 3*TFT_HEIGHT/6-5, recent_bode[3]*TFT_WIDTH/100, 3*TFT_HEIGHT/6+5, ST7735_BLACK);

        drawLine(actual_bode[1]*TFT_WIDTH/100, 2*TFT_HEIGHT/6-5, actual_bode[2]*TFT_WIDTH/100, 2*TFT_HEIGHT/6+5, ST7735_WHITE);
        drawLine(actual_bode[2]*TFT_WIDTH/100, 2*TFT_HEIGHT/6+5, actual_bode[2]*TFT_WIDTH/100, 3*TFT_HEIGHT/6-5, ST7735_WHITE);
        drawLine(actual_bode[2]*TFT_WIDTH/100, 3*TFT_HEIGHT/6-5, actual_bode[3]*TFT_WIDTH/100, 3*TFT_HEIGHT/6+5, ST7735_WHITE);

    case 4:
        drawLine(actual_bode[2]*TFT_WIDTH/100, 3*TFT_HEIGHT/6-5, recent_bode[3]*TFT_WIDTH/100, 3*TFT_HEIGHT/6+5, ST7735_BLACK);
        drawLine(recent_bode[3]*TFT_WIDTH/100, 3*TFT_HEIGHT/6+5, recent_bode[3]*TFT_WIDTH/100, 4*TFT_HEIGHT/6-5, ST7735_BLACK);
        drawLine(recent_bode[3]*TFT_WIDTH/100, 4*TFT_HEIGHT/6-5, recent_bode[4]*TFT_WIDTH/100, 4*TFT_HEIGHT/6+5, ST7735_BLACK);

        drawLine(actual_bode[2]*TFT_WIDTH/100, 3*TFT_HEIGHT/6-5, actual_bode[3]*TFT_WIDTH/100, 3*TFT_HEIGHT/6+5, ST7735_WHITE);
        drawLine(actual_bode[3]*TFT_WIDTH/100, 3*TFT_HEIGHT/6+5, actual_bode[3]*TFT_WIDTH/100, 4*TFT_HEIGHT/6-5, ST7735_WHITE);
        drawLine(actual_bode[3]*TFT_WIDTH/100, 4*TFT_HEIGHT/6-5, actual_bode[4]*TFT_WIDTH/100, 4*TFT_HEIGHT/6+5, ST7735_WHITE);

    case 5:
        drawLine(actual_bode[3]*TFT_WIDTH/100, 4*TFT_HEIGHT/6-5, recent_bode[4]*TFT_WIDTH/100, 4*TFT_HEIGHT/6+5, ST7735_BLACK);
        drawLine(recent_bode[4]*TFT_WIDTH/100, 4*TFT_HEIGHT/6+5, recent_bode[4]*TFT_WIDTH/100, 5*TFT_HEIGHT/6-5, ST7735_BLACK);
        drawLine(recent_bode[4]*TFT_WIDTH/100, 5*TFT_HEIGHT/6-5, recent_bode[5]*TFT_WIDTH/100, 5*TFT_HEIGHT/6+5, ST7735_BLACK);

        drawLine(actual_bode[3]*TFT_WIDTH/100, 4*TFT_HEIGHT/6-5, actual_bode[4]*TFT_WIDTH/100, 4*TFT_HEIGHT/6+5, ST7735_WHITE);
        drawLine(actual_bode[4]*TFT_WIDTH/100, 4*TFT_HEIGHT/6+5, actual_bode[4]*TFT_WIDTH/100, 5*TFT_HEIGHT/6-5, ST7735_WHITE);
        drawLine(actual_bode[4]*TFT_WIDTH/100, 5*TFT_HEIGHT/6-5, actual_bode[5]*TFT_WIDTH/100, 5*TFT_HEIGHT/6+5, ST7735_WHITE);

    case 6:
        drawLine(actual_bode[4]*TFT_WIDTH/100, 5*TFT_HEIGHT/6-5, recent_bode[5]*TFT_WIDTH/100, 5*TFT_HEIGHT/6+5, ST7735_BLACK);
        drawLine(recent_bode[5]*TFT_WIDTH/100, 5*TFT_HEIGHT/6+5, recent_bode[5]*TFT_WIDTH/100, 6*TFT_HEIGHT/6-5, ST7735_BLACK);
        drawLine(recent_bode[5]*TFT_WIDTH/100, 6*TFT_HEIGHT/6-5, 0, 6*TFT_HEIGHT/6+5, ST7735_BLACK);

        drawLine(actual_bode[4]*TFT_WIDTH/100, 5*TFT_HEIGHT/6-5, actual_bode[5]*TFT_WIDTH/100, 5*TFT_HEIGHT/6+5, ST7735_WHITE);
        drawLine(actual_bode[5]*TFT_WIDTH/100, 5*TFT_HEIGHT/6+5, actual_bode[5]*TFT_WIDTH/100, 6*TFT_HEIGHT/6-5, ST7735_WHITE);
        drawLine(actual_bode[5]*TFT_WIDTH/100, 6*TFT_HEIGHT/6-5, 0, 6*TFT_HEIGHT/6+5, ST7735_WHITE);
    default:
        break;
    }
    recent_bode[banda-1] = actual_bode[banda-1];
    actual_bode[banda-1] = percentage;
}



