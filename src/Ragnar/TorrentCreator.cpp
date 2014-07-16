#include "stdafx.h"
#include "TorrentCreator.h"
#include "Utils.h"

namespace Ragnar
{
    TorrentCreator::TorrentCreator(TorrentInfo^ info)
    {
        this->_creator = new libtorrent::create_torrent(*info->get_ptr());
    }

    TorrentCreator::~TorrentCreator()
    {
        delete this->_creator;
    }

    cli::array<byte>^ TorrentCreator::Generate()
    {
        libtorrent::entry entry = this->_creator->generate();

        if (entry.type() == libtorrent::entry::undefined_t)
        {
            throw gcnew System::Exception("Could not generate torrent file");
        }

        return Utils::GetByteArrayFromLibtorrentEntry(entry);
    }
}
