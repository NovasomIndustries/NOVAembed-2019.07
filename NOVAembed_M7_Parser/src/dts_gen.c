#include "../include/NOVAembed_M7_parser.h"
#include "../include/header.h"

char    dtsfile_dump[32768];
char    file_name[32],file_name_noext[32],dir_name[256];
char    file_name_dts[128],file_name_dtsi[128];
char    hog[1024];
char    gpio_hogs[2048];

int extract_speed(char *speed_var_ptr)
{
char    *duplicate;
    duplicate = strdup(speed_var_ptr);
    *index(duplicate,0x0a)=0;
    duplicate += strlen("M7_I2C2Speed=");
    return(atoi(duplicate));
}

void process_peripherals(void)
{
char    t[1024];
int     speed;
    if ( iomux->i2c2 == 1 )
    {
        sprintf(t,i2c0_defs_top);
        strcat(dtsfile_dump,t);
        speed = extract_speed(strstr(file_contents,"M7_I2C2Speed="));
        sprintf(t,"        clock-frequency = <%d>;\n",speed);
        strcat(dtsfile_dump,t);
        sprintf(t,i2c0_footer);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->spi == 1 )
    {
        sprintf(t,spi_defs);
        strcat(dtsfile_dump,t);
        sprintf(t,spidev_defs);
        strcat(dtsfile_dump,t);
        sprintf(t,spi_footer);
        strcat(dtsfile_dump,t);
    }
    if ( iomux->uart1 == 1 )
    {
        if ( iomux->uart1_4wires == 1 )
        {
            sprintf(t,uart1_4wires_defs);
            strcat(dtsfile_dump,t);
        }
        else
        {
            sprintf(t,uart1_defs);
            strcat(dtsfile_dump,t);
        }
    }
}

void create_dts_file(void)
{
FILE    *fpout_dts;

    sprintf(dtsfile_dump,dts_header);
    printf("After sprintf %s\n",dtsfile_dump);
    process_peripherals();
    printf("file_name_dts : %s\n",file_name_dts);
    if ( (fpout_dts = fopen(file_name_dts,"w" ) ))
    {
        fwrite(dtsfile_dump, strlen(dtsfile_dump), 1, fpout_dts);
        fclose(fpout_dts);
    }
    else
        printf("Write error\n");
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
    sprintf(file_name_dts,"/Devel/NOVAsdk/DtbUserWorkArea/%s.dts",file_name_noext);

    printf("Input File Name       :  %s\n",file_in);
    printf("Output DTS  File Name : %s\n",file_name_dts);
}

void store_dts_files(char *file_in)
{
    create_file_names(file_in);
    create_dts_file();
    printf("DTS  len : %d\n",(int )strlen(dtsfile_dump));
    dump_iomux();
}
