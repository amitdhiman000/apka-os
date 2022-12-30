ENTRY(loader)
OUTPUT ("kernel.bin")

phys = 0x000100000;
SECTIONS
{
	.__mbHeader phys : AT(phys) {
		mbheader = .;
		*(.__mbHeader)
		. = ALIGN(0x1000);
	}
	
	.text :
	{
		code = .;
		*(.text)
		*(.rodata)
		. = ALIGN(0x1000);
	}
	
	.data :
	{
		data = .;
		*(.data)
		. = ALIGN(0x1000);
	}
	
	.bss :
	{
		bss = .;
		*(.bss)
		. = ALIGN(0x1000);
	}
	end = .;
}
