#pragma once
#include "loginForm.h"
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
		MainForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm();
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
		void InitializeComponent(void);
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
};
}
