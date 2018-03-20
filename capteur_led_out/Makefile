ifndef TARGET
TARGET=z1
endif

CONTIKI_SOURCEFILES += sht11.c
APPS=serial-shell

CONTIKI_PROJECT = capteur_led_out
all: $(CONTIKI_PROJECT)

UIP_CONF_IPV6=1
WITH_IPV6=1

CONTIKI = ../../..
include $(CONTIKI)/Makefile.include

