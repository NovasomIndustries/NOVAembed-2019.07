#include "../include/NOVAembed_P_parser.h"
#include "../include/header.h"

char        file_contents[8192];
char        header_defs_dump[8192];
char        iomux_defs_dump[8192];
char        lvds_800x480_ch0_parserinput[1024];
char        lvds_800x480_ch1_parserinput[1024];
char        lvds_800x600_ch0_parserinput[1024];
char        lvds_800x600_ch1_parserinput[1024];
char        lvds_1024x600_ch0_parserinput[1024];
char        lvds_1024x600_ch1_parserinput[1024];
char        lvds_1024x768_ch0_parserinput[1024];
char        lvds_1024x768_ch1_parserinput[1024];
char        lvds_1280x800_ch0_parserinput[1024];
char        lvds_1280x800_ch1_parserinput[1024];
char        lvds_1366x768_ch0_parserinput[1024];
char        lvds_1366x768_ch1_parserinput[1024];

void read_support_parserinput(char *fname, char *parserinput_array , int len)
{
FILE *fpin;
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(parserinput_array, len, 1, fpin);
        fclose(fpin);
    }
    else
    {
        printf("Error on %s !!!\n",fname);
        exit(-1);
    }
}

void read_parserinput(void)
{
//FILE    *fpin;
char    parserinput_dir[]="/Devel/NOVAsdk/Qt/NOVAembed/NOVAembed_P_Parser/lvds_defs/";
char    fname[256];
int     len;

    bzero(lvds_800x480_ch0_parserinput,sizeof(lvds_800x480_ch0_parserinput));
    bzero(lvds_800x480_ch1_parserinput,sizeof(lvds_800x480_ch1_parserinput));
    bzero(lvds_800x600_ch0_parserinput,sizeof(lvds_800x600_ch0_parserinput));
    bzero(lvds_800x600_ch1_parserinput,sizeof(lvds_800x600_ch1_parserinput));
    bzero(lvds_1024x600_ch0_parserinput,sizeof(lvds_1024x600_ch0_parserinput));
    bzero(lvds_1024x600_ch1_parserinput,sizeof(lvds_1024x600_ch1_parserinput));
    bzero(lvds_1024x768_ch0_parserinput,sizeof(lvds_1024x768_ch0_parserinput));
    bzero(lvds_1024x768_ch1_parserinput,sizeof(lvds_1024x768_ch1_parserinput));
    bzero(lvds_1280x800_ch0_parserinput,sizeof(lvds_1280x800_ch0_parserinput));
    bzero(lvds_1280x800_ch1_parserinput,sizeof(lvds_1280x800_ch1_parserinput));
    bzero(lvds_1366x768_ch0_parserinput,sizeof(lvds_1366x768_ch0_parserinput));
    bzero(lvds_1366x768_ch1_parserinput,sizeof(lvds_1366x768_ch1_parserinput));

    sprintf(fname,"%s/lvds_800x480_ch0_parserinput",parserinput_dir);
    len=sizeof(lvds_800x480_ch0_parserinput);
    read_support_parserinput(fname,lvds_800x480_ch0_parserinput , len);
    sprintf(fname,"%s/lvds_800x480_ch1_parserinput",parserinput_dir);
    len=sizeof(lvds_800x480_ch1_parserinput);
    read_support_parserinput(fname,lvds_800x480_ch1_parserinput , len);
    sprintf(fname,"%s/lvds_800x600_ch0_parserinput",parserinput_dir);
    len=sizeof(lvds_800x600_ch0_parserinput);
    read_support_parserinput(fname,lvds_800x600_ch0_parserinput , len);
    sprintf(fname,"%s/lvds_800x600_ch1_parserinput",parserinput_dir);
    len=sizeof(lvds_800x600_ch1_parserinput);
    read_support_parserinput(fname,lvds_800x600_ch1_parserinput , len);
    sprintf(fname,"%s/lvds_1024x600_ch0_parserinput",parserinput_dir);
    len=sizeof(lvds_1024x600_ch0_parserinput);
    read_support_parserinput(fname,lvds_1024x600_ch0_parserinput , len);
    sprintf(fname,"%s/lvds_1024x600_ch1_parserinput",parserinput_dir);
    len=sizeof(lvds_1024x600_ch1_parserinput);
    read_support_parserinput(fname,lvds_1024x600_ch1_parserinput , len);
    sprintf(fname,"%s/lvds_1024x768_ch0_parserinput",parserinput_dir);
    len=sizeof(lvds_1024x768_ch0_parserinput);
    read_support_parserinput(fname,lvds_1024x768_ch0_parserinput , len);
    sprintf(fname,"%s/lvds_1024x768_ch1_parserinput",parserinput_dir);
    len=sizeof(lvds_1024x768_ch1_parserinput);
    read_support_parserinput(fname,lvds_1024x768_ch1_parserinput , len);
    sprintf(fname,"%s/lvds_1280x800_ch0_parserinput",parserinput_dir);
    len=sizeof(lvds_1280x800_ch0_parserinput);
    read_support_parserinput(fname,lvds_1280x800_ch0_parserinput , len);
    sprintf(fname,"%s/lvds_1280x800_ch1_parserinput",parserinput_dir);
    len=sizeof(lvds_1280x800_ch1_parserinput);
    read_support_parserinput(fname,lvds_1280x800_ch1_parserinput , len);
    sprintf(fname,"%s/lvds_1366x768_ch0_parserinput",parserinput_dir);
    len=sizeof(lvds_1366x768_ch0_parserinput);
    read_support_parserinput(fname,lvds_1366x768_ch0_parserinput , len);
    sprintf(fname,"%s/lvds_1366x768_ch1_parserinput",parserinput_dir);
    len=sizeof(lvds_1366x768_ch1_parserinput);
    read_support_parserinput(fname,lvds_1366x768_ch1_parserinput , len);
}

int main(int argc, char *argv[])
{
FILE *fpin;
char    file_name_in[256];

    bzero(file_contents,sizeof(file_contents));
    bzero(header_defs_dump,sizeof(header_defs_dump));
    bzero(iomux_defs_dump,sizeof(iomux_defs_dump));
    read_parserinput();
    if ( argc > 1 )
    {
        sprintf(file_name_in,"%s",argv[1]);
        if ( (fpin = fopen(file_name_in,"r" ) ))
        {
            fread(file_contents, sizeof(file_contents), 1, fpin);
            fclose(fpin);
        }
    }
    parse_special_iomux();
    store_dts_files(file_name_in);
    return 0;
}


