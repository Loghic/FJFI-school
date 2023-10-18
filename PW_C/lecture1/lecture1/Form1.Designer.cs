namespace lecture1
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
            this.add_button = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.win_button = new System.Windows.Forms.Button();
            this.test_button = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // add_button
            // 
            this.add_button.Location = new System.Drawing.Point(93, 12);
            this.add_button.Name = "add_button";
            this.add_button.Size = new System.Drawing.Size(165, 105);
            this.add_button.TabIndex = 0;
            this.add_button.Text = "Generate text";
            this.add_button.UseVisualStyleBackColor = true;
            this.add_button.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(93, 146);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(579, 250);
            this.textBox1.TabIndex = 1;
            // 
            // win_button
            // 
            this.win_button.Location = new System.Drawing.Point(503, 12);
            this.win_button.Name = "win_button";
            this.win_button.Size = new System.Drawing.Size(169, 105);
            this.win_button.TabIndex = 2;
            this.win_button.Text = "New window";
            this.win_button.UseVisualStyleBackColor = true;
            this.win_button.Click += new System.EventHandler(this.button2_Click);
            // 
            // test_button
            // 
            this.test_button.Cursor = System.Windows.Forms.Cursors.AppStarting;
            this.test_button.Location = new System.Drawing.Point(302, 12);
            this.test_button.Name = "test_button";
            this.test_button.Size = new System.Drawing.Size(162, 105);
            this.test_button.TabIndex = 3;
            this.test_button.Text = "loading";
            this.test_button.UseVisualStyleBackColor = true;
            this.test_button.Click += new System.EventHandler(this.test_button_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.test_button);
            this.Controls.Add(this.win_button);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.add_button);
            this.Name = "Form1";
            this.Text = "First Example";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button add_button;
        private TextBox textBox1;
        private Button win_button;
        private Button test_button;
    }
}