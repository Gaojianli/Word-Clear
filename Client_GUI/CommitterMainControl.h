﻿#pragma once
#include "Committer.h"
#include "socketMgnt.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ClientGUI {

	/// <summary>
	/// Summary for CommitterMainControl
	/// </summary>
	public ref class CommitterMainControl : public System::Windows::Forms::UserControl
	{
	public: Committer^ user;
	public: socketMgnt^ socketManager;
	public:
		CommitterMainControl(Committer^ user, socketMgnt^ socketManager) :user(user), socketManager(socketManager)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CommitterMainControl()
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
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
