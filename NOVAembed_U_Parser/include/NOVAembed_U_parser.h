#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <libgen.h>

#define     PIN_NAME_SIZE  48



typedef struct _iomux_cfg
{
    int pwm2;
    int spdif;
    int can1;
    int ecspi4;
    int ecspi4_dev;
    int uart6;
    int i2c2;
    int uart5rtscts;
} iomux_cfg;

typedef struct _iomux_pwm2
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char pwm_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_pwm2;

typedef struct _iomux_spdif
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char spdif_pin_name[PIN_NAME_SIZE];
    char pin_config[1][9];
} iomux_spdif;

typedef struct _iomux_can1
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char can1tx_pin_name[PIN_NAME_SIZE];
    char can1rx_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_can1;

typedef struct _iomux_ecspi4
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char mosi_pin_name[PIN_NAME_SIZE];
    char miso_pin_name[PIN_NAME_SIZE];
    char sclk_pin_name[PIN_NAME_SIZE];
    char ss0_pin_name[PIN_NAME_SIZE];
    char pin_config[4][9];
} iomux_ecspi4;

typedef struct _iomux_uart6
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char uart_txd_pin_name[PIN_NAME_SIZE];
    char uart_rxd_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_uart6;

typedef struct _iomux_i2c2
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char sda_pin_name[PIN_NAME_SIZE];
    char scl_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_i2c2;

typedef struct _iomux_uart_5rtscts
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char uart_rts_pin_name[PIN_NAME_SIZE];
    char uart_cts_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_uart_5rtscts;


typedef struct _gpio_support
{
    char combobox_string[PIN_NAME_SIZE];
    char pin_name_string[PIN_NAME_SIZE];
} gpio_support;


extern  void copy_and_resize(char *dest,char *source);
extern  void dump_iomux(void);


extern  char        file_contents[8192];
extern  void        parse_iomux(void);
extern  void        store_dts_files(char *file_in);
extern  iomux_cfg       *iomux;

extern  iomux_pwm2      *pwm2;
extern  iomux_can1      *can1;
extern  iomux_spdif     *spdif;
extern  iomux_ecspi4    *ecspi4;
extern  iomux_uart6     *uart6;
extern  iomux_i2c2      *i2c2;
