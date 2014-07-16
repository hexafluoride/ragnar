#include "stdafx.h"
#include "Alert.h"
#include "AlertFactory.h"
#include "MetadataReceivedAlert.h"
#include "SaveResumeDataAlert.h"
#include "StateChangedAlert.h"
#include "TorrentAddedAlert.h"
#include "TorrentFinishedAlert.h"
#include "TorrentRemovedAlert.h"

#include <libtorrent\alert.hpp>
#include <libtorrent\alert_types.hpp>
#include <libtorrent\session.hpp>

namespace Ragnar
{
    AlertFactory::AlertFactory(libtorrent::session& session)
        : _session(session)
    {
    }

    Alert^ AlertFactory::Pop()
    {
        std::auto_ptr<libtorrent::alert> alert = this->_session.pop_alert();

        if (!alert.get())
        {
            return nullptr;
        }

        return this->GetAlert(alert);
    }

    System::Collections::Generic::IEnumerable<Alert^>^ AlertFactory::PopAll()
    {
        std::deque<libtorrent::alert*> alerts;
        this->_session.pop_alerts(&alerts);

        auto result = gcnew System::Collections::Generic::List<Alert^>();

        for (std::deque<libtorrent::alert*>::iterator i = alerts.begin(), end(alerts.end()); i != end; i++)
        {
            std::auto_ptr<libtorrent::alert> a(*i);

            if (!a.get())
            {
                continue;
            }

            auto alert = this->GetAlert(a);

            if (alert != nullptr)
            {
                result->Add(alert);
            }
        }

        return result;
    }

    Alert^ AlertFactory::GetAlert(std::auto_ptr<libtorrent::alert> alert)
    {
        switch (alert->type())
        {
        case libtorrent::metadata_received_alert::alert_type:
            return gcnew MetadataReceivedAlert((libtorrent::metadata_received_alert*) alert.get());

        case libtorrent::save_resume_data_alert::alert_type:
            return gcnew SaveResumeDataAlert((libtorrent::save_resume_data_alert*) alert.get());

        case libtorrent::state_changed_alert::alert_type:
            return gcnew StateChangedAlert((libtorrent::state_changed_alert*) alert.get());

        case libtorrent::torrent_added_alert::alert_type:
            return gcnew TorrentAddedAlert((libtorrent::torrent_added_alert*) alert.get());

        case libtorrent::torrent_finished_alert::alert_type:
            return gcnew TorrentFinishedAlert((libtorrent::torrent_finished_alert*) alert.get());

        case libtorrent::torrent_removed_alert::alert_type:
            return gcnew TorrentRemovedAlert((libtorrent::torrent_removed_alert*) alert.get());
        }

        return nullptr;
    }
}
