#include "contiki.h"
#include "dev/leds.h"

#include "lib/random.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"
#include "net/uip.h"
#include "net/uip-ds6.h"

#include "simple-udp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UDP_PORT 1234

#define SEND_INTERVAL		(20 * CLOCK_SECOND)
#define SEND_TIME		(random_rand() % (SEND_INTERVAL))


static struct simple_udp_connection broadcast_connection;

PROCESS(capteur_led, "capteur led");
AUTOSTART_PROCESSES(&capteur_led);

static void
receiver(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
  char* datas = (char*) data;

  if(strlen(datas) == 1) {
    // Data from TempIn
    printf("[LED IN] Received a Temp In : %c\n", datas[0]);
    if(datas[0] == 'B') {
	leds_off(LEDS_ALL);
	leds_on(LEDS_GREEN);
    } else if (datas[0] == 'G') {
	leds_off(LEDS_ALL);
	leds_on(LEDS_RED);
    } else if (datas[0] == 'R') {
        leds_off(LEDS_ALL);
	leds_on(LEDS_BLUE);
    }
  } else {
    printf("[LED IN] Data not for me\n");
    uip_ipaddr_t addr;
    uip_create_linklocal_allnodes_mcast(&addr);
    simple_udp_sendto(&broadcast_connection, data, datalen, &addr);
  }
}

PROCESS_THREAD(capteur_led, ev, data)
{
	static struct etimer periodic_timer;
	static struct etimer send_timer;
	uip_ipaddr_t addr;

	PROCESS_BEGIN();
	leds_off(LEDS_ALL);

        simple_udp_register(&broadcast_connection, UDP_PORT,
                      NULL, UDP_PORT,
                      receiver);

        etimer_set(&periodic_timer, SEND_INTERVAL);

        while(1) {
                PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
                etimer_reset(&periodic_timer);
                etimer_set(&send_timer, SEND_TIME);

                PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&send_timer));
		uip_create_linklocal_allnodes_mcast(&addr);
        }

	PROCESS_END();
}

