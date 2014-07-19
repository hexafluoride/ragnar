using System;

namespace Ragnar.Client.Messages
{
    public class AddTorrentMessage
    {
        private readonly AddTorrentParams _addParams;

        public AddTorrentMessage(AddTorrentParams addParams)
        {
            if (addParams == null) throw new ArgumentNullException("addParams");
            _addParams = addParams;
        }

        public AddTorrentParams Params
        {
            get { return _addParams; }
        }
    }
}
