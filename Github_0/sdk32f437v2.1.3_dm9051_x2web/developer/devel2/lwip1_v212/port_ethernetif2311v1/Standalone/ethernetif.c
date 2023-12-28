/**
 * @file
 * Ethernet Interface for standalone applications (without RTOS) - works only for 
 * ethernet polling mode (polling for ethernet frame reception)
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#include "lwip/opt.h"
#include "dm9051_lw.h"
#include "dm9051_lw_conf.h"
#include "lwip/mem.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "netconf.h"
#include "developer_conf.h"

/* Network interface name */
#define IFNAME0 'd'
#define IFNAME1 'm'

#define OVERSIZE_LEN			PBUF_POOL_BUFSIZE //#define _PBUF_POOL_BUFSIZE 1514 //defined in "lwipopts.h" (JJ20201006)
#define RXBUFF_OVERSIZE_LEN		(OVERSIZE_LEN+2)
union {
	uint8_t rx;
	uint8_t tx;
} EthBuff[RXBUFF_OVERSIZE_LEN]; //[Single Task project.] not occupied by concurrently used.


uint8_t tmpMACaddr[ETHERNET_COUNT][6];

u8 *get_eth_buff(void)
{
	return &EthBuff[0].tx;
}

void lwip_set_mac(uint8_t* macadd)
{
  int i = mstep_get_net_index();
  tmpMACaddr[i][0] = macadd[0];
  tmpMACaddr[i][1] = macadd[1];
  tmpMACaddr[i][2] = macadd[2];
  tmpMACaddr[i][3] = macadd[3];
  tmpMACaddr[i][4] = macadd[4];
  tmpMACaddr[i][5] = macadd[5];
//printf("[lwip_set_mac[%d]] %02x%02x%02x%02x%02x%02x\r\n  %02x%02x%02x%02x%02x%02x\r\n", i,
//	tmpMACaddr[0][0],tmpMACaddr[0][1],tmpMACaddr[0][2],tmpMACaddr[0][3],tmpMACaddr[0][4],tmpMACaddr[0][5],
//	tmpMACaddr[1][0],tmpMACaddr[1][1],tmpMACaddr[1][2],tmpMACaddr[1][3],tmpMACaddr[1][4],tmpMACaddr[1][5]);
}

void lwip_get_mac(uint8_t *adr)
{
  int i = mstep_get_net_index();
  memcpy(adr, &tmpMACaddr[i][0], 6);
//printf("[mstep_Get_net_index[%d]] %02x%02x%02x%02x%02x%02x\r\n  %02x%02x%02x%02x%02x%02x\r\n", i,
//	tmpMACaddr[0][0],tmpMACaddr[0][1],tmpMACaddr[0][2],tmpMACaddr[0][3],tmpMACaddr[0][4],tmpMACaddr[0][5],
//	tmpMACaddr[1][0],tmpMACaddr[1][1],tmpMACaddr[1][2],tmpMACaddr[1][3],tmpMACaddr[1][4],tmpMACaddr[1][5]);
}

void GpioDisplay(void)
{
  int i;
  printf("\r\n");
//#if (_ETHERNET_COUNT >= 2)
//do {
  for (i = 0; i < ETHERNET_COUNT; i++) {
	mstep_set_net_index(i);
	printf("@ETHERNET INTERFACE      %s\r\n", mstep_conf_cpu_spi_ethernet());
  }
  mstep_set_net_index(0);
//} while(0);
//#elif (_ETHERNET_COUNT == 1)
//  printf("@ETHERNET INTERFACE      %s\r\n", mstep_conf_cpu_spi_ethernet());
//#endif
}

void dm9051_init_nondual(void)
{
	//int i; //_n_verify_id = 0;

	//printf(".dm9051_init_dual().s\r\n");
	
	//for (i = 0; i < ETHERNET_COUNT; i++) { //get_eth_interfaces()
		uint8_t adr[6];
		uint16_t id;
		//i = mstep_get_net_index(); //mstep_set_net_index(i); //set_pin_code(i);
		lwip_get_mac(adr);
		//dm9051_poweron_rst();
		//delay_ms(1);
		id = 
		  dm9051_init(adr);
		//_display_verify_chipid("dm9051_init", mstep_spi_conf_name(), id);
		 if (display_verify_chipid("dm9051_init", mstep_spi_conf_name(), id))
			 n_verify_id++;
	//}
	
	//printf(".dm9051_init_dual().e\r\n");
	
#if 0
	do {
	int pnc, j, k;
	for (pnc = 0; pnc < get_eth_interfaces(); pnc++) {
		uint16_t id;
		set_pin_code(pnc);
		_display_verify_chipid("mux-testing...", mstep_spi_conf_name(), 0);	
		for (i = 0; i < 16; i++) {
			gpio_mux_sel_type muxtbl[16] = {
				GPIO_MUX_0,
				GPIO_MUX_1,
				GPIO_MUX_2,
				GPIO_MUX_3,
				GPIO_MUX_4,
				GPIO_MUX_5,
				GPIO_MUX_6,
				GPIO_MUX_7,
				GPIO_MUX_8,
				GPIO_MUX_9,
				GPIO_MUX_10,
				GPIO_MUX_11,
				GPIO_MUX_12,
				GPIO_MUX_13,
				GPIO_MUX_14,
				GPIO_MUX_15,
			};
			gpio_spi_clk_mux(muxtbl[i]);
			
			printf("  sck Mux %x, %s\r\n", i, get_spi_name(pnc));
			
			//([.])
			for (j = 0; j < 16; j++) {
				printf("  Mux %x miso, Chip ID mosi:", j);
				gpio_spi_mi_mux(muxtbl[j]);
				for (k = 0; k < 16; k++) {
					gpio_spi_mo_mux(muxtbl[k]);
					id = read_chip_id();
					printf("  %4x", id);
					if (id == 0x9051) {
						printf("\r\n");
						printf("\r\n");
						goto cont;
					}
				}
				printf("\r\n");
			}
			  
			if (!((i + 1)%4)) {
			  printf("\r\n");
			}
		}
	cont:
		id = 0; //dummy-line for compiler.
	}
	} while(0);
#endif
}

