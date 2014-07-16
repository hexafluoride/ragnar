#include "stdafx.h"
#include "TorrentAlert.h"

namespace Ragnar
{
    TorrentAlert::TorrentAlert(libtorrent::torrent_alert* alert)
        : Alert((libtorrent::alert*) alert)
    {
        this->_handle = gcnew TorrentHandle(alert->handle);
    }

    TorrentHandle^ TorrentAlert::Handle::get()
    {
        return this->_handle;
    }
}
