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

#define     DEBUG_ON    1

#define MAXSRVIMAGES 32
QString imgFileName[MAXSRVIMAGES] , imgName[MAXSRVIMAGES] , imgVersion[MAXSRVIMAGES] , imgMinimumRequiredSD[MAXSRVIMAGES] , imgDescription[MAXSRVIMAGES] , imgFileSize[MAXSRVIMAGES];

void NOVAembed::ExtListHelper()
{
    QString currentboard;
    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";
    else
        currentboard=ui->Board_comboBox->currentText();

    ui->ExtFS_comboBox->clear();
    QStringList filters;
    QDir path(instpath+"/ExternalFileSystems/"+currentboard+"/");
    filters << "*.bz2";
    path.setNameFilters(filters);
    QStringList files = path.entryList(QDir::Files);
    ui->ExtFS_comboBox->addItems(files);
    ui->ExtFS_comboBox->setCurrentIndex(0);
}

void ServerimageFileHelper(QString distro_name)
{

    QSettings * configServerImages = 0;
    configServerImages = new QSettings( "/tmp/distros.cfg", QSettings::IniFormat );
    int i;
    QString strKeyLocalVersion(distro_name);
    QString fileNameAndIndex;
    imgFileName[0] = "";
    imgName[0] = "";
    imgFileName[0] = "";
    imgVersion[0] = "";
    imgMinimumRequiredSD[0] = "";
    imgDescription[0] = "No available images at the moment";
    imgFileSize[0] = "";
    for(i=0;i<MAXSRVIMAGES;i++)
    {
        fileNameAndIndex = "FileName"+QString::number(i);
        imgFileName[i] = configServerImages->value( strKeyLocalVersion + "FileName"+QString::number(i), "r").toString();
        std::cout << "FileName " << fileNameAndIndex.toLatin1().constData() << " : " << imgFileName[i].toLatin1().constData() << "\n" << std::flush;
        if ( imgFileName[i] == "r" )
            break;
        imgName[i] = configServerImages->value( strKeyLocalVersion + "Name"+QString::number(i), "r").toString();
        imgVersion[i] = configServerImages->value( strKeyLocalVersion + "Version"+QString::number(i), "r").toString();
        imgMinimumRequiredSD[i] = configServerImages->value( strKeyLocalVersion + "MinimumRequiredSD"+QString::number(i), "r").toString();
        imgDescription[i] = configServerImages->value( strKeyLocalVersion + "Description"+QString::number(i), "r").toString();
        imgFileSize[i] = configServerImages->value( strKeyLocalVersion + "FileSize"+QString::number(i), "r").toString();

    }
    #ifdef DEBUG_ON
    for(i=0;i<MAXSRVIMAGES;i++)
    {
        if ( imgFileName[i] == "r" )
            break;
        std::cout << "FileName " << i << " : " << imgFileName[i].toLatin1().constData() << "\n" << std::flush;
        std::cout << "Name " << i << " : " << imgName[i].toLatin1().constData() << "\n" << std::flush;
        std::cout << "Version " << i << " : " << imgVersion[i].toLatin1().constData() << "\n" << std::flush;
        std::cout << "MinimumRequiredSD " << i << " : " << imgMinimumRequiredSD[i].toLatin1().constData() << "\n" << std::flush;
        std::cout << "Description " << i << " : " << imgDescription[i].toLatin1().constData() << "\n" << std::flush;
        std::cout << "FileSize " << i << " : " << imgFileSize[i].toLatin1().constData() << "\n" << std::flush;
    }
    #endif
}

void NOVAembed::on_ExtFS_CheckAvailable_FS_pushButton_clicked()
{
QString currentboard;
QByteArray ba;
QString Qcmd;
QString ExternalFileSystemsFile;
int         i;
const char *cmd;

    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";
    else
        currentboard=ui->Board_comboBox->currentText();

    Qcmd = "rm /tmp/distros*.* ; cd /tmp; wget --tries=2 --timeout=10 http://"+repo_server+"/OS/distros.cfg";
    update_status_bar("Trying "+repo_server);
    ba = Qcmd.toLatin1();
    cmd = ba.data();
    system(cmd);

    update_status_bar("Downloading External File System List");

    ServerimageFileHelper("Distros "+currentboard+"/");

    update_status_bar("External File System List retrieved from "+repo_server);

    ui->ExtFS_Available_comboBox->clear();
    ui->ExtFS_Available_comboBox->setCurrentIndex(0);

    i = 0;
    ui->ExtFSName_lineEdit->clear();
    ui->ExtFSFileName_lineEdit->clear();
    ui->ExtFSVersion_lineEdit->clear();
    ui->ExtFSuSDsize_lineEdit->clear();
    ui->ExtFSBoard_lineEdit->clear();
    ui->ExtFSFileSize_lineEdit->clear();

    for(i=0;i<MAXSRVIMAGES;i++)
    {
        if ( imgFileName[i] == "r" )
        {
            imgFileName[i] = "";
            break;
        }
        ui->ExtFS_Available_comboBox->addItem(imgName[i]);
    }
    ui->ExtFS_Available_comboBox->setCurrentIndex(0);
    i = 0;

    ui->ExtFSName_lineEdit->setText(imgName[i]);
    ui->ExtFSFileName_lineEdit->setText(imgFileName[i]);
    ui->ExtFSVersion_lineEdit->setText(imgVersion[i]);
    ui->ExtFSuSDsize_lineEdit->setText(imgMinimumRequiredSD[i]);
    ui->ExtFSBoard_lineEdit->setText(imgDescription[i]);

    int num = imgFileSize[i].toInt();
    num /= (1024*1024);
    ui->ExtFSFileSize_lineEdit->setText(imgFileSize[i]);
    ui->MBytesLabel->setText(" bytes ("+QString::number(num)+" MB)");
}


