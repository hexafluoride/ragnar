#include "stdafx.h"
#include "Alert.h"

namespace Ragnar
{
    Alert::Alert(libtorrent::alert* alert)
    {
        this->_message = gcnew System::String(alert->message().c_str());
    }

    System::String^ Alert::Message::get()
    {
        return this->_message;
    }
}