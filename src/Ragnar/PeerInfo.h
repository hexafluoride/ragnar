#pragma once

namespace libtorrent
{
    struct peer_info;
}

namespace Ragnar
{
    public ref class PeerInfo
    {
    private:
        libtorrent::peer_info* _info;

    internal:
        PeerInfo(const libtorrent::peer_info &info);

    public:
        ~PeerInfo();

        // TODO: boost::uint32_t flags;
        // TODO: int source;
        // TODO: char read_state;
        // TODO: char write_state;

        property System::Net::IPEndPoint^ EndPoint { System::Net::IPEndPoint^ get(); }

        property int UpSpeed { int get(); }

        property int DownSpeed { int get(); }

        property int PayloadUpSpeed { int get(); }

        property int PayloadDownSpeed { int get(); }

        property long long TotalDownload { long long get(); }

        property long long TotalUpload { long long get(); }

        // TODO: peer_id pid;
        // TODO: bitfield pieces;

        property int UploadLimit { int get(); }

        property int DownloadLimit { int get(); }

        property System::TimeSpan^ LastRequest { System::TimeSpan^ get(); }

        property System::TimeSpan^ LastActive { System::TimeSpan^ get(); }

        property System::TimeSpan^ DownloadQueueTime { System::TimeSpan^ get(); }

        property int QueueBytes { int get(); }

        property System::TimeSpan^ RequestTimeout { System::TimeSpan^ get(); }

        property int SendBufferSize { int get(); }

        property int UsedSendBuffer { int get(); }

        property int ReceiveBufferSize { int get(); }

        property int UsedReceiveBuffer { int get(); }

        property int NumHashfails { int get(); }

        // TODO:    char country[2];

        property System::String^ InetAsName { System::String^ get(); }

        property int InetAs { int get(); }

        property int DownloadQueueLength { int get(); }

        property int TimedOutRequests { int get(); }

        property int BusyRequests { int get(); }

        property int RequestsInBuffer { int get(); }

        property int TargetDownloadQueueLength { int get(); }

        property int UploadQueueLength { int get(); }

        property int FailCount { int get(); }

        property int DownloadingPieceIndex { int get(); }

        property int DownloadingBlockIndex { int get(); }

        property int DownloadingProgress { int get(); }

        property int DownloadingTotal { int get(); }

        property System::String^ Client { System::String^ get(); }

        // TODO: property int ConnectionType { int get(); } enum flags

        property int RemoteDownloadRate { int get(); }

        property int PendingDiskBytes { int get(); }

        property int SendQuota { int get(); }

        property int ReceiveQuota { int get(); }

        property int RoundTripTime { int get(); }

        property int NumPieces { int get(); }

        property int DownloadRatePeak { int get(); }

        property int UploadRatePeak { int get(); }

        property int ProgressPpm { int get(); }

        property int EstimatedReciprocationRate { int get(); }

        property System::Net::IPEndPoint^ LocalEndPoint { System::Net::IPEndPoint^ get(); }
    };
}
