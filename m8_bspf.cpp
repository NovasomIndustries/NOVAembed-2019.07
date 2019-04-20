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
extern  QString Last_M8_BSPFactoryFile;
extern  QString LVDSVideo;
extern  QString Quad;
extern  QString instpath;
extern  QString Kernel;
extern  QString system_editor;

QString M8_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::M8_load_BSPF_File(QString fileName)
{
    on_M8_Clear_pushButton_clicked();
    Last_M8_BSPFactoryFile = fileName+".bspf";
}


void NOVAembed::M8_save_helper(QString fileName)
{
    QFileInfo fin(fileName);
    QString bspfbase = fin.baseName();
    QString fullpathname = "";

    fullpathname = instpath+"/DtbUserWorkArea/M8Class_bspf/"+ bspfbase+".bspf";

    QFile file(fullpathname);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file "),file.errorString());
        return;
    }

    QTextStream out(&file);
    out << QString("[M8_IOMUX]\n");
    out << QString("\n[M8_CONF]\n");
    file.close();
    update_status_bar("File "+Last_M8_BSPFactoryFile+" saved");
    Last_M8_BSPFactoryFile = bspfbase;
    storeNOVAembed_ini();

}

void NOVAembed::on_M8_Save_pushButton_clicked()
{
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/M8Class_bspf",tr(".bspf (*.bspf)"));
        if ( fileName.isEmpty() )
            return;
        QFileInfo fi(fileName);
        ui->M8_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->M8_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        M8_save_helper(fileName);
}

extern      int skip_filesave_on_Generate_pushButton_clicked;

void NOVAembed::on_M8_Generate_pushButton_clicked()
{
QFile scriptfile("/tmp/script");
QString FileNameNoExtension;
QFileInfo fi;
    if ( CheckIfKernelsPresent() == 1 )
    {
        update_status_bar("Kernel "+Kernel+" not present, download it.");
        return;
    }
    if ( skip_filesave_on_Generate_pushButton_clicked == 0)
    {
        // Save .bspf and Generate .dtb
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), instpath+"/DtbUserWorkArea/M8Class_bspf",tr(".bspf (*.bspf)"));
        if ( fileName.isEmpty() )
            return;

        QFileInfo fiLocal(fileName);
        fi = fiLocal;
        ui->M8_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->M8_Generate_pushButton->setText("Save and Generate "+fi.baseName()+".dtb");
        M8_save_helper(fileName);
        Last_M8_BSPFactoryFile = fi.baseName();
        FileNameNoExtension  = fi.baseName();
    }

    update_status_bar("Generating dtb "+FileNameNoExtension+".dtb ...");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    if ( ui->M8_EditBeforeGenerate_checkBox->isChecked())
        update_status_bar("User editing dtsi file");

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("[ ! -d "+instpath+"/DtbUserWorkArea ] && mkdir "+instpath+"/DtbUserWorkArea\n");
    out << QString("cd "+instpath+"/Utils\n");
    out << QString(instpath+"/Qt/NOVAembed/NOVAembed_M8_Parser/bin/Debug/NOVAembed_M8_Parser "+instpath+"/DtbUserWorkArea/M8Class_bspf/"+FileNameNoExtension+".bspf > "+instpath+"/Logs/M8_bspf.log\n");
    if ( ui->M8_EditBeforeGenerate_checkBox->isChecked())
        out << QString(system_editor+" "+instpath+"/DtbUserWorkArea/"+FileNameNoExtension+".dts\n");
    out << QString("./user_dtb_compile "+FileNameNoExtension+" M8 >> "+instpath+"/Logs/M8_bspf.log\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar(fi.baseName()+".dtb compiled, dtb is in "+instpath+"/DtbUserWorkArea folder as "+FileNameNoExtension+".dtb");
        const char *str;
        QByteArray ba;

        QString syscmd_quad = "cp "+instpath+"/DtbUserWorkArea/"+FileNameNoExtension+".dtb "+instpath+"/Deploy/novasomm8.dtb ; chmod 777 "+instpath+"/Deploy/novasomm8.dtb";
        ba = syscmd_quad.toLatin1();
        str = ba.data();
        system(str);
        //NOVAsom_Params_helper();
    }
    else
        update_status_bar("Error compiling "+fi.baseName()+".dtb");
    storeNOVAembed_ini();
}

/*****************************************************************************************************************************************************************************************/
/*                                                                             M8 BSP Factory                                                                                             */
/*****************************************************************************************************************************************************************************************/



void NOVAembed::on_M8_SPI1_checkBox_toggled(bool checked)
{

}



void NOVAembed::on_M8_I2C2_checkBox_toggled(bool checked)
{

}



void NOVAembed::on_M8_UART2_checkBox_toggled(bool checked)
{

}


void NOVAembed::on_M8_UART2_4WirescheckBox_toggled(bool checked)
{

}



void NOVAembed::on_M8_PWM2_checkBox_toggled(bool checked)
{

}

void NOVAembed::on_M8_Clear_pushButton_clicked()
{
    on_M8_SPI1_checkBox_toggled(false);
    on_M8_I2C2_checkBox_toggled(false);
    on_M8_UART2_checkBox_toggled(false);
    on_M8_UART2_4WirescheckBox_toggled(false);
    on_M8_PWM2_checkBox_toggled(false);
    ui->M8_PrimaryVideo_24bit_comboBox->setChecked(false);
}


void NOVAembed::on_M8_Load_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), instpath+"/DtbUserWorkArea/M8Class_bspf",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        M8_load_BSPF_File(fileName);
        update_status_bar("File "+Last_M8_BSPFactoryFile+" loaded");
        QFileInfo fi(fileName);
        ui->M8_Current_BSPF_File_label->setText(fi.baseName()+".bspf");
        ui->M8_Generate_pushButton->setText("Save "+fi.baseName()+".bspf and Generate "+fi.baseName()+".dtb");
        Last_M8_BSPFactoryFile = fileName;
        storeNOVAembed_ini();
    }
}
