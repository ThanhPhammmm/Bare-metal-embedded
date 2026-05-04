ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx):ORIGIN =0x08000000, LENGTH =1024K
    SRAM1(rwx):ORIGIN =0x20000000, LENGTH =112K
    SRAM2(rwx):ORIGIN =0x20000000+112K, LENGTH =16K
    SRAM(rwx):ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector_table)
        *(.text)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    }> FLASH

    .data :
    {
        _sdata = .;
        *(.data)
        *(.data*)
        *(.dma_buffer)
        *(.ccmram)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    }> SRAM
}