#include "types.h"
#include "stdio.h"
#include "string.h"
#include "error.h"
#include "common.h"


int putchar(int c) {
    int uart_base = 0x49020000;

  while ((read32(uart_base + 0x44) & 1)!=0);
  if (c =='\n') {
	write32(0x0d, uart_base + 0x00);
  	while ((read32(uart_base + 0x44) & 1)!=0);
	write32(0x0a, uart_base + 0x00);
  } else {
	write32(c, uart_base + 0x00);
  }
  return (unsigned char)c;
}

int puts(const char *s) {
  unsigned char c;

  while (c = (unsigned char)(*s++)) {
    if (putchar((int)c) == EOF) {
      return EOF;
    }
  }
  return 0;
}
