#include "types.h"
#include "memory.h"
#include "atag_priv.h"
#include "images.h"
#include "stdio.h"
#include "atag.h"
#include "common.h"

extern void u_to_hex(int x, int digits, char *s);

static void print_hex(int val)
{
   char s[]="yyyyyyyy";

   u_to_hex(val, 8, s);
   printf("%s", s);
}

void *atag_build() {
  struct memory_image image;
  struct tag *tag = (struct tag*)ATAG_BASE_ADDR;

  printf("building atags\n");
	
  tag->hdr.tag = ATAG_CORE;
  tag->hdr.size = tag_size (tag_core);
  tag->u.core.flags = 0;
  tag->u.core.pagesize = 0x00001000;
  tag->u.core.rootdev = 0x0000;
  tag = tag_next(tag);

  if (image_find(IMG_CMDLINE, &image) != NULL) {
    char *atag_cmdline = tag->u.cmdline.cmdline;

    tag->hdr.tag = ATAG_CMDLINE;
    tag->hdr.size = (sizeof(struct tag_header) + image.size + 1 + 3) >> 2;
    memcpy(atag_cmdline, image.data, image.size);
    if (atag_cmdline[image.size-1] == '\xa') {
      atag_cmdline[image.size-1] = '\0';
    } else {
      atag_cmdline[image.size] = '\0';
    }
   printf("cmdline found[%s]\n", atag_cmdline);
    tag = tag_next(tag);
  }

  tag->hdr.tag = ATAG_MBM_VERSION;
  tag->hdr.size = tag_size(tag_mbm_version);
  tag->u.mbm_version.mbm_version = 0x1234;
  tag = tag_next(tag);

  if (image_find(IMG_MOTFLATTREE, &image) != NULL) {
    tag->hdr.tag = ATAG_FLAT_DEV_TREE_ADDRESS;
    tag->hdr.size = tag_size (tag_flat_dev_tree_address);
    tag->u.flat_dev_tree_address.flat_dev_tree_address = (u32)image.data;
    tag->u.flat_dev_tree_address.flat_dev_tree_size = (u32)image.size;
    tag = tag_next(tag);
    printf("flattree found. address[0x");
    print_hex((u32)image.data);
    printf("], size[%d]\n", (u32)image.size);
  }

  if (image_find(IMG_INITRAMFS, &image) != NULL) {
    tag->hdr.tag = ATAG_INITRD2;
    tag->hdr.size = tag_size(tag_initrd);
    tag->u.initrd.start = (u32)image.data;
    tag->u.initrd.size = (u32)image.size;
    tag = tag_next(tag);
    printf("initramfs found. address[0x");
    print_hex((u32)image.data);
    printf("], size[%d]\n", (u32)image.size);
  }

  tag->hdr.tag = ATAG_NONE;
  tag->hdr.size = 0;
  printf("atags built. atags base addr[0x");
  print_hex(ATAG_BASE_ADDR);
  printf("]\n");
  return (void*)ATAG_BASE_ADDR;
}


