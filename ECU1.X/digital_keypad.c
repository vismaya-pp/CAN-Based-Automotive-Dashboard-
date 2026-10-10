#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    // Configure keypad pins as input
	TRISC = TRISC | INPUT_PINS;
}

unsigned char read_digital_keypad(unsigned char detection_type)
{
	static unsigned char once = 1;

    // Check for state-change detection
	if (detection_type == STATE_CHANGE)
	{
        // Check whether a key is pressed
		if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)
		{
			once = 0;

            // Return the pressed key
			return (KEY_PORT & INPUT_PINS);
		}
        // Reset once when key is released
		else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)
		{
			once = 1;
		}
	}
    // Check for level detection
	else if (detection_type == LEVEL)
	{
        // Return current keypad state
		return (KEY_PORT & INPUT_PINS);
	}

    // No key pressed
	return 0xFF;
}
