#pragma once
#include "socketMgnt.h"
#include "Player.h"
namespace ClientGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// The form used for play
	/// </summary>
	public ref class playForm : public System::Windows::Forms::Form
	{
	public: socketMgnt^ socketManager;
	public: Player^ user;
	private: Graphics^ g;
	private: int currentLevel;
	private: bool failFlag = false;
	private: int showTime;
	private: Tuple<int, int, int>^ userInfo;
	private: System::Windows::Forms::Button^ startButton;
	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ timeOutLabel;
	private: System::Windows::Forms::Label^ label5;
	private: List<wordSchema^>^ currentQuestionSet;
	private: System::Windows::Forms::Button^ nextButton;
	private:String^ currentWord;
	private: System::Windows::Forms::Button^ exitButton;
	private:int countOnCurrentLevel;
	public:
		playForm(Player^ user, socketMgnt^ socketManager);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~playForm();
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ answerBox;
	private: System::Windows::Forms::Button^ confirmButton;
	protected:


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ levelLabel;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ expLabel;
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
	private: System::Void PlayForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void PlayForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: void hideConfirm();
	private: void showConfirm();
	private: System::Void StartButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Timer_Tick(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ConfirmButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void AnswerBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void NextButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ExitButton_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
