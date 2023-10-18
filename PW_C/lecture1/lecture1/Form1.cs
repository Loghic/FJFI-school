namespace lecture1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private double n = 7.1;
        private void button1_Click(object sender, EventArgs e)
        {
      
      
            textBox1.AppendText ("Nejaky text " + n + " \r\n");
            n++;
        }

        private void button2_Click(object sender, EventArgs e)
        {

            Form1 f = new Form1();
            f.Visible = true;

        }

        private void test_button_Click(object sender, EventArgs e)
        {
            test_button.Text = "Wait I'm loading:))";
        }
    }
}