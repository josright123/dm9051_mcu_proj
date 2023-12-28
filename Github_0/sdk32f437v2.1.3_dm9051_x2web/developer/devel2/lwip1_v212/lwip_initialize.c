#include "netconf.h"
#include "tmr_init.h" //"gadge/dm9051_env_lw.h"
#include "main_malloc.h"
int n_verify_id = 0;

void lwip_initialize(void)
{
  int i;
  #define PROGRAMMER_TEST_LEN	MMALLOC_MAX_LEN //3KB --> 1kb
  /* Initialize the LwIP stack */
  printf(": lwip_init()\r\n");
  char *prefix_str = (char *) malloc(PROGRAMMER_TEST_LEN); //3KB
  printf(".###. %d/%d init!! [ %lx = malloc( %d ) for startup test for a reference can according to]\r\n", 0, 0, prefix_str, PROGRAMMER_TEST_LEN);
  sprintf(prefix_str, "%d/%d init>>", 0, 0);
  
  lwip_init(); //.SUIT FOR SHARED
	
  for (i = 0; i < ETHERNET_COUNT; i++) {
	mstep_set_net_index(i);
    tcpip_stack_init();
  }
  
	#if NON_CHIPID_STOP == 1
	if (n_verify_id != ETHERNET_COUNT) {
		printf("Chip ID CHECK experiment! Fail!!\r\n");
		printf("while(1)\r\n");
		while(1) ; //Feature attribute experiment!!
	}
	#endif
	#if VER_CHIPID_ONLY
	printf("Chip ID CHECK experiment! Succeed OK\r\n");
	printf("while(1)\r\n");
	while(1) ; //Feature attribute experiment!!
	#endif
	
  at32_dm9051_tmr_init();
  printf(".###. %s [free( %lx ), for startup test for a reference can according to]\r\n", prefix_str, prefix_str);
  free(prefix_str);
}
