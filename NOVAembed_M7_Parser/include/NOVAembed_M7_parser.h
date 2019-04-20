#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <libgen.h>

#define     PIN_NAME_SIZE  48

typedef struct _iomux_cfg
{
    int spi_dev;
    int spi;
    int i2c2;
    int uart1;
    int uart1_4wires;
} iomux_cfg;


typedef struct _iomux_spi
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char mosi_pin_name[PIN_NAME_SIZE];
    char miso_pin_name[PIN_NAME_SIZE];
    char sclk_pin_name[PIN_NAME_SIZE];
    char ss0_pin_name[PIN_NAME_SIZE];
    char ss1_pin_name[PIN_NAME_SIZE];
    char pin_config[4][9];
} iomux_spi;

typedef struct _iomux_i2c2
{
    char pinctrl0_name[PIN_NAME_SIZE];
    char grp_name[PIN_NAME_SIZE];
    char sda_pin_name[PIN_NAME_SIZE];
    char scl_pin_name[PIN_NAME_SIZE];
    char pin_config[2][9];
} iomux_i2c2;


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


extern  iomux_spi    *spi;
extern  iomux_i2c2      *i2c2;
