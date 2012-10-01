#include "types.h"
#include "stdio.h"
#include "error.h"
#include "atag.h"
#include "common.h"
#include "memory.h"
#include "hw_misc.h"
#include "images.h"

#define ARCH_NUMBER 2241

void critical_error(error_t err) {
   printf("Critical error %d\n", (int)err);
   while (1);
}

void __attribute__((__naked__)) enter_kernel(int zero, int arch, int *atags, int kern_addr) {
    __asm__ volatile (
        "bx r3\n"
    );
}


int main() {
  struct memory_image image;
  void *p;
  printf("milestone 2 loader\n");

  image_complete();

  image_dump_stats();
  write32(2, 0x48200010);
  while(!(read32(0x48200014)&1));

  if (image_find(IMG_LINUX, &image) != NULL) 
  {
      printf("ARCH_NUBMBER[%d], KERNEL_DEST[%d]\n", ARCH_NUMBER, KERNEL_DEST);

      enter_kernel(0, ARCH_NUMBER, atag_build(), KERNEL_DEST);
  } else 
  {
      critical_error(IMG_NOT_PROVIDED);
  }

  return 0;
}
