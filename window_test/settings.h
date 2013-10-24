#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>

	
	public class settings
	{
	public:
		static int size,level;
		//void click (System::Object^  sender, System::EventArgs^  e) {
		//	
		//}
	};

	public ref class cell : public System::Windows::Forms::Button {
		char c_color; //n - neutral; r - red; b - blue;
		int thr; //threshold (determined by cell position in grid: corner - 3; border - 5; else - 8)
		int value;
	public:
		cell (char c_c0l0r, int thr35h0ld, int valu3, int xx, int yy):c_color(c_c0l0r),thr(thr35h0ld),value(valu3) {
			Size.Width=50;
			Size.Height=50;
			Location.X=xx*50;
			Location.Y=yy*50;
			//text=(std::to_string(value));
			//Click += gcnew System::EventHandler(this, &Form1::sett_Click);
		}
		bool inc(char p_color) {
			bool explode=false;
			value++;
			if (value>thr)
				explode=true;
			c_color=p_color;
			return explode;
		}



	};

	struct TVar {
	cell ^* n;
	TVar *next;
	};

	class TLVar {
	private:
	TVar *First;
	public:
	TLVar() {
	First=0;
	}

	bool NewVar (char c_c0l0r, int thr35h0ld, int valu3, int xx, int yy) {
	TVar * n;
	n = new TVar;
	if (n)
	{
		cell^ x=gcnew cell(c_c0l0r, thr35h0ld, valu3, xx, yy);
	  n->n = &x;
		n->next = First;
		First = n;
	}
	return n;
	}

	TVar** FindVar (int pos, TVar* First=0) {
		if(First==0)First=this->First;
		if(pos==0)return &First;
		return FindVar(pos-1,First->next);
		/*static TVar **Found; Found = 0;
	if (First) if (First->war->getname()==name) Found = &First;
	else {
		 for (TVar *tmp = First; ((!Found)&&(tmp->next)); tmp = tmp->next) {
		 if (tmp->next->war->getname()==name)
			 Found = &tmp->next;
		 }
		}
	return Found;*/
	}

			void explosion (int size, int pos, char p_color) {
		FindVar(pos)->n->value=0;
		FindVar(pos)->n->c_color='n';
		if (pos<size-1)
			FindVar(pos+1)->n->inc(p_color);
		if (pos>0)
			FindVar(pos-1)->n->inc(p_color);
		if (pos<(size^2-size))
			FindVar(pos+size)->n->inc(p_color);
		if (pos>=size)
			FindVar(pos-size)->n->inc(p_color);
	}

		bool danger (int size, int pos) {
		bool danger=false;
		if (FindVar(pos)->n->value==FindVar(pos)->n->thr) {
			danger=true;
			return danger;
		}
		if (pos<size-1)
			if (FindVar(pos+1)->n->value==FindVar(pos+1)->n->thr) {
				danger=true;
				return danger;
			}	
		if (pos>0)
			if (FindVar(pos-1)->n->value==FindVar(pos-1)->n->thr) {
				danger=true;
				return danger;
			}
		if (pos<(size^2-size))
			if (FindVar(pos+size)->n->value==FindVar(pos+size)->n->thr) {
				danger=true;
				return danger;
			}
		if (pos>=size)
			if (FindVar(pos-size)->n->value==FindVar(pos)->n->thr)
				danger=true;	
		return danger;
	}

		void ai (int size, int level) {
		#define plus FindVar(i)->n->inc('r')
		srand(time(NULL));
		for (int i=0; i<(size*size); i++) {
			// dont make the cell explodable
			if (!(FindVar(i)->n->value==(FindVar(i)->n->thr)-1))
				switch (level) {
					case 0:
					plus;
					break;
					case 1:
					// 50-50 decision
					if ((rand()%1)&&(!(danger(m, size, i))))
						plus;
					break;
					case 2:
					// check if it can be *safely* exploded
					if (!(danger(m, size, i)))
						plus;					
				}
		}
	}

	};



	struct player {
		char p_color;
		int score;
	public:
		player(char p_c0l0r):p_color(p_c0l0r),score(0) {}
	};

	struct game {
		bool turn; //false - blue
		int w_score; //score enough to win
		int size;  // select (4/6/8) square width
		int level; // AI level
		char fill; //b - blank; t-triangles; x - cross; l - lines
		char who_won;
		game(int s1z3, int l3v3l):size(s1z3),level(l3v3l){
			w_score=size*10;
			who_won='n';
		}

		char turn() {
			player player1('b');
			player player2('r');
			
			if ((player1.score>=w_score)&&(player1.score>player2.score))
				who_won='b';
			if ((player2.p_color>=w_score)&&(player2.score>player1.score))
				who_won='r';
			turn=!turn;
			return who_won;
		}
		
		void side (int i, TLVar* m, int x, int y) { 
			static int d=0;
			int thr;
			d++;
			switch (d) {
				case 1: x+=1; break;
				case 2: y-=1; break;
				case 3: x-=1; break;
				case 4: y+=1; d=0;
			}
			// DefineMyThreshold
			if ((i==0)||(i==(size-1))||(i==(size*(size-1)))||(i==(size^2-1)))
				thr=3;
			else
				if ((i<(size-1))||(i>(size*(size-1)))||((i%size)==0)||((i%size)-(size-1)==0))
					thr=5;
				else
					thr=8;
			m->NewVar('n',thr,'0',x,y);
		}



		TLVar draw () {
			TLVar m;
			int x=5;
			int y=4;
			for (int i=0; i<(size / 2); i++) {
				x-=1;
				y+=1;
				for (int j=0; j<4; j++) {
				side(i, &m, x, y);
				}
			}
			return m;
		}
	};