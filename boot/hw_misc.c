#include "hw_misc.h"
#include "mxc91231.h"
#include "common.h"

void reset_display()
{
    uint32_t u;

    printf("enabling clocks\n");                                                                                                                                         

    u = read32(0x48004E00);                                                                                                                                                 
    printf("clock1[%d]\n", u);                                                                                                                                          
    u = read32(0x48004E10);                                                                                                                                                 
    printf("clock2[%d]\n", u);                                                                                                                                          
    write32(0x01, 0x48004E10);                                                                                                                                              
    u = read32(0x48004E10);                                                                                                                                                 
    printf("clock2[%d]\n", u);                                                                                                                                          
    write32(0x07, 0x48004E00);                                                                                                                                              
    u = read32(0x48004E00);                                                                                                                                                 
    printf("clock1[%d]\n", u);                                                                                                                                          

    u = read32(0x48004E30);                                                                                                                                                 
    printf("dss_cm[%d]\n", u);                                                                                                                                          
    //printf("setting dss_cm\n");                                                                                                                                         
    //write32(0x00, 0x48004E30);                                                                                                                                              
    u = read32(0x48004E40);                                                                                                                                                 
    printf("cm clksel dss[%d]\n", u);                                                                                                                                          
    printf("setting cm clksel dss\n");                                                                                                                                         
    write32(0x09, 0x48004E40);                                                                                                                                              
    u = read32(0x48004E44);                                                                                                                                                 
    printf("domain sleep[%d]\n", u);                                                                                                                                          
    printf("setting domain sleep\n");                                                                                                                                         
    write32(u & ~0x7, 0x48004E44);                                                                                                                                              

    u = read32(0x48004E48);                                                                                                                                                 
    printf("clk...[%d]\n", u);                                                                                                                                          
    printf("setting clk...\n");                                                                                                                                         
    write32(0x0, 0x48004E48);                                                                                                                                              

    u = read32(0x48004D30);                                                                                                                                                 
    printf("CM_AUTOIDLE_PLL[%d]\n", u);                                                                                                                                          
    printf("setting CM_AUTOIDLE_PLL\n", u);
    write32(0x0, 0x48004D30);

    u = read32(0x48004D00);                                                                                                                                                 
    printf("CM_CLKEN_PLL[%d]\n", u);                                                                                                                                          
    printf("setting CMM_CLKEN_PLL\n", u);
    write32(u | (0x07 << 16), 0x48004D00);

    u = read32(0x48004D44);                                                                                                                                                 
    printf("CM_CLKSEL_PLL2[%d]\n", u);                                                                                                                                          

    printf("resetting subsys\n");                                                                                                                                        
    write32(read32(0x48050010) | 0x01, 0x48050010);                                                                                                                    
    while(!(read32(0x48050014) & 0x01));                                                                                                                                    

    printf("turning off lcd\n");                                                                                                                                         
    u = read32(0x48050440);                                                                                                                                                 
    printf("lcd reg[%d], masked[%d]\n", u, u & (~0x03));                                                                                                             
    write32(read32(0x48050440) & (~0x03), 0x48050440);                                                                                                                 
    printf("turn off lcd done... sleeping ");                                                                                                                            



    printf("resetting display\n");                                                                                                                                         
    u = read32(0x48050040);                                                                                                                                                 
    //write32(0x03, 0x48050040);                                                                                                                                                 
    printf("resetting display\n");                                                                                                                                         
    printf("dss control[%d]\n", u);                                                                                                                                          
    /*
    printf("enabling clocks\n");                                                                                                                                         
    u = read32(0x48004E00);                                                                                                                                                 
    printf("clock1[%d]\n", u);                                                                                                                                          
    u = read32(0x48004E10);                                                                                                                                                 
    printf("clock2[%d]\n", u);                                                                                                                                          
    write32(0x07, 0x48004E00);                                                                                                                                              
    u = read32(0x48004E00);                                                                                                                                                 
    printf("clock1[%d]\n", u);                                                                                                                                          
    write32(0x01, 0x48004E10);                                                                                                                                              
    u = read32(0x48004E10);                                                                                                                                                 
    printf("clock2[%d]\n", u);                                                                                                                                          
    printf("clock2[%d]\n", u);                                                                                                                                          

    msleep(50);
    printf("setting pll control\n");                                                                                                                                          
    write32(0x00, 0x4804FF00);                                                                                                                                                 
    printf("setting pll control done\n");                                                                                                                                          

    u = read32(0x4804FF04);                                                                                                                                                 
    printf("pll status[%d]\n", u);                                                                                                                                          

    u = read32(0x4804FF00);                                                                                                                                                 
    printf("pll control[%d]\n", u);                                                                                                                                          

    printf("setting no autoidle\n");                                                                                                                                         
    write32(read32(0x48050010) & ~0x01, 0x48050010);                                                                                                                    

    printf("setting no autoidle for dispc\n");
    write32(read32(0x48050410) & ~0x01, 0x48050410);                                                                                                                    
    */

    printf("masking irqs\n");                                                                                                                                         
    write32(0x00, 0x4805041C);                                                                                                                 

    printf("resetting irqs\n");                                                                                                                                         
    write32(0xFFFFFFFF, 0x48050418);                                                                                                                 

    printf("turning off lcd\n");                                                                                                                                         
    u = read32(0x48050440);                                                                                                                                                 
    printf("lcd reg[%d], masked[%d]\n", u, u & (~0x03));                                                                                                             
    write32(read32(0x48050440) & (~0x03), 0x48050440);                                                                                                                 
    printf("turn off lcd done... sleeping ");                                                                                                                            
    msleep(50);                                                                                                                                                                  

    printf("reading irqstatus\n");                                                                                                                                         
    u = read32(0x48050418);                                                                                                                                                 
    printf("irqstatus reg[%d]\n", u);                                                                                                             

    printf("resetting framedone\n");                                                                                                                                         
    write32(read32(0x48050418) | 0x01, 0x48050418);                                                                                                                 

    printf("waiting for framedone\n");                                                                                                                                         
    while(!(read32(0x48050418) & 0x01))                                                                                                                                    


    printf("enabling clocks\n");                                                                                                                                         
    u = read32(0x48004E00);                                                                                                                                                 
    printf("clock1[%d]\n", u);                                                                                                                                          
    u = read32(0x48004E10);                                                                                                                                                 
    printf("clock2[%d]\n", u);                                                                                                                                          
    write32(0x07, 0x48004E00);                                                                                                                                              
    u = read32(0x48004E00);                                                                                                                                                 
    printf("clock1[%d]\n", u);                                                                                                                                          
    write32(0x01, 0x48004E10);                                                                                                                                              
    u = read32(0x48004E10);                                                                                                                                                 
    printf("clock2[%d]\n", u);                                                                                                                                          
    printf("clock2[%d]\n", u);                                                                                                                                          

    printf("resetting subsys\n");                                                                                                                                        
    write32(read32(0x48050010) | 0x01, 0x48050010);                                                                                                                    
    while(!(read32(0x48050014) & 0x01))                                                                                                                                    
        msleep(1);

    printf("resetting subsys done");                                                                                                                                     

    return;                                        
}

