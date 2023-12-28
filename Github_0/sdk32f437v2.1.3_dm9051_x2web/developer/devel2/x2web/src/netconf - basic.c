/**
  **************************************************************************
  * @file     netconf.c
  * @version  v1.0
  * @date     2023-04-28
  * @brief    network connection configuration
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
//#include "at32f435_437_board.h" //""at32f413_board.h" //#include "at32f415_board.h"
//#include "at32_cm4_device_support.h" //#include "at32f415.h" //"at32f435_437.h" //"at32f413.h" //"at32f435_437_board.h"
//#include "stdio.h"
//#include "dm9051_lw.h"
#include "dm9051_lw_conf.h"
#include "ethernetif.h"
#include "developer_conf.h" //#include "main.h" //#include "developer_conf.h"
//#include "_dm9051_at32_conf.h" //"dm9051_env.h" //"dm9051f_netconf.h" //"at32_emac.h" //has #include "dm9051_lw.h"
//#include "dm9051_spi_sync.h"
//#include "dm9051_at32_decl.h" 
#include "netconf.h" //has #include "ethernetif.h"
#include <string.h>

#ifndef DM9051_DIAG
#define DM9051_DIAG(x) do {printf x;} while(0)
#include <stdio.h>
#include <stdlib.h>
#endif

#define DM9051_RX_DBGMSG(expression, message) do { if ((expression)) { \
  DM9051_DIAG(message);}} while(0)

struct netif xnetif[ETHERNET_COUNT];  
//struct netif netif;
  
net_t *s__net_instance[ETHERNET_COUNT];

#if 0
.static void ethernetif_notify_conn_changed(struct netif *netif)
{
}
.static void env_ethernetif_update_config_cb(struct netif *netif) //tobe = env_linkchang_cb
{
}
.void _tcpip_stack_init(void)
{
}
#endif

int netconf_is_link_up(void)
{
	int pin = mstep_get_net_index();
	//return netif_is_up(&netif); //?
	return netif_is_link_up(&xnetif[pin]);
}

/**
  * @brief  this function is receive handler.
  * @param  none
  * @retval none
  */
err_t lwip_rx_hdlr(int i)
{
  err_t err; //int i = mstep_get_net_index();
  err = ethernetif_inp(&xnetif[i]);
  DM9051_RX_DBGMSG(err != ERR_OK && err != ERR_INPROGRESS, ("[netconf.c] ethernetif_input: IP input error\r\n"));
  return err;
}

void lwip_rx_loop_handler(void)
{
  int pin = mstep_get_net_index();
  err_t err = ethernetif_input(&xnetif[pin]);
  DM9051_RX_DBGMSG(err != ERR_OK && err != ERR_INPROGRESS, ("[netconf.c] ethernetif_input: IP input error\r\n"));
}

