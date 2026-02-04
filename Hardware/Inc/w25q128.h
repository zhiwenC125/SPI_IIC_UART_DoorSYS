#ifndef __W25Q128_H__
#define __W25Q128_H__

#include "stm32f1xx_hal.h"

#define W25Q128_CS(x)   do{ x ? \
                                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET): \
                                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); \
                        }while(0)

/* ָ��� */
#define FLASH_ManufactDeviceID                  0x90
#define FLASH_WriteEnable                       0x06
#define FLASH_ReadStatusReg1                    0x05
#define FLASH_ReadData                          0x03
#define FLASH_PageProgram                       0x02
#define FLASH_SectorErase                       0x20
#define FLASH_DummyByte                         0xFF
						
//// 控制SS电平高低输出
//#define W25Q128_CS_ENABLE()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
//#define W25Q128_CS_DISABLE()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
						
void w25q128_init(void);
uint16_t w25q128_read_id(void);
void w25q128_read_data(uint32_t address, uint8_t *data, uint32_t size);
void w25q128_write_page(uint32_t address, uint8_t *data, uint16_t size);
void w25q128_erase_sector(uint32_t address);

#endif
