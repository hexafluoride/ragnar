using System;
using Ragnar.Client.Models;

namespace Ragnar.Client.Messages
{
    public class TorrentAddedMessage
    {
        private readonly Torrent _torrent;

        public TorrentAddedMessage(Torrent torrent)
        {
            if (torrent == null) throw new ArgumentNullException("torrent");
            _torrent = torrent;
        }

        public Torrent Torrent
        {
            get { return _torrent; }
        }
    }
}
