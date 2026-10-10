/*
 * ECU1 ? Vehicle Input & Speed/Gear ECU
 * File:   ecu1_main.c
 * AUTHOR      : VISMAYA PP
 * ROLL NUMBER :25044_041
 * DESCRIPTION :Reads vehicle speed from the ADC potentiometer and gear/collision status from the 
               digital keypad. It converts the sensor values into CAN data and transmits Speed and 
               Gear messages to the dashboard ECU.
 
 * Created on July 2, 2026, 9:07 AM
 */

#include <xc.h>
#define _XTAL_FREQ 20000000

#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"


void init_config(void)
{
    /* Initialize ADC module */
    init_adc();

    /* Initialize digital keypad */
    init_digital_keypad();

    /* Initialize UART */
    init_uart();

    /* Initialize CAN */
    init_can();
}


void main()
{
    uint16_t speed;
    char gear;

    char speed_data[3];
    char gear_data[2];


    init_config();


    while(1)
    {

        /* Read vehicle speed */
        speed = get_speed();


        /*
         * Convert speed into ASCII
         * Example:
         * speed = 45
         * speed_data = {'4','5','\0'}
         */

        speed_data[0] = (speed / 10) + '0';
        speed_data[1] = (speed % 10) + '0';
        speed_data[2] = '\0';



        /* Read gear position */
        gear = get_gear_pos();


        /*
         * Convert gear into ASCII
         * Example:
         * gear = '3'
         */

        gear_data[0] = gear;
        gear_data[1] = '\0';



        /* CAN transmit speed */

        can_transmit(SPEED_MSG_ID,
                     (uint8_t *)speed_data,
                     2);

        __delay_ms(10);



        /* CAN transmit gear */

        can_transmit(GEAR_MSG_ID,
                     (uint8_t *)gear_data,
                     1);

        __delay_ms(10);



        /* UART Debug */
       // Display speed on UART
        puts("Speed : ");

        putch(speed_data[0]);
        putch(speed_data[1]);

        puts(" Km/h\r\n");

        // Display collision or gear status
        if(gear == 'C')
        {
            puts("Collision : DETECTED\r\n");
        }
        else
        {
            puts("Gear : ");
            putch(gear);
            puts("\r\n");
        }


        puts("----------------------\r\n");


        __delay_ms(100);

    }

    
}