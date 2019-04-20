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

extern  QString Last_U_BSPFactoryFile;
extern  QString Kernel;
extern  QString system_editor;

QString U_GPIO01_IO09_comboBox="GPIO01_IO09";
QString U_GPIO01_IO10_comboBox="GPIO01_IO10";
QString U_GPIO04_IO01_comboBox="GPIO04_IO01";
QString U_GPIO04_IO02_comboBox="GPIO04_IO02";
QString U_GPIO04_IO06_comboBox="GPIO04_IO06";
QString U_GPIO04_IO07_comboBox="GPIO04_IO07";
QString U_GPIO04_IO08_comboBox="GPIO04_IO08";
QString U_GPIO04_IO09_comboBox="GPIO04_IO09";
QString U_GPIO04_IO17_comboBox="GPIO04_IO17";
QString U_GPIO04_IO18_comboBox="GPIO04_IO18";
QString U_GPIO04_IO19_comboBox="GPIO04_IO19";
QString U_GPIO04_IO20_comboBox="GPIO04_IO20";
QString U_GPIO04_IO23_comboBox="GPIO04_IO23";
QString U_GPIO04_IO24_comboBox="GPIO04_IO24";
QString U_I2C2Speed="100000";
QString U_PrimaryVideo_comboBox;
extern  QString instpath;


QString U_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::U_load_BSPF_File(QString fileName)
{
QString strKeyFunc("U_IOMUX/");
QSettings * func_settings = 0;

    on_U_Clear_pushButton_clicked();
    func_settings = new QSettings( fileName+".bspf", QSettings::IniFormat );
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO04_IO06_comboBox") == "ECSPI4_SCLK" )
        on_U_SPI4_checkBox_toggled(true);
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO04_IO19_comboBox") == "I2C2_SDA" )
        on_U_I2C2_checkBox_toggled(true);
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO04_IO01_comboBox") == "CAN1_TX" )
        on_U_CAN1_checkBox_toggled(true);
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO04_IO17_comboBox") == "UART6_TX" )
        on_U_UART6_checkBox_toggled(true);
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO04_IO23_comboBox") == "UART5_RTS" )
        on_U_UART5_4WirescheckBox_toggled(true);
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO01_IO10_comboBox") == "SPDIF_OUT" )
        on_U_SPDIF_checkBox_toggled(true);
    if ( U_getvalue(strKeyFunc, func_settings , "U_GPIO01_IO09_comboBox") == "PWM2" )
        on_U_PWM2_checkBox_toggled(true);
    ui->U_SPIdev4_checkBox->setChecked(false);
    if ( U_getvalue(strKeyFunc, func_settings , "U_SPIdev4_checkBox") == "true" )
        ui->U_SPIdev4_checkBox->setChecked(true);



    ui->U_I2C2Speed_lineEdit->setText(U_getvalue(strKeyFunc, func_settings , "U_I2C2Speed"));
    ui->U_PrimaryVideo_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_PrimaryVideo_comboBox"));
    if ( U_getvalue(strKeyFunc, func_settings , "U_PrimaryVideo_24bit_comboBox") == "true")
        on_UPriVideo_24bit_checkBox_toggled(true);
}


