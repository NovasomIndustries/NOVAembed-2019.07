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
#include <QNetworkInterface>
#include <QDialog>
#include <iostream>

extern  QString instpath;
extern  QString repo_server;
extern  QString backup_repo_server;

/*****************************************************************************************************************************************************************************************/
/*                                                             External file systems Tab                                                                                                 */
/*****************************************************************************************************************************************************************************************/

QString extfsname;
QString extfsfilename;
QString extfsversion;
QString extfsboard;
QString minimumsdsize;
QString filesize;


void NOVAembed::ExtListHelper()
{
    QString full_board_path;

    ui->ExtFS_comboBox->clear();

    if ( ui->Board_comboBox->currentText() == "M7")
        full_board_path = instpath+"/ExternalFileSystems/M7/";
    if ( ui->Board_comboBox->currentText() == "M8")
        full_board_path = instpath+"/ExternalFileSystems/M8/";
    if ( ui->Board_comboBox->currentText() == "U")
        full_board_path = instpath+"/ExternalFileSystems/U/";
    if ( ui->Board_comboBox->currentText() == "P Class")
        full_board_path = instpath+"/ExternalFileSystems/P/";

    QStringList filters;
    QDir path(full_board_path);
    filters << "*.bz2";
    path.setNameFilters(filters);
    QStringList files = path.entryList(QDir::Files);
    ui->ExtFS_comboBox->addItems(files);
    ui->ExtFS_comboBox->setCurrentIndex(0);
}

void NOVAembed::on_ExtFS_CheckAvailable_FS_pushButton_clicked()
{
const char *cmd;
QByteArray ba;
QString currentboard=ui->Board_comboBox->currentText();
QString content;
QString ExternalFileSystemsFile;
QString Qcmd;
QString ShowName = "NotShown";

    ui->ExtFS_Available_comboBox->clear();
    ui->ExtFS_Available_comboBox->setCurrentIndex(0);

    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";

    update_status_bar("Downloading External File System List");

    Qcmd = "cd /tmp; rm nova_os*.* ;wget --tries=2 --timeout=10 http://"+repo_server+"/OS/"+currentboard+"/nova_os.txt";
    update_status_bar("Trying "+repo_server);
    ba = Qcmd.toLatin1();
    cmd = ba.data();
    system(cmd);

    QFile file("/tmp/nova_os.txt");
    if ( file.size() < 10 )
    {
        Qcmd = "cd /tmp; rm nova_os*.* ;wget --tries=2 --timeout=10 http://"+backup_repo_server+"/OS/"+currentboard+"/nova_os.txt";
        update_status_bar("Trying "+backup_repo_server);
        ba = Qcmd.toLatin1();
        cmd = ba.data();
        system(cmd);
        QFile file1("/tmp/nova_os.txt");
        if ( file1.size() < 10 )
        {
            update_status_bar("Failed to retrieve External File System List");
            return;
        }
        else
        {
            update_status_bar("External File System List retrieved from "+backup_repo_server);
        }
    }
    else
    {
        update_status_bar("External File System List retrieved from "+repo_server);
    }

    ui->ExtFS_comboBox->clear();
    ui->ExtFS_Available_comboBox->clear();
    ui->ExtFS_comboBox->setCurrentIndex(0);
    ui->ExtFS_Available_comboBox->setCurrentIndex(0);

    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            content = stream.readLine();
            if ( content.length() > 20 )
            {
                extfsfilename = content.split(" ").at(0);
                extfsname = content.split(" ").at(1);
                extfsboard = content.split(" ").at(2);
                extfsversion = content.split(" ").at(3);
                minimumsdsize = content.split(" ").at(4);
                ui->ExtFSuSDsize_lineEdit->setText(minimumsdsize);
                ui->ExtFSName_lineEdit->setText(extfsname);
                ui->ExtFSFileName_lineEdit->setText(extfsfilename);
                ui->ExtFSVersion_lineEdit->setText(extfsversion);
                ui->ExtFSBoard_lineEdit->setText(extfsboard);
                if ( ui->Board_comboBox->currentText() == "M8")
                    ExternalFileSystemsFile=instpath+"/ExternalFileSystems/M8/"+extfsfilename;
                if ( ui->Board_comboBox->currentText() == "M7")
                {
                    filesize = content.split(" ").at(5);
                    int num = filesize.toInt();
                    num /= (1024*1024);
                    QString size= filesize +" ("+QString::number(num)+" MB)";
                    ui->ExtFSFileSize_lineEdit->setText(size);
                    ExternalFileSystemsFile=instpath+"/ExternalFileSystems/M7/"+extfsfilename;
                }
                if ( ui->Board_comboBox->currentText() == "U5")
                    ExternalFileSystemsFile=instpath+"/ExternalFileSystems/U5/"+extfsfilename;
                if ( ui->Board_comboBox->currentText() == "P Series")
                    ExternalFileSystemsFile=instpath+"/ExternalFileSystems/P/"+extfsfilename;

                QFile scriptfile("/tmp/script");
                QTextStream out(&scriptfile);
                if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
                {
                    update_status_bar("Unable to create /tmp/script");
                    return;
                }
                out << QString("#!/bin/sh\n");
                out << QString("cd "+instpath+"/Utils\n");
                QString currentboard;
                currentboard = ui->Board_comboBox->currentText();
                if ( currentboard == "P Series")
                    currentboard="P";
                out << QString("./CheckExternalFS "+currentboard+" "+repo_server+" "+backup_repo_server+" "+extfsfilename+"\n");
                scriptfile.close();
                if ( run_script() == 0)
                {
                    ui->ExtFS_comboBox->addItem(extfsfilename);
                    update_status_bar("File System "+extfsfilename+" present");
                }
                else
                {
                    if ( ShowName == "NotShown")
                        ShowName = extfsname;
                    ui->ExtFS_Available_comboBox->addItem(extfsname);
                    on_ExtFS_Available_comboBox_currentIndexChanged(extfsname);
                    update_status_bar("File System "+extfsfilename+" to be downloaded");
                }
            }
        }
        file.close();
        ExtListHelper();

        if ( ShowName != "NotShown")
            on_ExtFS_Available_comboBox_currentIndexChanged(ShowName);
    }
}

