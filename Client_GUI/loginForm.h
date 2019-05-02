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
	public ref class loginForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Form^ parent;
	public: property User^ user;
	public: socketMgnt^ socketManager;
	public:
		loginForm(System::Windows::Forms::Form^ parent, socketMgnt^ socketManager):parent(parent), socketManager(socketManager){
			InitializeComponent();
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
		~loginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ userNameBox;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ passwordBox;

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
			this->userNameBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->passwordBox = (gcnew System::Windows::Forms::TextBox());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->signButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// userNameBox
			// 
			this->userNameBox->Location = System::Drawing::Point(207, 70);
			this->userNameBox->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->userNameBox->Name = L"userNameBox";
			this->userNameBox->Size = System::Drawing::Size(343, 35);
			this->userNameBox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(61, 74);
			this->label1->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(130, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Username:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(68, 142);
			this->label2->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 29);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password:";
			// 
			// passwordBox
			// 
			this->passwordBox->Location = System::Drawing::Point(207, 138);
			this->passwordBox->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->passwordBox->Name = L"passwordBox";
			this->passwordBox->PasswordChar = '*';
			this->passwordBox->Size = System::Drawing::Size(343, 35);
			this->passwordBox->TabIndex = 3;
			this->passwordBox->TextChanged += gcnew System::EventHandler(this, &loginForm::PasswordBox_TextChanged);
			// 
			// loginButton
			// 
			this->loginButton->Enabled = false;
			this->loginButton->Location = System::Drawing::Point(207, 207);
			this->loginButton->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(126, 49);
			this->loginButton->TabIndex = 4;
			this->loginButton->Text = L"Sign in";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &loginForm::LoginButton_Click);
			// 
			// signButton
			// 
			this->signButton->Location = System::Drawing::Point(426, 207);
			this->signButton->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->signButton->Name = L"signButton";
			this->signButton->Size = System::Drawing::Size(126, 49);
			this->signButton->TabIndex = 5;
			this->signButton->Text = L"Sign up";
			this->signButton->UseVisualStyleBackColor = true;
			this->signButton->Click += gcnew System::EventHandler(this, &loginForm::SignButton_Click);
			// 
			// login
			// 
			this->AcceptButton = this->loginButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(630, 300);
			this->Controls->Add(this->signButton);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->passwordBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->userNameBox);
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"login";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SignButton_Click(System::Object^ sender, System::EventArgs^ e) {
		auto sign = gcnew ClientGUI::registe(user,socketManager);
		sign->setParent(this);
		this->Hide();
		if (sign->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			auto t = parent->GetType();
			auto parentUser = t->GetProperty("globalUser");
			parentUser->SetValue(parent, user);
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
		}
		else {
			this->Show();
		}
	}
private: System::Void LoginButton_Click(System::Object^ sender, System::EventArgs^ e) {
	auto username = userNameBox->Text;
	auto password = passwordBox->Text;
	user = socketManager->login(username, password);
	if (user) {
		auto t = parent->GetType();
		auto parentUser = t->GetProperty("globalUser");
		parentUser->SetValue(parent, user);
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
	}
}
private: System::Void PasswordBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (userNameBox->Text != String::Empty && passwordBox->Text != String::Empty)
		loginButton->Enabled = true;
	else
		loginButton->Enabled = false;
}
};
}
