//
// dm9051opts.c
//
#include "dm9051_lw.h"
#include "dm9051_lw_conf.h"
#include "developer_conf.h" 
#include "netconf.h"
#include "testproc/testproc_lw.h"

#if TEST_PLAN_MODE //TestMode
u8 gfirst_log[ETHERNET_COUNT];
#endif

void ethcnt_ifdiplay_iomode(void)
{
	int i;
	GpioDisplay();
	ethcnt_ifdiplay_chipmac();
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("iomode[%d] %s / value %02x\r\n", mstep_get_net_index(), dm9051opts_desciomode(), iomode()); //dm9051opts_iomode()
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("csmode[%d] %s\r\n", mstep_get_net_index(), dm9051opts_desccsmode());
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("bmcrmode[%d] %s\r\n", i, dm9051opts_descncrmode());
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("rx's mode[%d] %s\r\n", i, dm9051opts_descpromismode());
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("checksum[%d] %s / value %02x %s\r\n", i, dm9051opts_descrxmode_checksum_offload(), //~dm9051opts_desc_rxchecksum_offload(), 
				isrxmode_checksum_offload() ? RCSSR_RCSEN : 0,
				isrxmode_checksum_offload() ? "(RCSSR_RCSEN)" : " "); //is_dm9051opts_rxmode_checksum_offload ~is_dm9051opts_rxchecksum_offload
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("fcrmode[%d] %s / value %02x\r\n", i, dm9051opts_descflowcontrolmode(), 
				isflowcontrolmode() ? FCR_DEFAULT_CONF : 0); //(_dm9051optsex[mstep_get_net_index()]._flowcontrolmode)
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		uint8_t *macaddr;
		mstep_set_net_index(i);
		macaddr = lwip_get_mac_addresse1();
		printf("config tobe mac[%d] %02x%02x%02x%02x%02x%02x\r\n", i, macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);
	}

	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		EepromDisplay(i);
	}
	
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		printf("ip[%d] %"U16_F".%"U16_F".%"U16_F".%"U16_F"\r\n", i,
		  ip4_addr1_16(netif_ip4_addr(&xnetif[i])), 
		  ip4_addr2_16(netif_ip4_addr(&xnetif[i])),
		  ip4_addr3_16(netif_ip4_addr(&xnetif[i])), 
		  ip4_addr4_16(netif_ip4_addr(&xnetif[i])));
	}
}

void ethcnt_ifdiplay_chipmac(void)
{
	int i;
	//.bannerline();
	for (i = 0; i< ETHERNET_COUNT; i++) {
		uint8_t buf[6];
		mstep_set_net_index(i);
	
		//part par
		cspi_read_regs(DM9051_PAR, buf, 6, csmode()); //dm9051opts_csmode_tcsmode()
		printf("chip-bare-mac[%d] %02x%02x%02x%02x%02x%02x\r\n", i, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
	}
}

void ethcnt_ifdiplay(void)
{
#if 0
	int i;
	for (i = 0; i< ETHERNET_COUNT; i++) {
		mstep_set_net_index(i);
		NetifDisplay(i);
		EepromDisplay(i);
	}
	//NetifDisplay(0); // [log]
	//NetifDisplay(1); // [log]
#endif
}

void first_log_init(void)
{
#if TEST_PLAN_MODE
	int i;
	for (i = 0; i < ETHERNET_COUNT; i++)
		gfirst_log[i] = 1; //Can know the first time reset the dm9051 chip!
#endif
}

u8 first_log_get(int i)
{
	return gfirst_log[i];
}

void first_log_clear(int i)
{
	gfirst_log[i] = 0;
}
