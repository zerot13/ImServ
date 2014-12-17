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
            this.button1 = new System.Windows.Forms.Button();
            this.responseLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // dirBrowseButton
            // 
            this.dirBrowseButton.Location = new System.Drawing.Point(13, 13);
            this.dirBrowseButton.Name = "dirBrowseButton";
            this.dirBrowseButton.Size = new System.Drawing.Size(86, 23);
            this.dirBrowseButton.TabIndex = 0;
            this.dirBrowseButton.Text = "Select Folder";
            this.dirBrowseButton.UseVisualStyleBackColor = true;
            this.dirBrowseButton.Click += new System.EventHandler(this.dirBrowseButton_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 227);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // responseLabel
            // 
            this.responseLabel.AutoSize = true;
            this.responseLabel.Location = new System.Drawing.Point(13, 208);
            this.responseLabel.Name = "responseLabel";
            this.responseLabel.Size = new System.Drawing.Size(33, 13);
            this.responseLabel.TabIndex = 2;
            this.responseLabel.Text = "Label";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.responseLabel);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.dirBrowseButton);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.FolderBrowserDialog folderBrowser;
        private System.Windows.Forms.Button dirBrowseButton;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label responseLabel;
    }
}

