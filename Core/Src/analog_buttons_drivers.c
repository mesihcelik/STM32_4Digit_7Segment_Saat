/*
 * analog_buttons_drivers.c
 *
 *  Created on: 22 Ağu 2022
 *      Author: mesih
 */
#include "stm32l4xx_hal.h"     //main.h dosyasından kopya çektik(orda tanımlanmış. Hal kütüphanesini tanımlıyoruz.

void rcc_clocks_enable(void){
	//BUTTON ==>  GPIO  - 5.Pin
	///// 1 - CLOCK SETTINGS  /////

	///Enable GPIOC Clock    (HAL kütüphanesiyle)
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	///Enable SYSCFG Clock (for EXTI)
	__HAL_RCC_SYSCFG_CLK_ENABLE();
}
void NVICS_Init(void){
    ///// 4 - NVIC SETTINGS /////         Kesmelerden sorumlu birim

    // set EXTI9_5 Priority on NVIC           Bit işlem için NVIC biriminin dosyasına bakmak gerekli pratik olsundiye CMSIS
    NVIC_SetPriority(EXTI9_5_IRQn,1);         //CMSIS kütüphanesi ile bizi ilgilendiren hattın kesmesini açtık. Önceliği 1 verdik kısıt sayıda IRQ hattı old. için 15 ile 10 arasını birbirine bağlamış tek fonksiyonda
    NVIC_SetPriority(EXTI15_10_IRQn,2);
    // Enable EXTI9_5 Interrupt on NVIC
    NVIC_EnableIRQ(EXTI9_5_IRQn);             //CMSIS kütüphanesi ile bu Interrupt'ı NVIC tarafında yetkilendiriyoruz.
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}
void PC5_Button_Driver_init(void){
	///// 2 - GPIO SETTINGS /////

	//Select Mode:Input
	GPIOC->MODER&= ~(1<<10);
	GPIOC->MODER&= ~(1<<11);

	//Pull-up Pull-down          01:pull-up
	GPIOC->PUPDR|= (1<<10);
	GPIOC->PUPDR&= ~(1<<11);

	///// 3 - EXTI_5 ==> GPIOC

	//Select EXTI_5 ==>  GPIOC                       **dizi olduğu için 4 EXTI register , mevcut EXTI 2 için EXTICR[1]  diye tanımlanıyor

    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI5_PC;    //ister stnin verdiği define değerle or'la istr


    //EXTI5 Interrupt Unmask

    EXTI->IMR1|= (1<<5);            //Maskeyi kaldır

    //EXTI13 Interrupt Falling edge

    EXTI->RTSR1 |= (1<<5);   //Düşen kenar kenar kenarın tetiklenmesi için enable durumuna getiriyoruz.
    //EXTI->FTSR1 |= EXTI_FTSR1_FT8;
}

