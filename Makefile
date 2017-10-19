ifeq ($(PARAM_FILE), )
	PARAM_FILE:=../../Makefile.param
	include $(PARAM_FILE)
endif			

obj-m := hisi_led_drv.o
#hisi_led_drv-y += hisi_led_drv.o

EXTRA_CFLAGS += -I$(REL_INC)
EXTRA_CFLAGS += $(DRV_CFLAGS)

default:
	@$(CC) -g -Wall -o hisi_led_test hisi_led_test.c
	@make -C $(LINUX_ROOT) M=$(PWD) modules 
clean: 
	@make -C $(LINUX_ROOT) M=$(PWD) clean 
