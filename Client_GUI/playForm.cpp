#include "playForm.h"

inline ClientGUI::playForm::playForm(Player^ user, socketMgnt^ socketManager) :user(user), socketManager(socketManager) {
	InitializeComponent();
	currentLevel = 1;
	showTime = 5;
	hideConfirm();
	label4->Hide();
	timeOutLabel->Hide();
	label5->Hide();
	nextButton->Hide();
	exitButton->Hide();
	//
	//TODO: Add the constructor code here
	//
}

/// <summary>
/// Clean up any resources being used.
/// </summary>

inline ClientGUI::playForm::~playForm()
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

inline void ClientGUI::playForm::InitializeComponent(void)
{
	this->components = (gcnew System::ComponentModel::Container());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->answerBox = (gcnew System::Windows::Forms::TextBox());
	this->confirmButton = (gcnew System::Windows::Forms::Button());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->levelLabel = (gcnew System::Windows::Forms::Label());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->expLabel = (gcnew System::Windows::Forms::Label());
	this->startButton = (gcnew System::Windows::Forms::Button());
	this->timer = (gcnew System::Windows::Forms::Timer(this->components));
	this->label4 = (gcnew System::Windows::Forms::Label());
	this->timeOutLabel = (gcnew System::Windows::Forms::Label());
	this->label5 = (gcnew System::Windows::Forms::Label());
	this->nextButton = (gcnew System::Windows::Forms::Button());
	this->exitButton = (gcnew System::Windows::Forms::Button());
	this->SuspendLayout();
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Location = System::Drawing::Point(183, 181);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(102, 20);
	this->label1->TabIndex = 0;
	this->label1->Text = L"Your answer:";
	// 
	// answerBox
	// 
	this->answerBox->ImeMode = System::Windows::Forms::ImeMode::Off;
	this->answerBox->Location = System::Drawing::Point(291, 178);
	this->answerBox->Name = L"answerBox";
	this->answerBox->Size = System::Drawing::Size(135, 26);
	this->answerBox->TabIndex = 1;
	this->answerBox->TextChanged += gcnew System::EventHandler(this, &playForm::AnswerBox_TextChanged);
	// 
	// confirmButton
	// 
	this->confirmButton->Enabled = false;
	this->confirmButton->Location = System::Drawing::Point(441, 176);
	this->confirmButton->Name = L"confirmButton";
	this->confirmButton->Size = System::Drawing::Size(86, 30);
	this->confirmButton->TabIndex = 2;
	this->confirmButton->Text = L"Confirm";
	this->confirmButton->UseVisualStyleBackColor = true;
	this->confirmButton->Click += gcnew System::EventHandler(this, &playForm::ConfirmButton_Click);
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Location = System::Drawing::Point(166, 23);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(107, 20);
	this->label2->TabIndex = 3;
	this->label2->Text = L"Current Level:";
	// 
	// levelLabel
	// 
	this->levelLabel->AutoSize = true;
	this->levelLabel->Location = System::Drawing::Point(279, 23);
	this->levelLabel->Name = L"levelLabel";
	this->levelLabel->Size = System::Drawing::Size(50, 20);
	this->levelLabel->TabIndex = 4;
	this->levelLabel->Text = L"{level}";
	// 
	// label3
	// 
	this->label3->AutoSize = true;
	this->label3->Location = System::Drawing::Point(447, 23);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(40, 20);
	this->label3->TabIndex = 5;
	this->label3->Text = L"Exp:";
	// 
	// expLabel
	// 
	this->expLabel->AutoSize = true;
	this->expLabel->Location = System::Drawing::Point(493, 23);
	this->expLabel->Name = L"expLabel";
	this->expLabel->Size = System::Drawing::Size(44, 20);
	this->expLabel->TabIndex = 6;
	this->expLabel->Text = L"{exp}";
	// 
	// startButton
	// 
	this->startButton->Location = System::Drawing::Point(283, 152);
	this->startButton->Name = L"startButton";
	this->startButton->Size = System::Drawing::Size(196, 78);
	this->startButton->TabIndex = 7;
	this->startButton->Text = L"Start";
	this->startButton->UseVisualStyleBackColor = true;
	this->startButton->Click += gcnew System::EventHandler(this, &playForm::StartButton_Click);
	// 
	// timer
	// 
	this->timer->Interval = 1000;
	this->timer->Tick += gcnew System::EventHandler(this, &playForm::Timer_Tick);
	// 
	// label4
	// 
	this->label4->AutoSize = true;
	this->label4->Location = System::Drawing::Point(236, 309);
	this->label4->Name = L"label4";
	this->label4->Size = System::Drawing::Size(165, 20);
	this->label4->TabIndex = 8;
	this->label4->Text = L"Word will disappear in ";
	// 
	// timeOutLabel
	// 
	this->timeOutLabel->AutoSize = true;
	this->timeOutLabel->Location = System::Drawing::Point(407, 309);
	this->timeOutLabel->Name = L"timeOutLabel";
	this->timeOutLabel->Size = System::Drawing::Size(24, 20);
	this->timeOutLabel->TabIndex = 9;
	this->timeOutLabel->Text = L"{t}";
	// 
	// label5
	// 
	this->label5->AutoSize = true;
	this->label5->Location = System::Drawing::Point(437, 309);
	this->label5->Name = L"label5";
	this->label5->Size = System::Drawing::Size(82, 20);
	this->label5->TabIndex = 10;
	this->label5->Text = L"Second(s)";
	// 
	// nextButton
	// 
	this->nextButton->Location = System::Drawing::Point(259, 309);
	this->nextButton->Name = L"nextButton";
	this->nextButton->Size = System::Drawing::Size(84, 33);
	this->nextButton->TabIndex = 11;
	this->nextButton->Text = L"Next";
	this->nextButton->UseVisualStyleBackColor = true;
	this->nextButton->Click += gcnew System::EventHandler(this, &playForm::NextButton_Click);
	// 
	// exitButton
	// 
	this->exitButton->Location = System::Drawing::Point(395, 309);
	this->exitButton->Name = L"exitButton";
	this->exitButton->Size = System::Drawing::Size(84, 33);
	this->exitButton->TabIndex = 12;
	this->exitButton->Text = L"Quit";
	this->exitButton->UseVisualStyleBackColor = true;
	this->exitButton->Click += gcnew System::EventHandler(this, &playForm::ExitButton_Click);
	// 
	// playForm
	// 
	this->AcceptButton = this->startButton;
	this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(742, 410);
	this->Controls->Add(this->exitButton);
	this->Controls->Add(this->nextButton);
	this->Controls->Add(this->label5);
	this->Controls->Add(this->timeOutLabel);
	this->Controls->Add(this->label4);
	this->Controls->Add(this->startButton);
	this->Controls->Add(this->expLabel);
	this->Controls->Add(this->label3);
	this->Controls->Add(this->levelLabel);
	this->Controls->Add(this->label2);
	this->Controls->Add(this->confirmButton);
	this->Controls->Add(this->answerBox);
	this->Controls->Add(this->label1);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->Margin = System::Windows::Forms::Padding(2);
	this->MaximizeBox = false;
	this->Name = L"playForm";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->Text = L"Word Clear ";
	this->Load += gcnew System::EventHandler(this, &playForm::PlayForm_Load);
	this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &playForm::PlayForm_Paint);
	this->ResumeLayout(false);
	this->PerformLayout();

}

