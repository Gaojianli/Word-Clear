#include "playForm.h"

inline System::Void ClientGUI::playForm::PlayForm_Load(System::Object^ sender, System::EventArgs^ e) {
	userInfo = Tuple::Create(user->count, user->exp, user->level);
	currentQuestionSet = socketManager->getQuestionsByLevel(user, currentLevel);
	levelLabel->Text = currentLevel.ToString();
	expLabel->Text = user->exp.ToString();
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
		String^ drawString = "Correct";
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
