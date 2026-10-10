/*
 * ECU3 ? Dashboard Display ECU
 * File:   main.c
 * AUTHOR      : VISMAYA PP
 * ROLL NUMBER :25044_041
 * DESCRIPTION :Receives CAN messages from ECU1 and ECU2 and displays Speed, Gear, RPM, and Indicator status
                on the CLCD. It also controls the left and right indicator LEDs according to the received 
                indicator command.
  
 * Created on July 7, 2026, 9:30 PM
 */





#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "timer0.h"
#include "uart.h"

static void init_leds() {
//    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
//    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
   init_clcd();
    init_can();
    
    //init_leds();

    // Enable Interrupts
   
    //init_timer0();
}

void main(void) {
    
    //init_uart();
    unsigned int delay = 0;
    // Initialize peripherals
     init_config();

    // ECU1 main loop 
    
        // Read CAN Bus data and handle it
    clcd_print("SPD", LINE1(0));
    clcd_print("GR",  LINE1(4));
    clcd_print("RPM", LINE1(8));
    clcd_print("IND", LINE1(13));

    clcd_print("00",   LINE2(0));
    clcd_putch('N',    LINE2(4));
    clcd_print("0000", LINE2(8));
    clcd_print("OFF",  LINE2(13));
        
       while(1)
    {
        process_canbus_data();

        delay++;
        if(delay >= 1000)
        {
            delay = 0;
            indicator_blink();
        }
    }
        
    
}
