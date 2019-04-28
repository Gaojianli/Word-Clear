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
	private: System::Windows::Forms::Form^ parent;
	public:
		registe(User^ userPtr, socketMgnt^ socketManager) :user(userPtr), socketManager(socketManager)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	public:void setParent(System::Windows::Forms::Form^ p) {
		parent = p;
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
	private: System::Windows::Forms::Button^ cancelButton;

	private: System::Windows::Forms::Button^ signButton;
	private: System::Windows::Forms::RadioButton^ playerRadio;


	private: System::Windows::Forms::RadioButton^ committerRadio;

	private: System::Windows::Forms::TextBox^ passwordBox;
	private: System::Windows::Forms::TextBox^ usernameBox;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

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
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->signButton = (gcnew System::Windows::Forms::Button());
			this->playerRadio = (gcnew System::Windows::Forms::RadioButton());
			this->committerRadio = (gcnew System::Windows::Forms::RadioButton());
			this->passwordBox = (gcnew System::Windows::Forms::TextBox());
			this->usernameBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(73, 46);
			this->label1->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(130, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Username:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(81, 100);
			this->label2->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 29);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Password:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(137, 158);
			this->label3->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(70, 29);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Role:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->cancelButton);
			this->groupBox1->Controls->Add(this->signButton);
			this->groupBox1->Controls->Add(this->playerRadio);
			this->groupBox1->Controls->Add(this->committerRadio);
			this->groupBox1->Controls->Add(this->passwordBox);
			this->groupBox1->Controls->Add(this->usernameBox);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(0, 0);
			this->groupBox1->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->groupBox1->Size = System::Drawing::Size(625, 299);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(381, 220);
			this->cancelButton->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(120, 46);
			this->cancelButton->TabIndex = 11;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &registe::cancelButton_Click);
			// 
			// signButton
			// 
			this->signButton->Enabled = false;
			this->signButton->Location = System::Drawing::Point(212, 220);
			this->signButton->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->signButton->Name = L"signButton";
			this->signButton->Size = System::Drawing::Size(120, 46);
			this->signButton->TabIndex = 10;
			this->signButton->Text = L"Confirm";
			this->signButton->UseVisualStyleBackColor = true;
			this->signButton->Click += gcnew System::EventHandler(this, &registe::signButton_Click);
			// 
			// playerRadio
			// 
			this->playerRadio->AutoSize = true;
			this->playerRadio->Location = System::Drawing::Point(373, 158);
			this->playerRadio->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->playerRadio->Name = L"playerRadio";
			this->playerRadio->Size = System::Drawing::Size(112, 33);
			this->playerRadio->TabIndex = 9;
			this->playerRadio->Text = L"Player";
			this->playerRadio->UseVisualStyleBackColor = true;
			// 
			// committerRadio
			// 
			this->committerRadio->AutoSize = true;
			this->committerRadio->Checked = true;
			this->committerRadio->Location = System::Drawing::Point(218, 158);
			this->committerRadio->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->committerRadio->Name = L"committerRadio";
			this->committerRadio->Size = System::Drawing::Size(135, 33);
			this->committerRadio->TabIndex = 8;
			this->committerRadio->TabStop = true;
			this->committerRadio->Text = L"Comitter";
			this->committerRadio->UseVisualStyleBackColor = true;
			// 
			// passwordBox
			// 
			this->passwordBox->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->passwordBox->Location = System::Drawing::Point(218, 100);
			this->passwordBox->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->passwordBox->Name = L"passwordBox";
			this->passwordBox->PasswordChar = '*';
			this->passwordBox->Size = System::Drawing::Size(281, 35);
			this->passwordBox->TabIndex = 7;
			this->passwordBox->WordWrap = false;
			this->passwordBox->TextChanged += gcnew System::EventHandler(this, &registe::passwordBox_TextChanged);
			// 
			// usernameBox
			// 
			this->usernameBox->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->usernameBox->Location = System::Drawing::Point(218, 46);
			this->usernameBox->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->usernameBox->Name = L"usernameBox";
			this->usernameBox->Size = System::Drawing::Size(281, 35);
			this->usernameBox->TabIndex = 5;
			this->usernameBox->WordWrap = false;
			// 
			// registe
			// 
			this->AcceptButton = this->signButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(625, 299);
			this->Controls->Add(this->groupBox1);
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"registe";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sign Up";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void passwordBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (usernameBox->Text != String::Empty && passwordBox->Text != String::Empty)
			signButton->Enabled = true;
		else
			signButton->Enabled = false;
	}
	private: System::Void signButton_Click(System::Object^ sender, System::EventArgs^ e) {
		user = socketManager->signup(usernameBox->Text, passwordBox->Text, playerRadio->Checked);
		if (user) {
			//set parent's user by using reflection 
			auto t = parent->GetType();
			auto parentUser = t->GetProperty("user");
			parentUser->SetValue(parent, user);
			this->DialogResult = Windows::Forms::DialogResult::OK;
		}
	}
	private: System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
	}
	};
}
