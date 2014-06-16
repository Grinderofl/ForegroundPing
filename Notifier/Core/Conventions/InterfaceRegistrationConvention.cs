using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Castle.Core.Internal;
using Castle.MicroKernel.Registration;
using Castle.Windsor;
using Notifier.Core.Windsor;

namespace Notifier.Core.Conventions
{
    public class InterfaceRegistrationConvention : IComponentConfiguration
    {
        public void Configure(IWindsorContainer container)
        {
            container.Register(
                Classes.FromThisAssembly()
                    .Where(x => x.Namespace != null && x.Namespace.EndsWith("Impl"))
                    .WithServiceAllInterfaces());
        }
    }
}
