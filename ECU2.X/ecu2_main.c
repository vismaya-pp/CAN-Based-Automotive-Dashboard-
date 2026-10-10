/*
 * ECU2 ? Engine & Indicator ECU
 * File:   ecu2_main.c
 * AUTHOR      : VISMAYA PP
 * ROLL NUMBER :25044_041
 * DESCRIPTION :Reads engine RPM through the ADC and detects left, right, hazard, and OFF 
               indicator commands using the digital keypad. It transmits RPM and Indicator
               status through the CAN bus.
 
 * Created on July 3, 2026, 8:31 AM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"

void init_config(void)
{
    // Initialize ADC
    init_adc();
    
    // Initialize digital keypad
    init_digital_keypad();
    
    // Initialize UART
    init_uart();
    
    // Configure indicator LEDs
    TRISB0 = 0;
    TRISB7 = 0;
    
    RB0 = 0;
    RB7 = 0;
    
    // Initialize CAN
    init_can();
    
}
volatile unsigned char led_state = LED_OFF;
int main(void)
{
    //call the functions
    uint32_t rpm;
    //uint16_t temp;
    IndicatorStatus indicator;
    
    // Initialize peripherals
    init_config();
    
    while(1)
    {
        // Read RPM
        rpm = get_rpm();
        
        // Transmit RPM through CAN
        can_transmit(RPM_MSG_ID, (uint8_t *)&rpm, 4);
        
        __delay_ms(10);
        
        //temp = get_engine_temp();
       // can_transmit(ENG_TEMP_MSG_ID, (uint8_t *)&temp, 2);
        
        // Read indicator switch
        indicator = process_indicator();
        
        // Transmit indicator status through CAN
        can_transmit(INDICATOR_MSG_ID, (uint8_t *)&indicator, 1);
        
        __delay_ms(10);
        
        // Display RPM on UART
        puts("\r\n-------------------------\r\n");

        puts("RPM : ");
        
        if(rpm >= 1000)
            putch((rpm / 1000) + '0');

        if(rpm >= 100)
            putch(((rpm / 100) % 10) + '0');

        if(rpm >= 10)
            putch(((rpm / 10) % 10) + '0');

        putch((rpm % 10) + '0');

        puts("\r\n");
        
        // Display indicator status
        puts("Indicator : ");
        
        switch(indicator)
        {
            
            case e_ind_left:
                
                RB0 = 0X01; // Toggle RB0
                RB7 = 0X00;  // Keep RB7 OFF
                puts("LEFT");
                
               
                
                break;
            
            case e_ind_right:
                
                RB0 = 0X00; // Toggle RB7
                RB7 = 0X01;   // Keep RB0 OFF
               
                puts("RIGHT");
                              
                
                
                break;
            
            case e_ind_hazard:
                               
                RB0 = 0X01; 
                RB7 = 0X01;  // Toggle RB7 and RB0
                
               puts("HAZARD");
                
                
                break;
                
            default:
              
                RB0 = 0X00; 
                RB7 = 0X00;  // Keep both OFF
                puts("STOP");
                break;
                
                
            
        }
        
      __delay_ms(50); 
        
    }
    
   
   
}
