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
#include <QMovie>
#include <iostream>


extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString CfgBitDefaultValue;
extern  QString _Board_comboBox;
extern  QString Last_M7_BSPFactoryFile;
extern  QString LVDSVideo;
extern  QString Quad;
extern  QString instpath;
extern  QString Kernel;
extern  QString system_editor;

QString M7_GPIO2_C1_comboBox="GPIO2_C1";
QString M7_GPIO0_A0_comboBox="GPIO0_A0";
QString M7_GPIO3_A4_comboBox="GPIO3_A4";    //UART1 TX
QString M7_GPIO2_C7_comboBox="GPIO2_C7";
QString M7_GPIO2_C4_comboBox="GPIO2_C4";
QString M7_GPIO2_C5_comboBox="GPIO2_C5";
QString M7_GPIO2_C0_comboBox="GPIO2_C0";
QString M7_GPIO2_C3_comboBox="GPIO2_C3";
QString M7_GPIO2_C6_comboBox="GPIO2_C6";
QString M7_GPIO2_B7_comboBox="GPIO2_B7";
QString M7_GPIO3_A6_comboBox="GPIO3_A6";    // UART1 RX
QString M7_GPIO3_A5_comboBox="GPIO3_A5";    // UART1 RTS
QString M7_GPIO3_A3_comboBox="GPIO3_A3";
QString M7_GPIO2_B4_comboBox="GPIO2_B4";
QString M7_GPIO3_B0_comboBox="GPIO3_B0";
QString M7_GPIO3_A1_comboBox="GPIO3_A1";
QString M7_GPIO3_A2_comboBox="GPIO3_A2";
QString M7_GPIO3_A0_comboBox="GPIO3_A0";
QString M7_GPIO2_D1_comboBox="GPIO2_D1";
QString M7_GPIO2_D0_comboBox="GPIO2_D0";
QString M7_GPIO3_A7_comboBox="GPIO3_A7";    // UART1 CTS

QString M7_I2C2Speed="100000";
QString M7_PrimaryVideo_comboBox;
QString M7_PrimaryVideo_24bit_comboBox;

QString M7_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::M7_load_BSPF_File(QString fileName)
{
QString strKeyFunc("M7_IOMUX/");
QSettings * func_settings = 0;

    std::cout << fileName.toLatin1().constData() << "\n" << std::flush;

    on_M7_Clear_pushButton_clicked();
    func_settings = new QSettings( fileName+".bspf", QSettings::IniFormat );
    if ( M7_getvalue(strKeyFunc, func_settings , "M7_GPIO3_A1_comboBox") == "SPI_TXD" )
    {
        on_M7_SPI1_checkBox_toggled(true);
        if ( M7_getvalue(strKeyFunc, func_settings , "M7_SPIdev_checkBox") == "false" )
            ui->M7_SPIdev_checkBox->setChecked(false);
        else
            ui->M7_SPIdev_checkBox->setChecked(true);
    }
    else
    {
        ui->M7_SPIdev_checkBox->setChecked(false);
        ui->M7_SPIdev_checkBox->setEnabled(false);
    }
    if ( M7_getvalue(strKeyFunc, func_settings , "M7_GPIO2_D1_comboBox") == "SDA" )
    {
        on_M7_I2C2_checkBox_toggled(true);
        QString speed = M7_getvalue(strKeyFunc, func_settings , "M7_I2C2Speed");
        std::cout << speed.toLatin1().constData() << "\n" << std::flush;

        ui->M7_I2C2Speed_lineEdit->setText(M7_getvalue(strKeyFunc, func_settings , "M7_I2C2Speed"));
    }
    if ( M7_getvalue(strKeyFunc, func_settings , "M7_GPIO3_A4_comboBox") == "UART1_TX" )
    {
        ui->M7_UART1_checkBox->setChecked(true);
        if ( M7_getvalue(strKeyFunc, func_settings , "M7_GPIO3_A5_comboBox") == "UART1_RTS" )
            ui->M7_UART1_4WirescheckBox->setChecked(true);
    }
    else
    {
        ui->M7_UART1_checkBox->setChecked(false);
        ui->M7_UART1_4WirescheckBox->setChecked(false);
    }
    if ( M7_getvalue(strKeyFunc, func_settings , "M7_PrimaryVideo_24bit_checkBox") == "true" )
        ui->M7_PrimaryVideo_24bit_checkBox->setChecked(true);
    ui->M7_PrimaryVideo_comboBox->setCurrentText(M7_getvalue(strKeyFunc, func_settings , "PrimaryVideo_comboBox"));
}


