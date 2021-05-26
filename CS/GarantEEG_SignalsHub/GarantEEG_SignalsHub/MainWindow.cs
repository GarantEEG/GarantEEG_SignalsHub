using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GarantEEG;
using System.Diagnostics;
using LSL;

namespace GarantEEG_SignalsHub
{
    public partial class MainWindow : Form
    {
        public static IGarantEEG m_GarantEEG { get; set; }

        private static System.Threading.Mutex m_Mutex = new System.Threading.Mutex();

        private static Timer m_DataTimer = new Timer();

        private List<GARANT_EEG_DATA> m_BufferData;

        StreamOutlet m_Outlet = null;

        StreamOutlet m_OutletRx = null;

        public MainWindow()
        {
            ConfigManager.Config = ConfigManager.Load("garant_eeg.json");

            InitializeComponent();

            le_IP.Text = ConfigManager.Config.IP;
            le_Port.Text = ConfigManager.Config.Port.ToString();
            cb_AutoReconnection.Checked = ConfigManager.Config.Autoreconnect;

            m_BufferData = new List<GARANT_EEG_DATA>();

            m_GarantEEG = new CGarantEEG();

            List<FilterInfo> filters = ConfigManager.Config.Filters;

            foreach (FilterInfo filter in filters)
            {
                m_GarantEEG.AddFilter(filter.Type, m_GarantEEG.GetRate(), filter.Frequency);
            }



            StreamInfo info = new StreamInfo("GarantEEG", "EEG", 8/*channels count*/, 500/*rate*/, channel_format_t.cf_float32, "GarantEEG");

            XMLElement channels = info.desc().append_child("channels");

            for (int i = 0; i < 8; i++)
            {
                channels.append_child("channel")
                    .append_child_value("label", string.Format("channel_{0}", i))
                    .append_child_value("type", "EEG")
                    .append_child_value("unit", "microvolts");
            }

            info.desc().append_child("acquisition")
                .append_child_value("manufacturer", "Neurotrend");

             m_Outlet = new StreamOutlet(info);



            StreamInfo infoRx = new StreamInfo("GarantEEG.Resistance", "EEG.Resistance", 10/*channels count*/, 10/*rate*/, channel_format_t.cf_float32, "GarantEEG.Resistance");

            XMLElement channelsRx = infoRx.desc().append_child("channels");

            for (int i = 0; i < 10; i++)
            {
                channelsRx.append_child("channel")
                    .append_child_value("label", string.Format("channel_rx_{0}", i))
                    .append_child_value("type", "EEG.Resistance")
                    .append_child_value("unit", "kOhm");
            }

            infoRx.desc().append_child("acquisition")
                .append_child_value("manufacturer", "Neurotrend");

            m_OutletRx = new StreamOutlet(infoRx);



            m_GarantEEG.ConnectionStateChanged += OnConnectionStateChanged;
            m_GarantEEG.RecordingStateChanged += OnRecordingStateChanged;
            m_GarantEEG.ReceivedData += OnReceivedData;
            m_DataTimer.Tick += OnUpdateDataTimer;

            m_DataTimer.Interval = 100;
            m_DataTimer.Start();
        }

        public void OnConnectionStateChanged(object sender, int code)
        {
        }

        public void OnRecordingStateChanged(object sender, int code)
        {
        }

        public void OnReceivedData(object sender, GARANT_EEG_DATA eegData)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted())
                return;

            if (eegData.DataRecordsCount > 0)
            {
                m_Mutex.WaitOne();

                m_BufferData.Add(eegData);

                m_Mutex.ReleaseMutex();
            }
        }

        public void OnUpdateDataTimer(object sender, EventArgs e)
        {
            m_Mutex.WaitOne();

            //Debug.WriteLine("OnUpdateDataTimer {0}", m_BufferData.Count);

            if (m_BufferData.Count > 0)
            {
                float[] data = new float[8];
                float[] dataRx = new float[10];
                bool useFilters = (ConfigManager.Config.UseFilters && m_GarantEEG.GetFiltersCount() != 0);

                for (int di = 0; di < m_BufferData.Count; di++)
                {
                    GARANT_EEG_DATA eegData = m_BufferData[di];

                    for (int j = 0; j < eegData.DataRecordsCount; j++)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            data[i] = (float)(useFilters ? eegData.FilteredChannelsData[j].Value[i] : eegData.RawChannelsData[j].Value[i]);
                        }

                        m_Outlet.push_sample(data);
                    }

                    for (int i = 0; i < 8; i++)
                        dataRx[i] = (float)eegData.ResistanceData.Value[i];

                    dataRx[8] = (float)eegData.ResistanceData.Ref;
                    dataRx[9] = (float)eegData.ResistanceData.Ground;

                    m_OutletRx.push_sample(dataRx);
                }

                m_BufferData.Clear();
            }

            if (m_GarantEEG != null)
            {
                pb_Progress.Value = m_GarantEEG.GetBatteryStatus();
                label1.Text = string.Format("{0}% battery", m_GarantEEG.GetBatteryStatus());
            }

            m_Mutex.ReleaseMutex();
        }

        private void le_IP_TextChanged(object sender, EventArgs e)
        {
            TextBox control = (TextBox)sender;
            ConfigManager.Config.IP = control.Text;
        }

        private void le_Port_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown control = (NumericUpDown)sender;
            ConfigManager.Config.Port = (int)control.Value;
        }

        private void cb_AutoReconnection_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox control = (CheckBox)sender;
            ConfigManager.Config.Autoreconnect = control.Checked;

            if (m_GarantEEG != null)
                m_GarantEEG.SetAutoReconnection(ConfigManager.Config.Autoreconnect);
        }

        private void bt_Start_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null)
                return;

            int port = (int)le_Port.Value;

            if (m_GarantEEG.Start(true, 500, le_IP.Text, port))
            {
                Debug.WriteLine("started ok");
            }
            else
            {
                Debug.WriteLine("started ne ok");
            }
        }

        private void bt_Stop_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null)
                return;

            m_GarantEEG.Stop();
        }

        private void bt_Filters_Click(object sender, EventArgs e)
        {
            FiltersForm f = new FiltersForm();
            f.ShowDialog();
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            ConfigManager.Config.Save("garant_eeg.json");
        }
    }
}
