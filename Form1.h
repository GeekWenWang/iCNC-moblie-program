#pragma once
#include "DEC\INC\Dec.h"
#include "MMI\INC\MMI.h"
#include "CNC\INC\cnc.h"
#include <string.h>

char serialCmd[3];


double counter;

extern CNC_DATA* cncDataPtr;

namespace iCNC_103020033 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports; 

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_start;
	private: System::Windows::Forms::Label^  label_X;
	private: System::Windows::Forms::Label^  label_X_Position;
	protected: 


	private: System::Windows::Forms::Label^  label_Y;
	private: System::Windows::Forms::Label^  label_Y_Position;



	private: System::Windows::Forms::Label^  label_t;
	private: System::Windows::Forms::Label^  label_T_Pass;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Timer^  timer_rtime;

	private: System::Windows::Forms::Button^  button_forward;
	private: System::Windows::Forms::Button^  button_CCW;
	private: System::Windows::Forms::Button^  button_CW;
	private: System::Windows::Forms::Button^  button_backward;
	private: System::Windows::Forms::Button^  button_Jog;
	private: System::Windows::Forms::Button^  button_Mem;
	private: System::Windows::Forms::RichTextBox^  richTextBox_ncFile;
	private: System::Windows::Forms::Button^  button_openFile;








	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Label^  label_Com;
	private: System::Windows::Forms::Label^  label_baudrate;


	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Button^  button_initCom;
	private: System::Windows::Forms::Button^  button_closeCom;


	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog_openNC;

	private: System::Windows::Forms::TextBox^  textBox_filePath;
	private: System::Windows::Forms::Label^  label_read;
	private: System::Windows::Forms::Label^  label_write;


	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  Button_send_Serial;
	private: System::Windows::Forms::Button^  button_stop;
	private: System::Windows::Forms::Timer^  nrtime;
	private: System::Windows::Forms::Label^  label_theta;
	private: System::Windows::Forms::Label^  label_theta_pos;
	private: System::Windows::Forms::Button^  button_reset;
	private: System::Windows::Forms::Label^  label_head;
	private: System::Windows::Forms::Label^  label_head_pos;
	private: System::Windows::Forms::Label^  label_serialCmd_1;
	private: System::Windows::Forms::Label^  label_serialCmd_2;
	private: System::Windows::Forms::Label^  label_show_serialCmd_1;
	private: System::Windows::Forms::Label^  label_show_serialCmd_2;





	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button_stop = (gcnew System::Windows::Forms::Button());
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->label_X = (gcnew System::Windows::Forms::Label());
			this->label_X_Position = (gcnew System::Windows::Forms::Label());
			this->label_Y = (gcnew System::Windows::Forms::Label());
			this->label_Y_Position = (gcnew System::Windows::Forms::Label());
			this->label_t = (gcnew System::Windows::Forms::Label());
			this->label_T_Pass = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->timer_rtime = (gcnew System::Windows::Forms::Timer(this->components));
			this->button_forward = (gcnew System::Windows::Forms::Button());
			this->button_CCW = (gcnew System::Windows::Forms::Button());
			this->button_CW = (gcnew System::Windows::Forms::Button());
			this->button_backward = (gcnew System::Windows::Forms::Button());
			this->button_Jog = (gcnew System::Windows::Forms::Button());
			this->button_Mem = (gcnew System::Windows::Forms::Button());
			this->richTextBox_ncFile = (gcnew System::Windows::Forms::RichTextBox());
			this->button_openFile = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label_Com = (gcnew System::Windows::Forms::Label());
			this->label_baudrate = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button_initCom = (gcnew System::Windows::Forms::Button());
			this->button_closeCom = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->openFileDialog_openNC = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox_filePath = (gcnew System::Windows::Forms::TextBox());
			this->label_read = (gcnew System::Windows::Forms::Label());
			this->label_write = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->Button_send_Serial = (gcnew System::Windows::Forms::Button());
			this->nrtime = (gcnew System::Windows::Forms::Timer(this->components));
			this->label_theta = (gcnew System::Windows::Forms::Label());
			this->label_theta_pos = (gcnew System::Windows::Forms::Label());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->label_head = (gcnew System::Windows::Forms::Label());
			this->label_head_pos = (gcnew System::Windows::Forms::Label());
			this->label_serialCmd_1 = (gcnew System::Windows::Forms::Label());
			this->label_serialCmd_2 = (gcnew System::Windows::Forms::Label());
			this->label_show_serialCmd_1 = (gcnew System::Windows::Forms::Label());
			this->label_show_serialCmd_2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button_stop
			// 
			this->button_stop->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button_stop->Location = System::Drawing::Point(119, 111);
			this->button_stop->Name = L"button_stop";
			this->button_stop->Size = System::Drawing::Size(75, 32);
			this->button_stop->TabIndex = 8;
			this->button_stop->Text = L"stop";
			this->button_stop->UseVisualStyleBackColor = true;
			this->button_stop->Click += gcnew System::EventHandler(this, &Form1::button_stop_Click);
			// 
			// button_start
			// 
			this->button_start->AutoSize = true;
			this->button_start->Location = System::Drawing::Point(12, 111);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(72, 32);
			this->button_start->TabIndex = 0;
			this->button_start->Text = L"start";
			this->button_start->UseVisualStyleBackColor = true;
			this->button_start->Click += gcnew System::EventHandler(this, &Form1::button_start_Click);
			// 
			// label_X
			// 
			this->label_X->AutoSize = true;
			this->label_X->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->label_X->Location = System::Drawing::Point(27, 18);
			this->label_X->Name = L"label_X";
			this->label_X->Size = System::Drawing::Size(19, 16);
			this->label_X->TabIndex = 1;
			this->label_X->Text = L"X";
			this->label_X->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label_X_Position
			// 
			this->label_X_Position->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_X_Position->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->label_X_Position->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label_X_Position->Location = System::Drawing::Point(94, 18);
			this->label_X_Position->Name = L"label_X_Position";
			this->label_X_Position->Size = System::Drawing::Size(64, 16);
			this->label_X_Position->TabIndex = 2;
			this->label_X_Position->Text = L"0";
			// 
			// label_Y
			// 
			this->label_Y->AutoSize = true;
			this->label_Y->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->label_Y->Location = System::Drawing::Point(27, 48);
			this->label_Y->Name = L"label_Y";
			this->label_Y->Size = System::Drawing::Size(19, 16);
			this->label_Y->TabIndex = 3;
			this->label_Y->Text = L"Y";
			// 
			// label_Y_Position
			// 
			this->label_Y_Position->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_Y_Position->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->label_Y_Position->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label_Y_Position->Location = System::Drawing::Point(94, 48);
			this->label_Y_Position->Name = L"label_Y_Position";
			this->label_Y_Position->Size = System::Drawing::Size(64, 16);
			this->label_Y_Position->TabIndex = 4;
			this->label_Y_Position->Text = L"0";
			// 
			// label_t
			// 
			this->label_t->AutoSize = true;
			this->label_t->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->label_t->Location = System::Drawing::Point(27, 75);
			this->label_t->Name = L"label_t";
			this->label_t->Size = System::Drawing::Size(12, 16);
			this->label_t->TabIndex = 5;
			this->label_t->Text = L"t";
			// 
			// label_T_Pass
			// 
			this->label_T_Pass->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_T_Pass->Font = (gcnew System::Drawing::Font(L"新細明體", 12));
			this->label_T_Pass->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label_T_Pass->Location = System::Drawing::Point(94, 75);
			this->label_T_Pass->Name = L"label_T_Pass";
			this->label_T_Pass->Size = System::Drawing::Size(64, 18);
			this->label_T_Pass->TabIndex = 6;
			this->label_T_Pass->Text = L"0";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label_X);
			this->groupBox1->Controls->Add(this->label_T_Pass);
			this->groupBox1->Controls->Add(this->label_X_Position);
			this->groupBox1->Controls->Add(this->label_Y_Position);
			this->groupBox1->Controls->Add(this->label_t);
			this->groupBox1->Controls->Add(this->label_Y);
			this->groupBox1->Location = System::Drawing::Point(12, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(172, 105);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"groupBox1";
			// 
			// timer_rtime
			// 
			this->timer_rtime->Interval = 25;
			this->timer_rtime->Tick += gcnew System::EventHandler(this, &Form1::timer_rtime_Tick);
			// 
			// button_forward
			// 
			this->button_forward->Enabled = false;
			this->button_forward->Location = System::Drawing::Point(65, 149);
			this->button_forward->Name = L"button_forward";
			this->button_forward->Size = System::Drawing::Size(75, 23);
			this->button_forward->TabIndex = 9;
			this->button_forward->Text = L"forward";
			this->button_forward->UseVisualStyleBackColor = true;
			this->button_forward->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_forward_mousedown);
			this->button_forward->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_forward_mouseup);
			// 
			// button_CCW
			// 
			this->button_CCW->Enabled = false;
			this->button_CCW->Location = System::Drawing::Point(9, 178);
			this->button_CCW->Name = L"button_CCW";
			this->button_CCW->Size = System::Drawing::Size(75, 23);
			this->button_CCW->TabIndex = 10;
			this->button_CCW->Text = L"CCW";
			this->button_CCW->UseVisualStyleBackColor = true;
			this->button_CCW->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_forward_mousedown);
			this->button_CCW->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_CCW_mouseup);
			// 
			// button_CW
			// 
			this->button_CW->Enabled = false;
			this->button_CW->Location = System::Drawing::Point(119, 178);
			this->button_CW->Name = L"button_CW";
			this->button_CW->Size = System::Drawing::Size(75, 23);
			this->button_CW->TabIndex = 11;
			this->button_CW->Text = L"CW";
			this->button_CW->UseVisualStyleBackColor = true;
			this->button_CW->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_CW_mousedown);
			this->button_CW->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_CW_mouseup);
			// 
			// button_backward
			// 
			this->button_backward->Enabled = false;
			this->button_backward->Location = System::Drawing::Point(65, 207);
			this->button_backward->Name = L"button_backward";
			this->button_backward->Size = System::Drawing::Size(75, 23);
			this->button_backward->TabIndex = 12;
			this->button_backward->Text = L"backward";
			this->button_backward->UseVisualStyleBackColor = true;
			this->button_backward->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_backward_mousedown);
			this->button_backward->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Button_backward_mouseup);
			// 
			// button_Jog
			// 
			this->button_Jog->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->button_Jog->Location = System::Drawing::Point(41, 285);
			this->button_Jog->Name = L"button_Jog";
			this->button_Jog->Size = System::Drawing::Size(129, 35);
			this->button_Jog->TabIndex = 13;
			this->button_Jog->Text = L"JOG";
			this->button_Jog->UseVisualStyleBackColor = false;
			this->button_Jog->Click += gcnew System::EventHandler(this, &Form1::button_Jog_Click);
			// 
			// button_Mem
			// 
			this->button_Mem->Location = System::Drawing::Point(282, 285);
			this->button_Mem->Name = L"button_Mem";
			this->button_Mem->Size = System::Drawing::Size(126, 35);
			this->button_Mem->TabIndex = 14;
			this->button_Mem->Text = L"MEM";
			this->button_Mem->UseVisualStyleBackColor = true;
			this->button_Mem->Click += gcnew System::EventHandler(this, &Form1::button_Mem_Click);
			// 
			// richTextBox_ncFile
			// 
			this->richTextBox_ncFile->Location = System::Drawing::Point(232, 0);
			this->richTextBox_ncFile->Name = L"richTextBox_ncFile";
			this->richTextBox_ncFile->Size = System::Drawing::Size(232, 113);
			this->richTextBox_ncFile->TabIndex = 15;
			this->richTextBox_ncFile->Text = L"";
			// 
			// button_openFile
			// 
			this->button_openFile->Location = System::Drawing::Point(232, 119);
			this->button_openFile->Name = L"button_openFile";
			this->button_openFile->Size = System::Drawing::Size(43, 23);
			this->button_openFile->TabIndex = 16;
			this->button_openFile->Text = L"load";
			this->button_openFile->UseVisualStyleBackColor = true;
			this->button_openFile->Click += gcnew System::EventHandler(this, &Form1::button_openFile_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(232, 148);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(232, 24);
			this->progressBar1->TabIndex = 18;
			// 
			// label_Com
			// 
			this->label_Com->AutoSize = true;
			this->label_Com->Location = System::Drawing::Point(232, 188);
			this->label_Com->Name = L"label_Com";
			this->label_Com->Size = System::Drawing::Size(31, 12);
			this->label_Com->TabIndex = 19;
			this->label_Com->Text = L"COM";
			// 
			// label_baudrate
			// 
			this->label_baudrate->AutoSize = true;
			this->label_baudrate->Location = System::Drawing::Point(232, 217);
			this->label_baudrate->Name = L"label_baudrate";
			this->label_baudrate->Size = System::Drawing::Size(45, 12);
			this->label_baudrate->TabIndex = 20;
			this->label_baudrate->Text = L"baudrate";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(281, 181);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(111, 20);
			this->comboBox1->TabIndex = 21;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"9600", L"115200"});
			this->comboBox2->Location = System::Drawing::Point(281, 211);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(111, 20);
			this->comboBox2->TabIndex = 22;
			// 
			// button_initCom
			// 
			this->button_initCom->Location = System::Drawing::Point(398, 185);
			this->button_initCom->Name = L"button_initCom";
			this->button_initCom->Size = System::Drawing::Size(66, 18);
			this->button_initCom->TabIndex = 23;
			this->button_initCom->Text = L"Init COM";
			this->button_initCom->UseVisualStyleBackColor = true;
			this->button_initCom->Click += gcnew System::EventHandler(this, &Form1::button_initCom_Click);
			// 
			// button_closeCom
			// 
			this->button_closeCom->Location = System::Drawing::Point(398, 211);
			this->button_closeCom->Name = L"button_closeCom";
			this->button_closeCom->Size = System::Drawing::Size(66, 18);
			this->button_closeCom->TabIndex = 24;
			this->button_closeCom->Text = L"CloseCOM";
			this->button_closeCom->UseVisualStyleBackColor = true;
			this->button_closeCom->Click += gcnew System::EventHandler(this, &Form1::button_closeCom_Click);
			// 
			// openFileDialog_openNC
			// 
			this->openFileDialog_openNC->FileName = L"openFileDialog";
			// 
			// textBox_filePath
			// 
			this->textBox_filePath->Location = System::Drawing::Point(282, 119);
			this->textBox_filePath->Name = L"textBox_filePath";
			this->textBox_filePath->Size = System::Drawing::Size(182, 22);
			this->textBox_filePath->TabIndex = 25;
			// 
			// label_read
			// 
			this->label_read->AutoSize = true;
			this->label_read->Location = System::Drawing::Point(230, 239);
			this->label_read->Name = L"label_read";
			this->label_read->Size = System::Drawing::Size(25, 12);
			this->label_read->TabIndex = 26;
			this->label_read->Text = L"read";
			// 
			// label_write
			// 
			this->label_write->AutoSize = true;
			this->label_write->Location = System::Drawing::Point(230, 260);
			this->label_write->Name = L"label_write";
			this->label_write->Size = System::Drawing::Size(28, 12);
			this->label_write->TabIndex = 27;
			this->label_write->Text = L"write";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(282, 235);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(182, 22);
			this->textBox1->TabIndex = 28;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(281, 257);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 29;
			// 
			// Button_send_Serial
			// 
			this->Button_send_Serial->Location = System::Drawing::Point(398, 257);
			this->Button_send_Serial->Name = L"Button_send_Serial";
			this->Button_send_Serial->Size = System::Drawing::Size(66, 23);
			this->Button_send_Serial->TabIndex = 30;
			this->Button_send_Serial->Text = L"send";
			this->Button_send_Serial->UseVisualStyleBackColor = true;
			this->Button_send_Serial->Click += gcnew System::EventHandler(this, &Form1::Button_send_Serial_Click);
			// 
			// nrtime
			// 
			this->nrtime->Interval = 50;
			this->nrtime->Tick += gcnew System::EventHandler(this, &Form1::nrtime_Tick);
			// 
			// label_theta
			// 
			this->label_theta->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_theta->Location = System::Drawing::Point(471, 18);
			this->label_theta->Name = L"label_theta";
			this->label_theta->Size = System::Drawing::Size(48, 16);
			this->label_theta->TabIndex = 31;
			this->label_theta->Text = L"theta";
			// 
			// label_theta_pos
			// 
			this->label_theta_pos->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_theta_pos->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_theta_pos->ForeColor = System::Drawing::Color::Lime;
			this->label_theta_pos->Location = System::Drawing::Point(525, 18);
			this->label_theta_pos->Name = L"label_theta_pos";
			this->label_theta_pos->Size = System::Drawing::Size(54, 16);
			this->label_theta_pos->TabIndex = 32;
			this->label_theta_pos->Text = L"0.00";
			// 
			// button_reset
			// 
			this->button_reset->Location = System::Drawing::Point(65, 249);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(75, 30);
			this->button_reset->TabIndex = 33;
			this->button_reset->Text = L"reset";
			this->button_reset->UseVisualStyleBackColor = true;
			this->button_reset->Click += gcnew System::EventHandler(this, &Form1::button_reset_Click);
			// 
			// label_head
			// 
			this->label_head->AutoSize = true;
			this->label_head->Location = System::Drawing::Point(468, 48);
			this->label_head->Name = L"label_head";
			this->label_head->Size = System::Drawing::Size(51, 12);
			this->label_head->TabIndex = 34;
			this->label_head->Text = L"headPoint";
			// 
			// label_head_pos
			// 
			this->label_head_pos->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_head_pos->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_head_pos->ForeColor = System::Drawing::Color::LawnGreen;
			this->label_head_pos->Location = System::Drawing::Point(528, 48);
			this->label_head_pos->Name = L"label_head_pos";
			this->label_head_pos->Size = System::Drawing::Size(51, 16);
			this->label_head_pos->TabIndex = 35;
			this->label_head_pos->Text = L"0.00";
			// 
			// label_serialCmd_1
			// 
			this->label_serialCmd_1->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_serialCmd_1->Location = System::Drawing::Point(472, 148);
			this->label_serialCmd_1->Name = L"label_serialCmd_1";
			this->label_serialCmd_1->Size = System::Drawing::Size(61, 16);
			this->label_serialCmd_1->TabIndex = 36;
			this->label_serialCmd_1->Text = L"serialCmd1";
			// 
			// label_serialCmd_2
			// 
			this->label_serialCmd_2->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_serialCmd_2->Location = System::Drawing::Point(472, 178);
			this->label_serialCmd_2->Name = L"label_serialCmd_2";
			this->label_serialCmd_2->Size = System::Drawing::Size(61, 16);
			this->label_serialCmd_2->TabIndex = 37;
			this->label_serialCmd_2->Text = L"serialCmd2";
			// 
			// label_show_serialCmd_1
			// 
			this->label_show_serialCmd_1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_show_serialCmd_1->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_show_serialCmd_1->ForeColor = System::Drawing::Color::LawnGreen;
			this->label_show_serialCmd_1->Location = System::Drawing::Point(539, 145);
			this->label_show_serialCmd_1->Name = L"label_show_serialCmd_1";
			this->label_show_serialCmd_1->Size = System::Drawing::Size(51, 16);
			this->label_show_serialCmd_1->TabIndex = 38;
			this->label_show_serialCmd_1->Text = L"0.00";
			// 
			// label_show_serialCmd_2
			// 
			this->label_show_serialCmd_2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label_show_serialCmd_2->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_show_serialCmd_2->ForeColor = System::Drawing::Color::LawnGreen;
			this->label_show_serialCmd_2->Location = System::Drawing::Point(539, 175);
			this->label_show_serialCmd_2->Name = L"label_show_serialCmd_2";
			this->label_show_serialCmd_2->Size = System::Drawing::Size(51, 16);
			this->label_show_serialCmd_2->TabIndex = 39;
			this->label_show_serialCmd_2->Text = L"0.00";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(590, 358);
			this->Controls->Add(this->label_show_serialCmd_2);
			this->Controls->Add(this->label_show_serialCmd_1);
			this->Controls->Add(this->label_serialCmd_2);
			this->Controls->Add(this->label_serialCmd_1);
			this->Controls->Add(this->label_head_pos);
			this->Controls->Add(this->label_head);
			this->Controls->Add(this->button_reset);
			this->Controls->Add(this->label_theta_pos);
			this->Controls->Add(this->label_theta);
			this->Controls->Add(this->Button_send_Serial);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label_write);
			this->Controls->Add(this->label_read);
			this->Controls->Add(this->textBox_filePath);
			this->Controls->Add(this->button_closeCom);
			this->Controls->Add(this->button_initCom);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label_baudrate);
			this->Controls->Add(this->label_Com);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button_openFile);
			this->Controls->Add(this->richTextBox_ncFile);
			this->Controls->Add(this->button_Mem);
			this->Controls->Add(this->button_Jog);
			this->Controls->Add(this->button_backward);
			this->Controls->Add(this->button_CW);
			this->Controls->Add(this->button_CCW);
			this->Controls->Add(this->button_forward);
			this->Controls->Add(this->button_stop);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button_start);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
				 {
					// Getting port names for car control
					 cncInit();
					array<Object^>^ objectArray = SerialPort::GetPortNames();
					// add string array to combobox
					this->comboBox1->Items->AddRange( objectArray );  

					this->button_Mem->BackColor = Color::Red;
					//decDataPtr->decState = DEC_INIT;
				 }
