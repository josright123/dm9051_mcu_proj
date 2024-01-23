//
// dm9051_lw_conf_at437x2spi.h //2.yc
//

#define board_conf_type	"\"dm9051_at32_mf\""
//1.const void *intr_pack = pdn; (without gpio)
//2.const void *intr_pack = pde; (with gpio)
//3.const void *intr_pack = NULL;
#define intr_pack	intr_pack_x2
const void *intr_pack_x2 = NULL;
//1.const gp_set_t *common_rst = NULL;
#define common_rst	common_rst_x2
const gp_set_t *common_rst_x2 = NULL; //&_pb8_rst_gpio_set;

#define devconf	devconf_XXXXXx2
const spi_dev_t devconf_XXXXXx2[BOARD_SPI_COUNT] = {
	#ifdef AT32F437xx
	#define devconf_at437_spi2(spi_setting_name) \
		{ \
			spi_setting_name, \
			{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK}, \
			{GPIOD, GPIO_PINS_1, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE1, GPIO_MUX_6},  /* //ISCK */ \
			{GPIOC, GPIO_PINS_2, CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE2, GPIO_MUX_5},	/* //IMISO */ \
			{GPIOD, GPIO_PINS_4, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE4, GPIO_MUX_6},	/* //IMOSI */ \
			{GPIOD, GPIO_PINS_0, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, /* //(PD0) Test-ISP2 OK */ \
		}
	#define devconf_at437_spi4(spi_setting_name) \
		{ \
			spi_setting_name, \
			{"SPI4", SPI4, CRM_SPI4_PERIPH_CLOCK}, \
			{GPIOE, GPIO_PINS_2, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE2, GPIO_MUX_5},   /* //ISCK */ \
			{GPIOE, GPIO_PINS_5, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE5, GPIO_MUX_5},	/* //IMISO */ \
			{GPIOE, GPIO_PINS_6, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	/* //IMOSI */ \
			{GPIOE, GPIO_PINS_4, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, /* //(PE4) Test-ISP4 OK */ \
		}
	#define devconf_at437_spi1(spi_setting_name) \
		{ \
			spi_setting_name, \
			{"SPI1", SPI1, CRM_SPI1_PERIPH_CLOCK}, \
			{GPIOA, GPIO_PINS_5, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE5, GPIO_MUX_5},   /* //ISCK */ \
			{GPIOA, GPIO_PINS_6, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	/* //IMISO */ \
			{GPIOA, GPIO_PINS_7, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE7, GPIO_MUX_5},	/* //IMOSI */ \
			{GPIOA, GPIO_PINS_15, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, /* //(PA15) Test-ISP1 OK */ \
		}
	devconf_at437_spi2("AT32F437 SPI2 ETHERNET, sck/mi/mo/cs pd1/pc2/pd4/pd0"),
	devconf_at437_spi4("AT32F437 SPI4 ETHERNET, sck/mi/mo/cs pe2/pe5/pe6/pe4"),
	devconf_at437_spi2("AT32F437 SPI2 ETHERNET, sck/mi/mo/cs pd1/pc2/pd4/pd0"),
	devconf_at437_spi1("AT32F437 SPI1 ETHERNET, sck/mi/mo/cs pa5/pa6/pa7/pa15"),
	#else
	#define devconf_at413_spi2(spi_setting_name) \
		{ \
			spi_setting_name, \
			{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK}, \
			{GPIOB, GPIO_PINS_13, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,    GPIO_PINSRC_NULL, GPIO_MUX_NULL},  /* //ISCK */ \
			{GPIOB, GPIO_PINS_14, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	/* //IMISO */ \
			{GPIOB, GPIO_PINS_15, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	/* //IMOSI */ \
			{GPIOB, GPIO_PINS_12, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, /* //(PB12) Test-ISP2 OK */ \
			/* {GPIOA, GPIO_PINS_4, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, (PB12) Test-ISP2 OK */ \
		}
	#define devconf_at413_spi1(spi_setting_name, gpport, pin, gpio_crm_clk) \
		{ \
			spi_setting_name, \
			{"SPI1",	SPI1,			CRM_SPI1_PERIPH_CLOCK}, \
			{GPIOA,		GPIO_PINS_5, 	CRM_GPIOA_PERIPH_CLOCK, 	GPIO_MODE_MUX, GPIO_PINSRC_NULL, GPIO_MUX_NULL},  /* //ISCK */ \
			{GPIOA,		GPIO_PINS_6, 	CRM_GPIOA_PERIPH_CLOCK, 	GPIO_MODE_INPUT,	GPIO_PINSRC_NULL, GPIO_MUX_NULL}, /* //IMISO */ \
			{GPIOA,		GPIO_PINS_7, 	CRM_GPIOA_PERIPH_CLOCK, 	GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL}, /* //IMOSI */ \
			/* {GPIOB,	GPIO_PINS_12,	CRM_GPIOB_PERIPH_CLOCK, 	GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK */ \
			/* {GPIOA,	GPIO_PINS_4,	CRM_GPIOA_PERIPH_CLOCK, 	GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, (PA4) Test-ISP2 OK */ \
			{gpport,	pin, 			gpio_crm_clk, 				GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, /* //(PA4) Test-ISP2 OK */ \
		}
	devconf_at413_spi2("AT32F413 SPI2 ETHERNET, sck/mi/mo/cs pb13/pb14/pb15/pb12"),
	devconf_at413_spi1("AT32F413 SPI1 ETHERNET, sck/mi/mo/cs pa5/pa6/pa7/pB12", GPIOB, GPIO_PINS_12, CRM_GPIOB_PERIPH_CLOCK),
	devconf_at413_spi1("AT32F413 SPI1 ETHERNET, sck/mi/mo/cs pa5/pa6/pa7/pa4", GPIOA, GPIO_PINS_4, CRM_GPIOA_PERIPH_CLOCK),
	#endif
};
	
#define dm9051optsex dm9051optsex_x2
optsex_t dm9051optsex_x2[BOARD_SPI_COUNT] = { //const 
	#define dmopts_normal(iomode, iomode_name) \
		{ \
			/* .set_name */ \
			iomode_name, \
			/* .test_plan_log */ \
			TRUE, /*FALSE,*/ \
			/* //vs MBNDRY_BYTE, "8-bit",/ MBNDRY_WORD, "16-bit",*/ \
			iomode, iomode_name, \
			/* //vs CS_EACH, "CS_EACH_MODE",/ CS_LONG, "CS_LONG_MODE",*/ \
			CS_EACH, "CS_EACH_MODE", \
			/* //phy27 */ \
			/* 0, */ \
			/* //vs. NCR_RST_DEFAULT, "NCR PwrOnRst-Default Mode",/ NCR_FORCE_100MF, "NCR_Force_100MF_mode"/ NCR_AUTO_NEG, "NCR_Auto_Negotiation_mode"*/ \
			NCR_FORCE_100MF, "NCR_Force_100MF_mode", /*NCR_RST_DEFAULT, "NCR PwrOnRst-Default Mode",*/ /*NCR_AUTO_NEG, "NCR_Auto_Negotiation_mode",*/ \
			/* //vs. 0, "Normal RX Mode",/ 1, "RX_Promiscuos_mode"*/ \
			0, "Normal RX Mode", \
			/* //vs. FALSE, "Checksum offload disable",/ TRUE, "checksum offload enable",*/ \
			TRUE, "rxmode checksum offload enable", \
			/* //vs. FALSE, "Flow control disable",/ TRUE, "Flow control enable",*/ \
			TRUE, "Flow control enable", \
		}
	#define dmopts_normal_1(iomode, iomode_name) \
		{ \
			/* .set_name */ \
			iomode_name, \
			/* //.test_plan_log */ \
			FALSE, \
			/* //vs MBNDRY_BYTE, "8-bit",/ MBNDRY_WORD, "16-bit",*/ \
			iomode, iomode_name, \
			/* //vs CS_EACH, "CS_EACH_MODE",/ CS_LONG, "CS_LONG_MODE", */ \
			CS_LONG, "CS_LONG_MODE", /*CS_EACH, "CS_EACH_MODE",*/ \
			/* 0, */ /* //phy27 */ \
			/* //vs. NCR_RST_DEFAULT, "NCR PwrOnRst-Default Mode",/ NCR_FORCE_100MF, "NCR_Force_100MF_mode"/ NCR_AUTO_NEG, "NCR_Auto_Negotiation_mode" */ \
			NCR_FORCE_100MF, "NCR_Force_100MF_mode", \
			/* //vs. 0, "Normal RX Mode",/ 1, "RX_Promiscuos_mode" */ \
			0, "Normal RX Mode", \
			/* //vs. FALSE, "Checksum offload disable",/ TRUE, "checksum offload enable", */ \
			TRUE, "rxmode checksum offload enable", \
			/* //vs. FALSE, "Flow control disable",/ TRUE, "Flow control enable", */ \
			TRUE, "Flow control enable", \
		}
	#define dmopts_test1(iomode, iomode_name) \
		{ \
			/* .set_name */ \
			iomode_name, \
			/* //.test_plan_log */ \
			FALSE, \
			/* //vs MBNDRY_BYTE, "8-bit",/ MBNDRY_WORD, "16-bit",*/ \
			iomode, iomode_name, \
			/* //vs CS_EACH, "CS_EACH_MODE",/ CS_LONG, "CS_LONG_MODE", */ \
			CS_EACH, "CS_EASH_MODE", \
			/* 0, */ /* //phy27 */ \
			/* //vs. NCR_RST_DEFAULT, "NCR PwrOnRst-Default Mode",/ NCR_FORCE_100MF, "NCR_Force_100MF_mode"/ NCR_AUTO_NEG, "NCR_Auto_Negotiation_mode" */ \
			NCR_AUTO_NEG, "NCR_Auto_Negotiation_mode", \
			/* //vs. 0, "Normal RX Mode",/ 1, "RX_Promiscuos_mode" */ \
			0, "Normal RX Mode", \
			/* //vs. FALSE, "Checksum offload disable",/ TRUE, "checksum offload enable", */ \
			TRUE, "rxmode checksum offload enable", \
			/* //vs. FALSE, "Flow control disable",/ TRUE, "Flow control enable", */ \
			TRUE, "Flow control enable", \
		}
	dmopts_normal_1(MBNDRY_BYTE, "8-bit"), //(MBNDRY_BYTE, "8-bit mode"),
	dmopts_normal(MBNDRY_BYTE, "8-bit"),
	dmopts_test1(MBNDRY_WORD, "16-bit mode"),
};

//
// 'pin_code' always 0. when ETHERNET_COUNT==1, but _BOARD_SPI_COUNT > 1.
//
int pin_code = 0;

//[lw.set]
//#define set_dm9051optsex_testplanlog(tlog)	dm9051optsex[pin_code].test_plan_log = tlog
//#define get_dm9051optsex_testplanlog()		dm9051optsex[pin_code].test_plan_log

#if 0
/*#define dm9051optsex_iomode()				dm9051optsex[pin_code].iomode
uint8_t dm9051opts_iomode(void)
{
	return dm9051optsex_iomode(); //dm9051optsex[pin_code].iomode;
}

#define dm9051optsex_desciomode()			dm9051optsex[pin_code].desciomode
char *dm9051opts_desciomode(void)
{
	return dm9051optsex_desciomode();
}*/
#endif
#if 0
/*#define dm9051optsex_promismode()			dm9051optsex[pin_code].promismode
uint8_t dm9051opts_promismode(void) 
{
	return dm9051optsex_promismode();
}

#define dm9051optsex_descpromismode()		dm9051optsex[pin_code].descpromismode
char *dm9051opts_descpromismode(void)
{
	return dm9051optsex_descpromismode();
}*/
#endif

#if 0
/*#define dm9051optsex_longcsmode()			dm9051optsex[pin_code].longcsmode
csmode_t dm9051opts_csmode(void) {
	return dm9051optsex_longcsmode();
}

#define dm9051optsex_desccsmode()			dm9051optsex[pin_code].desclongcsmode
char *dm9051opts_desccsmode(void) {
	return dm9051optsex_desccsmode();
}

#define dm9051optsex_ncrmode()				dm9051optsex[pin_code].ncrforcemode
ncrmode_t dm9051opts_ncrforcemode(void) {
	return dm9051optsex_ncrmode();
}

#define dm9051optsex_descncrmode()			dm9051optsex[pin_code].descncrmode
char *dm9051opts_descncrmode(void) {
	return dm9051optsex_descncrmode();
}*/
#endif

//confirm_state is_dm9051opts_rxmode_checksum_offload(void) //~is_dm9051opts_rxchecksum_offload(void)
//{
//	return dm9051optsex[mstep_get_net_index()].rxmode_checksum_offload;
//}

//char *dm9051opts_desc_rxchecksum_offload(void)
//{
//	return dm9051optsex[mstep_get_net_index()].descrxmode_checksum_offload;
//}

//confirm_state is_dm9051opts_flowcontrolmode(void)
//{
//	return dm9051optsex[mstep_get_net_index()].flowcontrolmode;
//}

//char *dm9051opts_descflowcontrolmode(void)
//{
//	return dm9051optsex[mstep_get_net_index()].descflowcontrolmode;
//}

DECL_SG_FUNCTION(confirm_state, test_plan_log)

//#define CSMODE_T_DECL_FUNCTION(field) \
//	DECL_FUNCTION(csmode_t, field)
//#define NCRMODE_T_DECL_FUNCTION(field) \
//	DECL_FUNCTION(ncrmode_t, field)

DECL_FUNCTION(uint8_t, iomode)
DECL_FUNCTION(uint8_t, promismode)

//CSMODE_T_DECL_FUNCTION(csmode)
//NCRMODE_T_DECL_FUNCTION(ncrmode)
DECL_FUNCTION(csmode_t, csmode)
DECL_FUNCTION(ncrmode_t, ncrmode)

//#define CONFIRM_STATE_DECL_FUNCTION(field) \
//	DECL_FUNCTION(confirm_state, field)
	
//CONFIRM_STATE_DECL_FUNCTION(rxmode_checksum_offload)
//CONFIRM_STATE_DECL_FUNCTION(flowcontrolmode)
DECL_FUNCTION(confirm_state, rxmode_checksum_offload)
DECL_FUNCTION(confirm_state, flowcontrolmode)

//[common.macro]
#define gpio_wire_sck()				devconf[pin_code].wire_sck 
#define gpio_wire_mi()				devconf[pin_code].wire_mi
#define gpio_wire_mo()				devconf[pin_code].wire_mo
#define gpio_cs()					devconf[pin_code].wire_cs
#define spihead()					devconf[pin_code].spidef
#define intr_data()					((struct modscfg_st *)intr_pack) //((intr_param_t *)intr_pack)
#define intr_data_scfg()			(((struct modscfg_st *)intr_pack)->extend) //(((intr_param_t *)intr_pack)->scfg)

#define intr_gpio_data()			((gp_set_t *)intr_data()->option)
#define intr_gpio_exister()			(intr_pack) ? intr_data()->option ? 1 : 0 : 0 //(!intr_pack) ? 0 : (intr_data()->scfg.next_avail == NEXT_AVAILABLE) ? 1 : 0

#define exint_scfg_exister()		(intr_pack)
#define exint_scfg_ptr()			(!intr_pack) ? NULL : intr_data()->extend //(!intr_pack) ? NULL : &(intr_data()->scfg)
#define scfg_info()					(intr_data()->scfg_inf)
#define scfg_crm()					(intr_data()->scfg_init.scfg_clk)
#define scfg_port()					(intr_data()->scfg_init.scfg_port_src)
#define scfg_pin()					(intr_data()->scfg_init.scfg_pin_src)
#define rst_gpio_data()				(common_rst)

#define cpuhead()					devconf[pin_code]
#define cpu_spi_conf_name()			cpuhead().cpu_api_info
#define spi_number()				spihead().spi_num //= spi_no()
#define spi_crm()					spihead().spi_crm_clk
#define spi_conf_name()				spihead().spi_name

#define exint_enable_info()			(intr_data_scfg()->irq_enable_inf)
#define exint_extline()				(intr_data_scfg()->extline.extline)
#define exint_crm()					(intr_data_scfg()->extline.intr_crm_clk)
#define intr_gpio_info()			(intr_gpio_data()->gp_info)
#define intr_gpio_ptr()				((const gpio_t *)(&intr_gpio_data()->gp))

#define rst_gpio_info()				(rst_gpio_data()->gp_info)
#define rst_gpio_ptr()				((const gpio_t *)(&rst_gpio_data()->gp))
#define rst_gpio_exister()			(rst_gpio_data() ? 1 : 0)
//#define rst_gpio_info()			(intr_gpio_data()->gp_info)
//#define rst_gpio_ptr()			&(intr_gpio_data()->gp)

#define mstep_set_index(i)			pin_code = i //empty for 1 eth project
#define mstep_turn_net_index()		//empty for 1 eth project

//-
#define mstep_get_index()			pin_code
//#define _mstep_get_net_index()	pin_code
//#define spi_dev()					&devconf

//-

//void set_dm9051opts_testplanlog(confirm_state test_log)
//{
//	set_dm9051optsex_testplanlog(test_log);
//}

//-

//confirm_state get_dm9051opts_testplanlog(void)
//{
//	return get_dm9051optsex_testplanlog();
//}

//-

void mstep_set_net_index(int i)
{
	mstep_set_index(i); //pinCode = i;
}

int mstep_get_net_index(void)
{
	return mstep_get_index();
}

void mstep_next_net_index(void)
{
	mstep_turn_net_index();
}

char *mstep_spi_conf_name(void)
{
	return spi_conf_name();
}

char *mstep_conf_cpu_spi_ethernet(void)
{
	return cpu_spi_conf_name();
}

char *mstep_conf_type(void)
{
	return board_conf_type;
}

//int mstep_conf_spi_count(void)
//{
//	return _BOARD_SPI_COUNT;
//}

//-
//-

int is_dm9051_board_irq(void)
{
	const struct extscfg_st *pexint_set = (const struct extscfg_st *) exint_scfg_ptr();
	return pexint_set ? 1 : 0;
}

int intr_gpio_exist(void) {
	return intr_gpio_exister();
}

static int rst_pin_exister(void) {
	return rst_gpio_exister();
}

static int intr_gpio_mptr(void) {
	if (intr_gpio_exist()) {
		printf(": %s :                 intr-pin/ %s\r\n", "config", intr_gpio_info()); //_intr_gpio_exist()->gp_info
		return 1;
	}
	return 0;
}

static int rst_pin_mexist(void) {
	if (rst_pin_exister()) {
		printf(": %s :                 rst-pin/ %s\r\n", "config", rst_gpio_info());
		return 1;
	}
	return 0;
}

// -

void GpioDisplay(void)
{
  int i;

//#if (_ETHERNET_COUNT >= 2)
//do {
  for (i = 0; i < ETHERNET_COUNT; i++) {
	mstep_set_net_index(i);
	printf("@ETHERNET INTERFACE        %s\r\n", mstep_conf_cpu_spi_ethernet());
  }
  //mstep_set_net_index(0);
//} while(0);
//#elif (_ETHERNET_COUNT == 1)
//  printf("@ETHERNET INTERFACE      %s\r\n", mstep_conf_cpu_spi_ethernet());
//#endif
}

/*********************************
 * config parameters accessing 
 *********************************/

//spi_type *spi_no(void)
//{
//	return spi_number(); //return spi_port(_pinCode).spi_num; //return spi_type_no(_pinCode);
//}

//static int exint_conf_mptr(void) {
//	if (_exint_conf_ptr()) {
//		printf(": %s :                 exint-irq, pexint_set\r\n", "config");
//		return 1;
//	}
//	return 0;
//}

//int intr_pin_exister(void) {
//	return _intr_gpio_exist() ? 1 : 0;
//}
