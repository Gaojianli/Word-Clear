#include "setServerForm.h"

inline System::Void ClientGUI::setServerForm::TestButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (nameBox->Text != String::Empty && portBox->Text != String::Empty) {
		try {
			int port = Convert::ToInt32(portBox->Text);
			auto host = System::Net::Dns::GetHostEntry(nameBox->Text);
			auto ip = host->AddressList[0];
			auto ipe = gcnew System::Net::IPEndPoint(ip, port);
			auto connection = gcnew System::Net::Sockets::Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Stream, System::Net::Sockets::ProtocolType::Tcp);
			connection->Connect(ipe);
			bool condition1 = connection->Poll(200, System::Net::Sockets::SelectMode::SelectRead);
			bool condition2 = (connection->Available == 0);
			if (condition1 && condition2) {
				connection->Close();
				delete connection;
				throw gcnew Exception("Server empty response.");
			}
			else {
				System::Windows::Forms::MessageBox::Show("Connection vaild!", "info");
				connection->Close();
				delete connection;
			}
		}
		catch (Exception^ e) {
			System::Windows::Forms::MessageBox::Show("Can't connect to server!" + e->ToString(), "Error");
		}
	}
}
