#ifndef __DRIVER_CONSOLE_H
#define __DRIVER_CONSOLE_H

#include "types.h"


enum real_color {
	rc_black = 0,
	rc_blue = 1,
	rc_green = 2,
	rc_cyan = 3,
	rc_red = 4,
	rc_magenta = 5,
	rc_brown = 6,
	rc_light_grey = 7,
	rc_dark_grey = 8,
	rc_light_blue = 9,
	rc_light_green = 10,
	rc_light_cyan = 11,
	rc_light_red = 12,
	rc_light_magenta = 13,
	rc_light_brown  = 14,   // yellow
	rc_white = 15
};


void cons_init(void);
void cons_putc(int c);
int cons_getc(void);

#endif /* !__DRIVER_CONSOLE_H */