void NOVAembed::on_ExtFS_Available_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->ExtFS_DownloadSelected_FS_pushButton->setText("Download "+ui->ExtFS_Available_comboBox->currentText());
    QFile file("/tmp/nova_os.txt");
    QString content;
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            content = stream.readLine();
            QString locextfsname = content.split(" ").at(1);
            if ( locextfsname == arg1)
            {
                extfsname = content.split(" ").at(1);
                extfsfilename = content.split(" ").at(0);
                extfsboard = content.split(" ").at(2);
                extfsversion = content.split(" ").at(3);
                minimumsdsize = content.split(" ").at(4);

                ui->ExtFSName_lineEdit->setText(extfsname);
                ui->ExtFSFileName_lineEdit->setText(extfsfilename);
                ui->ExtFSVersion_lineEdit->setText(extfsversion);
                ui->ExtFSBoard_lineEdit->setText(extfsboard);
                ui->ExtFSuSDsize_lineEdit->setText(minimumsdsize);

                if ( ui->Board_comboBox->currentText() == "M7")
                {
                    filesize = content.split(" ").at(5);
                    int num = filesize.toInt();
                    num /= (1024*1024);
                    QString size= filesize +" ("+QString::number(num)+" MB)";
                    ui->ExtFSFileSize_lineEdit->setText(size);
                }
                else
                    ui->ExtFSFileSize_lineEdit->setText("N/A");
            }
        }
        file.close();
    }
}

void NOVAembed::on_ExtFS_DownloadSelected_FS_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    QString currentboard=ui->Board_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/Utils\n");
    out << QString("./GetExternalFS "+currentboard+" "+repo_server+" "+backup_repo_server+" "+ui->ExtFSFileName_lineEdit->text()+"\n");
    scriptfile.close();
    if ( run_script() == 0)
    {
        ui->ExtFS_comboBox->addItem(ui->ExtFSFileName_lineEdit->text());
        update_status_bar("File System "+ui->ExtFS_Available_comboBox->currentText()+" downloaded");
    }
    else
        update_status_bar("File System "+ui->ExtFS_Available_comboBox->currentText()+" download error");
}

