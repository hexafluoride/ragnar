#include "stdafx.h"
#include "Collections\Vector.h"
#include "Interop\TorrentStatusValueConverter.h"
#include "StateUpdateAlert.h"
#include "TorrentStatus.h"

#include <libtorrent\alert_types.hpp>
#include <libtorrent\torrent_handle.hpp>

namespace Ragnar
{
    using namespace Ragnar::Collections;
    using namespace Ragnar::Interop;

    StateUpdateAlert::StateUpdateAlert(libtorrent::state_update_alert* alert)
        : TorrentAlert((libtorrent::torrent_alert*) alert)
    {
        this->_statuses = gcnew Vector<libtorrent::torrent_status, TorrentStatus^>(alert->status, gcnew TorrentStatusValueConverter());
    }
}
