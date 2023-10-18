namespace Paint2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            toolPanel = new Panel();
            comboBox = new ComboBox();
            pictureBox = new PictureBox();
            toolPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox).BeginInit();
            SuspendLayout();
            // 
            // toolPanel
            // 
            toolPanel.BackColor = Color.FromArgb(255, 255, 192);
            toolPanel.BorderStyle = BorderStyle.Fixed3D;
            toolPanel.Controls.Add(comboBox);
            toolPanel.Dock = DockStyle.Top;
            toolPanel.Location = new Point(0, 0);
            toolPanel.Name = "toolPanel";
            toolPanel.Size = new Size(800, 58);
            toolPanel.TabIndex = 0;
            // 
            // comboBox
            // 
            comboBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right;
            comboBox.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox.FormattingEnabled = true;
            comboBox.Items.AddRange(new object[] { "line", "rectangle", "ellipse" });
            comboBox.Location = new Point(665, 10);
            comboBox.Name = "comboBox";
            comboBox.Size = new Size(121, 23);
            comboBox.TabIndex = 0;
            // 
            // pictureBox
            // 
            pictureBox.Dock = DockStyle.Fill;
            pictureBox.Location = new Point(0, 58);
            pictureBox.Name = "pictureBox";
            pictureBox.Size = new Size(800, 392);
            pictureBox.TabIndex = 1;
            pictureBox.TabStop = false;
            pictureBox.SizeChanged += pictureBox_SizeChanged;
            pictureBox.MouseDown += pictureBox_MouseDown;
            pictureBox.MouseMove += pictureBox_MouseMove;
            pictureBox.MouseUp += pictureBox_MouseUp;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(pictureBox);
            Controls.Add(toolPanel);
            Name = "Form1";
            Text = "Form1";
            toolPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)pictureBox).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private Panel toolPanel;
        private PictureBox pictureBox;
        private ComboBox comboBox;
    }
}