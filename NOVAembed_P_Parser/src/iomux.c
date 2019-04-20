#include "../include/NOVAembed_P_parser.h"

iomux_cfg       *iomux;
iomux_audio     *audio4,*audio5,*audio6;
iomux_ecspi_5   *ecspi1_5,*ecspi2_5,*ecspi3_5;
iomux_ecspi_4   *ecspi1_4,*ecspi2_4,*ecspi3_4,*ecspi4;
iomux_i2c       *i2c1a,*i2c1b,*i2c3;
iomux_hog       *clk32k,*clk24m,*ccm_clko1,*wdog;
iomux_can       *can1,*can2;
iomux_spdif     *spdif;
iomux_sdcard_8  *sdcard_8;
iomux_sdcard_4  *sdcard_4;
iomux_epit      *epit1;
iomux_pwm       *pwm;
iomux_uart_2    *uart1,*uart2_2,*uart4_2;
iomux_uart_4    *uart2_4,*uart4_4;

void dump_iomux(void)
{
    printf("\nPeripherals usage ( 1 means IN USE ):\n");
    printf("**********************************************\n");
    printf("audio4   : %d\n",iomux->audio4);
    printf("audio5   : %d\n",iomux->audio5);
    printf("audio6   : %d\n",iomux->audio6);
    printf("ecspi1_4 : %d\n",iomux->ecspi1_4);
    printf("ecspi1_5 : %d\n",iomux->ecspi1_5);
    printf("ecspi2_4 : %d\n",iomux->ecspi2_4);
    printf("ecspi2_5 : %d\n",iomux->ecspi2_5);
    printf("ecspi3_4 : %d\n",iomux->ecspi3_4);
    printf("ecspi3_5 : %d\n",iomux->ecspi3_5);
    printf("ecspi4   : %d\n",iomux->ecspi4);
    printf("i2c1a    : %d\n",iomux->i2c1a);
    printf("i2c1b    : %d\n",iomux->i2c1b);
    printf("i2c2     : %d ( system , HDMI edid )\n",iomux->i2c2);
    printf("i2c3     : %d\n",iomux->i2c3);
    printf("sd3_4    : %d\n",iomux->sd3_4);
    printf("sd3_8    : %d\n",iomux->sd3_8);
    printf("can1     : %d\n",iomux->can1);
    printf("can2     : %d\n",iomux->can2);
    printf("uart1    : %d\n",iomux->uart1);
    printf("uart2_4  : %d\n",iomux->uart2_4);
    printf("uart2_2  : %d\n",iomux->uart2_2);
    printf("uart3    : %d ( system , console )\n",iomux->uart3);
    printf("uart4_4  : %d\n",iomux->uart4_4);
    printf("uart4_2  : %d\n",iomux->uart4_2);
    printf("uart5    : %d ( system , rs485 )\n",iomux->uart5);
    printf("spdif1   : %d\n",iomux->spdif1);
    printf("spdif2   : %d\n",iomux->spdif2);
    printf("pwm1     : %d\n",iomux->pwm1);
    printf("Hog group functions ( fixed functions pins ) :\n");
    printf("epit1    : %d\n",iomux->epit1);
    printf("clk24m   : %d\n",iomux->clk24m);
    printf("wdog     : %d\n",iomux->wdog);
    printf("ccm_clko1: %d\n",iomux->ccm_clko1);
    printf("clk32k   : %d\n",iomux->clk32k);
    printf("Special peripherals :\n");
    printf("sata     : %d\n",iomux->sata);
    printf("pcie     : %d\n",iomux->pcie);
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

/* Pins in the HOG group */
void process_clk32k(void)
{
    clk32k = calloc(1,sizeof(iomux_hog));
    sprintf(clk32k->hog_pin_name,"MX6QDL_PAD_GPIO_8__XTALOSC_REF_CLK_32K");
    sprintf(clk32k->pin_config[0],"17059");
    return;
}

void process_clk24m(void)
{
    clk24m = calloc(1,sizeof(iomux_hog));
    sprintf(clk24m->hog_pin_name,"MX6QDL_PAD_GPIO_3__XTALOSC_REF_CLK_24M");
    sprintf(clk24m->pin_config[0],"17059");
    return;
}

void process_clko1(void)
{
    ccm_clko1 = calloc(1,sizeof(iomux_hog));
    sprintf(ccm_clko1->hog_pin_name,"MX6QDL_PAD_GPIO_0__CCM_CLKO1");
    sprintf(ccm_clko1->pin_config[0],"17059");
    return;
}

void process_wdog(void)
{
char *t1;
    wdog = calloc(1,sizeof(iomux_hog));
    sprintf(wdog->hog_pin_name,"MX6QDL_PAD_GPIO_9__WDOG1_B");
    if ((t1 = strstr(file_contents,"P_GPIO4_IO29_cbit=")))
        copy_and_resize(wdog->pin_config[0],t1+sizeof("P_GPIO4_IO29_cbit"));
    return;
}
/* End of pins in the HOG group */


/* Special functions pins */

void process_pwm1(void)
{
    pwm = calloc(1,sizeof(iomux_pwm));
    sprintf(pwm->grp_name,"pwm1grp");
    sprintf(pwm->pinctrl0_name,"pinctrl_pwm1");
    sprintf(pwm->pwm_pin_name,"MX6QDL_PAD_GPIO_9__PWM1_OUT");
    sprintf(pwm->pin_config[0],"1b0b0");
    return;
}


void process_epit1(void)
{
char *t1;
    epit1 = calloc(1,sizeof(iomux_epit));
    sprintf(epit1->grp_name,"epit1grp");
    sprintf(epit1->pinctrl0_name,"pinctrl_epit1");
    sprintf(epit1->epit_pin_name,"MX6QDL_PAD_GPIO_0__EPIT1_OUT");
    if ((t1 = strstr(file_contents,"P_GPIO1_IO00_cbit=")))
        copy_and_resize(epit1->pin_config[0],t1+sizeof("P_GPIO1_IO00_cbit"));
    return;
}

void process_sd3_4(void)
{
    sdcard_4 = calloc(1,sizeof(iomux_sdcard_4));
    sprintf(sdcard_4->grp_name,"usdhc3grp");
    sprintf(sdcard_4->pinctrl0_name,"pinctrl_usdhc3");
    sprintf(sdcard_4->cmd_pin_name,"MX6QDL_PAD_SD3_CMD__SD3_CMD");
    sprintf(sdcard_4->clk_pin_name,"MX6QDL_PAD_SD3_CLK__SD3_CLK");
    sprintf(sdcard_4->data0_pin_name,"MX6QDL_PAD_SD3_DAT0__SD3_DATA0");
    sprintf(sdcard_4->data1_pin_name,"MX6QDL_PAD_SD3_DAT1__SD3_DATA1");
    sprintf(sdcard_4->data2_pin_name,"MX6QDL_PAD_SD3_DAT2__SD3_DATA2");
    sprintf(sdcard_4->data3_pin_name,"MX6QDL_PAD_SD3_DAT3__SD3_DATA3");
    sprintf(sdcard_4->pin_config[0],"17059");
    sprintf(sdcard_4->pin_config[1],"10059");
    sprintf(sdcard_4->pin_config[2],"17059");
    sprintf(sdcard_4->pin_config[3],"17059");
    sprintf(sdcard_4->pin_config[4],"17059");
    sprintf(sdcard_4->pin_config[5],"17059");
    return;
}

void process_sd3_8(void)
{
    sdcard_8 = calloc(1,sizeof(iomux_sdcard_8));
    sprintf(sdcard_8->grp_name,"usdhc3grp");
    sprintf(sdcard_8->pinctrl0_name,"pinctrl_usdhc3");
    sprintf(sdcard_8->cmd_pin_name,"MX6QDL_PAD_SD3_CMD__SD3_CMD");
    sprintf(sdcard_8->clk_pin_name,"MX6QDL_PAD_SD3_CLK__SD3_CLK");
    sprintf(sdcard_8->data0_pin_name,"MX6QDL_PAD_SD3_DAT0__SD3_DATA0");
    sprintf(sdcard_8->data1_pin_name,"MX6QDL_PAD_SD3_DAT1__SD3_DATA1");
    sprintf(sdcard_8->data2_pin_name,"MX6QDL_PAD_SD3_DAT2__SD3_DATA2");
    sprintf(sdcard_8->data3_pin_name,"MX6QDL_PAD_SD3_DAT3__SD3_DATA3");
    sprintf(sdcard_8->data4_pin_name,"MX6QDL_PAD_SD3_DAT4__SD3_DATA4");
    sprintf(sdcard_8->data5_pin_name,"MX6QDL_PAD_SD3_DAT5__SD3_DATA5");
    sprintf(sdcard_8->data6_pin_name,"MX6QDL_PAD_SD3_DAT6__SD3_DATA6");
    sprintf(sdcard_8->data7_pin_name,"MX6QDL_PAD_SD3_DAT7__SD3_DATA7");
    sprintf(sdcard_8->pin_config[0],"17059");
    sprintf(sdcard_8->pin_config[1],"10059");
    sprintf(sdcard_8->pin_config[2],"17059");
    sprintf(sdcard_8->pin_config[3],"17059");
    sprintf(sdcard_8->pin_config[4],"17059");
    sprintf(sdcard_8->pin_config[5],"17059");
    sprintf(sdcard_8->pin_config[6],"17059");
    sprintf(sdcard_8->pin_config[7],"17059");
    sprintf(sdcard_8->pin_config[8],"17059");
    sprintf(sdcard_8->pin_config[9],"17059");
    return;
}

void process_spdif1(void)
{
char *t1;
    spdif = calloc(1,sizeof(iomux_can));
    sprintf(spdif->grp_name,"spdifgrp");
    sprintf(spdif->pinctrl0_name,"pinctrl_spdif");
    sprintf(spdif->spdif_pin_name,"MX6QDL_PAD_ENET_RXD0__SPDIF_OUT");
    if ((t1 = strstr(file_contents,"P_ECSPI4_MISO_cbit=")))
        copy_and_resize(spdif->pin_config[0],t1+sizeof("P_ECSPI4_MISO_cbit"));
    return;
}
void process_spdif2(void)
{
char *t1;
    spdif = calloc(1,sizeof(iomux_can));
    sprintf(spdif->grp_name,"spdifgrp");
    sprintf(spdif->pinctrl0_name,"pinctrl_spdif");
    sprintf(spdif->spdif_pin_name,"MX6QDL_PAD_GPIO_17__SPDIF_OUT");
    if ((t1 = strstr(file_contents,"P_SPDIF_OUT_cbit=")))
        copy_and_resize(spdif->pin_config[0],t1+sizeof("P_SPDIF_OUT_cbit"));
    return;
}

void process_can1(void)
{
char *t1;
    can1 = calloc(1,sizeof(iomux_can));
    sprintf(can1->grp_name,"can1grp");
    sprintf(can1->pinctrl0_name,"pinctrl_flexcan1");
    sprintf(can1->cantx_pin_name,"MX6QDL_PAD_KEY_COL2__FLEXCAN1_TX");
    sprintf(can1->canrx_pin_name,"MX6QDL_PAD_KEY_ROW2__FLEXCAN1_RX");
    if ((t1 = strstr(file_contents,"P_SD3_CMD_cbit=")))
        copy_and_resize(can1->pin_config[0],t1+sizeof("P_SD3_CMD_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_CLK_cbit=")))
        copy_and_resize(can1->pin_config[1],t1+sizeof("P_SD3_CLK_cbit"));
    return;
}

