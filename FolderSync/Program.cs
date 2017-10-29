using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Reflection;
using System.Diagnostics;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace FolderSync
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
#if DEBUG
            MessageBox.Show("FolderSync Debug");
#endif
            if (args.Length < 1)
            {
#if DEBUG
                MessageBox.Show("Argument required.");
#endif
                return;
            }

            string sourcePath = args[0];

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            string localAppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            string dropboxInfoPath = Path.Combine(localAppDataPath, "Dropbox", "info.json");
            string dropboxInfoJson;
            using (var reader = new StreamReader(dropboxInfoPath))
            {
                dropboxInfoJson = reader.ReadToEnd();
            }

            dynamic dropboxInfo = JsonConvert.DeserializeObject(dropboxInfoJson);
            string dropboxRootPath = dropboxInfo.personal.path;

            string syncPath = BrowseToFolder("Select where to store this folder in Dropbox", dropboxRootPath);
            if (string.IsNullOrWhiteSpace(syncPath))
            {
                return;
            }

            string sourceName = Path.GetFileName(sourcePath);
            string destPath = Path.Combine(syncPath, sourceName);

            Process.Start("cmd.exe", string.Format("/C move \"{0}\" \"{1}\\\"", sourcePath, syncPath));
            Process.Start("cmd.exe", string.Format("/C mklink /J \"{0}\" \"{1}\"", sourcePath, destPath));
        }

        static string BrowseToFolder(string title, string rootPath)
        {
            var shellType = Type.GetTypeFromProgID("Shell.Application");
            var shell = Activator.CreateInstance(shellType);
            var folder = shellType.InvokeMember("BrowseForFolder", BindingFlags.InvokeMethod, null, shell, new object[] { 0, title, 0, rootPath });
            if (folder == null) return null; // User clicked cancel
            var folderSelf = folder.GetType().InvokeMember("Self", BindingFlags.GetProperty, null, folder, null);
            return folderSelf.GetType().InvokeMember("Path", BindingFlags.GetProperty, null, folderSelf, null) as string;
        }
    }
}
