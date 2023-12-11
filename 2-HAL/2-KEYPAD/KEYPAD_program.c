/**************************************************************************/
/*******************    Author : Mohamed ali saber   **********************/
/*******************    Layer  : HAL                 **********************/
/*******************    Component: KEYPAD              **********************/
/*******************    version : 1.00               **********************/
/*******************    date : 27/11/2023            **********************/
/**************************************************************************/

#include "STD_TYPES.h" //first include ever
/*here we are in HAL so we include files from MCAL*/

/* but we don't include PORT because the main only will include it*/

/* we include the interface file only*/

#include "DIO_interface.h"

/*then we include our component files*/

#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"

u8 KEYPAD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey = KEYPAD_NO_PRESSED_KEY;
	u8 Local_u8KEYPADArr[ROW_NUMBER][COLUMN_NUMBER] = KEYPAD_ARR_VALUES;
	u8 Local_u8ColumnIndix = 0;
	u8 Local_u8RowIndix = 0;
	u8 Local_u8ColumnArr[COLUMN_NUMBER] = {KEYPAD_COLUMN0_PIN,KEYPAD_COLUMN1_PIN,KEYPAD_COLUMN2_PIN,KEYPAD_COLUMN3_PIN};
	u8 Local_u8RowArr[ROW_NUMBER] = {KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};

	for(Local_u8ColumnIndix = 0; Local_u8ColumnIndix < COLUMN_NUMBER; Local_u8ColumnIndix++)
	{
		/*first step to activate current coulums*/
		DIO_u8SetPinValue(KEYPAD_PORT, )

	}

	return Local_u8PressedKey;
}
