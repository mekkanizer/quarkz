// window_test.cpp: главный файл проекта.

#include "stdafx.h"
#include "Form1.h"
#include "props.h"

Settings settings;

using namespace window_test;

	System::Void props<Form1>::button1_Click(System::Object^  sender, System::EventArgs^  e) {
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
				 this->Visible = false;

			 }

	System::Void props<Form1>::props_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
		if (!Visible) {
			game* curr;
			curr = new game(settings.size, settings.level);
			window->panel1->Controls->Clear();
			TLVar ^ array = curr->draw();
			TVar ^var;
			var = (array->FindVar(0, array->GetFirst()));
			if (var) do
			{
				window->panel1->Controls->Add(var->n);
				var = var->next;
			} while (var);
			window->label1->Visible = true;
			window->label4->Visible = true;

			bool b=true;

			do {
				window->label1->Text=(System::Convert::ToString(curr->b_score));
				window->label4->Text=(System::Convert::ToString(curr->r_score));
				if (curr->redraw) {
					curr->redraw=false;
					var = (array->FindVar(0, array->GetFirst()));
					if (var) do
					{
						var->n->display();
						var = var->next;
					} while (var);
				}
				if (curr->q) {
					window->panel1->Enabled = false;
					window->label2->Visible = false;
					window->label3->Visible = true;
					_sleep(1000);
					window->panel1->Enabled = true;
				}
				else {
					window->label2->Visible = true;
					window->label3->Visible = false;
				} 
			} while (b==false); //(curr->turn(array) == 'n');
		}
	}

	 System::Void Form1::sett_Click(System::Object^  sender, System::EventArgs^  e) {
				 props<Form1> ^ n_g = gcnew props<Form1>();
				 n_g->window = this;
				 n_g->Visible=true;
			}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск

	props<Form1> ^ temp0=gcnew props<Form1>();
	temp0->window = gcnew Form1();
	Application::Run(temp0->window);
	return 0;
}