void process_can2(void)
{
char *t1;
    can2 = calloc(1,sizeof(iomux_can));
    sprintf(can2->grp_name,"can2grp");
    sprintf(can2->pinctrl0_name,"pinctrl_flexcan2");
    sprintf(can2->cantx_pin_name,"MX6QDL_PAD_SD3_DAT0__FLEXCAN2_TX");
    sprintf(can2->canrx_pin_name,"MX6QDL_PAD_SD3_DAT1__FLEXCAN2_RX");
    if ((t1 = strstr(file_contents,"P_SD3_DATA0_cbit=")))
        copy_and_resize(can2->pin_config[0],t1+sizeof("P_SD3_DATA0_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_DATA1_cbit=")))
        copy_and_resize(can2->pin_config[1],t1+sizeof("P_SD3_DATA1_cbit"));
    return;
}

void process_i2c1b(void)
{
//char *t1;
    i2c1b = calloc(1,sizeof(iomux_i2c));
    sprintf(i2c1b->grp_name,"i2c1grp");
    sprintf(i2c1b->pinctrl0_name,"pinctrl_i2c1");
    sprintf(i2c1b->sda_pin_name,"MX6QDL_PAD_CSI0_DAT8__I2C1_SDA");
    sprintf(i2c1b->scl_pin_name,"MX6QDL_PAD_CSI0_DAT9__I2C1_SCL");
    sprintf(i2c1b->pin_config[0],"4001b8b1");
    sprintf(i2c1b->pin_config[1],"4001b8b1");
    /*
    if ((t1 = strstr(file_contents,"P_I2C1_SDA_cbit=")))
        copy_and_resize(i2c1b->pin_config[0],t1+sizeof("P_I2C1_SDA_cbit"));
    if ((t1 = strstr(file_contents,"P_I2C1_SCL_cbit=")))
        copy_and_resize(i2c1b->pin_config[1],t1+sizeof("P_I2C1_SCL_cbit"));
    */
    return;
}

