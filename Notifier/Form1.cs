﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Notifier.Core;
using Notifier.Core.Flags;
using Notifier.Features;

namespace Notifier
{
    public partial class Form1 : Form
    {
        private readonly IEventHookHandler _handler;
        private readonly Thread _thread;

        private static readonly uint KeypressId = Win32Wrapper.RegisterWindowMessage("WM_GLOBAL_KEYPRESS");
        private static readonly uint MouseId = Win32Wrapper.RegisterWindowMessage("WM_GLOBAL_MOUSE");

        [DllImport("Hooks.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Install(IntPtr hWnd);

        [DllImport("Hooks.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Uninstall();

        

        public Form1(IEventHookHandler handler)
        {
            _handler = handler;
            InitializeComponent();
            _handler.RegisterHandler(Win32.EVENT_SYSTEM_FOREGROUND);
            _thread = new Thread(EventLoop.Run);
            Install(Handle);
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            Uninstall();
            _thread.Abort();
            _handler.UnregisterAllHandlers();
            base.OnClosing(e);
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == KeypressId)
                Win32Wrapper.PlaySound("C:\\Windows\\Media\\Chord.wav", IntPtr.Zero,
                PlaySoundFlags.SND_FILENAME | PlaySoundFlags.SND_ASYNC);

            else if (m.Msg == MouseId)
                Win32Wrapper.PlaySound("C:\\Windows\\Media\\notify.wav", IntPtr.Zero,
                PlaySoundFlags.SND_FILENAME | PlaySoundFlags.SND_ASYNC);
            base.WndProc(ref m);
        }
    }
}
