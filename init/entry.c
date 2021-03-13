#include <x86.h>
#include <console.h>
#include <stdio.h>

int kern_entry()
{
	
	cons_init();

	cprintf("HELLO OS KERNEL\n");

	while(1);
}
