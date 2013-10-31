// window_test.cpp: главный файл проекта.

#include "stdafx.h"
#include "Form1.h"
#include "props.h"
#include "settings.h"


Settings settings;



using namespace window_test;

	System::Void props::button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 int size=8,level=2;
				 if (radioButton1->Checked)
					 size=4;
				 else if (radioButton2->Checked)
					 size=6;
				 if (radioButton7->Checked)
					 level=-1;
				 else if (radioButton4->Checked)
					 level=0;
				 else if (radioButton5->Checked)
					 level=1;
				 settings.level=level;
				 settings.size=size;
				 this->Close();
			 }

			 
	 System::Void props::props_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e, Form1^ ptr) {
			 game* curr;
			 curr = new game(settings.size, settings.level);
			 TLVar array=curr->draw(); 
			struct TVar *var;
			var = (*array.FindVar(0));
			if (var) do
			{
				ptr->Controls->Add(var->n);
				var=var->next;
			} while (var);

		 }

	 System::Void Form1::sett_Click(System::Object^  sender, System::EventArgs^  e) {
				 props ^ n_g = gcnew props();
				 n_g->Visible=true;
				 n_g->ptr=n_g->window;
			}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	props ^ temp0;
	Application::Run(temp0->window=gcnew Form1());
	return 0;
}
