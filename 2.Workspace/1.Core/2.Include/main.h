#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>

/* ========================================================================= */
/* 1. Base Addresses: Định nghĩa ranh giới các vùng nhớ                       */
/* ========================================================================= */
#define PERIPH_BASE         0x40000000U // Ép kiểu Unsigned
#define AHB1PERIPH_BASE     (PERIPH_BASE + 0x20000U)

#define GPIOD_BASE          (AHB1PERIPH_BASE + 0x0C00U)
#define RCC_BASE            (AHB1PERIPH_BASE + 0x3800U)

/* ========================================================================= */
/* 2. Peripheral Structs: Định nghĩa cấu trúc thanh ghi theo Data Sheet      */
/* ========================================================================= */

/**
 * @brief Cấu trúc thanh ghi điều khiển xung nhịp (RCC)
 * Phải đảm bảo khai báo đủ các thanh ghi hoặc dùng mảng đệm (padding) 
 * để AHB1ENR rơi trúng offset 0x30.
 */
typedef struct {
    volatile uint32_t CR;         // Offset: 0x00
    volatile uint32_t PLLCFGR;    // Offset: 0x04
    volatile uint32_t CFGR;       // Offset: 0x08
    volatile uint32_t CIR;        // Offset: 0x0C
    volatile uint32_t AHB1RSTR;   // Offset: 0x10
    volatile uint32_t AHB2RSTR;   // Offset: 0x14
    volatile uint32_t AHB3RSTR;   // Offset: 0x18
    uint32_t          RESERVED_0; // Offset: 0x1C (Vùng nhớ dự trữ)
    volatile uint32_t APB1RSTR;   // Offset: 0x20
    volatile uint32_t APB2RSTR;   // Offset: 0x24
    uint32_t          RESERVED_1[2]; // Offset: 0x28 - 0x2C
    volatile uint32_t AHB1ENR;    // Offset: 0x30
    // ... (Có thể định nghĩa tiếp nếu cần dùng)
} RCC_TypeDef;

/**
 * @brief Cấu trúc thanh ghi điều khiển cổng I/O (GPIO)
 */
typedef struct {
    volatile uint32_t MODER;      // Offset: 0x00
    volatile uint32_t OTYPER;     // Offset: 0x04
    volatile uint32_t OSPEEDR;    // Offset: 0x08
    volatile uint32_t PUPDR;      // Offset: 0x0C
    volatile uint32_t IDR;        // Offset: 0x10
    volatile uint32_t ODR;        // Offset: 0x14
    volatile uint32_t BSRR;       // Offset: 0x18
    volatile uint32_t LCKR;       // Offset: 0x1C
    volatile uint32_t AFR[2];     // Offset: 0x20 - 0x24 (Alternate function)
} GPIO_TypeDef;

/* ========================================================================= */
/* 3. Peripheral Pointers: Ép kiểu địa chỉ cơ sở thành con trỏ Struct        */
/* ========================================================================= */
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)

/* Bit Definitions (Tạo sẵn các macro thao tác bit cho rõ nghĩa) */
#define RCC_AHB1ENR_GPIODEN (1U << 3)
#define GPIO_MODER_MODER12  (3U << (12 * 2)) // Mask 2 bit của chân 12

/* Function prototypes */
void delay(volatile uint32_t time);

#endif // MAIN_H