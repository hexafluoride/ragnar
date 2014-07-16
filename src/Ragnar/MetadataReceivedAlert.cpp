#include "stdafx.h"
#include "MetadataReceivedAlert.h"

namespace Ragnar
{
    MetadataReceivedAlert::MetadataReceivedAlert(libtorrent::metadata_received_alert* alert)
        : TorrentAlert((libtorrent::torrent_alert*) alert)
    {
    }
}