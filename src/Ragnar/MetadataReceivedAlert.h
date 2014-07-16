#pragma once

#include <libtorrent\alert_types.hpp>
#include "TorrentAlert.h"

namespace Ragnar
{
    public ref class MetadataReceivedAlert : TorrentAlert
    {
    internal:
        MetadataReceivedAlert(libtorrent::metadata_received_alert* alert);
    };
}
