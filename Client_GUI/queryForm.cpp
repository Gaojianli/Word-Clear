#include "queryForm.h"

System::Void ClientGUI::queryForm::processQuerry(System::Object^ sender, System::EventArgs^ e) {
	Object^ value;
	if (propertyPicker->SelectedItem->Equals("Name"))
		value = valueBox->Text;
	else
		value = Convert::ToInt32(valueBox->Text);
	String^ property;
	if (propertyPicker->SelectedItem->Equals("Committed Questions") || propertyPicker->SelectedItem->Equals("Passed Ranks"))
		property = "count";
	else
		property = propertyPicker->SelectedItem->ToString()->ToLower();
	auto queryResult = socketManager->customizeQuery(user, property, playerRadio->Checked, value);
	if (queryResult == nullptr || queryResult->Count == 0)
		MessageBox::Show("No matches found!", "Error: 404");
	else
		MessageBox::Show("Found!", "Error:404");
}
