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
        *(.text.*)
        *(.rodata)
        *(.rodata*)
        *(.rodata.*)
        . = ALIGN(4);
        _etext = .;
    }> FLASH

    _la_data = LOADADDR(.data);
    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        *(.data*)
        *(.dma_buffer)
        *(.ccmram)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
        . = ALIGN(4);
        end = .;
    }> SRAM
}