void PC6_Button_Driver_init(void){
    //Select Mode:Input
	GPIOC->MODER&= ~(1<<12);
	GPIOC->MODER&= ~(1<<13);
	//Pull-up Pull-down          01:pull-up
	GPIOC->PUPDR|= (1<<12);
	GPIOC->PUPDR&= ~(1<<13);
    //EXTI Atama
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI6_PC;
    //EXTI5 Interrupt Unmask
    EXTI->IMR1|= (1<<6);
    //EXTI13 Interrupt Rising edge
    EXTI->RTSR1 |= (1<<6);
    //EXTI->FTSR1 |= EXTI_FTSR1_FT8;
}
void PC8_Button_Driver_init(void){
    //Select Mode:Input
	GPIOC->MODER&= ~(1<<16);
	GPIOC->MODER&= ~(1<<17);
	//Pull-up Pull-down          01:pull-up
	GPIOC->PUPDR|= (1<<16);
	GPIOC->PUPDR&= ~(1<<17);
    //EXTI Atama
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI8_PC;
    //EXTI5 Interrupt Unmask
    EXTI->IMR1|= (1<<8);
    //EXTI13 Interrupt Rising edge
    EXTI->RTSR1 |= (1<<8);
    //EXTI->FTSR1 |= EXTI_FTSR1_FT8;
}
void PC9_Button_Driver_init(void){
    //Select Mode:Input
	GPIOC->MODER&= ~(1<<18);
	GPIOC->MODER&= ~(1<<19);
	//Pull-up Pull-down          01:pull-up
	GPIOC->PUPDR|= (1<<18);
	GPIOC->PUPDR&= ~(1<<19);
    //EXTI Atama
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI9_PC;
    //EXTI5 Interrupt Unmask
    EXTI->IMR1|= (1<<9);
    //EXTI13 Interrupt Rising edge
    EXTI->RTSR1 |= (1<<9);
    //EXTI->FTSR1 |= EXTI_FTSR1_FT8;
}
void PA11_Button_Driver_init(void){
    //Select Mode:Input
	GPIOA->MODER&= ~(1<<22);
	GPIOA->MODER&= ~(1<<23);
	//Pull-up Pull-down          01:pull-up
	GPIOA->PUPDR|= (1<<22);
	GPIOA->PUPDR&= ~(1<<23);
    //EXTI Atama
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI11_PA;
    //EXTI5 Interrupt Unmask
    EXTI->IMR1|= (1<<11);
    //EXTI13 Interrupt Rising edge
    EXTI->RTSR1 |= (1<<11);
    //EXTI->FTSR1 |= EXTI_FTSR1_FT8;
}
void PC13_Button_Driver_init(void){
    //Select Mode:Input
	GPIOC->MODER&= ~(1<<26);
	GPIOC->MODER&= ~(1<<27);
	//Pull-up Pull-down          01:pull-up
	GPIOC->PUPDR|= (1<<26);
	GPIOC->PUPDR&= ~(1<<27);
    //EXTI Atama
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
    //EXTI5 Interrupt Unmask
    EXTI->IMR1|= (1<<13);
    //EXTI13 Interrupt Rising edge
    EXTI->RTSR1 |= (1<<13);
    //EXTI->FTSR1 |= EXTI_FTSR1_FT8;
}

int flagpc5 = 0, flagpc6 = 0, flagpc8 = 0, flagpc9 = 0, flagpa11 = 0, flagpc13 = 0, dgchn=0, dg0to22=0, dg22to0=0, dg0to9=0, dg9to0=0, dg0to5=0, dg5to0=0;

int flag_PC5(void){
	return flagpc5;
}
int flag_PC6(void){
	return flagpc6;
}
int flag_PC8(void){
	return flagpc8;
}
void flag_PC8_a(int a){
	flagpc8=a;
	return 0;
}
int flag_PC9(void){
	return flagpc9;
}
int flag_PA11(void){
	return flagpa11;
}
int flag_PC13(void){
	return flagpc13;
}
int dg0to9ch(int c10){   // digit deger degistir
	    if(c10<9 && dg9to0==1)
	    c10=c10+dg9to0;
	    else if(c10 == 9 && dg9to0==1)
	    c10=0;
	    else if(c10>1 && dg0to9==1)
	    c10=c10-dg0to9;
	    else if(c10<1 && dg0to9==1)
	    c10=9;

	    dg0to9=0;
	    dg9to0=0;
		return c10;
}
int dg0to5ch(int c6){   // digit deger degistir
	    if(c6<5 && dg5to0==1)
	    c6=c6+dg5to0;
	    else if(c6 == 5 && dg5to0==1)
	    c6=0;
	    else if(c6>1 && dg0to5==1)
	    c6=c6-dg0to5;
	    else if(c6<1 && dg0to5==1)
	    c6=5;

	    dg0to5=0;
	    dg5to0=0;
		return c6;
}
int dg0to22ch(int c23){   // digit deger degistir
	    if(c23<23 && dg22to0==1)
	    c23=c23+dg22to0;
	    else if(c23 == 23 && dg22to0==1)
	    c23=0;
	    else if(c23>1 && dg0to22==1)
	    c23=c23-dg0to22;
	    else if(c23<1 && dg0to22==1)
	    c23=23;

	    dg0to22=0;
	    dg22to0=0;
		return c23;
}

