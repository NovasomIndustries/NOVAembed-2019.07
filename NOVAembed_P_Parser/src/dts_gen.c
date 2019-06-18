#include "../include/NOVAembed_P_parser.h"
#include "../include/header.h"

char    dtsfile_dump[1024];
char    dtsifile_dump[65536];
char    file_name[32],file_name_noext[32],dir_name[256];
char    file_name_dts[128],file_name_dtsi[128];
char    hog[1024];
char    gpio_hogs[2048];

void create_dts_file(void)
{
FILE    *fpout_dts;
char    tstr[256];
    if ( strstr(file_contents,"Processor=QUAD"))
    {
        sprintf(dtsfile_dump,dts_defs_part1_QUAD);
        sprintf(tstr,"#include \"%s\"\n",file_name_dtsi);
        strcat(dtsfile_dump,tstr);
        strcat(dtsfile_dump,dts_defs_part2_SOLO_DL);
        if (iomux->sata == 1)
            strcat(dtsfile_dump,dts_defs_sata);
    }
    else
    {
        sprintf(dtsfile_dump,dts_defs_part1_SOLO_DL);
        sprintf(tstr,"#include \"%s\"\n",file_name_dtsi);
        strcat(dtsfile_dump,tstr);
        strcat(dtsfile_dump,dts_defs_part2_QUAD);
    }
    printf("Writing %s\n",file_name_dts);
    if ( (fpout_dts = fopen(file_name_dts,"w" ) ))
    {
        fwrite(dtsfile_dump, strlen(dtsfile_dump), 1, fpout_dts);
        fclose(fpout_dts);
    }
    else
    printf("Error\n");
}