void NOVAembed::M7_save_helper(QString fileName)
{
    QFileInfo fin(fileName);
    QString bspfbase = fin.baseName();
    QString fullpathname = "";

    fullpathname = instpath+"/DtbUserWorkArea/M7Class_bspf/"+ bspfbase+".bspf";

    QFile file(fullpathname);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file "),file.errorString());
        return;
    }

    QTextStream out(&file);
    out << QString("[M7_IOMUX]\n");

    out << QString("M7_GPIO2_C1_comboBox="+M7_GPIO2_C1_comboBox+"\n");
    out << QString("M7_GPIO0_A0_comboBox="+M7_GPIO0_A0_comboBox+"\n");
    out << QString("M7_GPIO3_A4_comboBox="+M7_GPIO3_A4_comboBox+"\n");
    out << QString("M7_GPIO2_C7_comboBox="+M7_GPIO2_C7_comboBox+"\n");
    out << QString("M7_GPIO2_C4_comboBox="+M7_GPIO2_C4_comboBox+"\n");
    out << QString("M7_GPIO2_C5_comboBox="+M7_GPIO2_C5_comboBox+"\n");
    out << QString("M7_GPIO2_C0_comboBox="+M7_GPIO2_C0_comboBox+"\n");
    out << QString("M7_GPIO2_C3_comboBox="+M7_GPIO2_C3_comboBox+"\n");
    out << QString("M7_GPIO2_C6_comboBox="+M7_GPIO2_C6_comboBox+"\n");
    out << QString("M7_GPIO2_B7_comboBox="+M7_GPIO2_B7_comboBox+"\n");
    out << QString("M7_GPIO3_A6_comboBox="+M7_GPIO3_A6_comboBox+"\n");
    out << QString("M7_GPIO3_A5_comboBox="+M7_GPIO3_A5_comboBox+"\n");
    out << QString("M7_GPIO3_A3_comboBox="+M7_GPIO3_A3_comboBox+"\n");
    out << QString("M7_GPIO2_B4_comboBox="+M7_GPIO2_B4_comboBox+"\n");
    out << QString("M7_GPIO3_B0_comboBox="+M7_GPIO3_B0_comboBox+"\n");

    out << QString("M7_GPIO3_A1_comboBox="+M7_GPIO3_A1_comboBox+"\n");
    out << QString("M7_GPIO3_A2_comboBox="+M7_GPIO3_A2_comboBox+"\n");
    out << QString("M7_GPIO3_A0_comboBox="+M7_GPIO3_A0_comboBox+"\n");

    out << QString("M7_GPIO2_D1_comboBox="+M7_GPIO2_D1_comboBox+"\n");
    out << QString("M7_GPIO2_D0_comboBox="+M7_GPIO2_D0_comboBox+"\n");
    out << QString("M7_GPIO3_A7_comboBox="+M7_GPIO3_A7_comboBox+"\n");

    if ( ui->M7_I2C2Speed_lineEdit->text().isEmpty() )
        ui->M7_I2C2Speed_lineEdit->setText("100000");
    M7_I2C2Speed = ui->M7_I2C2Speed_lineEdit->text();
    out << QString("M7_I2C2Speed="+M7_I2C2Speed+"\n");

    if ( ui->M7_SPI1_checkBox->isChecked() )
    {
        if ( ui->M7_SPIdev_checkBox->isChecked() )
            out << QString("M7_SPIdev_checkBox=true\n");
        else
            out << QString("M7_SPIdev_checkBox=false\n");
    }
    else
        out << QString("M7_SPIdev_checkBox=false\n");
    out << QString("M7_PrimaryVideo_comboBox="+ui->M7_PrimaryVideo_comboBox->currentText()+"\n");
    if ( ui->M7_PrimaryVideo_24bit_checkBox->isChecked() )
        out << QString("M7_PrimaryVideo_24bit_checkBox=true\n");
    else
        out << QString("M7_PrimaryVideo_24bit_checkBox=false\n");


    out << QString("\n[M7_CONF]\n");
    file.close();
    update_status_bar("File "+Last_M7_BSPFactoryFile+" saved");
    Last_M7_BSPFactoryFile = bspfbase;
    storeNOVAembed_ini();
}

