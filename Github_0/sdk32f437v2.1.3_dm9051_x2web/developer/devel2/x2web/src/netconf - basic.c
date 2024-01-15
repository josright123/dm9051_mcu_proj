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
//#include "lwip/netif.h"
//#include "at32f435_437_board.h" //""at32f413_board.h" //#include "at32f415_board.h"
//#include "at32_cm4_device_support.h" //#include "at32f415.h" //"at32f435_437.h" //"at32f413.h" //"at32f435_437_board.h"
//#include "stdio.h"
#include "dm9051_lw.h"
#include "dm9051_lw_conf.h"
#include "ethernetif.h"
#include "developer_conf.h" //#include "main.h" //#include "developer_conf.h"
//#include "_dm9051_at32_conf.h" //"dm9051_env.h" //"dm9051f_netconf.h" //"at32_emac.h" //has #include "dm9051_lw.h"
//#include "dm9051_spi_sync.h"
//#include "dm9051_at32_decl.h" 
#include "netconf.h" //has #include "ethernetif.h"
#include "testproc/testproc_lw.h"
#include <string.h>

#ifndef DM9051_DIAG
#define DM9051_DIAG(x) do {printf x;} while(0)
#include <stdio.h>
#include <stdlib.h>
#endif

#define DM9051_RX_DBGMSG(expression, message) do { if ((expression)) { \
  DM9051_DIAG(message);}} while(0)

struct netif xnetif[ETHERNET_COUNT]; //struct netif netif;
net_t *s__net_instance[ETHERNET_COUNT]; //net_t*

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

int testing_rx_count = 0;

err_t checksum_check_rxhdlr(int i) //lwip_rx_hdlr(void)
{
  //err_t err;
//#if TEST_PLAN_MODE
//  if (!check_get()) //!checkrxbcount
//	  return ERR_INPROGRESS;
//#endif

  //err = 
  //return ethernetif_inp(&xnetif[i]);
	
	  //struct pbuf *p = low_level_inp(netif);
	  //if (p == NULL) 
	  //	return ERR_INPROGRESS; //JJ.
	  //pbuf_free(p);
	  
	  uint8_t *buffer = get_rx_buffer(); //&EthBuff[0].rx;
	  uint16_t len = dm9051_rx(buffer);
	  if (!len)
		  return ERR_INPROGRESS;
	  
	  //testing_rx_count++;
	  dm9051_rxlog_monitor_rx_all(2, buffer, len); //dm9051_rxlog_monitor_rx();
	  
	  return ERR_OK;
	
//DM9051_RX_DBGMSG(err != ERR_OK && err != ERR_INPROGRESS, ("[netconf.c] ethernetif_input: IP input error\r\n"));
  //return err;
}

