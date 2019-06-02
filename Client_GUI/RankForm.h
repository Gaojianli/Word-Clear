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
	/// Rank Form
	/// </summary>
	public ref class RankForm : public System::Windows::Forms::Form
	{
	public: User^ user;
	public: socketMgnt^ socketManager;
	public:
		RankForm(User^ user, socketMgnt^ socketManager) :user(user), socketManager(socketManager)
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
		~RankForm()
		{
			if (components)
			{
				GC::Collect();
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^ tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^ tabPage1;

	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::ListView^ playerRanklistView;
	private: System::Windows::Forms::ColumnHeader^ idHeader;
	private: System::Windows::Forms::ColumnHeader^ nameHeader;
	private: System::Windows::Forms::ColumnHeader^ countHeader;
	private: System::Windows::Forms::ColumnHeader^ levelHeader;
	private: System::Windows::Forms::ColumnHeader^ expHeader;
	private: System::Windows::Forms::ListView^ committerlistView;


	private: System::Windows::Forms::ColumnHeader^ idHeader_committer;
	private: System::Windows::Forms::ColumnHeader^ nameHeader_committer;
	private: System::Windows::Forms::ColumnHeader^ countHeader_committer;
	private: System::Windows::Forms::ColumnHeader^ levelHeader_committer;

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
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->playerRanklistView = (gcnew System::Windows::Forms::ListView());
			this->idHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->nameHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->countHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->levelHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->expHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->committerlistView = (gcnew System::Windows::Forms::ListView());
			this->idHeader_committer = (gcnew System::Windows::Forms::ColumnHeader());
			this->nameHeader_committer = (gcnew System::Windows::Forms::ColumnHeader());
			this->countHeader_committer = (gcnew System::Windows::Forms::ColumnHeader());
			this->levelHeader_committer = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(739, 643);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->playerRanklistView);
			this->tabPage1->Location = System::Drawing::Point(10, 47);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(719, 586);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Player";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// playerRanklistView
			// 
			this->playerRanklistView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->idHeader,
					this->nameHeader, this->countHeader, this->levelHeader, this->expHeader
			});
			this->playerRanklistView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->playerRanklistView->FullRowSelect = true;
			this->playerRanklistView->GridLines = true;
			this->playerRanklistView->HideSelection = false;
			this->playerRanklistView->LabelWrap = false;
			this->playerRanklistView->Location = System::Drawing::Point(3, 3);
			this->playerRanklistView->MultiSelect = false;
			this->playerRanklistView->Name = L"playerRanklistView";
			this->playerRanklistView->Size = System::Drawing::Size(713, 580);
			this->playerRanklistView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->playerRanklistView->TabIndex = 0;
			this->playerRanklistView->UseCompatibleStateImageBehavior = false;
			this->playerRanklistView->View = System::Windows::Forms::View::Details;
			// 
			// idHeader
			// 
			this->idHeader->Text = L"id";
			this->idHeader->Width = 42;
			// 
			// nameHeader
			// 
			this->nameHeader->Text = L"Name";
			this->nameHeader->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->nameHeader->Width = 160;
			// 
			// countHeader
			// 
			this->countHeader->Text = L"Passed Ranks";
			this->countHeader->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->countHeader->Width = 191;
			// 
			// levelHeader
			// 
			this->levelHeader->Text = L"Level";
			this->levelHeader->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->levelHeader->Width = 81;
			// 
			// expHeader
			// 
			this->expHeader->Text = L"Exp";
			this->expHeader->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->expHeader->Width = 116;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->committerlistView);
			this->tabPage2->Location = System::Drawing::Point(10, 47);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(719, 586);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Committer";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// committerlistView
			// 
			this->committerlistView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->idHeader_committer,
					this->nameHeader_committer, this->countHeader_committer, this->levelHeader_committer
			});
			this->committerlistView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->committerlistView->FullRowSelect = true;
			this->committerlistView->GridLines = true;
			this->committerlistView->HideSelection = false;
			this->committerlistView->LabelWrap = false;
			this->committerlistView->Location = System::Drawing::Point(3, 3);
			this->committerlistView->MultiSelect = false;
			this->committerlistView->Name = L"committerlistView";
			this->committerlistView->Size = System::Drawing::Size(713, 580);
			this->committerlistView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->committerlistView->TabIndex = 0;
			this->committerlistView->UseCompatibleStateImageBehavior = false;
			this->committerlistView->View = System::Windows::Forms::View::Details;
			// 
			// idHeader_committer
			// 
			this->idHeader_committer->Text = L"id";
			this->idHeader_committer->Width = 42;
			// 
			// nameHeader_committer
			// 
			this->nameHeader_committer->Text = L"Name";
			this->nameHeader_committer->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->nameHeader_committer->Width = 160;
			// 
			// countHeader_committer
			// 
			this->countHeader_committer->Text = L"Committed questions";
			this->countHeader_committer->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->countHeader_committer->Width = 266;
			// 
			// levelHeader_committer
			// 
			this->levelHeader_committer->Text = L"Level";
			this->levelHeader_committer->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->levelHeader_committer->Width = 117;
			// 
			// RankForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(739, 643);
			this->Controls->Add(this->tabControl1);
			this->Name = L"RankForm";
			this->Text = L"Ranks";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &RankForm::RankForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void RankForm_Load(System::Object^ sender, System::EventArgs^ e) {
		List<UserSchema^>^ PlayerList;
		List<UserSchema^>^ CommitterList;
		if (user->isPlayer) {
			PlayerList = socketManager->getSameRoleUser(user);
			CommitterList = socketManager->getDifferentRoleUser(user);
		}
		else {
			CommitterList = socketManager->getSameRoleUser(user);
			PlayerList = socketManager->getDifferentRoleUser(user);
		}
		if (PlayerList == nullptr || CommitterList == nullptr) {
			this->Close();
			return;
		}
		CommitterList->Sort(gcnew CompareUser());
		PlayerList->Sort(gcnew CompareUser());
		playerRanklistView->BeginUpdate();
		for each (PlayerSchema ^ item in PlayerList) {
			auto ltv = gcnew ListViewItem();
			ltv->Text = item->id.ToString();
			ltv->SubItems->Add(item->name);
			ltv->SubItems->Add(item->count.ToString());
			ltv->SubItems->Add(item->level.ToString());
			ltv->SubItems->Add(item->exp.ToString());
			playerRanklistView->Items->Add(ltv);
		}
		playerRanklistView->EndUpdate();
		committerlistView->BeginUpdate();
		for each (CommitterSchema ^ item in CommitterList) {
			auto ltv = gcnew ListViewItem();
			ltv->Text = item->id.ToString();
			ltv->SubItems->Add(item->name);
			ltv->SubItems->Add(item->count.ToString());
			ltv->SubItems->Add(item->level.ToString());
			committerlistView->Items->Add(ltv);
		}
		committerlistView->EndUpdate();
		delete PlayerList;
		delete CommitterList;
	}
	};
}
