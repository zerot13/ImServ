using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Windows.Forms;

namespace ImageBrowser
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void dirBrowseButton_Click(object sender, EventArgs e)
        {
            DialogResult dr = folderBrowser.ShowDialog();
            if (dr == DialogResult.OK)
            {
                MessageBox.Show(folderBrowser.SelectedPath);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (folderBrowser.ShowDialog() != DialogResult.OK)
            {
                return;
            }
            
            responseLabel.Text = folderBrowser.SelectedPath;

            string[] fileList = GetImageFiles(folderBrowser.SelectedPath);

            foreach (string file in fileList)
            {
                if (SendFileName(Path.GetFileName(file)))
                {
                    byte[] fileData = File.ReadAllBytes(file);
                    SendFileData(fileData);
                }
            }
        }

        private bool SendFileName(string fileName)
        {
            string responseText = "";
            HttpWebRequest req = (HttpWebRequest)WebRequest.Create("");
            req.Method = "POST";

            using (StreamWriter writer = new StreamWriter(req.GetRequestStream()))
            {
                writer.Write(fileName);
                writer.Flush();
                writer.Close();
            }
            using (HttpWebResponse httpResponse = (HttpWebResponse)req.GetResponse())
            {
                using (StreamReader reader = new StreamReader(httpResponse.GetResponseStream()))
                {
                    responseText = reader.ReadToEnd();
                }
            }
            return responseText == "OK";
        }

        private void SendFileData(byte[] fileData)
        {
            HttpWebRequest req = (HttpWebRequest)WebRequest.Create("");
            req.Method = "POST";
            using (Stream s = req.GetRequestStream())
            {
                s.Write(fileData, 0, fileData.Length);
                s.Flush();
            }

            using (HttpWebResponse httpResponse = (HttpWebResponse)req.GetResponse())
            {
                using (StreamReader reader = new StreamReader(httpResponse.GetResponseStream()))
                {
                    responseLabel.Text = reader.ReadToEnd();
                }
            }
        }

        private string[] GetImageFiles(string selectedPath)
        {
            string[] filters = new String[] { "*.jpg", "*.jpeg", "*.png", "*.gif", "*.tiff", "*.bmp", "*.raw" };
            List<string> fileList = new List<string>();
            foreach (string filter in filters)
            {
                fileList.AddRange(Directory.GetFiles(selectedPath, filter, SearchOption.AllDirectories));
            }
            return fileList.ToArray();
        }
    }
}
