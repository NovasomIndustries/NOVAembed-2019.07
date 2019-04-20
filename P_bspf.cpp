#include "novaembed.h"
#include "ui_novaembed.h"
#include <QFileDialog>
#include <QTreeView>
#include <QDebug>
#include <QDir>
#include <QStatusBar>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include <QUrl>
#include <QtCore>
#include <QDesktopServices>
#include <QDirIterator>
#include <iostream>


extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString CfgBitDefaultValue;
extern  QString _Board_comboBox;
extern  QString Last_P_BSPFactoryFile;
extern  QString LVDSVideo;
extern  QString Quad;
extern  QString instpath;
extern  QString system_editor;
extern  QString Kernel;

/*****************************************************************************************************************************************************************************************/
/*                                                                             P BSP Factory                                                                                             */
/*****************************************************************************************************************************************************************************************/



void NOVAembed::on_P_SetCFGbits_pushButton_clicked()
{
    CfgBitDefaultValue = ui->P_cbit_lineEdit->text();
    ui->P_cbit_lineEdit->setText(CfgBitDefaultValue);
    storeNOVAembed_ini();
}

QString P_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}


/*********************** Bit calculator ******************************/
void NOVAembed::on_P_CreateCFGBits_pushButton_clicked()
{
   int  value = 0;
    /*
    CONFIG bits definition:
    NO_PAD_CTL                      (1 << 31)
    SION                            (1 << 30)
    PAD_CTL_HYS                     (1 << 16)
    PAD_CTL_PUS_100K_DOWN           (0 << 14)
    PAD_CTL_PUS_47K_UP              (1 << 14)
    PAD_CTL_PUS_100K_UP             (2 << 14)
    PAD_CTL_PUS_22K_UP              (3 << 14)
    PAD_CTL_PUE                     (1 << 13)
    PAD_CTL_PKE                     (1 << 12)
    PAD_CTL_ODE                     (1 << 11)
    PAD_CTL_SPEED_LOW               (1 << 6)
    PAD_CTL_SPEED_MED               (2 << 6)
    PAD_CTL_SPEED_HIGH              (3 << 6)
    PAD_CTL_DSE_DISABLE             (0 << 3)
    PAD_CTL_DSE_34ohm               (7 << 3)
    PAD_CTL_DSE_40ohm               (6 << 3)
    PAD_CTL_DSE_48ohm               (5 << 3)
    PAD_CTL_DSE_60ohm               (4 << 3)
    PAD_CTL_DSE_80ohm               (3 << 3)
    PAD_CTL_DSE_120ohm              (2 << 3)
    PAD_CTL_DSE_240ohm              (1 << 3)
    PAD_CTL_SRE_FAST                (1 << 0)
    PAD_CTL_SRE_SLOW                (0 << 0)

    */

   if ( ui->P_NO_PAD_CTL_checkBox->isChecked() == true )
       value = 1 << 31;
   else
   {
       if ( ui->P_SION_checkBox->isChecked() == true )
           value |= 1 << 30;
       if ( ui->P_HYS_PAD_CTL_checkBox->isChecked() == true )
           value |= 1 << 16;
       if ( ui->P_PUE_checkBox->isChecked() == true )
       {
           value |= 1 << 13;
           if ( ui->P_PD_100K_checkBox->isChecked() == true )
               value |= 0 << 14;
           if ( ui->P_PU_100K_checkBox->isChecked() == true )
               value |= 2 << 14;
           if ( ui->P_PU_47K_checkBox->isChecked() == true )
               value |= 1 << 14;
           if ( ui->P_PU_22K_checkBox->isChecked() == true )
               value |= 3 << 14;
       }
       if ( ui->P_PKE_checkBox->isChecked() == true )
           value |= 1 << 12;
       if ( ui->P_ODE_checkBox->isChecked() == true )
           value |= 1 << 11;
       if ( ui->P_SPEED_Low_checkBox->isChecked() == true )
           value |= 1 << 6;
       if ( ui->P_SPEED_Mid_checkBox->isChecked() == true )
           value |= 2 << 6;
       if ( ui->P_SPEED_High_checkBox->isChecked() == true )
           value |= 3 << 6;
       if ( ui->P_DSE_Disable_checkBox->isChecked() == true )
           value |= 0 << 3;
       else
       {
           if ( ui->P_DSE_34_checkBox->isChecked() == true )
               value |= 7 << 3;
           if ( ui->P_DSE_40_checkBox->isChecked() == true )
               value |= 6 << 3;
           if ( ui->P_DSE_48_checkBox->isChecked() == true )
               value |= 5 << 3;
           if ( ui->P_DSE_60_checkBox->isChecked() == true )
               value |= 4 << 3;
           if ( ui->P_DSE_80_checkBox->isChecked() == true )
               value |= 3 << 3;
           if ( ui->P_DSE_120_checkBox->isChecked() == true )
               value |= 2 << 3;
           if ( ui->P_DSE_240_checkBox->isChecked() == true )
               value |= 1 << 3;
       }
       if ( ui->P_SRE_Fast_checkBox->isChecked() == true )
           value |= 1 << 0;
       if ( ui->P_SRE_Slow_checkBox->isChecked() == true )
           value |= 0 << 0;

    }
    char result[16];
    sprintf(result,"0x%08x",value);
    ui->P_CFG_Bits_lineEdit->setText(result);
}


#define    NO_PAD_CTL                      (unsigned int )(1 << 31)
#define    SION                            (unsigned int )(1 << 30)
#define    PAD_CTL_HYS                     (unsigned int )(1 << 16)
#define    PAD_CTL_PUS_100K_DOWN           (unsigned int )(0 << 14)
#define    PAD_CTL_PUS_47K_UP              (unsigned int )(1 << 14)
#define    PAD_CTL_PUS_100K_UP             (unsigned int )(2 << 14)
#define    PAD_CTL_PUS_22K_UP              (unsigned int )(3 << 14)
#define    PAD_CTL_PUE                     (unsigned int )(1 << 13)
#define    PAD_CTL_PKE                     (unsigned int )(1 << 12)
#define    PAD_CTL_ODE                     (unsigned int )(1 << 11)
#define    PAD_CTL_SPEED_LOW               (unsigned int )(1 << 6)
#define    PAD_CTL_SPEED_MED               (unsigned int )(2 << 6)
#define    PAD_CTL_SPEED_HIGH              (unsigned int )(3 << 6)
#define    PAD_CTL_DSE_DISABLE             (unsigned int )(0 << 3)
#define    PAD_CTL_DSE_34ohm               (unsigned int )(7 << 3)
#define    PAD_CTL_DSE_40ohm               (unsigned int )(6 << 3)
#define    PAD_CTL_DSE_48ohm               (unsigned int )(5 << 3)
#define    PAD_CTL_DSE_60ohm               (unsigned int )(4 << 3)
#define    PAD_CTL_DSE_80ohm               (unsigned int )(3 << 3)
#define    PAD_CTL_DSE_120ohm              (unsigned int )(2 << 3)
#define    PAD_CTL_DSE_240ohm              (unsigned int )(1 << 3)
#define    PAD_CTL_SRE_FAST                (unsigned int )(1 << 0)
#define    PAD_CTL_SRE_SLOW                (unsigned int )(0 << 0)
#define    PAD_DSE_MASK                    (unsigned int )(0xfe)


void NOVAembed::on_P_DecodeCFGBits_pushButton_clicked()
{
    bool ok=1;
    QString a = ui->P_Decoded_CFG_Bits_lineEdit->text().right(8);
    unsigned int value = a.toUInt(&ok,16);

    if ( (unsigned int )(value & NO_PAD_CTL) == NO_PAD_CTL )
    {
        ui->P_NO_PAD_CTL_checkBox->setChecked(true);
        ui->P_DSE_Disable_checkBox->setEnabled(false);
        ui->P_DSE_frame->setEnabled(false);
        ui->P_Speed_frame->setEnabled(false);
        ui->P_SRE_frame->setEnabled(false);
        ui->P_PUE_checkBox->setEnabled(false);
        ui->P_PUPD_frame->setEnabled(false);
        ui->P_ODE_checkBox->setEnabled(false);
        ui->P_PKE_checkBox->setEnabled(false);
        ui->P_SION_checkBox->setEnabled(false);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(false);
    }
    else
    {

        ui->P_NO_PAD_CTL_checkBox->setChecked(false);
        ui->P_DSE_Disable_checkBox->setEnabled(true);
        ui->P_DSE_frame->setEnabled(true);
        ui->P_Speed_frame->setEnabled(true);
        ui->P_SRE_frame->setEnabled(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_PUPD_frame->setEnabled(true);
        ui->P_ODE_checkBox->setEnabled(true);
        ui->P_PKE_checkBox->setEnabled(true);
        ui->P_SION_checkBox->setEnabled(true);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(true);
    }

    ui->P_SION_checkBox->setChecked(false);
    ui->P_HYS_PAD_CTL_checkBox->setChecked(false);
    if ( (unsigned int )(value & SION) == SION )
        ui->P_SION_checkBox->setChecked(true);
    if ( (unsigned int )(value & PAD_CTL_HYS) == PAD_CTL_HYS )
        ui->P_HYS_PAD_CTL_checkBox->setChecked(true);

    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(false);
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PUE_checkBox->setChecked(false);
    ui->P_PKE_checkBox->setChecked(false);

    if ( (unsigned int )(value & PAD_CTL_PUS_47K_UP) == PAD_CTL_PUS_47K_UP )
    {
        ui->P_PU_47K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_PUPD_frame->setEnabled(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUS_100K_UP) == PAD_CTL_PUS_100K_UP )
    {
        ui->P_PU_100K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_PUPD_frame->setEnabled(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUS_22K_UP) == PAD_CTL_PUS_22K_UP )
    {
        ui->P_PU_22K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_PUPD_frame->setEnabled(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUE) == PAD_CTL_PUE )
    {
        ui->P_PD_100K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(false);
        ui->P_PUE_checkBox->setEnabled(false);
        ui->P_PUPD_frame->setEnabled(true);
    }

    if ( (unsigned int )(value & PAD_CTL_PKE) == PAD_CTL_PKE )
    {
        ui->P_PUE_checkBox->setChecked(true);
        ui->P_PUPD_frame->setEnabled(true);
        ui->P_PKE_checkBox->setChecked(true);
    }
    if ( (unsigned int )(value & PAD_CTL_ODE) == PAD_CTL_ODE )
    {
        ui->P_ODE_checkBox->setChecked(true);
        //ui->PUE_checkBox->setChecked(false);
        //ui->PUPD_frame->setEnabled(false);
    }

    ui->P_SPEED_Low_checkBox->setChecked(false);
    ui->P_SPEED_Mid_checkBox->setChecked(false);
    ui->P_SPEED_High_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_SPEED_LOW) == PAD_CTL_SPEED_LOW )
        ui->P_SPEED_Low_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_SPEED_MED) == PAD_CTL_SPEED_MED )
        ui->P_SPEED_Mid_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_SPEED_HIGH) == PAD_CTL_SPEED_HIGH )
        ui->P_SPEED_High_checkBox->setChecked(true);

    ui->P_DSE_34_checkBox->setChecked(false);
    ui->P_DSE_40_checkBox->setChecked(false);
    ui->P_DSE_48_checkBox->setChecked(false);
    ui->P_DSE_60_checkBox->setChecked(false);
    ui->P_DSE_80_checkBox->setChecked(false);
    ui->P_DSE_120_checkBox->setChecked(false);
    ui->P_DSE_240_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_DSE_34ohm) == PAD_CTL_DSE_34ohm )
        ui->P_DSE_34_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_40ohm) == PAD_CTL_DSE_40ohm )
        ui->P_DSE_40_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_48ohm) == PAD_CTL_DSE_48ohm )
        ui->P_DSE_48_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_60ohm) == PAD_CTL_DSE_60ohm )
        ui->P_DSE_60_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_80ohm) == PAD_CTL_DSE_80ohm )
        ui->P_DSE_80_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_120ohm) == PAD_CTL_DSE_120ohm )
        ui->P_DSE_120_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_240ohm) == PAD_CTL_DSE_240ohm )
        ui->P_DSE_240_checkBox->setChecked(true);
    else
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
        ui->P_DSE_Disable_checkBox->setChecked(true);
        ui->P_DSE_frame->setEnabled(false);
    }

    ui->P_SRE_Fast_checkBox->setChecked(false);
    ui->P_SRE_Slow_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_SRE_FAST) == PAD_CTL_SRE_FAST )
    {
        ui->P_SRE_Fast_checkBox->setChecked(true);
    }
    else
    {
        ui->P_SRE_Slow_checkBox->setChecked(true);
    }
}

