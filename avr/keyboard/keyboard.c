#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/common.h>
#include "../avr_common/uart.h"

int main(void)
{
    /*
        Configuring pin 37, 36 as output and 22, 23 as input

        PA0 = 37
        PA1 = 36

        PC0 = 22
        PC1 = 23
    */

    printf_init();
    const uint8_t input_mask = 0x3;
    const uint8_t output_mask = 0x3;

    DDRA = ~input_mask;
    DDRC = output_mask;

    PORTA = input_mask;  // Enabling pull-up on input
    PORTC = output_mask; // Setting all ports to 5V

    int curr_value = PINA;

    int row_number = 0;

    while (1)
    {
        if (row_number == 0)
        {
            PORTC &= ~0x1;   //Outputting 0v to PC0
            _delay_us(100);
            curr_value = PINA;
            //TODO
            #ifdef DEBUG 
            ("PIN<A> value on row 0 = %02x\n", ~curr_value);
            #endif
            if(~curr_value & 0x1 == 1){
                printf("Button 1 pressed!\n");
            } if(~curr_value & 0x2 == 1){
                printf("Button 2 pressed!\n");
            }
            PORTC = output_mask;
            row_number = 1;
        }
        else
        {   
            PORTC &= ~0x2; //Outputting 0V to PC1
            _delay_us(100);
            curr_value = PINA;
            //TODO
            #ifdef DEBUG 
            ("PIN<A> value on row 1 = %02x\n", ~curr_value);
            #endif
            if(~curr_value & 0x1 == 1){
                printf("Button 3 pressed!\n");
            } if(~curr_value & 0x2 == 1){
                printf("Button 4 pressed!\n");
            }
            PORTC = output_mask;
            row_number = 0;
        }
        _delay_ms(500);
    }

    return 0;
}