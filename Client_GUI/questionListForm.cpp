#include "questionListForm.h"
#include "schema.h"
/// <summary>
/// Required method for Designer support - do not modify
/// the contents of this method with the code editor.
/// </summary>



/// <summary>
/// Required method for Designer support - do not modify
/// the contents of this method with the code editor.
/// </summary>


/// <summary>
/// Clean up any resources being used.
/// </summary>

inline ClientGUI::questionListForm::questionListForm(List<wordSchemaWithCommitter^>^ wordList) :wordList(wordList)
{
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//
}

inline ClientGUI::questionListForm::~questionListForm()
{
	if (components)
	{
		delete components;
	}
}

inline void ClientGUI::questionListForm::InitializeComponent(void) {
	this->wordListView = (gcnew System::Windows::Forms::ListView());
	this->wordHeader = (gcnew System::Windows::Forms::ColumnHeader());
	this->levelHeader = (gcnew System::Windows::Forms::ColumnHeader());
	this->committerHeader = (gcnew System::Windows::Forms::ColumnHeader());
	this->SuspendLayout();
	// 
	// wordListView
	// 
	this->wordListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
		this->wordHeader, this->levelHeader,
			this->committerHeader
	});
	this->wordListView->Dock = System::Windows::Forms::DockStyle::Fill;
	this->wordListView->FullRowSelect = true;
	this->wordListView->GridLines = true;
	this->wordListView->HideSelection = false;
	this->wordListView->LabelWrap = false;
	this->wordListView->Location = System::Drawing::Point(0, 0);
	this->wordListView->MultiSelect = false;
	this->wordListView->Name = L"wordListView";
	this->wordListView->Size = System::Drawing::Size(580, 424);
	this->wordListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
	this->wordListView->TabIndex = 2;
	this->wordListView->UseCompatibleStateImageBehavior = false;
	this->wordListView->View = System::Windows::Forms::View::Details;
	// 
	// wordHeader
	// 
	this->wordHeader->Text = L"Word";
	this->wordHeader->Width = 170;
	// 
	// levelHeader
	// 
	this->levelHeader->Text = L"Difficulty";
	this->levelHeader->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
	this->levelHeader->Width = 172;
	// 
	// committerHeader
	// 
	this->committerHeader->Text = L"Committer";
	this->committerHeader->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
	this->committerHeader->Width = 189;
	// 
	// questionListForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(580, 424);
	this->Controls->Add(this->wordListView);
	this->MaximizeBox = false;
	this->Name = L"questionListForm";
	this->Text = L"Word List";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &questionListForm::QuestionListForm_FormClosed);
	this->Load += gcnew System::EventHandler(this, &questionListForm::QuestionListForm_Load);
	this->ResumeLayout(false);

}

inline System::Void ClientGUI::questionListForm::QuestionListForm_Load(System::Object^ sender, System::EventArgs^ e) {
	wordList->Sort(gcnew CompareWord());
	wordListView->BeginUpdate();
	for each (auto word in wordList){
		auto ltv = gcnew ListViewItem();
		ltv->Text = word->word;
		ltv->SubItems->Add(word->level.ToString());
		ltv->SubItems->Add(word->committerName);
		wordListView->Items->Add(ltv);
	}
	wordListView->EndUpdate();
}

inline System::Void ClientGUI::questionListForm::QuestionListForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	delete wordList;
	GC::Collect();
}
