using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Castle.MicroKernel.Registration;
using Castle.Windsor;
using Notifier.Core.Windsor;

namespace Notifier.Core.Conventions
{
    public class FormRegistrationConvention : IComponentConfiguration
    {
        public void Configure(IWindsorContainer container)
        {
            container.Register(Component.For<Form1>());
        }
    }
}