private: System::Void button_start_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(cncDataPtr->mmiData.opMode != NULL_MODE)
			 {
				 if(cncDataPtr->mmiData.opMode == MEM_MODE)
				 {
					 if(this->openFileDialog_openNC->RestoreDirectory == false)
					 {
						 MessageBox::Show("請載入檔案後繼續" , "格式錯誤", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					 }
					 else
					 {
						this->timer_rtime->Enabled=true;
						this->nrtime->Enabled=true;
						cncDataPtr->mmiData.START = true;
					 }
				 }
				 else if(cncDataPtr->mmiData.opMode == JOG_MODE)
				 {
					 this->timer_rtime->Enabled=true;
					 this->nrtime->Enabled=true;
					 cncDataPtr->mmiData.START = true;
				 }
			 }
			 else
			 {
				 MessageBox::Show("請選擇MEM_MODE或JOG_MODE" , "格式錯誤", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			 }
		 }

private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void timer_rtime_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(cncDataPtr->linkData.linkToIntpData.cmdValid == true || cncDataPtr->intpData.cmdValid == true)
			 {
				rtMain(cncDataPtr);
			 }
			 

			 counter  = counter + 0.033;
			 this->label_T_Pass-> Text = (counter).ToString("00.0s");

			//if(cncDataPtr->intpData.cmdValid == true)
			 //{
				//(cncDataPtr->mmiData.counter) = (cncDataPtr->mmiData.counter) +0.1;
			//}

			 
			 
			 
			 
			 if(cncDataPtr->intpData.serialCmdValid == true)
			 {
				 serialCmd[0] = cncDataPtr->intpData.serialCmd[0];
				 serialCmd[1] = cncDataPtr->intpData.serialCmd[1];

				 this->label_show_serialCmd_1->Text = serialCmd[0].ToString("0.00");
				 this->label_show_serialCmd_2->Text = serialCmd[1].ToString("0.00");
				 cncDataPtr->intpData.serialCmdValid = false;
			 }

			 
			 				 //Create a timer and double click it to create function
				 String^ message = gcnew String(serialCmd , 0 , 2);  //Convert char(serailCmd) from 0 to 3 into system string for writing out
				 
				 if(this->serialPort1->IsOpen) //Using this to check serial port is opened or not
				 {
					 this->serialPort1->Write(message); //If serial port is opened, use this method to write out message
					 this->textBox1->Text=message; //Text box for showing message
				 }
				 else
				 {
					 this->textBox1->Text="Port Not Opened"; //Text box for showing message
				 }

				 this->label_X_Position->Text = cncDataPtr->intpData.carCoordinate[0].ToString("0.00");
				 this->label_Y_Position->Text = cncDataPtr->intpData.carCoordinate[1].ToString("0.00");
				 this->label_theta_pos->Text = cncDataPtr->intpData.carCoordinate[2].ToString("0.00");
				 this->label_head_pos->Text = cncDataPtr->intpData.headPointer.ToString("0.00");
				 
		 }

