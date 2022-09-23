/*
 * timer6_driver.c
 *
 *  Created on: 13 Ağu 2022
 *      Author: mesih
 */

#include "stm32l4xx_hal.h"
#include "timer6_driver.h"
#include "4Digit_Driver.h"
#include "dht11.h"

DHT_DataTypedef DHT11_Data;
float Temperature, Humidity;

void timer6_init(void)             //Timer her 500 değerine geldiğinde resetlenip(update olduğunda) kesme gerçekleşecek
{
	//enable timer 6 clock
	__HAL_RCC_TIM6_CLK_ENABLE();

	//Timer clock(APB1) = 64 mhz  64000 = 1000 Hz (1 ms period)
	TIM6->PSC = 63999;               //prescaler ile periyod ayarı  (64000-1)

	//Reload in every 1000 ms         //Timer her 1000 değerine geldiğinde resetlenip başa dönecek  (1000-1) Döngü 1 sn olmuş olacak
	TIM6->ARR = 999;

	//Enable Timer Update Interrupt
	TIM6->DIER |= TIM_DIER_UIE;      //Update Interrupt Enable bitini 1 yapıyoruz

	//Enable TIM6 Interrupt on NVIC    //Timer 6 Interruptını enable ediyoruz
	NVIC_EnableIRQ(TIM6_IRQn);
    NVIC_SetPriority(TIM6_IRQn,2);     //Timer 6 Interruptının önceliği
}

//Set period (ms)
void timer6_set_period(uint16_t period)     //isteğe bağlı period belirleme fonksiyonu
{
	TIM6->ARR = period-1;
}

uint16_t timer6_get_counter_value(void)     //o anki counter değerini okuyan fonksiyon (timer in sayaç değerinin tutulduğu register)
{
	uint16_t cnt = TIM6->CNT;
	return cnt;
}

void timer6_enable(void)                //Timeri eneble yapmak için CR1 registerinde CEN bitini 1 yapan fonk.
{
	TIM6->CR1 |= TIM_CR1_CEN;
}

void timer6_disable(void)                //Timeri disable yapmak için CR1 registerinde CEN bitini 0 yapan fonk.
{
	TIM6->CR1 &= ~(TIM_CR1_CEN);
}