/*static*/ void phy_link_timer(void *arg) //=to_time_link() (are to phase-out, BUT keep called API-exist.)
{
  net_t *net = arg;
  static volatile uint8_t first_2rst_timer1500_2cnnt2initpub = 1;
  static volatile uint8_t first_timer_coerce2lnk = 1; /* Global assurance */
  uint8_t chip_link_up = (uint8_t) dm9051_link_update_dual(); //.dm9051_link_update();
  //.first_link_coerce_timer_support(&netif, chip_link_up);
  
  int pin = mstep_get_net_index();
	
  if(!netif_is_link_up(&xnetif[pin]))
  {
    if (chip_link_up) {
		//#if LINK_DETECTION_TCK_IMPL
		if (linkhandler_type() == TYPE_TICKS)
			linkup_cb(NULL, NULL, NET_LINK_UP); /*net->net_cb*/ 
		//#endif
		//#if LINK_DETECTION_NET_IMPL
		else if (linkhandler_type() == TYPE_TIMEROUTS)
			net->cbf(net, net->net_arg, NET_LINK_UP);
		//#endif
		first_timer_coerce2lnk = 0;
    }
    if (chip_link_up && first_2rst_timer1500_2cnnt2initpub == 0) {
		//first_link_coerce_timer_trigger:
		reset_proc(); //dm9051_reset_process();
		first_2rst_timer1500_2cnnt2initpub = 1;
    }
  }
  else if (netif_is_link_up(&xnetif[pin]))
  {
	if (!chip_link_up) { //This is such as unplug CAT5-45J
		//#if LINK_DETECTION_TCK_IMPL
		if (linkhandler_type() == TYPE_TICKS)
			linkup_cb(NULL, NULL, NET_LINK_DOWN); /*net->net_cb*/ 
		//#endif
		//#if LINK_DETECTION_NET_IMPL
		else if (linkhandler_type() == TYPE_TIMEROUTS)
			net->cbf(net, net->net_arg, NET_LINK_DOWN);
		//#endif
		first_timer_coerce2lnk = 0;
		first_2rst_timer1500_2cnnt2initpub = 0;
	}
  }
  
  if (first_timer_coerce2lnk) { //"startup_linkdown_process"
	first_timer_coerce2lnk++;
	if (first_timer_coerce2lnk > (1500 / get_link_handler_ms()))
	{
		//if (chip_link_up) netif_clear_flags(netif, NETIF_FLAG_LINK_UP); //down
		//else netif_set_flags(netif, NETIF_FLAG_LINK_UP); //up
		//#if LINK_DETECTION_TCK_IMPL
		if (linkhandler_type() == TYPE_TICKS)
			linkup_cb(NULL, NULL, chip_link_up ? NET_LINK_UP : NET_LINK_DOWN);
		//#endif
		//#if LINK_DETECTION_NET_IMPL
		else if (linkhandler_type() == TYPE_TIMEROUTS)
			net->cbf(net, net->net_arg, chip_link_up ? NET_LINK_UP : NET_LINK_DOWN);
		//#endif
		first_timer_coerce2lnk = 0;
		if (!chip_link_up)
		  first_2rst_timer1500_2cnnt2initpub = 0;
	}		
  }
  
  if (mqttc_is_connected() && first_2rst_timer1500_2cnnt2initpub) {
	first_2rst_timer1500_2cnnt2initpub++;
	if (first_2rst_timer1500_2cnnt2initpub > (1500 / get_link_handler_ms())) { // Calc to be 1.5 sec (1500 ms)
		first_2rst_timer1500_2cnnt2initpub = 0;
		
	  #if 0
		//printf(".[Publish_info]\r\n");
		//print_publish_info(get_mqtt_publish_topic_number());

		//printf("\r\n");
		//printf(".[Subscribe_info]\r\n");
		//print_subscribe_info();
		  
		//printf("\r\n");
		//publish_handle_news("link_tmr");
	  #endif
	}
  }

  #if MQTT_CLIENT_SUPPORT
  mqttc_goto_connect(&xnetif[pin], MY_PHY_LINKUP); /* bedo-once, Once relate to 'netif_is_link_up()' */
  mqttc_connect();
  #endif
  
  if (linkhandler_type() == TYPE_TIMEROUTS)
	sys_timeout(get_link_handler_ms(), phy_link_timer, net);

  onchange_timeouts_log("in-phy_link_timer"); //to-has this
}

void linkup_cb(net_t *net, void *arg, u8_t status) {
  //xxx = arg; NULL;
  int pin = mstep_get_net_index();
  if (status == NET_LINK_UP) {
	printf("dm9051[%d] link up\r\n", pin);
	//.onchange_timeouts_log("lnk-up"); //to-has this
	netif_set_link_up(&xnetif[pin]); //netif_set_link_up_INITAndTimer(&netif);
#if LWIP_NETIF_LINK_CALLBACK == 0
	env_ethernetif_update_config_cb(&xnetif[pin]);
#endif
#if (APP_ETH_COUNT > 1)  
	//.bench_test_tx_and_rx();
#endif
  }
  if (status == NET_LINK_DOWN) {
    printf("dm9051[%d] link down\r\n", pin);
	netif_set_link_down(&xnetif[pin]); //netif_set_link_down_Timer(&netif);

	#if MQTT_CLIENT_SUPPORT
	mqttc_close(); //= _mqtt_close(client, MQTT_CONNECT_DISCONNECTED);
	#endif
  }
}

