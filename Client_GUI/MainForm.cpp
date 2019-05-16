#include "MainForm.h"

inline ClientGUI::MainForm::MainForm(void)
{
	InitializeComponent();
	loginForm^ loginfrom;
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	try {
		socketManager = socketMgnt::getInstance();
		loginfrom = gcnew ClientGUI::loginForm(this, socketManager);
		loginfrom->init(globalUser);
		if (loginfrom->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
			System::Environment::Exit(2);
		}
	}
	catch (Exception^ e) {
		MessageBox::Show(e->ToString(), "Error");
		Environment::Exit(e->GetHashCode());
	}
	finally{
		if (loginfrom)
		delete loginfrom;
	}
		//
		//TODO: Add the constructor code here
		//
}

/// <summary>
/// Clean up any resources being used.
/// </summary>

inline ClientGUI::MainForm::~MainForm()
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

inline void ClientGUI::MainForm::InitializeComponent(void)
{
	this->panel1 = (gcnew System::Windows::Forms::Panel());
	this->SuspendLayout();
	// 
	// panel1
	// 
	this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
	this->panel1->Location = System::Drawing::Point(0, 0);
	this->panel1->Name = L"panel1";
	this->panel1->Size = System::Drawing::Size(650, 376);
	this->panel1->TabIndex = 0;
	// 
	// MainForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(650, 376);
	this->Controls->Add(this->panel1);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
	this->Name = L"MainForm";
	this->Text = L"Word Clear Game";
	this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
	this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
	this->ResumeLayout(false);

}

inline System::Void ClientGUI::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	//fill the windows with the user control
	System::Windows::Forms::UserControl^ control;
	if (globalUser->isPlayer)
		control = gcnew ClientGUI::PlayerMainControl(dynamic_cast<Player^>(globalUser), socketManager, this);
	else
		control = gcnew ClientGUI::CommitterMainControl(dynamic_cast<Committer^>(globalUser), socketManager);
	control->Location = Point(0, 0);
	this->panel1->Controls->Add(control);
	this->Width = control->Width;
	this->Height = control->Height;
	this->panel1->Location = Point(0, panel1->Location.Y);
	this->panel1->Size = control->Size;
	this->Size = control->Size;
	this->Height = this->Height + 60;
	GC::Collect();
}

inline System::Void ClientGUI::MainForm::MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	delete socketManager;
	Environment::Exit(0);
}