void process_uart1(void)
{
//char *t1;
    uart1 = calloc(1,sizeof(iomux_uart_2));
    sprintf(uart1->grp_name,"uart1grp");
    sprintf(uart1->pinctrl0_name,"pinctrl_uart1");
    sprintf(uart1->uart_txd_pin_name,"MX6QDL_PAD_CSI0_DAT10__UART1_TX_DATA");
    sprintf(uart1->uart_rxd_pin_name,"MX6QDL_PAD_CSI0_DAT11__UART1_RX_DATA");
    sprintf(uart1->pin_config[0],"1b0b1");
    sprintf(uart1->pin_config[1],"1b0b1");
    /*
    if ((t1 = strstr(file_contents,"P_UART1_TXD_cbit=")))
        copy_and_resize(uart1->pin_config[0],t1+sizeof("P_UART1_TXD_cbit"));
    if ((t1 = strstr(file_contents,"P_UART1_RXD_cbit=")))
        copy_and_resize(uart1->pin_config[1],t1+sizeof("P_UART1_RXD_cbit"));
    */
    return;
}

void process_uart2_2(void)
{
//char *t1;
    uart2_2 = calloc(1,sizeof(iomux_uart_2));
    sprintf(uart2_2->grp_name,"uart2grp");
    sprintf(uart2_2->pinctrl0_name,"pinctrl_uart2");
    sprintf(uart2_2->uart_txd_pin_name,"MX6QDL_PAD_SD3_DAT5__UART2_TX_DATA");
    sprintf(uart2_2->uart_rxd_pin_name,"MX6QDL_PAD_SD3_DAT5__UART2_RX_DATA");
    sprintf(uart2_2->pin_config[0],"1b0b1");
    sprintf(uart2_2->pin_config[1],"1b0b1");
    /*
    if ((t1 = strstr(file_contents,"P_SD3_DATA5_cbit=")))
        copy_and_resize(uart2_2->pin_config[0],t1+sizeof("P_SD3_DATA5_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_DATA4_cbit=")))
        copy_and_resize(uart2_2->pin_config[1],t1+sizeof("P_SD3_DATA4_cbit"));
    */
    return;
}

