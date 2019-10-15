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
#include <QNetworkInterface>
#include <QDialog>
#include <iostream>

extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString _Board_comboBox;
extern  QString Last_M7_BSPFactoryFile;
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
extern  QString instpath;
extern  QString system_editor;

extern  QString Last_P_FileSystem;
extern  QString Last_U_FileSystem;
extern  QString Last_N1_FileSystem;
extern  QString Last_M8_FileSystem;
extern  QString Last_M7_FileSystem;

extern  QWidget *PBSP_stab,*UBSP_stab,*SBSP_stab,*M8BSP_stab,*M9BSP_stab,*TOOL_stab;

extern QString BootValid , FSValid , KernelValid , uSDwriteValid;

extern  QString repo_server;
extern  QString backup_repo_server;

int initrd_size;

QWidget *current_stab;

/*****************************************************************************************************************************************************************************************/
/*                                                                               BKF Tab                                                                                                 */
/*****************************************************************************************************************************************************************************************/

void NOVAembed::initrd_helper(void)
{
    QFileInfo info1(instpath+"/FileSystem/"+FileSystemName+"/output/images/rootfs.ext2");

    initrd_size = ((info1.size() / 1024) * 1.1) + 20000; // Leave 20M of free space
/*
    std::cout << "\n" << FileSystemName.toLatin1().constData()<< "\n" << std::flush;
    std::cout << info1.size()<< "\n" << std::flush;
    std::cout << initrd_size << "\n" << std::flush;
*/
    ui->CurrentFS_lineEdit->setText( FileSystemName );
    ui->initRdSize_lineEdit->setText( QString::number(initrd_size) );
}

/* Write uSD frame enables */
void NOVAembed::uSD_Write_frame_enable()
{
    if (( KernelValid == "OK" ) && ( BootValid == "OK" ) && (FSValid == "OK"))
        ui->uSD_Write_frame->setEnabled(true);
    else
        ui->uSD_Write_frame->setEnabled(false);
    if ( ui->UserBSPFselectedlineEdit->text() == "Not Initialized")
        ui->Write_uSD_pushButton->setEnabled(false);
    else
        ui->Write_uSD_pushButton->setEnabled(true);
}

