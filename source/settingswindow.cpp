#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "mainform.h"
#include <QMessageBox>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow) {
    ui->setupUi(this);

    QIntValidator* inVal = new QIntValidator(this);
    inVal->setBottom(0);

    ui->downloadLimitVal->setValidator(inVal);
    ui->uploadLimitVal->setValidator(inVal);
    if (!QFile("./updater.xml").exists())
    {
        WriteSettings();
    }
    else
        ReadSettings();
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}

bool SettingsWindow::WriteSettings() {
    QFile file("./updater.xml");
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QXmlStreamWriter *xml = new QXmlStreamWriter();
    xml->setDevice(&file);

    xml->setAutoFormatting(true);
    xml->writeStartDocument();
    xml->writeStartElement("options");
    xml->writeTextElement("continueseeding", ui->KeepSeeding->isChecked()? "yes": "no");
    xml->writeTextElement("limitdownload", ui->LimitDownload->isChecked()? "yes": "no");
    xml->writeTextElement("limitdownload_val", ui->downloadLimitVal->text());
    xml->writeTextElement("limitupload", ui->LimitUpload->isChecked()? "yes": "no");
    xml->writeTextElement("limitupload_val", ui->uploadLimitVal->text());
    xml->writeEndElement();
    xml->writeEndDocument();

    delete xml;

    file.close();

    return true;
}

bool SettingsWindow::ReadSettings() {
    QFile file("./updater.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QXmlStreamReader *xml = new QXmlStreamReader();
    xml->setDevice(&file);

    while (!xml->atEnd())
    {
        QXmlStreamReader::TokenType token = xml->readNext();


        if(token == QXmlStreamReader::StartElement)
        {
            if (xml->name() == "continueseeding")
            {
                ui->KeepSeeding->setChecked(ParseBool(xml->readElementText()));
            }
            if (xml->name() == "limitdownload")
            {
                ui->LimitDownload->setChecked(ParseBool(xml->readElementText()));
            }
            if (xml->name() == "limitdownload_val")
            {
                ui->downloadLimitVal->setText(xml->readElementText());
            }
            if (xml->name() == "limitupload")
            {
                ui->LimitUpload->setChecked(ParseBool(xml->readElementText()));
            }
            if (xml->name() == "limitupload_val")
            {
                ui->uploadLimitVal->setText(xml->readElementText());
            }
        }
    }

    delete xml;
    file.close();

    return true;
}

bool SettingsWindow::ParseBool(QString &value) {
    return value == "yes"? true: false;
}

void SettingsWindow::on_applySettings_clicked() {
    WriteSettings();
    emit ApplySettings(ui->LimitDownload->isChecked()? ui->downloadLimitVal->text().toInt(): 0, ui->LimitUpload->isChecked()? ui->uploadLimitVal->text().toInt(): 0);
    SettingsWindow::hide();
}