void process_uart2_2aux(void)
{
//char *t1;
    uart2_2 = calloc(1,sizeof(iomux_uart_2));
    sprintf(uart2_2->grp_name,"uart2grp");
    sprintf(uart2_2->pinctrl0_name,"pinctrl_uart2");
    sprintf(uart2_2->uart_txd_pin_name,"MX6QDL_PAD_EIM_D26__UART2_TX_DATA");
    sprintf(uart2_2->uart_rxd_pin_name,"MX6QDL_PAD_EIM_D27__UART2_RX_DATA");
    sprintf(uart2_2->pin_config[0],"1b0b1");
    sprintf(uart2_2->pin_config[1],"1b0b1");
    /*
    if ((t1 = strstr(file_contents,"P_SD3_DATA5_cbit=")))
        copy_and_resize(uart2_2->pin_config[0],t1+sizeof("P_SD3_DATA5_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_DATA4_cbit=")))
        copy_and_resize(uart2_2->pin_config[1],t1+sizeof("P_SD3_DATA4_cbit"));
    */
    return;
}

void process_uart2_4(void)
{
//char *t1;
    uart2_4 = calloc(1,sizeof(iomux_uart_4));
    sprintf(uart2_4->grp_name,"uart2grp");
    sprintf(uart2_4->pinctrl0_name,"pinctrl_uart2");
    sprintf(uart2_4->uart_txd_pin_name,"MX6QDL_PAD_SD3_DAT5__UART2_TX_DATA");
    sprintf(uart2_4->uart_rxd_pin_name,"MX6QDL_PAD_SD3_DAT5__UART2_RX_DATA");
    sprintf(uart2_4->uart_rts_pin_name,"MX6QDL_PAD_SD3_CMD__UART2_RTS_B");
    sprintf(uart2_4->uart_cts_pin_name,"MX6QDL_PAD_SD3_CLK__UART2_CTS_B");
    sprintf(uart2_4->pin_config[0],"1b0b1");
    sprintf(uart2_4->pin_config[1],"1b0b1");
    sprintf(uart2_4->pin_config[2],"1b0b1");
    sprintf(uart2_4->pin_config[3],"1b0b1");
    /*
    if ((t1 = strstr(file_contents,"P_SD3_DATA5_cbit=")))
        copy_and_resize(uart2_4->pin_config[0],t1+sizeof("P_SD3_DATA5_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_DATA4_cbit=")))
        copy_and_resize(uart2_4->pin_config[1],t1+sizeof("P_SD3_DATA4_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_CLK_cbit=")))
        copy_and_resize(uart2_4->pin_config[2],t1+sizeof("P_SD3_CLK_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_CMD_cbit=")))
        copy_and_resize(uart2_4->pin_config[3],t1+sizeof("P_SD3_CMD_cbit"));
        */
    return;
}

void process_uart4_2(void)
{
//char *t1;
    uart4_2 = calloc(1,sizeof(iomux_uart_2));
    sprintf(uart4_2->grp_name,"uart4grp");
    sprintf(uart4_2->pinctrl0_name,"pinctrl_uart4");
    sprintf(uart4_2->uart_txd_pin_name,"MX6QDL_PAD_CSI0_DAT12__UART4_TX_DATA");
    sprintf(uart4_2->uart_rxd_pin_name,"MX6QDL_PAD_CSI0_DAT13__UART4_RX_DATA");
    sprintf(uart4_2->pin_config[0],"1b0b1");
    sprintf(uart4_2->pin_config[1],"1b0b1");
    /*
    if ((t1 = strstr(file_contents,"P_SD3_DATA5_cbit=")))
        copy_and_resize(uart4_2->pin_config[0],t1+sizeof("P_SD3_DATA5_cbit"));
    if ((t1 = strstr(file_contents,"P_SD3_DATA4_cbit=")))
        copy_and_resize(uart4_2->pin_config[1],t1+sizeof("P_SD3_DATA4_cbit"));
        */
    return;
}