/* Bootloader */
void NOVAembed::on_BootLoaderCompile_pushButton_clicked()
{

    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        QString a=NXP_P_BOOTLOADER;
        update_status_bar("Cloning "+a+" boot loader for "+ui->Board_comboBox->currentText()+" ... ");
        system(instpath.toLatin1()+"/Utils/clone_singleboot "+NXP_P_BOOTLOADER+"_"+NOVAEMBED_VERSION+" "+NXP_P_BOOTLOADER);
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        QString a=NXP_U_BOOTLOADER;
        update_status_bar("Cloning "+a+" boot loader for "+ui->Board_comboBox->currentText()+" ... ");
        system(instpath.toLatin1()+"/Utils/clone_singleboot "+NXP_U_BOOTLOADER+"_"+NOVAEMBED_VERSION+" "+NXP_U_BOOTLOADER);
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        QString a=QUALCOMM_BOOTLOADER;
        update_status_bar("Cloning "+a+" boot loader for "+ui->Board_comboBox->currentText()+" ... ");
        system(instpath.toLatin1()+"/Utils/clone_singleboot "+QUALCOMM_BOOTLOADER+"_"+NOVAEMBED_VERSION+" "+QUALCOMM_BOOTLOADER);
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        QString a=RK_M7_BOOTLOADER;
        update_status_bar("Cloning "+a+" boot loader for "+ui->Board_comboBox->currentText()+" ... ");
        system(instpath.toLatin1()+"/Utils/clone_singleboot "+RK_M7_BOOTLOADER+"_"+NOVAEMBED_VERSION+" "+RK_M7_BOOTLOADER);
    }

    QFile scriptfile("/tmp/script");
    update_status_bar("Compiling boot loader for "+ui->Board_comboBox->currentText()+" ... ");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/bash\n");
    out << QString("cd "+instpath+"/Utils\n");
    out << QString(". ./version\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString("cd nxp\n");
        out << QString("./umakeP > "+instpath+"/Logs/umakeP.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        out << QString("cd nxp\n");
        out << QString("./umakeU > "+instpath+"/Logs/umakeU.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        out << QString("cd qcom\n");
        out << QString("./umakeM8 > "+instpath+"/Logs/umakeM8.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        out << QString("cd rock\n");
        out << QString("./umakeM7 > "+instpath+"/Logs/umakeM7.log\n");
    }

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("Boot loader for "+ui->Board_comboBox->currentText()+" compiled");
        BootValid = "OK";
        ui->BootStatus_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Error building boot loader for "+ui->Board_comboBox->currentText());
        BootValid = "INVALID";
        ui->BootStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    uSD_Write_frame_enable();
    storeNOVAembed_ini();
}

/* Kernel */
void NOVAembed::on_KernelXconfig_pushButton_clicked()
{
    if ( CheckIfKernelsPresent() == 1 )
        return;
    QFile scriptfile("/tmp/script");
    QString config_file;

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/Kernel/"+Kernel+"\n");
    out << QString(". ../../Utils/"+SourceMeFile+"\n");


    if ( ui->Board_comboBox->currentText() == "P Series")
        config_file = NXP_P_DEFCONFIG;
    if ( ui->Board_comboBox->currentText() == "U5")
        config_file = NXP_U_DEFCONFIG;
    if ( ui->Board_comboBox->currentText() == "M8")
        config_file = QUALCOMM_DEFCONFIG;
    if ( ui->Board_comboBox->currentText() == "M7")
        config_file = RK_M7_DEFCONFIG;

    if ( !QFile(instpath+"/Kernel/"+Kernel+"/.config").exists() )
    {
            out << QString("make "+config_file+"\n");
    }
    out << QString("make xconfig\n");
    out << QString("echo \"0\" > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("Kernel configuration done");
        KernelValid = "OK";
        if ( ui->Board_comboBox->currentText() == "P Series")
            if ( !QFile(instpath+"/Kernel/"+NXP_P_KERNEL_BIN).exists() )
                KernelValid = "INVALID";
        if ( ui->Board_comboBox->currentText() == "U5")
            if ( !QFile(instpath+"/Kernel/"+NXP_U_KERNEL_BIN).exists() )
                KernelValid = "INVALID";
        if ( ui->Board_comboBox->currentText() == "M8")
            if ( !QFile(instpath+"/Kernel/"+QUALCOMM_KERNEL_BIN).exists() )
                KernelValid = "INVALID";
        if ( ui->Board_comboBox->currentText() == "M7")
            if ( !QFile(instpath+"/Kernel/"+RK_M7_KERNEL_BIN).exists() )
                KernelValid = "INVALID";
        if ( KernelValid == "OK" )
        {
            ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/valid.png"));
            std::cout << "KernelValid\n" << std::flush;
        }
        else
        {
            ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
            std::cout << "KernelNotValid\n" << std::flush;
        }

    }
    else
    {
        update_status_bar("Configuration error");
        KernelValid = "INVALID";
        ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    uSD_Write_frame_enable();

    storeNOVAembed_ini();
}


void NOVAembed::on_KernelCompile_pushButton_clicked()
{
    if ( CheckIfKernelsPresent() == 1 )
        return;
    if ( !QFile(instpath+"/Kernel/"+Kernel+"/.config").exists() )
    {
        on_KernelReCompile_pushButton_clicked();
        return;
    }

    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    update_status_bar("Compiling "+Kernel);
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("echo \"Compiled on `date`\"> "+instpath+"/Logs/kmake.log\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm zImage ; ln -s ../Kernel/"+Kernel+"/arch/arm/boot/zImage\n");
        out << QString("cd "+instpath+"/Utils/nxp\n");
        out << QString("./kmake "+Kernel+" "+SourceMeFile+" >> "+instpath+"/Logs/kmake.log\n");
        QString this_kernel=NXP_P_KERNEL;
        out << QString("if [ -f ../../FileSystem/"+FileSystemName+"/output/images/rootfs.ext2.gz ]; then\n");
        out << QString("    if [ -f ../../Kernel/"+this_kernel+"/vmlinux ]; then\n");
        out << QString("        cd ../../Kernel/"+this_kernel+"\n");
        out << QString("        ./install_modules_local "+FileSystemName+" >> "+instpath+"/Logs/kmake.log\n");
        out << QString("    fi\n");
        out << QString("fi\n");
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm zImage ; ln -s ../Kernel/"+Kernel+"/arch/arm/boot/zImage\n");
        out << QString("cd "+instpath+"/Utils/nxp\n");
        out << QString("./kmake "+Kernel+" "+SourceMeFile+" >> "+instpath+"/Logs/kmake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm Image ; ln -s ../Kernel/"+Kernel+"/arch/arm64/boot/Image\n");
        out << QString("cd "+instpath+"/Utils/qcom\n");
        out << QString("./kmake "+Kernel+" "+SourceMeFile+" >> "+instpath+"/Logs/kmake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        out << QString("cd "+instpath+"/Utils/rock\n");
        out << QString("./kmake "+Kernel+" "+SourceMeFile+" >> "+instpath+"/Logs/kmake.log\n");
        if ( FileSystemName != "" )
        {
            out << QString("if [ -d "+instpath+"/FileSystem/"+FileSystemName+"/output/target ]; then\n");
            out << QString("    rm -rf "+instpath+"/FileSystem/"+FileSystemName+"/output/target/lib/modules/*\n");
            out << QString("    ./modules_install "+instpath+"/Kernel/"+Kernel+" "+instpath+"/FileSystem/"+FileSystemName+" "+SourceMeFile+" >> "+instpath+"/Logs/kmake.log\n");
            out << QString("    ./rebuild_fs "+instpath+"/FileSystem/"+FileSystemName+" >> "+instpath+"/Logs/kmake.log\n");
            out << QString("fi\n");
        }
        if ( ui->UserBSPFselectedlineEdit->text() != "Not Initialized" )
        {
            out << QString("if [ -f "+instpath+"/DtbUserWorkArea/"+ui->UserBSPFselectedlineEdit->text()+".dtb ]; then\n");
            out << QString("    rm -rf "+instpath+"/Deploy/m7_dtb.dtb\n");
            out << QString("    cp "+instpath+"/DtbUserWorkArea/"+ui->UserBSPFselectedlineEdit->text()+".dtb "+instpath+"/Deploy/m7_dtb.dtb\n");
            out << QString("fi\n");
        }
    }
    scriptfile.close();
    if ( run_script() == 0)
    {
        initrd_helper();
        update_status_bar("Kernel built succesfully");
        KernelValid = "OK";
        ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Kernel Build error");
        KernelValid = "INVALID";
        ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    uSD_Write_frame_enable();

    storeNOVAembed_ini();
}

void NOVAembed::on_KernelReCompile_pushButton_clicked()
{
    if ( CheckIfKernelsPresent() == 1 )
        return;
    QFile scriptfile("/tmp/script");
    QString config_file;
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    update_status_bar("ReCompiling "+Kernel);

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("echo \"Compiled on `date`\"> "+instpath+"/Logs/kmake.log\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm zImage ; ln -s ../Kernel/"+Kernel+"/arch/arm/boot/zImage\n");
        out << QString("cd "+instpath+"/Utils/nxp\n");
        config_file = "imx_novasomp_defconfig";
        out << QString("./kremake "+Kernel+" "+SourceMeFile+" "+config_file+" >> "+instpath+"/Logs/kremake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm zImage ; ln -s ../Kernel/"+Kernel+"/arch/arm/boot/zImage\n");
        out << QString("cd "+instpath+"/Utils/nxp\n");
        config_file = "imx_v7_defconfig";
        out << QString("./kremake "+Kernel+" "+SourceMeFile+" "+config_file+" >> "+instpath+"/Logs/kremake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm Image ; ln -s ../Kernel/"+Kernel+"/arch/arm64/boot/Image\n");
        out << QString("cd "+instpath+"/Utils/qcom\n");
        config_file = "qcom_defconfig";
        out << QString("./kremake "+Kernel+" "+SourceMeFile+" "+config_file+" >> "+instpath+"/Logs/kremake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        out << QString("cd "+instpath+"/Deploy\n");
        out << QString("rm Image ; ln -s ../Kernel/"+Kernel+"/arch/arm64/boot/Image\n");
        out << QString("cd "+instpath+"/Utils/rock\n");
        config_file = "NOVAsomM7_defconfig";
        out << QString("./kremake "+Kernel+" "+SourceMeFile+" "+config_file+" >> "+instpath+"/Logs/kremake.log\n");
        out << QString("if [ -d "+instpath+"/FileSystem/"+FileSystemName+"/output/target ]; then\n");
        out << QString("    rm -rf "+instpath+"/FileSystem/"+FileSystemName+"/output/target/lib/modules/*\n");
        out << QString("    ./modules_install "+instpath+"/Kernel/"+Kernel+" "+instpath+"/FileSystem/"+FileSystemName+" "+SourceMeFile+" >> "+instpath+"/Logs/kmake.log\n");
        out << QString("    ./rebuild_fs "+instpath+"/FileSystem/"+FileSystemName+" >> "+instpath+"/Logs/kmake.log\n");
        if ( ui->UserBSPFselectedlineEdit->text() != "" )
        {
            out << QString("    if [ -f "+instpath+"/DtbUserWorkArea/"+ui->UserBSPFselectedlineEdit->text()+".dtb ]; then\n");
            out << QString("        rm -rf "+instpath+"/Deploy/m7_dtb.dtb\n");
            out << QString("        cp "+instpath+"/DtbUserWorkArea/"+ui->UserBSPFselectedlineEdit->text()+".dtb "+instpath+"/Deploy/m7_dtb.dtb\n");
            out << QString("    fi\n");
        }
        out << QString("fi\n");
    }
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("Kernel re-built succesfully");
        ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/valid.png"));
        KernelValid = "OK";
    }
    else
    {
        update_status_bar("Kernel re-build error");
        ui->KernelStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
        KernelValid = "INVALID";
    }
    uSD_Write_frame_enable();

    storeNOVAembed_ini();
}

/* File System */
void NOVAembed::on_SelectFileSystem_pushButton_clicked()
{
    //QString directory =  QFileDialog::getOpenFileName(this,"Open File System",instpath+"/FileSystem/","*.*");
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),instpath+"/FileSystem/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QFileInfo fileInfo(directory );
    QString filesystemname(fileInfo.fileName());
    ui->FileSystemSelectedlineEdit->setText(filesystemname);
    FileSystemName = filesystemname;
    storeNOVAembed_ini();
}

void NOVAembed::on_LaunchMenuConfig_pushButton_clicked()
{
    if ( ui->FileSystemSelectedlineEdit->text() == "")
    {
       update_status_bar("File system name is empty");
       return;
    }
    update_status_bar("Configuring "+FileSystemName+" ...");
    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/FileSystem/"+FileSystemName+"\n");
    out << QString("make menuconfig\n");
    out << QString("echo \"0\" > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("Buildroot Configuration Finished");
        FSValid = "OK";
        ui->FileSystemStatus_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Configuration error");
        FSValid = "INVALID";
        ui->FileSystemStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    storeNOVAembed_ini();
}

void NOVAembed::on_LaunchBusyboxMenuConfig_pushButton_clicked()
{
    if ( ui->FileSystemSelectedlineEdit->text() == "")
    {
       update_status_bar("File system name is empty");
       return;
    }
    update_status_bar("Configuring "+FileSystemName+" ...");
    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/FileSystem/"+FileSystemName+"\n");
    out << QString("make busybox-menuconfig\n");
    out << QString("echo \"0\" > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Busybox Configuration Finished");
    else
        update_status_bar("Configuration error");
}

void NOVAembed::on_ThisIsReferenceServer_checkBox_clicked(bool checked)
{
    QString IP;

    ui->iperror_label->setVisible(false);

    if ( checked == false )
    {
        ui->REFERENCE_SERVER_label->setEnabled(true);
        ui->REFERENCE_SERVER_lineEdit->setEnabled(true);
        IP=ui->REFERENCE_SERVER_lineEdit->text();
    }
    else
    {
        ui->REFERENCE_SERVER_label->setEnabled(false);
        ui->REFERENCE_SERVER_lineEdit->setEnabled(false);
        QNetworkInterface eth1Ip = QNetworkInterface::interfaceFromName("enp0s3");
        QList<QNetworkAddressEntry> entries = eth1Ip.addressEntries();
        if (!entries.isEmpty()) {
            QNetworkAddressEntry entry = entries.first();
            IP=entry.ip().toString();
        }
    }
    ui->REFERENCE_SERVER_lineEdit->setText(IP);

}

void NOVAembed::on_UserAPPSelect_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select User app to store in target /bin"), instpath,tr("all (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFileInfo fileinfo(fileName);
        QFile scriptfile("/tmp/script");
        update_status_bar("Storing user app "+fileinfo.baseName()+" in "+instpath+"/FileSystem/"+FileSystemName+"/output/target/bin");
        ui->UserAPPselectedlineEdit->setText(fileinfo.baseName());

        if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            update_status_bar("Unable to create /tmp/script");
            return;
        }
        QTextStream out(&scriptfile);
        out << QString("#!/bin/sh\n");
        out << QString("cp "+fileinfo.absoluteFilePath()+" "+instpath+"/FileSystem/"+FileSystemName+"/output/target/bin/.\n");
        out << QString("echo \"0\" > /tmp/result\n");
        out << QString("echo \""+fileinfo.absoluteFilePath()+" stored succesfully\"\n");
        out << QString("exit 0");

        scriptfile.close();
        if ( run_script() == 0)
        {
            update_status_bar("User app "+fileinfo.baseName()+" successfully written to "+instpath+"/FileSystem/"+FileSystemName+"/output/target/bin");
            on_FileSystemDeploy_pushButton_clicked();
        }
        else
            update_status_bar("User app "+fileinfo.baseName()+" write failed to "+instpath+"/FileSystem/"+FileSystemName+"/output/target/bin");
    }
}

void NOVAembed::on_FileSystemDeploy_pushButton_clicked()
{
    if ( ui->FileSystemSelectedlineEdit->text().isEmpty())
    {
        update_status_bar("File system name is empty");
        return;
    }
    QHostAddress myIP;
    QString IP=ui->REFERENCE_SERVER_lineEdit->text();
    if( myIP.setAddress(ui->REFERENCE_SERVER_lineEdit->text()) )
    {
        ui->iperror_label->setVisible(false);
    }
    else
    {
        ui->iperror_label->setVisible(true);
        update_status_bar("Invalid IP address");
        return;
    }
    QFile scriptfile("/tmp/script");
    update_status_bar("Compiling "+ui->FileSystemSelectedlineEdit->text()+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString("cd "+instpath+"/Utils/nxp\n");
        out << QString("./MakeFs "+ui->FileSystemSelectedlineEdit->text()+" "+IP+" P > "+instpath+"/Logs/FileSystem_Pmake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        out << QString("cd "+instpath+"/Utils/nxp\n");
        out << QString("./MakeFs "+ui->FileSystemSelectedlineEdit->text()+" "+IP+" U > "+instpath+"/Logs/FileSystem_Umake.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        out << QString("cd "+instpath+"/Utils\n");
        out << QString("./MakeFs "+ui->FileSystemSelectedlineEdit->text()+" "+IP+" M8 > "+instpath+"/Logs/FileSystem_M8make.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        out << QString("cd "+instpath+"/Utils/rock\n");
        out << QString("./MakeFs "+ui->FileSystemSelectedlineEdit->text()+" "+IP+" "+Kernel+" > "+instpath+"/Logs/FileSystem_M7make.log\n");
    }
    out << QString("cp "+instpath+"/FileSystem/"+ui->FileSystemSelectedlineEdit->text()+"/.config "+instpath+"/Deploy/"+ui->FileSystemSelectedlineEdit->text()+".buildroot.config\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("File system "+ui->FileSystemSelectedlineEdit->text()+" deployed");
        DeployedFileSystemName = FileSystemName = ui->FileSystemSelectedlineEdit->text();
        FSValid = "OK";
        ui->FileSystemStatus_label->setPixmap(QPixmap(":/Icons/valid.png"));
        initrd_helper();
        if ( ui->Board_comboBox->currentText() == "P Series")
            Last_P_FileSystem = instpath+"/FileSystem/"+FileSystemName+"/output/images/uInitrd";
        if ( ui->Board_comboBox->currentText() == "U5")
            Last_U_FileSystem = instpath+"/FileSystem/"+FileSystemName+"/output/images/uInitrd";
        if ( ui->Board_comboBox->currentText() == "M8")
            Last_M8_FileSystem = instpath+"/FileSystem/"+FileSystemName+"/output/images/uInitrd";
        if ( ui->Board_comboBox->currentText() == "M7")
            Last_M7_FileSystem = instpath+"/FileSystem/"+FileSystemName+"/output/images/uInitrd";
    }
    else
    {
        update_status_bar("Build error");
        FSValid = "INVALID";
        ui->FileSystemStatus_label->setPixmap(QPixmap(":/Icons/invalid.png"));
        if ( ui->Board_comboBox->currentText() == "P Series")
            Last_P_FileSystem = "";
        if ( ui->Board_comboBox->currentText() == "U5")
            Last_U_FileSystem = "";
        if ( ui->Board_comboBox->currentText() == "M8")
            Last_M8_FileSystem = "";
        if ( ui->Board_comboBox->currentText() == "M7")
            Last_M7_FileSystem = "";
    }
    uSD_Write_frame_enable();

    storeNOVAembed_ini();
}


/* uSD write */

void NOVAembed::on_UserPartition_comboBox_currentIndexChanged(const QString &arg1)
{
    NumberOfUserPartitions = arg1;
    if ( NumberOfUserPartitions == "-")
    {
                ui->label_78->setVisible(false);
                ui->UserPartition1Size_lineEdit->setVisible(false);
                ui->label_79->setVisible(false);
                ui->UserPartition2Size_lineEdit->setVisible(false);

    }
    if ( NumberOfUserPartitions == "1")
    {
                ui->label_78->setVisible(true);
                ui->UserPartition1Size_lineEdit->setVisible(true);
                ui->label_79->setVisible(false);
                ui->UserPartition2Size_lineEdit->setVisible(false);
    }
    if ( NumberOfUserPartitions == "2")
    {
                ui->label_78->setVisible(true);
                ui->UserPartition1Size_lineEdit->setVisible(true);
                ui->label_79->setVisible(true);
                ui->UserPartition2Size_lineEdit->setVisible(true);
    }
    storeNOVAembed_ini();
}


void NOVAembed::on_UserPartition1Size_lineEdit_textChanged(const QString &arg1)
{
    UserPartition1Size = arg1;
    storeNOVAembed_ini();
}


void NOVAembed::on_UserPartition2Size_lineEdit_textChanged(const QString &arg1)
{
    UserPartition2Size = arg1;
    storeNOVAembed_ini();
}

void NOVAembed::on_uSD_Device_comboBox_currentIndexChanged(const QString &arg1)
{
    uSD_Device = arg1;
    storeNOVAembed_ini();
}

QString NOVAsomParamsName;
void NOVAembed::NOVAsom_Params_helper()
{
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        if ( ui->PrimaryVideo_comboBox->currentText() == "HDMI 1920x1080")
        {
            NOVAsomParamsName = "NOVAsomParams_P_HDMI_1920x1080";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "HDMI 1280x720" )
        {
            NOVAsomParamsName = "NOVAsomParams_P_HDMI_1280x720";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 1920x1080 2Ch")
        {
            NOVAsomParamsName = "NOVAsomParams_P_LVDS_1920x10802CH";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 1366x768")
        {
            NOVAsomParamsName = "NOVAsomParams_P_LVDS_1366x768";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 1280x800")
        {
            if ( ui->PriVideo_24bit_checkBox->isChecked() == true)
                NOVAsomParamsName = "NOVAsomParams_P_LVDS_1280x800_24";
            else
                NOVAsomParamsName = "NOVAsomParams_P_LVDS_1280x800_18";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 1024x768")
        {
            NOVAsomParamsName = "NOVAsomParams_P_LVDS_1024x768";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 1024x600")
        {
            NOVAsomParamsName = "NOVAsomParams_P_LVDS_1024x600";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 800x600")
        {
            NOVAsomParamsName = "NOVAsomParams_P_LVDS_800x600";
        }
        if ( ui->PrimaryVideo_comboBox->currentText() == "LVDS 800x480")
        {
            NOVAsomParamsName = "NOVAsomParams_P_LVDS_800x480";
        }
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        if ( ui->U_PrimaryVideo_comboBox->currentText() == "800x480")
        {
            NOVAsomParamsName = "NOVAsomParams_U5_800x480";
        }
        if ( ui->U_PrimaryVideo_comboBox->currentText() == "480x272")
        {
            NOVAsomParamsName = "NOVAsomParams_U5_480x272";
        }
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        NOVAsomParamsName = "NOVAsomParams_M7";
    }
}

void qSleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

void NOVAembed::on_Write_uSD_pushButton_clicked()
{
    /*uSD_Device_comboBox*/
    uSD_Device = ui->uSD_Device_comboBox->currentText();
    if ( check_uSD_present(uSD_Device) == 1)
        return;

    NumberOfUserPartitions = ui->UserPartition_comboBox->currentText();
    if ( ui->UserPartition_comboBox->currentText() == "2")
    {
        if ((UserPartition1Size == "0") && (UserPartition2Size == "0"))
            UserPartition1Size = "32";    /* If both are 0 set user1 for 32MB */
    }
    ui->UserPartition1Size_lineEdit->setText(UserPartition1Size);
    ui->UserPartition2Size_lineEdit->setText(UserPartition2Size);
    QFile scriptfile("/tmp/script");
    update_status_bar("Writing uSD with "+FileSystemName);

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }

    NOVAsom_Params_helper();


    QFileInfo fi(ui->UserBSPFselectedlineEdit->text());

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");


    if ( ui->Board_comboBox->currentText() == "U5")
    {
        out << QString("cd "+instpath+"/Utils/nxp\n");
        out << QString("./flashU "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" "+fi.baseName()+" "+NOVAsomParamsName+" "+ui->initRdSize_lineEdit->text()+" > "+instpath+"/Logs/uSD_Write.log\n");
        if ( ui->UserAutoRun_checkBox->isChecked())
            out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> "+instpath+"/Logs/uSD_Write.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString("cd "+instpath+"/Utils/nxp\n");
        out << QString("./flashP "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" "+"SDL_"+fi.baseName()+".dtb"+" "+"QUAD_"+fi.baseName()+".dtb"+" "+NOVAsomParamsName+" "+ui->initRdSize_lineEdit->text()+" > "+instpath+"/Logs/uSD_Write.log\n");
        if ( ui->UserAutoRun_checkBox->isChecked())
            out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> "+instpath+"/Logs/uSD_Write.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        out << QString("cd "+instpath+"/Utils/qcom\n");
        out << QString("./flashM8 /dev/"+uSD_Device+" > "+instpath+"/Logs/uSD_Write.log\n");
        if ( ui->UserAutoRun_checkBox->isChecked())
            out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> "+instpath+"/Logs/uSD_Write.log\n");
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        out << QString("cd "+instpath+"/Utils/rock\n");
        if ( ui->FileSystemOnSD_checkBox->isChecked() == true)
            out << QString("./flash_sd_M7 "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" "+fi.baseName()+" > "+instpath+"/Logs/uSD_Write.log\n");
        else
            out << QString("./flashM7 "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" "+fi.baseName()+" > "+instpath+"/Logs/uSD_Write.log\n");
        if ( ui->UserAutoRun_checkBox->isChecked())
            out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> "+instpath+"/Logs/uSD_Write.log\n");
    }
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("uSD successfully written, file system is "+FileSystemName);
        DeployedFileSystemName = FileSystemName;
        storeNOVAembed_ini();
    }
    else
        update_status_bar("Write error");
}

void NOVAembed::on_GenerateFileSystem_pushButton_clicked()
{
    if ( ui->NewFileSystemSelectedlineEdit->text().isEmpty())
    {
        update_status_bar("File System name can't be empty");
        return;
    }
    if ( QDir(instpath+"/FileSystem/"+ui->NewFileSystemSelectedlineEdit->text()).exists() )
    {
        update_status_bar("A file system called "+ui->NewFileSystemSelectedlineEdit->text()+" already exists");
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "A file system called "+ui->NewFileSystemSelectedlineEdit->text()+" already exists      ","Overwrite?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QDir dir( instpath+"/FileSystem/"+ui->NewFileSystemSelectedlineEdit->text() );
            dir.removeRecursively();
        }
        else
        {
            return;
        }
    }
    QString testing = ui->NewFileSystemSelectedlineEdit->text().remove(" ");
    if ( testing != ui->NewFileSystemSelectedlineEdit->text() )
    {
        update_status_bar("Spaces in File System name not allowed");
        return;
    }
    QFile scriptfile("/tmp/script");
    update_status_bar("Creating file system "+ui->NewFileSystemSelectedlineEdit->text()+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/Utils\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
        out << QString("./SetupFs "+ui->NewFileSystemSelectedlineEdit->text()+" P "+ ui->NewFileSystemConfigurationcomboBox->currentText()+"\n");
    else
        out << QString("./SetupFs "+ui->NewFileSystemSelectedlineEdit->text()+" \""+ui->Board_comboBox->currentText()+"\" "+ ui->NewFileSystemConfigurationcomboBox->currentText()+"\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("File System "+ui->NewFileSystemSelectedlineEdit->text()+" generated succesfully");
        DeployedFileSystemName = FileSystemName = ui->NewFileSystemSelectedlineEdit->text();
        ui->FileSystemSelectedlineEdit->setText(DeployedFileSystemName);
        storeNOVAembed_ini();
    }
    else
        update_status_bar("File System Creation error");
}

void NOVAembed::on_AddFileSystemConfig_pushButton_clicked()
{
    QString fileName;
    QString dest_file;

    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        fileName = QFileDialog::getSaveFileName(this,tr("Select .config"), instpath+"/Utils/Configurations/PClass_Buildroot_",tr(".config (PClass_*.config)"));
        dest_file = instpath+"/Utils/Configurations/PClass_Buildroot_";
    }
    if ( ui->Board_comboBox->currentText() == "U5")
    {
        fileName = QFileDialog::getSaveFileName(this,tr("Select .config"), instpath+"/Utils/Configurations/U5Class_Buildroot_",tr(".config (U5Class_*.config)"));
        dest_file = instpath+"/Utils/Configurations/U5Class_Buildroot_";
    }
    if ( ui->Board_comboBox->currentText() == "M8")
    {
        fileName = QFileDialog::getSaveFileName(this,tr("Select .config"), instpath+"/Utils/Configurations/M8Class_Buildroot_",tr(".config (M8Class_*.config)"));
        dest_file = instpath+"/Utils/Configurations/M8Class_Buildroot_";
    }
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        fileName = QFileDialog::getSaveFileName(this,tr("Select .config"), instpath+"/Utils/Configurations/M7Class_Buildroot_",tr(".config (M7Class_*.config)"));
        dest_file = instpath+"/Utils/Configurations/M7Class_Buildroot_";
    }
    if (fileName.isEmpty())
    {
        update_status_bar(fileName+" overwrite cancelled");
        return;
    }
    else
    {
        update_status_bar(fileName+" selected");
    }
    QFile::copy(instpath+"/FileSystem/"+ui->FileSystemSelectedlineEdit->text()+"/.config", fileName);
    QFile::copy(instpath+"/FileSystem/"+ui->FileSystemSelectedlineEdit->text()+"/BusyBox.config", instpath+"/Utils/Configurations/BusyBox_"+ui->FileSystemSelectedlineEdit->text()+".config");
    compile_NewFileSystemFileSystemConfigurationcomboBox();
}

extern      int skip_filesave_on_Generate_pushButton_clicked;
extern      QString FileNameIfSkipped;
extern      int generate_dtb_result;

void NOVAembed::on_UserBSPFSelect_pushButton_clicked()
{
    QString fileName;
    if ( ui->Board_comboBox->currentText() == "P Series")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/PClass_bspf",tr("BSPF (*.bspf)"));
    if ( ui->Board_comboBox->currentText() == "U5")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/UClass_bspf",tr("BSPF (*.bspf)"));
    if ( ui->Board_comboBox->currentText() == "M8")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/M8Class_bspf",tr("BSPF (*.bspf)"));
    if ( ui->Board_comboBox->currentText() == "M7")
    {
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/M7Class_bspf",tr("BSPF (*.bspf)"));
        std::cout << "fileName : " << fileName.toLatin1().constData() << "\n" << std::flush;
    }
    if (fileName.isEmpty())
        return;
    else
    {
        skip_filesave_on_Generate_pushButton_clicked = 1;
        FileNameIfSkipped = fileName;
        if ( ui->Board_comboBox->currentText() == "P Series")
        {
            ui->P_EditBeforeGenerate_checkBox->setChecked(false);
            on_P_Generate_pushButton_clicked();
        }
        if ( ui->Board_comboBox->currentText() == "U5")
        {
            ui->U_EditBeforeGenerate_checkBox->setChecked(false);
            on_U_Generate_pushButton_clicked();
        }
        if ( ui->Board_comboBox->currentText() == "M8")
        {
            ui->M8_EditBeforeGenerate_checkBox->setChecked(false);
            on_M8_Generate_pushButton_clicked();

        }
        if ( ui->Board_comboBox->currentText() == "M7")
        {
            ui->M7_EditBeforeGenerate_checkBox->setChecked(false);
            on_M7_Generate_pushButton_clicked();

        }
        skip_filesave_on_Generate_pushButton_clicked = 0;

        QFileInfo fileinfo(fileName);
        fileinfo.baseName();
        ui->UserBSPFselectedlineEdit->setText(fileinfo.baseName());
        if ( ui->Board_comboBox->currentText() == "M8")
            Last_M8_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        if ( ui->Board_comboBox->currentText() == "P Series")
            Last_P_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        if ( ui->Board_comboBox->currentText() == "U5")
            Last_U_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        if ( ui->Board_comboBox->currentText() == "M7")
            Last_M7_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        storeNOVAembed_ini();
        if (( KernelValid == "OK" ) && ( FSValid == "OK" ) && ( BootValid == "OK" ) && (generate_dtb_result == 0))
            uSD_Write_frame_enable();

    }
}

void NOVAembed::on_UserAutoRun_checkBox_toggled(bool checked)
{
    if ( checked == true)
    {
        AutoRunSelected = "true";
        ui->UserAutoRunSelect_pushButton->setEnabled(true);
        ui->UserAutoRunSelectedlineEdit->setEnabled(true);
        ui->UserAutoRunSelectedlineEdit->setText(AutoRunFolder);
        ui->Write_AutoRun_pushButton->setEnabled(true);
    }
    else
    {
        AutoRunSelected = "false";
        ui->UserAutoRunSelect_pushButton->setEnabled(false);
        ui->UserAutoRunSelectedlineEdit->setEnabled(false);
        ui->Write_AutoRun_pushButton->setEnabled(false);
    }
    storeNOVAembed_ini();
}

void NOVAembed::on_UserAutoRunSelect_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select the AutoRun folder"),instpath+"",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->UserAutoRunSelectedlineEdit->setText(directory);
    AutoRunFolder = directory;
    ui->Write_AutoRun_pushButton->setEnabled(true);
    storeNOVAembed_ini();
}

void NOVAembed::on_Write_AutoRun_pushButton_clicked()
{
    uSD_Device = ui->uSD_Device_comboBox->currentText();
    QFile scriptfile("/tmp/script");
    update_status_bar("Writing AutoRun using folder "+ui->UserAutoRunSelectedlineEdit->text()+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/Utils\n");
    if ( ui->Board_comboBox->currentText() == "M7")
        out << QString("cd rock\n");
    else if ( ui->Board_comboBox->currentText() == "M8")
        out << QString("cd qcom\n");
    else if ( ui->Board_comboBox->currentText() == "P Series")
        out << QString("cd nxp\n");
    else
        out << QString("cd nxp\n");
    out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> "+instpath+"/Logs/uSD_Write\n");

    scriptfile.close();

    if ( run_script() == 0)
    {
        update_status_bar("AutoRun successfully written with folder "+ui->UserAutoRunSelectedlineEdit->text());
    }
    else
        update_status_bar("AutoRun Write error");
}

void NOVAembed::on_ViewBootLog_pushButton_clicked()
{
    if ( ui->Board_comboBox->currentText() == "P Series")
        if ( QFile(instpath+"/Logs/umakeP.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/umakeP.log");
    if ( ui->Board_comboBox->currentText() == "U5")
        if ( QFile(instpath+"/Logs/umakeU.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/umakeU.log");
    if ( ui->Board_comboBox->currentText() == "M8")
        if ( QFile(instpath+"/Logs/umakeM8.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/umakeM8.log");
    if ( ui->Board_comboBox->currentText() == "M7" )
        if ( QFile(instpath+"/Logs/umakeM7.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/umakeM7.log");
}

void NOVAembed::on_ViewFSLog_pushButton_clicked()
{
    if ( ui->Board_comboBox->currentText() == "P Series")
        if ( QFile(instpath+"/Logs/FileSystem_Pmake.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/FileSystem_Pmake.log");
    if ( ui->Board_comboBox->currentText() == "U5")
        if ( QFile(instpath+"/Logs/FileSystem_Umake.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/FileSystem_Umake.log");
    if ( ui->Board_comboBox->currentText() == "M8")
        if ( QFile(instpath+"/Logs/FileSystem_M8make.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/FileSystem_M8make.log");
    if ( ui->Board_comboBox->currentText() == "M7")
        if ( QFile(instpath+"/Logs/FileSystem_M7make.log").exists() )
            system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/FileSystem_M7make.log");
}

void NOVAembed::on_ViewKernelLog_pushButton_clicked()
{
    if ( QFile(instpath+"/Logs/kmake.log").exists() )
        system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/kmake.log");
}



void NOVAembed::on_ViewuSDwriteLog_pushButton_clicked()
{
    if ( QFile(instpath+"/Logs/uSD_Write.log").exists() )
        system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/uSD_Write.log");
}



void NOVAembed::on_ViewPreCompiledLog_pushButton_clicked()
{
    if ( QFile(instpath+"/Logs/extfs.log").exists() )
        system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/extfs.log");
}





/*****************************************************************************************************************************************************************************************/
/*                                                                             BKF Tab END                                                                                               */
/*****************************************************************************************************************************************************************************************/
