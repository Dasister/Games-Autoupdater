#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QWidget {
    Q_OBJECT
    
public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();
    
private:
    Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
