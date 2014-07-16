#include "stdafx.h"
#include "TorrentHandle.h"
#include "Utils.h"

namespace Ragnar
{
    TorrentHandle::TorrentHandle(const libtorrent::torrent_handle &handle)
    {
        this->_handle = new libtorrent::torrent_handle(handle);
    }

    TorrentHandle::~TorrentHandle()
    {
        delete this->_handle;
    }

    System::String^ TorrentHandle::InfoHash::get()
    {
        return gcnew String(libtorrent::to_hex(this->_handle->info_hash().to_string()).c_str());
    }

    TorrentStatus^ TorrentHandle::QueryStatus()
    {
        return gcnew TorrentStatus(this->_handle->status());
    }

    void TorrentHandle::SetPriority(int priority)
    {
        this->_handle->set_priority(priority);
    }

    void TorrentHandle::ClearError()
    {
        this->_handle->clear_error();
    }

    void TorrentHandle::Pause()
    {
        this->_handle->pause();
    }

    void TorrentHandle::Resume()
    {
        this->_handle->resume();
    }

    void TorrentHandle::SetUploadMode(bool value)
    {
        this->_handle->set_upload_mode(value);
    }

    void TorrentHandle::SetShareMode(bool value)
    {
        this->_handle->set_share_mode(value);
    }

    void TorrentHandle::FlushCache()
    {
        this->_handle->flush_cache();
    }

    void TorrentHandle::ApplyIPFilter(bool value)
    {
        this->_handle->apply_ip_filter(value);
    }

    void TorrentHandle::ForceRecheck()
    {
        this->_handle->force_recheck();
    }

    void TorrentHandle::SaveResumeData()
    {
        this->_handle->save_resume_data();
    }

    bool TorrentHandle::NeedSaveResumeData()
    {
        return this->_handle->need_save_resume_data();
    }

    bool TorrentHandle::AutoManaged::get()
    {
        return this->_handle->is_auto_managed();
    }

    void TorrentHandle::AutoManaged::set(bool value)
    {
        this->_handle->auto_managed(value);
    }

    void TorrentHandle::QueuePositionDown()
    {
        this->_handle->queue_position_down();
    }

    void TorrentHandle::QueuePositionTop()
    {
        this->_handle->queue_position_top();
    }

    void TorrentHandle::QueuePositionBottom()
    {
        this->_handle->queue_position_bottom();
    }

    void TorrentHandle::QueuePositionUp()
    {
        this->_handle->queue_position_up();
    }

    int TorrentHandle::QueuePosition::get()
    {
        return this->_handle->queue_position();
    }

    bool TorrentHandle::ResolveCountries::get()
    {
        return this->_handle->resolve_countries();
    }

    void TorrentHandle::ResolveCountries::set(bool value)
    {
        this->_handle->resolve_countries(value);
    }

    TorrentInfo^ TorrentHandle::TorrentFile::get()
    {
        auto ptr = this->_handle->torrent_file();

        if (!ptr)
        {
            return nullptr;
        }

        return gcnew TorrentInfo(*ptr.get());
    }

    void TorrentHandle::ForceReannounce()
    {
        this->_handle->force_reannounce();
    }

    void TorrentHandle::ForceReannounce(int seconds, int trackerIndex)
    {
        this->_handle->force_reannounce(seconds, trackerIndex);
    }

    void TorrentHandle::ForceDhtAnnounce()
    {
        this->_handle->force_dht_announce();
    }

    void TorrentHandle::ScrapeTracker()
    {
        this->_handle->scrape_tracker();
    }

    int TorrentHandle::UploadLimit::get()
    {
        return this->_handle->upload_limit();
    }

    void TorrentHandle::UploadLimit::set(int value)
    {
        this->_handle->set_upload_limit(value);
    }

    int TorrentHandle::DownloadLimit::get()
    {
        return this->_handle->download_limit();
    }

    void TorrentHandle::DownloadLimit::set(int value)
    {
        this->_handle->set_download_limit(value);
    }

    bool TorrentHandle::SequentialDownload::get()
    {
        return this->_handle->is_sequential_download();
    }

    void TorrentHandle::SequentialDownload::set(bool value)
    {
        this->_handle->set_sequential_download(value);
    }

    int TorrentHandle::MaxUploads::get()
    {
        return this->_handle->max_uploads();
    }

    void TorrentHandle::MaxUploads::set(int value)
    {
        this->_handle->set_max_uploads(value);
    }

    int TorrentHandle::MaxConnections::get()
    {
        return this->_handle->max_connections();
    }

    void TorrentHandle::MaxConnections::set(int value)
    {
        this->_handle->set_max_connections(value);
    }

    void TorrentHandle::SetTrackerLogin(System::String^ userName, System::String^ password)
    {
        this->_handle->set_tracker_login(Utils::GetStdStringFromManagedString(userName), Utils::GetStdStringFromManagedString(password));
    }

    void TorrentHandle::RenameFile(int fileIndex, System::String^ fileName)
    {
        this->_handle->rename_file(fileIndex, Utils::GetStdStringFromManagedString(fileName));
    }

    bool TorrentHandle::SuperSeeding::get()
    {
        return this->_handle->super_seeding();
    }

    void TorrentHandle::SuperSeeding::set(bool value)
    {
        this->_handle->super_seeding(value);
    }
}
