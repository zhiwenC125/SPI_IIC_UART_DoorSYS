#include "stm32f1xx_hal.h"
void led1_on(void);
void led1_off(void);
void led1_toggle(void);
void led2_on(void);
void led2_off(void);
void led2_toggle(void);

//初始化GPIO函数
void led_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //打开时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();                           // 使能GPIOB时钟
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;          // 两个LED对应的引脚
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             // 推挽输出
    gpio_initstruct.Pull = GPIO_PULLUP;                     // 上拉
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           // 高速
    HAL_GPIO_Init(GPIOB, &gpio_initstruct);
    //关闭LED
    led1_off();
    led2_off();
}

//点亮LED1的函数
void led1_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);   // 拉低LED1引脚，点亮LED1
}

//熄灭LED1的函数
void led1_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);     // 拉高LED1引脚，熄灭LED1
}

//翻转LED1状态的函数
void led1_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
}

//点亮LED2的函数
void led2_on(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);   // 拉低LED2引脚，点亮LED2
}

//熄灭LED2的函数
void led2_off(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);     // 拉高LED2引脚，熄灭LED2
}

//翻转LED2状态的函数
void led2_toggle(void)
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
}
