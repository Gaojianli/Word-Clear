#pragma once
#include "user.h"
#include "socketMgnt.h"
#include "registe.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for login
	/// </summary>
	public ref class login : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Form^ parent;
	public: User^ user;
	public: socketMgnt^ socketManager;
	public:
		login(System::Windows::Forms::Form^ parent, socketMgnt^ socketManager):parent(parent), socketManager(socketManager){
			InitializeComponent();
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			//
			//TODO: Add the constructor code here
			//
		}
	public: void init(User^ toset) {
		user = toset;
	}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ loginButton;
	private: System::Windows::Forms::Button^ signButton;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->signButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(133, 48);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(222, 26);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(39, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Username:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(44, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(133, 95);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(222, 26);
			this->textBox2->TabIndex = 3;
			// 
			// loginButton
			// 
			this->loginButton->Location = System::Drawing::Point(133, 143);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(81, 34);
			this->loginButton->TabIndex = 4;
			this->loginButton->Text = L"Sign in";
			this->loginButton->UseVisualStyleBackColor = true;
			// 
			// signButton
			// 
			this->signButton->Location = System::Drawing::Point(274, 143);
			this->signButton->Name = L"signButton";
			this->signButton->Size = System::Drawing::Size(81, 34);
			this->signButton->TabIndex = 5;
			this->signButton->Text = L"Sign up";
			this->signButton->UseVisualStyleBackColor = true;
			this->signButton->Click += gcnew System::EventHandler(this, &login::SignButton_Click);
			// 
			// login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(454, 207);
			this->Controls->Add(this->signButton);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"login";
			this->Text = L"Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SignButton_Click(System::Object^ sender, System::EventArgs^ e) {
		auto sign = gcnew ClientGUI::registe(user,socketManager);
		this->Hide();
		if (sign->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
		}
		else {
			this->Show();
		}
	}
};
}
