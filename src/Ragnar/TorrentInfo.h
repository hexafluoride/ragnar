#pragma once

#include <libtorrent\torrent_info.hpp>

namespace Ragnar
{
    public ref class TorrentInfo
    {
    private:
        libtorrent::torrent_info* _info;

    internal:
        libtorrent::torrent_info* get_ptr() { return this->_info; }
        TorrentInfo(const libtorrent::torrent_info &info);

    public:
        TorrentInfo(System::String^ fileName);
        TorrentInfo(cli::array<byte>^ buffer);

        ~TorrentInfo();

        // TODO: file_storage const& files () const;
        // TODO: file_storage const& orig_files() const;

        property System::String^ Name { System::String^ get(); }

        property System::String^ InfoHash { System::String^ get(); }

        property long long TotalSize { long long get(); }
    };
}
