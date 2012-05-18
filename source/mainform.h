#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>

#include <stdlib.h>
#include <string.h>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "libtorrent/config.hpp"

#include <boost/bind.hpp>
#include <boost/unordered_set.hpp>

#include "libtorrent/extensions/metadata_transfer.hpp"
#include "libtorrent/extensions/ut_metadata.hpp"
#include "libtorrent/extensions/ut_pex.hpp"
#include "libtorrent/extensions/smart_ban.hpp"

#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
#include "libtorrent/session.hpp"
#include "libtorrent/identify_client.hpp"
#include "libtorrent/alert_types.hpp"
#include "libtorrent/ip_filter.hpp"
#include "libtorrent/magnet_uri.hpp"
#include "libtorrent/bitfield.hpp"
#include "libtorrent/file.hpp"
#include "libtorrent/peer_info.hpp"
#include "libtorrent/socket_io.hpp" // print_address
#include "libtorrent/time.hpp"
#include "libtorrent/create_torrent.hpp"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    
private slots:
    void on_StartBtn_clicked();

    int Get_Game();
    QString GetSize(libtorrent::size_type total_download, libtorrent::size_type total_size);


private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
