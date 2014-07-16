#pragma once

#include <libtorrent\session.hpp>

#include "IAlertFactory.h"
#include "Alert.h"

namespace Ragnar
{
    public ref class AlertFactory : IAlertFactory
    {
    private:
        libtorrent::session& _session;
        Alert^ GetAlert(std::auto_ptr<libtorrent::alert> alert);

    internal:
        AlertFactory(libtorrent::session &session);

    public:
        virtual Alert^ Pop();

        virtual System::Collections::Generic::IEnumerable<Alert^>^ PopAll();
    };
}