void NOVAembed::on_ExtFS_Write_uSD_pushButton_clicked()
{
    if ( ui->ExtFS_comboBox->currentText() == "" )
    {
        QMessageBox mb("Error",
            "Please select a file system to write.\nIf you don't have a file system download it first.",
            QMessageBox::NoIcon,
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::NoButton,
            QMessageBox::NoButton);
        mb.exec();
        return;
    }
    QString extfsuSD_Device = ui->ExtFS_uSD_Device_comboBox->currentText();
    if ( check_uSD_present(extfsuSD_Device) == 1 )
        return;

    QFile scriptfile("/tmp/script");
    QString full_path;
    QFileInfo fi(ui->ExtFSBSPFselectedlineEdit->text());

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    if ( ui->Board_comboBox->currentText() == "U5")
        full_path=instpath+"/ExternalFileSystems/U5/"+ui->ExtFS_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "M8")
        full_path=instpath+"/ExternalFileSystems/M8/"+ui->ExtFS_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "P Series")
        full_path=instpath+"/ExternalFileSystems/P/"+ui->ExtFS_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "M7")
        full_path=instpath+"/ExternalFileSystems/M7/"+ui->ExtFS_comboBox->currentText();

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd "+instpath+"/Utils\n");

    if ( ui->ExtFSBSPFselectedlineEdit->text() == "")
        out << QString("./flash_extfs /dev/"+ui->ExtFS_uSD_Device_comboBox->currentText()+"  "+full_path+" > "+instpath+"/Logs/extfs.log \n");
    else
    {
        if ( ui->Board_comboBox->currentText() == "P Series")
            out << QString("./flash_extfs /dev/"+ui->ExtFS_uSD_Device_comboBox->currentText()+" "+full_path+" "+"SDL_"+fi.baseName()+".dtb"+" "+"QUAD_"+fi.baseName()+".dtb"+" > "+instpath+"/Logs/extfs.log \n");
        else
            out << QString("./flash_extfs /dev/"+ui->ExtFS_uSD_Device_comboBox->currentText()+" "+full_path+" "+fi.baseName()+".dtb"+" > "+instpath+"/Logs/extfs.log \n");
    }
    scriptfile.close();
    update_status_bar("Writing image "+ui->ExtFS_comboBox->currentText()+" ...");
    if ( run_script() == 0)
    {
        update_status_bar("File System "+ui->ExtFS_comboBox->currentText()+" written");
    }
    else
        update_status_bar("File System Creation error");
}

void NOVAembed::on_ExtFSBSPFSelect_pushButton_clicked()
{
    QString fileName;

    if ( ui->Board_comboBox->currentText() == "P Series")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/PClass_bspf",tr("BSPF (*.bspf)"));
    if ( ui->Board_comboBox->currentText() == "U5")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/UClass_bspf",tr("BSPF (*.bspf)"));
    if ( ui->Board_comboBox->currentText() == "M8")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/M8Class_bspf",tr("BSPF (*.bspf)"));
    if ( ui->Board_comboBox->currentText() == "M7")
        fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/M7Class_bspf",tr("BSPF (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFileInfo fileinfo(fileName);
        fileinfo.baseName();
        ui->ExtFSBSPFselectedlineEdit->setText(fileinfo.baseName());
    }
}

void NOVAembed::on_ExtFS_RemoveFS_clicked()
{
    if ( ui->ExtFS_comboBox->currentText() == "" )
    {
        QMessageBox mb("Error",
            "Please select a file system to remove.",
            QMessageBox::NoIcon,
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::NoButton,
            QMessageBox::NoButton);
        mb.exec();
        return;
    }
    QMessageBox::StandardButton reply;
    update_status_bar("About to remove "+ui->ExtFS_comboBox->currentText()+" ...");
    QString currentboard=ui->Board_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";

    reply = QMessageBox::question(this, "Warning","A file system called\n"+ui->ExtFS_comboBox->currentText()+"\nalready exists.\n\nReally do you want to remove it?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QFile fsfile( instpath+"/ExternalFileSystems/"+currentboard+"/"+ui->ExtFS_comboBox->currentText() );
        fsfile.remove();
        update_status_bar(ui->ExtFS_comboBox->currentText()+" Removed");
        int index = ui->ExtFS_comboBox->currentIndex();
        ui->ExtFS_comboBox->removeItem(index);
    }
    else
    {
        update_status_bar(ui->ExtFS_comboBox->currentText()+" Not Removed");
        return;
    }

}

/*****************************************************************************************************************************************************************************************/
/*                                                             External file systems Tab END                                                                                             */
/*****************************************************************************************************************************************************************************************/
