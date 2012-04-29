#ifndef MATRIXH
#define MATRIXH

#define sbi(port, pin)   ((port) |= (uint8_t)(1 << pin))
#define cbi(port, pin)   ((port) &= (uint8_t)~(1 << pin))

#define ROWS PORTD
#define COLUMNS PORTC

#define COL1 PC0
#define COL2 PC1
#define COL3 PC2
#define COL4 PC3
#define COL5 PC4

#define ROW1 PD0
#define ROW2 PD1
#define ROW3 PD2
#define ROW4 PD3
#define ROW5 PD4
#define ROW6 PD5
#define ROW7 PD6

#endif
