#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

public ref class Settings
{
public:
	int size, level;
};

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
				  BackColor::set(System::Drawing::Color::LightGray);
			break;
		case 'r': ForeColor::set(System::Drawing::Color::Red);
				  BackColor::set(System::Drawing::Color::LightPink);
			break;
		case 'b': ForeColor::set(System::Drawing::Color::Blue);
				  BackColor::set(System::Drawing::Color::LightBlue);
			break;
		}
	}

	cell(char c_c0l0r, int thr35h0ld, int valu3, int xx, int yy, int i, System::EventHandler^ eh,Settings^ settings) :c_color(c_c0l0r), thr(thr35h0ld), value(valu3) {
		Size = System::Drawing::Size(50, 50);
		Location = System::Drawing::Point(xx * 50, yy * 50);
		display();
		Click += eh;
		Tag::set(settings->size*settings->size-i-1);
	}
	bool inc(char p_color) {
		value++;
		c_color = p_color;
		return (value>thr);
	}
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
	char player;

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
		int k = 0;
		who_won = 'n';
		player = 'b';
		int thr;
		int size = settings->size;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++, k++) {
				if ((k == 0) || (k == (size - 1)) || (k == (size*(size - 1))) || (k == (size * size - 1)))
					thr = 3;
				else
				if ((k<(size - 1)) || (k>(size*(size - 1))) || ((k % size) == 0) || ((k % size) - (size - 1) == 0))
					thr = 5;
				else
					thr = 8;
				NewVar('n', thr, 0, i + 2, j + 2, j+(size*i),eh,settings);
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
		if (((FindVar(pos, First))->n)->value >= ((FindVar(pos, First))->n)->thr)
			((FindVar(pos, First))->n)->value = 0;
		((FindVar(pos, First))->n)->c_color = 'n';
		if (pos % size != 0)
		if (((FindVar(pos - 1, First))->n)->inc(p_color)) {
			result = explosion(size, pos-1, p_color);
		}
		if ((pos + 1) % size != 0)
		if (((FindVar(pos + 1, First))->n)->inc(p_color)) {
			result = explosion(size, pos+1, p_color);
		}
		if (pos < (size * (size - 1)))
		if (((FindVar(pos + size, First))->n)->inc(p_color)) {
			result = explosion(size, pos+size, p_color);
		}
		if (pos >= size)
		if (((FindVar(pos - size, First))->n)->inc(p_color)) {
			result = explosion(size, pos-size, p_color);
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

	void ai(int size, int level) {
	#define plus \
		if (((FindVar(i, First))->n)->inc('r')) \
			explosion(size, i, 'r'); \
		turn = false;

		srand(time(NULL));
		bool turn = true;
		for (int i = 0; (i<(size*size))&&(turn); i++) {
			// dont make the cell explodable
			if (!(((FindVar(i, First))->n)->value == ((FindVar(i, First))->n)->thr - 1))
				switch (level) {
				case 0:
					{plus}
					break;
				case 1:
					// 50-50 decision
					if ((rand() % 2) && (!(danger(size, i))))
					{plus}
					break;
				case 2:
					// check if it can be *safely* exploded
					if (!(danger(size, i)))
					{plus}
			}
		}
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

	// DEBUGGING function, not used in project
	// for convenient obtaining of current array values
	int* CheckValues(Settings^ settings) {
		TVar ^var = First;
		int size = settings->size*settings->size;
		int* result = new int[settings->size*settings->size];
		if (var)
			for (int i = size - 1; (i >= 0) && (var); i--, var = var->next) {
				result[i] = (int)(var->n->Tag); // choose what to get from array
			}
			return result;
		}

};