uint16_t dm9051_link_update_dual(void)
{
	int i;
	uint16_t updwn;
//#if (_ETHERNET_COUNT > 1) 
	for (i = 0; i < ETHERNET_COUNT; i++) { //get_eth_interfaces()
		mstep_set_net_index(i); //set_pin_code(i);
		updwn = dm9051_link_update();
		
	  //printf("[dm9051_link_update_dual].dm9051_link_update[%d] = result %d\r\n", i, updwn);
		
		if (updwn & 0x0004) {
			
			return 1; //break;
		}
	}
//#else
//	updwn = dm9051_link_update();
//#endif
	return 0; //return updwn;
}
void dm9051_tx_dual(uint8_t *buf, uint16_t len)
{
	//int i;
//#if (_ETHERNET_COUNT > 1) 
	//for (i = 0; i < ETHERNET_COUNT; i++) { //get_eth_interfaces()
	//	mstep_set_net_index(i); //set_pin_code(i);
	//	dm9051_tx(buf, len); //on_pin_code("dm9051_tx", 0);
	//}
	dm9051_tx(buf, len);
	dm9051_txlog_monitor_tx(2, buf, len);
//#else
//	dm9051_tx(buf, len);
//#endif
}
uint16_t dm9051_rx_dual(uint8_t *buff)
{
	//int i;
	u16 len;
//#if (_ETHERNET_COUNT > 1) 
	//for (i = 0; i < ETHERNET_COUNT; i++) { //get_eth_interfaces()
	//	mstep_set_net_index(i); //set_pin_code(i);
	//	len = dm9051_rx(buff);
	//	if (len)
	//		break;
	//}
	len = dm9051_rx(buff);
//#else
//	len = dm9051_rx(buff);
//#endif
	return len;
}

static void
low_level_init(struct netif *netif)
{
  int i = mstep_get_net_index();
  /* set MAC hardware address */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;
	
  netif->hwaddr[0] =  tmpMACaddr[i][0];
  netif->hwaddr[1] =  tmpMACaddr[i][1];
  netif->hwaddr[2] =  tmpMACaddr[i][2];
  netif->hwaddr[3] =  tmpMACaddr[i][3];
  netif->hwaddr[4] =  tmpMACaddr[i][4];
  netif->hwaddr[5] =  tmpMACaddr[i][5];

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
  dm9051_init_nondual(); //dm9051_init(MACaddr);
}

void process_txlog_debug(uint8_t *buffer, int len) {
  dm9051_txlog_disp(buffer, len);
}

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  struct pbuf *q;
  int l = 0;
  uint8_t *buffer = &EthBuff[0].tx; //Tx_Buff;
	
  for(q = p; q != NULL; q = q->next)
  {
    memcpy((u8_t*)&buffer[l], q->payload, q->len);
    l = l + q->len;
  }
  dm9051_tx_dual(buffer, (uint16_t) l); //dm9051_tx(.);
  
  process_txlog_debug(buffer, l);
  
  return ERR_OK;
}

	static struct pbuf *
	low_level_inp(struct netif *netif)
	{
	  struct pbuf *p, *q;
	  uint16_t len;
	  int l = 0;
	  uint8_t *buffer = &EthBuff[0].rx;
		
	  len = dm9051_rx(buffer);
	  if (!len)
		  return NULL;
	  
	  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
	  if (p)
	  {
		for (q = p; q != NULL; q = q->next)
		{
		  memcpy((u8_t*)q->payload, (u8_t*)&buffer[l], q->len);
		  l = l + q->len;
		}
	  }
	  return p;
	}

	static struct pbuf *
	low_level_input(struct netif *netif)
	{
	  struct pbuf *p, *q;
	  uint16_t len;
	  int l = 0;
	  uint8_t *buffer = &EthBuff[0].rx; //Rx_Buff;

	  len = dm9051_rx_dual(buffer); //dm9051_rx(.);
		
	  if (!len)
		  return NULL;
	  
		//.printf("net,rx (len %u)\r\n", len);
	  
		p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
		if (p)
		{
			for (q = p; q != NULL; q = q->next)
			{
			  memcpy((u8_t*)q->payload, (u8_t*)&buffer[l], q->len);
			  l = l + q->len;
			}
			#if 1
			//printf("ethernetif.c(pbuf:%s Eth Buffer total len %d)\r\n", "rx", len);
			#else
			//showpbuf("rx", netif, p);
			#endif
		}
	  return p;
	}
	
