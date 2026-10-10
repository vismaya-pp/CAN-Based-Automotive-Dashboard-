#include <xc.h>

#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"


/* Array containing all gear position */
char gear_array[TOTAL_GEARS] = {'GN', 'G1', 'G2', 'G3', 'G4', 'G5', 'GR', 'C'};


static unsigned char gear_count = 0;

/* Stores engine status
 * 0 -> Engine OFF
 * 1 -> Engine ON
 */
/* Read ADC value from potentiometer and convert it into speed */
uint16_t get_speed()
{
    // Implement the speed function
    
    uint16_t adc_value;
    uint16_t speed; 
    
    /* Read ADC value from  AN4 */
    adc_value = read_adc(SPEED_ADC_CHANNEL);
    
    //limit adc value
    if(adc_value > 350)
    {
        adc_value = 350;
    }
    
    speed = (adc_value * 99)/350;
    /* Convert ADC value  to speed */
    return speed;
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    unsigned char key;
    
    /* Read keypad */
    key = read_digital_keypad(STATE_CHANGE);
    
    
    /* Gear Up using SW1*/
    if(key == GEAR_UP)
    {
        /* If in Collision, return to Reverse */
        if(gear_count == TOTAL_GEARS - 1)
        {
            gear_count = TOTAL_GEARS - 2;    // R
        }
        else if(gear_count < TOTAL_GEARS - 2)
        {
            gear_count++;
        }
    }

    /* Gear Down  using SW2*/
    else if(key == GEAR_DOWN)
    {
        /* If in Collision, return to Reverse */
        if(gear_count == TOTAL_GEARS - 1)
        {
            gear_count = TOTAL_GEARS - 2;    // R
        }
        else if(gear_count > 0)
        {
            gear_count--;
        }
    }
    else if(key == COLLISION)
    {
        gear_count = TOTAL_GEARS - 1;        // C
    }

    return gear_array[gear_count];
}