void process_uart4_4(void)
{
//char *t1;
    uart4_4 = calloc(1,sizeof(iomux_uart_4));
    sprintf(uart4_4->grp_name,"uart4grp");
    sprintf(uart4_4->pinctrl0_name,"pinctrl_uart4");
    sprintf(uart4_4->uart_txd_pin_name,"MX6QDL_PAD_CSI0_DAT12__UART4_TX_DATA");
    sprintf(uart4_4->uart_rxd_pin_name,"MX6QDL_PAD_CSI0_DAT13__UART4_RX_DATA");
    sprintf(uart4_4->uart_rts_pin_name,"MX6QDL_PAD_CSI0_DAT16__UART4_RTS_B");
    sprintf(uart4_4->uart_cts_pin_name,"MX6QDL_PAD_CSI0_DAT17__UART4_CTS_B");
    sprintf(uart4_4->pin_config[0],"1b0b1");
    sprintf(uart4_4->pin_config[1],"1b0b1");
    sprintf(uart4_4->pin_config[2],"1b0b1");
    sprintf(uart4_4->pin_config[3],"1b0b1");
    /*
    if ((t1 = strstr(file_contents,"P_UART4_TXD_cbit=")))
        copy_and_resize(uart4_4->pin_config[0],t1+sizeof("P_UART4_TXD_cbit"));
    if ((t1 = strstr(file_contents,"P_UART4_RXD_cbit=")))
        copy_and_resize(uart4_4->pin_config[1],t1+sizeof("P_UART4_RXD_cbit"));
    if ((t1 = strstr(file_contents,"P_UART4_RTS_L_cbit=")))
        copy_and_resize(uart4_4->pin_config[2],t1+sizeof("P_UART4_RTS_L_cbit"));
    if ((t1 = strstr(file_contents,"P_UART4_CTS_L_cbit=")))
        copy_and_resize(uart4_4->pin_config[3],t1+sizeof("P_UART4_CTS_L_cbit"));
        */
    return;
}


void process_audio4(void)
{
    audio4 = calloc(1,sizeof(iomux_audio));
    sprintf(audio4->grp_name,"audmux4");
    sprintf(audio4->pinctrl0_name,"pinctrl_audmux4");
    sprintf(audio4->aud_rxd_pin_name,"MX6QDL_PAD_DISP0_DAT23__AUD4_RXD");
    sprintf(audio4->aud_txc_pin_name,"MX6QDL_PAD_DISP0_DAT20__AUD4_TXC");
    sprintf(audio4->aud_txd_pin_name,"MX6QDL_PAD_DISP0_DAT21__AUD4_TXD");
    sprintf(audio4->aud_txfs_pin_name,"MX6QDL_PAD_DISP0_DAT22__AUD4_TXFS"); //1b0b0
    sprintf(audio4->pin_config[0],"1b0b0");
    sprintf(audio4->pin_config[1],"1b0b0");
    sprintf(audio4->pin_config[2],"1b0b0");
    sprintf(audio4->pin_config[3],"1b0b0");
    return;
}

void process_audio5(void)
{
    audio5 = calloc(1,sizeof(iomux_audio));
    sprintf(audio5->grp_name,"audmux5");
    sprintf(audio5->pinctrl0_name,"pinctrl_audmux5");
    sprintf(audio5->aud_rxd_pin_name,"MX6QDL_PAD_DISP0_DAT19__AUD5_RXD");
    sprintf(audio5->aud_txc_pin_name,"MX6QDL_PAD_DISP0_DAT16__AUD5_TXC");
    sprintf(audio5->aud_txd_pin_name,"MX6QDL_PAD_DISP0_DAT17__AUD5_TXD");
    sprintf(audio5->aud_txfs_pin_name,"MX6QDL_PAD_DISP0_DAT18__AUD5_TXFS");
    sprintf(audio5->pin_config[0],"1b0b0");
    sprintf(audio5->pin_config[1],"1b0b0");
    sprintf(audio5->pin_config[2],"1b0b0");
    sprintf(audio5->pin_config[3],"1b0b0");
    return;
}

void process_audio6(void)
{
    audio6 = calloc(1,sizeof(iomux_audio));
    sprintf(audio6->grp_name,"audmux6");
    sprintf(audio6->pinctrl0_name,"pinctrl_audmux6");
    sprintf(audio6->aud_rxd_pin_name,"MX6QDL_PAD_DI0_PIN4__AUD6_RXD");
    sprintf(audio6->aud_txc_pin_name,"MX6QDL_PAD_DI0_PIN15__AUD6_TXC");
    sprintf(audio6->aud_txd_pin_name,"MX6QDL_PAD_DI0_PIN2__AUD6_TXD");
    sprintf(audio6->aud_txfs_pin_name,"MX6QDL_PAD_DI0_PIN3__AUD6_TXFS");
    sprintf(audio6->pin_config[0],"1b0b0");
    sprintf(audio6->pin_config[1],"1b0b0");
    sprintf(audio6->pin_config[2],"1b0b0");
    sprintf(audio6->pin_config[3],"1b0b0");
    return;
}

void process_ecspi1_5(void)
{
    ecspi1_5 = calloc(1,sizeof(iomux_ecspi_5));
    sprintf(ecspi1_5->grp_name,"ecspi1grp");
    sprintf(ecspi1_5->pinctrl0_name,"pinctrl_ecspi1");
    sprintf(ecspi1_5->mosi_pin_name,"MX6QDL_PAD_DISP0_DAT21__ECSPI1_MOSI");
    sprintf(ecspi1_5->miso_pin_name,"MX6QDL_PAD_DISP0_DAT22__ECSPI1_MISO");
    sprintf(ecspi1_5->sclk_pin_name,"MX6QDL_PAD_DISP0_DAT20__ECSPI1_SCLK");
    sprintf(ecspi1_5->ss0_pin_name,"MX6QDL_PAD_DISP0_DAT23__GPIO5_IO17");
    sprintf(ecspi1_5->ss1_pin_name,"MX6QDL_PAD_DISP0_DAT15__GPIO5_IO09");
    sprintf(ecspi1_5->pin_config[0],"100b1");
    sprintf(ecspi1_5->pin_config[1],"100b1");
    sprintf(ecspi1_5->pin_config[2],"100b1");
    sprintf(ecspi1_5->pin_config[3],"100b1");
    sprintf(ecspi1_5->pin_config[4],"100b1");
    return;
}

