
This directory is intended for project hardware information.

[The schematic](Ender3_schematic.PDF) is only for finding Port/Pin values [PAx]. Cross-reference the pinout below to define Digital Pin values [Dx].

                         ATMEL ATMEGA1284 Pinout 

                                +---\/---+
                    (D 0) PB0  1|        |40  PA0 (AI 0 / D31)
                    (D 1) PB1  2|        |39  PA1 (AI 1 / D30)
               INT2 (D 2) PB2  3|        |38  PA2 (AI 2 / D29)
                PWM (D 3) PB3  4|        |37  PA3 (AI 3 / D28)
             SS PWM (D 4) PB4  5|        |36  PA4 (AI 4 / D27)
               MOSI (D 5) PB5  6|        |35  PA5 (AI 5 / D26)
               MISO (D 6) PB6  7|        |34  PA6 (AI 6 / D25)
                SCK (D 7) PB7  8|        |33  PA7 (AI 7 / D24)
                          RST  9|        |32  AREF
                          VCC 10|        |31  GND
                          GND 11|        |30  AVCC
                        XTAL2 12|        |29  PC7 (D 23)
                        XTAL1 13|        |28  PC6 (D 22)
               RX0 (D 8)  PD0 14|        |27  PC5 (D 21) TDI
               TX0 (D 9)  PD1 15|        |26  PC4 (D 20) TDO
          INT0 RX1 (D 10) PD2 16|        |25  PC3 (D 19) TMS
          INT1 TX1 (D 11) PD3 17|        |24  PC2 (D 18) TCK
               PWM (D 12) PD4 18|        |23  PC1 (D 17) SDA
               PWM (D 13) PD5 19|        |22  PC0 (D 16) SCL
               PWM (D 14) PD6 20|        |21  PD7 (D 15) PWM
                                +--------+

