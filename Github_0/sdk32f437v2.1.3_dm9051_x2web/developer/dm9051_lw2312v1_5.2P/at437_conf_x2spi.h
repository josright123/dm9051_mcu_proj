//
// at437_conf_x2spi.h //2.yc
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
#ifndef AT32F437xx
	/**/
	{
		//ethernet f413
		//ethernet f413 spi2(crm, gpio)
		"AT32F413 SPI2 ETHERNET, sck/mi/mo/cs pb13/pb14/pb15/pb12",
		{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
		{GPIOB, GPIO_PINS_13, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,    GPIO_PINSRC_NULL, GPIO_MUX_NULL},  //ISCK
		{GPIOB, GPIO_PINS_14, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMISO
		{GPIOB, GPIO_PINS_15, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMOSI
		
		{GPIOB, GPIO_PINS_12, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
		//{GPIOA, GPIO_PINS_4, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
	},
	{
		//ethernet f413
		//ethernet f413 spi2(crm, gpio)
		
		//"AT32F413 SPI1 ETHERNET, sck/mi/mo/cs pb2/pb0/pc4/pa6",
		"AT32F413 SPI1 ETHERNET, sck/mi/mo/cs pa5/pa6/pa7/pa4",
		
		{"SPI1", SPI1, CRM_SPI1_PERIPH_CLOCK},
		
		//{GPIOB, GPIO_PINS_2, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX, GPIO_PINSRC_NULL, GPIO_MUX_NULL},  //ISCK
		//{GPIOB, GPIO_PINS_0, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMISO
		//{GPIOC, GPIO_PINS_4, CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMOSI
		
		//{GPIOA, GPIO_PINS_6, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
		
		{GPIOA, GPIO_PINS_5, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX, GPIO_PINSRC_NULL, GPIO_MUX_NULL},  //ISCK
		//{GPIOA, GPIO_PINS_6, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMISO
		{GPIOA, GPIO_PINS_6, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_INPUT,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMISO
		{GPIOA, GPIO_PINS_7, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMOSI
		
		{GPIOB, GPIO_PINS_12, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
		//{GPIOA, GPIO_PINS_4, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
	},
#else
//#endif
//#ifdef AT32F437xx
	/**/
#if 1
	{
		//ethernet f437 spi2(crm, gpio)
		"AT32F437 SPI2 ETHERNET, sck/mi/mo/cs pd1/pc2/pd4/pd0",
		{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
		{GPIOD, GPIO_PINS_1, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE1, GPIO_MUX_6},   //ISCK
		{GPIOC, GPIO_PINS_2, CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE2, GPIO_MUX_5},	//IMISO
		{GPIOD, GPIO_PINS_4, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE4, GPIO_MUX_6},	//IMOSI
		{GPIOD, GPIO_PINS_0, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PD0) Test-ISP2 OK
	},
#endif
	{
		//ethernet f437 spi4(crm, gpio)
		"AT32F437 SPI4 ETHERNET, sck/mi/mo/cs pe2/pe5/pe6/pe4",
		{"SPI4", SPI4, CRM_SPI4_PERIPH_CLOCK},
		{GPIOE, GPIO_PINS_2, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE2, GPIO_MUX_5},   //ISCK
		{GPIOE, GPIO_PINS_5, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE5, GPIO_MUX_5},	//IMISO
		{GPIOE, GPIO_PINS_6, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	//IMOSI
		{GPIOE, GPIO_PINS_4, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PE4) Test-ISP4 OK
	},
	{
		//ethernet f437 spi2(crm, gpio)
		"AT32F437 SPI2 ETHERNET, sck/mi/mo/cs pd1/pc2/pd4/pd0",
		{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
		{GPIOD, GPIO_PINS_1, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE1, GPIO_MUX_6},   //ISCK
		{GPIOC, GPIO_PINS_2, CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE2, GPIO_MUX_5},	//IMISO
		{GPIOD, GPIO_PINS_4, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE4, GPIO_MUX_6},	//IMOSI
		{GPIOD, GPIO_PINS_0, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PD0) Test-ISP2 OK
	},
	{
		//ethernet f437 spi1(crm, gpio)
		"AT32F437 SPI1 ETHERNET, sck/mi/mo/cs pa5/pa6/pa7/pa15",
		{"SPI1", SPI1, CRM_SPI1_PERIPH_CLOCK},
		{GPIOA, GPIO_PINS_5, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE5, GPIO_MUX_5},   //ISCK
		{GPIOA, GPIO_PINS_6, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	//IMISO
		{GPIOA, GPIO_PINS_7, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE7, GPIO_MUX_5},	//IMOSI
		{GPIOA, GPIO_PINS_15, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PA15) Test-ISP1 OK
	},
#endif
};

#define dm9051optsex dm9051optsex_x2
const optsex_t dm9051optsex_x2[BOARD_SPI_COUNT] = {
	{
		FALSE, //_test_plan_log
		MBNDRY_BYTE, "MBNDRY_BYTE",
		//MBNDRY_WORD, "MBNDRY_WORD",
		//CS_LONG, "CS_LONG_MODE",
		CS_EACH, "CS_EACH_MODE",
		0, //phy27
		//0, "NCR Normal Mode", //vs. 1, "NCR_Test_mode"
		1, "NCR_Test_mode",
		0, "Normal RX Mode", //vs. 1, "Promiscous_RX_mode"
	},
	{
		FALSE, //_test_plan_log
		MBNDRY_BYTE, "MBNDRY_BYTE",
		CS_EACH, "CS_EACH_MODE",
		0, //phy27
		0, "NCR Normal Mode", //vs. 1, "NCR_Test_mode"
		0, "Normal RX Mode", //vs. 1, "Promiscous_RX_mode"
	},
	{
		FALSE, //_test_plan_log
		MBNDRY_WORD, "MBNDRY_WORD",
		CS_EACH, "CS_EASH_MODE",
		0, //phy27
		0, "NCR Normal Mode", //vs. 1, "NCR_Test_mode"
		0, "Normal RX Mode", //vs. 1, "Promiscous_RX_mode"
	},
};

//[lw.set]
#define dm9051optsex_testplanlog()		dm9051optsex[pin_code].test_plan_log
#define dm9051optsex_iomode()			dm9051optsex[pin_code].iomode
#define dm9051optsex_desciomode()		dm9051optsex[pin_code].desciomode
#define dm9051optsex_longcsmode()		dm9051optsex[pin_code].longcsmode
#define dm9051optsex_desccsmode()		dm9051optsex[pin_code].desccssmode
#define dm9051optsex_ncrmode()			dm9051optsex[pin_code].ncrmode
#define dm9051optsex_descncrmode()		dm9051optsex[pin_code].descncrmode
#define dm9051optsex_promismode()		dm9051optsex[pin_code].promismode
#define dm9051optsex_descpromismode()	dm9051optsex[pin_code].descpromismode

//[common.macro]
//
// 'pin_code' always 0. when ETHERNET_COUNT==1, but _BOARD_SPI_COUNT > 1.
//
int pin_code = 0;
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
