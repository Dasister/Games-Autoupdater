#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QIntValidator>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget {
    Q_OBJECT
    
public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

private slots:
    bool WriteSettings();
    bool ReadSettings();
    bool ParseBool(QString &value);
    
    void on_applySettings_clicked();

signals:
    void ApplySettings(const int, const int);

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
