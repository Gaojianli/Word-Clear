#pragma once
#include "socketMgnt.h"
#include "Player.h"
#include "Committer.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// The form use for query user
	/// </summary>
	public ref class queryForm : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::GroupBox^ groupBox1;
	public:
	private: System::Windows::Forms::ComboBox^ propertyPicker;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RadioButton^ committerRadio;
	private: System::Windows::Forms::RadioButton^ playerRadio;
	private: System::Windows::Forms::Label^ label1;
	public: User^ user;
	private: System::Windows::Forms::TextBox^ valueBox;
	public:

	public:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ queryButton;
	private: System::Windows::Forms::ErrorProvider^ errorProvider1;

	public: socketMgnt^ socketManager;
	public:
		queryForm(User^ user, socketMgnt^ socketManager);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~queryForm();
	private: System::ComponentModel::IContainer^ components;
	protected:

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
	private: System::Void QueryForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void PlayerRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void CommitterRadio_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void valueBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ValueBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	private: System::Void PropertyPicker_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void processQuerry(System::Object^ sender, System::EventArgs^ e);
	};
}
