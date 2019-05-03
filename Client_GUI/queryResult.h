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
	/// Summary for queryResult
	/// </summary>
	public ref class queryResult : public System::Windows::Forms::UserControl
	{
	private:List<UserSchema^>^ result;
	public:
		queryResult(List<UserSchema^>^ result):result(result) {
			InitializeComponent();
			//detect role
			auto levelHeader = gcnew ColumnHeader();
			levelHeader->Text = L"Level";
			levelHeader->TextAlign = HorizontalAlignment::Center;
			levelHeader->Width = 81;
			if (result[0]->isPlayer) {
				auto countHeader = gcnew ColumnHeader();
				countHeader->Text = "Passed Ranks";
				countHeader->TextAlign = HorizontalAlignment::Center;
				countHeader->Width = 191;
				auto expHeader = gcnew ColumnHeader();;
				expHeader->Text = L"Exp";
				expHeader->TextAlign = HorizontalAlignment::Center;
				expHeader->Width = 116;
				resultListView->Columns->Add(countHeader);
				resultListView->Columns->Add(levelHeader);
				resultListView->Columns->Add(expHeader);
			}
			else {
				auto countHeader= gcnew ColumnHeader();
				countHeader->Text = "Committed questions";
				countHeader->TextAlign = HorizontalAlignment::Center;
				countHeader->Width = 266;
				resultListView->Columns->Add(countHeader);
				resultListView->Columns->Add(levelHeader);
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~queryResult()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ resultListView;
	protected:

	protected:
	private: System::Windows::Forms::ColumnHeader^ idHeader;
	private: System::Windows::Forms::ColumnHeader^ nameHeader;




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
			this->resultListView = (gcnew System::Windows::Forms::ListView());
			this->idHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->nameHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// resultListView
			// 
			this->resultListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->idHeader, this->nameHeader
			});
			this->resultListView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->resultListView->FullRowSelect = true;
			this->resultListView->GridLines = true;
			this->resultListView->HideSelection = false;
			this->resultListView->LabelWrap = false;
			this->resultListView->Location = System::Drawing::Point(0, 0);
			this->resultListView->MultiSelect = false;
			this->resultListView->Name = L"resultListView";
			this->resultListView->Size = System::Drawing::Size(769, 469);
			this->resultListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->resultListView->TabIndex = 1;
			this->resultListView->UseCompatibleStateImageBehavior = false;
			this->resultListView->View = System::Windows::Forms::View::Details;
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
			// queryResult
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->resultListView);
			this->Name = L"queryResult";
			this->Size = System::Drawing::Size(769, 469);
			this->Load += gcnew System::EventHandler(this, &queryResult::QueryResult_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void QueryResult_Load(System::Object^ sender, System::EventArgs^ e);
};
}
