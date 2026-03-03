namespace LabReportGenerator
{
    partial class LabReportGUI
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
            this.lblTitle = new System.Windows.Forms.Label();
            this.txtTitle = new System.Windows.Forms.TextBox();
            this.lblDiscipline = new System.Windows.Forms.Label();
            this.cmbDiscipline = new System.Windows.Forms.ComboBox();
            this.lblStudent = new System.Windows.Forms.Label();
            this.txtStudent = new System.Windows.Forms.TextBox();
            this.lblGroup = new System.Windows.Forms.Label();
            this.txtGroup = new System.Windows.Forms.TextBox();
            this.lblGoal = new System.Windows.Forms.Label();
            this.txtGoal = new System.Windows.Forms.TextBox();
            this.lblTask = new System.Windows.Forms.Label();
            this.txtTask = new System.Windows.Forms.TextBox();
            this.lblTheory = new System.Windows.Forms.Label();
            this.txtTheory = new System.Windows.Forms.TextBox();
            this.lblExperiment = new System.Windows.Forms.Label();
            this.txtExperiment = new System.Windows.Forms.TextBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.grpDynamic = new System.Windows.Forms.GroupBox();
            this.lblImageHint = new System.Windows.Forms.Label();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.picPreview = new System.Windows.Forms.PictureBox();
            this.lblCodeHint = new System.Windows.Forms.Label();
            this.rtbCode = new System.Windows.Forms.RichTextBox();
            this.grpMode = new System.Windows.Forms.GroupBox();
            this.radNoPattern = new System.Windows.Forms.RadioButton();
            this.radWithPattern = new System.Windows.Forms.RadioButton();
            this.btnGenerate = new System.Windows.Forms.Button();
            this.grpDynamic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picPreview)).BeginInit();
            this.grpMode.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblTitle
            // 
            this.lblTitle.AutoSize = true;
            this.lblTitle.Location = new System.Drawing.Point(12, 9);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(147, 20);
            this.lblTitle.TabIndex = 0;
            this.lblTitle.Text = "Название работы:";
            // 
            // txtTitle
            // 
            this.txtTitle.Location = new System.Drawing.Point(179, 9);
            this.txtTitle.Name = "txtTitle";
            this.txtTitle.Size = new System.Drawing.Size(158, 26);
            this.txtTitle.TabIndex = 1;
            // 
            // lblDiscipline
            // 
            this.lblDiscipline.AutoSize = true;
            this.lblDiscipline.Location = new System.Drawing.Point(29, 43);
            this.lblDiscipline.Name = "lblDiscipline";
            this.lblDiscipline.Size = new System.Drawing.Size(106, 20);
            this.lblDiscipline.TabIndex = 2;
            this.lblDiscipline.Text = "Дисциплина:";
            // 
            // cmbDiscipline
            // 
            this.cmbDiscipline.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbDiscipline.FormattingEnabled = true;
            this.cmbDiscipline.Items.AddRange(new object[] {
            "Базы данных",
            "Компьютерные сети",
            "Программирование"});
            this.cmbDiscipline.Location = new System.Drawing.Point(179, 43);
            this.cmbDiscipline.Name = "cmbDiscipline";
            this.cmbDiscipline.Size = new System.Drawing.Size(158, 28);
            this.cmbDiscipline.TabIndex = 3;
            // 
            // lblStudent
            // 
            this.lblStudent.AutoSize = true;
            this.lblStudent.Location = new System.Drawing.Point(30, 83);
            this.lblStudent.Name = "lblStudent";
            this.lblStudent.Size = new System.Drawing.Size(129, 20);
            this.lblStudent.TabIndex = 4;
            this.lblStudent.Text = "ФИО Студента:";
            // 
            // txtStudent
            // 
            this.txtStudent.Location = new System.Drawing.Point(179, 77);
            this.txtStudent.Name = "txtStudent";
            this.txtStudent.Size = new System.Drawing.Size(158, 26);
            this.txtStudent.TabIndex = 5;
            // 
            // lblGroup
            // 
            this.lblGroup.AutoSize = true;
            this.lblGroup.Location = new System.Drawing.Point(50, 115);
            this.lblGroup.Name = "lblGroup";
            this.lblGroup.Size = new System.Drawing.Size(65, 20);
            this.lblGroup.TabIndex = 6;
            this.lblGroup.Text = "Группа:";
            // 
            // txtGroup
            // 
            this.txtGroup.Location = new System.Drawing.Point(179, 109);
            this.txtGroup.Name = "txtGroup";
            this.txtGroup.Size = new System.Drawing.Size(158, 26);
            this.txtGroup.TabIndex = 7;
            // 
            // lblGoal
            // 
            this.lblGoal.AutoSize = true;
            this.lblGoal.Location = new System.Drawing.Point(60, 151);
            this.lblGoal.Name = "lblGoal";
            this.lblGoal.Size = new System.Drawing.Size(53, 20);
            this.lblGoal.TabIndex = 8;
            this.lblGoal.Text = "Цель:";
            // 
            // txtGoal
            // 
            this.txtGoal.Location = new System.Drawing.Point(179, 145);
            this.txtGoal.Name = "txtGoal";
            this.txtGoal.Size = new System.Drawing.Size(158, 26);
            this.txtGoal.TabIndex = 9;
            // 
            // lblTask
            // 
            this.lblTask.AutoSize = true;
            this.lblTask.Location = new System.Drawing.Point(48, 185);
            this.lblTask.Name = "lblTask";
            this.lblTask.Size = new System.Drawing.Size(80, 20);
            this.lblTask.TabIndex = 10;
            this.lblTask.Text = "Задание:";
            // 
            // txtTask
            // 
            this.txtTask.Location = new System.Drawing.Point(179, 185);
            this.txtTask.Name = "txtTask";
            this.txtTask.Size = new System.Drawing.Size(158, 26);
            this.txtTask.TabIndex = 11;
            // 
            // lblTheory
            // 
            this.lblTheory.AutoSize = true;
            this.lblTheory.Location = new System.Drawing.Point(50, 225);
            this.lblTheory.Name = "lblTheory";
            this.lblTheory.Size = new System.Drawing.Size(67, 20);
            this.lblTheory.TabIndex = 12;
            this.lblTheory.Text = "Теория:";
            // 
            // txtTheory
            // 
            this.txtTheory.Location = new System.Drawing.Point(179, 222);
            this.txtTheory.Multiline = true;
            this.txtTheory.Name = "txtTheory";
            this.txtTheory.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtTheory.Size = new System.Drawing.Size(158, 26);
            this.txtTheory.TabIndex = 13;
            // 
            // lblExperiment
            // 
            this.lblExperiment.AutoSize = true;
            this.lblExperiment.Location = new System.Drawing.Point(12, 258);
            this.lblExperiment.Name = "lblExperiment";
            this.lblExperiment.Size = new System.Drawing.Size(199, 20);
            this.lblExperiment.TabIndex = 14;
            this.lblExperiment.Text = "Описание экспиремента:";
            // 
            // txtExperiment
            // 
            this.txtExperiment.Location = new System.Drawing.Point(210, 258);
            this.txtExperiment.Multiline = true;
            this.txtExperiment.Name = "txtExperiment";
            this.txtExperiment.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtExperiment.Size = new System.Drawing.Size(127, 26);
            this.txtExperiment.TabIndex = 15;
            // 
            // grpDynamic
            // 
            this.grpDynamic.Controls.Add(this.rtbCode);
            this.grpDynamic.Controls.Add(this.lblCodeHint);
            this.grpDynamic.Controls.Add(this.picPreview);
            this.grpDynamic.Controls.Add(this.btnBrowse);
            this.grpDynamic.Controls.Add(this.lblImageHint);
            this.grpDynamic.Location = new System.Drawing.Point(33, 313);
            this.grpDynamic.Name = "grpDynamic";
            this.grpDynamic.Size = new System.Drawing.Size(430, 213);
            this.grpDynamic.TabIndex = 16;
            this.grpDynamic.TabStop = false;
            this.grpDynamic.Text = "Доп. данные";
            // 
            // lblImageHint
            // 
            this.lblImageHint.AutoSize = true;
            this.lblImageHint.Location = new System.Drawing.Point(19, 31);
            this.lblImageHint.Name = "lblImageHint";
            this.lblImageHint.Size = new System.Drawing.Size(151, 20);
            this.lblImageHint.TabIndex = 0;
            this.lblImageHint.Text = "Прикрепите схему:";
            this.lblImageHint.Visible = false;
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(358, 32);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(35, 25);
            this.btnBrowse.TabIndex = 2;
            this.btnBrowse.Text = "...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Visible = false;
            // 
            // picPreview
            // 
            this.picPreview.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.picPreview.Location = new System.Drawing.Point(188, 32);
            this.picPreview.Name = "picPreview";
            this.picPreview.Size = new System.Drawing.Size(153, 25);
            this.picPreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picPreview.TabIndex = 3;
            this.picPreview.TabStop = false;
            this.picPreview.Visible = false;
            // 
            // lblCodeHint
            // 
            this.lblCodeHint.AutoSize = true;
            this.lblCodeHint.Location = new System.Drawing.Point(27, 70);
            this.lblCodeHint.Name = "lblCodeHint";
            this.lblCodeHint.Size = new System.Drawing.Size(118, 20);
            this.lblCodeHint.TabIndex = 4;
            this.lblCodeHint.Text = "Вставьте код:";
            this.lblCodeHint.Visible = false;
            // 
            // rtbCode
            // 
            this.rtbCode.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.rtbCode.Font = new System.Drawing.Font("Consolas", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.rtbCode.Location = new System.Drawing.Point(188, 80);
            this.rtbCode.Name = "rtbCode";
            this.rtbCode.Size = new System.Drawing.Size(153, 96);
            this.rtbCode.TabIndex = 5;
            this.rtbCode.Text = "";
            this.rtbCode.Visible = false;
            this.rtbCode.WordWrap = false;
            // 
            // grpMode
            // 
            this.grpMode.Controls.Add(this.radWithPattern);
            this.grpMode.Controls.Add(this.radNoPattern);
            this.grpMode.Location = new System.Drawing.Point(450, 43);
            this.grpMode.Name = "grpMode";
            this.grpMode.Size = new System.Drawing.Size(200, 128);
            this.grpMode.TabIndex = 6;
            this.grpMode.TabStop = false;
            this.grpMode.Text = "Режим работы";
            // 
            // radNoPattern
            // 
            this.radNoPattern.AutoSize = true;
            this.radNoPattern.Checked = true;
            this.radNoPattern.Location = new System.Drawing.Point(21, 34);
            this.radNoPattern.Name = "radNoPattern";
            this.radNoPattern.Size = new System.Drawing.Size(138, 24);
            this.radNoPattern.TabIndex = 0;
            this.radNoPattern.TabStop = true;
            this.radNoPattern.Text = "Без паттерна";
            this.radNoPattern.UseVisualStyleBackColor = true;
            // 
            // radWithPattern
            // 
            this.radWithPattern.AutoSize = true;
            this.radWithPattern.Location = new System.Drawing.Point(21, 70);
            this.radWithPattern.Name = "radWithPattern";
            this.radWithPattern.Size = new System.Drawing.Size(132, 24);
            this.radWithPattern.TabIndex = 1;
            this.radWithPattern.TabStop = true;
            this.radWithPattern.Text = "С паттерном";
            this.radWithPattern.UseVisualStyleBackColor = true;
            // 
            // btnGenerate
            // 
            this.btnGenerate.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnGenerate.Location = new System.Drawing.Point(463, 207);
            this.btnGenerate.Name = "btnGenerate";
            this.btnGenerate.Size = new System.Drawing.Size(173, 56);
            this.btnGenerate.TabIndex = 2;
            this.btnGenerate.Text = "Сгенерировать отчет";
            this.btnGenerate.UseVisualStyleBackColor = false;
            // 
            // LabReportGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.ClientSize = new System.Drawing.Size(695, 554);
            this.Controls.Add(this.btnGenerate);
            this.Controls.Add(this.grpMode);
            this.Controls.Add(this.grpDynamic);
            this.Controls.Add(this.txtExperiment);
            this.Controls.Add(this.lblExperiment);
            this.Controls.Add(this.txtTheory);
            this.Controls.Add(this.lblTheory);
            this.Controls.Add(this.txtTask);
            this.Controls.Add(this.lblTask);
            this.Controls.Add(this.txtGoal);
            this.Controls.Add(this.lblGoal);
            this.Controls.Add(this.txtGroup);
            this.Controls.Add(this.lblGroup);
            this.Controls.Add(this.txtStudent);
            this.Controls.Add(this.lblStudent);
            this.Controls.Add(this.cmbDiscipline);
            this.Controls.Add(this.lblDiscipline);
            this.Controls.Add(this.txtTitle);
            this.Controls.Add(this.lblTitle);
            this.Name = "LabReportGUI";
            this.Text = "Генератор отчетов";
            this.grpDynamic.ResumeLayout(false);
            this.grpDynamic.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picPreview)).EndInit();
            this.grpMode.ResumeLayout(false);
            this.grpMode.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblTitle;
        private System.Windows.Forms.TextBox txtTitle;
        private System.Windows.Forms.Label lblDiscipline;
        private System.Windows.Forms.ComboBox cmbDiscipline;
        private System.Windows.Forms.Label lblStudent;
        private System.Windows.Forms.TextBox txtStudent;
        private System.Windows.Forms.Label lblGroup;
        private System.Windows.Forms.TextBox txtGroup;
        private System.Windows.Forms.Label lblGoal;
        private System.Windows.Forms.TextBox txtGoal;
        private System.Windows.Forms.Label lblTask;
        private System.Windows.Forms.TextBox txtTask;
        private System.Windows.Forms.Label lblTheory;
        private System.Windows.Forms.TextBox txtTheory;
        private System.Windows.Forms.Label lblExperiment;
        private System.Windows.Forms.TextBox txtExperiment;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.GroupBox grpDynamic;
        private System.Windows.Forms.Label lblImageHint;
        private System.Windows.Forms.RichTextBox rtbCode;
        private System.Windows.Forms.Label lblCodeHint;
        private System.Windows.Forms.PictureBox picPreview;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.GroupBox grpMode;
        private System.Windows.Forms.RadioButton radWithPattern;
        private System.Windows.Forms.RadioButton radNoPattern;
        private System.Windows.Forms.Button btnGenerate;
    }
}

