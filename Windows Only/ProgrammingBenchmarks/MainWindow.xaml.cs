using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Threading;

namespace ProgrammingBenchmarks
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly string EXE_DIR = AppDomain.CurrentDomain.BaseDirectory;
        public MainWindow()
        {
            InitializeComponent();

            versionNumber.Text = "v" + System.Reflection.Assembly.GetEntryAssembly().GetName().Version;
        }

        private void start_Click(object sender, RoutedEventArgs e)
        {
            programAlive.IsIndeterminate = true;

            status.Content = "Doing base run: Cloning from GitHub. This may take some time, see the command prompt window for status... (Will be placed in a temporary directory in the program folder)";

            Process.Start(AppDomain.CurrentDomain.BaseDirectory + "\\batchFiles\\Chromium\\baseRun.bat");
        }
    }
}
