/*
 * 4Digit_Driver.h
 *
 *  Created on: Aug 13, 2022
 *      Author: mesih
 */

#ifndef INC_4DIGIT_DRIVER_H_
#define INC_4DIGIT_DRIVER_H_
#include "stm32l4xx_hal.h"

void TM1637_Init(void);
void TM1637_Demo(void);
void TM1637_DisplayDecimal_Saat(int v, int displaySeparator);
void TM1637_DisplayDecimal_Ayar(int sa2,int sa1,int dk2,int dk1, int displaySeparator);
void TM1637_SetBrightness(char brightness);
void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_ReadResult(void);
void TM1637_WriteByte(unsigned char b);
void TM1637_DelayUsec(unsigned int i);
void TM1637_ClkHigh(void);
void TM1637_ClkLow(void);
void TM1637_DataHigh(void);
void TM1637_DATALow(void);


#endif /* INC_4DIGIT_DRIVER_H_ */
