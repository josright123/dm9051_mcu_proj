/*typedef enum {
	NEXT_NULL       = 0x00,
	NEXT_AVAILABLE  = 0x01
} next_ext_param;

struct scfg_st {
	const char *irq_enable_inf;	
	extline_t extline;
	const char *scfg_inf;	
	extint_init_t scfg_init;
	next_ext_param next_avail;
};

typedef struct {
	struct scfg_st scfg;
} intr_param_t;

typedef struct {
	struct scfg_st scfg;
	const char *gp_info;	//gpio-info
	const gpio_t gp;        //gpio-t
} intr_paramfull_t;*/

#if 0 //[Test]
	typedef struct spi_pack_st {
		char *cpu_api_info;	//cpu name is for the purpose to lead the pins, for easy recogition!
		spihead_t spidef;
		gpio_t wire_sck;
		gpio_t wire_mi;
		gpio_t wire_mo;
		gpio_t wire_cs;
	} spi_pack_t;

	#ifndef AT32F437xx
	const spi_pack_t spi2_pack_f413 = {
		//ethernet f413 spi2(crm, gpio)
		"AT32F413 SPI2 ETHERNET, sck/mi/mo/cs pb13/pb14/pb15/pb12",
		{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
		{GPIOB, GPIO_PINS_13, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,    GPIO_PINSRC_NULL, GPIO_MUX_NULL},  //ISCK
		{GPIOB, GPIO_PINS_14, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMISO
		{GPIOB, GPIO_PINS_15, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMOSI
		{GPIOB, GPIO_PINS_12, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
	};
	#define pack_decl	 spi2_pack_f413 
	const spi_pack_t spi2_pack_f437 = {
		//ethernet f437 spi2(crm, gpio)
		"AT32F437 SPI2 ETHERNET, sck/mi/mo/cs pd1/pc2/pd4/pd0",
		{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
		{GPIOD, GPIO_PINS_1, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE1, GPIO_MUX_6},   //ISCK
		{GPIOC, GPIO_PINS_2, CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE2, GPIO_MUX_5},	//IMISO
		{GPIOD, GPIO_PINS_4, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE4, GPIO_MUX_6},	//IMOSI
		{GPIOD, GPIO_PINS_0, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PD0) Test-ISP2 OK
	};
	const spi_pack_t spi4_pack_f437 = {
		//ethernet f437 spi4(crm, gpio)
		"AT32F437 SPI4 ETHERNET, sck/mi/mo/cs pe2/pe5/pe6/pe4",
		{"SPI4", SPI4, CRM_SPI4_PERIPH_CLOCK},
		{GPIOE, GPIO_PINS_2, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE2, GPIO_MUX_5},   //ISCK
		{GPIOE, GPIO_PINS_5, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE5, GPIO_MUX_5},	//IMISO
		{GPIOE, GPIO_PINS_6, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	//IMOSI
		{GPIOE, GPIO_PINS_4, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PE4) Test-ISP4 OK
	};
	const spi_pack_t spi1_pack_f437 = {
		//
		//ethernet f437 spi1(crm, gpio)
		"AT32F437 SPI1 ETHERNET, sck/mi/mo/cs pa5/pa6/pa7/pa15",
		{"SPI1", SPI1, CRM_SPI1_PERIPH_CLOCK},
		{GPIOA, GPIO_PINS_5, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE5, GPIO_MUX_5},   //ISCK
		{GPIOA, GPIO_PINS_6, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	//IMISO
		{GPIOA, GPIO_PINS_7, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE7, GPIO_MUX_5},	//IMOSI
		{GPIOA, GPIO_PINS_15, CRM_GPIOA_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PA15) Test-ISP1 OK
		//
		//ethernet f437 spi1(crm, gpio)
		"AT32F437 SPI1 ETHERNET, sck/mi/mo/cs pe13/pe14/pe15/pe12",
		{"SPI1", SPI1, CRM_SPI1_PERIPH_CLOCK},
		{GPIOE, GPIO_PINS_13, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE13, GPIO_MUX_4},   // o4 x5 x6 ISCK
		{GPIOE, GPIO_PINS_14, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	 GPIO_PINS_SOURCE14, GPIO_MUX_4},	// o4 x5 IMISO
		{GPIOE, GPIO_PINS_15, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	 GPIO_PINS_SOURCE15, GPIO_MUX_4},	// o4 x6 IMOSI
		{GPIOE, GPIO_PINS_12, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,   GPIO_MUX_NULL}, //(PE12) Test-ISP1 TEST
		//
	};
	#endif
#endif
	
#if 0
const static gp_set_t pb8_rst_gpio_set = { //(crm, gpio)
	"AT32 RST PAD, gpio pb8",
	{GPIOB, GPIO_PINS_8,  CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_OUTPUT, 	GPIO_PINSRC_NULL, GPIO_MUX_NULL,} //(PB8) RST-pin
};
//.const static common_rst_t common_rst = {
//.	&pb8_rst_gpio_set,
//.};
#endif

#if 0 //[not used this fieldes form which is "scfg_st".]
#if !defined(AT32F437xx)
const static struct extscfg_st pc7_intr = {
		"enable SCFG, extline pc7",
		{ CRM_GPIOC_PERIPH_CLOCK, EXINT_LINE_7, EXINT9_5_IRQn}, // correspond to and with PC7
		"AT32 SCFG, exint pc7",
		{ CRM_IOMUX_PERIPH_CLOCK, GPIO_PORT_SOURCE_GPIOC, GPIO_PINS_SOURCE7},
		//NEXT_NULL,
};
#endif
#endif

/* User_data 2
 */
 
#if 0
gp_set_t gp = {
	"AT32 INT PAD, gpio pc7",
	{GPIOC, GPIO_PINS_7,  CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_INPUT, 	GPIO_PINSRC_NULL, GPIO_MUX_NULL,}, //(PC7) INT-pin
};

struct extscfg_st pe = { //struct linescfg_st 
	"enable SCFG, extline pc7",
	{ CRM_GPIOC_PERIPH_CLOCK, EXINT_LINE_7, EXINT9_5_IRQn}, // correspond to and with PC7
};
struct modscfg_st pdn = {
	"AT32 SCFG, exint pc7",
	{ CRM_IOMUX_PERIPH_CLOCK, GPIO_PORT_SOURCE_GPIOC, GPIO_PINS_SOURCE7},
	&pe, //essential
	NULL,
};
struct modscfg_st pde = {
	"AT32 SCFG, exint pc7",
	{ CRM_IOMUX_PERIPH_CLOCK, GPIO_PORT_SOURCE_GPIOC, GPIO_PINS_SOURCE7},
	&pe, //essential
	&gp,
};
#endif

/*
//.!AT32F437xx
typedef struct ext_gpio_st {
	crm_periph_clock_type scfg_clk;
	gpio_port_source_type scfg_port_src;
	gpio_pins_source_type scfg_pin_src;
} ext_gpio_t;

//.AT32F437xx
typedef struct ext_scfg_st {
	crm_periph_clock_type scfg_clk;
	scfg_port_source_type scfg_port_src; //SCFG_PORT_SOURCE_X
	scfg_pins_source_type scfg_pin_src; //SCFG_PINS_SOURCEX
} ext_scfg_t;
*/	

//typedef struct gpio_set_st {
//	const gpio_t wire_descript;
//} gpio_set_t;

//.typedef struct {
//.  const gp_set_t *rst_gpio; //.  const gpio_set_t *rst_gpio_set;
//.} common_rst_t;
/* Single-SPI interface f413/f437
 */
 
/*#define board_conf_type "\"dm9051_at32_cf\""
const void *intr_pack = NULL;
const gp_set_t *common_rst = NULL; //&_pb8_rst_gpio_set;

#define devconf	devconf_XXX
const static spi_dev_t devconf_XXX = {
#if !defined(AT32F437xx)
	//ethernet f413
	//ethernet f413 spi2(crm, gpio)
	"AT32F413 SPI2 ETHERNET, sck/mi/mo/cs pb13/pb14/pb15/pb12",
	{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
	{GPIOB, GPIO_PINS_13, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,    GPIO_PINSRC_NULL, GPIO_MUX_NULL},  //ISCK
	{GPIOB, GPIO_PINS_14, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMISO
	{GPIOB, GPIO_PINS_15, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_MUX,	GPIO_PINSRC_NULL, GPIO_MUX_NULL},	//IMOSI
	{GPIOB, GPIO_PINS_12, CRM_GPIOB_PERIPH_CLOCK, GPIO_MODE_OUTPUT, GPIO_PINSRC_NULL, GPIO_MUX_NULL}, //(PB12) Test-ISP2 OK
#elif defined(AT32F437xx)
	//ethernet f437 spi2(crm, gpio)
	//"AT32F437 SPI2 ETHERNET, sck/mi/mo/cs pd1/pc2/pd4/pd0",
	//{"SPI2", SPI2, CRM_SPI2_PERIPH_CLOCK},
	//{GPIOD, GPIO_PINS_1, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE1, GPIO_MUX_6},   //ISCK
	//{GPIOC, GPIO_PINS_2, CRM_GPIOC_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE2, GPIO_MUX_5},	//IMISO
	//{GPIOD, GPIO_PINS_4, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE4, GPIO_MUX_6},	//IMOSI
	//{GPIOD, GPIO_PINS_0, CRM_GPIOD_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PD0) Test-ISP2 OK
	//ethernet f437 spi4(crm, gpio)
	"AT32F437 SPI4 ETHERNET, sck/mi/mo/cs pe2/pe5/pe6/pe4",
	{"SPI4", SPI4, CRM_SPI4_PERIPH_CLOCK},
	{GPIOE, GPIO_PINS_2, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,     GPIO_PINS_SOURCE2, GPIO_MUX_5}, //ISCK
	{GPIOE, GPIO_PINS_5, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE5, GPIO_MUX_5},	//IMISO
	{GPIOE, GPIO_PINS_6, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_MUX,	  	GPIO_PINS_SOURCE6, GPIO_MUX_5},	//IMOSI
	{GPIOE, GPIO_PINS_4, CRM_GPIOE_PERIPH_CLOCK, GPIO_MODE_OUTPUT,  GPIO_PINSRC_NULL,  GPIO_MUX_NULL}, //(PE4) Test-ISP4 OK
#endif
};

const optsex_t dm9051optsex = {
	FALSE,
	MBNDRY_WORD, "MBNDRY_WORD",
	CS_EACH, "CS_EACH_MODE",
	0, //phy27
	0, "NCR Normal Mode", //vs. 1, "NCR_Test_mode"
	0, "Normal RX Mode", //vs. 1, "Promiscous_RX_mode"
};*/

typedef struct spihead_sel_st {
  char *spi_name;
  spi_type *spi_num;        		//= SPIPORT;
  crm_periph_clock_type spi_crm_clk;	//= SPI_CRM_CLK;
} spihead_t;

typedef struct gpio_sel_st {
	gpio_type *gpport;        		//= PORT;
	uint16_t pin;           		//= PIN;
	crm_periph_clock_type gpio_crm_clk;  //= CRM_CLK;	
	gpio_mode_type gpio_mode;		//= type
	gpio_pins_source_type pinsrc;
	gpio_mux_sel_type muxsel;
} gpio_t;

typedef struct gp_set_st {
	const char *gp_info;	
	const gpio_t gp;
} gp_set_t;

typedef struct extline_st {
	crm_periph_clock_type intr_crm_clk; //CRM_GPIOC_PERIPH_CLOCK,
	uint32_t extline; //= LINE
	IRQn_Type irqn; //= EXINTn_m
} extline_t;

typedef struct extint_init_st {
	crm_periph_clock_type scfg_clk;
#if !defined(AT32F437xx)
	gpio_port_source_type scfg_port_src;
	gpio_pins_source_type scfg_pin_src;
#elif defined(AT32F437xx)
	scfg_port_source_type scfg_port_src; //SCFG_PORT_SOURCE_X
	scfg_pins_source_type scfg_pin_src; //SCFG_PINS_SOURCEX
#endif
} extint_init_t;

typedef struct {
	char *cpu_api_info;	//cpu name is for the purpose to lead the pins, for easy recogition!
	spihead_t spidef;
	gpio_t wire_sck;
	gpio_t wire_mi;
	gpio_t wire_mo;
	gpio_t wire_cs;
} spi_dev_t;

struct extscfg_st { //struct linescfg_st
	const char *irq_enable_inf;	
	extline_t extline;
};

struct modscfg_st {
	const char *scfg_inf;	
	extint_init_t scfg_init;
	struct extscfg_st *extend; //struct linescfg_st *extend; //essential
	gp_set_t *option;
};

typedef struct {
	confirm_state test_plan_log;
	uint8_t iomode;
	char *desciomode;
	csmode_t longcsmode; //long chip_select mode
	char *desccssmode;
	uint8_t phy27;
	uint8_t ncrmode;
	char *descncrmode;
	uint8_t promismode; //promiscuous mode
	char *descpromismode;
} optsex_t;

//[lw.set]
#define dm9051optsex_testplanlog()		dm9051optsex.test_plan_log
#define dm9051optsex_iomode()			dm9051optsex.iomode
#define dm9051optsex_desciomode()		dm9051optsex.desciomode
#define dm9051optsex_longcsmode()		dm9051optsex.longcsmode
#define dm9051optsex_desccsmode()		dm9051optsex.desccssmode
#define dm9051optsex_ncrmode()			dm9051optsex.ncrmode
#define dm9051optsex_descncrmode()		dm9051optsex.descncrmode
#define dm9051optsex_promismode()		dm9051optsex.promismode
#define dm9051optsex_descpromismode()	dm9051optsex.descpromismode

//[common.macro]
#define gpio_wire_sck()				devconf.wire_sck 
#define gpio_wire_mi()				devconf.wire_mi
#define gpio_wire_mo()				devconf.wire_mo
#define gpio_cs()					devconf.wire_cs
#define spihead()					devconf.spidef
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

#define cpuhead()					devconf
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

#define mstep_set_index(i)			//empty for 1 eth project
#define mstep_turn_net_index()		//empty for 1 eth project
//-
//.#define mstep_get_index()		pin_code
//#define spi_dev()					&devconf
