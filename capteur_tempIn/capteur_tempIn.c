#include "contiki.h" 
#include "dev/temperature-sensor.h" 
#include "dev/light-sensor.h" 
#include "dev/leds.h" 
#include <stdio.h> 
#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "net/uip.h"
#include "net/uip-ds6.h"
#include "simple-udp.h"
#include <string.h>
#include <time.h>

#define UDP_PORT 1234

#define SEND_INTERVAL		(20 * CLOCK_SECOND)
#define SEND_TIME		(random_rand() % (SEND_INTERVAL))

static struct simple_udp_connection broadcast_connection;

PROCESS(send_sensor_info_process, "Print the Sensors Information"); 
AUTOSTART_PROCESSES(&send_sensor_info_process); 

static void
receiver(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
    printf("[TEMP_IN] Data never for me\n");
    char* datas = (char*) data;
    if (strlen(datas) == 1) {
	return;
    }
    uip_ipaddr_t addr;
    uip_create_linklocal_allnodes_mcast(&addr);
    simple_udp_sendto(&broadcast_connection, data, 2, &addr);
}

PROCESS_THREAD(send_sensor_info_process, ev, data) { 
	static struct etimer periodic_timer;
	static struct etimer send_timer;
	uip_ipaddr_t addr;

	static struct etimer etimer;

	PROCESS_BEGIN(); 

       simple_udp_register(&broadcast_connection, UDP_PORT,
                      NULL, UDP_PORT,
                      receiver);

        etimer_set(&periodic_timer, SEND_INTERVAL);

        while(1) {
                PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
                etimer_reset(&periodic_timer);
                etimer_set(&send_timer, SEND_TIME);
                PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&send_timer));

		char *temperature;
		int t = rand() % (40);

		if (t > 30) {		
			temperature = "R";
		} else if (t < 10) {
			temperature = "B";
		} else {
			temperature = "G";
		}

                printf("Sending from capteur_tempIn t : %d, tempIn : %s \n", t, temperature);
		uip_create_linklocal_allnodes_mcast(&addr);
                simple_udp_sendto(&broadcast_connection, temperature, 5, &addr);
        }

	PROCESS_END();
}

