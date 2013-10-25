/*
но я бы делал ии в такой игре примерно так:
старался бы заполнить все клетки так, 
чтоб в них оставалось по 1 ходу до активации взрываемости, 
а если есть взрывающиеся квадратики - он бы кликал на них, 
если б это не создало больше 1 активного квадратика не на границе карты 
хотя не, не все клетки, а по определённому условию - 
чтоб если игрок его активирует, чтоб ии мог открыть его, 
и это не создало бы активных квадратиков 


Диман

последнего условия не понял 
чтоб если игрок активирует то что? 
ты про точ тобы он сам взрывал но взрывал аккуратно? 
 

Антон

именно
ещё, чтоб приоритет был у мощных клеток 

private: 
  void button1_Click(System::Object ^ sender,
    System::EventArgs ^ e)
  {
    Form ^ dlg1 = gcnew Form();
    dlg1->ShowDialog();
  }


*/

bool danger (*button *m, int size, int pos) {
	bool danger=false;
	if ((*m[i])->value==(*m[i])->thr) {
		danger=true;
		return danger;
	}
	if (*m[pos+1])
		if ((*m[pos+1])->value==(*m[pos+1])->thr) {
			danger=true;
			return danger;
		}	
	if (*m[pos-1])
		if ((*m[pos-1])->value==(*m[pos-1])->thr) {
			danger=true;
			return danger;
		}
	if (*m[pos+size])
		if ((*m[pos+size])->value==(*m[pos+size])->thr) {
			danger=true;
			return danger;
		}
	if (*m[pos-size])
		if ((*m[pos-size])->value==(*m[pos-size])->thr)
			danger=true;	
	return danger;
}

void ai (*button *m, int size, int level) {
	#define plus inc((*m[i])->value, 'r')
	srand(time(NULL));
	for (int i=0; i<(size^2); i++) {
		// dont make the cell explodable
		if (!((*m[i])->value==((*m[i])->thr)-1))
			switch (level) {
				case 0:
				plus;
				break;
				case 1:
				// 50-50 decision
				if ((rand()%1)&&(!(danger(*button *m, size, i))))
					plus;
				break;
				case 2:
				// check if it can be *safely* exploded
				if (!(danger(*button *m, size, i)))
					plus;					
			}
	}
}

void explosion (*button *m, int size, int pos, char p_color) {
	(*m[pos])->value=0;
	(*m[pos])->c_color='n';
	if (pos<size)
		inc((*m[pos+1])->value, p_color);
	if (pos>0)
		inc((*m[pos-1])->value, p_color);
	if (pos<(size^2-size))
		inc((*m[pos+size])->value, p_color);
	if (pos>=size)
		inc((*m[pos-size])->value, p_color);
}

(i<(size-1))

void side (int i, *button *m, int x, int y) { 
	static int d=0;
	int thr;
	d++;
	switch (d) {
		1: x+=1; break;
		2: y-=1; break;
		3: x-=1; break;
		4: y+=1; d=0;
	}
	// DefineMyThreshold
	if ((i==0)||(i==(size-1))||(i==(size*(size-1)))||(i==(size^2-1)))
		thr=3;
	else
		if ((i<(size-1))||(i>(size*(size-1)))||((i%size)==0)||((i%size)-(size-1)==0))
			thr=5;
		else
			thr=8;
	m[i]=*(create_cell());
}

button** draw (int size) {
	m(*button)= new button[size^2];
	int x=5;
	int y=4;
	for (int a=0; i<(size / 2); i++) {
		x-=1;
		y+=1;
		for (int j=0; j<4; j++) {
		side(i, m, x, y);
		}
	}
	return m;
}


		
		
		
		
		
class cell {
	char c_color; //n - neutral; r - red; b - blue;
	int thr; //threshold (determined by cell position in grid: corner - 3; border - 5; else - 8)
	int value;
public:
	bool inc(int *value; char p_color) {
		bool explode=false;
		value++;
		if ((*value)>thr)
			explode=true;
		c_color=p_color;
		return explode;
	}
};

class player {
	char p_color;
	int score;
};

class game {
	bool turn; //false - blue
	int w_score; //score enough to win
	bool type; //false - HUMANxHUMAN
	int size;  // select (4/6/8) cube width
	char fill; //b - blank; t-triangles; x - cross; l - lines
	void process ()	{


	}

	char turn() {
		char who_won='n';
		//if (player.score()>=w_score)
		//	who_won=player.color();
		return who_won;
	}
};

int main()
{
	
	return 0;
}