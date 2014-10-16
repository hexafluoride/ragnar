using System;
using System.Diagnostics;
using System.Threading;
using Caliburn.Micro;
using Ragnar.Client.Messages;
using Ragnar.Client.Models;

namespace Ragnar.Client.Services
{
    public class SessionService : ISessionService
        , IHandle<AddTorrentMessage>
    {
        private readonly ISession _session;
        private readonly IEventAggregator _eventAggregator;
        private readonly Thread _alertsThread;
        private bool _isStopping;

        public SessionService(ISession session, IEventAggregator eventAggregator)
        {
            if (session == null) throw new ArgumentNullException("session");
            if (eventAggregator == null) throw new ArgumentNullException("eventAggregator");

            _session = session;
            _eventAggregator = eventAggregator;
            _alertsThread = new Thread(ReadAlerts);

            _eventAggregator.Subscribe(this);
        }

        public void Start()
        {
            _session.SetAlertMask(SessionAlertCategory.All);
            _session.ListenOn(6881, 6889);

            // Start reading the alerts
            _alertsThread.Start();
        }

        public void Stop()
        {
            _isStopping = true;
            _alertsThread.Join();
        }

        public void Handle(AddTorrentMessage message)
        {
            _session.AsyncAddTorrent(message.Params);
        }

        private void ReadAlerts()
        {
            var timeout = TimeSpan.FromSeconds(0.5);
            var lastPost = DateTime.Now;

            while (!_isStopping)
            {
                if ((DateTime.Now - lastPost).TotalSeconds > 1)
                {
                    _session.PostTorrentUpdates();

                    lastPost = DateTime.Now;
                }

                var foundAlerts = _session.Alerts.PeekWait(timeout);
                if (!foundAlerts) continue;

                var alerts = _session.Alerts.PopAll();

                foreach (var alert in alerts)
                {
                    Debug.WriteLine(alert.Message);

                    if (alert is TorrentAddedAlert)
                    {
                        Handle((TorrentAddedAlert) alert);
                    }
                    else if (alert is StateUpdateAlert)
                    {
                        Handle((StateUpdateAlert) alert);
                    }
                }
            }
        }

        private void Handle(TorrentAddedAlert alert)
        {
            var msg = new TorrentAddedMessage(new Torrent
            {
                InfoHash = alert.Handle.InfoHash.ToHex(),
                Name = alert.Handle.TorrentFile.Name,
                Size = alert.Handle.TorrentFile.TotalSize,
                State = alert.Handle.GetStatus().State
            });

            _eventAggregator.PublishOnBackgroundThread(msg);
        }

        private void Handle(StateUpdateAlert alert)
        {
            for (var i = 0; i < alert.Statuses.Count; i++)
            {
                var status = alert.Statuses[i];
                var torrent = new Torrent
                {
                    InfoHash = status.InfoHash.ToHex(),
                    Name = status.Name,
                    Progress = status.Progress,
                    DownloadRate = status.DownloadRate,
                    UploadRate = status.UploadRate,
                    State = status.State
                };

                _eventAggregator.PublishOnBackgroundThread(new TorrentUpdatedMessage(torrent));
            }
        }
    }
}
