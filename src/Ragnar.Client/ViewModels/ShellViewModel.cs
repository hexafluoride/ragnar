using System;
using Caliburn.Micro;
using Microsoft.Win32;
using Ragnar.Client.Messages;
using Ragnar.Client.Models;
using Ragnar.Client.Services;

namespace Ragnar.Client.ViewModels
{
    public sealed class ShellViewModel : Screen
        , IHandle<TorrentAddedMessage>
    {
        private readonly ISessionService _sessionService;
        private readonly IWindowManager _windowManager;
        private readonly IEventAggregator _eventAggregator;
        private readonly IObservableCollection<Torrent> _torrents; 

        public ShellViewModel(ISessionService sessionService,
            IWindowManager windowManager,
            IEventAggregator eventAggregator)
        {
            if (sessionService == null) throw new ArgumentNullException("sessionService");
            if (windowManager == null) throw new ArgumentNullException("windowManager");
            if (eventAggregator == null) throw new ArgumentNullException("eventAggregator");

            _sessionService = sessionService;
            _windowManager = windowManager;
            _eventAggregator = eventAggregator;
            _torrents = new BindableCollection<Torrent>();

            _eventAggregator.Subscribe(this);
        }

        public IObservableCollection<Torrent> Torrents
        {
            get { return _torrents; }
        }

        public void Handle(TorrentAddedMessage message)
        {
            _torrents.Add(message.Torrent);
        }

        protected override void OnActivate()
        {
            _sessionService.Start();
        }

        protected override void OnDeactivate(bool close)
        {
            _sessionService.Stop();
        }

        public void ShowAddTorrent()
        {
            var dialog = new OpenFileDialog
            {
                Filter = "Torrents (*.torrent)|*.torrent",
                Title = "Select a .torrent file to open"
            };

            if (dialog.ShowDialog() == true)
            {
                // Show Add dialog with torrent selected
                var torrentInfo = new TorrentInfo(dialog.FileName);
                _windowManager.ShowDialog(new AddTorrentViewModel(_eventAggregator, torrentInfo));
            }
        }
    }
}
