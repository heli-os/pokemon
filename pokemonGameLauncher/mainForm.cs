using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pokemonGameLauncher
{
    public partial class mainForm : MetroFramework.Forms.MetroForm
    {
        public mainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
 
        }

        private void userID_lb_Click(object sender, EventArgs e)
        {

        }

        private void metroTextBox1_Click(object sender, EventArgs e)
        {

        }

        private void userID_lb_Click_1(object sender, EventArgs e)
        {

        }

        private void metroTabControl1_TabIndexChanged(object sender, EventArgs e)
        {


        }

        private void metroTabControl1_Click(object sender, EventArgs e)
        {
            switch (metroTabControl1.SelectedIndex)
            {
                case 0:
                    login_userID_txt.TabStop = true;
                    login_userID_txt.TabIndex = 1;
                    login_userPW_txt.TabStop = true;
                    login_userPW_txt.TabIndex = 2;
                    login_Login_btn.TabStop = true;
                    login_Login_btn.TabIndex = 3;

                    regist_userID_txt.TabStop = false;
                    regist_userPW_txt.TabStop = false;
                    regist_userPW_Confirm_txt.TabStop = false;
                    regist_Register_btn.TabStop = false;
                    break;
                case 1:
                    login_userID_txt.TabStop = false;
                    login_userPW_txt.TabStop = false;
                    login_Login_btn.TabStop = false;

                    regist_userID_txt.TabStop = true;
                    regist_userID_txt.TabIndex = 1;

                    regist_userPW_txt.TabStop = true;
                    regist_userPW_txt.TabIndex = 2;

                    regist_userPW_Confirm_txt.TabStop = true;
                    regist_userPW_Confirm_txt.TabIndex = 3;

                    regist_Register_btn.TabStop = true;
                    regist_Register_btn.TabIndex = 4;
                    break;
            }
        }

        private void login_userID_txt_KeyPress(object sender, KeyPressEventArgs e)
        {
        }

        private void login_userID_txt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                login_Login_btn_Click(sender, EventArgs.Empty);
            }
        }

        private void login_Login_btn_Click(object sender, EventArgs e)
        {
            String callUrl = "http://ync.jupiterflow.com/pokemon/login";
            String[] data = new String[2];
            data[0] = login_userID_txt.Text;         // id
            data[1] = login_userPW_txt.Text;         // pw

            String postData = String.Format("userid={0}&userpw={1}", data[0], data[1]);


            HttpWebRequest httpWebRequest = (HttpWebRequest)WebRequest.Create(callUrl);
            // 인코딩 UTF-8
            byte[] sendData = UTF8Encoding.UTF8.GetBytes(postData);
            httpWebRequest.ContentType = "application/x-www-form-urlencoded; charset=UTF-8";
            httpWebRequest.Method = "POST";
            httpWebRequest.ContentLength = sendData.Length;
            Stream requestStream = httpWebRequest.GetRequestStream();
            requestStream.Write(sendData, 0, sendData.Length);
            requestStream.Close();
            HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            StreamReader streamReader = new StreamReader(httpWebResponse.GetResponseStream(), Encoding.GetEncoding("UTF-8"));
            string ret = streamReader.ReadToEnd();
            streamReader.Close();
            httpWebResponse.Close();

            if (ret.IndexOf("Login succeed") >= 0)
            {
                string userNo = ret.Split('[')[1].Split(']')[0];
                regist_userID_txt.Text = "";
                regist_userPW_txt.Text = "";
                regist_userPW_Confirm_txt.Text = "";
                MessageBox.Show("Login succeed");
                Process.Start(Application.StartupPath + @"\Pokemon_client.exe", userNo);
                Application.Exit();
            }else
            {
                MessageBox.Show(ret);
            }
        }

        private void login_userPW_txt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                login_Login_btn_Click(sender, EventArgs.Empty);
            }
        }

        private void regist_userID_txt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                regist_Register_btn_Click(sender, EventArgs.Empty);
            }
        }

        private void regist_Register_btn_Click(object sender, EventArgs e)
        {

            String callUrl = "http://ync.jupiterflow.com/pokemon/register";
            String[] data = new String[3];
            data[0] = regist_userID_txt.Text;         // id
            data[1] = regist_userPW_txt.Text;         // pw
            data[2] = regist_userPW_Confirm_txt.Text; // pw confirm

            String postData = String.Format("userid={0}&userpw={1}&userpw_confirm={2}", data[0], data[1], data[2]);
        

            HttpWebRequest httpWebRequest = (HttpWebRequest)WebRequest.Create(callUrl);
            // 인코딩 UTF-8
            byte[] sendData = UTF8Encoding.UTF8.GetBytes(postData);
            httpWebRequest.ContentType = "application/x-www-form-urlencoded; charset=UTF-8";
            httpWebRequest.Method = "POST";
            httpWebRequest.ContentLength = sendData.Length;
            Stream requestStream = httpWebRequest.GetRequestStream();
            requestStream.Write(sendData, 0, sendData.Length);
            requestStream.Close();
            HttpWebResponse httpWebResponse = (HttpWebResponse)httpWebRequest.GetResponse();
            StreamReader streamReader = new StreamReader(httpWebResponse.GetResponseStream(), Encoding.GetEncoding("UTF-8"));
            string ret = streamReader.ReadToEnd();
            streamReader.Close();
            httpWebResponse.Close();

            if(ret == "Register succeed")
            {
                regist_userID_txt.Text = "";
                regist_userPW_txt.Text = "";
                regist_userPW_Confirm_txt.Text = "";
            }

            MessageBox.Show(ret);
        }

        private void regist_userPW_txt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                regist_Register_btn_Click(sender, EventArgs.Empty);
            }
        }

        private void regist_userPW_Confirm_txt_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                regist_Register_btn_Click(sender, EventArgs.Empty);
            }
        }

        private void metroTabControl1_Layout(object sender, LayoutEventArgs e)
        {
            metroTabControl1.TabIndex = 0;
            switch (metroTabControl1.SelectedIndex)
            {
                case 0:
                    login_userID_txt.TabStop = true;
                    login_userID_txt.TabIndex = 1;
                    login_userPW_txt.TabStop = true;
                    login_userPW_txt.TabIndex = 2;
                    login_Login_btn.TabStop = true;
                    login_Login_btn.TabIndex = 3;

                    regist_userID_txt.TabStop = false;
                    regist_userPW_txt.TabStop = false;
                    regist_userPW_Confirm_txt.TabStop = false;
                    regist_Register_btn.TabStop = false;
                    break;
                case 1:
                    login_userID_txt.TabStop = false;
                    login_userPW_txt.TabStop = false;
                    login_Login_btn.TabStop = false;

                    regist_userID_txt.TabStop = true;
                    regist_userID_txt.TabIndex = 1;

                    regist_userPW_txt.TabStop = true;
                    regist_userPW_txt.TabIndex = 2;

                    regist_userPW_Confirm_txt.TabStop = true;
                    regist_userPW_Confirm_txt.TabIndex = 3;

                    regist_Register_btn.TabStop = true;
                    regist_Register_btn.TabIndex = 4;
                    break;
            }
        }
    }
}
