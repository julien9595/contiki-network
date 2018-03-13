#include "contiki.h" 
#include "dev/sht11-sensor.h" 
#include "dev/light-sensor.h" 
#include "dev/leds.h" 
#include <stdio.h> 


PROCESS(send_sensor_info_process, "Print the Sensors Information"); 
AUTOSTART_PROCESSES(&send_sensor_info_process); 


static int get_light(void) { 
	return 10 * light_sensor.value(LIGHT_SENSOR_PHOTOSYNTHETIC) / 7; 
} 

static int get_temp(void) { 
	return ((sht11_sensor.value(SHT11_SENSOR_TEMP) / 10) - 396) / 10; 
}

PROCESS_THREAD(send_sensor_info_process, ev, data) { 

	static struct etimer etimer;

	PROCESS_BEGIN(); 
	SENSORS_ACTIVATE(light_sensor); 
	SENSORS_ACTIVATE(sht11_sensor); 

	while(1) {
		etimer_set(&etimer, CLOCK_SECOND);
		printf("Light: %d \n", get_light()); 
		printf("Temperature / 10 - 396 / 10 : %d \n", ((sht11_sensor.value(SHT11_SENSOR_TEMP) / 10) - 396) / 10); 

	}

	PROCESS_END();
}

/*
#include "contiki.h"
#include "dev/temperature-sensor.h"
#include <stdio.h>

PROCESS(capteur_tempIn, "Capteur temperateur IN");
AUTOSTART_PROCESSES(&capteur_tempIn);

PROCESS_THREAD(capteur_tempIn, ev, data) {

	static struct etimer etimer;

	PROCESS_BEGIN();

	printf("Starting mesuring temperature inside\r\n");

	while(1) {
		etimer_set(&etimer, CLOCK_SECOND);

		PROCESS_WAIT_UNTIL(etimer_expired(&etimer));

		unsigned int temp = temperature_sensor.value(0);
		printf("\nTemp : %d.%d °C \r", temp/10, temp-(temp/10)*10);
	}

	PROCESS_END();
}*/
