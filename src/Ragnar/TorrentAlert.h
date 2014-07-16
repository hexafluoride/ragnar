#pragma once

#include <libtorrent\alert_types.hpp>
#include <libtorrent\torrent_handle.hpp>

#include "Alert.h"
#include "TorrentHandle.h"

namespace Ragnar
{
    public ref class TorrentAlert abstract : Alert
    {
    private:
        TorrentHandle^ _handle;

    internal:
        TorrentAlert(libtorrent::torrent_alert* alert);

    public:
        property TorrentHandle^ Handle { TorrentHandle^ get(); }
    };
}