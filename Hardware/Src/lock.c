#include "lock.h"

//初始化GPIO函数
void lock_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();                           // 使能GPIOB时钟
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_7;                       // 继电器对应的引脚
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             // 推挽输出
    gpio_initstruct.Pull = GPIO_PULLUP;                     // 上拉
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           // 高速
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //关闭LED
    lock_off();
}

//闭合继电器的函数
void lock_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);   // 拉低LED1引脚，点亮LED1
}

//松开继电器的函数
void lock_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);     // 拉高LED1引脚，熄灭LED1
}

//获取继电器状态的函数
uint8_t lock_status_get(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
}