void NOVAembed::on_P_PKE_checkBox_clicked()
{
}

void NOVAembed::on_P_ODE_checkBox_clicked()
{
}

void NOVAembed::on_P_NO_PAD_CTL_checkBox_clicked()
{
    if ( ui->P_NO_PAD_CTL_checkBox->isChecked() == true )
    {
        ui->P_PUPD_frame->setEnabled(false);
        ui->P_Speed_frame->setEnabled(false);
        ui->P_SRE_frame->setEnabled(false);
        ui->P_DSE_frame->setEnabled(false);
        ui->P_PUE_checkBox->setEnabled(false);
        ui->P_SION_checkBox->setEnabled(false);
        ui->P_ODE_checkBox->setEnabled(false);
        ui->P_PKE_checkBox->setEnabled(false);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(false);
        ui->P_DSE_Disable_checkBox->setEnabled(false);
    }
    else
    {
        ui->P_PUPD_frame->setEnabled(true);
        ui->P_Speed_frame->setEnabled(true);
        ui->P_SRE_frame->setEnabled(true);
        ui->P_DSE_frame->setEnabled(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_SION_checkBox->setEnabled(true);
        ui->P_ODE_checkBox->setEnabled(true);
        ui->P_PKE_checkBox->setEnabled(true);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(true);
        ui->P_DSE_Disable_checkBox->setEnabled(true);
    }

}

void NOVAembed::on_P_PUE_checkBox_clicked()
{
    if ( ui->P_PUE_checkBox->isChecked() == true )
    {
        ui->P_ODE_checkBox->setChecked(false);
        ui->P_PKE_checkBox->setChecked(false);
        ui->P_PUPD_frame->setEnabled(true);
    }
    else
    {
        ui->P_PUPD_frame->setEnabled(false);
    }
}


void NOVAembed::on_P_PD_100K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(true);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(false);
}


void NOVAembed::on_P_PU_100K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(true);
    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(false);
}


void NOVAembed::on_P_PU_47K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_47K_checkBox->setChecked(true);
    ui->P_PU_22K_checkBox->setChecked(false);
}



void NOVAembed::on_P_PU_22K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(true);
}


