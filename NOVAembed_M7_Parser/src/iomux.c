#include "../include/NOVAembed_M7_parser.h"

iomux_cfg       *iomux;
iomux_spi       *spi;
iomux_i2c2      *i2c2;

void dump_iomux(void)
{
    printf("\nPeripherals usage ( 1 means IN USE ):\n");
    printf("**********************************************\n");
    printf("spi      : %d\n",iomux->spi);
    printf("i2c2     : %d\n",iomux->i2c2);
    printf("uart1    : %d\n",iomux->uart1);
    printf("uart1 4w : %d\n",iomux->uart1_4wires);
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

void parse_iomux(void)
{
    iomux = calloc(1,sizeof(iomux_cfg));

    if ( strstr(file_contents,"M7_GPIO3_A1_comboBox=SPI_TXD"))
    {
        iomux->spi = 1;
    }

    if ( strstr(file_contents,"M7_GPIO2_D1_comboBox=SDA"))
    {
        iomux->i2c2 = 1;
    }

    if ( strstr(file_contents,"M7_GPIO3_A4_comboBox=UART1_TX"))
    {
        if ( strstr(file_contents,"M7_GPIO3_A5_comboBox=UART1_RTS"))
        {
            iomux->uart1_4wires = 1;
        }
        iomux->uart1 = 1;
    }
}

