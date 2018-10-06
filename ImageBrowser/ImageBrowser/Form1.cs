using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Net;
using System.Windows.Forms;

namespace ImageBrowser
{
    public partial class Form1 : Form
    {
        private LogManager _logger;
        private Queue<string> retryFiles;

        public Form1()
        {
            InitializeComponent();
            _logger = new LogManager();
            retryFiles = new Queue<string>();
        }

        private void dirBrowseButton_Click(object sender, EventArgs e)
        {
            if (folderBrowser.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            directoryLabel.Text = folderBrowser.SelectedPath;
            fileCountLabel.Text = GetImageFiles(folderBrowser.SelectedPath).Length + " files";
        }

        private void runButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (!Directory.Exists(folderBrowser.SelectedPath))
                {
                    MessageBox.Show("Directory does not exist.");
                }
                string[] fileList = GetImageFiles(folderBrowser.SelectedPath);
                fileProgressBar.Maximum = fileList.Length;
                fileProgressBar.Minimum = 0;
                fileProgressBar.Value = 0;
                fileProgressBar.Step = 1;
                progressTextBox.Text = "Transferring files.";
                foreach (string file in fileList)
                {
                    try
                    {
                        if (!TransferFile(file))
                        {
                            _logger.Error(string.Format("Error while sending file: {0}", file));
                            retryFiles.Enqueue(file);
                        }
                        else
                        {
                            fileProgressBar.PerformStep();
                        }
                    }
                    catch (Exception exc)
                    {
                        _logger.Error(string.Format("Error while sending file: {0}", file), exc);
                        retryFiles.Enqueue(file);
                    }
                }
                while (retryFiles.Count > 0)
                {
                    string currentFile = retryFiles.Dequeue();
                    try
                    {
                        if (!TransferFile(currentFile))
                        {
                            _logger.Error(string.Format("Error while sending file: {0}", currentFile));
                            retryFiles.Enqueue(currentFile);
                        }
                        else
                        {
                            fileProgressBar.PerformStep();
                        }
                    }
                    catch (Exception exc)
                    {
                        _logger.Error(string.Format("Error while sending file: {0}", currentFile), exc);
                        retryFiles.Enqueue(currentFile);
                    }
                }
                progressTextBox.Text = "Transfer Complete";
                if (deleteCheckBox.Checked)
                {
                    progressTextBox.Text += " - Deleting transferred files";
                    fileProgressBar.Value = 0;
                    fileProgressBar.Maximum -= retryFiles.Count;
                    foreach (string file in fileList)
                    {
                        if (!retryFiles.Contains(file))
                        {
                            File.Delete(file);
                            fileProgressBar.PerformStep();
                        }
                    }
                }
                progressTextBox.Text = string.Format("Successfully transferred {0} files.", fileList.Length - retryFiles.Count);
                if (deleteCheckBox.Checked)
                {
                    progressTextBox.Text += "\r\nSuccessfully transferred files have been deleted.";
                }
                if (retryFiles.Count > 0)
                {
                    progressTextBox.Text += string.Format("\r\nFailed on {0} files: ", retryFiles.Count);
                    foreach (string file in retryFiles)
                    {
                        progressTextBox.Text += string.Format("\r\n{0}", file);
                    }
                }
            }
            catch (Exception exc)
            {
                _logger.Error("Exception occurred while processing files.", exc);
            }
        }

        private bool TransferFile(string file)
        {
            if (SendFileName(Path.GetFileName(file)))
            {
                byte[] fileData = File.ReadAllBytes(file);
                return SendFileData(fileData);
            }
            return false;
        }

        private bool SendFileName(string fileName)
        {
            string responseText;
            string url = ConfigurationManager.AppSettings["urlTarget"];
            HttpWebRequest req = (HttpWebRequest) WebRequest.Create(url);
            req.Method = "POST";

            using (StreamWriter writer = new StreamWriter(req.GetRequestStream()))
            {
                writer.Write(fileName);
                writer.Flush();
                writer.Close();

                using (HttpWebResponse httpResponse = (HttpWebResponse) req.GetResponse())
                {
                    using (StreamReader reader = new StreamReader(httpResponse.GetResponseStream()))
                    {
                        responseText = reader.ReadToEnd();
                    }
                }
            }
            return responseText == "OK";
        }

        private bool SendFileData(byte[] fileData)
        {
            string responseText;
            string url = ConfigurationManager.AppSettings["urlTarget"];
            HttpWebRequest req = (HttpWebRequest) WebRequest.Create(url);
            req.Method = "POST";
            using (Stream s = req.GetRequestStream())
            {
                s.Write(fileData, 0, fileData.Length);
                s.Flush();
            }

            using (HttpWebResponse httpResponse = (HttpWebResponse) req.GetResponse())
            {
                using (StreamReader reader = new StreamReader(httpResponse.GetResponseStream()))
                {
                    responseText = reader.ReadToEnd();
                }
            }
            return responseText == "OK";
        }

        private string[] GetImageFiles(string selectedPath)
        {
            string[] filters = new String[] {"*.jpg", "*.jpeg", "*.png", "*.gif", "*.tiff", "*.bmp", "*.raw"};
            List<string> fileList = new List<string>();
            foreach (string filter in filters)
            {
                fileList.AddRange(Directory.GetFiles(selectedPath, filter, SearchOption.AllDirectories));
            }
            return fileList.ToArray();
        }
    }
}