private: System::Void button_Mem_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			 cncDataPtr->mmiData.opMode = MEM_MODE;

			 this->button_forward->Enabled=false;
			 this->button_backward->Enabled=false;
			 this->button_CW->Enabled=false;
			 this->button_CCW->Enabled=false;

			 button_Mem->BackColor = Color::Red;
			 button_Jog->BackColor = Color::SteelBlue;
			 //button_MDI->BackColor = Color::SteelBlue;
		}

private: System::Void button_openFile_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  if(cncDataPtr->mmiData.opMode==MEM_MODE)  
			  {
				this->openFileDialog_openNC->InitialDirectory = " ";
				this->openFileDialog_openNC->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";
				this->openFileDialog_openNC->FilterIndex = 1;
				this->openFileDialog_openNC->DefaultExt = "*.txt";
				this->openFileDialog_openNC->FileName = "";
				this->openFileDialog_openNC->RestoreDirectory = true;
				if(this->openFileDialog_openNC->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->textBox_filePath->Text = openFileDialog_openNC->FileName;
					this->richTextBox_ncFile->LoadFile(openFileDialog_openNC->FileName , RichTextBoxStreamType::PlainText);
					strcpy(cncDataPtr->mmiData.ncFileName, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog_openNC->FileName));
					cncDataPtr->mmiData.ncFileValid = true;
				}
			  }
			  else
			  {
				  MessageBox::Show("請選擇MEM_MODE" , "格式錯誤", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			  }
		  }




