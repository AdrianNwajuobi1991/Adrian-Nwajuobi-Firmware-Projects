#include <avr/io.h>

#define SLAVE_SELECT 			SPI_SS_PORT &= ~(1 << SPI_SS);
#define SLAVE_DESELECT 			SPI_SS_PORT |=  (1 << SPI_SS)

// Instruction Set from data sheet
#define READ			0b00000011
#define WRITE			0b00000010
#define WRDI			0b00000100
#define WREN			0b00000110
#define RDSR			0b00000101
#define WRSR			0b00000001

// Status Register bits

#define WIP				0
#define	WEL				1
#define	BP0				2
#define	BP1				3

#define BYTES_PER_PAGE    64
#define	BYTES_MAX		32767

//Functions

void init_SPI(void);

void byte_trade(uint8_t byte);

void send_address(uint16_t address);

uint8_t read_status(void);

void write_status(uint8_t status);

void write_enable(void);

void write_disable(void);

uint8_t read_byte(uint16_t address);

uint16_t read_word(uint16_t address);

void write_byte(uint16_t address, uint8_t byte);

void write_word(uint16_t address, uint16_t word);
