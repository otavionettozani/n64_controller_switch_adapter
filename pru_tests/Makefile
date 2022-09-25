PRU_SWPKG = /usr/lib/ti/pru-software-support-package

CC = clpru
LD = lnkpru
CFLAGS = --include_path=$(PRU_SWPKG)/include \
         --include_path=$(PRU_SWPKG)/include/am335x
LDFLAGS = $(PRU_SWPKG)/labs/lab_2/AM335x_PRU.cmd

all: hw_test

hw.o: hw.c
    $(CC) $(CFLAGS) $^ --output_file $@

hw_test: hw.o
    $(LD) $(LDFLAGS) $^ -o $@
