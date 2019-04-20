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


extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString CfgBitDefaultValue;
extern  QString _Board_comboBox;
extern  QString Last_M8_BSPFactoryFile;
extern  QString LVDSVideo;
extern  QString Quad;
extern  QString instpath;

QString M9_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::M9_load_BSPF_File(QString fileName)
{
QString strKeyFunc("M8_IOMUX/");
QSettings * func_settings = 0;

    on_M8_Clear_pushButton_clicked();

    Last_M8_BSPFactoryFile = fileName;

    func_settings = new QSettings( fileName, QSettings::IniFormat );
}


void NOVAembed::M9_save_helper(QString fileName)
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
    Last_M8_BSPFactoryFile = fileName;
    storeNOVAembed_ini();

}

void NOVAembed::on_M9_Load_pushButton_clicked()
{

}


void NOVAembed::on_M9_Save_pushButton_clicked()
{

}