char    sf[2048];
char    t[512];
void process_sf(void)
{
    if ( pwm != NULL )
    {
        sprintf(sf,"        %s: %s{\n",pwm->pinctrl0_name,pwm->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",pwm->pwm_pin_name,pwm->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"      };\n");
        strcat(dtsifile_dump,sf);
    }
    printf("%s : epit1\n",__FUNCTION__);
    if ( epit1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",epit1->pinctrl0_name,epit1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",epit1->epit_pin_name,epit1->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"      };\n");
        strcat(dtsifile_dump,sf);
    }
    printf("%s : sdcard_8\n",__FUNCTION__);
    if ( sdcard_8 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",sdcard_8->pinctrl0_name,sdcard_8->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",sdcard_8->cmd_pin_name,sdcard_8->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->clk_pin_name,sdcard_8->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data0_pin_name,sdcard_8->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data1_pin_name,sdcard_8->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data2_pin_name,sdcard_8->pin_config[4]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data3_pin_name,sdcard_8->pin_config[5]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data4_pin_name,sdcard_8->pin_config[6]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data5_pin_name,sdcard_8->pin_config[7]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data6_pin_name,sdcard_8->pin_config[8]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_8->data7_pin_name,sdcard_8->pin_config[9]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    printf("%s : sdcard_4\n",__FUNCTION__);
    if ( sdcard_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",sdcard_4->pinctrl0_name,sdcard_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",sdcard_4->cmd_pin_name,sdcard_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_4->clk_pin_name,sdcard_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_4->data0_pin_name,sdcard_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_4->data1_pin_name,sdcard_4->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_4->data2_pin_name,sdcard_4->pin_config[4]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard_4->data3_pin_name,sdcard_4->pin_config[5]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    printf("%s : spdif\n",__FUNCTION__);
    if ( spdif != NULL )
    {
        sprintf(sf,"        %s: %s{\n",spdif->pinctrl0_name,spdif->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",spdif->spdif_pin_name,spdif->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( can1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",can1->pinctrl0_name,can1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",can1->cantx_pin_name,can1->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",can1->canrx_pin_name,can1->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( can2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",can2->pinctrl0_name,can2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",can2->cantx_pin_name,can2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",can2->canrx_pin_name,can2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart1->pinctrl0_name,uart1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart1->uart_txd_pin_name,uart1->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart1->uart_rxd_pin_name,uart1->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart2_2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart2_2->pinctrl0_name,uart2_2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart2_2->uart_txd_pin_name,uart2_2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_2->uart_rxd_pin_name,uart2_2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart4_2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart4_2->pinctrl0_name,uart4_2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart4_2->uart_txd_pin_name,uart4_2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_2->uart_rxd_pin_name,uart4_2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart2_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart2_4->pinctrl0_name,uart2_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_txd_pin_name,uart2_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_rxd_pin_name,uart2_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_rts_pin_name,uart2_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_cts_pin_name,uart2_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart4_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart4_4->pinctrl0_name,uart4_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_txd_pin_name,uart4_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_rxd_pin_name,uart4_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_rts_pin_name,uart4_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_cts_pin_name,uart4_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( audio4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",audio4->pinctrl0_name,audio4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",audio4->aud_rxd_pin_name,audio4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio4->aud_txc_pin_name,audio4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio4->aud_txd_pin_name,audio4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio4->aud_txfs_pin_name,audio4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( audio5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",audio5->pinctrl0_name,audio5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",audio5->aud_rxd_pin_name,audio5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio5->aud_txc_pin_name,audio5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio5->aud_txd_pin_name,audio5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio5->aud_txfs_pin_name,audio5->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( audio6 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",audio6->pinctrl0_name,audio6->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",audio6->aud_rxd_pin_name,audio6->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio6->aud_txc_pin_name,audio6->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio6->aud_txd_pin_name,audio6->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio6->aud_txfs_pin_name,audio6->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( ecspi1_5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi1_5->pinctrl0_name,ecspi1_5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi1_5->mosi_pin_name,ecspi1_5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->miso_pin_name,ecspi1_5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->sclk_pin_name,ecspi1_5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->ss0_pin_name,ecspi1_5->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->ss1_pin_name,ecspi1_5->pin_config[4]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi1_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi1_4->pinctrl0_name,ecspi1_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi1_4->mosi_pin_name,ecspi1_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_4->miso_pin_name,ecspi1_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_4->sclk_pin_name,ecspi1_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_4->ss0_pin_name,ecspi1_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi2_5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi2_5->pinctrl0_name,ecspi2_5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi2_5->mosi_pin_name,ecspi2_5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->miso_pin_name,ecspi2_5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->sclk_pin_name,ecspi2_5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->ss0_pin_name,ecspi2_5->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->ss1_pin_name,ecspi2_5->pin_config[4]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi2_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi2_4->pinctrl0_name,ecspi2_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi2_4->mosi_pin_name,ecspi2_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_4->miso_pin_name,ecspi2_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_4->sclk_pin_name,ecspi2_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_4->ss0_pin_name,ecspi2_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( ecspi3_5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi3_5->pinctrl0_name,ecspi3_5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi3_5->mosi_pin_name,ecspi3_5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->miso_pin_name,ecspi3_5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->sclk_pin_name,ecspi3_5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->ss0_pin_name,ecspi3_5->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->ss1_pin_name,ecspi3_5->pin_config[4]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi3_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi3_4->pinctrl0_name,ecspi3_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi3_4->mosi_pin_name,ecspi3_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_4->miso_pin_name,ecspi3_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_4->sclk_pin_name,ecspi3_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_4->ss0_pin_name,ecspi3_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi4->pinctrl0_name,ecspi4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi4->mosi_pin_name,ecspi4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi4->miso_pin_name,ecspi4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi4->sclk_pin_name,ecspi4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi4->ss0_pin_name,ecspi4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( i2c1a != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c1a->pinctrl0_name,i2c1a->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c1a->sda_pin_name,i2c1a->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c1a->scl_pin_name,i2c1a->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( i2c1b != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c1b->pinctrl0_name,i2c1b->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c1b->sda_pin_name,i2c1b->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c1b->scl_pin_name,i2c1b->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( i2c3 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c3->pinctrl0_name,i2c3->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c3->sda_pin_name,i2c3->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c3->scl_pin_name,i2c3->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    sprintf (sf,"    };\n");
    strcat (sf," };\n");
    strcat(dtsifile_dump,sf);
    printf("%s : finished\n",__FUNCTION__);
}

int extract_speed(char *speed_var_ptr)
{
char    *duplicate;
    duplicate = strdup(speed_var_ptr);
    *index(duplicate,0x0a)=0;
    duplicate += strlen("P_I2C1Speed=");
    //printf("%s : %s %d %d\n",__func__,duplicate,strlen(duplicate),atoi(duplicate));
    return(atoi(duplicate));
}

void process_special_devs(void)
{
char    t[1024];
int     speed;

    if (( iomux->i2c1a == 1 ) || ( iomux->i2c1b == 1 ))
    {
        sprintf(t,i2c1_defs_top);
        strcat(dtsifile_dump,t);
        speed = extract_speed(strstr(file_contents,"P_I2C1Speed="));
        sprintf(t,"        clock-frequency = <%d>;\n",speed);
        strcat(dtsifile_dump,t);
        strcat(dtsifile_dump,i2c1_defs_bottom);
    }
    if ( iomux->i2c3 == 1 )
    {
        sprintf(t,i2c3_defs_top);
        strcat(dtsifile_dump,t);
        speed = extract_speed(strstr(file_contents,"P_I2C3Speed="));
        sprintf(t,"        clock-frequency = <%d>;\n",speed);
        strcat(dtsifile_dump,t);
        strcat(dtsifile_dump,i2c3_defs_bottom);
    }
    if ( iomux->pcie == 1 )
    {
        sprintf(t,pcie_enabled_defs);
    }
    else
    {
        sprintf(t,pcie_disabled_defs);
    }
    strcat(dtsifile_dump,t);
    if (( iomux->spdif1 == 1 ) || ( iomux->spdif2 == 1 ))
    {
        sprintf(t,spdif_enabled_defs);
        strcat(dtsifile_dump,t);
    }

    if ( iomux->uart1 == 1 )
    {
        sprintf(t,uart1_defs);
        strcat(dtsifile_dump,t);
    }

    if ( iomux->uart2_4 == 1 )
    {
        sprintf(t,uart2_4_defs);
        strcat(dtsifile_dump,t);
    }

    if ( iomux->uart2_2 == 1 )
    {
        sprintf(t,uart2_2_defs);
        strcat(dtsifile_dump,t);
    }

    if ( iomux->uart2_2 == 0 )
    {
        sprintf(t,uart2_2_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->uart4_4 == 1 )
    {
        sprintf(t,uart4_4_defs);
        strcat(dtsifile_dump,t);
    }

    if ( iomux->uart4_2 == 1 )
    {
        sprintf(t,uart4_2_defs);
        strcat(dtsifile_dump,t);
    }

    if ( iomux->ecspi1_4 == 1 )
    {
        if ( iomux->ecspi1_dev == 1)
            sprintf(t,ecspi1_dev_4_defs);
        else
            sprintf(t,ecspi1_4_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->ecspi1_5 == 1 )
    {
        if ( iomux->ecspi1_dev == 1)
            sprintf(t,ecspi1_dev_5_defs);
        else
            sprintf(t,ecspi1_5_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->ecspi2_4 == 1 )
    {
        if ( iomux->ecspi2_dev == 1)
            sprintf(t,ecspi2_dev_4_defs);
        else
            sprintf(t,ecspi2_4_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->ecspi2_5 == 1 )
    {
        if ( iomux->ecspi2_dev == 1)
            sprintf(t,ecspi2_dev_5_defs);
        else
            sprintf(t,ecspi2_5_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->ecspi3_4 == 1 )
    {
        if ( iomux->ecspi3_dev == 1)
            sprintf(t,ecspi3_dev_4_defs);
        else
            sprintf(t,ecspi3_4_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->ecspi3_5 == 1 )
    {
        if ( iomux->ecspi3_dev == 1)
            sprintf(t,ecspi3_dev_5_defs);
        else
            sprintf(t,ecspi3_5_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->ecspi4 == 1 )
    {
        if ( iomux->ecspi4_dev == 1)
            sprintf(t,ecspi4_dev_4_defs);
        else
            sprintf(t,ecspi4_4_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->audio4 == 1 )
    {
        sprintf(t,audmux4_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->audio5 == 1 )
    {
        sprintf(t,audmux5_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->audio6 == 1 )
    {
        sprintf(t,audmux6_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->can1 == 1 )
    {
        sprintf(t,can1_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->can2 == 1 )
    {
        sprintf(t,can2_defs);
        strcat(dtsifile_dump,t);
    }
    if ( iomux->sd3_4 == 1 )
    {
        sprintf(t,usdhc3_4_defs);
        strcat(dtsifile_dump,t);
    }
}

void process_videos_header(void)
{
char    mxcfb[1024];

    //printf("***\n");
    if (strstr(file_contents,"PrimaryVideo_comboBox=HDMI"))
    {
        if (strstr(file_contents,"PrimaryVideo_comboBox=HDMI 1920x1080"))
            sprintf(mxcfb,dtsi_header_hdmivideo1920_mxcfb1_defs);
        else
            sprintf(mxcfb,dtsi_header_hdmivideo1280_mxcfb1_defs);
        if ( strstr(file_contents,"P_SecVideo_24bit_checkBox=true"))
            strcat(mxcfb,dtsi_header_lvdsvideo_mxcfb2_24_defs);
        else
            strcat(mxcfb,dtsi_header_lvdsvideo_mxcfb2_18_defs);
        strcat(mxcfb,dtsi_header_lvdsvideo_mxcfb3_18_defs);
    }

    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS"))
    {
        printf("PrimaryVideo_comboBox=LVDS\n");

        if ( strstr(file_contents,"P_PriVideo_24bit_checkBox=true"))
            sprintf(mxcfb,dtsi_header_lvdsvideo_mxcfb1_24_defs);
        else
            sprintf(mxcfb,dtsi_header_lvdsvideo_mxcfb1_18_defs);

        if (strstr(file_contents,"SecondaryVideo_comboBox=HDMI"))
        {
            if (strstr(file_contents,"SecondaryVideo_comboBox=HDMI 1920x1080"))
                strcat(mxcfb,dtsi_header_hdmivideo1920_mxcfb2_defs);
            else
                strcat(mxcfb,dtsi_header_hdmivideo1280_mxcfb2_defs);
        }
        else
        {
            if ( strstr(file_contents,"P_SecVideo_24bit_checkBox=true"))
                strcat(mxcfb,dtsi_header_lvdsvideo_mxcfb2_24_defs);
            else
                strcat(mxcfb,dtsi_header_lvdsvideo_mxcfb2_18_defs);
        }
        strcat(mxcfb,dtsi_header_lvdsvideo_mxcfb3_18_defs);
    }
    strcat(mxcfb,dtsi_footer_video_defs);
    //printf("%s\n",mxcfb);
    //printf("***\n");
    strcat(dtsifile_dump,mxcfb);
}

void apply_spwg_jeida_pri(char *ldb)
{
    printf("%s\n",ldb);
    if (strstr(file_contents,"P_PriVideo_spwg_checkBox=true"))
    {
        printf("P_PriVideo_spwg_checkBox=true!\n");
        char * pch;
        pch = strstr (ldb,"\"jeida\";");
        if ( pch != NULL )
        {
            strncpy (pch,"\"spwg\" ;",7);
            printf("Found!\n");
        }
        printf("PriVideo : spwg\n");
    }
    else
    {
        printf("P_PriVideo_spwg_checkBox=false!\n");
        char * pch;
        pch = strstr (ldb,"\"spwg\" ;");
        if ( pch != NULL )
        {
            strncpy (pch,"\"jeida\" ;",7);
            printf("Found!\n");
        }
        printf("PriVideo : jeida\n");
    }
    printf("%s\n",ldb);
}

void apply_spwg_jeida_sec(char *ldb)
{
char * pch;
int secjeida=0;
    if (strstr(file_contents,"P_SecVideo_spwg_checkBox=true"))
    {
        char * pch;
        pch = strstr (ldb,"\"jeida\";");
        if ( pch != NULL )
            strncpy (pch,"\"spwg\" ;",7);
        printf("SecVideo : spwg\n");
    }
    else
    {
        printf("P_SecVideo_spwg_checkBox=false!\n");
        pch = strstr (ldb,"\"spwg\" ;");
        if ( pch != NULL )
        {
            strncpy (pch,"\"jeida\" ;",7);
            secjeida=1;
            /*
            char * pch1;
            pch1 = strstr (ldb,"fsl,data-width = <18>;");
            if ( pch1 != NULL )
                strncpy (pch,"fsl,data-width = <24>;",22);
                */
            printf("Found!\n");
        }
        if ( secjeida )
        {
            pch = strstr (ldb,"fsl,data-width = <18>;");
            if ( pch != NULL )
                strncpy (pch,"fsl,data-width = <24>;",22);
        }
        printf("SecVideo : jeida\n");
    }
}

char    ldb[16384];
void process_lvds_channels(void)
{

    sprintf(ldb,dtsi_lvds_header_defs);
    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS 800x480"))
    {
        apply_spwg_jeida_pri(lvds_800x480_ch0_parserinput);
        strcat(ldb,lvds_800x480_ch0_parserinput);
        printf("PrimaryVideo   : LVDS 800x480\n");
    }
    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS 800x600"))
    {
        apply_spwg_jeida_pri(lvds_800x600_ch0_parserinput);
        strcat(ldb,lvds_800x600_ch0_parserinput);
        printf("PrimaryVideo   : LVDS 800x600\n");
    }
    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS 1024x600"))
    {
        apply_spwg_jeida_pri(lvds_1024x600_ch0_parserinput);
        strcat(ldb,lvds_1024x600_ch0_parserinput);
        printf("PrimaryVideo   : LVDS 1024x600\n");
    }
    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS 1024x768"))
    {
        apply_spwg_jeida_pri(lvds_1024x768_ch0_parserinput);
        strcat(ldb,lvds_1024x768_ch0_parserinput);
        printf("PrimaryVideo   : LVDS 1024x768\n");
    }
    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS 1280x800"))
    {
        apply_spwg_jeida_pri(lvds_1280x800_ch0_parserinput);
        strcat(ldb,lvds_1280x800_ch0_parserinput);
        printf("PrimaryVideo   : LVDS 1280x800\n");
    }
    if (strstr(file_contents,"PrimaryVideo_comboBox=LVDS 1366x768"))
    {
        apply_spwg_jeida_pri(lvds_1366x768_ch0_parserinput);
        strcat(ldb,lvds_1366x768_ch0_parserinput);
        printf("PrimaryVideo   : LVDS 1366x768\n");
    }

    if (strstr(file_contents,"SecondaryVideo_comboBox=LVDS 800x480"))
    {
        apply_spwg_jeida_sec(lvds_800x480_ch1_parserinput);
        strcat(ldb,lvds_800x480_ch1_parserinput);
        printf("SecondaryVideo : LVDS 800x480\n");
    }
    if (strstr(file_contents,"SecondaryVideo_comboBox=LVDS 800x600"))
    {
        apply_spwg_jeida_sec(lvds_800x600_ch1_parserinput);
        strcat(ldb,lvds_800x600_ch1_parserinput);
        printf("SecondaryVideo : LVDS 800x600\n");
    }
    if (strstr(file_contents,"SecondaryVideo_comboBox=LVDS 1024x600"))
    {
        apply_spwg_jeida_sec(lvds_1024x600_ch1_parserinput);
        strcat(ldb,lvds_1024x600_ch1_parserinput);
        printf("SecondaryVideo : LVDS 1024x600\n");
    }
    if (strstr(file_contents,"SecondaryVideo_comboBox=LVDS 1024x768"))
    {
        apply_spwg_jeida_sec(lvds_1024x768_ch1_parserinput);
        strcat(ldb,lvds_1024x768_ch1_parserinput);
        printf("SecondaryVideo : LVDS 1024x768\n");
    }
    if (strstr(file_contents,"SecondaryVideo_comboBox=LVDS 1280x800"))
    {
        apply_spwg_jeida_sec(lvds_1280x800_ch1_parserinput);
        strcat(ldb,lvds_1280x800_ch1_parserinput);
        printf("SecondaryVideo : LVDS 1280x800\n");
    }
    if (strstr(file_contents,"SecondaryVideo_comboBox=LVDS 1366x768"))
    {
        apply_spwg_jeida_sec(lvds_1366x768_ch1_parserinput);
        strcat(ldb,lvds_1366x768_ch1_parserinput);
        printf("SecondaryVideo   : LVDS 1366x768\n");
    }
    strcat(ldb,dtsi_lvds_footer_defs);
    strcat(dtsifile_dump,ldb);
}

void process_special_hogs(void)
{
char    t[128];
    sprintf(hog,"        pinctrl_hog: hoggrp {\n");
    strcat (hog,"            fsl,pins = <\n");
    if ( clk32k != NULL)
    {
        sprintf(t,"                %s 0x%s\n",clk32k->hog_pin_name,clk32k->pin_config[0]);
        strcat (hog,t);
    }
    if ( clk24m != NULL)
    {
        sprintf(t,"                %s 0x%s\n",clk24m->hog_pin_name,clk24m->pin_config[0]);
        strcat (hog,t);
    }
    if ( ccm_clko1 != NULL)
    {
        sprintf(t,"                %s 0x%s\n",ccm_clko1->hog_pin_name,ccm_clko1->pin_config[0]);
        strcat (hog,t);
    }
    if ( wdog != NULL)
    {
        sprintf(t,"                %s 0x%s\n",wdog->hog_pin_name,wdog->pin_config[0]);
        strcat (hog,t);
    }
}

char *generate_hog_gpio( char *combobox_string , char *pin_name_string)
{
char    *tdest;
char    *cbit_string,*dup_string;
char    *tsource,t1[128];

    dup_string = strdup(combobox_string);
    cbit_string = strsep(&dup_string,"comboBox=");
    strcat(cbit_string,"cbit=");
    tdest = calloc(1,128);
    if ( strstr(file_contents,combobox_string))
    {
        if ((tsource = strstr(file_contents,cbit_string)))
        {
            copy_and_resize(t1,tsource+strlen(cbit_string));
            sprintf(tdest,"                %s 0x%s\n",pin_name_string,t1);
            return tdest;
        }
    }
    sprintf(tdest,"-");
    return tdest;
}

gpio_support    gpios[] =
{
    { "P_ECSPI1_MISO_comboBox=GPIO5_IO16"  , "MX6QDL_PAD_DISP0_DAT22__GPIO5_IO16" },
    { "P_ECSPI1_MOSI_comboBox=GPIO5_IO15"  , "MX6QDL_PAD_DISP0_DAT21__GPIO5_IO15" },
    { "P_ECSPI1_SS0_comboBox=GPIO5_IO17"   , "MX6QDL_PAD_DISP0_DAT23__GPIO5_IO17" },
    { "P_ECSPI1_SCK_comboBox=GPIO5_IO14"   , "MX6QDL_PAD_DISP0_DAT20__GPIO5_IO14" },
    { "P_ECSPI2_SS1_comboBox=GPIO5_IO09"   , "MX6QDL_PAD_DISP0_DAT15__GPIO5_IO09" },
    { "P_ECSPI2_MISO_comboBox=GPIO5_IO11"  , "MX6QDL_PAD_DISP0_DAT17__GPIO5_IO11" },
    { "P_ECSPI2_MOSI_comboBox=GPIO5_IO10"  , "MX6QDL_PAD_DISP0_DAT16__GPIO5_IO10" },
    { "P_ECSPI2_SCK_comboBox=GPIO5_IO13"   , "MX6QDL_PAD_DISP0_DAT19__GPIO5_IO13" },
    { "P_ECSPI3_MISO_comboBox=GPIO4_IO23"  , "MX6QDL_PAD_DISP0_DAT2__GPIO4_IO23 " },
    { "P_ECSPI3_SCK_comboBox=GPIO4_IO21"   , "MX6QDL_PAD_DISP0_DAT0__GPIO4_IO21 " },
    { "P_ECSPI3_MOSI_comboBox=GPIO4_IO22"  , "MX6QDL_PAD_DISP0_DAT1__GPIO4_IO22 " },
    { "P_ECSPI3_SS0_comboBox=GPIO4_IO24"   , "MX6QDL_PAD_DISP0_DAT3__GPIO4_IO24 " },
    { "P_ECSPI3_SS1_comboBox=GPIO4_IO25"   , "MX6QDL_PAD_DISP0_DAT4__GPIO4_IO25 " },
    { "P_ECSPI4_MISO_comboBox=GPIO3_IO22"  , "MX6QDL_PAD_EIM_D22__GPIO3_IO22    " },
    { "P_ECSPI4_MOSI_comboBox=GPIO3_IO28"  , "MX6QDL_PAD_EIM_D28__GPIO3_IO28    " },
    { "P_ECSPI4_SCK_comboBox=GPIO3_IO21"   , "MX6QDL_PAD_EIM_D21__GPIO3_IO21    " },
    { "P_ECSPI4_SS0_comboBox=GPIO3_IO29"   , "MX6QDL_PAD_EIM_D29__GPIO3_IO29    " },
    { "P_I2C3_SCL_comboBox=GPIO3_IO17"     , "MX6QDL_PAD_EIM_D17__GPIO3_IO17    " },
    { "P_I2C3_SDA_comboBox=GPIO3_IO18"     , "MX6QDL_PAD_EIM_D18__GPIO3_IO18    " },
    { "P_KHZ32_CLK_OUT_comboBox=GPIO1_IO08", "MX6QDL_PAD_GPIO_8__GPIO1_IO08     " },
    { "P_SD3_CMD_comboBox=GPIO7_IO02"      , "MX6QDL_PAD_SD3_CMD__GPIO7_IO02    " },
    { "P_SD3_CLK_comboBox=GPIO7_IO03"      , "MX6QDL_PAD_SD3_CLK__GPIO7_IO03    " },
    { "P_SD3_DATA0_comboBox=GPIO7_IO04"    , "MX6QDL_PAD_SD3_DAT0__GPIO7_IO04   " },
    { "P_SD3_DATA1_comboBox=GPIO7_IO05"    , "MX6QDL_PAD_SD3_DAT1__GPIO7_IO05   " },
    { "P_SD3_DATA2_comboBox=GPIO7_IO06"    , "MX6QDL_PAD_SD3_DAT2__GPIO7_IO06   " },
    { "P_SD3_DATA3_comboBox=GPIO7_IO07"    , "MX6QDL_PAD_SD3_DAT3__GPIO7_IO07   " },
    { "P_SD3_DATA4_comboBox=GPIO7_IO01"    , "MX6QDL_PAD_SD3_DAT4__GPIO7_IO01   " },
    { "P_SD3_DATA5_comboBox=GPIO7_IO00"    , "MX6QDL_PAD_SD3_DAT5__GPIO7_IO00   " },
    { "P_SD3_DATA6_comboBox=GPIO6_IO18"    , "MX6QDL_PAD_SD3_DAT6__GPIO6_IO18   " },
    { "P_SD3_DATA7_comboBox=GPIO6_IO17"    , "MX6QDL_PAD_SD3_DAT7__GPIO6_IO17   " },
    { "P_GPIO3_IO20_comboBox=GPIO3_IO20"   , "MX6QDL_PAD_EIM_D20__GPIO3_IO20    " },
    { "P_GPIO1_IO00_comboBox=GPIO1_IO00"   , "MX6QDL_PAD_GPIO_0__GPIO1_IO00     " },
    { "P_GPIO4_IO29_comboBox=GPIO4_IO29"   , "MX6QDL_PAD_DISP0_DAT8__GPIO4_IO29 " },
    { "P_AUD6_TXD_comboBox=GPIO4_IO18"     , "MX6QDL_PAD_DI0_PIN2__GPIO4_IO18   " },
    { "P_AUD6_TXFS_comboBox=GPIO4_IO19"    , "MX6QDL_PAD_DI0_PIN3__GPIO4_IO19   " },
    { "P_AUD6_RXD_comboBox=GPIO4_IO20"     , "MX6QDL_PAD_DI0_PIN4__GPIO4_IO20   " },
    { "P_AUD6_TXC_comboBox=GPIO4_IO17"     , "MX6QDL_PAD_DI0_PIN15__GPIO4_IO17  " },
    { "P_I2C1_SDA_comboBox=GPIO5_IO26"     , "MX6QDL_PAD_CSI0_DAT8__GPIO5_IO26  " },
    { "P_I2C1_SCL_comboBox=GPIO5_IO27"     , "MX6QDL_PAD_CSI0_DAT9__GPIO5_IO27  " },
    { "P_UART1_TXD_comboBox=GPIO5_IO28"    , "MX6QDL_PAD_CSI0_DAT10__GPIO5_IO28 " },
    { "P_UART1_RXD_comboBox=GPIO5_IO29"    , "MX6QDL_PAD_CSI0_DAT11__GPIO5_IO29 " },
    { "P_SPDIF_OUT_comboBox=GPIO7_IO12"    , "MX6QDL_PAD_GPIO_17__GPIO7_IO12    " },
    { "P_UART4_RTS_L_comboBox=GPIO6_IO02"  , "MX6QDL_PAD_CSI0_DAT16__GPIO6_IO02 " },
    { "P_UART4_TXD_comboBox=GPIO5_IO30"    , "MX6QDL_PAD_CSI0_DAT12__GPIO5_IO30 " },
    { "P_UART4_RXD_comboBox=GPIO5_IO31"    , "MX6QDL_PAD_CSI0_DAT13__GPIO5_IO31 " },
    { "P_UART4_CTS_L_comboBox=GPIO6_IO03"  , "MX6QDL_PAD_CSI0_DAT17__GPIO6_IO03 " },
    { "last_string" , },
};

void process_gpio_hogs(void)
{
int    i = 0 , gpio_counter=0;
char * gen;
    while( strcmp(gpios[i].combobox_string,"last_string") != 0 )
    {
        gen = generate_hog_gpio(gpios[i].combobox_string,gpios[i].pin_name_string);
        if ( strlen(gen) > 1 )
        {
            strcat (hog,gen);
            gpio_counter++;
            free(gen);
        }
        i++;
    }
    strcat (hog,"          >;\n");
    strcat (hog,"        };\n");
    strcat (dtsifile_dump,hog);
    printf("Found %d gpios, initialized as hogs\n",gpio_counter);
}

void create_dtsi_file(void)
{
FILE    *fpout_dtsi;

    sprintf(dtsifile_dump,dtsi_header1_defs);
    process_videos_header();
    strcat(dtsifile_dump,dtsi_header2_defs);
    strcat(dtsifile_dump,iomux_defs);
    process_special_hogs();
    process_gpio_hogs();
    process_sf();
    process_special_devs();
    process_lvds_channels();
    if ( (fpout_dtsi = fopen(file_name_dtsi,"w" ) ))
    {
        fwrite(dtsifile_dump, strlen(dtsifile_dump)-1, 1, fpout_dtsi);
        fclose(fpout_dtsi);
    }
    printf("Dtsi file created\n");
}

void create_file_names(char *file_in)
{
int     i;
    bzero(dtsfile_dump,sizeof(dtsfile_dump));
    bzero(dtsifile_dump,sizeof(dtsifile_dump));

    sprintf(file_name,"%s",basename(strdup(file_in)));
    sprintf(dir_name,"%s",dirname(strdup(file_in)));

    sprintf(file_name_noext,"%s",file_name);
    if ( strlen(file_in) < 4 )
    {
        printf("File name %s is invalid\n",file_name);
        exit (-1);
    }
    for(i=0;i<strlen(file_name_noext);i++)
    {
        if ( file_name_noext[i] == '.')
            file_name_noext[i]=0;
    }
    sprintf(file_name_dts,"/Devel/NOVAsdk/DtbUserWorkArea/%s.dts",file_name_noext);
    sprintf(file_name_dtsi,"/Devel/NOVAsdk/DtbUserWorkArea/%s.dtsi",file_name_noext);

    printf("Input File Name       :  %s\n",file_in);
    printf("Output DTS  File Name : %s\n",file_name_dts);
    printf("Output DTSi File Name : %s\n",file_name_dtsi);
}

void store_dts_files(char *file_in)
{
    create_file_names(file_in);
    dump_iomux();
    create_dts_file();
    create_dtsi_file();
    printf("DTS  len : %d\n",(int )strlen(dtsfile_dump));
    printf("DTSi len : %d\n",(int )strlen(dtsifile_dump));
}
