#pragma once

#include <libtorrent\create_torrent.hpp>

#include "TorrentInfo.h"

namespace Ragnar
{
    public ref class TorrentCreator
    {
    private:
        libtorrent::create_torrent* _creator;

    public:
        TorrentCreator(TorrentInfo^ info);
        ~TorrentCreator();

        cli::array<byte>^ Generate();
    };
}
