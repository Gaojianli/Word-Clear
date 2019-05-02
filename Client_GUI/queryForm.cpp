﻿#include "queryForm.h"
#include "queryResult.h"
System::Void ClientGUI::queryForm::processQuerry(System::Object^ sender, System::EventArgs^ e) {
	Object^ value;
	if (propertyPicker->SelectedItem->Equals("Name"))
		value = valueBox->Text;
	else
		value = Convert::ToInt32(valueBox->Text);
	//alias property
	String^ property;
	if (propertyPicker->SelectedItem->Equals("Committed Questions") || propertyPicker->SelectedItem->Equals("Passed Ranks"))
		property = "count";
	else if (propertyPicker->SelectedItem->Equals("UID"))
		property = "id";
	else
		property = propertyPicker->SelectedItem->ToString()->ToLower();

	auto queryResult = socketManager->customizeQuery(user, property, playerRadio->Checked, value);
	if (queryResult == nullptr || queryResult->Count == 0)
		MessageBox::Show("No matches found!", "Error: 404");
	else {
		auto resultForm = gcnew Form();
		auto userControl = gcnew ClientGUI::queryResult(queryResult);
		userControl->Location = Point(0, 0);
		resultForm->Size = userControl->Size;
		resultForm->Controls->Add(userControl);
		userControl->Location = Point(0, userControl->Location.Y);
		resultForm->Height = userControl->Height + 80;
		resultForm->Text = "Query Result";
		resultForm->StartPosition = Windows::Forms::FormStartPosition::CenterScreen;
		resultForm->Show();
	}
		
}
