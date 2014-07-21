#include "stdafx.h"
#include "Alert.h"
#include "AlertFactory.h"
#include "FileCompletedAlert.h"
#include "MetadataReceivedAlert.h"
#include "SaveResumeDataAlert.h"
#include "StateChangedAlert.h"
#include "StateUpdateAlert.h"
#include "StatsAlert.h"
#include "TorrentAddedAlert.h"
#include "TorrentFinishedAlert.h"
#include "TorrentPausedAlert.h"
#include "TorrentRemovedAlert.h"
#include "TorrentResumedAlert.h"
#include "TorrentCheckedAlert.h"

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

    bool AlertFactory::PeekWait(System::TimeSpan timeout)
    {
        libtorrent::alert const* a = this->_session.wait_for_alert(libtorrent::milliseconds(timeout.TotalMilliseconds));
        return a != 0;
    }

    Alert^ AlertFactory::GetAlert(std::auto_ptr<libtorrent::alert> alert)
    {
        switch (alert->type())
        {
        case libtorrent::file_completed_alert::alert_type:
            return gcnew FileCompletedAlert(static_cast<libtorrent::file_completed_alert*>(alert.get()));

        case libtorrent::metadata_received_alert::alert_type:
            return gcnew MetadataReceivedAlert(static_cast<libtorrent::metadata_received_alert*>(alert.get()));

        case libtorrent::save_resume_data_alert::alert_type:
            return gcnew SaveResumeDataAlert(static_cast<libtorrent::save_resume_data_alert*>(alert.get()));

        case libtorrent::state_changed_alert::alert_type:
            return gcnew StateChangedAlert(static_cast<libtorrent::state_changed_alert*>(alert.get()));

        case libtorrent::state_update_alert::alert_type:
            return gcnew StateUpdateAlert(static_cast<libtorrent::state_update_alert*>(alert.get()));

        case libtorrent::stats_alert::alert_type:
            return gcnew StatsAlert(static_cast<libtorrent::stats_alert*>(alert.get()));

        case libtorrent::torrent_added_alert::alert_type:
            return gcnew TorrentAddedAlert(static_cast<libtorrent::torrent_added_alert*>(alert.get()));

        case libtorrent::torrent_finished_alert::alert_type:
            return gcnew TorrentFinishedAlert(static_cast<libtorrent::torrent_finished_alert*>(alert.get()));

        case libtorrent::torrent_paused_alert::alert_type:
            return gcnew TorrentPausedAlert(static_cast<libtorrent::torrent_paused_alert*>(alert.get()));

        case libtorrent::torrent_removed_alert::alert_type:
            return gcnew TorrentRemovedAlert(static_cast<libtorrent::torrent_removed_alert*>(alert.get()));

        case libtorrent::torrent_resumed_alert::alert_type:
            return gcnew TorrentResumedAlert(static_cast<libtorrent::torrent_resumed_alert*>(alert.get()));

        case libtorrent::torrent_checked_alert::alert_type:
            return gcnew TorrentCheckedAlert(static_cast<libtorrent::torrent_checked_alert*>(alert.get()));
        }

        return nullptr;
    }
}
