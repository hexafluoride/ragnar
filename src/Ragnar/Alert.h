#pragma once

#include <libtorrent\alert.hpp>

namespace Ragnar
{
    public ref class Alert abstract
    {
    private:
        System::String^ _message;

    internal:
        Alert(libtorrent::alert* alert);

    public:
        property System::String^ Message { System::String^ get(); }
    };
}