void process_ecspi1_4(void)
{
    ecspi1_4 = calloc(1,sizeof(iomux_ecspi_4));
    sprintf(ecspi1_4->grp_name,"ecspi1grp");
    sprintf(ecspi1_4->pinctrl0_name,"pinctrl_ecspi1");
    sprintf(ecspi1_4->mosi_pin_name,"MX6QDL_PAD_DISP0_DAT21__ECSPI1_MOSI");
    sprintf(ecspi1_4->miso_pin_name,"MX6QDL_PAD_DISP0_DAT22__ECSPI1_MISO");
    sprintf(ecspi1_4->sclk_pin_name,"MX6QDL_PAD_DISP0_DAT20__ECSPI1_SCLK");
    sprintf(ecspi1_4->ss0_pin_name,"MX6QDL_PAD_DISP0_DAT23__GPIO5_IO17");
    sprintf(ecspi1_4->pin_config[0],"100b1");
    sprintf(ecspi1_4->pin_config[1],"100b1");
    sprintf(ecspi1_4->pin_config[2],"100b1");
    sprintf(ecspi1_4->pin_config[3],"100b1");
    return;
}

void process_ecspi2_5(void)
{
    ecspi2_5 = calloc(1,sizeof(iomux_ecspi_5));
    sprintf(ecspi2_5->grp_name,"ecspi2grp");
    sprintf(ecspi2_5->pinctrl0_name,"pinctrl_ecspi2");
    sprintf(ecspi2_5->mosi_pin_name,"MX6QDL_PAD_DISP0_DAT16__ECSPI2_MOSI");
    sprintf(ecspi2_5->miso_pin_name,"MX6QDL_PAD_DISP0_DAT17__ECSPI2_MISO");
    sprintf(ecspi2_5->sclk_pin_name,"MX6QDL_PAD_DISP0_DAT19__ECSPI2_SCLK");
    sprintf(ecspi2_5->ss0_pin_name,"MX6QDL_PAD_DISP0_DAT18__GPIO5_IO12");
    sprintf(ecspi2_5->ss1_pin_name,"MX6QDL_PAD_DISP0_DAT15__GPIO5_IO09");
    sprintf(ecspi2_5->pin_config[0],"100b1");
    sprintf(ecspi2_5->pin_config[1],"100b1");
    sprintf(ecspi2_5->pin_config[2],"100b1");
    sprintf(ecspi2_5->pin_config[3],"100b1");
    sprintf(ecspi2_5->pin_config[4],"100b1");
    return;
}

void process_ecspi2_4(void)
{
    ecspi2_4 = calloc(1,sizeof(iomux_ecspi_4));
    sprintf(ecspi2_4->grp_name,"ecspi2grp");
    sprintf(ecspi2_4->pinctrl0_name,"pinctrl_ecspi2");
    sprintf(ecspi2_4->mosi_pin_name,"MX6QDL_PAD_DISP0_DAT16__ECSPI2_MOSI");
    sprintf(ecspi2_4->miso_pin_name,"MX6QDL_PAD_DISP0_DAT17__ECSPI2_MISO");
    sprintf(ecspi2_4->sclk_pin_name,"MX6QDL_PAD_DISP0_DAT19__ECSPI2_SCLK");
    sprintf(ecspi2_4->ss0_pin_name,"MX6QDL_PAD_DISP0_DAT18__GPIO5_IO12");
    sprintf(ecspi2_4->pin_config[0],"100b1");
    sprintf(ecspi2_4->pin_config[1],"100b1");
    sprintf(ecspi2_4->pin_config[2],"100b1");
    sprintf(ecspi2_4->pin_config[3],"100b1");
    return;
}

void process_ecspi3_5(void)
{
    ecspi3_5 = calloc(1,sizeof(iomux_ecspi_5));
    sprintf(ecspi3_5->grp_name,"ecspi3grp");
    sprintf(ecspi3_5->pinctrl0_name,"pinctrl_ecspi3");
    sprintf(ecspi3_5->mosi_pin_name,"MX6QDL_PAD_DISP0_DAT1__ECSPI3_MOSI");
    sprintf(ecspi3_5->miso_pin_name,"MX6QDL_PAD_DISP0_DAT2__ECSPI3_MISO");
    sprintf(ecspi3_5->sclk_pin_name,"MX6QDL_PAD_DISP0_DAT0__ECSPI3_SCLK");
    sprintf(ecspi3_5->ss0_pin_name,"MX6QDL_PAD_DISP0_DAT3__GPIO4_IO24");
    sprintf(ecspi3_5->ss1_pin_name,"MX6QDL_PAD_DISP0_DAT4__GPIO4_IO25");
    sprintf(ecspi3_5->pin_config[0],"100b1");
    sprintf(ecspi3_5->pin_config[1],"100b1");
    sprintf(ecspi3_5->pin_config[2],"100b1");
    sprintf(ecspi3_5->pin_config[3],"100b1");
    sprintf(ecspi3_5->pin_config[4],"100b1");
    return;
}

