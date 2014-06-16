using System;
using Notifier.Core;
using Notifier.Core.Flags;

namespace Notifier.Features
{
    public class EventProc
    {
        public static void EventCallback(IntPtr hook, uint type, IntPtr hWnd, int idObject, int idChild, uint thread,
            uint time)
        {
            Win32Wrapper.PlaySound("C:\\Windows\\Media\\Speech Misrecognition.wav", IntPtr.Zero,
                PlaySoundFlags.SND_FILENAME | PlaySoundFlags.SND_ASYNC);
        }
    }
}