private: System::Void button_stop_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->timer_rtime->Enabled=false;
			 this->label_T_Pass-> Text = (counter).ToString("00.0s");
			 counter=0.0;
		 }


private: System::Void nrtime_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(cncDataPtr->intpData.lineCmd == NULL_CMD)
			 {
				nrtMain(cncDataPtr);
			 }

			 if(cncDataPtr->decData.asciiPtr[0] == '\0')
			 {
				 this->nrtime->Enabled=false;
				 free(cncDataPtr->decData.dynamicBufferPtr);
			 }

			 if(cncDataPtr->linkData.linkToMmiData.counter >1000)
			 {
				 cncDataPtr->linkData.linkToMmiData.counter = 0;
			 }
		 }

private: System::Void button_initCom_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //init COM
			 this->textBox1->Text = String::Empty;
			 if(this->comboBox1->Text == String::Empty || this->comboBox2->Text == String::Empty)
			 {
				 this->textBox1->Text = "Please Select Port Settings";
			 }
			 else 
			 {
				 try
				 {
					 // make sure port isn't open	
					 if(!this->serialPort1->IsOpen)
					 {
						 this->serialPort1->PortName = this->comboBox1->Text;

						 this->serialPort1->BaudRate = Int32::Parse(this->comboBox2->Text);

						 this->textBox2->Text = "Enter Message Here";

						 //open serial port 
						 this->serialPort1->Open();
						 this->progressBar1->Value = 100;
					 }
					 else
						 this->textBox1->Text = "Port isn't opened";
				 }
				 catch(UnauthorizedAccessException^)
				 {
					 this->textBox1->Text = "UnauthorizedAccess";
				 }
			 }
		 }
