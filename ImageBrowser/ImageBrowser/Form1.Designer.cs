namespace ImageBrowser
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.dirBrowseButton = new System.Windows.Forms.Button();
            this.runButton = new System.Windows.Forms.Button();
            this.directoryLabel = new System.Windows.Forms.Label();
            this.fileCountLabel = new System.Windows.Forms.Label();
            this.fileProgressBar = new System.Windows.Forms.ProgressBar();
            this.progressLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // dirBrowseButton
            // 
            this.dirBrowseButton.Location = new System.Drawing.Point(12, 38);
            this.dirBrowseButton.Name = "dirBrowseButton";
            this.dirBrowseButton.Size = new System.Drawing.Size(98, 23);
            this.dirBrowseButton.TabIndex = 0;
            this.dirBrowseButton.Text = "Select Directory";
            this.dirBrowseButton.UseVisualStyleBackColor = true;
            this.dirBrowseButton.Click += new System.EventHandler(this.dirBrowseButton_Click);
            // 
            // runButton
            // 
            this.runButton.Location = new System.Drawing.Point(12, 83);
            this.runButton.Name = "runButton";
            this.runButton.Size = new System.Drawing.Size(98, 23);
            this.runButton.TabIndex = 1;
            this.runButton.Text = "Transfer Files";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // directoryLabel
            // 
            this.directoryLabel.AutoSize = true;
            this.directoryLabel.Location = new System.Drawing.Point(12, 9);
            this.directoryLabel.Name = "directoryLabel";
            this.directoryLabel.Size = new System.Drawing.Size(109, 13);
            this.directoryLabel.TabIndex = 2;
            this.directoryLabel.Text = "No directory specified";
            // 
            // fileCountLabel
            // 
            this.fileCountLabel.AutoSize = true;
            this.fileCountLabel.Location = new System.Drawing.Point(12, 22);
            this.fileCountLabel.Name = "fileCountLabel";
            this.fileCountLabel.Size = new System.Drawing.Size(34, 13);
            this.fileCountLabel.TabIndex = 3;
            this.fileCountLabel.Text = "0 files";
            // 
            // fileProgressBar
            // 
            this.fileProgressBar.Location = new System.Drawing.Point(12, 112);
            this.fileProgressBar.Name = "fileProgressBar";
            this.fileProgressBar.Size = new System.Drawing.Size(260, 23);
            this.fileProgressBar.TabIndex = 4;
            // 
            // progressLabel
            // 
            this.progressLabel.AutoSize = true;
            this.progressLabel.Location = new System.Drawing.Point(12, 138);
            this.progressLabel.Name = "progressLabel";
            this.progressLabel.Size = new System.Drawing.Size(0, 13);
            this.progressLabel.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.progressLabel);
            this.Controls.Add(this.fileProgressBar);
            this.Controls.Add(this.fileCountLabel);
            this.Controls.Add(this.directoryLabel);
            this.Controls.Add(this.runButton);
            this.Controls.Add(this.dirBrowseButton);
            this.Name = "Form1";
            this.Text = "File Transfer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.FolderBrowserDialog folderBrowser;
        private System.Windows.Forms.Button dirBrowseButton;
        private System.Windows.Forms.Button runButton;
        private System.Windows.Forms.Label directoryLabel;
        private System.Windows.Forms.Label fileCountLabel;
        private System.Windows.Forms.ProgressBar fileProgressBar;
        private System.Windows.Forms.Label progressLabel;
    }
}

