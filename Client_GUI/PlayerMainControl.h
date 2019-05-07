#pragma once
#include "Player.h"
#include "RankForm.h"
#include "queryForm.h"
#include "playForm.h"
#include "socketMgnt.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ClientGUI {

	/// <summary>
	/// Summary for PlayerMainControl
	/// </summary>
	public ref class PlayerMainControl : public System::Windows::Forms::UserControl
	{
	public: Player^ user;
	private: System::Windows::Forms::Label^ label1;
	public:
	private: System::Windows::Forms::Label^ userNameLabel;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ levelLabel;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ countLabel;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ expLabel;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ startButton;
	private: System::Windows::Forms::Button^ quitButton;
	private: System::Windows::Forms::Button^ queryButton;



	private: System::Windows::Forms::Button^ rankButton;
	private: Form^ parent;




	public: socketMgnt^ socketManager;
	public:
		PlayerMainControl(Player^ user, socketMgnt^ socketManager, Form^ parent) :user(user), socketManager(socketManager),parent(parent)
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
		~PlayerMainControl()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->userNameLabel = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->levelLabel = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->countLabel = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->expLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->queryButton = (gcnew System::Windows::Forms::Button());
			this->rankButton = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(89, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Name:";
			// 
			// userNameLabel
			// 
			this->userNameLabel->AutoSize = true;
			this->userNameLabel->Location = System::Drawing::Point(165, 39);
			this->userNameLabel->Name = L"userNameLabel";
			this->userNameLabel->Size = System::Drawing::Size(138, 29);
			this->userNameLabel->TabIndex = 1;
			this->userNameLabel->Text = L"{username}";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(379, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 29);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Level:";
			// 
			// levelLabel
			// 
			this->levelLabel->AutoSize = true;
			this->levelLabel->Location = System::Drawing::Point(462, 39);
			this->levelLabel->Name = L"levelLabel";
			this->levelLabel->Size = System::Drawing::Size(82, 29);
			this->levelLabel->TabIndex = 3;
			this->levelLabel->Text = L"{level}";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(550, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(173, 29);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Passed Ranks:";
			// 
			// countLabel
			// 
			this->countLabel->AutoSize = true;
			this->countLabel->Location = System::Drawing::Point(729, 39);
			this->countLabel->Name = L"countLabel";
			this->countLabel->Size = System::Drawing::Size(89, 29);
			this->countLabel->TabIndex = 5;
			this->countLabel->Text = L"{count}";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(818, 39);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(60, 29);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Exp:";
			// 
			// expLabel
			// 
			this->expLabel->AutoSize = true;
			this->expLabel->Location = System::Drawing::Point(884, 39);
			this->expLabel->Name = L"expLabel";
			this->expLabel->Size = System::Drawing::Size(70, 29);
			this->expLabel->TabIndex = 7;
			this->expLabel->Text = L"{exp}";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->quitButton);
			this->groupBox1->Controls->Add(this->queryButton);
			this->groupBox1->Controls->Add(this->rankButton);
			this->groupBox1->Controls->Add(this->startButton);
			this->groupBox1->Location = System::Drawing::Point(94, 86);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(889, 369);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Operations";
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(521, 215);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(218, 82);
			this->quitButton->TabIndex = 3;
			this->quitButton->Text = L"Exit";
			this->quitButton->UseVisualStyleBackColor = true;
			this->quitButton->Click += gcnew System::EventHandler(this, &PlayerMainControl::QuitButton_Click);
			// 
			// queryButton
			// 
			this->queryButton->Location = System::Drawing::Point(122, 215);
			this->queryButton->Name = L"queryButton";
			this->queryButton->Size = System::Drawing::Size(218, 82);
			this->queryButton->TabIndex = 2;
			this->queryButton->Text = L"Query";
			this->queryButton->UseVisualStyleBackColor = true;
			this->queryButton->Click += gcnew System::EventHandler(this, &PlayerMainControl::QueryButton_Click);
			// 
			// rankButton
			// 
			this->rankButton->Location = System::Drawing::Point(521, 87);
			this->rankButton->Name = L"rankButton";
			this->rankButton->Size = System::Drawing::Size(218, 82);
			this->rankButton->TabIndex = 1;
			this->rankButton->Text = L"Ranks";
			this->rankButton->UseVisualStyleBackColor = true;
			this->rankButton->Click += gcnew System::EventHandler(this, &PlayerMainControl::RankButton_Click);
			// 
			// startButton
			// 
			this->startButton->Location = System::Drawing::Point(122, 87);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(218, 82);
			this->startButton->TabIndex = 0;
			this->startButton->Text = L"Play";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &PlayerMainControl::StartButton_Click);
			// 
			// PlayerMainControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->expLabel);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->countLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->levelLabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->userNameLabel);
			this->Controls->Add(this->label1);
			this->Name = L"PlayerMainControl";
			this->Size = System::Drawing::Size(1072, 523);
			this->Load += gcnew System::EventHandler(this, &PlayerMainControl::PlayerMainControl_Load);
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void PlayerMainControl_Load(System::Object^ sender, System::EventArgs^ e) {
		userNameLabel->Text = user->name + " (UID:" + user->id.ToString() + ")";
		levelLabel->Text = user->level.ToString();
		countLabel->Text = user->count.ToString();
		expLabel->Text = user->exp.ToString();
	}
	private: System::Void QuitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		delete socketManager;
		Environment::Exit(0);
	}
	private: System::Void RankButton_Click(System::Object^ sender, System::EventArgs^ e) {
		auto rank = gcnew RankForm(user, socketManager);
		rank->Show();
	}
private: System::Void QueryButton_Click(System::Object^ sender, System::EventArgs^ e) {
	auto query = gcnew queryForm(user, socketManager);
	query->Show();
}
private: System::Void StartButton_Click(System::Object^ sender, System::EventArgs^ e) {
	parent->Hide();
	auto playerForm = gcnew playForm(user, socketManager);
	if (auto result = playerForm->ShowDialog(); result == DialogResult::OK) {
		parent->Show();
		socketManager->updatePlayer(user);
		levelLabel->Text = user->level.ToString();
		countLabel->Text = user->count.ToString();
		expLabel->Text = user->exp.ToString();
	}
	else
		parent->Show();
	delete playerForm;
}
};
}
