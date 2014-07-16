#pragma once

#include "Alert.h"

namespace Ragnar
{
    public interface class IAlertFactory
    {
        Alert^ Pop();

        System::Collections::Generic::IEnumerable<Alert^>^ PopAll();
    };
}
