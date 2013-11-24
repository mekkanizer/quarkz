#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

public ref class Settings
{
public:
	int size, level;
};

//extern Settings settings;

public ref struct cell : public System::Windows::Forms::Button {
	char c_color; //n - neutral; r - red; b - blue;
	int thr; //threshold (determined by cell position in grid: corner - 3; border - 5; else - 8)
	int value;
public:
	void display() {
		Text::set(System::Convert::ToString(value));
		switch (c_color)
		{
		case 'n': ForeColor::set(System::Drawing::Color::Black);
			break;
		case 'r': ForeColor::set(System::Drawing::Color::Red);
			break;
		case 'b': ForeColor::set(System::Drawing::Color::Blue);
			break;
		}
	}

	cell(char c_c0l0r, int thr35h0ld, int valu3, int xx, int yy, int i, System::EventHandler^ eh,Settings^ settings) :c_color(c_c0l0r), thr(thr35h0ld), value(valu3) {
		Size = System::Drawing::Size(50, 50);
		Location = System::Drawing::Point(xx * 50, yy * 50);
		display();
		Click += eh;// gcnew System::EventHandler(this, &cell::cell_Click);
		Tag::set(settings->size*settings->size-i-1);
	}
	bool inc(char p_color) {
		bool explode = false;
		value++;
		if (value>thr)
			explode = true;
		c_color = p_color;
		return explode;
	}
	//System::Void cell_Click(System::Object^  sender, System::EventArgs^  e);
};

public ref struct TVar {
	cell^ n;
	TVar^ next;
};

public ref class TLVar {
private:
	TVar ^First;
public:
	int b_score; // blue player score
	int r_score; // red player score
	int w_score; // score enough to win
	char fill; // b - blank; t-triangles; x - cross; l - lines
	char who_won;

	bool NewVar(char c_c0l0r, int thr35h0ld, int valu3, int xx, int yy, int i,System::EventHandler^ eh,Settings^ settings) {
		TVar ^ n = gcnew TVar();
		if (n)
		{
			cell^ x = gcnew cell(c_c0l0r, thr35h0ld, valu3, xx, yy, i,eh,settings);
			n->n = x;
			n->next = First;
			First = n;
		}
		return true;
	}


public:

	TLVar(System::EventHandler^ eh,Settings^ settings){
		w_score = settings->size * 10;
		b_score = 0;
		r_score = 0;
		who_won = 'n';
		int thr;
		for (int i = 0; i < settings->size; i++) {
			if ((i == 0) || (i == (settings->size - 1)) || (i == (settings->size*(settings->size - 1))) || (i == (settings->size ^ 2 - 1)))
				thr = 3;
			else
			if ((i<(settings->size - 1)) || (i>(settings->size*(settings->size - 1))) || ((i%settings->size) == 0) || ((i%settings->size) - (settings->size - 1) == 0))
				thr = 5;
			else
				thr = 8;
			for (int j = 0; j < settings->size; j++) {
				int test = j + (settings->size*i);
				NewVar('n', thr, 0, i + 2, j + 2, j+(settings->size*i),eh,settings);
			}
		}
	}


	TVar ^ GetFirst() {
		return First;
	}

	TVar^ FindVar(int pos, TVar^ First) {
		if (pos == 0)return First;
		return FindVar(pos - 1, First->next);
	}

	bool explosion(int size, int pos, char p_color) {
		bool result = false;
		((FindVar(pos, First))->n)->value = 0;
		((FindVar(pos, First))->n)->c_color = 'n';
		if (pos<size - 1)
		if (((FindVar(pos + 1, First))->n)->inc(p_color)) {
			result = true;
			explosion(size, pos, 'r');
		}
		if (pos>0)
		if (((FindVar(pos - 1, First))->n)->inc(p_color)) {
			result = true;
			explosion(size, pos, 'r');
		}
		if (pos<(size ^ 2 - size))
		if (((FindVar(pos + size, First))->n)->inc(p_color)) {
			result = true;
			explosion(size, pos, 'r');
		}
		if (pos >= size)
		if (((FindVar(pos - size, First))->n)->inc(p_color)) {
			result = true;
			explosion(size, pos, 'r');
		}
		return result;
	}

	bool danger(int size, int pos) {
		bool danger = false;
		if (((FindVar(pos, First))->n)->value == ((FindVar(pos, First))->n)->thr) {
			danger = true;
			return danger;
		}
		if (pos<size - 1)
		if (((FindVar(pos + 1, First))->n)->value == ((FindVar(pos + 1, First))->n)->thr) {
			danger = true;
			return danger;
		}
		if (pos>0)
		if (((FindVar(pos - 1, First))->n)->value == ((FindVar(pos - 1, First))->n)->thr) {
			danger = true;
			return danger;
		}
		if (pos<(size ^ 2 - size))
		if (((FindVar(pos + size, First))->n)->value == ((FindVar(pos + size, First))->n)->thr) {
			danger = true;
			return danger;
		}
		if (pos >= size)
		if (((FindVar(pos - size, First))->n)->value == ((FindVar(pos - size, First))->n)->thr)
			danger = true;
		return danger;
	}

	int ai(int size, int level) {
		int result = -1;
#define plus ((FindVar(i, First))->n)->inc('r')
		srand(time(NULL));
		for (int i = 0; i<(size*size); i++) {
			// dont make the cell explodable
			if (!(((FindVar(i, First))->n)->value == ((FindVar(i, First))->n)->thr - 1))
				switch (level) {
				case 0:
					if (plus) {
						result = i;
						explosion(size, i, 'r');
					}
					break;
				case 1:
					// 50-50 decision
					if ((rand() % 1) && (!(danger(size, i))))
					if (plus) {
						result = i;
						explosion(size, i, 'r');
					}
					break;
				case 2:
					// check if it can be *safely* exploded
					if (!(danger(size, i)))
					if (plus) {
						result = i;
						explosion(size, i, 'r');
					}
			}
		}
		return result;
	}

	int GetScore(char p_color) {
		int result = 0;
		TVar ^srch;
		srch = FindVar(0, First);
		if (srch) do
		{
			if (srch->n->c_color == p_color)
				result += srch->n->value;
			srch = srch->next;
		} while (srch);
		return result;
	}

};