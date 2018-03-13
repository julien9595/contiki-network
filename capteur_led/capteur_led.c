#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(capteur_led, "capteur led");
AUTOSTART_PROCESSES(&capteur_led);

PROCESS_THREAD(capteur_led, ev, data)
{
	PROCESS_BEGIN();
	leds_on(LEDS_ALL);
	PROCESS_END();
}