int switch_leftright(void){   // digit kaydir
		return dgchn;
}


void EXTI9_5_IRQHandler(void)     //Kesme gerçekleştiğinde çağrılan fonksiyon
{
	// Pending register //   Interrupt isteği geldiğinde bu registerin ilgili bite ait değer 1 olur. Bunu koşulu kullanarak IRQ hattını ortak kullanan 10 ile 15 arasındaki kesmelerden gelen bilgileri ayırt edip işeleme sokabiliriz.
	if((EXTI->PR1&EXTI_PR1_PIF5)==EXTI_PR1_PIF5)        // PR1 and 0x2000 eşitmi  0x2000 dedik
	{
		EXTI->PR1 |= EXTI_PR1_PIF5;                     // Bu komutla Pendingin ilgili bitine  1  yazarak sıfırladık

		if(flagpc5 == 0)              //sn<<>>sa gecis
		flagpc5 = 1;
	    else if(flagpc5 == 1)
	    flagpc5 = 0;
	}
	if((EXTI->PR1&EXTI_PR1_PIF8)==EXTI_PR1_PIF8)
	{
		EXTI->PR1 |= EXTI_PR1_PIF8;

		if(flagpc8 < 4)      //ayar
		flagpc8 = flagpc8+1;
	    else if(flagpc8 == 4)
	    flagpc8 = 0;
	}
	if((EXTI->PR1&EXTI_PR1_PIF6)==EXTI_PR1_PIF6)
	{
		EXTI->PR1 |= EXTI_PR1_PIF6;
		if(dg0to9 == 0)             //pc6 0-9 sayi azalt
		dg0to9 = 1;
	    else if(dg0to9 == 1)
	    dg0to9 = 0;

		if(dg0to5 == 0)             //pc6 0-5 sayi azalt
		dg0to5 = 1;
	    else if(dg0to5 == 1)
	    dg0to5 = 0;

		if(dg0to22 == 0)             //pc6 0-23 sayi azalt
		dg0to22 = 1;
	    else if(dg0to22 == 1)
	    dg0to22 = 0;

	}
	if((EXTI->PR1&EXTI_PR1_PIF9)==EXTI_PR1_PIF9)
	{
		EXTI->PR1 |= EXTI_PR1_PIF9;
		if(dgchn<3)      //saga kaydir
		dgchn = dgchn+1;
	    else if(dgchn == 3)
	    dgchn = 1;

	}
}
void EXTI15_10_IRQHandler(void)     //Kesme gerçekleştiğinde çağrılan fonksiyon
{
	if((EXTI->PR1&EXTI_PR1_PIF13)==EXTI_PR1_PIF13)
	{
		EXTI->PR1 |= EXTI_PR1_PIF13;
		if(dgchn>1)      //sola kaydir
		dgchn = dgchn-1;
	    else if(dgchn == 1||dgchn == 0)
		dgchn = 3;
	}
	if((EXTI->PR1&EXTI_PR1_PIF11)==EXTI_PR1_PIF11)
	{
		EXTI->PR1 |= EXTI_PR1_PIF11;

		if(dg9to0 == 0)             //pa11 0-9 sayi arttir
		dg9to0 = 1;
	    else if(dg9to0 == 1)
	    dg9to0 = 0;

		if(dg5to0 == 0)             //pa11 0-5 sayi arttir
		dg5to0 = 1;
	    else if(dg5to0 == 1)
	    dg5to0 = 0;

		if(dg22to0 == 0)             //pa11 0-23 sayi arttir
		dg22to0 = 1;
	    else if(dg22to0 == 1)
	    dg22to0 = 0;
	}

}
void flag_PC5_reset(void)
{
	flagpc5=0;
}
void flag_PC8_reset(void)
{
	flagpc8=0;
}
void switch_leftright_reset(void){
	dgchn=0;
}
