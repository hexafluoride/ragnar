#include "stdafx.h"
#include "AddTorrentParams.h"
#include "TorrentInfo.h"
#include "Utils.h"

#include <libtorrent\add_torrent_params.hpp>
#include <libtorrent\magnet_uri.hpp>

namespace Ragnar
{
    AddTorrentParams::AddTorrentParams()
    {
        this->_params = new libtorrent::add_torrent_params();
    }

    AddTorrentParams::AddTorrentParams(const libtorrent::add_torrent_params &params)
    {
        this->_params = new libtorrent::add_torrent_params(params);
    }

    AddTorrentParams::~AddTorrentParams()
    {
        delete this->_params;
    }

    System::String^ AddTorrentParams::SavePath::get()
    {
        return gcnew System::String(this->_params->save_path.c_str());
    }

    void AddTorrentParams::SavePath::set(System::String^ value)
    {
        this->_params->save_path = Utils::GetStdStringFromManagedString(value);
    }

    System::String^ AddTorrentParams::Url::get()
    {
        return gcnew System::String(this->_params->url.c_str());
    }

    void AddTorrentParams::Url::set(System::String^ value)
    {
        this->_params->url = Utils::GetStdStringFromManagedString(value);
    }

    TorrentInfo^ AddTorrentParams::TorrentInfo::get()
    {
        return this->_info;
    }

    void AddTorrentParams::TorrentInfo::set(Ragnar::TorrentInfo^ value)
    {
        this->_info = value;
        this->_params->ti = value->get_ptr();
    }

    cli::array<byte>^ AddTorrentParams::ResumeData::get()
    {
        return this->_resumeData;
    }

    void AddTorrentParams::ResumeData::set(cli::array<byte>^ value)
    {
        this->_resumeData = value;
        this->_params->resume_data.resize(value->Length);

        for (int i = 0; i < value->Length; i++)
        {
            this->_params->resume_data[i] = value[i];
        }
    }

    AddTorrentParams^ Ragnar::AddTorrentParams::FromMagnetUri(System::String^ uri)
    {
        libtorrent::add_torrent_params params;
        libtorrent::error_code ec;
        
        libtorrent::parse_magnet_uri(Utils::GetStdStringFromManagedString(uri), params, ec);

        if (ec)
        {
            throw gcnew System::Exception(gcnew System::String(ec.message().c_str()));
        }

        return gcnew AddTorrentParams(params);
    }
}