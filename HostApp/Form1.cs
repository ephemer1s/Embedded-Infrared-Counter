using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HostApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void groupbox_com_init()
        {
            textBox2.Text = "9600";
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 2;
            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
        }

        private void groupbox_collect_init()
        {
            textBox1.Text = "60";
            textBox3.Text = "10";
        }

        public void com_init()
        {
            ComVars.baudrate = 9600;
            ComVars.com = "COM1";
            ComVars.data_bit = 8;
            ComVars.parity_bit = 1;
            ComVars.end_bit = 1;
        }

        public void collect_init()
        {
            ComVars.collect_time = 60;
            ComVars.alert_valve = 10;
            ComVars.num_entered = 0;
            ComVars.num_exited = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Interval = 1000;
            timer1.Start();
            groupbox_com_init();
            groupbox_collect_init();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            /* display current time */
            toolStripStatusTime.Text = DateTime.Now.ToString();

            /* write file */
            //string[] logs = new string[] { "Zara Ali", "Nuha Ali" };
            //using (StreamWriter sw = new StreamWriter("./logs/logs.txt"))
            //{
            //    foreach (string s in logs)
            //    {
            //        sw.WriteLine(s);
            //    }
            //}
        }

        private void button_collect_apply_Click(object sender, EventArgs e)
        {

        }

        private void button_serial_apply_Click(object sender, EventArgs e)
        {

        }

        private void button_serial_reset_Click(object sender, EventArgs e)
        {
            com_init();
            groupbox_com_init();
        }
    }
}
