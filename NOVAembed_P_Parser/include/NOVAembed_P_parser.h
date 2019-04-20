#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <libgen.h>

#define     PIN_NAME_SIZE  48

typedef struct _iomux_cfg
{
    int ecspi1_4;
    int ecspi1_5;
    int ecspi1_dev;
    int audio4;
    int ecspi2_4;
    int ecspi2_5;
    int ecspi2_dev;
    int audio5;
    int ecspi3_5;
    int ecspi3_4;
    int ecspi3_dev;
    int ecspi4;
    int ecspi4_dev;
    int spdif1;
    int i2c1a;      /* expansion, power from expansion, 2 wires, J9-23 and J9-24 */
    int i2c1b;      /* expansion, 2 wires, J9-20 and J9-22 */
    int i2c2;       /* edid for hdmi */
    int i2c3;       /* expansion, 2 wires */
    int clk32k;
    int sd3_4;
    int sd3_8;
    int uart2;
    int can1;
    int can2;
    int epit1;
    int clk24m;
    int pwm1;
    int wdog;
    int audio6;
    int ccm_clko1;
    int uart1;      /* expansion, power from expansion, 2 wires */
    int uart2_4;    /* aux rs232 */
    int uart2_2;    /* aux rs232 */
    int uart3;      /* console */
    int uart4_4;    /* expansion, power from expansion, 4 wires */
    int uart4_2;    /* expansion, power from expansion, 2 wires */
    int uart5;      /* rs485 */
    int spdif2;
    int sata;
    int pcie;
    char video[32];
} iomux_cfg;

typedef struct _iomux_audio
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char aud_rxd_pin_name[PIN_NAME_SIZE];
    char aud_txc_pin_name[PIN_NAME_SIZE];
    char aud_txd_pin_name[PIN_NAME_SIZE];
    char aud_txfs_pin_name[PIN_NAME_SIZE];
    char pin_config[4][9];
} iomux_audio;

typedef struct _iomux_ecspi_5
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char mosi_pin_name[PIN_NAME_SIZE];
    char miso_pin_name[PIN_NAME_SIZE];
    char sclk_pin_name[PIN_NAME_SIZE];
    char ss0_pin_name[PIN_NAME_SIZE];
    char ss1_pin_name[PIN_NAME_SIZE];
    char pin_config[5][9];
} iomux_ecspi_5;

typedef struct _iomux_ecspi_4
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char mosi_pin_name[PIN_NAME_SIZE];
    char miso_pin_name[PIN_NAME_SIZE];
    char sclk_pin_name[PIN_NAME_SIZE];
    char ss0_pin_name[PIN_NAME_SIZE];
    char pin_config[4][9];
} iomux_ecspi_4;

typedef struct _iomux_i2c
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char sda_pin_name[PIN_NAME_SIZE];
    char scl_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_i2c;

typedef struct _iomux_sdcard_4
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char cmd_pin_name[PIN_NAME_SIZE];
    char clk_pin_name[PIN_NAME_SIZE];
    char data0_pin_name[PIN_NAME_SIZE];
    char data1_pin_name[PIN_NAME_SIZE];
    char data2_pin_name[PIN_NAME_SIZE];
    char data3_pin_name[PIN_NAME_SIZE];
    char pin_config[6][9];
} iomux_sdcard_4;

typedef struct _iomux_sdcard_8
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char cmd_pin_name[PIN_NAME_SIZE];
    char clk_pin_name[PIN_NAME_SIZE];
    char data0_pin_name[PIN_NAME_SIZE];
    char data1_pin_name[PIN_NAME_SIZE];
    char data2_pin_name[PIN_NAME_SIZE];
    char data3_pin_name[PIN_NAME_SIZE];
    char data4_pin_name[PIN_NAME_SIZE];
    char data5_pin_name[PIN_NAME_SIZE];
    char data6_pin_name[PIN_NAME_SIZE];
    char data7_pin_name[PIN_NAME_SIZE];
    char pin_config[10][9];
} iomux_sdcard_8;

typedef struct _iomux_uart_2
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char uart_txd_pin_name[PIN_NAME_SIZE];
    char uart_rxd_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_uart_2;

typedef struct _iomux_uart_4
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char uart_txd_pin_name[PIN_NAME_SIZE];
    char uart_rxd_pin_name[PIN_NAME_SIZE];
    char uart_rts_pin_name[PIN_NAME_SIZE];
    char uart_cts_pin_name[PIN_NAME_SIZE];
    char pin_config[4][9];
} iomux_uart_4;

typedef struct _iomux_spdif
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char spdif_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_spdif;
/*
typedef struct _iomux_clk
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char clk_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_clk;
*/
typedef struct _iomux_can
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char cantx_pin_name[PIN_NAME_SIZE];
    char canrx_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_can;

typedef struct _iomux_epit
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char epit_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_epit;

typedef struct _iomux_pwm
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char pwm_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_pwm;
/*
typedef struct _iomux_wdog
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char wdog_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_wdog;
*/
typedef struct _iomux_hog
{
    char hog_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_hog;


typedef struct _gpio_support
{
    char combobox_string[PIN_NAME_SIZE];
    char pin_name_string[PIN_NAME_SIZE];
} gpio_support;


extern  char        file_contents[8192];
extern  char        lvds_800x480_ch0_parserinput[1024];
extern  char        lvds_800x480_ch1_parserinput[1024];
extern  char        lvds_800x600_ch0_parserinput[1024];
extern  char        lvds_800x600_ch1_parserinput[1024];
extern  char        lvds_1024x600_ch0_parserinput[1024];
extern  char        lvds_1024x600_ch1_parserinput[1024];
extern  char        lvds_1024x768_ch0_parserinput[1024];
extern  char        lvds_1024x768_ch1_parserinput[1024];
extern  char        lvds_1280x800_ch0_parserinput[1024];
extern  char        lvds_1280x800_ch1_parserinput[1024];
extern  char        lvds_1366x768_ch0_parserinput[1024];
extern  char        lvds_1366x768_ch1_parserinput[1024];

extern  iomux_cfg   *iomux;
extern  char        special_hogs[1024];
extern  char        gpio_hogs[2048];

extern  void parse_special_iomux(void);
extern  void dump_iomux(void);
extern  void store_dts_files(char *file_in);
extern  void copy_and_resize(char *dest,char *source);

extern  iomux_cfg       *iomux;
extern  iomux_audio     *audio4,*audio5,*audio6;
extern  iomux_ecspi_5   *ecspi1_5,*ecspi2_5,*ecspi3_5;
extern  iomux_ecspi_4   *ecspi1_4,*ecspi2_4,*ecspi3_4,*ecspi4;
extern  iomux_i2c       *i2c1a,*i2c1b,*i2c3;
extern  iomux_hog       *clk32k,*clk24m,*ccm_clko1,*wdog;
extern  iomux_can       *can1,*can2;
extern  iomux_spdif     *spdif;
extern  iomux_sdcard_4  *sdcard_4;
extern  iomux_sdcard_8  *sdcard_8;
extern  iomux_epit      *epit1;
extern  iomux_pwm       *pwm;
extern  iomux_uart_2    *uart1,*uart2_2,*uart4_2;
extern  iomux_uart_4    *uart2_4,*uart4_4;
