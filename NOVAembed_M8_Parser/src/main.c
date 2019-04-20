#include "../include/NOVAembed_M8_parser.h"
#include "../include/header.h"

char        file_contents[8192];
char        header_defs_dump[8192];
char        iomux_defs_dump[8192];


int main(int argc, char *argv[])
{
FILE *fpin;
char    file_name_in[256];

    bzero(file_contents,sizeof(file_contents));
    bzero(header_defs_dump,sizeof(header_defs_dump));
    bzero(iomux_defs_dump,sizeof(iomux_defs_dump));
    if ( argc < 2 )
        sprintf(file_name_in,"/Devel/NOVAsdk2019.1/DtbUserWorkArea/M8Class_bspf/test01.bspf");
    else
        sprintf(file_name_in,"%s",argv[1]);

    if ( (fpin = fopen(file_name_in,"r" ) ))
    {
        fread(file_contents, sizeof(file_contents), 1, fpin);
        fclose(fpin);
    }
    else
    {
        printf("%s Not found\n",file_name_in);
        return -1;
    }
    parse_iomux();
    store_dts_files(file_name_in);
    return 0;
}