inline System::Void ClientGUI::playForm::PlayForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	g = this->CreateGraphics();
}

inline System::Void ClientGUI::playForm::PlayForm_Load(System::Object^ sender, System::EventArgs^ e) {
	userInfo = Tuple::Create(user->count, user->exp, user->level);
	currentQuestionSet = socketManager->getQuestionsByLevel(user, currentLevel);
	if (currentQuestionSet == nullptr) {
		this->Close();
		return;
	}
	levelLabel->Text = currentLevel.ToString();
	expLabel->Text = user->exp.ToString();
}

inline void ClientGUI::playForm::hideConfirm() {
	label1->Hide();
	answerBox->Hide();
	confirmButton->Hide();
}

inline void ClientGUI::playForm::showConfirm() {
	label1->Show();
	answerBox->Show();
	confirmButton->Show();
}

inline System::Void ClientGUI::playForm::StartButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (currentQuestionSet && currentQuestionSet->Count != 0) {
		countOnCurrentLevel = 0;
		startButton->Hide();
		g->Clear(this->BackColor);
		int index = (gcnew Random())->Next(0, currentQuestionSet->Count);
		String^ drawString = currentQuestionSet[index]->word;
		currentWord = drawString;
		currentQuestionSet->RemoveAt(index);
		auto drawFont = gcnew System::Drawing::Font("Arial", 16);
		auto drawBrush = gcnew	System::Drawing::SolidBrush(System::Drawing::Color::Black);
		float x = (float)(this->Width - 100 - 16 * drawString->Length) / 2;
		float y = (float)(this->Height - 140 - 16) / 2;
		auto drawFormat = gcnew System::Drawing::StringFormat();
		g->DrawString(drawString, drawFont, drawBrush, x, y, drawFormat);
		timer->Enabled = true;
		label4->Show();
		timeOutLabel->Text = showTime.ToString();
		timeOutLabel->Show();
		label5->Show();
	}
}