void NOVAembed::U_save_helper(QString fileName)
{
    QFileInfo fin(fileName);
    QString bspfbase = fin.baseName();
    QString fullpathname = "";

    fullpathname = instpath+"/DtbUserWorkArea/UClass_bspf/"+ bspfbase+".bspf";

    QFile file(fullpathname);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file "),file.errorString());
        return;
    }

    QTextStream out(&file);
    out << QString("[U_IOMUX]\n");
    out << QString("U_GPIO01_IO09_comboBox="+U_GPIO01_IO09_comboBox+"\n");
    out << QString("U_GPIO01_IO10_comboBox="+U_GPIO01_IO10_comboBox+"\n");
    out << QString("U_GPIO04_IO01_comboBox="+U_GPIO04_IO01_comboBox+"\n");
    out << QString("U_GPIO04_IO02_comboBox="+U_GPIO04_IO02_comboBox+"\n");
    out << QString("U_GPIO04_IO06_comboBox="+U_GPIO04_IO06_comboBox+"\n");
    out << QString("U_GPIO04_IO07_comboBox="+U_GPIO04_IO07_comboBox+"\n");
    out << QString("U_GPIO04_IO08_comboBox="+U_GPIO04_IO08_comboBox+"\n");
    out << QString("U_GPIO04_IO09_comboBox="+U_GPIO04_IO09_comboBox+"\n");
    out << QString("U_GPIO04_IO17_comboBox="+U_GPIO04_IO17_comboBox+"\n");
    out << QString("U_GPIO04_IO18_comboBox="+U_GPIO04_IO18_comboBox+"\n");
    out << QString("U_GPIO04_IO19_comboBox="+U_GPIO04_IO19_comboBox+"\n");
    out << QString("U_GPIO04_IO20_comboBox="+U_GPIO04_IO20_comboBox+"\n");
    out << QString("U_GPIO04_IO23_comboBox="+U_GPIO04_IO23_comboBox+"\n");
    out << QString("U_GPIO04_IO24_comboBox="+U_GPIO04_IO24_comboBox+"\n");


    if ( ui->U_I2C2Speed_lineEdit->text().isEmpty() )
        ui->U_I2C2Speed_lineEdit->setText("100000");
    U_I2C2Speed = ui->U_I2C2Speed_lineEdit->text();
    out << QString("U_I2C2Speed="+U_I2C2Speed+"\n");


    if ( ui->U_SPIdev4_checkBox->isChecked() )
        out << QString("U_SPIdev4_checkBox=true\n");
    else
        out << QString("U_SPIdev4_checkBox=false\n");

    out << QString("U_PrimaryVideo_comboBox="+ui->U_PrimaryVideo_comboBox->currentText()+"\n");
    U_PrimaryVideo_comboBox   = ui->U_PrimaryVideo_comboBox->currentText();
    if ( ui->U_PrimaryVideo_24bit_comboBox->isChecked() )
        out << QString("U_PrimaryVideo_24bit_comboBox=true\n");
    else
        out << QString("U_PrimaryVideo_24bit_comboBox=false\n");

    out << QString("\n[U_CONF]\n");
    out << QString("U_GPIO01_IO09_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO01_IO10_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO01_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO02_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO06_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO07_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO08_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO09_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO17_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO18_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO19_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO20_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO23_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    out << QString("U_GPIO04_IO24_cbit="+ui->P_cbit_lineEdit->text()+"\n");
    file.close();
    update_status_bar("File "+Last_U_BSPFactoryFile+" saved");
    Last_U_BSPFactoryFile = bspfbase;
    storeNOVAembed_ini();

}

void NOVAembed::on_U_Clear_pushButton_clicked()
{
    on_U_SPI4_checkBox_toggled(false);
    on_U_I2C2_checkBox_toggled(false);
    on_U_CAN1_checkBox_toggled(false);
    on_U_UART6_checkBox_toggled(false);
    on_U_UART5_4WirescheckBox_toggled(false);
    on_U_SPDIF_checkBox_toggled(false);
    on_U_PWM2_checkBox_toggled(false);
    ui->U_PrimaryVideo_24bit_comboBox->setChecked(false);
}

void NOVAembed::on_U_SetCFGbits_pushButton_clicked()
{
}

void NOVAembed::on_U_SPI4_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO04_IO06->setText("ECSPI4_SCLK");
        ui->label_UGPIO04_IO07->setText("ECSPI4_MOSI");
        ui->label_UGPIO04_IO08->setText("ECSPI4_MISO");
        ui->label_UGPIO04_IO09->setText("ECSPI4_SS0");
        ui->U_SPIdev4_checkBox->setEnabled(true);
        U_GPIO04_IO06_comboBox="ECSPI4_SCLK";
        U_GPIO04_IO07_comboBox="ECSPI4_MOSI";
        U_GPIO04_IO08_comboBox="ECSPI4_MISO";
        U_GPIO04_IO09_comboBox="ECSPI4_SS0";
        ui->U_SPI4_checkBox->setChecked(true);
    }
    else
    {
        ui->U_SPI4_checkBox->setChecked(false);
        ui->label_UGPIO04_IO07->setText("GPIO04_IO07");
        ui->label_UGPIO04_IO08->setText("GPIO04_IO08");
        ui->label_UGPIO04_IO06->setText("GPIO04_IO06");
        ui->label_UGPIO04_IO09->setText("GPIO04_IO09");
        ui->U_SPIdev4_checkBox->setEnabled(false);
        U_GPIO04_IO06_comboBox="GPIO04_IO06";
        U_GPIO04_IO07_comboBox="GPIO04_IO07";
        U_GPIO04_IO08_comboBox="GPIO04_IO08";
        U_GPIO04_IO09_comboBox="GPIO04_IO09";
        ui->U_SPI4_checkBox->setChecked(false);
    }

}



