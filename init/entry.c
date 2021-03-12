#include "x86.h"
#include "console.h"


int kern_entry()
{
	
	cons_init();

	int color = rc_green << 8;
	cons_putc(color | 'H');	
	cons_putc(color | 'E');
	cons_putc(color | 'L');
	cons_putc(color | 'L');
	cons_putc(color | 'O');
	cons_putc(color | ' ');
	cons_putc(color | 'O');
	cons_putc(color | 'S');
	cons_putc(color | ' ');
	cons_putc(color | 'K');
	cons_putc(color | 'E');
	cons_putc(color | 'R');
	cons_putc(color | 'N');
	cons_putc(color | 'E');
	cons_putc(color | 'L');
	cons_putc(color | '\n');

	return 0;
}
