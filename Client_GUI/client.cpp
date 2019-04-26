#include "MainForm.h"

using namespace ClientGUI;


int main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::Run(gcnew MainForm());
	return 0;
}