#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "HAL_SPI_SIM.h"
#include "LTC68041.h"
#include "timer.h"
#include "Balance.h"
#include <stdio.h>
// STM32+XL8812
// 2024.06.19 finish
// 裸机主动均衡器

int main(void)
{
	delay_init();
	uart_init(115200);
	HAL_SPI_SIM_Init();
	LTC6804_initialize();
	TIM_Int_Init0();
	TIM_PWM_Init00(9, 287);
	while (1)
	{
		ADC_V(); // AFE 电压采集
		if (FLAG == 0)//未连接电池，不进行均衡策略判断，MOSFET保持关断。接通电池后，延时5S，FLAG置0。
		{
			Balance_Methord(B);			// 根据采集电压，执行均衡策略
			//Battery_Select(Vdiff, max); // 控制相应MOSFET，进行单体放电
			Battery_Select(1, 1); // 控制相应MOSFET，进行单体放电
		}
	}
}
