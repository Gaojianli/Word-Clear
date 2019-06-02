#pragma once
#include "schema.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// The list question form
	/// </summary>
	public ref class questionListForm : public System::Windows::Forms::Form
	{
	private:List<wordSchemaWithCommitter^>^ wordList;
	public:
		questionListForm(List<wordSchemaWithCommitter^>^ wordList);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~questionListForm();
	private: System::Windows::Forms::ListView^ wordListView;
	private: System::Windows::Forms::ColumnHeader^ wordHeader;
	private: System::Windows::Forms::ColumnHeader^ levelHeader;
	private: System::Windows::Forms::ColumnHeader^ committerHeader;

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
	private: System::Void QuestionListForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void QuestionListForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	};
}
