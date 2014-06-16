using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Castle.MicroKernel.Registration;
using Castle.Windsor;
using Notifier.Core.Windsor;

namespace Notifier
{
    static class Program
    {
        private static IWindsorContainer _container;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            RegisterContainer();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(_container.Resolve<Form1>());
        }

        private static void RegisterContainer()
        {
            _container = new WindsorContainer();
            _container.Register(
                Classes.FromThisAssembly()
                    .Where(x => typeof (IComponentConfiguration).IsAssignableFrom(x))
                    .WithServices(typeof (IComponentConfiguration)));
            foreach (var component in _container.ResolveAll<IComponentConfiguration>())
                component.Configure(_container);
        }
    }
}