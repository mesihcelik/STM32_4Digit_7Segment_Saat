/*
 * timer6_driver.h
 *
 *  Created on: 13 Ağu 2022
 *      Author: mesih
 */

#ifndef INC_TIMER6_DRIVER_H_
#define INC_TIMER6_DRIVER_H_

#include <stdint.h>

void timer6_init(void);                         //Timer başlangıç ayarı fonksiyonu
uint16_t timer6_get_counter_value(void);        //Timerin o anki counter değerini okuyan fonksiyon
void timer6_enable(void);                       //Timer i açan ve döndüren fonk.
void timer6_disable(void);                      //Timer i kapatan fonk.
void TIM6_DAC_IRQHandler(void);
void s_n_cal(void);
void te_hu_sensor(void);

#endif /* INC_TIMER6_DRIVER_H_ */
