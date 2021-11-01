/*
 * SPI.h
 *
 *  Created on: 28 jun. 2021
 *      Author: fernando
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_


#include <stdint.h>
#include <stdbool.h>

// The initialisation function. Call it once from your main() program before
// issuing any SPI commands with the functions below!
void SPI_Master_Init(void);

#define wc(DATA) SPI_Master_transmit_char(DATA, true)
#define wd(DATA) SPI_Master_transmit_char(DATA, false)

void SPI_Master_transmit_char(uint8_t data, bool commandmode);


#endif /* SPI_SPI_H_ */
