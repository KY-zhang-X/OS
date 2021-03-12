#include <x86.h>
#include <string.h>
#include <console.h>

/***** Serial I/O code *****/
#define COM1            0x3F8

#define COM_RX          0       // In:  Receive buffer (DLAB=0)
#define COM_TX          0       // Out: Transmit buffer (DLAB=0)
#define COM_DLL         0       // Out: Divisor Latch Low (DLAB=1)
#define COM_DLM         1       // Out: Divisor Latch High (DLAB=1)
#define COM_IER         1       // Out: Interrupt Enable Register
#define COM_IER_RDI     0x01    // Enable receiver data interrupt
#define COM_IIR         2       // In:  Interrupt ID Register
#define COM_FCR         2       // Out: FIFO Control Register
#define COM_LCR         3       // Out: Line Control Register
#define COM_LCR_DLAB    0x80    // Divisor latch access bit
#define COM_LCR_WLEN8   0x03    // Wordlength: 8 bits
#define COM_MCR         4       // Out: Modem Control Register
#define COM_MCR_RTS     0x02    // RTS complement
#define COM_MCR_DTR     0x01    // DTR complement
#define COM_MCR_OUT2    0x08    // Out2 complement
#define COM_LSR         5       // In:  Line Status Register
#define COM_LSR_DATA    0x01    // Data available
#define COM_LSR_TXRDY   0x20    // Transmit buffer avail
#define COM_LSR_TSRE    0x40    // Transmitter off

#define MONO_BASE       0x3B4
#define MONO_BUF        0xB0000
#define CGA_BASE        0x3D4
#define CGA_BUF         0xB8000
#define CRT_ROWS        25
#define CRT_COLS        80
#define CRT_SIZE        (CRT_ROWS * CRT_COLS)

#define _CUR_HIGH	0x0E
#define _CUR_LOW	0x0F

#define LPTPORT         0x378

static uint16_t addr_6845;
static uint16_t *crt_buf;
static uint16_t crt_pos;

static void cga_init(void)
{
	volatile uint16_t *cp = (uint16_t *)CGA_BUF;
	uint16_t cp_save = *cp;
	*cp = (uint16_t)0x5AA5;
	if (*cp != 0x5AA5) {
		cp = (uint16_t*)MONO_BUF;
		addr_6845 = MONO_BASE;
	}
	else {
		*cp = cp_save;
		addr_6845 = CGA_BASE;
	}

	uint32_t pos;
	outb(addr_6845, _CUR_HIGH);
	pos = inb(addr_6845 + 1) << 8;
	outb(addr_6845, _CUR_LOW);
	pos |= inb(addr_6845 + 1);

	crt_buf = (uint16_t*) cp;
	crt_pos  = pos;
}

static void cga_putc(int c)
{
	if (!(c & ~0xFF)) {
		c |= 0x0700;
	}

	switch (c & 0xFF) {
	case '\b':
		if (crt_pos > 0) {
			crt_pos --;
			crt_buf[crt_pos] = (c & ~0xFF) | ' ';
		}
		break;
	case '\n':
		crt_pos += CRT_COLS;
	case '\r':
		crt_pos -= (crt_pos % CRT_COLS);
		break;
	default:
		crt_buf[crt_pos ++] = c;
		break;
	}

	if (crt_pos >= CRT_SIZE) {
		int i;
		memmove(crt_buf, crt_buf + CRT_COLS, (CRT_SIZE - CRT_COLS) * sizeof(uint16_t));
		for (i = CRT_SIZE - CRT_COLS; i < CRT_SIZE; i ++) {
			crt_buf[i] = 0x0700 | ' ';
		}
		crt_pos -= CRT_COLS;
	}

	outb(addr_6845, _CUR_HIGH);
	outb(addr_6845 + 1, (crt_pos >> 8) & 0xFF);
	outb(addr_6845, _CUR_LOW);
	outb(addr_6845 + 1, crt_pos & 0xFF);
}





void cons_init(void)
{
	cga_init();
}

void cons_putc(int c)
{
	cga_putc(c);
}