int hw_preboot() {
/* Enable USBOTG clocks */
  modify_register32(CRM_AP_BASE_ADDR+0xc, 0, 1 << 12);
  modify_register32(CRM_AP_BASE_ADDR+0x28, 0, 0x3 << 22);
  modify_register32(CRM_AP_BASE_ADDR+0x34, 0, 0x3 << 16);
/* Reset USBOTG */
  write32(0x3f, USBOTG_CTRL_BASE_ADDR+0x10);
  while (read32(USBOTG_CTRL_BASE_ADDR+0x10)) {
  }
/* Enable main USBOTG clock */
  write32(0x1, USBOTG_CTRL_BASE_ADDR+0xc);
/* Disable SDHC1/2 clocks */
  modify_register32(CRM_AP_BASE_ADDR+0x60, 0, 1 << 0);
  modify_register32(CRM_AP_BASE_ADDR+0x60, 0, 1 << 8);
/* Reset EPIT */
  modify_register32(EPIT1_AP_BASE_ADDR+0x0, 0x1, 0);
  modify_register32(EPIT1_AP_BASE_ADDR+0x0, 0, 0x10000);
  while (read32(EPIT1_AP_BASE_ADDR+0x0) & 0x10000) {
  }
/* Disable and clear KPP */
  write16(0xf, KPP_BASE_ADDR+0x2);
/* Stop SDMA */
  write32(0xffffffff, SDMA_BASE_ADDR+0x8);
  write32(0xffffffff, SDMA_BASE_ADDR+0x4);
/* Reset SDMA */
  write32(0x1, SDMA_BASE_ADDR+0x24);
  while (read32(SDMA_BASE_ADDR+0x28) & 0x1) {
  }
/* Enable UART3 clocks */
  modify_register32(CRM_AP_BASE_ADDR+0x5c, 0, 1 << 16);  
}
