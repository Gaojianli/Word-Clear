#pragma once
#include "Committer.h"
#include "RankForm.h"
#include "commit.h"
#include "socketMgnt.h"
#include "queryForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ClientGUI {

	/// <summary>
	/// main control for committer
	/// </summary>
	public ref class CommitterMainControl : public System::Windows::Forms::UserControl
	{
	public: Committer^ user;
	private: System::Windows::Forms::Label^ countLabel;
	public:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ levelLabel;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ userNameLabel;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ quitButton;
	private: System::Windows::Forms::Button^ queryButton;

	private: System::Windows::Forms::Button^ rankButton;
	private: System::Windows::Forms::Button^ commitButton;
	private: System::Windows::Forms::LinkLabel^ viewQuestionLabel;
	public: socketMgnt^ socketManager;
	public:
		CommitterMainControl(Committer^ user, socketMgnt^ socketManager) :user(user), socketManager(socketManager)
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
		~CommitterMainControl()
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
			this->countLabel = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->levelLabel = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->userNameLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->queryButton = (gcnew System::Windows::Forms::Button());
			this->rankButton = (gcnew System::Windows::Forms::Button());
			this->commitButton = (gcnew System::Windows::Forms::Button());
			this->viewQuestionLabel = (gcnew System::Windows::Forms::LinkLabel());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// countLabel
			// 
			this->countLabel->AutoSize = true;
			this->countLabel->Location = System::Drawing::Point(843, 35);
			this->countLabel->Name = L"countLabel";
			this->countLabel->Size = System::Drawing::Size(89, 29);
			this->countLabel->TabIndex = 13;
			this->countLabel->Text = L"{count}";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(591, 35);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(246, 29);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Committed questions:";
			// 
			// levelLabel
			// 
			this->levelLabel->AutoSize = true;
			this->levelLabel->Location = System::Drawing::Point(495, 35);
			this->levelLabel->Name = L"levelLabel";
			this->levelLabel->Size = System::Drawing::Size(82, 29);
			this->levelLabel->TabIndex = 11;
			this->levelLabel->Text = L"{level}";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(412, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 29);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Level:";
			// 
			// userNameLabel
			// 
			this->userNameLabel->AutoSize = true;
			this->userNameLabel->Location = System::Drawing::Point(182, 35);
			this->userNameLabel->Name = L"userNameLabel";
			this->userNameLabel->Size = System::Drawing::Size(138, 29);
			this->userNameLabel->TabIndex = 9;
			this->userNameLabel->Text = L"{username}";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(92, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 29);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Name:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->quitButton);
			this->groupBox1->Controls->Add(this->queryButton);
			this->groupBox1->Controls->Add(this->rankButton);
			this->groupBox1->Controls->Add(this->commitButton);
			this->groupBox1->Location = System::Drawing::Point(96, 86);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(888, 368);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Operations";
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(521, 215);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(218, 83);
			this->quitButton->TabIndex = 3;
			this->quitButton->Text = L"Exit";
			this->quitButton->UseVisualStyleBackColor = true;
			this->quitButton->Click += gcnew System::EventHandler(this, &CommitterMainControl::QuitButton_Click);
			// 
			// queryButton
			// 
			this->queryButton->Location = System::Drawing::Point(121, 215);
			this->queryButton->Name = L"queryButton";
			this->queryButton->Size = System::Drawing::Size(218, 83);
			this->queryButton->TabIndex = 2;
			this->queryButton->Text = L"Query";
			this->queryButton->UseVisualStyleBackColor = true;
			this->queryButton->Click += gcnew System::EventHandler(this, &CommitterMainControl::QueryButton_Click);
			// 
			// rankButton
			// 
			this->rankButton->Location = System::Drawing::Point(521, 87);
			this->rankButton->Name = L"rankButton";
			this->rankButton->Size = System::Drawing::Size(218, 83);
			this->rankButton->TabIndex = 1;
			this->rankButton->Text = L"Ranks";
			this->rankButton->UseVisualStyleBackColor = true;
			this->rankButton->Click += gcnew System::EventHandler(this, &CommitterMainControl::RankButton_Click);
			// 
			// commitButton
			// 
			this->commitButton->Location = System::Drawing::Point(121, 87);
			this->commitButton->Name = L"commitButton";
			this->commitButton->Size = System::Drawing::Size(218, 83);
			this->commitButton->TabIndex = 0;
			this->commitButton->Text = L"Commit";
			this->commitButton->UseVisualStyleBackColor = true;
			this->commitButton->Click += gcnew System::EventHandler(this, &CommitterMainControl::CommitButton_Click);
			// 
			// viewQuestionLabel
			// 
			this->viewQuestionLabel->AutoSize = true;
			this->viewQuestionLabel->Location = System::Drawing::Point(91, 457);
			this->viewQuestionLabel->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->viewQuestionLabel->Name = L"viewQuestionLabel";
			this->viewQuestionLabel->Size = System::Drawing::Size(214, 29);
			this->viewQuestionLabel->TabIndex = 15;
			this->viewQuestionLabel->TabStop = true;
			this->viewQuestionLabel->Text = L"View All Questions";
			this->viewQuestionLabel->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CommitterMainControl::ViewQuestionLabel_LinkClicked);
			// 
			// CommitterMainControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->viewQuestionLabel);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->countLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->levelLabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->userNameLabel);
			this->Controls->Add(this->label1);
			this->Name = L"CommitterMainControl";
			this->Size = System::Drawing::Size(1072, 523);
			this->Load += gcnew System::EventHandler(this, &CommitterMainControl::CommitterMainControl_Load);
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CommitterMainControl_Load(System::Object^ sender, System::EventArgs^ e) {
		userNameLabel->Text = user->name + " (UID:" + user->id.ToString() + ")";
		levelLabel->Text = user->level.ToString();
		countLabel->Text = user->count.ToString();
	}
	private: System::Void CommitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		auto commitForm = gcnew Form();
		auto userControl = gcnew commit(user, socketManager);
		userControl->Location = Point(0, 0);
		commitForm->Size = userControl->Size;
		commitForm->Controls->Add(userControl);
		userControl->Location = Point(0, userControl->Location.Y);
		commitForm->Height = userControl->Height + 80;
		commitForm->Text = "Commit";
		commitForm->StartPosition = Windows::Forms::FormStartPosition::CenterScreen;
		if (commitForm->ShowDialog() == Windows::Forms::DialogResult::OK) {
			MessageBox::Show("Commit successfully!", "Info");
			user->count++;
			if (user->count / 10 > user->level)
				user->level++;
			delete commitForm;
		}
		levelLabel->Text = user->level.ToString();
		countLabel->Text = user->count.ToString();
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
		 private: System::Void ViewQuestionLabel_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
			 auto thread = gcnew Threading::Thread(gcnew Threading::ThreadStart(this, &CommitterMainControl::fetchQuestionList));
			 thread->Start();
		 }
				  //invoke this after fetch question List
	private: void finishFetch(List<wordSchemaWithCommitter^>^ questionList) {
		if (questionList != nullptr) {
			auto listForm = gcnew questionListForm(questionList);
			listForm->Show();
		}
	};
	private: delegate void finishFetchDelegate(List<wordSchemaWithCommitter^>^ questionList);

			 //fetch the word list in another thread
	private: void fetchQuestionList() {
		auto finish = gcnew finishFetchDelegate(this, &CommitterMainControl::finishFetch);
		auto questionList = socketManager->getQuestionWithCommitter(user);
		this->Invoke(finish, questionList);//invoke callback function
	}
};
}
