#include <stdint.h>
#include <rsc_types.h>
#include "./r30_pins.c"

#define CYCLES_PER_SECOND 200000000

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void) {
  while (1) {
    __R30 |= P9_30;
    __delay_cycles(CYCLES_PER_SECOND/2);
    __R30 &= ~P9_30;
    __delay_cycles(CYCLES_PER_SECOND/2);
  }
}


/* required by PRU */
#pragma DATA_SECTION(pru_remoteproc_ResourceTable, ".resource_table")
#pragma RETAIN(pru_remoteproc_ResourceTable)
struct my_resource_table {
    struct resource_table base;
    uint32_t offset[1];
} pru_remoteproc_ResourceTable = { 1, 0, 0, 0, 0 };