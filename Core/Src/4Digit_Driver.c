/*
 * 4Digit_Driver.c
 *
 *  Created on: Aug 13, 2022
 *      Author: mesih
 */
#include "4Digit_Driver.h"
#include "main.h"
#include "stm32l4xx_hal.h"

const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x39, 0x38, 0x63, 0x79, 0x40, // 8-9,     A=10,C=11,L=12,Der=13,E=14,-=15,S=5,Boş=16,H=17,u=18
    0x00, 0x76, 0x1c,
};

void TM1637_ClkHigh(void)                                 //clock bitini 1 yapan fonksiyon
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}

void TM1637_ClkLow(void)                                  //clock bitini 0 yapan fonksiyon
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
}

void TM1637_DataHigh(void)                                 //data bitini 1 yapan fonksiyon
{
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);
}

void TM1637_DataLow(void)                                 //data bitini 0 yapan fonksiyon
{
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
}

void TM1637_Demo(void)
{
	uint8_t i = 0;

	TM1637_Init();
	TM1637_SetBrightness(8);

	while(1){
		TM1637_DisplayDecimal(i++, 0);
	}
}


void TM1637_Init(void)           //io ve parlaklık tanımlamaları
{
	MX_GPIO_Init();
    TM1637_SetBrightness(8);
}


void TM1637_DisplayDecimal_Saat(int v, int displaySeparator) //Display karakter yansıma fonksiyon
{
	unsigned char digitArr[4];
	for (int i = 0; i < 4; ++i) {
			if (i == 0) {
				digitArr[i] = segmentMap[v % 10];
				v /= 10;
			} else if (i == 1) {
				digitArr[i] = segmentMap[v % 6];
				v /= 6;
			} else if (i == 2) {
				digitArr[i] = segmentMap[v % 10];
				if (displaySeparator) {
					digitArr[i] |= 1 << 7;
				}
				v /= 10;
			} else if (i == 3) {
				digitArr[i] = segmentMap[v % 6];
		}
	}

    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);
    TM1637_ReadResult();

    for (int i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}
void TM1637_DisplayDecimal_Ayar(int sa2,int sa1,int dk2,int dk1, int displaySeparator) //Display karakter yansıma fonksiyon
{
	unsigned char digitArr[4];
	for (int i = 0; i < 4; ++i) {
			if (i == 0) {
				if(switch_leftright()==1){
					if (displaySeparator)
					digitArr[i] = segmentMap[dk1];
					else
				    digitArr[i] = segmentMap[16];

				}else{
					digitArr[i] = segmentMap[dk1];
				}

			} else if (i == 1) {
				if(switch_leftright()==2){
					if (displaySeparator)
					digitArr[i] = segmentMap[dk2];
					else
				    digitArr[i] = segmentMap[16];

				}else{
					digitArr[i] = segmentMap[dk2];
				}

			} else if (i == 2) {
				if(switch_leftright()==3){
					if (displaySeparator)
					digitArr[i] = segmentMap[sa1];
					else
				    digitArr[i] = segmentMap[16];

				}else{
					digitArr[i] = segmentMap[sa1];
				}
				if (displaySeparator) {
					digitArr[i] |= 1 << 7;
				}
			} else if (i == 3) {
				if(switch_leftright()==3){
					if (displaySeparator)
					digitArr[i] = segmentMap[sa2];
					else
				    digitArr[i] = segmentMap[16];

				}else{
					digitArr[i] = segmentMap[sa2];
				}
		}
	}

    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);
    TM1637_ReadResult();

    for (int i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}

// Valid brightness values: 0 - 8.
// 0 = display off.
void TM1637_SetBrightness(char brightness)    //parlaklık ayarı fonk.
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    TM1637_Start();
    TM1637_WriteByte(0x87 + brightness);
    TM1637_ReadResult();
    TM1637_Stop();
}

void TM1637_Start(void)              //başlama fonk.
{
    TM1637_ClkHigh();                //Clock bitini high
    TM1637_DataHigh();               //data bitini high
    TM1637_DelayUsec(2);
    TM1637_DataLow();                //Data yı low a çek
}

void TM1637_Stop(void)               //CLK hig seviye olduğunda ve DIO low seviyeden high seviyeye geçtiğinde veri girişi sona erer
{
    TM1637_ClkLow();
    TM1637_DelayUsec(2);
    TM1637_DataLow();
    TM1637_DelayUsec(2);
    TM1637_ClkHigh();
    TM1637_DelayUsec(2);
    TM1637_DataHigh();
}

void TM1637_ReadResult(void)           //Okumuma fonk.
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);

    TM1637_ClkHigh();
    TM1637_DelayUsec(2);
    TM1637_ClkLow();
}

void TM1637_WriteByte(unsigned char b)         //Datayı göndermeye başlamak için
{
	for (int i = 0; i < 8; ++i) {
		TM1637_ClkLow();
		if (b & 0x01) {
			TM1637_DataHigh();
		}
		else {
			TM1637_DataLow();
		}
		TM1637_DelayUsec(3);
		b >>= 1;
		TM1637_ClkHigh();
		TM1637_DelayUsec(3);
	}
}

void TM1637_DelayUsec(unsigned int i)
{
    for (; i>0; i--) {
        for (int j = 0; j < 500; ++j) {
					__NOP();
        }
    }
}
