namespace DrawBox
{
    public partial class Window : Form
    {
        public Window()
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
            Brush b = new SolidBrush(Color.CornflowerBlue);
            Graphics g = Graphics.FromImage(image);
            g.FillRectangle(b, 0, 0, w, h);

            if (old != null)
            {
                g.DrawImage(old, 0, 0);
            }
            pictureBox.Image = image;
        }

        private int X0, Y0;
        private bool click = false;
        private Bitmap save;

        private void pictureBox_MouseDown (object sender, MouseEventArgs e)
        {
            X0 = e.X;
            Y0 = e.Y;
            click = true;
            save = new Bitmap(pictureBox.Image);
        }

        private void pictureBox_MouseMove (object sender, MouseEventArgs e)
        {
            if (click)
            {
                Graphics g = Graphics.FromImage(pictureBox.Image);
                g.DrawImage(save,0, 0);
                Pen p = new Pen(Color.FromArgb(255, 0, 0));
                g.DrawLine(p, X0, Y0, e.X, e.Y);
                pictureBox.Invalidate();
            }
        }

        private void pictureBox_MouseUp (object sender, MouseEventArgs e)
        {
            click = false;
        }
       
    }
}