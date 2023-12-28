#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

#include "lwip/err.h"
#include "lwip/netif.h"

//#include "at32f435_437.h" //"at32f413.h" //#include "at32f415.h"

void dm9051_init_nondual(void); //dm9051_init_dual(void);
uint16_t dm9051_link_update_dual(void);
void dm9051_tx_dual(uint8_t *buf, uint16_t len);
uint16_t dm9051_rx_dual(uint8_t *buff);

err_t ethernetif_init(struct netif *netif);
err_t ethernetif_input(struct netif *netif);

err_t ethernetif_inp(struct netif *netif);

void lwip_set_mac(unsigned char* macadd);
void lwip_get_mac(uint8_t *adr);

void line7_proc(void);
void reset_proc(void);

#endif
