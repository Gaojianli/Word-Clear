﻿#include "queryForm.h"
#include "queryResult.h"
inline ClientGUI::queryForm::queryForm(User^ user, socketMgnt^ socketManager) :user(user), socketManager(socketManager)
{
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//
}

/// <summary>
/// Clean up any resources being used.
/// </summary>

inline ClientGUI::queryForm::~queryForm()
{
	if (components)
	{
		delete components;
	}
}

/// <summary>
/// Required method for Designer support - do not modify
/// the contents of this method with the code editor.
/// </summary>

inline void ClientGUI::queryForm::InitializeComponent(void)
{
	this->components = (gcnew System::ComponentModel::Container());
	this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
	this->queryButton = (gcnew System::Windows::Forms::Button());
	this->valueBox = (gcnew System::Windows::Forms::TextBox());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->propertyPicker = (gcnew System::Windows::Forms::ComboBox());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->committerRadio = (gcnew System::Windows::Forms::RadioButton());
	this->playerRadio = (gcnew System::Windows::Forms::RadioButton());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
	this->groupBox1->SuspendLayout();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
	this->SuspendLayout();
	// 
	// groupBox1
	// 
	this->groupBox1->Controls->Add(this->queryButton);
	this->groupBox1->Controls->Add(this->valueBox);
	this->groupBox1->Controls->Add(this->label3);
	this->groupBox1->Controls->Add(this->propertyPicker);
	this->groupBox1->Controls->Add(this->label2);
	this->groupBox1->Controls->Add(this->committerRadio);
	this->groupBox1->Controls->Add(this->playerRadio);
	this->groupBox1->Controls->Add(this->label1);
	this->groupBox1->Location = System::Drawing::Point(52, 26);
	this->groupBox1->Name = L"groupBox1";
	this->groupBox1->Size = System::Drawing::Size(704, 265);
	this->groupBox1->TabIndex = 0;
	this->groupBox1->TabStop = false;
	this->groupBox1->Text = L"Conditions";
	// 
	// queryButton
	// 
	this->queryButton->Enabled = false;
	this->queryButton->Location = System::Drawing::Point(505, 200);
	this->queryButton->Name = L"queryButton";
	this->queryButton->Size = System::Drawing::Size(135, 42);
	this->queryButton->TabIndex = 5;
	this->queryButton->Text = L"Query";
	this->queryButton->UseVisualStyleBackColor = true;
	this->queryButton->Click += gcnew System::EventHandler(this, &queryForm::processQuerry);
	// 
	// valueBox
	// 
	this->valueBox->Enabled = false;
	this->valueBox->ImeMode = System::Windows::Forms::ImeMode::Off;
	this->valueBox->Location = System::Drawing::Point(147, 155);
	this->valueBox->Name = L"valueBox";
	this->valueBox->Size = System::Drawing::Size(138, 35);
	this->valueBox->TabIndex = 1;
	this->valueBox->TextChanged += gcnew System::EventHandler(this, &queryForm::valueBox_TextChanged);
	this->valueBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &queryForm::ValueBox_KeyPress);
	// 
	// label3
	// 
	this->label3->AutoSize = true;
	this->label3->Location = System::Drawing::Point(61, 155);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(80, 29);
	this->label3->TabIndex = 1;
	this->label3->Text = L"Value:";
	// 
	// propertyPicker
	// 
	this->propertyPicker->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->propertyPicker->FormattingEnabled = true;
	this->propertyPicker->ImeMode = System::Windows::Forms::ImeMode::Off;
	this->propertyPicker->Location = System::Drawing::Point(146, 106);
	this->propertyPicker->Name = L"propertyPicker";
	this->propertyPicker->Size = System::Drawing::Size(273, 37);
	this->propertyPicker->TabIndex = 4;
	this->propertyPicker->SelectedIndexChanged += gcnew System::EventHandler(this, &queryForm::PropertyPicker_SelectedIndexChanged);
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Location = System::Drawing::Point(30, 109);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(110, 29);
	this->label2->TabIndex = 3;
	this->label2->Text = L"Property:";
	// 
	// committerRadio
	// 
	this->committerRadio->AutoSize = true;
	this->committerRadio->Location = System::Drawing::Point(264, 63);
	this->committerRadio->Name = L"committerRadio";
	this->committerRadio->Size = System::Drawing::Size(155, 33);
	this->committerRadio->TabIndex = 2;
	this->committerRadio->TabStop = true;
	this->committerRadio->Text = L"Committer";
	this->committerRadio->UseVisualStyleBackColor = true;
	this->committerRadio->CheckedChanged += gcnew System::EventHandler(this, &queryForm::CommitterRadio_CheckedChanged);
	// 
	// playerRadio
	// 
	this->playerRadio->AutoSize = true;
	this->playerRadio->Location = System::Drawing::Point(146, 63);
	this->playerRadio->Name = L"playerRadio";
	this->playerRadio->Size = System::Drawing::Size(112, 33);
	this->playerRadio->TabIndex = 1;
	this->playerRadio->TabStop = true;
	this->playerRadio->Text = L"Player";
	this->playerRadio->UseVisualStyleBackColor = true;
	this->playerRadio->CheckedChanged += gcnew System::EventHandler(this, &queryForm::PlayerRadio_CheckedChanged);
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Location = System::Drawing::Point(70, 63);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(70, 29);
	this->label1->TabIndex = 0;
	this->label1->Text = L"Role:";
	// 
	// errorProvider1
	// 
	this->errorProvider1->ContainerControl = this;
	// 
	// queryForm
	// 
	this->AcceptButton = this->queryButton;
	this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(798, 321);
	this->Controls->Add(this->groupBox1);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->MaximizeBox = false;
	this->Name = L"queryForm";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->Text = L"Query user";
	this->Load += gcnew System::EventHandler(this, &queryForm::QueryForm_Load);
	this->groupBox1->ResumeLayout(false);
	this->groupBox1->PerformLayout();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
	this->ResumeLayout(false);

}
inline System::Void ClientGUI::queryForm::QueryForm_Load(System::Object^ sender, System::EventArgs^ e) {
	//default choice
	playerRadio->Checked = user->isPlayer;
	committerRadio->Checked = !user->isPlayer;

}
inline System::Void ClientGUI::queryForm::PlayerRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	propertyPicker->Items->Clear();
	valueBox->Enabled = false;
	valueBox->Text = String::Empty;
	propertyPicker->Items->Add("UID");
	propertyPicker->Items->Add("Name");
	propertyPicker->Items->Add("Level");
	if (playerRadio->Checked) {
		propertyPicker->Items->Add("Passed Ranks");
		propertyPicker->Items->Add("Exp");
	}
	else {
		propertyPicker->Items->Add("Committed Questions");
	}
}
inline System::Void ClientGUI::queryForm::CommitterRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	propertyPicker->Items->Clear();
	valueBox->Enabled = false;
	valueBox->Text = String::Empty;
	propertyPicker->Items->Add("UID");
	propertyPicker->Items->Add("Name");
	propertyPicker->Items->Add("Level");
	if (playerRadio->Checked) {
		propertyPicker->Items->Add("Passed Ranks");
		propertyPicker->Items->Add("Exp");
	}
	else {
		propertyPicker->Items->Add("Committed Questions");
	}
}
inline System::Void ClientGUI::queryForm::valueBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (propertyPicker->SelectedItem == nullptr || valueBox->Text == String::Empty)
		queryButton->Enabled = false;
	else
		queryButton->Enabled = true;
}
inline System::Void ClientGUI::queryForm::ValueBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (!propertyPicker->SelectedItem->Equals("Name")) //can type number only
		if (e->KeyChar != '\b')
			if ((e->KeyChar < '0') || (e->KeyChar > '9')) {
				errorProvider1->SetError(valueBox, "Can't input any non-numeric characters");
				e->Handled = true;
			}
			else {
				errorProvider1->Clear();
			}

}
inline System::Void ClientGUI::queryForm::PropertyPicker_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	valueBox->Text = String::Empty;
	valueBox->Enabled = true;
}
System::Void ClientGUI::queryForm::processQuerry(System::Object^ sender, System::EventArgs^ e) {
	Object^ value;
	if (propertyPicker->SelectedItem->Equals("Name"))
		value = valueBox->Text;
	else
		value = Convert::ToInt32(valueBox->Text);
	//alias property
	String^ property;
	if (propertyPicker->SelectedItem->Equals("Committed Questions") || propertyPicker->SelectedItem->Equals("Passed Ranks"))
		property = "count";
	else if (propertyPicker->SelectedItem->Equals("UID"))
		property = "id";
	else
		property = propertyPicker->SelectedItem->ToString()->ToLower();

	auto queryResult = socketManager->customizeQuery(user, property, playerRadio->Checked, value);
	if (queryResult == nullptr || queryResult->Count == 0)
		MessageBox::Show("No matches found!", "Error: 404");
	else {
		auto resultForm = gcnew Form();
		auto userControl = gcnew ClientGUI::queryResult(queryResult);
		userControl->Location = Point(0, 0);
		resultForm->Size = userControl->Size;
		resultForm->Controls->Add(userControl);
		userControl->Location = Point(0, userControl->Location.Y);
		resultForm->Height = userControl->Height + 80;
		resultForm->Text = "Query Result";
		resultForm->StartPosition = Windows::Forms::FormStartPosition::CenterScreen;
		resultForm->Show();
	}
		
}
