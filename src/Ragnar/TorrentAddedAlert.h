#pragma once

#include <libtorrent\alert_types.hpp>
#include "TorrentAlert.h"

namespace Ragnar
{
    public ref class TorrentAddedAlert : TorrentAlert
    {
    internal:
        TorrentAddedAlert(libtorrent::torrent_added_alert* alert);
    };
}
