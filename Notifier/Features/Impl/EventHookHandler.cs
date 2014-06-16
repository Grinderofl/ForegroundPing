using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Notifier.Core;

namespace Notifier.Features.Impl
{
    public class EventHookHandler : IEventHookHandler
    {
        private readonly List<IntPtr> _hooks;

        public EventHookHandler()
        {
            _hooks = new List<IntPtr>();
        }

        public void RegisterHandler(uint @event)
        {
            var hook = Win32Wrapper.SetWinEventHook(@event, @event, IntPtr.Zero, EventProc.EventCallback, 0, 0,
                Win32.WINEVENT_OUTOFCONTEXT | Win32.WINEVENT_SKIPOWNPROCESS);
            if (hook == IntPtr.Zero)
                throw new Win32Exception(Marshal.GetLastWin32Error());
            
            _hooks.Add(hook);
        }

        public void UnregisterHandler(IntPtr hook)
        {
            Win32Wrapper.UnhookWinEvent(hook);
        }

        public void UnregisterAllHandlers()
        {
            _hooks.ForEach(UnregisterHandler);
        }
    }
}
