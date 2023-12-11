/**************************************************************************/
/*******************    Author : Mohamed ali saber   **********************/
/*******************    Layer  : HAL                 **********************/
/*******************    Component: CLCD              **********************/
/*******************    version : 1.00               **********************/
/*******************    date : 24/11/2023            **********************/
/**************************************************************************/

/* pre peocessor file guard*/

#ifndef CLCD_interface_H_
#define CLCD_interface_H_

void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidInit(void);
void CLCD_voidSendString(const char* Copy_pcString);
void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos);
void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8XPos, u8 Copy_u8YPos);


#endif
