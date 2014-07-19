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

            var sessionImpl = _session as Session;
            if (sessionImpl != null) sessionImpl.Dispose();
        }

        public void Handle(AddTorrentMessage message)
        {
            _session.AsyncAddTorrent(message.Params);
        }

        private void ReadAlerts()
        {
            var timeout = TimeSpan.FromSeconds(1);

            while (!_isStopping)
            {
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
                }
            }
        }

        private void Handle(TorrentAddedAlert alert)
        {
            var msg = new TorrentAddedMessage(new Torrent
            {
                Name = alert.Handle.TorrentFile.Name
            });

            _eventAggregator.PublishOnBackgroundThread(msg);
        }
    }
}
