#include "stdafx.h"
#include "TorrentAddedAlert.h"

namespace Ragnar
{
    TorrentAddedAlert::TorrentAddedAlert(libtorrent::torrent_added_alert* alert)
        : TorrentAlert((libtorrent::torrent_alert*) alert)
    {
    }
}