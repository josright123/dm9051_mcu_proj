#include "dm9051_lw.h"
#include "dm9051_lw_conf.h"
#include "lwip/apps/httpd.h"

#include "developer_conf.h"
#include "netconf.h"
#include "testproc/testproc_lw.h"
#include "main_malloc.h"

static void proc_run_init(void)
{
  int i;
  mqtt_client_init_log();
	
  for (i = 0; i < ETHERNET_COUNT; i++) {
	  mstep_set_net_index(i);
		
	  printf("[i= %d INIT-NOW] working for pin_code: %d\r\n", i, mstep_get_net_index());

	  //.tcpip_stack_init();
	  //.dm9051_tmr_init(); //delay_ms(30);
	  //.mqtt_client_process_init();

	  if (linkhandler_type() == TYPE_TIMEROUTS)
		  netlink_init();
  }

  //. mqtt_client_init_log(i);
  
  reset_change_timeouts(); //SHARED. //make below _log has no print-out!
  onchange_timeouts_log("main-init"); //SHARED.

  httpd_init(); //CAN BE SHARED. AS FOR BOTH xnetif[] ?
  
  //debug_dynamic_page();
  //.printf("httpd_init() finish\r\n"); 
}

static void proc_run_handler(int i) //HOW i can suit for!
{
	#if 1
		lwip_rx_hdlr(i);
		  
		//#if (APP_ETH_COUNT > 1) 
		//	mstep_next_net_index(); //next_pin_code();
		//#endif
	#else
		lwip_rx_loop_handler(); /* lwip receive handle */
	#endif
}

void proc_runs(void)
{
  int c = 0;
  proc_run_init();
  bannerline();

  for(;;)
  {
	    int i;
		/*
		for (i = 0; i < ETHERNET_COUNT; i++) {
			mstep_set_net_index(i);
			proc_run_handler(i); //PARAM i
			lwip_periodic_handle(); //THE EACH, //timeout handle
		}*/
		
		i = 0;
		mstep_set_net_index(i);
		proc_run_handler(i); //PARAM i
		lwip_periodic_handle(); //THE EACH, /*timeout handle*/

		threads_support();
	    if (c < 12) {
			#define PROGRAMMER_TEST_LEN	MMALLOC_MAX_LEN1 //3KB --> 1kb
			c++;
			if (c == 12) {
				char *prefix_str = (char *) malloc(PROGRAMMER_TEST_LEN); //3KB
				printf("  .###. %d/%d main-loop!!@%d [ %lx = malloc( %d ) in looping test for a reference can according to]\r\n", 1, 1, c, prefix_str, PROGRAMMER_TEST_LEN);
				sprintf(prefix_str, "%d/%d main-loop>>", 1, 1);
				printf("  .###. %s@%d [free( %lx ), for startup test for a reference can according to]\r\n", prefix_str, c, prefix_str);
				free(prefix_str);
			}
		}
  }
}
