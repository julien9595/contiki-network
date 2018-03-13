ifndef TARGET
TARGET=z1
endif

CONTIKI_PROJECT = test_led
CONTIKI_SOURCEFILES += sht11.c
APPS=serial-shell

CONTIKI_PROJECT = capteur_led
all: $(CONTIKI_PROJECT)

#UIP_CONF_IPV6=1

CONTIKI = ../../..
include $(CONTIKI)/Makefile.include

