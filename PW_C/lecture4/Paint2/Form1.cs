using System.Drawing.Imaging;

namespace Paint2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            pictureBox_SizeChanged(null, null);
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
                Graphics g = Graphics.FromImage(pictureBox.Image);
                g.DrawImage(save, 0, 0);
                Pen p = new Pen(Color.FromArgb(255, 0, 0));
                p.Width = 3;
                g.DrawLine(p, X0, Y0, e.X, e.Y);
                pictureBox.Invalidate();
            }
        }

        private void pictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            click = false;
        }

    }
}