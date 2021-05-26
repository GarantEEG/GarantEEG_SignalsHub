using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GarantEEG_SignalsHub
{
    public partial class FiltersForm : Form
    {
        public FiltersForm()
        {
            InitializeComponent();

            checkBox9.Checked = ConfigManager.Config.UseFilters;

            listBox1.Items.Clear();

            if (MainWindow.m_GarantEEG != null)
            {
                var filters = MainWindow.m_GarantEEG.GetFilters();

                foreach (var filter in filters)
                {
                    listBox1.Items.Add(string.Format("Butterworth: {0} Hz", filter.Frequency()));
                }
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            Form5 f = new Form5();
            f.ShowDialog();

            listBox1.Items.Clear();
            ConfigManager.Config.Filters.Clear();

            var filters = MainWindow.m_GarantEEG.GetFilters();

            foreach (var filter in filters)
            {
                listBox1.Items.Add(string.Format("Butterworth: {0} Hz", filter.Frequency()));
                ConfigManager.Config.Filters.Add(new FilterInfo(filter.Type(), filter.Frequency()));
            }
        }

        private void button13_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show(
                "Are you shure you want to delete the selected filter?",
                "Remove filter?",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (res == DialogResult.Yes)
            {
                int index = listBox1.SelectedIndex;

                if (index >= 0 && index < listBox1.Items.Count)
                {
                    listBox1.Items.RemoveAt(index);

                    if (index < ConfigManager.Config.Filters.Count)
                        ConfigManager.Config.Filters.RemoveAt(index);

                    if (MainWindow.m_GarantEEG != null)
                    {
                        var filters = MainWindow.m_GarantEEG.GetFilters();

                        if (index < filters.Count)
                            MainWindow.m_GarantEEG.RemoveFilter(filters[index]);
                    }
                }
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show(
                "Are you shure you want to delete the all filters?",
                "Remove filters",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (res == DialogResult.Yes)
            {
                listBox1.Items.Clear();
                ConfigManager.Config.Filters.Clear();

                if (MainWindow.m_GarantEEG != null)
                    MainWindow.m_GarantEEG.RemoveAllFilters();
            }
        }

        private void button15_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void checkBox9_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.UseFilters = checkBox9.Checked;
        }
    }
}
