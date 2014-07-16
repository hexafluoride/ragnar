using System;
using System.IO;
using System.Linq;
using System.Threading;

namespace Ragnar.SampleClient
{
    public class Program
    {
        public static void Main(string[] args)
        {
            new Program().Run(args);
        }

        public void Run(string[] args)
        {
            using (var session = new Session())
            {
                if (File.Exists(".ses_state"))
                {
                    Console.WriteLine("Loading state");
                    session.LoadState(File.ReadAllBytes(".ses_state"));
                }

                session.ListenOn(6881, 6889);

                var p = new AddTorrentParams
                {
                    SavePath = "C:\\Downloads",
                    TorrentInfo = new TorrentInfo(args[0])
                };

                if (File.Exists(Path.Combine(".resume", p.TorrentInfo.Name + ".fastresume")))
                {
                    Console.WriteLine("Loading fast resume data");
                    p.ResumeData = File.ReadAllBytes(Path.Combine(".resume", p.TorrentInfo.Name + ".fastresume"));
                }

                var handle = session.AddTorrent(p);

                while (true)
                {
                    var status = handle.QueryStatus();

                    if (status.IsSeeding)
                    {
                        break;
                    }

                    Console.WriteLine("{0}%", status.Progress*100);

                    Thread.Sleep(1000);
                }

                session.Pause();

                // Save torrent resume data
                if (handle.NeedSaveResumeData())
                {
                    Console.WriteLine("Saving resume data");
                    handle.SaveResumeData();
                    var savedFastResume = false;

                    while (!savedFastResume)
                    {
                        var alerts = session.Alerts.PopAll();
                        if (alerts == null || !alerts.Any()) continue;

                        foreach (var alert in alerts)
                        {
                            if (alert is SaveResumeDataAlert)
                            {
                                var saveResumeAlert = (SaveResumeDataAlert)alert;

                                if (!Directory.Exists(".resume")) Directory.CreateDirectory(".resume");

                                var status = saveResumeAlert.Handle.QueryStatus();
                                File.WriteAllBytes(
                                    Path.Combine(".resume", status.Name + ".fastresume"),
                                    saveResumeAlert.ResumeData);

                                Console.WriteLine("Resume data saved");

                                savedFastResume = true;

                                break;
                            }
                        }
                    }
                }

                // Save state
                Console.WriteLine("Saving state.");
                File.WriteAllBytes(".ses_state", session.SaveState());
            }
        }
    }
}
