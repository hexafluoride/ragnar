using System;
using System.Collections.Generic;
using System.Windows;
using Caliburn.Micro;
using Ninject;
using Ragnar.Client.Services;
using Ragnar.Client.ViewModels;

namespace Ragnar.Client
{
    public class RagnarBootstrapper : BootstrapperBase
    {
        private readonly IKernel _kernel;

        public RagnarBootstrapper()
            : base(true)
        {
            _kernel = new StandardKernel();

            // Initialize Caliburn.Micro
            Initialize();
        }

        protected override void Configure()
        {
            // Caliburn components
            _kernel.Bind<IEventAggregator>().To<EventAggregator>().InSingletonScope();
            _kernel.Bind<IWindowManager>().To<WindowManager>().InSingletonScope();

            // Components
            _kernel.Bind<ISession>().To<Session>().InSingletonScope();
            _kernel.Bind<ISessionService>().To<SessionService>().InSingletonScope();

            // View models
            _kernel.Bind<AddTorrentViewModel>().ToSelf();
        }

        protected override void BuildUp(object instance)
        {
            _kernel.Inject(instance);
        }

        protected override IEnumerable<object> GetAllInstances(Type service)
        {
            if (service == null)
            {
                throw new ArgumentNullException("service");
            }

            return _kernel.GetAll(service);
        }

        protected override object GetInstance(Type service, string key)
        {
            if (service == null)
            {
                throw new ArgumentNullException("service");
            }

            return _kernel.Get(service);
        }

        protected override void OnExit(object sender, EventArgs e)
        {
            if (!_kernel.IsDisposed)
            {
                _kernel.Dispose();
            }

            base.OnExit(sender, e);
        }

        protected override void OnStartup(object sender, StartupEventArgs e)
        {
            DisplayRootViewFor<ShellViewModel>();
        }
    }
}