void process_ecspi3_4(void)
{
    ecspi3_4 = calloc(1,sizeof(iomux_ecspi_4));
    sprintf(ecspi3_4->grp_name,"ecspi3grp");
    sprintf(ecspi3_4->pinctrl0_name,"pinctrl_ecspi3");
    sprintf(ecspi3_4->mosi_pin_name,"MX6QDL_PAD_DISP0_DAT1__ECSPI3_MOSI");
    sprintf(ecspi3_4->miso_pin_name,"MX6QDL_PAD_DISP0_DAT2__ECSPI3_MISO");
    sprintf(ecspi3_4->sclk_pin_name,"MX6QDL_PAD_DISP0_DAT0__ECSPI3_SCLK");
    sprintf(ecspi3_4->ss0_pin_name,"MX6QDL_PAD_DISP0_DAT3__GPIO4_IO24");
    sprintf(ecspi3_4->pin_config[0],"100b1");
    sprintf(ecspi3_4->pin_config[1],"100b1");
    sprintf(ecspi3_4->pin_config[2],"100b1");
    sprintf(ecspi3_4->pin_config[3],"100b1");
    return;
}

void process_ecspi4(void)
{
    ecspi4 = calloc(1,sizeof(iomux_ecspi_4));
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

void process_i2c1a(void)
{
    i2c1a = calloc(1,sizeof(iomux_i2c));
    sprintf(i2c1a->grp_name,"i2c1grp");
    sprintf(i2c1a->pinctrl0_name,"pinctrl_i2c1");
    sprintf(i2c1a->sda_pin_name,"MX6QDL_PAD_EIM_D28__I2C1_SDA");
    sprintf(i2c1a->scl_pin_name,"MX6QDL_PAD_EIM_D21__I2C1_SCL");
    sprintf(i2c1a->pin_config[0],"4001b8b1");
    sprintf(i2c1a->pin_config[1],"4001b8b1");
    return;
}

void process_i2c3(void)
{
    i2c3 = calloc(1,sizeof(iomux_i2c));
    sprintf(i2c3->grp_name,"i2c3grp");
    sprintf(i2c3->pinctrl0_name,"pinctrl_i2c3");
    sprintf(i2c3->sda_pin_name,"MX6QDL_PAD_EIM_D18__I2C3_SDA");
    sprintf(i2c3->scl_pin_name,"MX6QDL_PAD_EIM_D17__I2C3_SCL");
    sprintf(i2c3->pin_config[0],"4001b8b1");
    sprintf(i2c3->pin_config[1],"4001b8b1");
    return;
}


void parse_special_iomux(void)
{
    iomux = calloc(1,sizeof(iomux_cfg));
    /* Set system peripherals */
    iomux->uart3 = 1;   /* console */
    iomux->uart5 = 1;   /* rs485 */
    iomux->i2c2 = 1;    /* edid for hdmi */
    /* On J13 */
    if ( strstr(file_contents,"P_ECSPI1_MISO_comboBox=AUD4_TXFS"))
    {
        iomux->audio4 = 1;
        process_audio4();
    }
    if ( strstr(file_contents,"P_ECSPI1_MISO_comboBox=ECSPI1_MISO"))
    {
        if ( strstr(file_contents,"P_ECSPI2_SS1_comboBox=ECSPI1_SS1"))
        {
            iomux->ecspi1_5 = 1;
            process_ecspi1_5();
        }
        else
        {
            iomux->ecspi1_4 = 1;
            process_ecspi1_4();
        }
    }
    if ( strstr(file_contents,"P_ECSPI2_MISO_comboBox=AUD5_TXD"))
    {
        iomux->audio5 = 1;
        process_audio5();
    }
    if ( strstr(file_contents,"P_ECSPI2_MISO_comboBox=ECSPI2_MISO"))
    {
        if ( strstr(file_contents,"P_ECSPI2_SS1_comboBox=ECSPI2_SS1"))
        {
            iomux->ecspi2_5 = 1;
            process_ecspi2_5();
        }
        else
        {
            iomux->ecspi2_4 = 1;
            process_ecspi2_4();
        }
    }
    if ( strstr(file_contents,"P_ECSPI3_MISO_comboBox=ECSPI3_MISO"))
    {
        if ( strstr(file_contents,"P_ECSPI3_SS1_comboBox=ECSPI3_SS1"))
        {
            iomux->ecspi3_5 = 1;
            process_ecspi3_5();
        }
        else
        {
            iomux->ecspi3_4 = 1;
            process_ecspi3_4();
        }
    }

    if ( strstr(file_contents,"P_ECSPI4_MISO_comboBox=ECSPI4_MISO"))
    {
        iomux->ecspi4 = 1;
        process_ecspi4();
    }
    if ( strstr(file_contents,"P_ECSPI4_MISO_comboBox=SPDIF_OUT"))
    {
        process_spdif1();
        iomux->spdif1 = 1;
    }
    if ( strstr(file_contents,"P_ECSPI4_MOSI_comboBox=I2C1_SDA"))
    {
        process_i2c1a();
        iomux->i2c1a = 1;
    }
    if ( strstr(file_contents,"P_I2C3_SDA_comboBox=I2C3_SDA"))
    {
        process_i2c3();
        iomux->i2c3 = 1;
    }
    if ( strstr(file_contents,"P_KHZ32_CLK_OUT_comboBox=32KHZ_CLK_OUT"))
    {
        process_clk32k();
        iomux->clk32k = 1;
    }
    if ( strstr(file_contents,"P_SD3_CMD_comboBox=SD3_CMD"))
    {
        if ( strstr(file_contents,"P_SD3_DATA4_comboBox=SD3_DATA4"))
        {
            process_sd3_8();
            iomux->sd3_8 = 1;
        }
        else
        {
            process_sd3_4();
            iomux->sd3_4 = 1;
        }
    }

    if ( strstr(file_contents,"P_SD3_CMD_comboBox=FLEXCAN1_TX"))
    {
        process_can1();
        iomux->can1 = 1;
    }
    if ( strstr(file_contents,"P_SD3_DATA0_comboBox=FLEXCAN2_TX"))
    {
        process_can2();
        iomux->can2 = 1;
    }
    if ( strstr(file_contents,"P_SD3_DATA4_comboBox=UART2_RXD"))
    {
        if ( strstr(file_contents,"P_SD3_CMD_comboBox==UART2_CTS_B"))
        {
            iomux->uart2_4 = 1;
            process_uart2_4();
        }
        else
        {
            iomux->uart2_2 = 1;
            process_uart2_2();
        }
    }
    else
    {
        iomux->uart2_2 = 1;
        process_uart2_2aux();
    }

    /* On J9 */
    if ( strstr(file_contents,"P_GPIO3_IO20_comboBox=XTALOSC_REF_CLK_24M"))
    {
        process_clk24m();
        iomux->clk24m = 1;
    }
    if ( strstr(file_contents,"P_GPIO1_IO00_comboBox=CCM_CLKO1"))
    {
        process_clko1();
        iomux->ccm_clko1 = 1;
    }
    if ( strstr(file_contents,"P_GPIO1_IO00_comboBox=CCM_CLKO1"))
    {
        process_epit1();
        iomux->epit1 = 1;
    }
    if ( strstr(file_contents,"P_GPIO4_IO29_comboBox=PWM1_OUT"))
    {
        process_pwm1();
        iomux->pwm1 = 1;
    }
    if ( strstr(file_contents,"P_GPIO4_IO29_comboBox=WDOG1_B"))
    {
        process_wdog();
        iomux->wdog = 1;
    }
    if ( strstr(file_contents,"P_AUD6_TXD_comboBox=AUD6_TXD"))
    {
        iomux->audio6 = 1;
        process_audio6();
    }
    if ( strstr(file_contents,"P_I2C1_SDA_comboBox=I2C1_SDA"))
    {
        process_i2c1b();
        iomux->i2c1b = 1;
    }
    if ( strstr(file_contents,"P_UART1_TXD_comboBox=UART1_TXD"))
    {
        process_uart1();
        iomux->uart1 = 1;
    }
    if ( strstr(file_contents,"P_UART4_TXD_comboBox=UART4_TXD"))
    {
        if ( strstr(file_contents,"P_UART4_RTS_L_comboBox=UART4_RTS_L"))
        {
            iomux->uart4_4 = 1;
            process_uart4_4();
        }
        else
        {
            iomux->uart4_2 = 1;
            process_uart4_2();
        }
    }
    if ( strstr(file_contents,"P_SPDIF_OUT_comboBox=SPDIF_OUT"))
    {
        process_spdif2();
        iomux->spdif2 = 1;
    }

    if ( strstr(file_contents,"P_SATA_checkBox=true"))
        iomux->sata = 1;
    if ( strstr(file_contents,"P_PCIe_checkBox=true"))
        iomux->pcie = 1;
    if ( strstr(file_contents,"defaultVideo_comboBox=HDMI 1920x1080"))
        sprintf(iomux->video,"HDMI1920x1080");
    if ( strstr(file_contents,"defaultVideo_comboBox=HDMI 1280x720"))
        sprintf(iomux->video,"HDMI1280x720");
    if ( strstr(file_contents,"P_SPIdev1_checkBox=true"))
        iomux->ecspi1_dev = 1;
    if ( strstr(file_contents,"P_SPIdev2_checkBox=true"))
        iomux->ecspi2_dev = 1;
    if ( strstr(file_contents,"P_SPIdev3_checkBox=true"))
        iomux->ecspi3_dev = 1;
    if ( strstr(file_contents,"P_SPIdev4_checkBox=true"))
        iomux->ecspi4_dev = 1;
}

