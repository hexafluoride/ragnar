#include "stdafx.h"
#include "TorrentInfo.h"
#include "Utils.h"

namespace Ragnar
{
    TorrentInfo::TorrentInfo(const libtorrent::torrent_info &info)
    {
        this->_info = new libtorrent::torrent_info(info);
    }

    TorrentInfo::TorrentInfo(System::String^ fileName)
    {
        this->_info = new libtorrent::torrent_info(Utils::GetStdStringFromManagedString(fileName));
    }

    TorrentInfo::TorrentInfo(cli::array<byte>^ buffer)
    {
        pin_ptr<unsigned char> ptr = &buffer[0];
        const char *pbegin = (const char*)(const unsigned char*)ptr;

        this->_info = new libtorrent::torrent_info(pbegin, buffer->Length);
    }

    TorrentInfo::~TorrentInfo()
    {
        delete this->_info;
    }

    System::String^ TorrentInfo::Name::get()
    {
        return gcnew System::String(this->_info->name().c_str());
    }

    System::String^ TorrentInfo::InfoHash::get()
    {
        return gcnew String(libtorrent::to_hex(this->_info->info_hash().to_string()).c_str());
    }

    long long TorrentInfo::TotalSize::get()
    {
        return this->_info->total_size();
    }
}
