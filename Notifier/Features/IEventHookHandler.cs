using System;

namespace Notifier.Features
{
    public interface IEventHookHandler
    {
        void RegisterHandler(uint @event);
        void UnregisterHandler(IntPtr hook);
        void UnregisterAllHandlers();
    }
}