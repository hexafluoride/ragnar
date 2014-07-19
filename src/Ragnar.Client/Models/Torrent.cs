using Caliburn.Micro;

namespace Ragnar.Client.Models
{
    public class Torrent : PropertyChangedBase
    {
        private string _name;
        private float _progress;

        public string Name
        {
            get { return _name; }
            set
            { 
                NotifyOfPropertyChange(() => Name);
                _name = value;
            }
        }

        public float Progress
        {
            get { return _progress; }
            set
            {
                NotifyOfPropertyChange(() => Progress);
                _progress = value;
            }
        }
    }
}
