#pragma once

#include "AddTorrentParams.h"
#include "IAlertFactory.h"
#include "TorrentHandle.h"

namespace Ragnar
{
    public interface class ISession
    {
        void LoadState(cli::array<byte>^ buffer);
        cli::array<byte>^ SaveState();

        TorrentHandle^ FindTorrent(System::String^ infoHash);
        System::Collections::Generic::IEnumerable<TorrentHandle^>^ GetTorrents();

        TorrentHandle^ AddTorrent(AddTorrentParams^ params);

        void AsyncAddTorrent(AddTorrentParams^ params);

        void Pause();
        void Resume();

        property bool IsPaused { bool get(); }

        property bool IsDhtRunning { bool get(); }

        void StartDht();

        void StopDht();

        void SetKey(int key);

        void ListenOn(int lower, int upper);

        property bool IsListening { bool get(); }

        property int ListenPort { int get(); }

        property int SslListenPort { int get(); }

        void RemoveTorrent(TorrentHandle^ handle);

        property IAlertFactory^ Alerts { IAlertFactory^ get(); }

        void SetAlertMask(unsigned int mask);

        void StopLsd();

        void StartLsd();

        void StopUpnp();

        void StartUpnp();

        void StopNatPmp();

        void StartNatPmp();
    };
}

