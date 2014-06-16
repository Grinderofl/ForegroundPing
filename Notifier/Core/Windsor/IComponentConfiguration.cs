using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Castle.Windsor;

namespace Notifier.Core.Windsor
{
    public interface IComponentConfiguration
    {
        void Configure(IWindsorContainer container);
    }
}
