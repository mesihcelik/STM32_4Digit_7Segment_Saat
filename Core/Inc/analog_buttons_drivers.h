/*
 * analog_buttons_drivers.h
 *
 *  Created on: 22 Ağu 2022
 *      Author: mesih
 */

#ifndef INC_ANALOG_BUTTONS_DRIVERS_H_
#define INC_ANALOG_BUTTONS_DRIVERS_H_

void rcc_clocks_enable(void);
void NVICS_Init(void);
void PC5_Button_Driver_init(void);
void PC6_Button_Driver_init(void);
void PC8_Button_Driver_init(void);
void PC9_Button_Driver_init(void);
void PA11_Button_Driver_init(void);
void PC13_Button_Driver_init(void);
void EXTI9_5_IRQHandler(void);
int flag_PC5(void);
int flag_PC6(void);
int flag_PC8(void);
void flag_PC8_a(int a);
int flag_PC9(void);
int flag_PA11(void);
int flag_PC13(void);

void flag_PC5_reset(void);
void flag_PC8_reset(void);

void switch_leftright_reset(void);

int flag_sa_sn(void);


int switch_leftright(void);
int dg0to9ch(int c10);
int dg0to5ch(int c6);
int dg0to22ch(int c23);

#endif /* INC_ANALOG_BUTTONS_DRIVERS_H_ */
