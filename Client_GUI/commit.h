#pragma once
#include "socketMgnt.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ClientGUI {

	/// <summary>
	/// commit form
	/// </summary>
	public ref class commit : public System::Windows::Forms::UserControl
	{
	public: socketMgnt^ socketManager;
	public: Committer^ user;
	public:
		commit(Committer^ user, socketMgnt^ socketManager) :user(user), socketManager(socketManager)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~commit()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ commitBox;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ difficultySelect;

	private: System::Windows::Forms::Button^ commitButton;

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
			this->commitBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->difficultySelect = (gcnew System::Windows::Forms::ComboBox());
			this->commitButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// commitBox
			// 
			this->commitBox->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->commitBox->Location = System::Drawing::Point(147, 61);
			this->commitBox->Name = L"commitBox";
			this->commitBox->Size = System::Drawing::Size(272, 35);
			this->commitBox->TabIndex = 0;
			this->commitBox->TextChanged += gcnew System::EventHandler(this, &commit::CommitBox_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(53, 61);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Word:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(22, 126);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(108, 29);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Difficulty:";
			// 
			// difficultySelect
			// 
			this->difficultySelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->difficultySelect->FormattingEnabled = true;
			this->difficultySelect->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7",
					L"8", L"9", L"10"
			});
			this->difficultySelect->Location = System::Drawing::Point(147, 123);
			this->difficultySelect->Name = L"difficultySelect";
			this->difficultySelect->Size = System::Drawing::Size(70, 37);
			this->difficultySelect->TabIndex = 3;
			this->difficultySelect->SelectedIndexChanged += gcnew System::EventHandler(this, &commit::ComboBox1_SelectedIndexChanged);
			// 
			// commitButton
			// 
			this->commitButton->Enabled = false;
			this->commitButton->Location = System::Drawing::Point(203, 197);
			this->commitButton->Name = L"commitButton";
			this->commitButton->Size = System::Drawing::Size(123, 40);
			this->commitButton->TabIndex = 4;
			this->commitButton->Text = L"Commit";
			this->commitButton->UseVisualStyleBackColor = true;
			this->commitButton->Click += gcnew System::EventHandler(this, &commit::CommitButton_Click);
			// 
			// commit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->commitButton);
			this->Controls->Add(this->difficultySelect);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->commitBox);
			this->Name = L"commit";
			this->Size = System::Drawing::Size(523, 291);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ComboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (commitBox->Text != String::Empty)
			commitButton->Enabled = true;
	}
	private: System::Void CommitBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (commitBox->Text == String::Empty)
			commitButton->Enabled = false;
	}
	private: System::Void CommitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int difficulty = Convert::ToInt32(difficultySelect->SelectedItem->ToString());
		if (socketManager->commit(commitBox->Text, difficulty, user))
			((Form^)this->Parent)->DialogResult = System::Windows::Forms::DialogResult::OK;
	}
	};
}