void NOVAembed::on_U_I2C2_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO04_IO19->setText("I2C2_SDA");
        ui->label_UGPIO04_IO20->setText("I2C2_SCL");
        ui->U_I2C2Speed_lineEdit->setEnabled(true);
        U_GPIO04_IO19_comboBox="I2C2_SDA";
        U_GPIO04_IO20_comboBox="I2C2_SCL";
        ui->U_I2C2_checkBox->setChecked(true);

    }
    else
    {
        ui->U_I2C2_checkBox->setChecked(false);
        ui->label_UGPIO04_IO19->setText("GPIO04_IO19");
        ui->label_UGPIO04_IO20->setText("GPIO04_IO20");
        ui->U_I2C2Speed_lineEdit->setEnabled(false);
        U_GPIO04_IO19_comboBox="GPIO04_IO19";
        U_GPIO04_IO20_comboBox="GPIO04_IO20";
        ui->U_I2C2_checkBox->setChecked(false);

    }
}


void NOVAembed::on_U_CAN1_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO04_IO02->setText("CAN1_TX");
        ui->label_UGPIO04_IO02->setText("CAN1_RX");
        U_GPIO04_IO01_comboBox="CAN1_TX";
        U_GPIO04_IO02_comboBox="CAN1_RX";
        ui->U_CAN1_checkBox->setChecked(true);

    }
    else
    {
        ui->U_CAN1_checkBox->setChecked(false);
        ui->label_UGPIO04_IO02->setText("GPIO04_IO01");
        ui->label_UGPIO04_IO02->setText("GPIO04_IO02");
        U_GPIO04_IO01_comboBox="GPIO04_IO01";
        U_GPIO04_IO02_comboBox="GPIO04_IO02";
        ui->U_CAN1_checkBox->setChecked(false);
    }
}


void NOVAembed::on_U_UART6_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO04_IO17->setText("UART6_TX");
        ui->label_UGPIO04_IO18->setText("UART6_RX");
        U_GPIO04_IO17_comboBox="UART6_TX";
        U_GPIO04_IO18_comboBox="UART6_RX";
        ui->U_UART6_checkBox->setChecked(true);
    }
    else
    {
        ui->U_UART6_checkBox->setChecked(false);
        ui->label_UGPIO04_IO17->setText("GPIO04_IO17");
        ui->label_UGPIO04_IO18->setText("GPIO04_IO18");
        U_GPIO04_IO17_comboBox="GPIO04_IO17";
        U_GPIO04_IO18_comboBox="GPIO04_IO18";
        ui->U_UART6_checkBox->setChecked(false);
    }
}


void NOVAembed::on_U_UART5_4WirescheckBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO4_IO23->setText("UART5_RTS");
        ui->label_UGPIO4_IO24->setText("UART5_CTS");
        U_GPIO04_IO23_comboBox="UART5_RTS";
        U_GPIO04_IO24_comboBox="UART5_CTS";
        ui->U_UART6_checkBox->setChecked(true);

    }
    else
    {
        ui->U_UART6_4WirescheckBox->setChecked(false);
        ui->label_UGPIO4_IO23->setText("GPIO4_IO23");
        ui->label_UGPIO4_IO24->setText("GPIO4_IO24");
        U_GPIO04_IO23_comboBox="GPIO04_IO23";
        U_GPIO04_IO24_comboBox="GPIO04_IO24";
        ui->U_UART6_4WirescheckBox->setChecked(false);
    }
}

void NOVAembed::on_U_SPDIF_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO1_IO10->setText("SPDIF_OUT");
        U_GPIO01_IO10_comboBox="SPDIF_OUT";
        ui->U_SPDIF_checkBox->setChecked(true);
    }
    else
    {
        ui->U_SPDIF_checkBox->setChecked(false);
        ui->label_UGPIO1_IO10->setText("GPIO1_IO10");
        U_GPIO01_IO10_comboBox="GPIO01_IO10";
        ui->U_SPDIF_checkBox->setChecked(false);
    }
}


