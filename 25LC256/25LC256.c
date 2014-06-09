#include "25LC256.h"

void init_SPI (void){
	 SPI_SS_DDR |= (1 << SPI_SS);                        /* set SS output */
  SPI_SS_PORT |= (1 << SPI_SS);       /* start off not selected (high) */

  SPI_MOSI_DDR |= (1 << SPI_MOSI);                   /* output on MOSI */
  SPI_MISO_PORT |= (1 << SPI_MISO);                  /* pullup on MISO */
  SPI_SCK_DDR |= (1 << SPI_SCK);                      /* output on SCK */

  /* Don't have to set phase, polarity b/c
   * default works with 25LCxxx chips */
  SPCR |= (1 << SPR1);                /* div 16, safer for breadboards */
  SPCR |= (1 << MSTR);                                  /* clockmaster */
  SPCR |= (1 << SPE); 
}

void byte_trade (uint8_t byte){
	SPDR = byte;
	loop_until_bit_is_set(SPSR, SPIF);
}

void send_address (uint16_t address){
	byte_trade((uint8_t) (address >> 8));
	byte_trade((uint8_t) address);
}

uint8_t read_status(void) {
	SLAVE_SELECT;
	byte_trade(RDSR);
	byte_trade(0);
	SLAVE_DESELECT;
	return (SPDR);
}

void write_enable(void) {
	SLAVE_SELECT;
	byte_trade(WREN);
	SLAVE_DESELECT;
}

void write_disable(void) {
	SLAVE_SELECT;
	byte_trade(WRDI);
	SLAVE_DESELECT;
}

void write_status(uint8_t status) {
	write_enable();
	SLAVE_SELECT;
	byte_trade(WRSR);
	byte_trade(status);
	SLAVE_DESELECT;
	while(read_status() & (1 << WIP)){;
	}
}

uint8_t read_byte(uint16_t address){
	SLAVE_SELECT;
	byte_trade(READ);
	send_address(address);
	trade_byte(0);
	SLAVE_DESELECT;
	return (SPDR);
}

uint16_t read_word (uint16_t address){
	uint16_t word_val;
	SLAVE_SELECT;
	byte_trade(READ);
	send_address(address);
	byte_trade(0);
	word_val = SPDR;
	word_val <<= 8;
	byte_trade(0);
	word_val += SPDR;
	SLAVE_DESELECT;
	return (word_val);
}

void write_byte(uint16_t address, uint8_t byte){
	write_enable();
	SLAVE_SELECT;
	byte_trade(WRITE);
	send_address(address);
	byte_trade(byte);
	SLAVE_DESELECT;
	while(read_status() & (1 << WIP)){;
	}
}

void write_word(uint16_t address, uint16_t word){
	write_enable();
	SLAVE_SELECT;
	byte_trade(WRITE);
	send_address(address);
	byte_trade((uint8_t) (word >> 8));
	byte_trade((uint8_t) (word));
	SLAVE_DESELECT;
	while(read_status() & (1 << WIP)){;
	}
}




