#pragma once
#include "schema.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// set server host and port
	/// </summary>
	public ref class setServerForm : public System::Windows::Forms::Form
	{
	private:connectInfo^ conInfo;
	public:
		setServerForm(connectInfo^ conInfo);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~setServerForm();
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ nameBox;

	private: System::Windows::Forms::TextBox^ portBox;

	private: System::Windows::Forms::ErrorProvider^ errorProvider1;
	private: System::Windows::Forms::Button^ connectButton;
	private: System::Windows::Forms::Button^ testButton;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void);
#pragma endregion
	private: System::Void portBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	private: System::Void TestButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ConnectButton_Click(System::Object^ sender, System::EventArgs^ e);
};
}