void NOVAembed::on_M7_Load_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), instpath+"/DtbUserWorkArea/M7Class_bspf",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        on_P_Clear_pushButton_clicked();
        M7_load_BSPF_File(fileName);
        update_status_bar("File "+Last_M7_BSPFactoryFile+" loaded");
        QFileInfo fi(fileName);
        ui->P_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->P_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    }
}


void NOVAembed::on_M7_Save_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/M7Class_bspf",tr(".bspf (*.bspf)"));
    if ( fileName.isEmpty() )
        return;
    QFileInfo fi(fileName);
    ui->M7_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
    ui->M7_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
    M7_save_helper(fileName);
}

extern      int skip_filesave_on_Generate_pushButton_clicked;

void NOVAembed::on_M7_Generate_pushButton_clicked()
{
QFile scriptfile("/tmp/script");
QString dtc_file;
QFileInfo fi;

    if ( CheckIfKernelsPresent() == 1 )
    {
        update_status_bar("Kernel "+Kernel+" not present, please download it.");
        return;
    }

    dtc_file= instpath+"/Kernel/"+Kernel.toLatin1()+"/scripts/dtc/dtc";
    QFile dtc_compiler(dtc_file);
    if ( ! dtc_compiler.exists() )
    {
        update_status_bar("dtc executable not present, probably "+Kernel+" has not yet compiled. Please compile it.");
        return;
    }
    if ( skip_filesave_on_Generate_pushButton_clicked == 0)
    {
        // Save .bspf and Generate .dtb
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/M7Class_bspf",tr(".bspf (*.bspf)"));
        if ( fileName.isEmpty() )
            return;
        QFileInfo fiLocal(fileName);
        fi = fiLocal;
        ui->M7_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->M7_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        M7_save_helper(fileName);
        Last_M7_BSPFactoryFile = fi.baseName();
    }
    update_status_bar("Generating dtb "+Last_M7_BSPFactoryFile+".dtb ...");
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
    out << QString("rm -f "+instpath+"/DtbUserWorkArea/m7_dtb.dtb\n");
    out << QString("cd "+instpath+"/Utils\n");
    out << QString(instpath+"/Qt/NOVAembed/NOVAembed_M7_Parser/bin/Debug/NOVAembed_M7_Parser "+instpath+"/DtbUserWorkArea/M7Class_bspf/"+Last_M7_BSPFactoryFile+".bspf > "+instpath+"/Logs/M7_bspf.log\n");
    if ( ui->M7_EditBeforeGenerate_checkBox->isChecked())
        out << QString(system_editor+" "+instpath+"/DtbUserWorkArea/"+Last_M7_BSPFactoryFile+".dts\n");
    out << QString("./user_dtb_compile "+Last_M7_BSPFactoryFile+" M7 >> "+instpath+"/Logs/M7_bspf.log\n");
    out << QString("if [ -f "+instpath+"/DtbUserWorkArea/"+Last_M7_BSPFactoryFile+".dtb ]; then\n");
    out << QString("    rm "+instpath+"/Deploy/m7_dtb.dtb\n");
    out << QString("    cp "+instpath+"/DtbUserWorkArea/"+Last_M7_BSPFactoryFile+".dtb "+instpath+"/Deploy/m7_dtb.dtb\n");
    out << QString("    echo 0 > /tmp/result\n");
    out << QString("else\n");
    out << QString("    echo 1 > /tmp/result\n");
    out << QString("fi\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar(fi.baseName()+".dtb compiled, dtb is in "+instpath+"/DtbUserWorkArea folder as "+Last_M7_BSPFactoryFile+".dtb");
        NOVAsom_Params_helper();
    }
    else
        update_status_bar("Error compiling "+fi.baseName()+".dtb");
}


void NOVAembed::on_M7_ViewDtbCompileLog_pushButton_clicked()
{
    system(system_editor.toLatin1()+" "+instpath.toLatin1()+"/Logs/M7_bspf.log");
}