void NOVAembed::on_P_SPEED_Low_checkBox_clicked()
{
    if ( ui->P_SPEED_Low_checkBox->isChecked() == true )
    {
        ui->P_SPEED_Low_checkBox->setChecked(true);
        ui->P_SPEED_Mid_checkBox->setChecked(false);
        ui->P_SPEED_High_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_SPEED_Mid_checkBox_clicked()
{
    if ( ui->P_SPEED_Mid_checkBox->isChecked() == true )
    {
        ui->P_SPEED_Low_checkBox->setChecked(false);
        ui->P_SPEED_Mid_checkBox->setChecked(true);
        ui->P_SPEED_High_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_SPEED_High_checkBox_clicked()
{
    if ( ui->P_SPEED_High_checkBox->isChecked() == true )
    {
        ui->P_SPEED_Low_checkBox->setChecked(false);
        ui->P_SPEED_Mid_checkBox->setChecked(false);
        ui->P_SPEED_High_checkBox->setChecked(true);
    }
}

void NOVAembed::on_P_SRE_Fast_checkBox_clicked()
{
    if ( ui->P_SRE_Fast_checkBox->isChecked() == true )
    {
        ui->P_SRE_Fast_checkBox->setChecked(true);
        ui->P_SRE_Slow_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_SRE_Slow_checkBox_clicked()
{
    if ( ui->P_SRE_Slow_checkBox->isChecked() == true )
    {
        ui->P_SRE_Fast_checkBox->setChecked(false);
        ui->P_SRE_Slow_checkBox->setChecked(true);
    }
}

void NOVAembed::on_P_DSE_Disable_checkBox_clicked()
{
    if ( ui->P_DSE_Disable_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setDisabled(true);
        ui->P_DSE_40_checkBox->setDisabled(true);
        ui->P_DSE_48_checkBox->setDisabled(true);
        ui->P_DSE_60_checkBox->setDisabled(true);
        ui->P_DSE_80_checkBox->setDisabled(true);
        ui->P_DSE_120_checkBox->setDisabled(true);
        ui->P_DSE_240_checkBox->setDisabled(true);
        ui->P_DSE_frame->setEnabled(false);
    }
    else
    {
        ui->P_DSE_34_checkBox->setDisabled(false);
        ui->P_DSE_40_checkBox->setDisabled(false);
        ui->P_DSE_48_checkBox->setDisabled(false);
        ui->P_DSE_60_checkBox->setDisabled(false);
        ui->P_DSE_80_checkBox->setDisabled(false);
        ui->P_DSE_120_checkBox->setDisabled(false);
        ui->P_DSE_240_checkBox->setDisabled(false);


        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(true);
        ui->P_DSE_frame->setEnabled(true);
    }
}

void NOVAembed::on_P_DSE_34_checkBox_clicked()
{
    if ( ui->P_DSE_34_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(true);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_40_checkBox_clicked()
{
    if ( ui->P_DSE_40_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(true);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_48_checkBox_clicked()
{
    if ( ui->P_DSE_48_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(true);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_60_checkBox_clicked()
{
    if ( ui->P_DSE_60_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(true);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_80_checkBox_clicked()
{
    if ( ui->P_DSE_80_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(true);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_120_checkBox_clicked()
{
    if ( ui->P_DSE_120_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(true);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_240_checkBox_clicked()
{
    if ( ui->P_DSE_240_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(true);
    }
}
/*********************** Bit calculator end ******************************/

QString P_ECSPI1_MISO_comboBox="GPIO5_IO16";
QString P_ECSPI1_MOSI_comboBox="GPIO5_IO15";
QString P_ECSPI1_SS0_comboBox="GPIO5_IO17";
QString P_ECSPI1_SCK_comboBox="GPIO5_IO14";
QString P_ECSPI2_SS0_comboBox = "GPIO5_IO12";
QString P_ECSPI2_SS1_comboBox = "GPIO5_IO09";
QString P_ECSPI2_MISO_comboBox ="GPIO5_IO11";
QString P_ECSPI2_MOSI_comboBox = "GPIO5_IO10";
QString P_ECSPI2_SCK_comboBox = "GPIO5_IO13";
QString P_ECSPI3_MISO_comboBox ="GPIO4_IO23";
QString P_ECSPI3_SCK_comboBox = "GPIO4_IO21";
QString P_ECSPI3_MOSI_comboBox = "GPIO4_IO22";
QString P_ECSPI3_SS0_comboBox = "GPIO4_IO24";
QString P_ECSPI3_SS1_comboBox = "GPIO4_IO25";
QString P_ECSPI4_MISO_comboBox="GPIO3_IO22";
QString P_ECSPI4_MOSI_comboBox = "GPIO3_IO28";
QString P_ECSPI4_SCK_comboBox = "GPIO3_IO21";
QString P_ECSPI4_SS0_comboBox = "GPIO3_IO29";
QString P_I2C3_SCL_comboBox= "GPIO3_IO17";
QString P_I2C3_SDA_comboBox= "GPIO3_IO18";
QString P_KHZ32_CLK_OUT_comboBox = "GPIO1_IO08";
QString P_SD3_CMD_comboBox   ="GPIO7_IO02";
QString P_SD3_CLK_comboBox   ="GPIO7_IO03";
QString P_SD3_DATA0_comboBox ="GPIO7_IO04";
QString P_SD3_DATA1_comboBox ="GPIO7_IO05";
QString P_SD3_DATA2_comboBox ="GPIO7_IO06";
QString P_SD3_DATA3_comboBox ="GPIO7_IO07";
QString P_SD3_DATA4_comboBox ="GPIO7_IO01";
QString P_SD3_DATA5_comboBox ="GPIO7_IO00";
QString P_SD3_DATA6_comboBox ="GPIO6_IO18";
QString P_SD3_DATA7_comboBox ="GPIO6_IO17";
QString P_GPIO3_IO20_comboBox ="GPIO3_IO20";
QString P_GPIO1_IO00_comboBox ="GPIO1_IO00";
QString P_GPIO4_IO29_comboBox ="GPIO4_IO29";
QString P_AUD6_TXD_comboBox  ="GPIO4_IO18";
QString P_AUD6_RXD_comboBox  ="GPIO4_IO20";
QString P_AUD6_TXFS_comboBox ="GPIO4_IO19";
QString P_AUD6_TXC_comboBox  ="GPIO4_IO17";
QString P_I2C1_SDA_comboBox= "GPIO5_IO26";
QString P_I2C1_SCL_comboBox = "GPIO5_IO27";
QString P_UART1_TXD_comboBox ="GPIO5_IO28";
QString P_UART1_RXD_comboBox = "GPIO5_IO29";
QString P_SPDIF_OUT_comboBox= "GPIO7_IO12";
QString P_UART4_RTS_L_comboBox= "GPIO6_IO02";
QString P_UART4_TXD_comboBox= "GPIO5_IO30";
QString P_UART4_RXD_comboBox="GPIO5_IO31";
QString P_UART4_CTS_L_comboBox="GPIO6_IO03";
QString P_I2C1Speed="100000";
QString P_I2C3Speed="100000";
QString P_SATA_checkBox="false";
QString P_PCIe_checkBox="true";
QString P_PrimaryVideo_comboBox;
QString P_SecondaryVideo_comboBox;
QString Processor;
QString spwg_flag;


void NOVAembed::on_P_SPI1_checkBox_toggled(bool checked)
{
    ui->P_SPI1_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->P_Audio4_checkBox->setChecked(false);
        ui->P_Audio4_checkBox->setEnabled(false);
        ui->P_SPI1_2ndSScheckBox->setEnabled(true);
        ui->P_SPIdev1_checkBox->setEnabled(true);
        ui->label_PECSPI1_MISO->setText("ECSPI1_MISO");
        ui->label_PECSPI1_MOSI->setText("ECSPI1_MOSI");
        ui->label_PECSPI1_SCK->setText("ECSPI1_SCK");
        ui->label_PECSPI1_SS0->setText("ECSPI1_SS0");
    }
    else
    {
        ui->P_Audio4_checkBox->setEnabled(true);
        ui->P_SPI1_2ndSScheckBox->setChecked(false);
        ui->P_SPI1_2ndSScheckBox->setEnabled(false);
        ui->P_SPIdev1_checkBox->setChecked(false);
        ui->P_SPIdev1_checkBox->setEnabled(false);
        ui->label_PECSPI1_MISO->setText("GPIO5_IO16");
        ui->label_PECSPI1_MOSI->setText("GPIO5_IO15");
        ui->label_PECSPI1_SCK->setText("GPIO5_IO14");
        ui->label_PECSPI1_SS0->setText("GPIO5_IO17");
    }
}

void NOVAembed::on_P_SPI2_checkBox_toggled(bool checked)
{
    ui->P_SPI2_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->P_Audio5_checkBox->setChecked(false);
        ui->P_Audio5_checkBox->setEnabled(false);
        ui->P_SPI2_2ndSScheckBox->setEnabled(true);
        ui->P_SPIdev2_checkBox->setEnabled(true);
        ui->label_PECSPI2_MISO->setText("ECSPI2_MISO");
        ui->label_PECSPI2_MOSI->setText("ECSPI2_MOSI");
        ui->label_PECSPI2_SCK->setText("ECSPI2_SCK");
        ui->label_PECSPI2_SS0->setText("ECSPI2_SS0");
    }
    else
    {
        ui->P_SPI2_2ndSScheckBox->setChecked(false);
        ui->P_SPI2_2ndSScheckBox->setEnabled(false);
        ui->P_Audio5_checkBox->setEnabled(true);
        ui->P_SPIdev2_checkBox->setChecked(false);
        ui->P_SPIdev2_checkBox->setEnabled(false);
        ui->label_PECSPI2_MISO->setText("GPIO5_IO11");
        ui->label_PECSPI2_MOSI->setText("GPIO5_IO10");
        ui->label_PECSPI2_SCK->setText("GPIO5_IO13");
        ui->label_PECSPI2_SS0->setText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_SPI1_2ndSScheckBox_toggled(bool checked)
{
    if ( checked )
    {
        if ( ui->P_SPI1_checkBox->isChecked())
        {
            ui->P_SPI1_2ndSScheckBox->setChecked(true);
            ui->P_SPI2_2ndSScheckBox->setChecked(false);
            ui->label_PECSPI2_SS1->setText("ECSPI1_SS1");
        }
        else
        {
            ui->P_SPI1_2ndSScheckBox->setChecked(false);
            ui->label_PECSPI2_SS1->setText("GPIO5_IO09");
        }
    }
    else
    {
        ui->label_PECSPI2_SS1->setText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_SPI2_2ndSScheckBox_toggled(bool checked)
{
    if ( checked )
    {
        if ( ui->P_SPI2_checkBox->isChecked())
        {
            ui->P_SPI2_2ndSScheckBox->setChecked(true);
            ui->P_SPI1_2ndSScheckBox->setChecked(false);
            ui->label_PECSPI2_SS1->setText("ECSPI2_SS1");
        }
        else
        {
            ui->P_SPI2_2ndSScheckBox->setChecked(false);
            ui->label_PECSPI2_SS1->setText("GPIO5_IO09");
        }
    }
    else
    {
        ui->label_PECSPI2_SS1->setText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_Audio4_checkBox_toggled(bool checked)
{
    ui->P_Audio4_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->P_SPI1_checkBox->setChecked(false);
        ui->P_SPI1_checkBox->setEnabled(false);
        ui->P_SPI1_2ndSScheckBox->setChecked(false);
        ui->P_SPI1_2ndSScheckBox->setEnabled(false);
        ui->P_SPIdev1_checkBox->setChecked(false);
        ui->P_SPIdev1_checkBox->setEnabled(false);
        ui->label_PECSPI1_MISO->setText("AUD4_TXFS");
        ui->label_PECSPI1_MOSI->setText("AUD4_TXD");
        ui->label_PECSPI1_SCK->setText("AUD4_TXC");
        ui->label_PECSPI1_SS0->setText("AUD4_RXD");
        ui->label_PECSPI2_SS1->setText("GPIO5_IO09");
    }
    else
    {
        ui->P_SPI1_checkBox->setEnabled(true);
        ui->P_SPI1_2ndSScheckBox->setEnabled(false);
        ui->label_PECSPI1_MISO->setText("GPIO5_IO16");
        ui->label_PECSPI1_MOSI->setText("GPIO5_IO15");
        ui->label_PECSPI1_SCK->setText("GPIO5_IO14");
        ui->label_PECSPI1_SS0->setText("GPIO5_IO17");
    }
}


void NOVAembed::on_P_Audio5_checkBox_toggled(bool checked)
{
    ui->P_Audio5_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->P_SPI2_checkBox->setChecked(false);
        ui->P_SPI2_2ndSScheckBox->setChecked(false);
        ui->P_SPI2_checkBox->setEnabled(false);
        ui->P_SPI2_2ndSScheckBox->setEnabled(false);
        ui->P_SPIdev2_checkBox->setChecked(false);
        ui->P_SPIdev2_checkBox->setEnabled(false);
        ui->label_PECSPI2_MISO->setText("AUD5_TXFS");
        ui->label_PECSPI2_MOSI->setText("AUD5_TXD");
        ui->label_PECSPI2_SCK->setText("AUD5_TXC");
        ui->label_PECSPI2_SS0->setText("AUD5_RXD");
        ui->label_PECSPI2_SS1->setText("GPIO5_IO09");
    }
    else
    {
        ui->P_SPI2_checkBox->setEnabled(true);
        ui->label_PECSPI2_MISO->setText("GPIO5_IO11");
        ui->label_PECSPI2_MOSI->setText("GPIO5_IO10");
        ui->label_PECSPI2_SCK->setText("GPIO5_IO13");
        ui->label_PECSPI2_SS0->setText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_SPI3_checkBox_toggled(bool checked)
{
    if (  checked )
    {
        ui->P_SPI3_checkBox->setChecked(true);
        ui->P_SPI3_2ndSScheckBox->setEnabled(true);
        ui->P_SPIdev3_checkBox->setEnabled(true);
        ui->label_PECSPI3_MISO->setText("ECSPI3_MISO");
        ui->label_PECSPI3_MOSI->setText("ECSPI3_MOSI");
        ui->label_PECSPI3_SCK->setText("ECSPI3_SCK");
        ui->label_PECSPI3_SS0->setText("ECSPI3_SS0");
    }
    else
    {
        ui->P_SPI3_2ndSScheckBox->setEnabled(false);
        ui->P_SPI3_2ndSScheckBox->setChecked(false);
        ui->P_SPIdev3_checkBox->setChecked(false);
        ui->P_SPIdev3_checkBox->setEnabled(false);
        ui->label_PECSPI3_MISO->setText("GPIO4_IO23");
        ui->label_PECSPI3_MOSI->setText("GPIO4_IO22");
        ui->label_PECSPI3_SCK->setText("GPIO4_IO21");
        ui->label_PECSPI3_SS0->setText("GPIO4_IO24");
        ui->label_PECSPI3_SS1->setText("GPIO4_IO25");
    }
}

void NOVAembed::on_P_I2C1_checkBox_toggled(bool checked)
{
    ui->P_I2C1_checkBox->setChecked(checked);
    if (  checked )
    {
        ui->P_I2C1_OnJ13checkBox->setEnabled(true);
        ui->label_PI2C1_SDA->setText("I2C1_SDA");
        ui->label_PI2C1_SCL->setText("I2C1_SCL");
    }
    else
    {
        ui->P_I2C1_OnJ13checkBox->setChecked(false);
        ui->P_I2C1_OnJ13checkBox->setEnabled(false);
        ui->P_SPI3_2ndSScheckBox->setChecked(false);
        ui->label_PI2C1_SDA->setText("GPIO5_IO26");
        ui->label_PI2C1_SCL->setText("GPIO5_IO27");
    }
}

void NOVAembed::on_P_I2C1_OnJ13checkBox_toggled(bool checked)
{
    ui->P_I2C1_OnJ13checkBox->setChecked(checked);
    if ( checked )
    {
        ui->P_SPI4_checkBox->setChecked(false);
        ui->P_SPI4_checkBox->setEnabled(false);
        ui->label_PECSPI4_MISO->setText("GPIO3_IO22");
        ui->label_PECSPI4_MOSI->setText("I2C1_SDA");
        ui->label_PECSPI4_SCK->setText("I2C1_SCL");
        ui->label_PECSPI4_SS0->setText("GPIO3_IO29");
        ui->label_PI2C1_SDA->setText("GPIO5_IO26");
        ui->label_PI2C1_SCL->setText("GPIO5_IO27");
    }
    else
    {
        ui->label_PECSPI4_MOSI->setText("GPIO3_IO28");
        ui->label_PECSPI4_SCK->setText("GPIO3_IO21");
        ui->label_PI2C1_SDA->setText("I2C1_SDA");
        ui->label_PI2C1_SCL->setText("I2C1_SCL");
        if ( ui->P_SPDIF_OnJ13checkBox->isChecked() == false)
            ui->P_SPI4_checkBox->setEnabled(true);
    }
}

void NOVAembed::on_P_I2C3_checkBox_toggled(bool checked)
{
    ui->P_I2C3_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->label_PI2C3_SDA->setText("I2C3_SDA");
        ui->label_PI2C3_SCL->setText("I2C3_SCL");
    }
    else
    {
        ui->label_PI2C3_SDA->setText("GPIO3_IO18");
        ui->label_PI2C3_SCL->setText("GPIO3_IO17");
    }
}


void NOVAembed::on_P_SPI4_checkBox_toggled(bool checked)
{
    ui->P_SPI4_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->P_I2C1_OnJ13checkBox->setEnabled(false);
        ui->P_SPDIF_OnJ13checkBox->setEnabled(false);
        ui->P_SPIdev4_checkBox->setEnabled(true);
        ui->label_PECSPI4_MISO->setText("ECSPI4_MISO");
        ui->label_PECSPI4_MOSI->setText("ECSPI4_MOSI");
        ui->label_PECSPI4_SCK->setText("ECSPI4_SCK");
        ui->label_PECSPI4_SS0->setText("ECSPI4_SS0");
    }
    else
    {
        ui->P_SPDIF_OnJ13checkBox->setEnabled(true);
        ui->P_SPIdev4_checkBox->setChecked(false);
        ui->P_SPIdev4_checkBox->setEnabled(false);
        ui->label_PECSPI4_MISO->setText("GPIO3_IO22");
        ui->label_PECSPI4_MOSI->setText("GPIO3_IO28");
        ui->label_PECSPI4_SCK->setText("GPIO3_IO21");
        ui->label_PECSPI4_SS0->setText("GPIO3_IO29");
    }
}

void NOVAembed::on_P_CCMCLKO1_checkBox_toggled(bool checked)
{
    ui->P_CCMCLKO1_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_EPIT1_checkBox->setChecked(false);
        ui->P_EPIT1_checkBox->setEnabled(false);
        ui->label_PGPIO1_IO00->setText("CCM_CLKO1");
    }
    else
    {
        ui->label_PGPIO1_IO00->setText("GPIO1_IO00");
        ui->P_EPIT1_checkBox->setEnabled(true);
    }
}

void NOVAembed::on_P_EPIT1_checkBox_toggled(bool checked)
{
    ui->P_EPIT1_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_CCMCLKO1_checkBox->setChecked(false);
        ui->P_CCMCLKO1_checkBox->setEnabled(false);
        ui->label_PGPIO1_IO00->setText("EPIT1_OUT");
    }
    else
    {
        ui->label_PGPIO1_IO00->setText("GPIO1_IO00");
        ui->P_CCMCLKO1_checkBox->setEnabled(true);
    }
}
/*
void NOVAembed::on_P_PWM1_checkBox_toggled(bool checked)
{
    ui->P_PWM1_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_WD1_checkBox->setChecked(false);
        ui->P_WD1_checkBox->setEnabled(false);
        ui->label_PGPIO4_IO29->setText("PWM1_OUT");

    }
    else
    {
        ui->P_WD1_checkBox->setEnabled(true);
        ui->label_PGPIO4_IO29->setText("GPIO4_IO29");
    }
}
*/
void NOVAembed::on_P_WD1_checkBox_toggled(bool checked)
{
    ui->P_WD1_checkBox->setChecked(checked);
    if ( checked)
    {
        //ui->P_PWM1_checkBox->setChecked(false);
        //ui->P_PWM1_checkBox->setEnabled(false);
        ui->label_PGPIO4_IO29->setText("WDOG1_B");
    }
    else
    {
        //ui->P_PWM1_checkBox->setEnabled(true);
        ui->label_PGPIO4_IO29->setText("GPIO4_IO29");
    }
}

void NOVAembed::on_P_SDCARD3_checkBox_toggled(bool checked)
{
    ui->P_SDCARD3_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_CAN1_checkBox->setChecked(false);
        ui->P_CAN1_checkBox->setEnabled(false);
        ui->P_CAN2_checkBox->setChecked(false);
        ui->P_CAN2_checkBox->setEnabled(false);
        ui->P_UART2_4WirescheckBox->setChecked(false);
        ui->P_UART2_4WirescheckBox->setEnabled(false);
        if ( ui->P_UART2_checkBox->isChecked() == false )
            ui->P_SDCARD3IS8_checkBox->setEnabled(true);
        ui->label_PSD3_CMD->setText("SD3_CMD");
        ui->label_PSD3_CLK->setText("SD3_CLK");
        ui->label_PSD3_DATA0->setText("SD3_DATA0");
        ui->label_PSD3_DATA1->setText("SD3_DATA1");
        ui->label_PSD3_DATA2->setText("SD3_DATA2");
        ui->label_PSD3_DATA3->setText("SD3_DATA3");
    }
    else
    {
        ui->P_CAN1_checkBox->setEnabled(true);
        ui->P_CAN2_checkBox->setEnabled(true);
        ui->P_UART2_4WirescheckBox->setEnabled(true);
        ui->P_SDCARD3IS8_checkBox->setChecked(false);
        ui->P_SDCARD3IS8_checkBox->setEnabled(false);
        ui->label_PSD3_CMD->setText("GPIO7_IO02");
        ui->label_PSD3_CLK->setText("GPIO7_IO03");
        ui->label_PSD3_DATA0->setText("GPIO7_IO04");
        ui->label_PSD3_DATA1->setText("GPIO7_IO05");
        ui->label_PSD3_DATA2->setText("GPIO7_IO06");
        ui->label_PSD3_DATA3->setText("GPIO7_IO07");
        ui->label_PSD3_DATA4->setText("GPIO7_IO01");
        ui->label_PSD3_DATA5->setText("GPIO7_IO00");
        ui->label_PSD3_DATA6->setText("GPIO7_IO18");
        ui->label_PSD3_DATA7->setText("GPIO7_IO17");
    }
}

void NOVAembed::on_P_SDCARD3IS8_checkBox_toggled(bool checked)
{
    ui->P_SDCARD3IS8_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_UART2_checkBox->setChecked(false);
        ui->P_UART2_4WirescheckBox->setChecked(false);
        ui->P_UART2_checkBox->setEnabled(false);
        ui->P_UART2_4WirescheckBox->setEnabled(false);
        ui->label_PSD3_DATA4->setText("SD3_DATA4");
        ui->label_PSD3_DATA5->setText("SD3_DATA5");
        ui->label_PSD3_DATA6->setText("SD3_DATA6");
        ui->label_PSD3_DATA7->setText("SD3_DATA7");
    }
    else
    {
        ui->P_UART2_checkBox->setEnabled(true);
        ui->P_UART2_4WirescheckBox->setEnabled(true);
        ui->label_PSD3_DATA4->setText("GPIO7_IO01");
        ui->label_PSD3_DATA5->setText("GPIO7_IO00");
        ui->label_PSD3_DATA6->setText("GPIO7_IO18");
        ui->label_PSD3_DATA7->setText("GPIO7_IO17");
    }
}

void NOVAembed::on_P_CAN1_checkBox_toggled(bool checked)
{
    ui->P_CAN1_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_SDCARD3_checkBox->setChecked(false);
        ui->P_SDCARD3IS8_checkBox->setChecked(false);
        ui->P_SDCARD3_checkBox->setEnabled(false);
        ui->P_SDCARD3IS8_checkBox->setEnabled(false);
        ui->P_UART2_4WirescheckBox->setChecked(false);
        ui->P_UART2_4WirescheckBox->setEnabled(false);
        ui->label_PSD3_CMD->setText("FLEAXCAN1_TX");
        ui->label_PSD3_CLK->setText("FLEAXCAN1_RX");
    }
    else
    {
        if ( ui->P_CAN2_checkBox->isChecked() == false)
        {
            ui->P_SDCARD3_checkBox->setEnabled(true);
            ui->P_SDCARD3IS8_checkBox->setEnabled(true);
        }
        if ( ui->P_UART2_checkBox->isChecked() == true)
            ui->P_UART2_4WirescheckBox->setEnabled(true);
        ui->label_PSD3_CMD->setText("GPIO7_IO02");
        ui->label_PSD3_CLK->setText("GPIO7_IO03");
    }
}

void NOVAembed::on_P_CAN2_checkBox_toggled(bool checked)
{
    ui->P_CAN2_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->P_SDCARD3_checkBox->setChecked(false);
        ui->P_SDCARD3IS8_checkBox->setChecked(false);
        ui->P_SDCARD3_checkBox->setEnabled(false);
        ui->P_SDCARD3IS8_checkBox->setEnabled(false);
        ui->label_PSD3_DATA0->setText("FLEXCAN2_TX");
        ui->label_PSD3_DATA1->setText("FLEXCAN2_rX");
    }
    else
    {
        if ( ui->P_CAN1_checkBox->isChecked() == false)
        {
            ui->P_SDCARD3_checkBox->setEnabled(true);
            ui->P_SDCARD3IS8_checkBox->setEnabled(true);
        }
        ui->label_PSD3_DATA0->setText("GPIO7_IO04");
        ui->label_PSD3_DATA1->setText("GPIO7_IO05");
    }
}

void NOVAembed::on_P_UART2_checkBox_toggled(bool checked)
{
    ui->P_UART2_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->label_PSD3_DATA4->setText("UART2_RXD");
        ui->label_PSD3_DATA5->setText("UART2_TXD");
        if ( ui->P_CAN1_checkBox->isChecked() == false)
            ui->P_UART2_4WirescheckBox->setEnabled(true);
        ui->P_SDCARD3IS8_checkBox->setChecked(false);
        ui->P_SDCARD3IS8_checkBox->setEnabled(false);
    }
    else
    {
        ui->P_UART2_4WirescheckBox->setChecked(false);
        ui->P_UART2_4WirescheckBox->setEnabled(false);
        ui->P_SDCARD3IS8_checkBox->setEnabled(true);
        ui->label_PSD3_DATA4->setText("GPIO7_IO01");
        ui->label_PSD3_DATA5->setText("GPIO7_IO00");
    }
}

void NOVAembed::on_P_UART2_4WirescheckBox_toggled(bool checked)
{
    ui->P_UART2_4WirescheckBox->setChecked(checked);
    if ( checked)
    {
        ui->P_SDCARD3_checkBox->setChecked(false);
        ui->P_SDCARD3IS8_checkBox->setChecked(false);
        ui->P_SDCARD3_checkBox->setEnabled(false);
        ui->P_SDCARD3IS8_checkBox->setEnabled(false);
        ui->P_CAN1_checkBox->setChecked(false);
        ui->P_CAN1_checkBox->setEnabled(false);
        ui->label_PSD3_CMD->setText("UART2_CTS_B");
        ui->label_PSD3_CLK->setText("UART2_RTS_B");
    }
    else
    {
        ui->P_SDCARD3_checkBox->setEnabled(true);
        ui->P_CAN1_checkBox->setEnabled(true);
        ui->label_PSD3_CMD->setText("GPIO7_IO02");
        ui->label_PSD3_CLK->setText("GPIO7_IO03");
    }
}

void NOVAembed::on_P_UART4_checkBox_toggled(bool checked)
{
    ui->P_UART4_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->label_PUART4_TXD->setText("UART4_TXD");
        ui->label_PUART4_RXD->setText("UART4_RXD");
        ui->P_UART4_4WirescheckBox->setEnabled(true);
    }
    else
    {
        ui->P_UART4_4WirescheckBox->setChecked(false);
        ui->P_UART4_4WirescheckBox->setEnabled(false);
        ui->label_PUART4_TXD->setText("GPIO5_IO30");
        ui->label_PUART4_RXD->setText("GPIO5_IO31");
    }
}

void NOVAembed::on_P_UART4_4WirescheckBox_toggled(bool checked)
{
    ui->P_UART4_4WirescheckBox->setChecked(checked);
    if ( checked)
    {
        ui->label_PUART4_RTS_L->setText("UART4_RTS_L");
        ui->label_PUART4_CTS_L->setText("UART4_CTS_L");
    }
    else
    {
        ui->label_PUART4_RTS_L->setText("GPIO6_IO02");
        ui->label_PUART4_CTS_L->setText("GPIO6_IO03");
    }
}

void NOVAembed::on_P_Audio6_checkBox_toggled(bool checked)
{
    ui->P_Audio6_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->label_PAUD6_TXD->setText("AUD6_TXD");
        ui->label_PAUD6_RXD->setText("AUD6_RXD");
        ui->label_PAUD6_TXFS->setText("AUD6_TXFS");
        ui->label_PAUD6_TXC->setText("AUD6_TXC");
    }
    else
    {
        ui->label_PAUD6_TXD->setText("GPIO4_IO18");
        ui->label_PAUD6_RXD->setText("GPIO4_IO20");
        ui->label_PAUD6_TXFS->setText("GPIO4_IO19");
        ui->label_PAUD6_TXC->setText("GPIO4_IO17");
    }
}

void NOVAembed::on_P_UART1_checkBox_toggled(bool checked)
{
    ui->P_UART1_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->label_PUART1_TXD->setText("UART1_TXD");
        ui->label_PUART1_RXD->setText("UART1_RXD");
    }
    else
    {
        ui->label_PUART1_TXD->setText("GPIO5_IO28");
        ui->label_PUART1_RXD->setText("GPIO5_IO29");
    }
}

void NOVAembed::on_P_KHZ32_checkBox_toggled(bool checked)
{
    ui->P_KHZ32_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->label_P32KHZ_CLK_OUT->setText("32KHZCLK_OUT");
    }
    else
    {
        ui->label_P32KHZ_CLK_OUT->setText("GPIO1_IO08");
    }
}

void NOVAembed::on_P_MHZ24_checkBox_toggled(bool checked)
{
    ui->P_MHZ24_checkBox->setChecked(checked);
    if ( checked)
    {
        ui->label_PGPIO3_IO20->setText("24MHZCLK_OUT");
    }
    else
    {
        ui->label_PGPIO3_IO20->setText("GPIO3_IO20");
    }
}

void NOVAembed::on_P_SPDIF_checkBox_toggled(bool checked)
{
    ui->P_SPDIF_checkBox->setChecked(checked);
    if ( checked )
    {
        ui->label_PSPDIF_OUT->setText("SPDIF_OUT");
        if ( ui->P_SPI4_checkBox->isChecked() == false )
            ui->P_SPDIF_OnJ13checkBox->setEnabled(true);
    }
    else
    {
        ui->P_SPDIF_OnJ13checkBox->setEnabled(false);
        ui->label_PSPDIF_OUT->setText("GPIO7_IO12");
    }
}

void NOVAembed::on_P_SPDIF_OnJ13checkBox_toggled(bool checked)
{
    ui->P_SPDIF_OnJ13checkBox->setChecked(checked);
    if ( checked )
    {
        if ( ui->P_SPDIF_checkBox->isChecked() == true )
        {
            ui->label_PSPDIF_OUT->setText("GPIO7_IO12");
            ui->label_PECSPI4_MISO->setText("SPDIF_OUT");
            ui->P_SPI4_checkBox->setChecked(false);
            ui->P_SPI4_checkBox->setEnabled(false);
            ui->P_SPIdev4_checkBox->setChecked(false);
            ui->P_SPIdev4_checkBox->setEnabled(false);
        }
    }
    else
    {
        ui->label_PSPDIF_OUT->setText("SPDIF_OUT");
        ui->label_PECSPI4_MISO->setText("GPIO3_IO22");
        if ( ui->P_I2C1_OnJ13checkBox->isChecked() == false)
            ui->P_SPI4_checkBox->setEnabled(true);
    }
}


void set_all_io(void)
{
     P_ECSPI1_MISO_comboBox="GPIO5_IO16";
     P_ECSPI1_MOSI_comboBox="GPIO5_IO15";
     P_ECSPI1_SS0_comboBox="GPIO5_IO17";
     P_ECSPI1_SCK_comboBox="GPIO5_IO14";
     P_ECSPI2_SS0_comboBox = "GPIO5_IO12";
     P_ECSPI2_SS1_comboBox = "GPIO5_IO09";
     P_ECSPI2_MISO_comboBox ="GPIO5_IO11";
     P_ECSPI2_MOSI_comboBox = "GPIO5_IO10";
     P_ECSPI2_SCK_comboBox = "GPIO5_IO13";
     P_ECSPI3_MISO_comboBox ="GPIO4_IO23";
     P_ECSPI3_SCK_comboBox = "GPIO4_IO21";
     P_ECSPI3_MOSI_comboBox = "GPIO4_IO22";
     P_ECSPI3_SS0_comboBox = "GPIO4_IO24";
     P_ECSPI3_SS1_comboBox = "GPIO4_IO25";
     P_ECSPI4_MISO_comboBox="GPIO3_IO22";
     P_ECSPI4_MOSI_comboBox = "GPIO3_IO28";
     P_ECSPI4_SCK_comboBox = "GPIO3_IO21";
     P_ECSPI4_SS0_comboBox = "GPIO3_IO29";
     P_I2C3_SCL_comboBox= "GPIO3_IO17";
     P_I2C3_SDA_comboBox= "GPIO3_IO18";
     P_KHZ32_CLK_OUT_comboBox = "GPIO1_IO08";
     P_SD3_CMD_comboBox   ="GPIO7_IO02";
     P_SD3_CLK_comboBox   ="GPIO7_IO03";
     P_SD3_DATA0_comboBox ="GPIO7_IO04";
     P_SD3_DATA1_comboBox ="GPIO7_IO05";
     P_SD3_DATA2_comboBox ="GPIO7_IO06";
     P_SD3_DATA3_comboBox ="GPIO7_IO07";
     P_SD3_DATA4_comboBox ="GPIO7_IO01";
     P_SD3_DATA5_comboBox ="GPIO7_IO00";
     P_SD3_DATA6_comboBox ="GPIO6_IO18";
     P_SD3_DATA7_comboBox ="GPIO6_IO17";
     P_GPIO3_IO20_comboBox ="GPIO3_IO20";
     P_GPIO1_IO00_comboBox ="GPIO1_IO00";
     P_GPIO4_IO29_comboBox ="GPIO4_IO29";
     P_AUD6_TXD_comboBox  ="GPIO4_IO18";
     P_AUD6_RXD_comboBox  ="GPIO4_IO20";
     P_AUD6_TXFS_comboBox ="GPIO4_IO19";
     P_AUD6_TXC_comboBox  ="GPIO4_IO17";
     P_I2C1_SDA_comboBox= "GPIO5_IO26";
     P_I2C1_SCL_comboBox = "GPIO5_IO27";
     P_UART1_TXD_comboBox ="GPIO5_IO28";
     P_UART1_RXD_comboBox = "GPIO5_IO29";
     P_SPDIF_OUT_comboBox= "GPIO7_IO12";
     P_UART4_RTS_L_comboBox= "GPIO6_IO02";
     P_UART4_TXD_comboBox= "GPIO5_IO30";
     P_UART4_RXD_comboBox="GPIO5_IO31";
     P_UART4_CTS_L_comboBox="GPIO6_IO03";
     P_I2C1Speed="100000";
     P_I2C3Speed="100000";
     P_SATA_checkBox="false";
     P_PCIe_checkBox="true";
     P_PrimaryVideo_comboBox="Unset";
     P_SecondaryVideo_comboBox="Unset";
     Processor="Unset";
}

void NOVAembed::P_pin_decode()
{
    set_all_io();
    if ( ui->P_I2C3_checkBox->isChecked() == true )
    {
        P_I2C3_SCL_comboBox ="I2C3_SCL";
        P_I2C3_SDA_comboBox ="I2C3_SDA";
    }
    if ( ui->P_I2C1_checkBox->isChecked() == true )
    {
        if ( ui->P_I2C1_OnJ13checkBox->isChecked() == true )
        {
            P_ECSPI4_MOSI_comboBox = "I2C1_SDA";
            P_ECSPI4_SCK_comboBox  = "I2C1_SCL";
        }
        else
        {
            P_I2C1_SDA_comboBox = "I2C1_SDA";
            P_I2C1_SCL_comboBox  = "I2C1_SCL";
        }
    }

    if ( ui->P_SPI1_checkBox->isChecked() == true )
    {
        P_ECSPI1_MISO_comboBox ="ECSPI1_MISO";
        P_ECSPI1_MOSI_comboBox = "ECSPI1_MOSI";
        P_ECSPI1_SS0_comboBox = "ECSPI1_SS0";
        P_ECSPI1_SCK_comboBox = "ECSPI1_SCK";
    }
    if ( ui->P_SPI2_checkBox->isChecked() == true )
    {
        P_ECSPI2_MISO_comboBox ="ECSPI2_MISO";
        P_ECSPI2_MOSI_comboBox = "ECSPI2_MOSI";
        P_ECSPI2_SS0_comboBox = "ECSPI2_SS0";
        P_ECSPI2_SCK_comboBox = "ECSPI2_SCK";
    }
    if ( ui->P_SPI3_checkBox->isChecked() == true )
    {
        P_ECSPI3_MISO_comboBox ="ECSPI3_MISO";
        P_ECSPI3_MOSI_comboBox = "ECSPI3_MOSI";
        P_ECSPI3_SS0_comboBox = "ECSPI3_SS0";
        P_ECSPI3_SCK_comboBox = "ECSPI3_SCK";
    }
    else
    {
        P_ECSPI3_MISO_comboBox ="GPIO4_IO23";
        P_ECSPI3_MOSI_comboBox = "GPIO4_IO22";
        P_ECSPI3_SS0_comboBox = "GPIO4_IO24";
        P_ECSPI3_SCK_comboBox = "GPIO4_IO21";
    }
    if ( ui->P_SPI4_checkBox->isChecked() == true )
    {
        P_ECSPI4_MISO_comboBox ="ECSPI4_MISO";
        P_ECSPI4_MOSI_comboBox = "ECSPI4_MOSI";
        P_ECSPI4_SS0_comboBox = "ECSPI4_SS0";
        P_ECSPI4_SCK_comboBox = "ECSPI4_SCK";
    }
    else
    {
        if (( ui->P_SPDIF_checkBox->isChecked() == true ) && ( ui->P_SPDIF_OnJ13checkBox->isChecked() == true ))
            P_ECSPI4_MISO_comboBox ="GPIO3_IO22";
        if ( ui->P_I2C1_checkBox->isChecked() == false )
            P_ECSPI4_MOSI_comboBox = "GPIO3_IO28";
        if (( ui->P_I2C1_checkBox->isChecked() == true ) && ( ui->P_I2C1_OnJ13checkBox->isChecked() == false ))
            P_ECSPI4_MOSI_comboBox = "GPIO3_IO28";
        P_ECSPI4_SS0_comboBox = "GPIO3_IO29";
        if ( ui->P_I2C1_checkBox->isChecked() == false )
            P_ECSPI4_SCK_comboBox = "GPIO3_IO21";
        if (( ui->P_I2C1_checkBox->isChecked() == true ) && ( ui->P_I2C1_OnJ13checkBox->isChecked() == false ))
            P_ECSPI4_SCK_comboBox = "GPIO3_IO21";
    }

    if (( ui->P_SPDIF_checkBox->isChecked() == true ) && ( ui->P_SPDIF_OnJ13checkBox->isChecked() == false ))
        P_SPDIF_OUT_comboBox ="SPDIF_OUT";
    if (( ui->P_SPDIF_checkBox->isChecked() == true ) && ( ui->P_SPDIF_OnJ13checkBox->isChecked() == true ))
        P_ECSPI4_MISO_comboBox ="SPDIF_OUT";

    if ( ui->P_SPI1_2ndSScheckBox->isChecked() == true )
        P_ECSPI2_SS1_comboBox = "ECSPI1_SS1";
    else if ( ui->P_SPI2_2ndSScheckBox->isChecked() == true )
        P_ECSPI2_SS1_comboBox = "ECSPI2_SS1";
    else
        P_ECSPI2_SS1_comboBox = "GPIO5_IO09";

    if ( ui->P_SPI3_2ndSScheckBox->isChecked() == true )
        P_ECSPI3_SS1_comboBox = "ECSPI3_SS1";
    else
        P_ECSPI3_SS1_comboBox = "GPIO4_IO25";


    if ( ui->P_Audio4_checkBox->isChecked() == true )
    {
        P_ECSPI1_MISO_comboBox ="AUD4_TXFS";
        P_ECSPI1_MOSI_comboBox = "AUD4_TXD";
        P_ECSPI1_SS0_comboBox = "AUD4_RXD";
        P_ECSPI1_SCK_comboBox = "AUD4_TXC";
    }
    if (( ui->P_Audio4_checkBox->isChecked() == false ) && ( ui->P_SPI1_checkBox->isChecked() == false ))
    {
        P_ECSPI1_MISO_comboBox ="GPIO5_IO16";
        P_ECSPI1_MOSI_comboBox = "GPIO5_IO15";
        P_ECSPI1_SS0_comboBox = "GPIO5_IO17";
        P_ECSPI1_SCK_comboBox = "GPIO5_IO14";
    }
    if ( ui->P_Audio5_checkBox->isChecked() == true )
    {
        P_ECSPI2_MISO_comboBox ="AUD5_TXD";
        P_ECSPI2_MOSI_comboBox = "AUD5_TXC";
        P_ECSPI2_SS0_comboBox = "AUD5_TXFS";
        P_ECSPI2_SCK_comboBox = "AUD5_RXD";
    }

    if (( ui->P_Audio5_checkBox->isChecked() == false ) && ( ui->P_SPI2_checkBox->isChecked() == false ))
    {
        P_ECSPI2_MISO_comboBox ="GPIO5_IO11";
        P_ECSPI2_MOSI_comboBox = "GPIO5_IO10";
        P_ECSPI2_SS0_comboBox = "GPIO5_IO12";
        P_ECSPI2_SCK_comboBox = "GPIO5_IO13";
    }
    if ( ui->P_Audio6_checkBox->isChecked() == true )
    {
        P_AUD6_TXD_comboBox ="AUD6_TXD";
        P_AUD6_RXD_comboBox = "AUD6_TXC";
        P_AUD6_TXFS_comboBox = "AUD6_TXFS";
        P_AUD6_TXC_comboBox = "AUD6_RXD";
    }
    else
    {
        P_AUD6_TXD_comboBox ="GPIO4_IO18";
        P_AUD6_RXD_comboBox = "GPIO4_IO20";
        P_AUD6_TXFS_comboBox = "GPIO4_IO19";
        P_AUD6_TXC_comboBox = "GPIO4_IO17";
    }


    if ( ui->P_SDCARD3_checkBox->isChecked())
    {
        P_SD3_CMD_comboBox = "SD3_CMD";
        P_SD3_CLK_comboBox = "SD3_CLK";
        P_SD3_DATA0_comboBox = "SD3_DATA0";
        P_SD3_DATA1_comboBox = "SD3_DATA1";
        P_SD3_DATA2_comboBox = "SD3_DATA2";
        P_SD3_DATA3_comboBox = "SD3_DATA3";
        if ( ui->P_SDCARD3IS8_checkBox->isChecked())
        {
            P_SD3_DATA4_comboBox = "SD3_DATA4";
            P_SD3_DATA5_comboBox = "SD3_DATA5";
            P_SD3_DATA6_comboBox = "SD3_DATA6";
            P_SD3_DATA7_comboBox = "SD3_DATA7";
        }
    }

    if ( ui->P_CAN1_checkBox->isChecked() == true )
    {
        P_SD3_CLK_comboBox = "FLEXCAN1_RX";
        P_SD3_CMD_comboBox = "FLEXCAN1_TX";
    }

    if ( ui->P_CAN1_checkBox->isChecked() == true )
    {
        P_SD3_CLK_comboBox = "FLEXCAN1_RX";
        P_SD3_CMD_comboBox = "FLEXCAN1_TX";
    }

    if ( ui->P_CAN2_checkBox->isChecked() == true )
    {
        P_SD3_DATA0_comboBox = "FLEXCAN2_TX";
        P_SD3_DATA1_comboBox = "FLEXCAN2_RX";
    }
    if ( ui->P_UART1_checkBox->isChecked() == true )
    {
        P_UART1_TXD_comboBox = "UART1_TXD";
        P_UART1_RXD_comboBox = "UART1_RXD";
    }
    if ( ui->P_UART2_checkBox->isChecked() == true )
    {
        P_SD3_DATA4_comboBox = "UART2_RXD";
        P_SD3_DATA5_comboBox = "UART2_TXD";
    }
    if ( ui->P_UART2_4WirescheckBox->isChecked() == true )
    {
        P_SD3_CMD_comboBox = "UART2_CTS_B";
        P_SD3_CLK_comboBox = "UART2_RTS_B";
    }
    if ( ui->P_UART4_checkBox->isChecked() == true )
    {
        P_UART4_RXD_comboBox = "UART4_RXD";
        P_UART4_TXD_comboBox = "UART4_TXD";
    }
    if ( ui->P_UART4_4WirescheckBox->isChecked() == true )
    {
        P_UART4_CTS_L_comboBox = "UART4_CTS_L";
        P_UART4_RTS_L_comboBox = "UART4_RTS_L";
    }

    if ( ui->P_KHZ32_checkBox->isChecked() == true )
    {
        P_KHZ32_CLK_OUT_comboBox = "32KHZ_CLK_OUT";
    }

    if ( ui->P_CCMCLKO1_checkBox->isChecked() == true )
    {
        P_GPIO1_IO00_comboBox = "CCM_CLKO1";
    }
    else
    {
        if ( ui->P_EPIT1_checkBox->isChecked() == true )
            P_GPIO1_IO00_comboBox = "EPIT1_OUT";
        else
            P_GPIO1_IO00_comboBox = "GPIO1_IO00";
    }

    /*if ( ui->P_PWM1_checkBox->isChecked() == true )
    {
        P_GPIO4_IO29_comboBox = "PWM1_OUT";
    }
    else
    */
    {
        if ( ui->P_WD1_checkBox->isChecked() == true )
            P_GPIO4_IO29_comboBox = "WDOG1_B";
        else
            P_GPIO4_IO29_comboBox = "GPIO1_IO00";
    }
    if ( ui->P_MHZ24_checkBox->isChecked() == true )
    {
        P_GPIO3_IO20_comboBox = "XTALOSC_REF_CLK_24M";
    }
    else
    {
        P_GPIO3_IO20_comboBox = "GPIO3_IO20";
    }

    if ( ui->P_SATA_checkBox->isChecked() )
        P_SATA_checkBox = "P_SATA_checkBox=true";
    else
        P_SATA_checkBox = "P_SATA_checkBox=false";

    if ( ui->P_PCIe_checkBox->isChecked())
        P_PCIe_checkBox = "P_PCIe_checkBox=true";
    else
        P_PCIe_checkBox = "P_PCIe_checkBox=false";

    P_PrimaryVideo_comboBox   = ui->PrimaryVideo_comboBox->currentText();
    P_SecondaryVideo_comboBox = ui->SecondaryVideo_comboBox->currentText();
}

void NOVAembed::P_save_helper(QString fileName , QString Processor_model)
{
    QFileInfo fin(fileName);
    QString bspfbase = fin.baseName();
    QString fullpathname = "";
    if ( Processor_model.isEmpty() )
    {
        fullpathname = instpath+"/DtbUserWorkArea/PClass_bspf/"+ bspfbase+".bspf";
    }
    else
    {
        fullpathname = instpath+"/DtbUserWorkArea/PClass_bspf/temp/"+Processor_model + "_" + bspfbase+".bspf";
    }
    QFile file(fullpathname);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file "),file.errorString());
        return;
    }

    P_pin_decode();
    QTextStream out(&file);
    out << QString("[P_IOMUX]\n");
    out << QString("P_ECSPI1_MISO_comboBox="+P_ECSPI1_MISO_comboBox+"\n");
    out << QString("P_ECSPI1_MOSI_comboBox="+P_ECSPI1_MOSI_comboBox+"\n");
    out << QString("P_ECSPI1_SS0_comboBox="+P_ECSPI1_SS0_comboBox+"\n");
    out << QString("P_ECSPI1_SCK_comboBox="+P_ECSPI1_SCK_comboBox+"\n");
    out << QString("P_ECSPI2_SS0_comboBox="+P_ECSPI2_SS0_comboBox+"\n");
    out << QString("P_ECSPI2_SS1_comboBox="+P_ECSPI2_SS1_comboBox+"\n");
    out << QString("P_ECSPI2_MISO_comboBox="+P_ECSPI2_MISO_comboBox+"\n");
    out << QString("P_ECSPI2_MOSI_comboBox="+P_ECSPI2_MOSI_comboBox+"\n");
    out << QString("P_ECSPI2_SCK_comboBox="+P_ECSPI2_SCK_comboBox+"\n");
    out << QString("P_ECSPI3_MISO_comboBox="+P_ECSPI3_MISO_comboBox+"\n");
    out << QString("P_ECSPI3_SCK_comboBox="+P_ECSPI3_SCK_comboBox+"\n");
    out << QString("P_ECSPI3_MOSI_comboBox="+P_ECSPI3_MOSI_comboBox+"\n");
    out << QString("P_ECSPI3_SS0_comboBox="+P_ECSPI3_SS0_comboBox+"\n");
    out << QString("P_ECSPI3_SS1_comboBox="+P_ECSPI3_SS1_comboBox+"\n");
    out << QString("P_ECSPI4_MISO_comboBox="+P_ECSPI4_MISO_comboBox+"\n");
    out << QString("P_ECSPI4_MOSI_comboBox="+P_ECSPI4_MOSI_comboBox+"\n");
    out << QString("P_ECSPI4_SCK_comboBox="+P_ECSPI4_SCK_comboBox+"\n");
    out << QString("P_ECSPI4_SS0_comboBox="+P_ECSPI4_SS0_comboBox+"\n");
    out << QString("P_I2C3_SCL_comboBox="+P_I2C3_SCL_comboBox+"\n");
    out << QString("P_I2C3_SDA_comboBox="+P_I2C3_SDA_comboBox+"\n");
    out << QString("P_KHZ32_CLK_OUT_comboBox="+P_KHZ32_CLK_OUT_comboBox+"\n");
    out << QString("P_SD3_CMD_comboBox="+P_SD3_CMD_comboBox+"\n");
    out << QString("P_SD3_CLK_comboBox="+P_SD3_CLK_comboBox+"\n");
    out << QString("P_SD3_DATA0_comboBox="+P_SD3_DATA0_comboBox+"\n");
    out << QString("P_SD3_DATA1_comboBox="+P_SD3_DATA1_comboBox+"\n");
    out << QString("P_SD3_DATA2_comboBox="+P_SD3_DATA2_comboBox+"\n");
    out << QString("P_SD3_DATA3_comboBox="+P_SD3_DATA3_comboBox+"\n");
    out << QString("P_SD3_DATA4_comboBox="+P_SD3_DATA4_comboBox+"\n");
    out << QString("P_SD3_DATA5_comboBox="+P_SD3_DATA5_comboBox+"\n");
    out << QString("P_SD3_DATA6_comboBox="+P_SD3_DATA6_comboBox+"\n");
    out << QString("P_SD3_DATA7_comboBox="+P_SD3_DATA7_comboBox+"\n");
    out << QString("P_GPIO3_IO20_comboBox="+P_GPIO3_IO20_comboBox+"\n");
    out << QString("P_GPIO1_IO00_comboBox="+P_GPIO1_IO00_comboBox+"\n");
    out << QString("P_GPIO4_IO29_comboBox="+P_GPIO4_IO29_comboBox+"\n");
    out << QString("P_AUD6_TXD_comboBox="+P_AUD6_TXD_comboBox+"\n");
    out << QString("P_AUD6_RXD_comboBox="+P_AUD6_RXD_comboBox+"\n");
    out << QString("P_AUD6_TXFS_comboBox="+P_AUD6_TXFS_comboBox+"\n");
    out << QString("P_AUD6_TXC_comboBox="+P_AUD6_TXC_comboBox+"\n");
    out << QString("P_I2C1_SDA_comboBox="+P_I2C1_SDA_comboBox+"\n");
    out << QString("P_I2C1_SCL_comboBox="+P_I2C1_SCL_comboBox+"\n");
    out << QString("P_UART1_TXD_comboBox="+P_UART1_TXD_comboBox+"\n");
    out << QString("P_UART1_RXD_comboBox="+P_UART1_RXD_comboBox+"\n");
    out << QString("P_SPDIF_OUT_comboBox="+P_SPDIF_OUT_comboBox+"\n");
    out << QString("P_UART4_RTS_L_comboBox="+P_UART4_RTS_L_comboBox+"\n");
    out << QString("P_UART4_TXD_comboBox="+P_UART4_TXD_comboBox+"\n");
    out << QString("P_UART4_RXD_comboBox="+P_UART4_RXD_comboBox+"\n");
    out << QString("P_UART4_CTS_L_comboBox="+P_UART4_CTS_L_comboBox+"\n");
    if ( ui->P_I2C1Speed_lineEdit->text().isEmpty() )
        ui->P_I2C1Speed_lineEdit->setText("100000");
    if ( ui->P_I2C3Speed_lineEdit->text().isEmpty() )
        ui->P_I2C3Speed_lineEdit->setText("100000");
    P_I2C1Speed = ui->P_I2C1Speed_lineEdit->text();
    P_I2C3Speed = ui->P_I2C3Speed_lineEdit->text();
    out << QString("P_I2C1Speed="+P_I2C1Speed+"\n");
    out << QString("P_I2C3Speed="+P_I2C3Speed+"\n");

    if ( ui->PriVideo_24bit_checkBox->isChecked() )
        out << QString("P_PriVideo_24bit_checkBox=true\n");
    else
        out << QString("P_PriVideo_24bit_checkBox=false\n");
    if (ui->PriVideo_spwg_checkBox->isChecked() )
        out << QString("P_PriVideo_spwg_checkBox=true\n");
    else
        out << QString("P_PriVideo_spwg_checkBox=false\n");

    if ( ui->SecVideo_24bit_checkBox->isChecked() )
        out << QString("P_SecVideo_24bit_checkBox=true\n");
    else
        out << QString("P_SecVideo_24bit_checkBox=false\n");
    if (ui->SecVideo_spwg_checkBox->isChecked() )
        out << QString("P_SecVideo_spwg_checkBox=true\n");
    else
        out << QString("P_SecVideo_spwg_checkBox=false\n");

    if ( ui->P_SPIdev1_checkBox->isChecked() )
        out << QString("P_SPIdev1_checkBox=true\n");
    else
        out << QString("P_SPIdev1_checkBox=false\n");
    if ( ui->P_SPIdev2_checkBox->isChecked() )
        out << QString("P_SPIdev2_checkBox=true\n");
    else
        out << QString("P_SPIdev2_checkBox=false\n");
    if ( ui->P_SPIdev3_checkBox->isChecked() )
        out << QString("P_SPIdev3_checkBox=true\n");
    else
        out << QString("P_SPIdev3_checkBox=false\n");
    if ( ui->P_SPIdev4_checkBox->isChecked() )
        out << QString("P_SPIdev4_checkBox=true\n");
    else
        out << QString("P_SPIdev4_checkBox=false\n");
    if ( +ui->P_PCIe_checkBox->isChecked())
        out << QString("P_PCIe_checkBox=true\n");
    else
        out << QString("P_PCIe_checkBox=false\n");
    if ( +ui->PriVideo_spwg_checkBox->isChecked())
        out << QString("PriVideo_spwg_checkBox=true\n");
    else
        out << QString("PriVideo_spwg_checkBox=false\n");
    out << QString("PrimaryVideo_comboBox="+ui->PrimaryVideo_comboBox->currentText()+"\n");
    out << QString("SecondaryVideo_comboBox="+ui->SecondaryVideo_comboBox->currentText()+"\n");
    P_PrimaryVideo_comboBox   = ui->PrimaryVideo_comboBox->currentText();
    P_SecondaryVideo_comboBox = ui->SecondaryVideo_comboBox->currentText();
    if ( Processor_model == "QUAD")
    {
        out << QString("Processor=QUAD\n");
        if ( ui->P_SATA_checkBox->isChecked() )
            out << QString("P_SATA_checkBox=true\n");
        else
            out << QString("P_SATA_checkBox=false\n");
    }
    else
    {
        if ( Processor_model.isEmpty() )
        {
            if ( ui->P_SATA_checkBox->isChecked() )
                out << QString("P_SATA_checkBox=true\n");
            else
                out << QString("P_SATA_checkBox=false\n");
        }
        else
        {
            out << QString("Processor=SOLO/DL\n");
            out << QString("P_SATA_checkBox=false\n");
        }
    }

    out << QString("\n[P_CONF]\n");
    out << QString("P_ECSPI1_MISO_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI1_MOSI_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI1_SS0_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI1_SCK_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI2_SS0_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI2_SS1_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI2_MISO_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI2_MOSI_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI2_SCK_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI3_MISO_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI3_SCK_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI3_MOSI_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI3_SS0_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI3_SS1_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI4_MISO_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI4_MOSI_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI4_SCK_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_ECSPI4_SS0_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_I2C3_SCL_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_I2C3_SDA_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_KHZ32_CLK_OUT_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_CMD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_CLK_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA0_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA1_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA2_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA3_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA4_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA5_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA6_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SD3_DATA7_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO3_IO19_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO3_IO20_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO1_IO00_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO4_IO14_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO4_IO26_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO4_IO27_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO4_IO28_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO4_IO29_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_GPIO6_IO05_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_AUD6_TXD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_AUD6_RXD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_AUD6_TXFS_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_AUD6_TXC_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_I2C1_SDA_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_I2C1_SCL_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_UART1_TXD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_UART1_RXD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_SPDIF_OUT_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_UART4_RTS_L_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_UART4_TXD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_UART4_RXD_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("P_UART4_CTS_L_cbit="+ui->P_cbit_lineEdit->text()+"\n");

    file.close();
    update_status_bar("File "+Last_P_BSPFactoryFile+" saved");
    Last_P_BSPFactoryFile = bspfbase;
    storeNOVAembed_ini();
}



void NOVAembed::on_P_Load_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), instpath+"/DtbUserWorkArea/PClass_bspf",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        on_P_Clear_pushButton_clicked();
        P_load_BSPF_File(fileName);
        update_status_bar("File "+Last_P_BSPFactoryFile+" loaded");
        QFileInfo fi(fileName);
        ui->P_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->P_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    }
}

void NOVAembed::P_load_BSPF_File(QString fileName)
{
QString strKeyFunc("P_IOMUX/");
QSettings * func_settings = 0;

    on_P_Clear_pushButton_clicked();
    set_all_io();
    func_settings = new QSettings( fileName+".bspf", QSettings::IniFormat );
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI1_MISO_comboBox") == "ECSPI1_MISO" )
        on_P_SPI1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_MISO_comboBox") == "ECSPI2_MISO" )
        on_P_SPI2_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI3_MISO_comboBox") == "ECSPI3_MISO" )
        on_P_SPI3_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_MISO_comboBox") == "ECSPI4_MISO" )
        on_P_SPI4_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_SS1_comboBox") == "ECSPI1_SS1" )
        on_P_SPI1_2ndSScheckBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_SS1_comboBox") == "ECSPI2_SS1" )
        on_P_SPI2_2ndSScheckBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI1_MISO_comboBox") == "AUD4_TXFS" )
        on_P_Audio4_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_MISO_comboBox") == "AUD5_TXD" )
        on_P_Audio5_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_AUD6_TXD_comboBox") == "AUD6_TXD" )
        on_P_Audio6_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_MOSI_comboBox") == "I2C1_SDA" )
    {
        on_P_I2C1_checkBox_toggled(true);
        on_P_I2C1_OnJ13checkBox_toggled(true);
    }
    if ( P_getvalue(strKeyFunc, func_settings , "P_I2C1_SDA_comboBox") == "I2C1_SDA" )
        on_P_I2C1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_I2C3_SCL_comboBox") == "I2C3_SCL" )
        on_P_I2C3_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_CMD_comboBox") == "FLEXCAN1_TX" )
        on_P_CAN1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA0_comboBox") == "FLEXCAN2_TX" )
        on_P_CAN2_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_UART1_TXD_comboBox") == "UART1_TXD" )
        on_P_UART1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA4_comboBox") == "UART2_RXD" )
        on_P_UART2_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_CMD_comboBox") == "UART2_CTS_B" )
        on_P_UART2_4WirescheckBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_UART4_TXD_comboBox") == "UART4_TXD" )
        on_P_UART4_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_UART4_RTS_L_comboBox") == "UART4_RTS_L" )
        on_P_UART4_4WirescheckBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_KHZ32_CLK_OUT_comboBox") == "32KHZ_CLK_OUT" )
        on_P_KHZ32_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_GPIO3_IO20_comboBox") == "XTALOSC_REF_CLK_24M" )
        on_P_MHZ24_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_GPIO1_IO00_comboBox") == "CCM_CLKO1" )
        on_P_CCMCLKO1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_GPIO1_IO00_comboBox") == "EPIT1_OUT" )
        on_P_EPIT1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_GPIO4_IO29_comboBox") == "WDOG1_B" )
        on_P_WD1_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_CMD_comboBox") == "SD3_CMD" )
        on_P_SDCARD3_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA4_comboBox") == "SD3_DATA4" )
        on_P_SDCARD3IS8_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA4_comboBox") == "SD3_DATA4" )
        on_P_SDCARD3IS8_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SPDIF_OUT_comboBox") == "SPDIF_OUT" )
        on_P_SPDIF_checkBox_toggled(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_MISO_comboBox") == "SPDIF_OUT" )
    {
        on_P_SPDIF_checkBox_toggled(true);
        on_P_SPDIF_OnJ13checkBox_toggled(true);
    }
    ui->P_I2C1Speed_lineEdit->setText(P_getvalue(strKeyFunc, func_settings , "P_I2C1Speed"));
    ui->P_I2C3Speed_lineEdit->setText(P_getvalue(strKeyFunc, func_settings , "P_I2C3Speed"));

    ui->P_SPIdev1_checkBox->setChecked(false);
    ui->P_SPIdev2_checkBox->setChecked(false);
    ui->P_SPIdev3_checkBox->setChecked(false);
    ui->P_SPIdev4_checkBox->setChecked(false);

    if ( P_getvalue(strKeyFunc, func_settings , "P_SPIdev1_checkBox") == "true" )
        ui->P_SPIdev1_checkBox->setChecked(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SPIdev2_checkBox") == "true" )
        ui->P_SPIdev2_checkBox->setChecked(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SPIdev3_checkBox") == "true" )
        ui->P_SPIdev3_checkBox->setChecked(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SPIdev4_checkBox") == "true" )
        ui->P_SPIdev4_checkBox->setChecked(true);

    if ( P_getvalue(strKeyFunc, func_settings , "P_SATA_checkBox") == "true" )
        ui->P_SATA_checkBox->setChecked(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_PCIe_checkBox") == "true" )
        ui->P_PCIe_checkBox->setChecked(true);
    ui->PrimaryVideo_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "PrimaryVideo_comboBox"));
    ui->SecondaryVideo_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SecondaryVideo_comboBox"));
    ui->PriVideo_24bit_checkBox->setChecked(false);
    ui->PriVideo_spwg_checkBox->setChecked(false);
    ui->SecVideo_24bit_checkBox->setChecked(false);
    ui->SecVideo_spwg_checkBox->setChecked(false);

    if ( P_getvalue(strKeyFunc, func_settings , "P_PriVideo_24bit_checkBox") == "true" )
        ui->PriVideo_24bit_checkBox->setChecked(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_PriVideo_spwg_checkBox") == "true" )
        ui->PriVideo_spwg_checkBox->setChecked(true);

    if ( P_getvalue(strKeyFunc, func_settings , "P_SecVideo_24bit_checkBox") == "true" )
        ui->SecVideo_24bit_checkBox->setChecked(true);
    if ( P_getvalue(strKeyFunc, func_settings , "P_SecVideo_spwg_checkBox") == "true" )
        ui->SecVideo_spwg_checkBox->setChecked(true);

}

void NOVAembed::on_P_Clear_pushButton_clicked()
{
    ui->PrimaryVideo_comboBox->setCurrentIndex(0);
    ui->SecondaryVideo_comboBox->setCurrentIndex(0);
    ui->P_SPI1_checkBox->setChecked(false);
    ui->P_SPI2_checkBox->setChecked(false);
    ui->P_SPI3_checkBox->setChecked(false);
    ui->P_SPI4_checkBox->setChecked(false);
    ui->P_SPI1_2ndSScheckBox->setChecked(false);
    ui->P_SPI1_2ndSScheckBox->setEnabled(false);
    ui->P_SPI2_2ndSScheckBox->setChecked(false);
    ui->P_SPI2_2ndSScheckBox->setEnabled(false);
    ui->P_SPI3_2ndSScheckBox->setChecked(false);
    ui->P_SPI3_2ndSScheckBox->setEnabled(false);
    ui->P_SPIdev1_checkBox->setChecked(false);
    ui->P_SPIdev2_checkBox->setChecked(false);
    ui->P_SPIdev3_checkBox->setChecked(false);
    ui->P_SPIdev4_checkBox->setChecked(false);
    ui->P_SPIdev1_checkBox->setEnabled(false);
    ui->P_SPIdev2_checkBox->setEnabled(false);
    ui->P_SPIdev3_checkBox->setEnabled(false);
    ui->P_SPIdev4_checkBox->setEnabled(false);

    ui->P_Audio4_checkBox->setChecked(false);
    ui->P_Audio5_checkBox->setChecked(false);
    ui->P_Audio6_checkBox->setChecked(false);

    ui->P_CAN1_checkBox->setChecked(false);
    ui->P_CAN2_checkBox->setChecked(false);

    ui->P_CCMCLKO1_checkBox->setChecked(false);
    ui->P_EPIT1_checkBox->setChecked(false);

    ui->P_I2C1_checkBox->setChecked(false);
    ui->P_I2C1_OnJ13checkBox->setChecked(false);
    ui->P_I2C1_OnJ13checkBox->setEnabled(false);
    ui->P_I2C3_checkBox->setChecked(false);

    ui->P_KHZ32_checkBox->setChecked(false);
    ui->P_MHZ24_checkBox->setChecked(false);
    //ui->P_PWM1_checkBox->setChecked(false);
    ui->P_PCIe_checkBox->setChecked(true);
    ui->P_SATA_checkBox->setChecked(false);
    ui->P_SPDIF_checkBox->setChecked(false);
    ui->P_SPDIF_OnJ13checkBox->setChecked(false);
    ui->P_SPDIF_OnJ13checkBox->setEnabled(false);
    ui->P_UART1_checkBox->setChecked(false);
    ui->P_UART2_checkBox->setChecked(false);
    ui->P_UART4_checkBox->setChecked(false);
    ui->P_UART2_4WirescheckBox->setChecked(false);
    ui->P_UART2_4WirescheckBox->setEnabled(false);
    ui->P_UART4_4WirescheckBox->setChecked(false);
    ui->P_UART4_4WirescheckBox->setEnabled(false);

    ui->P_SDCARD3_checkBox->setChecked(false);
    ui->P_SDCARD3IS8_checkBox->setChecked(false);
    ui->P_SDCARD3IS8_checkBox->setEnabled(false);
/* FILIPPO */

    ui->label_PECSPI1_MISO->setText("GPIO5_IO16");
    ui->label_PECSPI1_MOSI->setText("GPIO5_IO15");
    ui->label_PECSPI1_SS0->setText("GPIO5_IO17");
    ui->label_PECSPI1_SCK->setText("GPIO5_IO14");
    ui->label_PECSPI2_SS0 ->setText( "GPIO5_IO12");
    ui->label_PECSPI2_SS1 ->setText( "GPIO5_IO09");
    ui->label_PECSPI2_MISO ->setText("GPIO5_IO11");
    ui->label_PECSPI2_MOSI ->setText( "GPIO5_IO10");
    ui->label_PECSPI2_SCK ->setText( "GPIO5_IO13");
    ui->label_PECSPI3_MISO ->setText("GPIO4_IO23");
    ui->label_PECSPI3_SCK ->setText( "GPIO4_IO21");
    ui->label_PECSPI3_MOSI ->setText( "GPIO4_IO22");
    ui->label_PECSPI3_SS0 ->setText( "GPIO4_IO24");
    ui->label_PECSPI3_SS1 ->setText( "GPIO4_IO25");
    ui->label_PECSPI4_MISO->setText("GPIO3_IO22");
    ui->label_PECSPI4_MOSI ->setText( "GPIO3_IO28");
    ui->label_PECSPI4_SCK ->setText( "GPIO3_IO21");
    ui->label_PECSPI4_SS0 ->setText( "GPIO3_IO29");
    ui->label_PI2C3_SCL->setText( "GPIO3_IO17");
    ui->label_PI2C3_SDA->setText( "GPIO3_IO18");
    ui->label_P32KHZ_CLK_OUT ->setText( "GPIO1_IO08");
    ui->label_PSD3_CMD->setText("GPIO7_IO02");
    ui->label_PSD3_CLK->setText("GPIO7_IO03");
    ui->label_PSD3_DATA0->setText("GPIO7_IO04");
    ui->label_PSD3_DATA1->setText("GPIO7_IO05");
    ui->label_PSD3_DATA2->setText("GPIO7_IO06");
    ui->label_PSD3_DATA3->setText("GPIO7_IO07");
    ui->label_PSD3_DATA4->setText("GPIO7_IO01");
    ui->label_PSD3_DATA5->setText("GPIO7_IO00");
    ui->label_PSD3_DATA6->setText("GPIO7_IO18");
    ui->label_PSD3_DATA7->setText("GPIO7_IO17");
    ui->label_PGPIO3_IO20 ->setText("GPIO3_IO20");
    ui->label_PGPIO1_IO00 ->setText("GPIO1_IO00");
    ui->label_PGPIO4_IO29 ->setText("GPIO4_IO29");
    ui->label_PAUD6_TXD  ->setText("GPIO4_IO18");
    ui->label_PAUD6_RXD  ->setText("GPIO4_IO20");
    ui->label_PAUD6_TXFS ->setText("GPIO4_IO19");
    ui->label_PAUD6_TXC  ->setText("GPIO4_IO17");
    ui->label_PI2C1_SDA->setText( "GPIO5_IO26");
    ui->label_PI2C1_SCL ->setText( "GPIO5_IO27");
    ui->label_PUART1_TXD ->setText("GPIO5_IO28");
    ui->label_PUART1_RXD ->setText( "GPIO5_IO29");
    ui->label_PSPDIF_OUT->setText( "GPIO7_IO12");
    ui->label_PUART4_RTS_L->setText( "GPIO6_IO02");
    ui->label_PUART4_TXD->setText( "GPIO5_IO30");
    ui->label_PUART4_RXD->setText("GPIO5_IO31");
    ui->label_PUART4_CTS_L->setText("GPIO6_IO03");

    ui->label_PSD3_CMD->setText("GPIO7_IO02");
    ui->label_PSD3_CLK->setText("GPIO7_IO03");
    ui->label_PSD3_DATA0->setText("GPIO7_IO04");
    ui->label_PSD3_DATA1->setText("GPIO7_IO05");
    ui->label_PSD3_DATA2->setText("GPIO7_IO06");
    ui->label_PSD3_DATA3->setText("GPIO7_IO07");
    ui->label_PSD3_DATA4->setText("GPIO7_IO01");
    ui->label_PSD3_DATA5->setText("GPIO7_IO00");
    ui->label_PSD3_DATA6->setText("GPIO7_IO18");
    ui->label_PSD3_DATA7->setText("GPIO7_IO17");

}


void NOVAembed::on_P_Save_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/PClass_bspf",tr(".bspf (*.bspf)"));
    if ( fileName.isEmpty() )
        return;
    QFileInfo fi(fileName);
    ui->P_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
    ui->P_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    P_save_helper(fileName,"QUAD");
    P_save_helper(fileName,"SDL");
    P_save_helper(fileName,"");
    Last_P_BSPFactoryFile = fi.baseName();
    storeNOVAembed_ini();
}

extern      int skip_filesave_on_Generate_pushButton_clicked;

void NOVAembed::on_P_Generate_pushButton_clicked()
{
QFile scriptfile("/tmp/script");
QString SDL_FileNameNoExtension ;
QString QUAD_FileNameNoExtension;
    if ( CheckIfKernelsPresent() == 1 )
    {
        update_status_bar("Kernel "+Kernel+" not present, download it.");
        return;
    }
    // Save .bspf and Generate .dtb
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/PClass_bspf",tr(".bspf (*.bspf)"));
    if ( fileName.isEmpty() )
        return;
    QFileInfo fi(fileName);
    if ( skip_filesave_on_Generate_pushButton_clicked == 0)
    {
        QFile scriptfile("/tmp/script");
        ui->P_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->P_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        P_save_helper(fileName,"QUAD");
        P_save_helper(fileName,"SDL");
        P_save_helper(fileName,"");
    }
    Last_P_BSPFactoryFile = fi.baseName();
    storeNOVAembed_ini();
    SDL_FileNameNoExtension  = "SDL_"+fi.baseName();
    QUAD_FileNameNoExtension = "QUAD_"+fi.baseName();

    update_status_bar("Generating dtb "+SDL_FileNameNoExtension+".dtb and "+QUAD_FileNameNoExtension+" ...");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    if ( ui->P_EditBeforeGenerate_checkBox->isChecked())
        update_status_bar("User editing dtsi file");

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("[ ! -d "+instpath+"/DtbUserWorkArea ] && mkdir "+instpath+"/DtbUserWorkArea\n");
    out << QString("cd "+instpath+"/Utils\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString(instpath+"/Qt/NOVAembed/NOVAembed_P_Parser/bin/Debug/NOVAembed_P_Parser "+instpath+"/DtbUserWorkArea/PClass_bspf/temp/"+SDL_FileNameNoExtension+".bspf > "+instpath+"/Logs/P_bspf.log\n");
        if ( ui->P_EditBeforeGenerate_checkBox->isChecked())
            out << QString(system_editor+" "+instpath+"/DtbUserWorkArea/"+SDL_FileNameNoExtension+".dtsi\n");
        out << QString("./user_dtb_compile "+SDL_FileNameNoExtension+" P >> "+instpath+"/Logs/P_bspf.log\n");
        out << QString(instpath+"/Qt/NOVAembed/NOVAembed_P_Parser/bin/Debug/NOVAembed_P_Parser "+instpath+"/DtbUserWorkArea/PClass_bspf/temp/"+QUAD_FileNameNoExtension+".bspf >> "+instpath+"/Logs/P_bspf.log\n");
        if ( ui->P_EditBeforeGenerate_checkBox->isChecked())
            out << QString(system_editor+" "+instpath+"/DtbUserWorkArea/"+QUAD_FileNameNoExtension+".dtsi\n");
        out << QString("./user_dtb_compile "+QUAD_FileNameNoExtension+" P >> "+instpath+"/Logs/P_bspf.log\n");
    }

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar(fi.baseName()+".dtb compiled, dtb is in "+instpath+"/DtbUserWorkArea folder as "+SDL_FileNameNoExtension+".dtb and "+QUAD_FileNameNoExtension+".dtb");
        const char *str;
        QByteArray ba;

        QString syscmd_quad = "cp "+instpath+"/DtbUserWorkArea/"+QUAD_FileNameNoExtension+".dtb "+instpath+"/Deploy/imx6q-novasomP.dtb ; chmod 777 "+instpath+"/Deploy/imx6q-novasomP.dtb";
        ba = syscmd_quad.toLatin1();
        str = ba.data();
        system(str);

        QString syscmd_sdl  = "cp "+instpath+"/DtbUserWorkArea/"+SDL_FileNameNoExtension+".dtb "+instpath+"/Deploy/imx6sdl-novasomP.dtb ; chmod 777 "+instpath+"/Deploy/imx6sdl-novasomP.dtb";
        ba = syscmd_sdl.toLatin1();
        str = ba.data();
        system(str);

        NOVAsom_Params_helper();
        storeNOVAembed_ini();
    }
    else
        update_status_bar("Error compiling "+fi.baseName()+".dtb");
}


void NOVAembed::on_ViewDtbCompileLog_pushButton_clicked()
{
   system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/P_bspf.log");
}


void NOVAembed::on_PrimaryVideo_comboBox_currentIndexChanged(const QString &arg1)
{
    if (( arg1 == "HDMI 1920x1080") || ( arg1 == "HDMI 1280x720"))
        ui->PriVideo_spwg_checkBox->setEnabled(false);
    else
        ui->PriVideo_spwg_checkBox->setEnabled(true);

}

/*****************************************************************************************************************************************************************************************/
/*                                                                             P BSP Factory END                                                                                         */
/*****************************************************************************************************************************************************************************************/

