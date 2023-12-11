/**************************************************************************/
/*******************    Author : Mohammed Ali Saber   **********************/
/*******************    Layer  : HAL                 **********************/
/*******************    Component: CLCD              **********************/
/*******************    version : 1.00               **********************/
/*******************    date : 24/11/2023            **********************/
/**************************************************************************/

#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h" // i include only this file
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*
	 send command
	 //ctrl pins first \\
	  rs=> command or data
	  rw=> read or write
	  e=> active enable to read data
	  1-set rs to low to select command
	  2-r\w => write
	  3- data => command to the eight pins
	  4-enable pulse for 2 milli seconds
	 */
	/*set rs to low*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/*set rw pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/* set command to the eight pins for data through set port function*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*set rs to HIGH for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);

	/*set rw pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/* set Data to the eight pins for data through set port function*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);

}

/*send string function*/
void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}

}

void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8Address=0;

	/*if x ==0 we target the first line*/
	if(Copy_u8XPos == 0)
	{
		Local_u8Address=Copy_u8YPos;
	}

	/*if x ==1 we target the second line*/
	else if(Copy_u8XPos == 1)
	{
		Local_u8Address=Copy_u8YPos+(0x40);
	}
	/*here we added 128 because the binary address we got is 7 digits only and we need the 8th digit to be 1*/
	CLCD_voidSendCommand(Local_u8Address+128);
}


void CLCD_voidInit(void)
{
	/*wait more that 30ms */
	_delay_ms(40);

	/*Function set command */
	/*RS | R/w | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 */
	/* 0 |  0  |  0  |  0  |  1  |  1  |  N  |  F  |  X  |  X  */
	/* N => number of lines we have two choice 0 or 1 */
	/* 0 => one line //// 1=> two lines*/
	/* F => Font size we have two choice 0 or 1 */
	/* 0 => (5*8) (columns of pixels)*(Rows of pixels) smaller font*/
	/*1 => (5*11)(columns of pixels)*(Rows of pixels) bigger font  */
	/*X => don not care choose any value*/
	/*the R/s and r/w have been chosen before*/

	/*we choose two lines and 5*8 Font size */
	CLCD_voidSendCommand(0b00111100);

	/*Display(screen) on/off command */
	/*RS | R/w | DB7 | DB6 | DB5 | DB4 | DB3 | DB2 | DB1 | DB0 */
	/* 0 |  0  |  0  |  0  |  0  |  0  |  1  |  D  |  C  |  B  */
	/*D => Display enable 0=> disable & 1=> enable*/
	/*C => cursor enable 0=> disable & 1=> enable */
	/*B => blink cursor 0=> don't blink & 1=> blink*/
	/*Display(screen) on/off command & the cursor state*/
	CLCD_voidSendCommand(0b00001100);

	/*clear screen it is a fixed command */
	CLCD_voidSendCommand(0b00000001);
}



/*CGRAM => charchater gerenator ram */


void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress = 0, Local_u8Iterator;
	/*calculate the CGRAM address*/
	Local_u8CGRAMAddress = Copy_u8PatternNumber*8;

	/*Send CG ram address command to lcd , with 6 bit =1 */
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/*write the pattern to CG ram*/
	for(Local_u8Iterator=0; Local_u8Iterator<8; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/*go to the target pos*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*display the pattern */
	CLCD_voidSendData(Copy_u8PatternNumber);

}
