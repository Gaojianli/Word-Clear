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
	private: Panel^ panel;
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
			//fill the windows with the user control
			System::Windows::Forms::UserControl^ control;
			if (globalUser->isPlayer)
				control = gcnew ClientGUI::PlayerMainControl(dynamic_cast<Player^>(globalUser), socketManager);
			else
				control= gcnew ClientGUI::CommitterMainControl(dynamic_cast<Committer^>(globalUser), socketManager);
			control->Location = Point(0, 0);
			this->panel = gcnew Panel();
			this->panel->Controls->Add(control);
			this->Width = control->Width;
			this->Height = control->Height;
			this->panel->Location = Point(0, panel->Location.Y);
			this->panel->Size = control->Size;
			this->Size = control->Size;
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
			this->SuspendLayout();
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(418, 259);
			this->Name = L"MainForm";
			this->Text = L"Word Clear Game";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