volatile uint8_t displayColon = 0;
volatile uint8_t displayColonde = 0;
int saniye=69780;       //int saniye=1;
int saat=0;
int alarm=86402;
int dk1=16,dk2=16,sa=0,sag=0,sol=0;
int A=10,C=11,L=12,Der=13,E=14,Tr=15,H=17,u=18,S=5;
//Timer6 Interrupt Request Handler             //startuptan handler fonksiyon ismini kopyala
void TIM6_DAC_IRQHandler(void)         //kesme gerçekleştiğinde dönecek fonsiyon
{
	TIM6->SR &= ~(TIM_SR_UIF); //Timer6 ya ait kesme bayrağını sıfırla (yoksa yeni gelen kesmeyi algılamaz)
	saat=saniye / 60;
	displayColon= !displayColon;       //tersini alma
	//SAAT-DERECE-NEM oto gecis
	if(saniye%81==68&&flag_PC8()==0)
		flag_PC8_a(5);
	if(saniye%81==70&&flag_PC8()==5)
		flag_PC8_a(0);
	if(saniye%81==78&&flag_PC8()==0)
	    flag_PC8_a(6);
	if(saniye%81==80&&flag_PC8()==6)
		flag_PC8_a(0);

	//SAAT Ana Kod
	if (flag_PC5()==0 && flag_PC8()==0) {        //sa-dk
		if (dk1!=0 || dk2!=0 || sa!=0 || switch_leftright_reset()!=0 ) {
			dk1=0;
			dk2=0;
			sa=0;
			switch_leftright_reset();
		}
		TM1637_DisplayDecimal_Saat(saat, displayColon);
	} else if (flag_PC5()==1 && flag_PC8()==0) {          //dk-sn
		if (dk1!=0 || dk2!=0 || sa!=0 || switch_leftright_reset()!=0) {
			dk1=0;
			dk2=0;
			sa=0;
			switch_leftright_reset();
			flag_PC5_reset();
			return;
		}
		TM1637_DisplayDecimal_Saat(saniye, displayColon);
	}
	saniye=saniye+1;
	if (saniye==86401)
		saniye=1;
	//Ayarlama KODU  (-SE-)
	if (flag_PC8()==1) {
		if (switch_leftright()==0) {
			TM1637_DisplayDecimal_Ayar(Tr, S, E, Tr, displayColonde);
			if (dk1!=0 || dk2!=0 || sa!=0 || switch_leftright_reset()!=0) {
				dk1=0;
				dk2=0;
				sa=0;
				switch_leftright_reset();
				return;
			}
		}
		if (switch_leftright()==1) {
			dk1=dg0to9ch(dk1);
		} else if (switch_leftright()==2) {
			dk2=dg0to5ch(dk2);
		} else if (switch_leftright()==3) {
			sa=dg0to22ch(sa);
		}
		if (flag_PC5()==1) {
			saniye=60*dk1+600*dk2+3600*sa;
			dk1=1;
			switch_leftright_reset();
			flag_PC8_reset();
		}
		if (switch_leftright()==1 || switch_leftright()==2 || switch_leftright()==3)
			TM1637_DisplayDecimal_Ayar(sa/10, sa%10, dk2, dk1, displayColon);
	}
	//ALARM KODU(-AL-)
	if (flag_PC8()==2) {
		if (switch_leftright()==0) {
			TM1637_DisplayDecimal_Ayar(Tr, A, L, Tr, displayColonde);
			if (dk1!=0 || dk2!=0 || sa!=0 || switch_leftright_reset()!=0) {
				dk1=0;
				dk2=0;
				sa=0;
				switch_leftright_reset();
				return;
			}
		}
		if (switch_leftright()==1) {
			dk1=dg0to9ch(dk1);
		} else if (switch_leftright()==2) {
			dk2=dg0to5ch(dk2);
		} else if (switch_leftright()==3) {
			sa=dg0to22ch(sa);
		}
		if (flag_PC5()==1) {
			alarm=60*dk1+600*dk2+3600*sa+1;
			dk1=1;
			switch_leftright_reset();
			flag_PC8_reset();
		}
		if (switch_leftright()==1 || switch_leftright()==2 || switch_leftright()==3)
			TM1637_DisplayDecimal_Ayar(sa/10, sa%10, dk2, dk1, displayColon);

		if (alarm < 86402 && switch_leftright()==0) { //Alarm ayarlandıktan sonra ekrana yansıtan kod
			HAL_Delay(200);
			TM1637_DisplayDecimal_Saat(alarm/60, displayColon);
		}

	}
	//Alarm Devrede
	if (saniye >= alarm && saniye <= alarm + 120) {
		buzzer_on();
		HAL_Delay(100);
		buzzer_off();
		HAL_Delay(100);
		buzzer_on();
		HAL_Delay(100);
		buzzer_off();
		if (saniye == alarm + 120 || flag_PC8() > 0) //Tuşa basarsan alarm susar ve 2 dakika kurulu sonra alarmın değerini atar.
			alarm = 86402;
	}
	//SICAKLIK(-C-)
	if (flag_PC8() == 3||flag_PC8() == 5) {
			TM1637_DisplayDecimal_Ayar((int)Temperature/10, (int)Temperature%10, C, Der, displayColonde);
	}
	//NEM(-Hu-)
	if (flag_PC8() == 4||flag_PC8() == 6) {
				TM1637_DisplayDecimal_Ayar((int)Humidity/10, (int)Humidity%10, H, u, displayColonde);
		}
}
void te_hu_sensor(void){
	DHT_GetData(&DHT11_Data);
	Temperature = DHT11_Data.Temperature;
	Humidity = DHT11_Data.Humidity;
	HAL_Delay(3000);
}


