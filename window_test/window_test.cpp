#include "stdafx.h"
#include "Form1.h"
#include "props.h"
#include "settings.h"



using namespace window_test;

/* public ref class PTR : public System::Windows::Forms::Form
{
public:
	static Form1 ^ window;
	static TLVar ^ array;
};*/


System::Void props::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	int size = 8, level = 2;
	if (radioButton1->Checked)
		size = 4;
	else if (radioButton2->Checked)
		size = 6;
	if (radioButton7->Checked)
		level = -1;
	else if (radioButton4->Checked)
		level = 0;
	else if (radioButton5->Checked)
		level = 1;
	f->settings->level = level;
	f->settings->size = size;
	this->Visible = false;

}

System::Void props::props_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
	if (!Visible) {
		TLVar^ tlvar = gcnew TLVar(gcnew System::EventHandler(this->f, &Form1::cell_Click),f->settings);
		this->f->array = tlvar;
		this->f->panel1->Controls->Clear();
		TVar ^var;
		var = (this->f->array->FindVar(0, this->f->array->GetFirst()));
		if (var) do
		{
			this->f->panel1->Controls->Add(var->n);
			var = var->next;
		} while (var);
		this->f->label1->Visible = true;
		this->f->label4->Visible = true;
		this->f->label1->Text = (System::Convert::ToString(this->f->array->b_score));
		this->f->label4->Text = (System::Convert::ToString(this->f->array->r_score));
		this->f->label2->Visible = true;
	}
}

System::Void Form1::sett_Click(System::Object^  sender, System::EventArgs^  e) {
	props ^ n_g = gcnew props(this);
	n_g->Visible = true;
}



System::Void Form1::cell_Click(System::Object^  sender, System::EventArgs^  e) {
	// human turn
	TVar ^var;
	int test = (int)(((Control^)sender)->Tag);
	var = (array->FindVar((int)(((Control^)sender)->Tag), array->GetFirst()));
	if (var->n->inc('b')) 
		array->explosion(settings->size, (int)(((Control^)sender)->Tag), 'b');
	
	// refresh the score
	array->b_score = array->GetScore('b');
	this->label1->Text = (System::Convert::ToString(array->b_score));
	// prepare AI turn
//	this->label2->Hide();
	label7->ForeColor = System::Drawing::Color::Red;
	//PTR::window->label7->Hide();
	//PTR::window->label7->Show();
//	this->label7->Hide();
//	this->label7->Show();
	//this->label7->Show();
	//this->label7->BringToFront();
	this->label7->Location = System::Drawing::Point(440, 37);
	label7->BackColor = System::Drawing::Color::Black;
	this->label7->BringToFront();
	//setVisibleLabel7();

	//bool testt = PTR::window->label3->Visible;
	//PTR::window->label3->Visible = true;
	this->panel1->Enabled = false;



	_sleep(10000);
	this->panel1->Enabled = true;
	// AI turn	 
	this->array->ai(settings->size, settings->level);
	// refresh the score
	this->array->r_score = array->GetScore('r');
	this->label4->Text = (System::Convert::ToString(array->r_score));
	// prepare human turn
	this->label2->Visible = true;
	this->label7->Location = System::Drawing::Point(417, 17);
	label7->ForeColor = System::Drawing::Color::Green;
	//label7->ForeColor = Form1::BackColor;
//	this->label7->Hide();
	//	PTR::window->label7->Hide();
	// redraw

		var = (array->FindVar(0, array->GetFirst()));
		if (var) do
		{
			var->n->display();
			var = var->next;
		} while (var);

	// check if the game is over
	if ((array->b_score >= array->w_score) && (array->b_score>array->r_score))
		array->who_won = 'b';
	if ((array->r_score >= array->w_score) && (array->r_score>array->b_score))
		array->who_won = 'r';
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Âêëþ÷åíèå âèçóàëüíûõ ýôôåêòîâ Windows XP äî ñîçäàíèÿ êàêèõ-ëèáî ýëåìåíòîâ óïðàâëåíèÿ
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Ñîçäàíèå ãëàâíîãî îêíà è åãî çàïóñê
//	PTR::window = gcnew Form1();
	Application::Run(gcnew Form1());
	return 0;
}
