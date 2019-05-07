#pragma once
#include "schema.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for setServerForm
	/// </summary>
	public ref class setServerForm : public System::Windows::Forms::Form
	{
	private:connectInfo^ conInfo;
	public:
		setServerForm(connectInfo^ conInfo):conInfo(conInfo){
			InitializeComponent();
			nameBox->Text = conInfo->serverName;
			portBox->Text = conInfo->port.ToString();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~setServerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ nameBox;

	private: System::Windows::Forms::TextBox^ portBox;

	private: System::Windows::Forms::ErrorProvider^ errorProvider1;
	private: System::Windows::Forms::Button^ connectButton;
	private: System::Windows::Forms::Button^ testButton;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->nameBox = (gcnew System::Windows::Forms::TextBox());
			this->portBox = (gcnew System::Windows::Forms::TextBox());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->testButton = (gcnew System::Windows::Forms::Button());
			this->connectButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(43, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Server:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(70, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 29);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Port:";
			// 
			// nameBox
			// 
			this->nameBox->Location = System::Drawing::Point(139, 31);
			this->nameBox->Name = L"nameBox";
			this->nameBox->Size = System::Drawing::Size(231, 35);
			this->nameBox->TabIndex = 2;
			// 
			// portBox
			// 
			this->portBox->Location = System::Drawing::Point(139, 98);
			this->portBox->Name = L"portBox";
			this->portBox->Size = System::Drawing::Size(231, 35);
			this->portBox->TabIndex = 3;
			this->portBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &setServerForm::portBox_KeyPress);
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// testButton
			// 
			this->testButton->Location = System::Drawing::Point(104, 158);
			this->testButton->Name = L"testButton";
			this->testButton->Size = System::Drawing::Size(112, 46);
			this->testButton->TabIndex = 4;
			this->testButton->Text = L"Test";
			this->testButton->UseVisualStyleBackColor = true;
			this->testButton->Click += gcnew System::EventHandler(this, &setServerForm::TestButton_Click);
			// 
			// connectButton
			// 
			this->connectButton->Location = System::Drawing::Point(280, 158);
			this->connectButton->Name = L"connectButton";
			this->connectButton->Size = System::Drawing::Size(112, 46);
			this->connectButton->TabIndex = 5;
			this->connectButton->Text = L"Connect";
			this->connectButton->UseVisualStyleBackColor = true;
			this->connectButton->Click += gcnew System::EventHandler(this, &setServerForm::ConnectButton_Click);
			// 
			// setServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(436, 245);
			this->Controls->Add(this->connectButton);
			this->Controls->Add(this->testButton);
			this->Controls->Add(this->portBox);
			this->Controls->Add(this->nameBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->Name = L"setServerForm";
			this->Text = L"Set server";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void portBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar != '\b')
			if ((e->KeyChar < '0') || (e->KeyChar > '9')) {
				errorProvider1->SetError(portBox, "Can't input any non-numeric characters");
				e->Handled = true;
			}
			else {
				errorProvider1->Clear();
			}
	}
	private: System::Void TestButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ConnectButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			int port = Convert::ToInt32(portBox->Text);
			conInfo->port = port;
			conInfo->serverName = nameBox->Text;
			this->DialogResult = Windows::Forms::DialogResult::OK;
		}
		catch (...) {
			System::Windows::Forms::MessageBox::Show("Connection invaild!", "info");
		}
	}
};
}
