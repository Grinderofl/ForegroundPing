using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Notifier.Core;
using Notifier.Features;

namespace Notifier
{
    public partial class Form1 : Form
    {
        private readonly IEventHookHandler _handler;

        public Form1(IEventHookHandler handler)
        {
            _handler = handler;
            InitializeComponent();
            _handler.RegisterHandler(Win32.EVENT_SYSTEM_FOREGROUND);
            var thread = new ThreadStart(EventLoop.Run);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            _handler.UnregisterAllHandlers();
            base.OnClosing(e);
        }
    }
}
