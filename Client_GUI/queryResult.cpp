#include "queryResult.h"

inline ClientGUI::queryResult::queryResult(List<UserSchema^>^ result) :result(result) {
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
		auto countHeader = gcnew ColumnHeader();
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

/// <summary>
/// Clean up any resources being used.
/// </summary>

inline ClientGUI::queryResult::~queryResult()
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

inline void ClientGUI::queryResult::InitializeComponent(void)
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

inline System::Void ClientGUI::queryResult::QueryResult_Load(System::Object^ sender, System::EventArgs^ e) {
	//load data
	result->Sort(gcnew CompareUser());
	if (result[0]->isPlayer) {
		resultListView->BeginUpdate();
		for each (PlayerSchema ^ item in result) {
			auto ltv = gcnew ListViewItem();
			ltv->Text = item->id.ToString();
			ltv->SubItems->Add(item->name);
			ltv->SubItems->Add(item->count.ToString());
			ltv->SubItems->Add(item->level.ToString());
			ltv->SubItems->Add(item->exp.ToString());
			resultListView->Items->Add(ltv);
		}
		resultListView->EndUpdate();
	}
	else {
		resultListView->BeginUpdate();
		for each (CommitterSchema ^ item in result) {
			auto ltv = gcnew ListViewItem();
			ltv->Text = item->id.ToString();
			ltv->SubItems->Add(item->name);
			ltv->SubItems->Add(item->count.ToString());
			ltv->SubItems->Add(item->level.ToString());
			resultListView->Items->Add(ltv);
		}
		resultListView->EndUpdate();
	}
}