void NOVAembed::on_U_PWM2_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->label_UGPIO01_IO09->setText("PWM2");
        U_GPIO01_IO09_comboBox="PWM2";
        ui->U_PWM2_checkBox->setChecked(true);
    }
    else
    {
        ui->label_UGPIO01_IO09->setText("GPIO01_IO09");
        U_GPIO01_IO09_comboBox="GPIO01_IO09";
        ui->U_PWM2_checkBox->setChecked(false);
    }
}



void NOVAembed::on_UPriVideo_24bit_checkBox_toggled(bool checked)
{
    if ( checked )
        ui->U_PrimaryVideo_24bit_comboBox->setChecked(true);
    else
        ui->U_PrimaryVideo_24bit_comboBox->setChecked(false);
}



void NOVAembed::on_U_Load_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), instpath+"/DtbUserWorkArea/UClass_bspf",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        U_load_BSPF_File(fileName);
        update_status_bar("File "+Last_U_BSPFactoryFile+" loaded");
        QFileInfo fi(fileName);
        ui->U_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->U_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        Last_U_BSPFactoryFile = fi.baseName();
        storeNOVAembed_ini();
    }
}

void NOVAembed::on_U_Save_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/UClass_bspf",tr(".bspf (*.bspf)"));
    if ( fileName.isEmpty() )
        return;
    QFileInfo fi(fileName);
    ui->U_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
    ui->U_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    U_save_helper(fileName);
}

extern      int skip_filesave_on_Generate_pushButton_clicked;

void NOVAembed::on_U_Generate_pushButton_clicked()
{
QFile scriptfile("/tmp/script");
QFileInfo fi;

    if ( CheckIfKernelsPresent() == 1 )
    {
        update_status_bar("Kernel "+Kernel+" not present, download it.");
        return;
    }
    // Save .bspf and Generate .dtb
    if ( skip_filesave_on_Generate_pushButton_clicked == 0)
    {
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/UClass_bspf",tr(".bspf (*.bspf)"));
        if ( fileName.isEmpty() )
            return;

        QFileInfo fiLocal(fileName);
        fi = fiLocal;
        ui->U_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->U_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        U_save_helper(fileName);
        Last_U_BSPFactoryFile = fi.baseName();
    }

    update_status_bar("Generating dtb "+Last_U_BSPFactoryFile+".dtb ...");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    if ( ui->U_EditBeforeGenerate_checkBox->isChecked())
        update_status_bar("User editing dtsi file");

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("[ ! -d "+instpath+"/DtbUserWorkArea ] && mkdir "+instpath+"/DtbUserWorkArea\n");
    out << QString("cd "+instpath+"/Utils\n");
    out << QString(instpath+"/Qt/NOVAembed/NOVAembed_U_Parser/bin/Debug/NOVAembed_U_Parser "+instpath+"/DtbUserWorkArea/UClass_bspf/"+Last_U_BSPFactoryFile+".bspf > "+instpath+"/Logs/U_bspf.log\n");
    if ( ui->U_EditBeforeGenerate_checkBox->isChecked())
        out << QString(system_editor+" "+instpath+"/DtbUserWorkArea/"+Last_U_BSPFactoryFile+".dts\n");
    out << QString("./user_dtb_compile "+Last_U_BSPFactoryFile+" U >> "+instpath+"/Logs/U_bspf.log\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar(fi.baseName()+".dtb compiled, dtb is in "+instpath+"/DtbUserWorkArea folder as "+Last_U_BSPFactoryFile+".dtb");
        const char *str;
        QByteArray ba;

        QString syscmd_quad = "cp "+instpath+"/DtbUserWorkArea/"+Last_U_BSPFactoryFile+".dtb "+instpath+"/Deploy/novasomu.dtb ; chmod 777 "+instpath+"/Deploy/novasomu.dtb";
        ba = syscmd_quad.toLatin1();
        str = ba.data();
        system(str);
        NOVAsom_Params_helper();
    }
    else
        update_status_bar("Error compiling "+fi.baseName()+".dtb");
}

void NOVAembed::on_U_ViewDtbCompileLog_pushButton_clicked()
{
    system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/U_bspf.log");
}