err_t do_checksum_check_rxhdlr(void) //lwip_rx_hdlr(void)
{
  int i = mstep_get_net_index();;
  return checksum_check_rxhdlr(i);
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

static
void op_link_timer(net_t *net) {
  #define CARRY_NUM 3 //5 //7
  static int xcarry[ETHERNET_COUNT] = { 0, 0 };
  static volatile uint8_t first_2rst_timer1500_2cnnt2initpub = 1;
  //.static volatile uint8_t first_timer_coerce2lnk = 1; /* #if 0/#endif, Global assurance */
  int pin;
  uint16_t bmsr;
  uint8_t chip_link_up; //= (uint8_t) dm9051_link_update_dual(); //.dm9051_link_update();

  pin = mstep_get_net_index(); //= net->netif_pin_code;
  bmsr = dm9051_bmsr_update();
  chip_link_up = bmsr & 0x0004;

do {
	static int xc[ETHERNET_COUNT] = { 0, 0 };
	
	//operation_to[pin]
	
	if (!netif_is_link_up(&xnetif[pin])) {
		if (xcarry[pin] < CARRY_NUM) {
			xc[pin]++;
			if (xc[pin] == 1) {
				xcarry[pin]++;
				if (xcarry[pin] == CARRY_NUM) {
					//'chip_link_up' always should be down!?
					//printf("&xnetif[%d] %s, %"U16_F".%"U16_F".%"U16_F".%"U16_F" (%s/ %02d.times_link_state %s dm9051[%d])\r\n", 
						//pin, /*xcarry[pin],*/ chip_link_up ? "up" : "down",
						//ip4_addr1_16(netif_ip4_addr(&xnetif[pin])), 
						//ip4_addr2_16(netif_ip4_addr(&xnetif[pin])),
						//ip4_addr3_16(netif_ip4_addr(&xnetif[pin])), 
						//ip4_addr4_16(netif_ip4_addr(&xnetif[pin])),
						//chip_link_up ? "NET_LINK_UP" : "NET_LINK_DOWN",
						//CARRY_NUM, chip_link_up ? "link up" : "link down", pin);
					//printf("dm9051[%d] down, %"U16_F".%"U16_F".%"U16_F".%"U16_F" (times.%02d bmsr %04x)\r\n",
						//pin,
						//ip4_addr1_16(netif_ip4_addr(&xnetif[pin])), 
						//ip4_addr2_16(netif_ip4_addr(&xnetif[pin])),
						//ip4_addr3_16(netif_ip4_addr(&xnetif[pin])), 
						//ip4_addr4_16(netif_ip4_addr(&xnetif[pin])),
						//xcarry[pin], bmsr);
					printf("dm9051[%d] link down\r\n", pin);
					waitdone_set_true(pin);
					//.NO NEED.
					//.net->cbf(net, net->net_arg, NET_LINK_DOWN);
					first_2rst_timer1500_2cnnt2initpub = 0;
				}
				else
					printf("&xnetif[%d][%02d] bmsr %04x\r\n", pin, xcarry[pin], bmsr);
			}
			if (xc[pin] == 30)
				xc[pin] = 0;
		}
	} else {
		xc[pin] = 0;
		xcarry[pin] = 0;
	}
} while(0);

  if(!netif_is_link_up(&xnetif[pin]))
  {
	if (!chip_link_up)
		tpp_refine_linkdown_progress();
    if (chip_link_up) {
		//#if LINK_DETECTION_TCK_IMPL
		if (linkhandler_type() == TYPE_TICKS) {
			if (!tp_all_done())
				linkup_spring_cb(NULL, NULL, NET_LINK_UP);
			else
				linkup_re_cb(NULL, NULL, NET_LINK_UP); /*net->net_cb*/ 
		//#endif
		//#if LINK_DETECTION_NET_IMPL
		} else if (linkhandler_type() == TYPE_TIMEROUTS) {
			//printf("&xnetif[%d] up, %"U16_F".%"U16_F".%"U16_F".%"U16_F" (%s/ real.linkup dm9051[%d])\r\n",
				//pin, //xcarry[pin],
				//ip4_addr1_16(netif_ip4_addr(&xnetif[pin])), 
				//ip4_addr2_16(netif_ip4_addr(&xnetif[pin])),
				//ip4_addr3_16(netif_ip4_addr(&xnetif[pin])), 
				//ip4_addr4_16(netif_ip4_addr(&xnetif[pin])),
				//"NET_LINK_UP", pin);
			xcarry[pin] = 0; //[for print-log below,]
			printf("dm9051[%d] up, %"U16_F".%"U16_F".%"U16_F".%"U16_F" (times.%02d bmsr %04x)\r\n",
				pin,
				ip4_addr1_16(netif_ip4_addr(&xnetif[pin])), 
				ip4_addr2_16(netif_ip4_addr(&xnetif[pin])),
				ip4_addr3_16(netif_ip4_addr(&xnetif[pin])), 
				ip4_addr4_16(netif_ip4_addr(&xnetif[pin])),
				xcarry[pin], bmsr);
			net->cbf(net, net->net_arg, NET_LINK_UP);
		}
		//#endif
		//.first_timer_coerce2lnk = 0;
    }
    if (chip_link_up && first_2rst_timer1500_2cnnt2initpub == 0) {
#if (LWIP_TESTMODE == 0)
		//first_link_coerce_timer_trigger:
		ethernetif_reset_proc(); //dm9051_reset_process();
#endif
		first_2rst_timer1500_2cnnt2initpub = 1;
    }
  }
  else if (netif_is_link_up(&xnetif[pin]))
  {
	if (chip_link_up)
		tpp_refine_linkup_progress();
	/*if (!chip_link_up) //This is such as unplug CAT5-45J */ 
	else {
		//#if LINK_DETECTION_TCK_IMPL
		if (linkhandler_type() == TYPE_TICKS) {
			if (!tp_all_done())
				linkup_spring_cb(NULL, NULL, NET_LINK_DOWN);
			else
				linkup_re_cb(NULL, NULL, NET_LINK_DOWN); /*net->net_cb*/ 
		//#endif
		//#if LINK_DETECTION_NET_IMPL
		} else if (linkhandler_type() == TYPE_TIMEROUTS) {
			printf(" ...[%d] down\r\n", pin);
			//printf("&xnetif[%d] down, bmsr %04x\r\n", pin, bmsr);
			net->cbf(net, net->net_arg, NET_LINK_DOWN);
		}
		//#endif
		//.first_timer_coerce2lnk = 0;
		first_2rst_timer1500_2cnnt2initpub = 0;
	}
  }
  
 #if 0
  if (first_timer_coerce2lnk) { //"startup_linkdown_process"
	first_timer_coerce2lnk++;
	if (first_timer_coerce2lnk > ((1500 / get_link_handler_ms()) + 1)) { //add 1 for later a little.
		//#if LINK_DETECTION_TCK_IMPL
		if (linkhandler_type() == TYPE_TICKS) {
			if (!tp_all_done())
				linkup_spring_cb(NULL, NULL, chip_link_up ? NET_LINK_UP : NET_LINK_DOWN);
			else
				linkup_re_cb(NULL, NULL, chip_link_up ? NET_LINK_UP : NET_LINK_DOWN);
		//#endif
		//#if LINK_DETECTION_NET_IMPL
		} else if (linkhandler_type() == TYPE_TIMEROUTS) {
			printf("&xnetif[%d] %s, %"U16_F".%"U16_F".%"U16_F".%"U16_F" (%s/ 1500.link_state %s dm9051[%d])\r\n", 
				pin, /*xcarry[pin],*/ chip_link_up ? "up" : "down",
				ip4_addr1_16(netif_ip4_addr(&xnetif[pin])), 
				ip4_addr2_16(netif_ip4_addr(&xnetif[pin])),
				ip4_addr3_16(netif_ip4_addr(&xnetif[pin])), 
				ip4_addr4_16(netif_ip4_addr(&xnetif[pin])),
				chip_link_up ? "NET_LINK_UP" : "NET_LINK_DOWN",
				chip_link_up ? "link up" : "link down", pin);
			net->cbf(net, net->net_arg, chip_link_up ? NET_LINK_UP : NET_LINK_DOWN);
		}
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
 #endif

  #if MQTT_CLIENT_SUPPORT
  mqttc_goto_connect(&xnetif[pin], MY_PHY_LINKUP); /* bedo-once, Once relate to 'netif_is_link_up()' */
  mqttc_connect();
  #endif
}

/*static*/ 
void phy_link_timer(void *arg) //=to_time_link() (are to phase-out, BUT keep called API-exist.)
{
  int pinsave = mstep_get_net_index(); //HERE save: pin = mstep_get_net_index();
  mstep_set_net_index(((net_t *)arg)->netif_pin_code); //HERE SET: mstep_set_net_index(x);
	
  op_link_timer(arg); //.op_link_timer(pincode, net);
	
  if (linkhandler_type() == TYPE_TIMEROUTS)
	sys_timeout(get_link_handler_ms(), phy_link_timer, arg);

  onchange_timeouts_log("in-phy_link_timer");
  mstep_set_net_index(pinsave); //HERE restore: pin = mstep_get_net_index();
}

void linkup_spring_cb(net_t *net, void *arg, u8_t status) {
  int pin = mstep_get_net_index();
  if (status == NET_LINK_UP) {
	tpp_set_linkup_stage(); //gtestproc_stage = _TST_LINKUP_FOUND;
	if (tpp_get_link_state()) {
	  printf("dm9051[%d] link up\r\n", pin);
	  waitdone_set_true(pin);
	}
	
	//netif_set_link_up(&xnetif[pin]); //netif_set_link_up_INITAndTimer(&netif);
	//part of: ==
	if (!(xnetif[pin].flags & NETIF_FLAG_LINK_UP)) //=NETIF_FLAG_LINK_UP=0x04U
	  netif_set_flags(&xnetif[pin], NETIF_FLAG_LINK_UP);
  }
  if (status == NET_LINK_DOWN) {
  #if LWIP_TESTMODE // && LWIP_TESTMODE_REAL
	if (!tp_all_done()) {
		display_state();
		tpp_set_linkdown_stage();
		if (!tpp_recognized_stage())
		  printf("dm9051_spring_testt[%d] link down\r\n", pin);
	}
  #endif
	//netif_set_link_down(&xnetif[pin]); //netif_set_link_down_Timer(&netif);
	//part of: =
	if (xnetif[pin].flags & NETIF_FLAG_LINK_UP)
	  netif_clear_flags(&xnetif[pin], NETIF_FLAG_LINK_UP);
  }
}

void linkup_re_cb(net_t *net, void *arg, u8_t status) {
  int pin = mstep_get_net_index(); //xxx = arg; NULL;
	
  if (status == NET_LINK_UP) {
	tpp_set_linkup_stage(); //gtestproc_stage = _TST_LINKUP_FOUND;
	if (tpp_get_link_state()) {
	  printf("dm9051[%d] link up\r\n", pin);
	}
	
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
   #if LWIP_TESTMODE // && LWIP_TESTMODE_REAL
	if (!tp_all_done()) {
		display_state();
		tpp_set_linkdown_stage();
		if (!tpp_recognized_stage())
		  printf("dm9051_re_testt[%d] link down\r\n", pin);
	}
   #endif
	  
	netif_set_link_down(&xnetif[pin]); //netif_set_link_down_Timer(&netif);
	#if MQTT_CLIENT_SUPPORT
	mqttc_close(); //= _mqtt_close(client, MQTT_CONNECT_DISCONNECTED);
	#endif
  }
}

//#if LINK_DETECTION_NET
	//#if LINK_DETECTION_NET_IMPL
	static void net_new_task(net_t *net, net_link_cb_t cb, void *arg) //(void *arg)= NULL
	{	
	  net->netif_pin_code = mstep_get_net_index();
	  net->link_state = NET_LINK_DOWN; //net->cyclic_tick = 0;
	  net->net_arg = arg;
	  net->cbf = cb;
		
	  /* Start cyclic link_handle timer */
	  sys_timeout(get_link_handler_ms(), phy_link_timer, net); //(no sys_untimeout(), THIS IS FOREEVER LOOP CYCLE, such as 'link_handle()')
	}
	
	static void net_renew_task(net_t *net, net_link_cb_t cb) //(, void *arg)
	{
	  net->cbf = cb;
	}
	
	static int waitdone_flags[ETHERNET_COUNT] = { 0 };
	
	void waitdone_set_true(int i) {
		waitdone_flags[i] = 1;
	}
	
	void netlink_spring_wait(void)
	{
		//uint16_t bmsr = dm9051_bmsr_update();
		int i, loopf;
		uint16_t bmcr;
		printf("while(1), waiting...\r\n");
		for (i = 0; i < ETHERNET_COUNT; i++) {
			mstep_set_net_index(i);
			bmcr = phy_read(0);
			printf("bmcr[%d] bmcrmode by %s, is %04x\r\n", i, dm9051opts_descncrmode(), bmcr);
		}
		printf("while(1), waiting... has [%d %d]\r\n", waitdone_flags[0], waitdone_flags[1]); //temp
		do {
			threads_support();
			
			loopf = 0;
			for (i = 0; i < ETHERNET_COUNT; i++)
				if (!waitdone_flags[i])
					loopf = 1;
		} while(loopf);
		printf("while(1), waiting... done [%d %d]\r\n", waitdone_flags[0], waitdone_flags[1]); //temp
		for (i = 0; i < ETHERNET_COUNT; i++)
			if (netif_is_link_up(&xnetif[i]))
				printf("dm9051[%d]... is active and is available...\r\n", i); //temp
	}

	void netlink_spring_init(void) // (are to phase-in, NOW start API-skelton.)
	{
	  s__net_instance[mstep_get_net_index()] = (net_t *)mem_calloc(1, sizeof(net_t));
	  if (s__net_instance[mstep_get_net_index()] == NULL)
	  {
		printf("net: s__net_instance[i] malloc fail @@!!!\r\n");
		while(1);
	  }
	  //s__net_instance[i]->link_state = NET_LINK_DOWN;
	  net_new_task(s__net_instance[mstep_get_net_index()], linkup_spring_cb, NULL);
	}
	
	void netlink_reinit(void)
	{
	  net_renew_task(s__net_instance[mstep_get_net_index()], linkup_re_cb); //(, NULL)
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
#if APPLICATION_LWIP_PRINT_TIMEOUTS
	sys_print_timeouts_times1(headstr, sys_count_timeouts());
#endif
#endif
#endif
}
