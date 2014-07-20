using System;
using Caliburn.Micro;

namespace Ragnar.Client.Models
{
    public class Torrent : PropertyChangedBase
    {
        private string _infoHash;
        private string _name;
        private long _size;
        private float _progress;
        private TorrentState _state;
        private int _downloadRate;
        private int _uploadRate;
        private TimeSpan _eta;

        public string InfoHash
        {
            get { return _infoHash; }
            set
            {
                _infoHash = value;
                NotifyOfPropertyChange(() => InfoHash);
            }
        }

        public string Name
        {
            get { return _name; }
            set
            {
                _name = value;
                NotifyOfPropertyChange(() => Name);
            }
        }

        public long Size
        {
            get { return _size; }
            set
            {
                _size = value;
                NotifyOfPropertyChange(() => Size);
            }
        }

        public float Progress
        {
            get { return _progress; }
            set
            {
                _progress = value;
                NotifyOfPropertyChange(() => Progress);
            }
        }

        public TorrentState State
        {
            get { return _state; }
            set
            {
                _state = value;
                NotifyOfPropertyChange(() => State);
            }
        }

        public int DownloadRate
        {
            get { return _downloadRate; }
            set
            {
                _downloadRate = value;
                NotifyOfPropertyChange(() => DownloadRate);
            }
        }

        public int UploadRate
        {
            get { return _uploadRate; }
            set
            {
                _uploadRate = value;
                NotifyOfPropertyChange(() => UploadRate);
            }
        }
    }
}
