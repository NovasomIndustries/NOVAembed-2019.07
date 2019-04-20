#include "../include/NOVAembed_M8_parser.h"

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
    printf("uart6    : %d\n",iomux->uart6);
    printf("i2c2     : %d\n",iomux->i2c2);
    printf("**********************************************\n\n");
}

void copy_and_resize(char *dest,char *source)
{
char *dup = strdup(source);
int i;
    *index(dup,0x0a)=0;
    if ( strlen(dup)<10)
    {
        if (( dup[0] == '0' ) && (dup[1] == 'x' ))
            dup += 2;
        sprintf(dest,"%8s", dup);
        for(i=0;i<8;i++)
            if ( dest[i] == ' ')
                dest[i]='0';
    }
    else
        snprintf(dest,9,"%s",dup+2);
}

void process_pwm2(void)
{
    pwm2 = calloc(1,sizeof(iomux_pwm2));
    sprintf(pwm2->grp_name,"pwm2grp");
    sprintf(pwm2->pinctrl0_name,"pinctrl_pwm2");
    sprintf(pwm2->pwm_pin_name,"MX6UL_PAD_GPIO1_IO08__PWM1_OUT");
    sprintf(pwm2->pin_config[0],"1b0b0");
    return;
}

void process_ecspi4(void)
{
    ecspi4 = calloc(1,sizeof(iomux_ecspi4));
    sprintf(ecspi4->grp_name,"ecspi4grp");
    sprintf(ecspi4->pinctrl0_name,"pinctrl_ecspi4");
    sprintf(ecspi4->mosi_pin_name,"MX6QDL_PAD_EIM_D28__ECSPI4_MOSI");
    sprintf(ecspi4->miso_pin_name,"MX6QDL_PAD_EIM_D22__ECSPI4_MISO");
    sprintf(ecspi4->sclk_pin_name,"MX6QDL_PAD_EIM_D21__ECSPI4_SCLK");
    sprintf(ecspi4->ss0_pin_name, "MX6QDL_PAD_EIM_D29__GPIO3_IO29");
    sprintf(ecspi4->pin_config[0],"100b1");
    sprintf(ecspi4->pin_config[1],"100b1");
    sprintf(ecspi4->pin_config[2],"100b1");
    sprintf(ecspi4->pin_config[3],"100b1");
    return;
}
void process_spdif(void)
{
char *t1;
    spdif = calloc(1,sizeof(iomux_spdif));
    sprintf(spdif->grp_name,"spdifgrp");
    sprintf(spdif->pinctrl0_name,"pinctrl_spdif");
    sprintf(spdif->spdif_pin_name,"MX6QDL_PAD_ENET_RXD0__SPDIF_OUT");
    if ((t1 = strstr(file_contents,"P_ECSPI4_MISO_cbit=")))
        copy_and_resize(spdif->pin_config[0],t1+sizeof("P_ECSPI4_MISO_cbit"));
    return;
}

void process_i2c2(void)
{
    i2c2 = calloc(1,sizeof(iomux_i2c2));
    sprintf(i2c2->grp_name,"i2c2grp");
    sprintf(i2c2->pinctrl0_name,"pinctrl_i2c2");
    sprintf(i2c2->sda_pin_name,"MX6QDL_PAD_EIM_D28__I2C1_SDA");
    sprintf(i2c2->scl_pin_name,"MX6QDL_PAD_EIM_D21__I2C1_SCL");
    sprintf(i2c2->pin_config[0],"4001b8b1");
    sprintf(i2c2->pin_config[1],"4001b8b1");
    return;
}
void process_uart6(void)
{
    uart6 = calloc(1,sizeof(iomux_uart6));
    sprintf(uart6->grp_name,"uart4grp");
    sprintf(uart6->pinctrl0_name,"pinctrl_uart4");
    sprintf(uart6->uart_txd_pin_name,"MX6QDL_PAD_CSI0_DAT12__UART4_TX_DATA");
    sprintf(uart6->uart_rxd_pin_name,"MX6QDL_PAD_CSI0_DAT13__UART4_RX_DATA");
    sprintf(uart6->pin_config[0],"1b0b1");
    sprintf(uart6->pin_config[1],"1b0b1");
    return;
}

void parse_iomux(void)
{
    iomux = calloc(1,sizeof(iomux_cfg));

    if ( strstr(file_contents,"U_GPIO01_IO09_comboBox=PWM2"))
    {
        iomux->pwm2 = 1;
        process_pwm2();
    }
    if ( strstr(file_contents,"U_GPIO04_IO06_comboBox=ECSPI4_SCLK"))
    {
        iomux->ecspi4 = 1;
        process_ecspi4();
    }

    if ( strstr(file_contents,"U_GPIO01_IO10_comboBox=SPDIF_OUT"))
    {
        process_spdif();
        iomux->spdif = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO01_comboBox=CAN1_TX"))
    {
        //process_can1();
        iomux->can1 = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO19_comboBox=I2C2_SDA"))
    {
        process_i2c2();
        iomux->i2c2 = 1;
    }
    if ( strstr(file_contents,"U_GPIO04_IO17_comboBox=UART6_TX"))
    {
        process_uart6();
        iomux->uart6 = 1;
    }
    if ( strstr(file_contents,"U_SPIdev4_checkBox=true"))
        iomux->ecspi4_dev = 1;
}