void NOVAembed::on_M7_Clear_pushButton_clicked()
{
    M7_GPIO2_C1_comboBox="GPIO2_C1";
    M7_GPIO0_A0_comboBox="GPIO0_A0";
    M7_GPIO3_A4_comboBox="GPIO3_A4";
    M7_GPIO2_C7_comboBox="GPIO2_C7";
    M7_GPIO2_C4_comboBox="GPIO2_C4";
    M7_GPIO2_C5_comboBox="GPIO2_C5";
    M7_GPIO2_C0_comboBox="GPIO2_C0";
    M7_GPIO2_C3_comboBox="GPIO2_C3";
    M7_GPIO2_C6_comboBox="GPIO2_C6";
    M7_GPIO2_B7_comboBox="GPIO2_B7";
    M7_GPIO3_A6_comboBox="GPIO3_A6";
    M7_GPIO3_A5_comboBox="GPIO3_A5";
    M7_GPIO3_A3_comboBox="GPIO3_A3";
    M7_GPIO2_B4_comboBox="GPIO2_B4";
    M7_GPIO3_B0_comboBox="GPIO3_B0";
    M7_GPIO3_A1_comboBox="GPIO3_A1";
    M7_GPIO3_A2_comboBox="GPIO3_A2";
    M7_GPIO3_A0_comboBox="GPIO3_A0";
    M7_GPIO2_D1_comboBox="GPIO2_D1";
    M7_GPIO2_D0_comboBox="GPIO2_D0";
    M7_GPIO3_A7_comboBox="GPIO3_A7";

    ui->M7_SPI1_checkBox->setChecked(false);
    ui->M7_SPIdev_checkBox->setEnabled(false);
    ui->M7_SPIdev_checkBox->setChecked(false);
    ui->M7_I2C2_checkBox->setChecked(false);
    ui->M7_UART1_checkBox->setChecked(false);
    ui->M7_UART1_4WirescheckBox->setChecked(false);
    ui->M7_UART1_4WirescheckBox->setEnabled(false);
    ui->M7_PrimaryVideo_comboBox->setCurrentIndex(0);
    ui->M7_PrimaryVideo_24bit_checkBox->setChecked(false);
    ui->M7_I2C2Speed_lineEdit->setText("100000");

    ui->label_M7GPIO2_D1->setText(M7_GPIO2_D1_comboBox);
    ui->label_M7GPIO2_D0->setText(M7_GPIO2_D0_comboBox);
    ui->label_M7GPIO2_C1->setText(M7_GPIO2_C1_comboBox);
    ui->label_M7GPIO0_A0->setText(M7_GPIO0_A0_comboBox);
    ui->label_M7GPIO3_A4->setText(M7_GPIO3_A4_comboBox);
    ui->label_M7GPIO3_A1->setText(M7_GPIO3_A1_comboBox);
    ui->label_M7GPIO3_A2->setText(M7_GPIO3_A2_comboBox);
    ui->label_M7GPIO3_A0->setText(M7_GPIO3_A0_comboBox);

    ui->label_M7GPIO2_C7->setText(M7_GPIO2_C7_comboBox);
    ui->label_M7GPIO2_C4->setText(M7_GPIO2_C4_comboBox);
    ui->label_M7GPIO2_C5->setText(M7_GPIO2_C5_comboBox);

    ui->label_M7GPIO2_C0->setText(M7_GPIO2_C0_comboBox);
    ui->label_M7GPIO2_C3->setText(M7_GPIO2_C3_comboBox);
    ui->label_M7GPIO2_C6->setText(M7_GPIO2_C6_comboBox);

    ui->label_M7GPIO2_B7->setText(M7_GPIO2_B7_comboBox);
    ui->label_M7GPIO2_B4->setText(M7_GPIO2_B4_comboBox);
    ui->label_M7GPIO3_B0->setText(M7_GPIO3_B0_comboBox);

    ui->label_M7GPIO3_A7->setText(M7_GPIO3_A7_comboBox);
    ui->label_M7GPIO3_A6->setText(M7_GPIO3_A6_comboBox);
    ui->label_M7GPIO3_A5->setText(M7_GPIO3_A5_comboBox);
    ui->label_M7GPIO3_A3->setText(M7_GPIO3_A3_comboBox);

}



