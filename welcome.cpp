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
//#include <QHostInfo>
#include <QDirIterator>
#include <iostream>


extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString _Board_comboBox;
extern  QString Last_M8_BSPFactoryFile;
extern  QString Last_P_BSPFactoryFile;
extern  QString Last_U_BSPFactoryFile;
extern  QString NumberOfUserPartitions;
extern  QString UserPartition1Size;
extern  QString UserPartition2Size;
extern  QString uSD_Device;
extern  QString CurrentBSPF_Tab;
extern  QString CurrentPrimaryVideo;
extern  QString CurrentSecondaryVideo;
extern  QString AutoRunSelected;
extern  QString AutoRunFolder;
extern  QString Kernel;
extern  QString SourceMeFile;
extern  QWidget *PBSP_stab,*UBSP_stab,*SBSP_stab,*M8BSP_stab,*M7BSP_stab,*N1BSP_stab,*TOOL_stab;
extern  QString system_pdf_viewer;

extern QString BootValid , FSValid , KernelValid , uSDwriteValid;

extern int initrd_size;
extern  QString instpath;

extern QWidget *current_stab;
extern  QString AlreadyCompiled;

void NOVAembed::Board_comboBox_setText(const QString &arg1)
{
    ui->HUM_pushButton->setText(arg1+" Hardware User Manual");
}

void NOVAembed::on_Board_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( _Board_comboBox == arg1 )
        return;
    _Board_comboBox = arg1;
    AlreadyCompiled = "NO";

    Board_comboBox_setText(arg1);

    if ( _Board_comboBox == "U5")
    {
        CurrentBSPF_Tab = "U BSP Factory";
        Kernel=NXP_U_KERNEL;
        SourceMeFile=NXP_U_SOURCEME;
        current_stab = UBSP_stab;
        ui->brand_label->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
        ui->FileSystemSelectedlineEdit->setText("");
        ui->BoardNameBKF->setText(arg1);
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
    }
    if ( _Board_comboBox == "P Series")
    {
        CurrentBSPF_Tab = "P BSP Factory";
        Kernel=NXP_P_KERNEL;
        SourceMeFile=NXP_P_SOURCEME;
        current_stab = PBSP_stab;
        ui->brand_label->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
        ui->BoardNameBKF->setText(arg1);
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
        ui->FileSystemSelectedlineEdit->setText("");
        ui->UserBSPFSelect_pushButton->setVisible(true);
        ui->UserBSPFselectedlineEdit->setVisible(true);
    }
    if ( _Board_comboBox == "M8")
    {
        CurrentBSPF_Tab = "M8 BSP Factory";
        Kernel=QUALCOMM_KERNEL;
        SourceMeFile=QUALCOMM_SOURCEME;
        current_stab = M8BSP_stab;
        ui->brand_label->setPixmap(QPixmap(":/Icons/Qualcomm_Snapdragon_logo.png"));
        ui->BoardNameBKF->setText(arg1);
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/Qualcomm_Snapdragon_logo.png"));
        ui->FileSystemSelectedlineEdit->setText("");
        ui->UserBSPFSelect_pushButton->setVisible(true);
        ui->UserBSPFselectedlineEdit->setVisible(true);
    }
    if ( _Board_comboBox == "M7")
    {
        CurrentBSPF_Tab = "M7 BSP Factory";
        Kernel=RK_M7_KERNEL;
        current_stab = M7BSP_stab;
        SourceMeFile=RK_M7_SOURCEME;
        ui->brand_label->setPixmap(QPixmap(":/Icons/RockchipLogo.jpg"));
        ui->BoardNameBKF->setText(arg1);
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/RockchipLogo.jpg"));
        ui->FileSystemSelectedlineEdit->setText("");
        ui->UserBSPFSelect_pushButton->setVisible(true);
        ui->UserBSPFselectedlineEdit->setVisible(true);
    }
    /*
    ui->tab->removeTab(4);
    ui->tab->removeTab(3);
    */
    ui->tab->removeTab(2);
    ui->tab->insertTab(2,current_stab,CurrentBSPF_Tab);
    /*
    ui->tab->insertTab(3,TOOL_stab,"External File Systems");
    ui->tab->insertTab(4,TOOL_stab,"Tools");
    */

    compile_NewFileSystemFileSystemConfigurationcomboBox();
    compile_ExtFS_comboBox();
    storeNOVAembed_ini();
}

void NOVAembed::on_HUM_pushButton_clicked()
{
    QString syscmd,filename;

    if ( ui->Board_comboBox->currentText() == "P Series")
        filename = HUM_P;
    if ( ui->Board_comboBox->currentText() == "U5")
        filename = HUM_U5;
    if ( ui->Board_comboBox->currentText() == "M7")
        filename = HUM_M7;
    if ( ui->Board_comboBox->currentText() == "M8")
        filename = HUM_M8;
    syscmd = system_pdf_viewer+" "+instpath+"/Doc/"+filename;
    QByteArray ba = syscmd.toLatin1();
    const char *str = ba.data();
    system(str);
}

void NOVAembed::on_NovaEmbedM_pushButton_clicked()
{
    system(system_pdf_viewer.toLatin1()+" "+instpath.toLatin1()+"/Doc/SUM-NOVAembed-V1.0.pdf");
}

