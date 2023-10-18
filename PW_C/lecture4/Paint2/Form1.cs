using System.Drawing.Imaging;

namespace Paint2
{
    public partial class Form1 : Form
    {

        const int lineInx = 0;
        const int rectangleInx = 1;
        const int ellipseInx = 2;

        Pen pen = new Pen(Color.FromArgb(255, 0, 0), 3);
        SolidBrush brush = new SolidBrush(Color.Yellow);

        private int colorCnt = 1;

        public Form1()
        {
            InitializeComponent();
            pictureBox_SizeChanged(null, null);
            comboBox.SelectedIndex = lineInx;
            addButton(Color.Red);
            addButton(Color.Green);
            addButton(Color.Yellow);
        }

        private void addButton(Color color)
        {
            Panel p = new Panel();
            p.Width = colorPanel.Width;
            p.Height = colorPanel.Height;
            p.Top = colorPanel.Top; // Y
            p.Left = colorCnt * colorPanel.Width + (colorCnt+1) * colorPanel.Left; // X
            colorCnt++;
            p.Parent = toolPanel;
            // toolPanel.Controls.Add(p)
            p.BackColor = color;
            p.MouseDown += colorPanel_MouseDown;
        }

        private void colorPanel_MouseDown(object sender, MouseEventArgs e)
        {
            Panel panel = sender as Panel;
            if (e.Button == MouseButtons.Middle || Control.ModifierKeys == Keys.Shift)
            {
                ColorDialog dlg = new ColorDialog();
                dlg.Color = panel.BackColor;
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    panel.BackColor = dlg.Color;
                    pen.Color = panel.BackColor;
                }
            }
            else if (e.Button == MouseButtons.Right || Control.ModifierKeys == Keys.Control)
                brush.Color = panel.BackColor;
            else if (e.Button == MouseButtons.Left)
                pen.Color = panel.BackColor;
        }


        private void pictureBox_SizeChanged(object sender, EventArgs e)
        {
            Image old = pictureBox.Image;

            int w = pictureBox.Width;
            int h = pictureBox.Height;
            if (old != null)
            {
                if (w < old.Width) w = old.Width;
                if (h < old.Height) h = old.Height;
            }

            Bitmap image = new Bitmap(w, h);
            Graphics g = Graphics.FromImage(image);
            Brush b = new SolidBrush(Color.White);
            g.FillRectangle(b, 0, 0, w, h);

            if (old != null)
            {
                g.DrawImage(old, 0, 0);
            }

            pictureBox.Image = image;

            if (false)
            {
                w = pictureBox.Width;
                h = pictureBox.Height;
                Bitmap bmp = new Bitmap(w, h, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

                byte[] data = new byte[4 * w * h];
                {
                    int y = 20;
                    for (int x = 10; x <= 80; x++)
                    {
                        int i = 4 * (x + y * w);
                        data[i + 1] = 255; // Green
                        data[i + 3] = 255; // Alpha
                    }
                }

                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++)
                    {
                        int i = 4 * (x + y * w);
                        data[i] = (byte)(x % 256); // Blue
                        data[i + 1] = (byte)(y & 0xff); // Green
                        data[i + 2] = 0; // Red
                        data[i + 3] = 255; // Alpha
                    }

                // http://stackoverflow.com/questions/68717508/receiving-double-image-with-bitmap-on-c-sharp
                Rectangle dimension = new Rectangle(0, 0, bmp.Width, bmp.Height);
                BitmapData picData = bmp.LockBits(dimension, ImageLockMode.ReadWrite, bmp.PixelFormat);
                IntPtr pixelStartAddress = picData.Scan0;
                System.Runtime.InteropServices.Marshal.Copy(data, 0, pixelStartAddress, data.Length);
                bmp.UnlockBits(picData);

                pictureBox.Image = bmp;
            }

        }

        private int X0, Y0;
        private bool click = false;
        private Bitmap save;

        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            X0 = e.X;
            Y0 = e.Y;
            click = true;
            save = new Bitmap(pictureBox.Image);
        }
        private void pictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (click)
            {
                int tool = comboBox.SelectedIndex;

                Graphics g = Graphics.FromImage(pictureBox.Image);
                g.DrawImage(save, 0, 0);
                switch (tool)
                {
                    case lineInx:
                        g.DrawLine(pen, X0, Y0, e.X, e.Y);
                        break;
                    case rectangleInx:
                        int X1 = X0;
                        int Y1 = Y0;
                        int X2 = e.X;
                        int Y2 = e.Y;
                        if (X1 > X2) { int t = X1; X1 = X2; X2 = t; }
                        if (Y1 > Y2) { int t = Y1; Y1 = Y2; Y2 = t; }
                        g.FillRectangle(brush, X1, Y1, X2 - X1, Y2 - Y1);
                        g.DrawRectangle(pen, X1, Y1, X2 - X1, Y2 - Y1);
                        break;
                    case ellipseInx:
                        g.FillEllipse(brush, X0, Y0, e.X - X0, e.Y - Y0);
                        g.DrawEllipse(pen, X0, Y0, e.X - X0, e.Y - Y0);
                        break;
                }
                pictureBox.Invalidate();
            }
        }

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            click = false;
        }

     
    }
}