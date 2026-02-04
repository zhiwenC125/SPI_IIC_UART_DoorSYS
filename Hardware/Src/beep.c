#include "stm32f1xx_hal.h"
void beep_on(void);
void beep_off(void);

//初始化GPIO函数
void beep_init(void)
{
    GPIO_InitTypeDef gpio_initstruct;
    //打开时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();                           // 使能GPIOB时钟
    
    //调用GPIO初始化函数
    gpio_initstruct.Pin = GPIO_PIN_13;                       // 蜂鸣器对应的引脚
    gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;             // 推挽输出
    gpio_initstruct.Pull = GPIO_PULLUP;                     // 上拉
    gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;           // 高速
    HAL_GPIO_Init(GPIOC, &gpio_initstruct);
    //关闭蜂鸣器
    beep_off();
}

//打开蜂鸣器的函数
void beep_on(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);   // 拉低蜂鸣器引脚，打开蜂鸣器
}

//关闭蜂鸣器的函数
void beep_off(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);     // 拉高蜂鸣器引脚，关闭蜂鸣器
}
