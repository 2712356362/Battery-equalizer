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
// �������������

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
		ADC_V(); // AFE ��ѹ�ɼ�
		if (FLAG == 0)//δ���ӵ�أ������о�������жϣ�MOSFET���ֹضϡ���ͨ��غ���ʱ5S��FLAG��0��
		{
			Balance_Methord(B);			// ���ݲɼ���ѹ��ִ�о������
			//Battery_Select(Vdiff, max); // ������ӦMOSFET�����е���ŵ�
			Battery_Select(1, 1); // ������ӦMOSFET�����е���ŵ�
		}
	}
}
