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

extern  QString instpath;

QString fileName1, fileName2;

void NOVAembed::on_CodeBlock_pushButton_clicked()
{
    system("codeblocks &");
}

void NOVAembed::on_Meld_pushButton_clicked()
{
    system("meld &");
}

void NOVAembed::on_QtCreator_pushButton_clicked()
{
    system("qtcreator &");

}

