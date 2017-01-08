MEMORY
{
	SRAM_A (rwx) : ORIGIN = 0x00000000, LENGTH = 32K
}

SECTIONS
{
	.text :
	{
		_text = .;
		KEEP(*(.bt0_head))
		KEEP(*(.bt0_start))
		*(.text*)
		*(.rodata*)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		. = ALIGN(8);
		_etext = .;
	} > SRAM_A

	.ARM : {
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
	} > SRAM_A

	__init_data = .;

	.data : AT(__init_data)
	{
		_data = .;
		*(.data*)
		. = ALIGN (8);
		_edata = .;
	} > SRAM_A

	.bss :
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(8);
		_ebss = .;
	} > SRAM_A
}