void NOVAembed::on_ExtFS_Available_comboBox_currentIndexChanged(int index)
{
    std::cout << "index = " << index << "\n" << std::flush;
    if ( index >= 0 )
    {
        ui->ExtFSName_lineEdit->setText(imgName[index]);
        ui->ExtFSFileName_lineEdit->setText(imgFileName[index]);
        ui->ExtFSVersion_lineEdit->setText(imgVersion[index]);
        ui->ExtFSuSDsize_lineEdit->setText(imgMinimumRequiredSD[index]);
        ui->ExtFSBoard_lineEdit->setText(imgDescription[index]);
        int num = imgFileSize[index].toInt();
        num /= (1024*1024);
        ui->ExtFSFileSize_lineEdit->setText(imgFileSize[index] );
        ui->MBytesLabel->setText(" bytes ("+QString::number(num)+" MB)");
     }
}

void NOVAembed::on_ExtFS_DownloadSelected_FS_pushButton_clicked()
{

    QString force_yes="NO";

    QFile scriptfile("/tmp/script");
    QString currentboard=ui->Board_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";

    QString ExternalFileSystemsFile=instpath+"/ExternalFileSystems/"+currentboard+"/"+ui->ExtFSFileName_lineEdit->text();
    QFileInfo fi(ExternalFileSystemsFile);

    if (  fi.exists())
    {
        if ( fi.size() != ui->ExtFSFileSize_lineEdit->text().toInt())
        {
            std::cout << "fi.size() : " << fi.size() << " != " << ui->ExtFSFileName_lineEdit->text().toLatin1().constData() << " : " << ui->ExtFSFileSize_lineEdit->text().toInt() << "\n" << std::flush;
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning","A file system called\n"+ui->ExtFSFileName_lineEdit->text()+"\nalready exists but has different size,\n probably due to a partial download or a network error.\n\nPress \"Yes\" to download it again.", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
                force_yes = "YES";
            else
                return;
        }
        else
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Warning","A file system called\n"+ui->ExtFSFileName_lineEdit->text()+"\nalready exists and has the same size.\n\nReally do you want to download it again?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
                force_yes = "YES";
            else
                return;
        }
    }
    else
        force_yes="YES";

    if (force_yes == "YES")
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Message","About to download\n"+ui->ExtFSFileName_lineEdit->text()+"\nof "+ui->ExtFSFileSize_lineEdit->text()+" "+ui->MBytesLabel->text()+".\nAre you sure?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QFile fsfile( instpath+"/ExternalFileSystems/"+currentboard+"/"+ui->ExtFSFileName_lineEdit->text());
            fsfile.remove();
            update_status_bar(" Downloading "+ui->ExtFSFileName_lineEdit->text()+" from "+repo_server);
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
                update_status_bar("File System "+ui->ExtFSFileName_lineEdit->text()+" downloaded");
            }
            else
                update_status_bar("File System "+ui->ExtFSFileName_lineEdit->text()+" download error");
        }
        else
        {
            update_status_bar("Download cancelled");
            return;
        }
    }
    else
    {
        update_status_bar(ui->ExtFS_comboBox->currentText()+" Not downloaded");
        return;
    }
}

void NOVAembed::on_ExtFSBSPFSelect_pushButton_clicked()
{
    QString fileName;
    QString currentboard=ui->Board_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";

    fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), instpath+"/DtbUserWorkArea/"+currentboard+"Class_bspf",tr("BSPF (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFileInfo fileinfo(fileName);
        fileinfo.baseName();
        ui->ExtFSBSPFselectedlineEdit->setText(fileinfo.baseName());
    }
}

void NOVAembed::on_ExtFS_Write_uSD_pushButton_clicked()
{
    QString currentboard=ui->Board_comboBox->currentText();
    if ( ui->Board_comboBox->currentText() == "P Series")
        currentboard="P";

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

    full_path=instpath+"/ExternalFileSystems/"+currentboard+"/"+ui->ExtFS_comboBox->currentText();

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

/*
void NOVAembed::on_ExtFS_Available_comboBox_currentIndexChanged(const QString &arg1)
{
    return;
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
*/

/*
void NOVAembed::on_ExtFS_CheckAvailable_FS_pushButton_clickedOLD()
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
*/







/*****************************************************************************************************************************************************************************************/
/*                                                             External file systems Tab END                                                                                             */
/*****************************************************************************************************************************************************************************************/