private: System::Void button_closeCom_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  //close serialPort
			 this->serialPort1->Close();
			 // update progress bar
			 this->progressBar1->Value = 0;
			 // Enable the init button
			 this->button_initCom->Enabled = true;
			 //close COM
		 }
private: System::Void Button_send_Serial_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  // add sender name
			 String^ name = this->serialPort1->PortName;
			 // grab text and store in send buffer
			 String^ message = this->textBox2->Text;
			 // write to serial
			 if(this->serialPort1->IsOpen)
			 {
				 this->serialPort1->Write(message);
			 }
			 else
			 {
				 this->textBox1->Text="Port Not Opened";
			 }
		 }

private: System::Void Button_forward_mousedown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 50;
			serialCmd[1] = '!';
		 }
private: System::Void Button_forward_mouseup(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 120;
			serialCmd[1] = '!';
		 }
private: System::Void Button_CW_mousedown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 119;
			serialCmd[1] = '!';
		 }
private: System::Void Button_CW_mouseup(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 120;
			serialCmd[1] = '!';
		 }
private: System::Void Button_backward_mousedown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 serialCmd[0] = 71;
			 serialCmd[1] = '!';
		 }
private: System::Void Button_backward_mouseup(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 120;
			serialCmd[1] = '!';

		 }
private: System::Void Button_CCW_mousedown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 118;
			serialCmd[1] = '!';
		 }
private: System::Void Button_CCW_mouseup(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			serialCmd[0] = 120;
			serialCmd[1] = '!';
		 }
private: System::Void button_Jog_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->button_Jog->BackColor= System::Drawing::Color::Red;
			 cncDataPtr->mmiData.opMode = JOG_MODE;
			 this->button_forward->Enabled=true;
			 this->button_backward->Enabled=true;
			 this->button_CW->Enabled=true;
			 this->button_CCW->Enabled=true;
		 }
private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 cncDataPtr->mmiData.RESET = true;
			 cncDataPtr->mmiData.mmiState = MMI_RESET;

			 cncMain(cncDataPtr);

			 this->label_X_Position->Text = cncDataPtr->intpData.carCoordinate[0].ToString("0.00");
			 this->label_Y_Position->Text = cncDataPtr->intpData.carCoordinate[1].ToString("0.00");
			 this->label_theta_pos->Text = cncDataPtr->intpData.carCoordinate[2].ToString("0.00");
		 }
};//public
		 
        }//namespace