//#if LINK_DETECTION_NET
	//#if LINK_DETECTION_NET_IMPL
	static void net_new_task(net_t *net, net_link_cb_t cb, void *arg)
	{
	  net->link_state = NET_LINK_DOWN; //net->cyclic_tick = 0;
	  net->net_arg = arg;
	  net->cbf = cb;
	  /* Start cyclic link_handle timer */
	  sys_timeout(get_link_handler_ms(), phy_link_timer, net); //(no sys_untimeout(), THIS IS FOREEVER LOOP CYCLE, such as 'link_handle()')
	  //return ERR_OK;
	}

	void netlink_init(void) // (are to phase-in, NOW start API-skelton.)
	{
	  s__net_instance[mstep_get_net_index()] = (net_t *)mem_calloc(1, sizeof(net_t));
	  if (s__net_instance[mstep_get_net_index()] == NULL)
	  {
		printf("net: s__net_instance[i] malloc fail @@!!!\r\n");
		while(1);
	  }
	  //s__net_instance[i]->link_state = NET_LINK_DOWN;
	  net_new_task(s__net_instance[mstep_get_net_index()], linkup_cb, NULL);
	}
	//#endif
//#endif

//#if (LINK_DETECTION_TCK > 0)
//#if LINK_DETECTION_TCK_IMPL
static void link_handle1(void) // (are to phase-in)
{
#if MQTT_CLIENT_LINK_TMR_TYPE		==		TYPE_TICKS
  //=static volatile uint32_t link_timer = get_link_handler_ms(); //LINK_HANDLER_MS;
  static volatile uint32_t link_timer = 0;
	
  if (!link_timer) 
	  link_timer = all_local_time + get_link_handler_ms();
  if (all_local_time >= link_timer) {
    link_timer = all_local_time + get_link_handler_ms();
	phy_link_timer(NULL); //to_time_link();
  }
#endif
}
//#endif
//#endif

#if 0 //LWIP_DHCP
void finetmr_handle(void);
void coarsetmr_handle(void);
#endif
	
void lwip_periodic_handle(void)
{
//#if (LINK_DETECTION_TCK > 0)
//#if LINK_DETECTION_TCK_IMPL
	if (linkhandler_type() == TYPE_TICKS)
		link_handle1();
//#endif
//#endif
	//if (get_publishhandler_type() == TYPE_TICKS)
	//	publish_handle1();
#if 0 //LWIP_DHCP
	finetmr_handle();
	coarsetmr_handle();
#endif
}

// [netconf - COMM2]

#if 0 //LWIP_DHCP
void finetmr_handle(void) {
  static volatile uint32_t dhcp_fine_timer = 0;
  /* Fine DHCP periodic process every 500ms */
  if (all_local_time - dhcp_fine_timer >= DHCP_FINE_TIMER_MSECS || all_local_time < dhcp_fine_timer)
  {
    dhcp_fine_timer =  all_local_time;
    dhcp_fine_tmr();
  }
}
void coarsetmr_handle(void) {
  static volatile uint32_t dhcp_coarse_timer = 0;
  /* DHCP Coarse periodic process every 60s */
  if (all_local_time - dhcp_coarse_timer >= DHCP_COARSE_TIMER_MSECS || all_local_time < dhcp_coarse_timer)
  {
    dhcp_coarse_timer =  all_local_time;
	printf("dhcp_coarse_tmr()...\r\n");
    dhcp_coarse_tmr();
  }
}
#endif

// [netconf - LOG]

void dm9051_delay_in_core_process1(uint16_t nms) //finally, dm9051_lw.c
{
  #if 1
	printf("dm9051_driver setup delay %u ms..\r\n", nms);
	if (nms)
	  delay_ms(nms); //from James' advice! to be determined with a reproduced test cases!!
  #endif
}

void reset_change_timeouts(void)
{
#if MQTT_DEBUG_SYS_TIMEOUTS_SHOW
#if LWIP_TESTMODE
	sys_print_timeouts_times0(sys_count_timeouts());
#endif
#endif
}

void onchange_timeouts_log(const char *headstr)
{
#if MQTT_DEBUG_SYS_TIMEOUTS_SHOW
#if LWIP_TESTMODE
	sys_print_timeouts_times1(headstr, sys_count_timeouts());
#endif
#endif
}
