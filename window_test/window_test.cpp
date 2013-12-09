#include "stdafx.h"
#include "Form1.h"
#include "props.h"
#include "settings.h"

using namespace window_test;


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
		this->f->panel1->Enabled = true;
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
	//array->CheckValues(settings);
	var = (array->FindVar((int)(((Control^)sender)->Tag), array->GetFirst()));
	if (var->n->inc(array->player)) 
		array->explosion(settings->size, (int)(((Control^)sender)->Tag), array->player);
	
	// refresh the score
	array->b_score = array->GetScore(array->player);
	this->label1->Text = (System::Convert::ToString(array->b_score));

	// prepare next turn
	if (settings->level==-1) {
		switch (array->player) {
			case 'b': array->player = 'r'; 
					this->label2->Visible = false;
					this->label7->Visible = true;
				break;
			case 'r': array->player = 'b'; 
					this->label2->Visible = true;
					this->label7->Visible = false;
				break;
		}
		// refresh the score
		this->array->r_score = array->GetScore('r');
		this->label4->Text = (System::Convert::ToString(array->r_score));
		this->gameover();
	}
	else {
		this->label2->Visible = false;
		this->label7->Visible = true;
		this->panel1->Enabled = false;
		this->timer1->Start();
	}	
	// the rest of turn code is located in timer1_Tick
}

System::Void Form1::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	this->panel1->Enabled = true;
	// AI turn	 
	this->array->ai(settings->size, settings->level);
	// refresh the score
	this->array->r_score = array->GetScore('r');
	this->label4->Text = (System::Convert::ToString(array->r_score));

	//check array
	this->array->CheckValues(settings);

	// prepare human turn
	this->label2->Visible = true;
	this->label7->Visible = false;

	this->gameover();
	this->timer1->Stop();
}

void Form1::gameover() {
	// redraw
	TVar ^var;
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
	if (array->who_won != 'n') {
		switch (array->who_won) {
		case 'b': this->label2->Text = "Синие победили";
			break;
		case 'r': this->label7->Text = "Красные победили";
			break;
		}
		this->panel1->Enabled = false;
	}
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Form1());
	return 0;
}
