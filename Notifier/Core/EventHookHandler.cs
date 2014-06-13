using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Notifier.Core
{
    public class EventHookHandler
    {
        private List<IntPtr> _hooks;

        public EventHookHandler()
        {
            _hooks = new List<IntPtr>();
        }

        public void RegisterHandler(uint @event)
        {
            var hook = Win32Wrapper.SetWinEventHook(@event, @event, IntPtr.Zero, EventProc.EventCallback, 0, 0,
                Win32.WINEVENT_OUTOFCONTEXT | Win32.WINEVENT_SKIPOWNPROCESS);
            _hooks.Add(hook);
        }

        public void UnregisterHandler(IntPtr hook)
        {
            
        }

        public void UnregisterAllHandlers()
        {
            
        }
    }
}
