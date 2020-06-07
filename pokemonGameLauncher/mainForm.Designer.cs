namespace pokemonGameLauncher
{
    partial class mainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.metroTabControl1 = new MetroFramework.Controls.MetroTabControl();
            this.metroTabPage1 = new MetroFramework.Controls.MetroTabPage();
            this.login_Login_btn = new MetroFramework.Controls.MetroButton();
            this.metroLabel1 = new MetroFramework.Controls.MetroLabel();
            this.userID_lb = new MetroFramework.Controls.MetroLabel();
            this.login_userPW_txt = new MetroFramework.Controls.MetroTextBox();
            this.login_userID_txt = new MetroFramework.Controls.MetroTextBox();
            this.metroTabPage2 = new MetroFramework.Controls.MetroTabPage();
            this.regist_Register_btn = new MetroFramework.Controls.MetroButton();
            this.metroLabel4 = new MetroFramework.Controls.MetroLabel();
            this.metroLabel2 = new MetroFramework.Controls.MetroLabel();
            this.metroLabel3 = new MetroFramework.Controls.MetroLabel();
            this.regist_userPW_Confirm_txt = new MetroFramework.Controls.MetroTextBox();
            this.regist_userPW_txt = new MetroFramework.Controls.MetroTextBox();
            this.regist_userID_txt = new MetroFramework.Controls.MetroTextBox();
            this.metroTabControl1.SuspendLayout();
            this.metroTabPage1.SuspendLayout();
            this.metroTabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // metroTabControl1
            // 
            this.metroTabControl1.Controls.Add(this.metroTabPage1);
            this.metroTabControl1.Controls.Add(this.metroTabPage2);
            this.metroTabControl1.FontSize = MetroFramework.MetroTabControlSize.Tall;
            this.metroTabControl1.FontWeight = MetroFramework.MetroTabControlWeight.Bold;
            this.metroTabControl1.ItemSize = new System.Drawing.Size(140, 32);
            this.metroTabControl1.Location = new System.Drawing.Point(23, 63);
            this.metroTabControl1.Name = "metroTabControl1";
            this.metroTabControl1.SelectedIndex = 0;
            this.metroTabControl1.Size = new System.Drawing.Size(284, 209);
            this.metroTabControl1.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            this.metroTabControl1.TabIndex = 5;
            this.metroTabControl1.TabStop = false;
            this.metroTabControl1.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.metroTabControl1.TabIndexChanged += new System.EventHandler(this.metroTabControl1_TabIndexChanged);
            this.metroTabControl1.Click += new System.EventHandler(this.metroTabControl1_Click);
            this.metroTabControl1.Layout += new System.Windows.Forms.LayoutEventHandler(this.metroTabControl1_Layout);
            // 
            // metroTabPage1
            // 
            this.metroTabPage1.Controls.Add(this.login_Login_btn);
            this.metroTabPage1.Controls.Add(this.metroLabel1);
            this.metroTabPage1.Controls.Add(this.userID_lb);
            this.metroTabPage1.Controls.Add(this.login_userPW_txt);
            this.metroTabPage1.Controls.Add(this.login_userID_txt);
            this.metroTabPage1.HorizontalScrollbarBarColor = true;
            this.metroTabPage1.Location = new System.Drawing.Point(4, 36);
            this.metroTabPage1.Name = "metroTabPage1";
            this.metroTabPage1.Size = new System.Drawing.Size(276, 169);
            this.metroTabPage1.TabIndex = 0;
            this.metroTabPage1.Text = "LOGIN";
            this.metroTabPage1.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.metroTabPage1.VerticalScrollbarBarColor = true;
            // 
            // login_Login_btn
            // 
            this.login_Login_btn.Location = new System.Drawing.Point(3, 113);
            this.login_Login_btn.Name = "login_Login_btn";
            this.login_Login_btn.Size = new System.Drawing.Size(270, 49);
            this.login_Login_btn.TabIndex = 3;
            this.login_Login_btn.Text = "LOGIN";
            this.login_Login_btn.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.login_Login_btn.Click += new System.EventHandler(this.login_Login_btn_Click);
            // 
            // metroLabel1
            // 
            this.metroLabel1.AutoSize = true;
            this.metroLabel1.BackColor = System.Drawing.Color.Transparent;
            this.metroLabel1.FontSize = MetroFramework.MetroLabelSize.Tall;
            this.metroLabel1.FontWeight = MetroFramework.MetroLabelWeight.Bold;
            this.metroLabel1.ForeColor = System.Drawing.Color.White;
            this.metroLabel1.Location = new System.Drawing.Point(3, 66);
            this.metroLabel1.Name = "metroLabel1";
            this.metroLabel1.Size = new System.Drawing.Size(91, 25);
            this.metroLabel1.TabIndex = 0;
            this.metroLabel1.Text = "USER PW";
            this.metroLabel1.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.metroLabel1.Click += new System.EventHandler(this.userID_lb_Click_1);
            // 
            // userID_lb
            // 
            this.userID_lb.AutoSize = true;
            this.userID_lb.BackColor = System.Drawing.Color.Transparent;
            this.userID_lb.FontSize = MetroFramework.MetroLabelSize.Tall;
            this.userID_lb.FontWeight = MetroFramework.MetroLabelWeight.Bold;
            this.userID_lb.ForeColor = System.Drawing.Color.White;
            this.userID_lb.Location = new System.Drawing.Point(3, 20);
            this.userID_lb.Name = "userID_lb";
            this.userID_lb.Size = new System.Drawing.Size(81, 25);
            this.userID_lb.TabIndex = 0;
            this.userID_lb.Text = "USER ID";
            this.userID_lb.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.userID_lb.Click += new System.EventHandler(this.userID_lb_Click_1);
            // 
            // login_userPW_txt
            // 
            this.login_userPW_txt.FontSize = MetroFramework.MetroTextBoxSize.Medium;
            this.login_userPW_txt.FontWeight = MetroFramework.MetroTextBoxWeight.Bold;
            this.login_userPW_txt.Location = new System.Drawing.Point(100, 69);
            this.login_userPW_txt.Name = "login_userPW_txt";
            this.login_userPW_txt.PasswordChar = '*';
            this.login_userPW_txt.PromptText = "Input Your PW...";
            this.login_userPW_txt.Size = new System.Drawing.Size(173, 23);
            this.login_userPW_txt.TabIndex = 2;
            this.login_userPW_txt.KeyDown += new System.Windows.Forms.KeyEventHandler(this.login_userPW_txt_KeyDown);
            // 
            // login_userID_txt
            // 
            this.login_userID_txt.FontSize = MetroFramework.MetroTextBoxSize.Medium;
            this.login_userID_txt.FontWeight = MetroFramework.MetroTextBoxWeight.Bold;
            this.login_userID_txt.Location = new System.Drawing.Point(100, 23);
            this.login_userID_txt.Name = "login_userID_txt";
            this.login_userID_txt.PromptText = "Input Your ID...";
            this.login_userID_txt.Size = new System.Drawing.Size(173, 23);
            this.login_userID_txt.TabIndex = 1;
            this.login_userID_txt.KeyDown += new System.Windows.Forms.KeyEventHandler(this.login_userID_txt_KeyDown);
            this.login_userID_txt.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.login_userID_txt_KeyPress);
            // 
            // metroTabPage2
            // 
            this.metroTabPage2.Controls.Add(this.regist_Register_btn);
            this.metroTabPage2.Controls.Add(this.metroLabel4);
            this.metroTabPage2.Controls.Add(this.metroLabel2);
            this.metroTabPage2.Controls.Add(this.metroLabel3);
            this.metroTabPage2.Controls.Add(this.regist_userPW_Confirm_txt);
            this.metroTabPage2.Controls.Add(this.regist_userPW_txt);
            this.metroTabPage2.Controls.Add(this.regist_userID_txt);
            this.metroTabPage2.HorizontalScrollbarBarColor = true;
            this.metroTabPage2.Location = new System.Drawing.Point(4, 36);
            this.metroTabPage2.Name = "metroTabPage2";
            this.metroTabPage2.Size = new System.Drawing.Size(276, 169);
            this.metroTabPage2.TabIndex = 1;
            this.metroTabPage2.Text = "REGISTER";
            this.metroTabPage2.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.metroTabPage2.VerticalScrollbarBarColor = true;
            // 
            // regist_Register_btn
            // 
            this.regist_Register_btn.Location = new System.Drawing.Point(3, 113);
            this.regist_Register_btn.Name = "regist_Register_btn";
            this.regist_Register_btn.Size = new System.Drawing.Size(270, 49);
            this.regist_Register_btn.TabIndex = 7;
            this.regist_Register_btn.Text = "REGISTER";
            this.regist_Register_btn.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.regist_Register_btn.Click += new System.EventHandler(this.regist_Register_btn_Click);
            // 
            // metroLabel4
            // 
            this.metroLabel4.AutoSize = true;
            this.metroLabel4.BackColor = System.Drawing.Color.Transparent;
            this.metroLabel4.FontSize = MetroFramework.MetroLabelSize.Tall;
            this.metroLabel4.FontWeight = MetroFramework.MetroLabelWeight.Bold;
            this.metroLabel4.ForeColor = System.Drawing.Color.White;
            this.metroLabel4.Location = new System.Drawing.Point(3, 70);
            this.metroLabel4.Name = "metroLabel4";
            this.metroLabel4.Size = new System.Drawing.Size(114, 25);
            this.metroLabel4.TabIndex = 0;
            this.metroLabel4.Text = "PW Confirm";
            this.metroLabel4.Theme = MetroFramework.MetroThemeStyle.Dark;
            // 
            // metroLabel2
            // 
            this.metroLabel2.AutoSize = true;
            this.metroLabel2.BackColor = System.Drawing.Color.Transparent;
            this.metroLabel2.FontSize = MetroFramework.MetroLabelSize.Tall;
            this.metroLabel2.FontWeight = MetroFramework.MetroLabelWeight.Bold;
            this.metroLabel2.ForeColor = System.Drawing.Color.White;
            this.metroLabel2.Location = new System.Drawing.Point(3, 38);
            this.metroLabel2.Name = "metroLabel2";
            this.metroLabel2.Size = new System.Drawing.Size(91, 25);
            this.metroLabel2.TabIndex = 0;
            this.metroLabel2.Text = "USER PW";
            this.metroLabel2.Theme = MetroFramework.MetroThemeStyle.Dark;
            // 
            // metroLabel3
            // 
            this.metroLabel3.AutoSize = true;
            this.metroLabel3.BackColor = System.Drawing.Color.Transparent;
            this.metroLabel3.FontSize = MetroFramework.MetroLabelSize.Tall;
            this.metroLabel3.FontWeight = MetroFramework.MetroLabelWeight.Bold;
            this.metroLabel3.ForeColor = System.Drawing.Color.White;
            this.metroLabel3.Location = new System.Drawing.Point(3, 6);
            this.metroLabel3.Name = "metroLabel3";
            this.metroLabel3.Size = new System.Drawing.Size(81, 25);
            this.metroLabel3.TabIndex = 0;
            this.metroLabel3.Text = "USER ID";
            this.metroLabel3.Theme = MetroFramework.MetroThemeStyle.Dark;
            // 
            // regist_userPW_Confirm_txt
            // 
            this.regist_userPW_Confirm_txt.Location = new System.Drawing.Point(123, 73);
            this.regist_userPW_Confirm_txt.Name = "regist_userPW_Confirm_txt";
            this.regist_userPW_Confirm_txt.PasswordChar = '*';
            this.regist_userPW_Confirm_txt.PromptText = "Input new PW confirm...";
            this.regist_userPW_Confirm_txt.Size = new System.Drawing.Size(150, 23);
            this.regist_userPW_Confirm_txt.TabIndex = 6;
            this.regist_userPW_Confirm_txt.KeyDown += new System.Windows.Forms.KeyEventHandler(this.regist_userPW_Confirm_txt_KeyDown);
            // 
            // regist_userPW_txt
            // 
            this.regist_userPW_txt.Location = new System.Drawing.Point(123, 41);
            this.regist_userPW_txt.Name = "regist_userPW_txt";
            this.regist_userPW_txt.PasswordChar = '*';
            this.regist_userPW_txt.PromptText = "Input new PW...";
            this.regist_userPW_txt.Size = new System.Drawing.Size(150, 23);
            this.regist_userPW_txt.TabIndex = 5;
            this.regist_userPW_txt.KeyDown += new System.Windows.Forms.KeyEventHandler(this.regist_userPW_txt_KeyDown);
            // 
            // regist_userID_txt
            // 
            this.regist_userID_txt.Location = new System.Drawing.Point(123, 9);
            this.regist_userID_txt.Name = "regist_userID_txt";
            this.regist_userID_txt.PromptText = "Input new ID...";
            this.regist_userID_txt.Size = new System.Drawing.Size(150, 23);
            this.regist_userID_txt.TabIndex = 4;
            this.regist_userID_txt.KeyDown += new System.Windows.Forms.KeyEventHandler(this.regist_userID_txt_KeyDown);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(330, 295);
            this.Controls.Add(this.metroTabControl1);
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.Resizable = false;
            this.Text = "Pokemon Launcher";
            this.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.metroTabControl1.ResumeLayout(false);
            this.metroTabPage1.ResumeLayout(false);
            this.metroTabPage1.PerformLayout();
            this.metroTabPage2.ResumeLayout(false);
            this.metroTabPage2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private MetroFramework.Controls.MetroTabControl metroTabControl1;
        private MetroFramework.Controls.MetroTabPage metroTabPage1;
        private MetroFramework.Controls.MetroLabel userID_lb;
        private MetroFramework.Controls.MetroTextBox login_userID_txt;
        private MetroFramework.Controls.MetroTabPage metroTabPage2;
        private MetroFramework.Controls.MetroButton login_Login_btn;
        private MetroFramework.Controls.MetroLabel metroLabel1;
        private MetroFramework.Controls.MetroTextBox login_userPW_txt;
        private MetroFramework.Controls.MetroButton regist_Register_btn;
        private MetroFramework.Controls.MetroLabel metroLabel4;
        private MetroFramework.Controls.MetroLabel metroLabel2;
        private MetroFramework.Controls.MetroLabel metroLabel3;
        private MetroFramework.Controls.MetroTextBox regist_userPW_Confirm_txt;
        private MetroFramework.Controls.MetroTextBox regist_userPW_txt;
        private MetroFramework.Controls.MetroTextBox regist_userID_txt;
    }
}

