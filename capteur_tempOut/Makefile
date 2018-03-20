ifndef TARGET
TARGET=z1
endif

CONTIKI_SOURCEFILES += sht11.c
APPS=serial-shell

CONTIKI_PROJECT = capteur_tempOut
all: $(CONTIKI_PROJECT)

WITH_IPV6=1
UIP_CONF_IPV6=1

CONTIKI = ../../..
include $(CONTIKI)/Makefile.include

