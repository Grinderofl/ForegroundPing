using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Notifier.Core;

namespace Notifier.Features
{
    public class EventLoop
    {
        public static void Run()
        {
            while (true)
            {
                MSG msg;
                if (!Win32Wrapper.PeekMessage(out msg, IntPtr.Zero, 0, 0, Win32.PM_REMOVE)) continue;
                if (msg.Message == Win32.WM_QUIT)
                    break;
                Win32Wrapper.TranslateMessage(ref msg);
                Win32Wrapper.DispatchMessage(ref msg);
            }
        }
    }
}
