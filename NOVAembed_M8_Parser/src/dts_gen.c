#include "../include/NOVAembed_M8_parser.h"
#include "../include/header.h"

char    dtsfile_dump[32768];
char    file_name[32],file_name_noext[32],dir_name[256];
char    file_name_dts[128],file_name_dtsi[128];
char    hog[1024];
char    gpio_hogs[2048];


#if 0
void process_sf(void)
{
char    sf[1024];
char    t[128];
    if ( pwm2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",pwm2->pinctrl0_name,pwm2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",pwm2->pwm_pin_name,pwm2->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"      };\n");
        strcat(dtsfile_dump,sf);
    }
    if ( spdif != NULL )
    {
        sprintf(sf,"        %s: %s{\n",spdif->pinctrl0_name,spdif->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",spdif->spdif_pin_name,spdif->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsfile_dump,sf);
    }
    if ( can1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",can1->pinctrl0_name,can1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",can1->can1tx_pin_name,can1->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",can1->can1rx_pin_name,can1->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsfile_dump,sf);
    }
    if ( uart6 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart6->pinctrl0_name,uart6->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart6->uart_txd_pin_name,uart6->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart6->uart_rxd_pin_name,uart6->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsfile_dump,sf);
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
        strcat(dtsfile_dump,sf);
    }
    if ( i2c2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c2->pinctrl0_name,i2c2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c2->sda_pin_name,i2c2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c2->scl_pin_name,i2c2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsfile_dump,sf);
    }
    sprintf (sf,"  };\n");
    strcat (sf," };\n");
    strcat(dtsfile_dump,sf);
}
#endif // 0

int extract_speed(char *speed_var_ptr)
{
char    *duplicate;
    duplicate = strdup(speed_var_ptr);
    *index(duplicate,0x0a)=0;
    duplicate += strlen("U_I2C2Speed=");
    return(atoi(duplicate));
}

void process_special_devs_pins(void)
{
char    t[1024];
    if ( iomux->spdif == 1 )
    {
        sprintf(t,spdif_pins);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->uart6 == 1 )
    {
        sprintf(t,uart6_pins);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->ecspi4 == 1 )
    {
        sprintf(t,ecspi4_pins);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->can1 == 1 )
    {
        sprintf(t,can1_pins);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->pwm2 == 1 )
    {
        sprintf(t,pwm2_pins);
        strcat(dtsfile_dump,t);
    }
    sprintf (t,"  };");
    strcat(dtsfile_dump,t);
}

void process_special_devs_defs(void)
{
char    t[1024];
int     speed;

    if ( iomux->i2c2 == 1 )
    {
        sprintf(t,i2c2_defs_top);
        strcat(dtsfile_dump,t);
        speed = extract_speed(strstr(file_contents,"U_I2C2Speed="));
        sprintf(t,"        clock-frequency = <%d>;\n",speed);
        strcat(dtsfile_dump,t);
        strcat(dtsfile_dump,i2c2_defs_bottom);
    }
    if ( iomux->spdif == 1 )
    {
        sprintf(t,spdif_defs);
        strcat(dtsfile_dump,t);
    }

    if ( iomux->uart6 == 1 )
    {
        sprintf(t,uart6_defs);
        strcat(dtsfile_dump,t);
    }

    if ( iomux->ecspi4 == 1 )
    {
        sprintf(t,ecspi4_defs);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->can1 == 1 )
    {
        sprintf(t,can1_defs);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->pwm2 == 1 )
    {
        sprintf(t,pwm2_defs);
        strcat(dtsfile_dump,t);
    }
    strcat(dtsfile_dump,lcd_defs);
}


void create_dts_file(void)
{
FILE    *fpout_dts;

    sprintf(dtsfile_dump,dts_header);
    process_special_devs_pins();
    strcat(dtsfile_dump,dts_footer);
    process_special_devs_defs();
    if ( (fpout_dts = fopen(file_name_dts,"w" ) ))
    {
        fwrite(dtsfile_dump, strlen(dtsfile_dump), 1, fpout_dts);
        fclose(fpout_dts);
    }
}

void create_file_names(char *file_in)
{
int     i;
    bzero(dtsfile_dump,sizeof(dtsfile_dump));

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
    sprintf(file_name_dts,"/Devel/NOVAsdk2019.1/DtbUserWorkArea/%s.dts",file_name_noext);

    printf("Input File Name       :  %s\n",file_in);
    printf("Output DTS  File Name : %s\n",file_name_dts);
}

void store_dts_files(char *file_in)
{
    create_file_names(file_in);
    dump_iomux();
    create_dts_file();
    printf("DTS  len : %d\n",(int )strlen(dtsfile_dump));
}
