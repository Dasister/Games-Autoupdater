#include "mainform.h"
#include "ui_mainform.h"
#include "aboutwindow.h"

#include <stdlib.h>
#include <string.h>
#include <QFileDialog>
#include <QDir>

using namespace libtorrent;

bool paused = true;

/* Torrent vars */
session s;
session_settings settings;

torrent_status state;

torrent_handle h;
error_code ec;

/* Torrent vars */

/* Var's */
int game;
/* Var's */
/* Enum's */

enum CurGame
{
    Game_Unknown = -1,
    Game_CSS,
    Game_DODS,
    Game_TF2,
};

/* Enum's */



MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    game = MainForm::Get_Game();
    switch (game)
    {
        case Game_DODS: ui->statusBar->showMessage("Day of Defeat: Source Found!"); break;
        default: ui->statusBar->showMessage("Game not found!"); break;
    }
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_StartBtn_clicked()
{
    if (paused)
    {
        QString fname = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Открыть"),
                         "C:/",
                         "TorrenFile (*.torrent)");

        s.listen_on(std::make_pair(6881, 6889), ec);
        if (ec)
        {
            ui->label->setText(QString::fromLocal8Bit(ec.message().c_str()));
            return;
        }
        add_torrent_params p;
        p.save_path = "./";
        p.ti = new torrent_info(fname.toStdString(), ec);
        if (ec)
        {
            ui->label->setText(QString::fromLocal8Bit(ec.message().c_str()));
            return;
        }
        h = s.add_torrent(p, ec);
        torrent_info info = h.get_torrent_info();
        size_type total_size = info.total_size();
        if (ec)
        {
             ui->label->setText(QString::fromLocal8Bit(ec.message().c_str()));
             return;
        }

        ui->label->setText("Downloading...");
        ui->StartBtn->setText("Pause");
        s.resume();
        paused = false;
        QString status_str;
        state = h.status();
        while (!paused && !state.is_finished)
        {
            state = h.status();
            state.total_download;

            if (state.state == torrent_status::checking_files)
            {
                status_str = "Checking...";
            }
            else
            {
                status_str.sprintf("Downloading... Download speed is %.2f KB/s. ", state.download_rate * 1.0 / 1024);
                status_str += GetSize(state.total_download, total_size);
            }
            ui->label->setText(status_str);
            ui->progressBar->setValue(state.progress_ppm / 10000.f);
            QApplication::processEvents();
        }
        ui->label->setText("Done!");
    }
    else
    {
        paused = true;
        ui->StartBtn->setText("Start");
        s.pause();
        ui->label->setText("Cancelled");
        QApplication::processEvents();
    }
}

/* Misc */

int MainForm::Get_Game()
{
    if (QDir("cstrike").exists())
        return Game_CSS;
    if (QDir("dod").exists())
        return Game_DODS;
    if (QDir("tf").exists())
        return Game_TF2;
    return Game_Unknown;
}

QString MainForm::GetSize(size_type total_download, size_type total_size)
{
    char *buf_str = new char [500];
    if ((float)((state.total_download * 1.0) / (1024 * 1024 * 1024)) < 1)
    {
        snprintf(buf_str, 499, "Downloaded %.2f MB from", state.total_download * 1.0 / (1024 * 1024));
    }
    else
        snprintf(buf_str, 499, "Downloaded %.2f GB from", state.total_download * 1.0 / (1024 * 1024 * 1024));
    if ((float)((total_size * 1.0) / (1024 * 1024 * 1024)) < 1)
    {
        snprintf(buf_str, 499, "%s %.2f MB", buf_str, total_size * 1.0 / (1024 * 1024));
    }
    else
        snprintf(buf_str, 499, "%s %.2f GB", buf_str, total_size * 1.0 / (1024 * 1024 * 1024));

    QString str = QString::fromAscii(buf_str);
    delete [] buf_str;
    return str;
}

/* Misc */

