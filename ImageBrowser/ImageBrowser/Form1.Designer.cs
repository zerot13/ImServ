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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.dirBrowseButton = new System.Windows.Forms.Button();
            this.runButton = new System.Windows.Forms.Button();
            this.directoryLabel = new System.Windows.Forms.Label();
            this.fileCountLabel = new System.Windows.Forms.Label();
            this.fileProgressBar = new System.Windows.Forms.ProgressBar();
            this.deleteCheckBox = new System.Windows.Forms.CheckBox();
            this.progressTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // dirBrowseButton
            // 
            this.dirBrowseButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            resources.ApplyResources(this.dirBrowseButton, "dirBrowseButton");
            this.dirBrowseButton.Name = "dirBrowseButton";
            this.dirBrowseButton.UseVisualStyleBackColor = true;
            this.dirBrowseButton.Click += new System.EventHandler(this.dirBrowseButton_Click);
            // 
            // runButton
            // 
            resources.ApplyResources(this.runButton, "runButton");
            this.runButton.Name = "runButton";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // directoryLabel
            // 
            resources.ApplyResources(this.directoryLabel, "directoryLabel");
            this.directoryLabel.Name = "directoryLabel";
            // 
            // fileCountLabel
            // 
            resources.ApplyResources(this.fileCountLabel, "fileCountLabel");
            this.fileCountLabel.Name = "fileCountLabel";
            // 
            // fileProgressBar
            // 
            resources.ApplyResources(this.fileProgressBar, "fileProgressBar");
            this.fileProgressBar.Name = "fileProgressBar";
            // 
            // deleteCheckBox
            // 
            resources.ApplyResources(this.deleteCheckBox, "deleteCheckBox");
            this.deleteCheckBox.Name = "deleteCheckBox";
            this.deleteCheckBox.UseVisualStyleBackColor = true;
            // 
            // progressTextBox
            // 
            this.progressTextBox.BackColor = System.Drawing.SystemColors.ControlLightLight;
            resources.ApplyResources(this.progressTextBox, "progressTextBox");
            this.progressTextBox.Name = "progressTextBox";
            this.progressTextBox.ReadOnly = true;
            // 
            // Form1
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.progressTextBox);
            this.Controls.Add(this.deleteCheckBox);
            this.Controls.Add(this.fileProgressBar);
            this.Controls.Add(this.fileCountLabel);
            this.Controls.Add(this.directoryLabel);
            this.Controls.Add(this.runButton);
            this.Controls.Add(this.dirBrowseButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.KeyPreview = true;
            this.Name = "Form1";
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
        private System.Windows.Forms.CheckBox deleteCheckBox;
        private System.Windows.Forms.TextBox progressTextBox;
    }
}

