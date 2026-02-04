#include "stm32f1xx_hal.h"

// 静态变量，保存 CPU 的频率 (Hz)
static uint32_t fac_us = 0;

/**
  * @brief  初始化 DWT 计数器
  * @note   在使用 Delay_us 之前必须在 main 中调用一次
  */
void Delay_Init(void){
	// 1. 获取系统时钟频率 (STM32F1 通常是 72000000 => 72MHz)
	uint32_t sysclk = HAL_RCC_GetHCLKFreq();
	// 2. 计算 1 微秒需要的时钟周期数 (72MHz 下，1us = 72 个周期)
	fac_us = sysclk / 1000000;
	// 3. 开启 DWT 外设
    // DEMCR: Debug Exception and Monitor Control Register
    // 这一步是解开 DWT 的“封印”
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 开启TRC
	// 4. 清空计数器 CYCCNT
	DWT->CYCCNT = 0;
	// 5. 启动计数器
	DWT->CTRL |= DWT_CTRL_CPIEVTENA_Msk; // 开始计数
}
/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	// 1. 记录刚进来的时间点 (快照)
	uint32_t start_tick = DWT->CYCCNT;
	// 2. 计算目标需要经过多少个时钟周期
	uint32_t target_ticks = xus*fac_us;
	// 3. 循环等待，直到当前时间减去开始时间超过目标值
    // 利用 uint32_t 的溢出特性，即使 CYCCNT 溢出也能正确计算差值
	while((DWT->CYCCNT - start_tick) < target_ticks);
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
