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
            ComVars.time_stamp = DateTime.Now.ToString();
            timer2.Stop();


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
            string s = "";
            string f = "./logs/logs.txt";
            if (ComVars.num_enter != int.Parse(labelQ.Text))
            {
                s = "Total Enter: " + ComVars.num_enter.ToString() + " at " + DateTime.Now.ToString();
                using (StreamWriter sw = new StreamWriter(f, true))
                {
                    sw.WriteLine(s);
                }
            }
            if(ComVars.num_exit != int.Parse(labelE.Text))
            {
                s = "Total Exit: " + ComVars.num_enter.ToString() + " at " + DateTime.Now.ToString();
                using (StreamWriter sw = new StreamWriter(f, true))
                {
                    sw.WriteLine(s);
                }
            }


            /* update UI according to data */
            labelQ.Text = ComVars.num_enter.ToString();
            labelE.Text = ComVars.num_exit.ToString();

            ComVars.flow_exit = ComVars.num_exit;
            ComVars.flow_enter = ComVars.num_enter;

            labelA.Text = ComVars.flow_enter.ToString();
            labelD.Text = ComVars.flow_exit.ToString();
        }

        private void button_collect_apply_Click(object sender, EventArgs e)
        {
            //button_collect_apply.Enabled = false;
            int a = int.Parse(textBox1.Text);
            int b = int.Parse(textBox3.Text);

            ComVars.collect_time = (byte)a;
            ComVars.alert_valve = (byte)b;
            //ComVars.used_time = 0;
            collectData_init();
            MessageBox.Show("采集设置应用成功");
            /* serialPort write & send variables */
            if (!serialPort1.IsOpen)
            {
                MessageBox.Show("串口未建立连接，请先建立连接");
            }
            else
            {
                byte[] buf = new byte[] { ComVars.collect_time, ComVars.alert_valve };
                serialPort1.Write(buf, 0, buf.Length);
                MessageBox.Show("Successful sent! Byte1(Dec):" + buf[0].ToString() + " Byte2(Dec):" + buf[1].ToString());
            }
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
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
            setCom();
            linkCom();
        }

        private void setCom()
        {
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
            if(recv == "0")
            {
                if (timer2.Enabled == false)
                {
                    timer2.Enabled = true;
                    timer2.Start();
                }
                ComVars.num_enter++;
            }
            if(recv == "1")
            {
                if (timer2.Enabled == false)
                {
                    timer2.Enabled = true;
                    timer2.Start();
                }
                ComVars.num_exit++;
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            //if (ComVars.num_enter >= ComVars.alert_valve)
            //{
            //    pictureBox1.BackColor = Color.MistyRose;
            //    groupBox1.BackColor = Color.MistyRose;
            //}

            //if (ComVars.num_exit >= ComVars.alert_valve)
            //{
            //    pictureBox2.BackColor = Color.MistyRose;
            //    groupBox2.BackColor = Color.MistyRose;
            //}

            //if (ComVars.used_time == ComVars.collect_time)
            //{
            //    timer2.Stop();
            //}
            //ComVars.used_time++;

            //ComVars.flow_exit = ComVars.num_exit;
            //ComVars.flow_enter = ComVars.num_enter;

            //labelA.Text = ComVars.flow_enter.ToString();
            //labelD.Text = ComVars.flow_exit.ToString();

            //toolStriptimer2.Text = ComVars.used_time.ToString() + "s";
        }

        private void toolStripStatusLabel2_Click(object sender, EventArgs e)
        {
            //toolStriptimer2.Text = "0s";
            //ComVars.used_time = 0;
            //timer2.Stop();
        }

        private void 采集数据清零ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            collectData_init();
            getCollectData();
        }
    }
}