inline System::Void ClientGUI::playForm::Timer_Tick(System::Object^ sender, System::EventArgs^ e) {
	if (showTime > 0) {
		showTime--;
		timeOutLabel->Text = showTime.ToString();
	}
	else {
		timer->Enabled = false;
		label4->Hide();
		timeOutLabel->Hide();
		label5->Hide();
		g->Clear(this->BackColor);
		showConfirm();
	}

}

System::Void ClientGUI::playForm::ConfirmButton_Click(System::Object^ sender, System::EventArgs^ e) {
	hideConfirm();
	exitButton->Show();
	if (answerBox->Text->Equals(currentWord)) {
		answerBox->Text = String::Empty;
		nextButton->Show();
		String^ drawString = "Correct!";
		auto drawFont = gcnew System::Drawing::Font("Arial", 16);
		auto drawBrush = gcnew	System::Drawing::SolidBrush(System::Drawing::Color::Green);
		float x = (float)(this->Width - 100 - 16 * drawString->Length) / 2;
		float y = (float)(this->Height - 140 - 16) / 2;
		auto drawFormat = gcnew System::Drawing::StringFormat();
		g->DrawString(drawString, drawFont, drawBrush, x, y, drawFormat);
		countOnCurrentLevel++;
		user->addCount();
		expLabel->Text = user->exp.ToString();
		//level up!
		if (countOnCurrentLevel > currentLevel && currentLevel < 10) {
			currentLevel++;
			countOnCurrentLevel = 0;
			levelLabel->Text = currentLevel.ToString();
			delete currentQuestionSet;
			currentQuestionSet = socketManager->getQuestionsByLevel(user, currentLevel);
			if (currentQuestionSet == nullptr) {
				this->Close();
				return;
			}
		}
		if (currentLevel == 10 && currentQuestionSet->Count == 0) {
			MessageBox::Show("You have passed all ranks!", "Congratulation");
			this->DialogResult = Windows::Forms::DialogResult::OK;
		}
	}
	else {
		failFlag = true;
		String^ drawString = "Wrong answer!";
		auto drawFont = gcnew System::Drawing::Font("Arial", 16);
		auto drawBrush = gcnew	System::Drawing::SolidBrush(System::Drawing::Color::Red);
		float x = (float)(this->Width - 100 - 16 * drawString->Length) / 2;
		float y = (float)(this->Height - 180 - 16) / 2;
		auto drawFormat = gcnew System::Drawing::StringFormat();
		g->DrawString(drawString, drawFont, drawBrush, x, y, drawFormat);
		g->DrawString("Correct answer is " + currentWord, gcnew System::Drawing::Font("Arial", 12), drawBrush, x, y + 60, drawFormat);
	}

}

inline System::Void ClientGUI::playForm::AnswerBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	if (answerBox->Text != String::Empty)
		confirmButton->Enabled = true;
	else
		confirmButton->Enabled = false;
}

System::Void ClientGUI::playForm::NextButton_Click(System::Object^ sender, System::EventArgs^ e) {
	nextButton->Hide();
	exitButton->Hide();
	if (currentQuestionSet->Count == 0) {
		delete currentQuestionSet;
		currentQuestionSet = socketManager->getQuestionsByLevel(user, ++currentLevel);
	}
	g->Clear(this->BackColor);
	int index = (gcnew Random())->Next(0, currentQuestionSet->Count);
	String^ drawString = currentQuestionSet[index]->word;
	currentWord = drawString;
	currentQuestionSet->RemoveAt(index);
	auto drawFont = gcnew System::Drawing::Font("Arial", 16);
	auto drawBrush = gcnew	System::Drawing::SolidBrush(System::Drawing::Color::Black);
	float x = (float)(this->Width - 100 - 16 * drawString->Length) / 2;
	float y = (float)(this->Height - 140 - 16) / 2;
	auto drawFormat = gcnew System::Drawing::StringFormat();
	g->DrawString(drawString, drawFont, drawBrush, x, y, drawFormat);
	label4->Show();
	timeOutLabel->Text = showTime.ToString();
	timeOutLabel->Show();
	label5->Show();
	showTime = 5 - currentLevel / 5;
	timeOutLabel->Text = showTime.ToString();
	timer->Enabled = true;
}

inline System::Void ClientGUI::playForm::ExitButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (failFlag) {
		//revert changes
		user->count = userInfo->Item1;
		user->exp = userInfo->Item2;
		user->level = userInfo->Item3;
		this->DialogResult = Windows::Forms::DialogResult::Abort;
	}
	else
		this->DialogResult = Windows::Forms::DialogResult::OK;
}
