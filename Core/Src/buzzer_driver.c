/*
 * buzzer_driver.c
 *
 *  Created on: 29 Ağu 2022
 *      Author: mesih
 */
#include "stm32l4xx_hal.h"         //main.h dosyasından kopya çektik(orda tanımlanmış. Hal kütüphanesini tanımlıyoruz.

void buzzerdriver_init(void)          //başlangıç fonksiyonu
{

	RCC->AHB2ENR|=(1<<0);

	GPIOA->MODER|= (1<<2);
	GPIOA->MODER&= ~(1<<3);

	GPIOA->OTYPER&= ~(1<<1);

	GPIOA->OSPEEDR|= (1<<2);
	GPIOA->OSPEEDR&= ~(1<<3);

	GPIOA->PUPDR   &= ~(1<<2);
    GPIOA->PUPDR   &= ~(1<<3);
	}
void buzzer_on(void)            //Buzzer aktif
{
	GPIOA->ODR |= (1<<1);
	}
void buzzer_off(void)           //Buzzer Pasif
{
	GPIOA->ODR &= ~(1<<1);
	}


