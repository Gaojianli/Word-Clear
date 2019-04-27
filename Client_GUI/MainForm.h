#pragma once
#include "login.h"
#include "user.h"
#include "socketMgnt.h"
#include "PlayerMainControl.h"
#include "CommitterMainControl.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public: property User^ globalUser;
	public: socketMgnt^ socketManager;
	public:
		MainForm(void)
		{
			InitializeComponent();
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			socketManager = socketMgnt::getInstance();
			auto login = gcnew ClientGUI::login(this, socketManager);
			login->init(globalUser);
			if (login->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
				this->Close();
				System::Environment::Exit(2);
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	protected:

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
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->Name = L"MainForm";
			this->Text = L"Word Clear Game";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		//fill the windows with the user control
		System::Windows::Forms::UserControl^ control;
		if (globalUser->isPlayer)
			control = gcnew ClientGUI::PlayerMainControl(dynamic_cast<Player^>(globalUser), socketManager);
		else
			control = gcnew ClientGUI::CommitterMainControl(dynamic_cast<Committer^>(globalUser), socketManager);
		control->Location = Point(0, 0);
		this->panel1->Controls->Add(control);
		this->Width = control->Width;
		this->Height = control->Height;
		this->panel1->Location = Point(0, panel1->Location.Y);
		this->panel1->Size = control->Size;
		this->Size = control->Size;
		this->Height = this->Height + 80;
		GC::Collect();
	}
	};
}
