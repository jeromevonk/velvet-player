// VelvetPlayer.cpp : MainForm project file.

#include "stdafx.h"
#include "Main.h"

using namespace VelvetPlayer;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
   // Enabling Windows XP visual effects before any controls are created
   Application::EnableVisualStyles();
   Application::SetCompatibleTextRenderingDefault(false);

   // Create the MainForm window and run it
   Application::Run( gcnew Main() );
   return 0;
}
