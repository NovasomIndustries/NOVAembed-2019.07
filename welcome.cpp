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

void NOVAembed::Board_comboBox_setText(const QString &arg1)
{
    ui->HUM_pushButton->setText(arg1+" Hardware User Manual");
}

void NOVAembed::on_Board_comboBox_currentIndexChanged(const QString &arg1)
{
int kernelok=0,bootok=0;
QFileInfo check_file1;
QString file_exists_path;
    if ( _Board_comboBox == arg1 )
        return;
    _Board_comboBox = arg1;
    file_exists_path = BLOBS_PATH;

    Board_comboBox_setText(arg1);

    if ( _Board_comboBox == "U5")
    {
        CurrentBSPF_Tab = "U BSP Factory";
        Kernel=NXP_U_KERNEL;
        current_stab = UBSP_stab;
        SourceMeFile=NXP_U_SOURCEME;
        check_file1 = QFileInfo(instpath+"/Blobs/"+NXP_U_BLOB_NAME);
        if (check_file1.exists() && check_file1.isFile())
            kernelok=1;
        else
            std::cout << "U5 kernel not found\n" << std::flush;
        check_file1 = QFileInfo(instpath+"/Blobs/u-uboot.imx");
        if (check_file1.exists() && check_file1.isFile())
            bootok=1;
        else
            std::cout << "U5 uboot not found\n" << std::flush;
        ui->brand_label->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
        ui->FileSystemSelectedlineEdit->setText("");
        ui->BoardNameBKF->setText(arg1);
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
    }
    if ( _Board_comboBox == "P Series")
    {
        ui->FileSystemSelectedlineEdit->setText("");
        Kernel=NXP_P_KERNEL;
        CurrentBSPF_Tab = "P BSP Factory";
        current_stab = PBSP_stab;
        ui->UserBSPFSelect_pushButton->setVisible(true);
        ui->UserBSPFselectedlineEdit->setVisible(true);
        SourceMeFile=NXP_P_SOURCEME;
        bootok=0;
        check_file1 = QFileInfo(instpath+"/Blobs/"+NXP_P_BLOB_NAME);
        if (check_file1.exists() && check_file1.isFile())
            kernelok=1;
        else
            std::cout << "P Series kernel not found\n" << std::flush;
        check_file1 = QFileInfo(instpath+"/Blobs/p-uboot.img");
        if (check_file1.exists() && check_file1.isFile())
            bootok++;
        else
            std::cout << "P Series uboot 0 not found\n" << std::flush;
        check_file1 = QFileInfo(instpath+"/Blobs/p-SPL");
        if (check_file1.exists() && check_file1.isFile())
            bootok++;
        else
            std::cout << "P Series uboot 1 not found\n" << std::flush;
        if ( bootok == 2)
            bootok=1;
        else
            bootok=0;
        ui->brand_label->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/NXP-Logo.png"));
        ui->BoardNameBKF->setText(arg1);
    }
    if ( _Board_comboBox == "M8")
    {
        ui->FileSystemSelectedlineEdit->setText("");
        Kernel=QUALCOMM_KERNEL;
        CurrentBSPF_Tab = "M8 BSP Factory";
        current_stab = M8BSP_stab;
        ui->UserBSPFSelect_pushButton->setVisible(true);
        ui->UserBSPFselectedlineEdit->setVisible(true);
        SourceMeFile=QUALCOMM_SOURCEME;
        file_exists_path += QUALCOMM_BLOB_NAME;
        check_file1 = QFileInfo(file_exists_path);
        if (check_file1.exists() && check_file1.isFile())
            kernelok=1;
        else
            std::cout << "M8 kernel not found\n" << std::flush;
        check_file1 = QFileInfo(instpath+"/Bootloader/u-boot-novasomM8-2017.11/u-boot.bin");
        if (check_file1.exists() && check_file1.isFile())
            bootok=1;
        else
            std::cout << "M8 uboot not found\n" << std::flush;
        ui->brand_label->setPixmap(QPixmap(":/Icons/Qualcomm_Snapdragon_logo.png"));
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/Qualcomm_Snapdragon_logo.png"));
        ui->BoardNameBKF->setText(arg1);
    }
    if ( _Board_comboBox == "M7")
    {
        ui->FileSystemSelectedlineEdit->setText("");
        Kernel=RK_M7_KERNEL;
        CurrentBSPF_Tab = "M7 BSP Factory";
        current_stab = M7BSP_stab;
        ui->UserBSPFSelect_pushButton->setVisible(true);
        ui->UserBSPFselectedlineEdit->setVisible(true);
        bootok=0;
        QString thepath;
        thepath=instpath+"/Kernel/"+RK_M7_KERNEL+"/arch/arm64/boot/Image";
        check_file1 = QFileInfo(thepath);
        if (check_file1.exists() && check_file1.isFile())
            kernelok=1;
        else
            std::cout << "welcome.cpp : M7 kernel not found : "<<thepath.toLatin1().constData() <<"\n" << std::flush;

        thepath=instpath+"/Bootloader/"+RK_M7_BOOTPATH+"/uboot.img";
        check_file1 = QFileInfo(thepath);
        if (check_file1.exists() && check_file1.isFile())
            bootok++;
        else
            std::cout << "welcome.cpp : M7 uboot not found : " << thepath.toLatin1().constData() <<"\n" << std::flush;
        thepath=instpath+"/Bootloader/"+RK_M7_BOOTPATH+"/trust.img";
        if (check_file1.exists() && check_file1.isFile())
            bootok++;
        else
            std::cout << "welcome.cpp : M7 trust not found : "<< thepath.toLatin1().constData() <<"\n" << std::flush;

        thepath=instpath+"/Bootloader/"+RK_M7_BOOTPATH+"/idbloader.img";
        if (check_file1.exists() && check_file1.isFile())
            bootok++;
        else
            std::cout << "welcome.cpp : M7 idbloader not found\n"<< thepath.toLatin1().constData() <<"\n" << std::flush;
        if ( bootok == 3)
            bootok=1;
        else
            bootok=0;
        ui->brand_label->setPixmap(QPixmap(":/Icons/RockchipLogo.jpg"));
        ui->BrandNameBKF->setPixmap(QPixmap(":/Icons/RockchipLogo.jpg"));
        ui->BoardNameBKF->setText(arg1);
    }
    /* hide Tools for recompose order, remind : N1 has no BSPF tab */
    ui->tab->removeTab(3);
    ui->tab->removeTab(2);
    ui->tab->insertTab(2,current_stab,CurrentBSPF_Tab);
    ui->tab->insertTab(3,TOOL_stab,"Tools");

    compile_NewFileSystemFileSystemConfigurationcomboBox();

    if ( bootok == 0 )
    {
        BootValid = "INVALID";
    }
    else
    {
        BootValid = "OK";
    }
    if ( kernelok == 0 )
    {
        KernelValid = "INVALID";
    }
    else
    {
        KernelValid = "OK";
    }
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

