#pragma once

#include <libtorrent\alert_types.hpp>

#include "TorrentAlert.h"

namespace Ragnar
{
    public ref class SaveResumeDataAlert : TorrentAlert
    {
    private:
        libtorrent::save_resume_data_alert* _alert;
        cli::array<byte>^ _resumeData;

    internal:
        SaveResumeDataAlert(libtorrent::save_resume_data_alert* alert);

    public:
        property cli::array<byte>^ ResumeData { cli::array<byte>^ get(); }
    };
}