void NOVAembed::on_M7_SPI1_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M7_SPI1_checkBox->setChecked(true);
        ui->M7_SPIdev_checkBox->setEnabled(true);
        M7_GPIO3_A1_comboBox="SPI_TXD";
        M7_GPIO3_A2_comboBox="SPI_RXD";
        M7_GPIO3_A0_comboBox="SPI_CLK";
        M7_GPIO2_B4_comboBox="SPI_SS0";
        M7_GPIO3_B0_comboBox="SPI_SS1";
    }
    else
    {
        ui->M7_SPI1_checkBox->setChecked(false);
        ui->M7_SPIdev_checkBox->setEnabled(false);
        ui->M7_SPIdev_checkBox->setChecked(false);
        M7_GPIO3_A1_comboBox="GPIO3_A1";
        M7_GPIO3_A2_comboBox="GPIO3_A2";
        M7_GPIO3_A0_comboBox="GPIO3_A0";
        M7_GPIO2_B4_comboBox="GPIO2_B4";
        M7_GPIO3_B0_comboBox="GPIO3_B0";
    }
    ui->label_M7GPIO3_A1->setText(M7_GPIO3_A1_comboBox);
    ui->label_M7GPIO3_A2->setText(M7_GPIO3_A2_comboBox);
    ui->label_M7GPIO3_A0->setText(M7_GPIO3_A0_comboBox);
    ui->label_M7GPIO2_B4->setText(M7_GPIO2_B4_comboBox);
    ui->label_M7GPIO3_B0->setText(M7_GPIO3_B0_comboBox);
}

void NOVAembed::on_M7_I2C2_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M7_I2C2_checkBox->setChecked(true);
        ui->M7_I2C2Speed_lineEdit->setEnabled(true);
        M7_GPIO2_D1_comboBox="SDA";
        M7_GPIO2_D0_comboBox="SCL";
    }
    else
    {
        ui->M7_I2C2_checkBox->setChecked(false);
        ui->M7_I2C2Speed_lineEdit->setEnabled(false);
        M7_GPIO2_D1_comboBox="GPIO2_D1";
        M7_GPIO2_D0_comboBox="GPIO2_D0";
    }
    ui->label_M7GPIO2_D1->setText(M7_GPIO2_D1_comboBox);
    ui->label_M7GPIO2_D0->setText(M7_GPIO2_D0_comboBox);
}

void NOVAembed::on_M7_UART1_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M7_UART1_checkBox->setChecked(true);
        ui->M7_UART1_4WirescheckBox->setEnabled(true);
        M7_GPIO3_A4_comboBox="UART1_TX";
        M7_GPIO3_A6_comboBox="UART1_RX";
    }
    else
    {
        ui->M7_UART1_checkBox->setChecked(false);
        ui->M7_UART1_4WirescheckBox->setChecked(false);
        ui->M7_UART1_4WirescheckBox->setEnabled(false);
        M7_GPIO3_A4_comboBox="GPIO3_A4";
        M7_GPIO3_A6_comboBox="GPIO3_A6";
    }
    ui->label_M7GPIO3_A4->setText(M7_GPIO3_A4_comboBox);
    ui->label_M7GPIO3_A6->setText(M7_GPIO3_A6_comboBox);
}



void NOVAembed::on_M7_UART1_4WirescheckBox_toggled(bool checked)
{
    if ( checked )
    {
        ui->M7_UART1_4WirescheckBox->setChecked(true);
        M7_GPIO3_A5_comboBox="UART1_RTS";
        M7_GPIO3_A7_comboBox="UART1_CTS";
    }
    else
    {
        ui->M7_UART1_4WirescheckBox->setChecked(false);
        M7_GPIO3_A5_comboBox="GPIO3_A5";
        M7_GPIO3_A7_comboBox="GPIO3_A7";
    }
    ui->label_M7GPIO3_A5->setText(M7_GPIO3_A5_comboBox);
    ui->label_M7GPIO3_A7->setText(M7_GPIO3_A7_comboBox);
}
/*
QString M7_GPIO3_A4_comboBox="GPIO3_A4";    //UART1 TX
QString M7_GPIO3_A6_comboBox="GPIO3_A6";    // UART1 RX
QString M7_GPIO3_A5_comboBox="GPIO3_A5";    // UART1 RTS
QString M7_GPIO3_A7_comboBox="GPIO3_A7";    // UART1 CTS
*/
