#include "stm32f1xx_hal.h"                  // Device header
#include "Delay.h"
uint8_t keyValue = 0;

void Keyboard_Init(void){
	__HAL_RCC_GPIOB_CLK_ENABLE(); // GPIOB时钟开启
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_14;
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_12 |GPIO_PIN_13;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 中断优先设置
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
	HAL_NVIC_SetPriority(EXTI1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// 中断服务函数

void EXTI0_IRQHandler(void){
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void EXTI1_IRQHandler(void){
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

//void EXTI2_IRQHandler(void){
//	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
//}

void EXTI15_10_IRQHandler(void){
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
}

// 回调函数，触发中断然后调用回调，要判断引脚判断
// 哪个触发中断

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t row = 0, column = 0;
	if(keyValue != 0) return;
    const uint16_t ROW_PINS[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_14, GPIO_PIN_10};
    const uint8_t ROW_VALUES[] = {0x10, 0x20, 0x30, 0x40};
	for (uint8_t i = 0; i < 4; i++){
		if(GPIO_Pin == ROW_PINS[i]){
			row = ROW_VALUES[i];
		}
	}
    
    //确定列
	const uint16_t PIN_Array[3] = {GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13};
	const uint8_t COLUMN_Array[3] = {0x01, 0x02, 0x03};
	for(uint8_t i = 0; i < 3; i++){
		if(HAL_GPIO_ReadPin(GPIOB, PIN_Array[i]) == GPIO_PIN_SET)
		{
			Delay_us(10);
			while(HAL_GPIO_ReadPin(GPIOB, PIN_Array[i]))
				column = COLUMN_Array[i];
		}
	}
    if(row != 0 && column != 0)
        keyValue = row | column;
}


uint8_t keyboard_GetValue(void){
	uint16_t ch = 0;
	if (keyValue != 0){
		switch(keyValue){
			// 第一行
			case 0x11: ch = '1'; break;
			case 0x12: ch = '2'; break;
			case 0x13: ch = '3'; break;
			// 第二行
			case 0x21: ch = '4'; break;
			case 0x22: ch = '5'; break;
			case 0x23: ch = '6'; break;
			// 第三行
			case 0x31: ch = '7'; break;
			case 0x32: ch = '8'; break;
			case 0x33: ch = '9'; break;
			// 第四行
			case 0x41: ch = '*'; break;
			case 0x42: ch = '0'; break;
			case 0x43: ch = '#'; break;
			
			default: ch = 0; break;
		}
		keyValue = 0x00;
	}
	return ch;
}
