
namespace GarantEEG_SignalsHub
{
    partial class MainWindow
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.pb_Progress = new System.Windows.Forms.ProgressBar();
            this.bt_Filters = new System.Windows.Forms.Button();
            this.bt_Stop = new System.Windows.Forms.Button();
            this.bt_Start = new System.Windows.Forms.Button();
            this.cb_AutoReconnection = new System.Windows.Forms.CheckBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.le_Port = new System.Windows.Forms.NumericUpDown();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.le_IP = new System.Windows.Forms.TextBox();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.le_Port)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.pb_Progress);
            this.groupBox2.Controls.Add(this.bt_Filters);
            this.groupBox2.Controls.Add(this.bt_Stop);
            this.groupBox2.Controls.Add(this.bt_Start);
            this.groupBox2.Controls.Add(this.cb_AutoReconnection);
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(0, 0);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(1);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(0);
            this.groupBox2.Size = new System.Drawing.Size(451, 132);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(366, 62);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "0% battery";
            // 
            // pb_Progress
            // 
            this.pb_Progress.Location = new System.Drawing.Point(207, 54);
            this.pb_Progress.Name = "pb_Progress";
            this.pb_Progress.Size = new System.Drawing.Size(156, 28);
            this.pb_Progress.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.pb_Progress.TabIndex = 3;
            // 
            // bt_Filters
            // 
            this.bt_Filters.Location = new System.Drawing.Point(52, 92);
            this.bt_Filters.Name = "bt_Filters";
            this.bt_Filters.Size = new System.Drawing.Size(99, 28);
            this.bt_Filters.TabIndex = 2;
            this.bt_Filters.Text = "Filters";
            this.bt_Filters.UseVisualStyleBackColor = true;
            this.bt_Filters.Click += new System.EventHandler(this.bt_Filters_Click);
            // 
            // bt_Stop
            // 
            this.bt_Stop.Location = new System.Drawing.Point(102, 54);
            this.bt_Stop.Name = "bt_Stop";
            this.bt_Stop.Size = new System.Drawing.Size(93, 28);
            this.bt_Stop.TabIndex = 2;
            this.bt_Stop.Text = "Stop";
            this.bt_Stop.UseVisualStyleBackColor = true;
            this.bt_Stop.Click += new System.EventHandler(this.bt_Stop_Click);
            // 
            // bt_Start
            // 
            this.bt_Start.Location = new System.Drawing.Point(3, 54);
            this.bt_Start.Name = "bt_Start";
            this.bt_Start.Size = new System.Drawing.Size(93, 28);
            this.bt_Start.TabIndex = 2;
            this.bt_Start.Text = "Start";
            this.bt_Start.UseVisualStyleBackColor = true;
            this.bt_Start.Click += new System.EventHandler(this.bt_Start_Click);
            // 
            // cb_AutoReconnection
            // 
            this.cb_AutoReconnection.AutoSize = true;
            this.cb_AutoReconnection.Location = new System.Drawing.Point(306, 25);
            this.cb_AutoReconnection.Name = "cb_AutoReconnection";
            this.cb_AutoReconnection.Size = new System.Drawing.Size(113, 17);
            this.cb_AutoReconnection.TabIndex = 1;
            this.cb_AutoReconnection.Text = "Auto reconnection";
            this.cb_AutoReconnection.UseVisualStyleBackColor = true;
            this.cb_AutoReconnection.CheckedChanged += new System.EventHandler(this.cb_AutoReconnection_CheckedChanged);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.le_Port);
            this.groupBox4.Location = new System.Drawing.Point(200, 8);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(99, 40);
            this.groupBox4.TabIndex = 0;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Port";
            // 
            // le_Port
            // 
            this.le_Port.Location = new System.Drawing.Point(7, 15);
            this.le_Port.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.le_Port.Name = "le_Port";
            this.le_Port.Size = new System.Drawing.Size(86, 20);
            this.le_Port.TabIndex = 0;
            this.le_Port.Value = new decimal(new int[] {
            12345,
            0,
            0,
            0});
            this.le_Port.ValueChanged += new System.EventHandler(this.le_Port_ValueChanged);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.le_IP);
            this.groupBox3.Location = new System.Drawing.Point(3, 8);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(191, 40);
            this.groupBox3.TabIndex = 0;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "IP";
            // 
            // le_IP
            // 
            this.le_IP.Location = new System.Drawing.Point(7, 15);
            this.le_IP.Name = "le_IP";
            this.le_IP.Size = new System.Drawing.Size(178, 20);
            this.le_IP.TabIndex = 0;
            this.le_IP.TextChanged += new System.EventHandler(this.le_IP_TextChanged);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(451, 132);
            this.Controls.Add(this.groupBox2);
            this.Name = "MainWindow";
            this.Text = "Garant EEG signals hub";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainWindow_FormClosing);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.le_Port)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ProgressBar pb_Progress;
        private System.Windows.Forms.Button bt_Filters;
        private System.Windows.Forms.Button bt_Stop;
        private System.Windows.Forms.Button bt_Start;
        private System.Windows.Forms.CheckBox cb_AutoReconnection;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.NumericUpDown le_Port;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox le_IP;
    }
}

