#pragma once
#include "user.h"
#include "socketMgnt.h"

namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for registe
	/// </summary>
	public ref class registe : public System::Windows::Forms::Form
	{
	private: User^ user;
	private: socketMgnt^ socketManager;
	public:
		registe(User^ userPtr, socketMgnt^ socketManager):user(userPtr),socketManager(socketManager)
		{
			InitializeComponent();
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~registe()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::TextBox^ passwordBox;
	private: System::Windows::Forms::TextBox^ usernameBox;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->passwordBox = (gcnew System::Windows::Forms::TextBox());
			this->usernameBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Username:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(52, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Password:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(88, 109);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 20);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Role:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Controls->Add(this->passwordBox);
			this->groupBox1->Controls->Add(this->usernameBox);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(0, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(426, 206);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(245, 152);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(77, 32);
			this->button2->TabIndex = 11;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &registe::Button2_Click);
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(136, 152);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(77, 32);
			this->button1->TabIndex = 10;
			this->button1->Text = L"Confirm";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &registe::Button1_Click);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(240, 109);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(77, 24);
			this->radioButton2->TabIndex = 9;
			this->radioButton2->Text = L"Player";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(140, 109);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(94, 24);
			this->radioButton1->TabIndex = 8;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Comitter";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// passwordBox
			// 
			this->passwordBox->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->passwordBox->Location = System::Drawing::Point(140, 69);
			this->passwordBox->Name = L"passwordBox";
			this->passwordBox->Size = System::Drawing::Size(182, 26);
			this->passwordBox->TabIndex = 7;
			this->passwordBox->WordWrap = false;
			this->passwordBox->TextChanged += gcnew System::EventHandler(this, &registe::passwordBox_TextChanged);
			// 
			// usernameBox
			// 
			this->usernameBox->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->usernameBox->Location = System::Drawing::Point(140, 32);
			this->usernameBox->Name = L"usernameBox";
			this->usernameBox->Size = System::Drawing::Size(182, 26);
			this->usernameBox->TabIndex = 5;
			this->usernameBox->WordWrap = false;
			// 
			// registe
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(426, 206);
			this->Controls->Add(this->groupBox1);
			this->Name = L"registe";
			this->Text = L"Sign Up";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void passwordBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		button1->Enabled = true;
	}
private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void Button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->DialogResult = Windows::Forms::DialogResult::Cancel;
}
};
}
