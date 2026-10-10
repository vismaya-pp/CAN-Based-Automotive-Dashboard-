
#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"
//#include "uart.h"
 

volatile unsigned char led_state = LED_OFF;
unsigned char ind = e_ind_off;
//unsigned char *ind_arr[4] = {"OFF", "<--", "-->", "<->"};


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
     // Check data length
    if(len != 2)
        return;

    // Display 
    clcd_putch(data[0], LINE2(0));
    clcd_putch(data[1], LINE2(1));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{     
    //Implement the gear function
     // Check data length
   if(len != 1)
        return;

   // Display gear
    clcd_putch(data[0], LINE2(4));
  
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    uint32_t rpm;

    // Check data length
    if(len != 4)
        return;

    rpm = ((uint32_t)data[0]) |
          ((uint32_t)data[1] << 8) |
          ((uint32_t)data[2] << 16) |
          ((uint32_t)data[3] << 24);

clcd_putch((unsigned char)((rpm / 1000) % 10) + '0', LINE2(8));  // Display thousands
clcd_putch((unsigned char)((rpm / 100) % 10) + '0', LINE2(9));  // Display hundreds
clcd_putch((unsigned char)((rpm / 10) % 10) + '0', LINE2(10));  // Display tens
clcd_putch((unsigned char)(rpm % 10) + '0', LINE2(11));         // Display ones

} 

void handle_indicator_data(uint8_t *data, uint8_t len) 
{  
//    if(len != 1)
//        return;
//
//    if(data[0] > 3)
//        return;
//
//    ind = data[0];
//
//    clcd_print(ind_arr[ind], LINE2(13));
//  
    
    // Check data length
    if(len != 1)
        return;

    // Check indicator value
    if(data[0] > e_ind_hazard)
        return;


   // Update indicator state
    ind = data[0];


    // Check OFF state
    if(ind == e_ind_off)
    {
        clcd_print("OFF", LINE2(13));
    }
    // Check left state
    else if(ind == e_ind_left)
    {
        clcd_print("<--", LINE2(13));
    }
    // Check right state
    else if(ind == e_ind_right)
    {
        clcd_print("-->", LINE2(13));
    }
    // Check hazard state
    else if(ind == e_ind_hazard)
    {
        clcd_print("<->", LINE2(13));
    }
}

void indicator_blink()
{   
    static unsigned char flag = 0;

    // Check OFF state
    if(ind == e_ind_off)
    {
        RIGHT_IND_OFF();
        LEFT_IND_OFF();
        flag =0;
    }
    // Check left indicator
    else if(ind == e_ind_left)
    {
        if(flag == 0)
        {
            flag = 1;
            LEFT_IND_ON();
            RIGHT_IND_OFF();
        }
        else
        {
            flag = 0;
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }
    }
    // Check right indicator
    else if(ind == e_ind_right)
    {
        if(flag == 0)
        {
            flag = 1;
            RIGHT_IND_ON();
            LEFT_IND_OFF();
        }
        else
        {
            flag = 0;
            RIGHT_IND_OFF();
            LEFT_IND_OFF();
        }
    }
    // Check hazard state
    else if(ind == e_ind_hazard)
    {
        if(flag == 0)
        {
            flag = 1;
            LEFT_IND_ON();
            RIGHT_IND_ON();
        }
        else
        {
            flag = 0;
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
        }
    }
    
}

void process_canbus_data(void) 
{   
    //process the CAN bus data
    uint16_t msg_id;
    uint8_t data[8];
    uint8_t len;
    
    // Receive CAN message
    can_receive(&msg_id, data, &len);
    
   if(len == 0)
        return;

    // Check message ID
    switch(msg_id)
    {
        // Speed message
        case SPEED_MSG_ID:
            handle_speed_data(data, len);
            break;

            // Gear message
        case GEAR_MSG_ID:
            handle_gear_data(data, len);
            break;

            // RPM message
        case RPM_MSG_ID:
            handle_rpm_data(data, len);
            break;

            // Indicator message
        case INDICATOR_MSG_ID:
            handle_indicator_data(data, len);
            break;

        default:
            break;
    }
}
