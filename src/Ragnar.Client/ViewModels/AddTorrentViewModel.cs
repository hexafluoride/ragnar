using System;
using System.IO;
using Caliburn.Micro;
using Ragnar.Client.Messages;

namespace Ragnar.Client.ViewModels
{
    public class AddTorrentViewModel : Screen
    {
        private readonly IEventAggregator _eventAggregator;
        private readonly AddTorrentParams _addParams;

        public AddTorrentViewModel(IEventAggregator eventAggregator, TorrentInfo torrentInfo)
        {
            if (eventAggregator == null) throw new ArgumentNullException("eventAggregator");

            _eventAggregator = eventAggregator;
            _addParams = new AddTorrentParams
            {
                TorrentInfo = torrentInfo
            };

            _addParams.SavePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), "Downloads");
        }

        public string SavePath
        {
            get { return _addParams.SavePath; }
            set { _addParams.SavePath = value; }
        }

        public string Title
        {
            get { return _addParams.TorrentInfo.Name; }
        }

        public void Add()
        {
            _eventAggregator.PublishOnBackgroundThread(new AddTorrentMessage(_addParams));
            TryClose(true);
        }
    }
}
