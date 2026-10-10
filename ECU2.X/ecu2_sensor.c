#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "digital_keypad.h"


volatile IndicatorStatus cur_ind_status = e_ind_off;
volatile IndicatorStatus prev_ind_status = e_ind_off;
volatile unsigned char led_state = LED_OFF;


/* Read RPM from potentiometer */
uint32_t get_rpm()
{
    //Implement the rpm function
    uint32_t adc_value;
    
    // Read ADC value
    adc_value = read_adc(RPM_ADC_CHANNEL);
    
    
    /* Convert 0-1023 ADC to 0-8000 RPM */
    return (adc_value * 6000) / 1023;
}

//uint16_t get_engine_temp()
//{
//    //Implement the engine temperature function
//    uint16_t adc_value;
//    
//    adc_value = read_adc(ENG_TEMP_ADC_CHANNEL);
//    
//    return (adc_value * 120) / 1023;
//}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    
    unsigned char key;
    
    // Read keypad
    key = read_digital_keypad(STATE_CHANGE);
    
    // Check pressed switch
    switch(key)
    {
        case SWITCH1:
            cur_ind_status = e_ind_left;
            break;
        
        case SWITCH2:
            cur_ind_status = e_ind_right;
            break;
            
        case SWITCH3:
            cur_ind_status = e_ind_hazard;
            break;
            
        case SWITCH4:
            cur_ind_status = e_ind_off;
            break; 
            
        default:
            break;
    }
    return cur_ind_status;
}
