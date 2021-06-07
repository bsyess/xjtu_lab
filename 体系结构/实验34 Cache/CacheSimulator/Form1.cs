using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CacheSimulator
{
    public partial class Form1 : Form
    {
        private Cache cache = new Cache();
        private List<String> din = new List<string>();
        private int dinp = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void 关于ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            MessageBox.Show("计试81 白思雨 2186123935","关于");
        }
        private void 使用帮助ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("1. 启动模拟器\n      鼠标双击 \"CacheSimulator.exe\" 即可启动运行。\n2. 操作界面\n       在交互式界面中，左侧为指令展示区域，右侧为操作和结果输出区域。\n3. 操作流程\n       选择菜单栏 \"文件\"-\"打开\" 导入运行文件并在控制区域进行操作，或手工输入并点击 \"执行\" 按钮手动执行。\n4. 模拟结果\n      模拟结果将在下方展示，包括各项访问总次数、不命中次数、不命中率等统计信息。", "使用帮助");
        }

        private void 打开ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                System.IO.StreamReader sr = new System.IO.StreamReader(openFileDialog1.FileName);
                din.Clear();
                while (!sr.EndOfStream)
                {
                    din.Add(sr.ReadLine());
                }
                sr.Close();
                dinp = 0;
                listBox1.Items.Clear();
                for (int i = 0; i < 1000; i++)
                {
                    if (i < din.Count)
                        listBox1.Items.Add(din[i]);
                }
                listBox1.SelectedIndex = 0;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Reset();
        }

        private void Reset()
        {
            comboBox1.SelectedIndex = 5;
            comboBox2.SelectedIndex = 1;
            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
            comboBox5.SelectedIndex = 0;
            comboBox6.SelectedIndex = 0;
            comboBox1.Enabled = true;
            comboBox2.Enabled = true;
            comboBox3.Enabled = true;
            comboBox4.Enabled = true;
            comboBox5.Enabled = true;
            comboBox6.Enabled = true;
            if (listBox1.Items.Count > 0)
                listBox1.SelectedIndex = 0;
            cache.Reset();
            dinp = 0;
            textBox2.Text = "";
        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Reset();
        }

        private void RunString(String s)
        {
            string[] l = s.Split();
            if (l.Length >= 2)
            {
                cache.RunOnce(Convert.ToInt32(l[0]), Convert.ToUInt32(l[1], 16));
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            RunString(textBox1.Text);
            UpdateCounts();
        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Dispose();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (dinp < din.Count)
            {
                RunString(din[dinp]);
                dinp++;
                if (dinp < listBox1.Items.Count)
                    listBox1.SelectedIndex = dinp;
                UpdateCounts();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            while (dinp < din.Count)
            {
                RunString(din[dinp]);
                dinp++;
            }
            listBox1.SelectedIndex = listBox1.Items.Count - 1;
            UpdateCounts();
        }

        private void UpdateCounts()
        {
            int TotalCount = cache.ReadDCount + cache.ReadICount + cache.WriteCount;
            int TotalMiss = cache.ReadDMiss + cache.ReadIMiss + cache.WriteMiss;
            textBox2.Text = String.Format(
                "访问总次数: {0}\t不命中次数: {1}\t不命中率: {2:P2}" + Environment.NewLine +
                "读指令次数: {3}\t不命中次数: {4}\t不命中率: {5:P2}" + Environment.NewLine +
                "读数据次数: {6}\t不命中次数: {7}\t不命中率: {8:P2}" + Environment.NewLine +
                "写数据次数: {9}\t不命中次数: {10}\t不命中率: {11:P2}" + Environment.NewLine,
                TotalCount, TotalMiss, (double)TotalMiss / TotalCount,
                cache.ReadICount, cache.ReadIMiss, (double)cache.ReadIMiss / cache.ReadICount,
                cache.ReadDCount, cache.ReadDMiss, (double)cache.ReadDMiss / cache.ReadDCount,
                cache.WriteCount, cache.WriteMiss, (double)cache.WriteMiss / cache.WriteCount
            );
            if (cache.Updated)
            {
                textBox2.Text += Environment.NewLine + String.Format("访问类型: {0}\t地址: {1}\t块号: {2}" + Environment.NewLine +
                    "块内地址: {3}\t索引: {4}\t命中情况: {5}",
                    cache.Type == 0 ? "读数据" : cache.Type == 1 ? "写数据" : "读指令",
                    cache.Address, cache.BlockNum, cache.InBlockAddress, cache.IndexNum, cache.Miss ? "不命中" : "命中");
            }
            comboBox1.Enabled = false;
            comboBox2.Enabled = false;
            comboBox3.Enabled = false;
            comboBox4.Enabled = false;
            comboBox5.Enabled = false;
            comboBox6.Enabled = false;
        }

        private void SetOptions()
        {
            Cache.CacheSize = 2048 << comboBox1.SelectedIndex;
            Cache.BlockSize = 16 << comboBox2.SelectedIndex;
            Cache.Associativity = 1 << comboBox3.SelectedIndex;
            Cache.ReplaceMethod = comboBox4.SelectedIndex;
            Cache.PrefetchMethod = comboBox5.SelectedIndex;
            Cache.WriteMethod = comboBox6.SelectedIndex;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetOptions();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetOptions();
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetOptions();
        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetOptions();
        }

        private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetOptions();
        }

        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetOptions();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }
    }
}
