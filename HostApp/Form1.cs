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
using System.IO.Ports;
using System.Net.Security;

namespace HostApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void getSerialAttr()
        {
            textBox2.Text = serialPort1.BaudRate.ToString();
            comboBox1.SelectedItem = serialPort1.PortName.ToString();
            comboBox2.SelectedItem = serialPort1.DataBits.ToString();
            comboBox3.SelectedIndex = (int)serialPort1.Parity;
            comboBox4.SelectedIndex = (int)serialPort1.StopBits;
        }

        public void serialPort_init()
        {
            serialPort1.BaudRate = 9600;
            serialPort1.PortName = "COM3";
            serialPort1.DataBits = 8;
            serialPort1.Parity = Parity.None;
            serialPort1.StopBits = StopBits.One;
        }

        private void getCollectAttr()
        {
            textBox1.Text = ComVars.collect_time.ToString();
            textBox3.Text = ComVars.alert_valve.ToString();
        }

        public void collectAttr_init()
        {
            ComVars.collect_time = 60;
            ComVars.alert_valve = 10;
            ComVars.num_enter = 0;
            ComVars.num_exit = 0;
        }

        public void collectData_init()
        {
            ComVars.num_enter = 0;
            ComVars.num_exit = 0;
            ComVars.flow_enter = 0;
            ComVars.flow_exit = 0;
        }

        public void getCollectData()
        {
            labelQ.Text = ComVars.num_enter.ToString();
            labelE.Text = ComVars.num_exit.ToString();
            labelA.Text = ComVars.flow_enter.ToString();
            labelD.Text = ComVars.flow_exit.ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Interval = 1000;
            timer1.Start();
            ComVars.recv_buffer = "";

            serialPort_init();
            getSerialAttr();

            collectAttr_init();
            getCollectAttr();

            collectData_init();
            getCollectData();
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
            //button_collect_apply.Enabled = false;
            ComVars.collect_time = int.Parse(textBox1.Text);
            ComVars.alert_valve = int.Parse(textBox2.Text);
            ComVars.used_time = 0;
            collectData_init();
            MessageBox.Show("采集设置应用成功");
        }

        private void button_serial_reset_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("是否重置串口设置?", "", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                serialPort_init();
                MessageBox.Show("重置成功");
            }
        }

        private void button_serial_apply_Click(object sender, EventArgs e)
        {
            //button_serial_apply.Enabled = false;

            /* Apply Changes */
            bool err = false;
            try
            {
                serialPort1.BaudRate = int.Parse(textBox2.Text);
                serialPort1.DataBits = comboBox2.SelectedIndex + 6;
                serialPort1.Parity = (Parity)comboBox3.SelectedIndex;
                serialPort1.StopBits = (StopBits)(comboBox4.SelectedIndex + 1);
                serialPort1.PortName = comboBox1.Text;
            }
            catch (ArgumentOutOfRangeException)
            {
                serialPort_init();
                getSerialAttr();
                err = true;
                MessageBox.Show("参数值不合法，请检查串口参数。参数值已重置为初始值。");
            }
            if (!err)
            {
                MessageBox.Show("串口设置应用成功");
            }

            linkCom();
        }

        private void linkCom()
        {
            try
            {
                serialPort1.Open();
                MessageBox.Show("串口连接成功");
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString());
                this.Close();
            }
        }

        private void timer3_Tick(object sender, EventArgs e)
        {

        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int n = serialPort1.BytesToRead;
            byte[] buf = new byte[n];
            serialPort1.Read(buf, 0, n);
            string recv = "";
            recv += Encoding.ASCII.GetString(buf);
            MessageBox.Show(recv);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (ComVars.used_time == ComVars.collect_time)
            {
                toolStripStatusLabel3.Visible = true;
                timer2.Stop();
            }
            ComVars.used_time++;
            toolStripStatusLabel2.Text = ComVars.used_time.ToString() + "s";

            ComVars.flow_exit = (int)((float)ComVars.num_exit / (float)ComVars.used_time * 60);
            ComVars.flow_enter = (int)((float)ComVars.num_enter / (float)ComVars.used_time * 60);

            labelA.Text = ComVars.flow_enter.ToString();
            labelD.Text = ComVars.flow_exit.ToString();

        }

        private void debugToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ComVars.used_time = 0;
            timer2.Interval = 1000;
            timer2.Start();
            toolStripStatusLabel2.Text = ComVars.used_time.ToString() + "s";
            toolStripStatusLabel3.Visible = false;
        }


    }
}
