#include "queryResult.h"

inline System::Void ClientGUI::queryResult::QueryResult_Load(System::Object^ sender, System::EventArgs^ e) {
	//load data
	result->Sort(gcnew CompareUser());
	if (result[0]->isPlayer) {
		resultListView->BeginUpdate();
		for each (PlayerSchema ^ item in result) {
			auto ltv = gcnew ListViewItem();
			ltv->Text = item->id.ToString();
			ltv->SubItems->Add(item->name);
			ltv->SubItems->Add(item->count.ToString());
			ltv->SubItems->Add(item->level.ToString());
			ltv->SubItems->Add(item->exp.ToString());
			resultListView->Items->Add(ltv);
		}
		resultListView->EndUpdate();
	}
	else {
		resultListView->BeginUpdate();
		for each (CommitterSchema ^ item in result) {
			auto ltv = gcnew ListViewItem();
			ltv->Text = item->id.ToString();
			ltv->SubItems->Add(item->name);
			ltv->SubItems->Add(item->count.ToString());
			ltv->SubItems->Add(item->level.ToString());
			resultListView->Items->Add(ltv);
		}
		resultListView->EndUpdate();
	}
}