void process_rxlog_arp(struct pbuf *p) {
	dm9051_rxlog_arp(p->payload, p->tot_len, p->len);
}
void process_rxlog_ack(struct pbuf *p, err_t err) {
	char errbuf[36];
	if (err == ERR_OK)
		sprintf(errbuf, "ERR_OK = %s", lwip_strerr(err)); //printf(" .[debug process this 'ACK'] is ERR_OK = %s\r\n", lwip_strerr(err));
	else
		sprintf(errbuf, "err %d = %s", err, lwip_strerr(err)); //printf(" .[debug process this 'ACK'] is err %d = %s\r\n", err, lwip_strerr(err));
	  
	dm9051_rxlog_ack(p->payload, p->tot_len, errbuf);
}
	
err_t ethernetif_inp(struct netif *netif)
{
	  err_t err;
	  struct pbuf *p;

	  p = low_level_inp(netif);
	  if (p == NULL) 
		return ERR_INPROGRESS; //JJ.

	  err = netif->input(p, netif);
	  if (err != ERR_OK)
	  {
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
		pbuf_free(p);
	  }
	  
	  return err;
}

err_t mstep_input(struct pbuf *p)
{
	int pin = mstep_get_net_index();
	struct netif *netif = &xnetif[pin];
	
	return netif->input(p, netif);
   //err = netif->input(p, netif);
}

err_t ethernetif_input(struct netif *netif)
{
	  err_t err;
	  struct pbuf *p;
		
	  #if 1
	  onchange_timeouts_log("ethernetif_input() call-to low_lvl_input && netif_input,rx"); //to-has this
	  #endif

	  /* move received packet into a new pbuf */
	  p = low_level_input(netif);

	  /* no packet could be read, silently ignore this */
	  if (p == NULL) 
		return ERR_INPROGRESS; //JJ.

	  process_rxlog_arp(p);
	  
	  /* entry point to the LwIP stack */
	  err = mstep_input(p);
  
	  process_rxlog_ack(p, err);
	  
	  if (err != ERR_OK)
	  {
		LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
		pbuf_free(p);
	  }
	  return err;
}

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif
{
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
  int unused;
};

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;
  LWIP_ASSERT("netif != NULL", (netif != NULL));
	
  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL)
  {
    LWIP_DEBUGF(NETIF_DEBUG, ("_ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }
  
  #if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
  #endif

  #if 0
  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  //NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);
  #endif

  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}

#ifndef AT32F437xx
int test_line7_enter = 0;
uint8_t my_debounce = 0;
void line7_proc(void) {
	
  uint8_t isr;
  isr = cspi_read_reg(DM9051_ISR);
  
  printf("[INFO]: line7() enter %d ... isr %02x\r\n", ++test_line7_enter, isr);

#if 0
  printf("................................ line7_proc(), where test_line7_enter_check_setup is %d\r\n", test_line7_enter_check_setup);
  if (test_line7_enter_check_setup == 0)
	  printf("................................ [WARN]: line7_proc() encounterred illegal enter! '_test_line7_enter_check_setup' still on 0\r\n");
#endif
  
  if (my_debounce == 0) {
	my_debounce = 8;
	at32_led_toggle(LED4);
	//at32_led_toggle(LED2);
	//at32_led_toggle(LED3);
	//at32_led_on(LED4);
  }
  
  #if 1
  //lwip_rx_loop_handler();
  //lwip_rx_hdlr();
  lwip_rx_loop_handler();
  #else
  do {
	uint16_t len;
	len = test_rx_hdlr();
	if (len) {
		if (test_total_send_count_setup) {
			
			test_total_send_count_setup = CalcModelShow(test_total_send_count_setup);
			
		} else 
			printf("[WARN]: line7() encounterred under_flow count!\r\n");
	}
  } while(len);
  #endif
  
  my_debounce += 8; // if this only, when 256, i.e. 0
  my_debounce &= 0x3f; // when 64, i.e. 0
  
  isr = cspi_read_reg(DM9051_ISR);
  printf("[INFO]: line7() exit %d ... isr %02x\r\n", ++test_line7_enter, isr);
  printf("[INFO]: line7() exit write isr %02x\r\n", isr);
  cspi_write_reg(DM9051_ISR, isr);
}
#endif

void reset_proc(void) {
	dm9051_reset_process();
}
