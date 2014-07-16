#pragma once

#include <libtorrent\torrent_handle.hpp>

#include "TorrentInfo.h"
#include "TorrentStatus.h"

namespace Ragnar
{
    public ref class TorrentHandle
    {
    private:
        libtorrent::torrent_handle* _handle;

    internal:
        libtorrent::torrent_handle* get_ptr() { return this->_handle; }

        TorrentHandle(const libtorrent::torrent_handle &handle);

    public:
        ~TorrentHandle();

        // add_piece
        // read_piece
        // have_piece
        // get_peer_info

        property System::String^ InfoHash { System::String^ get(); }

        TorrentStatus^ QueryStatus();

        // get_download_queue

        // clear_piece_deadlines()
        // reset_piece_deadline()
        // set_piece_deadline()

        void SetPriority(int priority);

        // file_progress

        void ClearError();

        // add_tracker()
        // replace_trackers()
        // trackers()

        // url_seeds()
        // add_url_seed()
        // remove_url_seed()

        // http_seeds()
        // remove_http_seed()
        // add_http_seed()

        // add_extension()

        // set_metadata()

        // is_valid();

        void Pause();

        void Resume();

        void SetUploadMode(bool value);

        void SetShareMode(bool value);

        void FlushCache();

        void ApplyIPFilter(bool value);

        void ForceRecheck();

        void SaveResumeData();

        bool NeedSaveResumeData();

        property bool AutoManaged { bool get(); void set(bool value); }

        void QueuePositionDown();

        void QueuePositionTop();

        void QueuePositionBottom();

        void QueuePositionUp();

        property int QueuePosition { int get(); }

        property bool ResolveCountries { bool get(); void set(bool value); }

        // set_ssl_certificate_buffer()
        // set_ssl_certificate()

        // get_storage_impl()

        property TorrentInfo^ TorrentFile { TorrentInfo^ get(); }

        // use_interface()

        // piece_availability()

        // int piece_priority (int index) const;
        // void piece_priority(int index, int priority) const;
        // void prioritize_pieces(std::vector<int> const& pieces) const;
        // std::vector<int> piece_priorities() const;

        // int file_priority (int index) const;
        // void prioritize_files(std::vector<int> const& files) const;
        // void file_priority(int index, int priority) const;
        // std::vector<int> file_priorities() const;

        void ForceReannounce();

        void ForceReannounce(int seconds, int trackerIndex);

        void ForceDhtAnnounce();

        void ScrapeTracker();

        property int UploadLimit { int get(); void set(int value); }

        property int DownloadLimit { int get(); void set(int value); }

        property bool SequentialDownload { bool get(); void set(bool value); }

        // TODO: void connect_peer (tcp::endpoint const& adr, int source = 0) const;

        property int MaxUploads { int get(); void set(int value); }

        property int MaxConnections { int get(); void set(int value); }

        void SetTrackerLogin(System::String^ userName, System::String^ password);

        // TODO: void MoveStorage(System::String^ savePath) // flags?

        void RenameFile(int fileIndex, System::String^ fileName);

        property bool SuperSeeding { bool get(); void set(bool value); }
    };
}
