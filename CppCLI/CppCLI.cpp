#include "pch.h"

using namespace System;
using namespace WPF;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	WPF::MainWindow^ main = gcnew WPF::MainWindow();
	main->ShowDialog();
    return 0;
}
