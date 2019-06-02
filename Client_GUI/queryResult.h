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
	/// query result
	/// </summary>
	public ref class queryResult : public System::Windows::Forms::UserControl
	{
	private:List<UserSchema^>^ result;
	public:
		queryResult(List<UserSchema^>^ result);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~queryResult();
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
		void InitializeComponent(void);
#pragma endregion
	private: System::Void QueryResult_Load(System::Object^ sender, System::EventArgs^ e);
};
}
