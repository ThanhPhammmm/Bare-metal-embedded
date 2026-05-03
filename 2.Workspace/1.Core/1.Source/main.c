#include "main.h"

/* ======================================================================= */
/* 1. .data SECTION: Biến toàn cục/static ĐÃ khởi tạo giá trị (khác 0)     */
/* Sẽ được copy từ Flash (ROM) sang RAM bởi startup code (Reset_Handler)   */
/* ======================================================================= */
uint32_t g_blink_rate = 1000000;
static uint8_t s_device_id = 0xAA;

/* ======================================================================= */
/* 2. .bss SECTION: Biến toàn cục/static CHƯA khởi tạo (hoặc gán bằng 0)   */
/* Không tốn dung lượng trên Flash, startup code sẽ tự fill 0 vào RAM      */
/* ======================================================================= */
uint32_t g_tick_count;
static uint32_t s_error_flags = 0;

/* ======================================================================= */
/* 3. .rodata SECTION (Read-Only Data): Hằng số (Constants)                */
/* Nằm chết trên Flash, không tốn RAM. Dùng cho chuỗi, bảng tra cứu (LUT)  */
/* ======================================================================= */
const uint32_t c_max_ticks = 0xFFFFFFFF;
const char c_version_string[] = "v1.0.0-baremetal";

/* ======================================================================= */
/* 4. CUSTOM SECTIONS: Ép trình biên dịch đặt data vào vùng nhớ tự định nghĩa*/
/* Rất hay dùng trong lập trình Kernel, Bootloader, hoặc DMA/CCMRAM STM32  */
/* ======================================================================= */
// Giả lập cấp phát một mảng đệm riêng cho DMA để không bị dính cache
__attribute__((section(".dma_buffer"))) uint8_t g_rx_buffer[256];

// Đặt biến vào vùng Core Coupled Memory (CCM RAM) của STM32 để truy xuất cực nhanh
__attribute__((section(".ccmram"))) uint32_t g_fast_counter = 0; 

/* ======================================================================= */
/* 5. .text SECTION: Chứa mã lệnh của chương trình (Instructions)          */
/* ======================================================================= */
void delay(volatile uint32_t time)
{
    while(time--) {
        __asm__("nop"); 
    }
}

int main(void)
{
    // Kích hoạt xung nhịp cho GPIOD
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 

    // Cấu hình chân PD12 làm Output
    GPIOD->MODER &= ~GPIO_MODER_MODER12;
    GPIOD->MODER |= (1U << (12 * 2));

    while (1)
    {
        // Tương tác với các biến để compiler không optimize (tối ưu hóa) mất chúng
        g_tick_count++;
        g_fast_counter += 2;
        
        // Cập nhật cờ lỗi giả định nếu tick quá giới hạn
        if (g_tick_count >= c_max_ticks) {
            s_error_flags = s_device_id; 
        }

        // Đảo trạng thái chân PD12
        GPIOD->ODR ^= (1U << 12);
        
        // Sử dụng biến thuộc .data làm thời gian delay
        delay(g_blink_rate);
    }
    
    return 0;
}