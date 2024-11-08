#ifndef pinout_h
#define pinout_h

// ATMEL ATMEGA644/ATMEGA1284 / SANGUINO
//
//                        +---\/---+
//            (D 0) PB0  1|        |40  PA0 (AI 0 / D31)
//            (D 1) PB1  2|        |39  PA1 (AI 1 / D30)
//       INT2 (D 2) PB2  3|        |38  PA2 (AI 2 / D29)
//        PWM (D 3) PB3  4|        |37  PA3 (AI 3 / D28)
//     SS PWM (D 4) PB4  5|        |36  PA4 (AI 4 / D27)
//       MOSI (D 5) PB5  6|        |35  PA5 (AI 5 / D26)
//       MISO (D 6) PB6  7|        |34  PA6 (AI 6 / D25)
//        SCK (D 7) PB7  8|        |33  PA7 (AI 7 / D24)
//                  RST  9|        |32  AREF
//                  VCC 10|        |31  GND
//                  GND 11|        |30  AVCC
//                XTAL2 12|        |29  PC7 (D 23)
//                XTAL1 13|        |28  PC6 (D 22)
//       RX0 (D 8)  PD0 14|        |27  PC5 (D 21) TDI
//       TX0 (D 9)  PD1 15|        |26  PC4 (D 20) TDO
//  INT0 RX1 (D 10) PD2 16|        |25  PC3 (D 19) TMS
//  INT1 TX1 (D 11) PD3 17|        |24  PC2 (D 18) TCK
//       PWM (D 12) PD4 18|        |23  PC1 (D 17) SDA
//       PWM (D 13) PD5 19|        |22  PC0 (D 16) SCL
//       PWM (D 14) PD6 20|        |21  PD7 (D 15) PWM
//                        +--------+

#define PIN_A0 (31)
#define PIN_A1 (30)
#define PIN_A2 (29)
#define PIN_A3 (28)
#define PIN_A4 (27)
#define PIN_A5 (26)
#define PIN_A6 (25)
#define PIN_A7 (24)

#define PIN_B0 (0)
#define PIN_B1 (1)
#define PIN_B2 (2)
#define PIN_B3 (3)
#define PIN_B4 (4)
#define PIN_B5 (5)
#define PIN_B6 (6)
#define PIN_B7 (7)

#define PIN_C0 (16)
#define PIN_C1 (17)
#define PIN_C2 (18)
#define PIN_C3 (19)
#define PIN_C4 (20)
#define PIN_C5 (21)
#define PIN_C6 (22)
#define PIN_C7 (23)

#define PIN_D0 (8)
#define PIN_D1 (9)
#define PIN_D2 (10)
#define PIN_D3 (11)
#define PIN_D4 (12)
#define PIN_D5 (13)
#define PIN_D6 (14)
#define PIN_D7 (15)

#endif