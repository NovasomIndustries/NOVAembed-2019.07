#include "../include/NOVAembed_U_parser.h"

iomux_cfg       *iomux;
iomux_pwm2      *pwm2;
iomux_can1      *can1;
iomux_spdif     *spdif;
iomux_ecspi4    *ecspi4;
iomux_uart6     *uart6;
iomux_i2c2      *i2c2;

void dump_iomux(void)
{
    printf("\nPeripherals usage ( 1 means IN USE ):\n");
    printf("**********************************************\n");
    printf("pwm2     : %d\n",iomux->pwm2);
    printf("can1     : %d\n",iomux->can1);
    printf("spdif    : %d\n",iomux->spdif);
    printf("ecspi4   : %d\n",iomux->ecspi4);
    printf("uart5    : %d\n",iomux->uart5);
    printf("uart6    : %d\n",iomux->uart6);
    printf("i2c2     : %d\n",iomux->i2c2);
    printf("**********************************************\n\n");
}

void parse_iomux(void)
{
    iomux = calloc(1,sizeof(iomux_cfg));

    if ( strstr(file_contents,"U_GPIO01_IO09_comboBox=PWM2"))
    {
        iomux->pwm2 = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO06_comboBox=ECSPI4_SCLK"))
    {
        iomux->ecspi4 = 1;
    }

    if ( strstr(file_contents,"U_GPIO01_IO10_comboBox=SPDIF_OUT"))
    {
        iomux->spdif = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO01_comboBox=CAN1_TX"))
    {
        iomux->can1 = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO19_comboBox=I2C2_SDA"))
    {
        iomux->i2c2 = 1;
    }
    if ( strstr(file_contents,"U_GPIO01_IO30_comboBox=UART5_TX"))
    {
        iomux->uart5 = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO17_comboBox=UART6_TX"))
    {
        iomux->uart6 = 1;
    }
    if ( strstr(file_contents,"U_SPIdev4_checkBox=true"))
        iomux->ecspi4_dev = 1;
}

