#pragma once

#include <libtorrent\session.hpp>

#include "TorrentInfo.h"

namespace Ragnar
{
    public ref class AddTorrentParams
    {
    private:
        libtorrent::add_torrent_params* _params;
        cli::array<byte>^ _resumeData;
        TorrentInfo^ _info;

    internal:
        libtorrent::add_torrent_params& get_ptr() { return *_params; }
        AddTorrentParams(const libtorrent::add_torrent_params &params);

    public:
        AddTorrentParams();
        ~AddTorrentParams();

        property System::String^ SavePath
        {
            void set(System::String^ value);
            System::String^ get();
        }

        property System::String^ Url
        {
            void set(System::String^ value);
            System::String^ get();
        }

        property TorrentInfo^ TorrentInfo
        {
            void set(Ragnar::TorrentInfo^ value);
            Ragnar::TorrentInfo^ get();
        }

        property cli::array<byte>^ ResumeData
        {
            cli::array<byte>^ get();
            void set(cli::array<byte>^ value);
        }

        static AddTorrentParams^ FromMagnetUri(System::String^ uri);
    };
}
