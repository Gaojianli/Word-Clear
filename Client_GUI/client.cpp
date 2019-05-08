#include "MainForm.h"

using namespace ClientGUI;
using namespace System::Reflection;
[assembly:AssemblyVersionAttribute("3.0.3")] ;
[STAThread]
int main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::Run(gcnew MainForm());
	return 0;
}