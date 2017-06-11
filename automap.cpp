#include <iostream>
#include <new>
#define Net_Cond NULL
#define Wrong_State -1
#define M 5
//bool Net_Cond(char){return false;}

typedef bool (*Cond)(char);
typedef Cond** Auto_Map;
bool cond_a(char x){return (x=='a');}
bool cond_b(char x){return (x=='b');}
const int n=5;
bool cond_else (char){return true;}
bool The_End (char){std::cout<<"end program..."<<std::endl; return 0;}

int auto_map(int current_state, Auto_Map amap, int size, char ch) {
	for(int i=0; i<size; ++i) {
		Cond fun = amap[current_state][i];
		if(NULL != fun && true == fun(ch)) {
			return i;
		}		
	}
	return Wrong_State;
}


int main()
{
	
	Auto_Map m = new Cond*[M];
    for (int i=0; i<M; i++) {
        m[i] = new Cond[M];
	}
	m[0][0] = Net_Cond;		m[1][0] = Net_Cond;
	m[0][1] = cond_a;		m[1][1] = cond_a;
	m[0][2] = Net_Cond;		m[1][2] = cond_b;	
	m[0][3] = Net_Cond;		m[1][3] = Net_Cond;	
        m[0][4] = cond_else;	        m[1][4] = cond_else;
	
	m[2][0] = Net_Cond;		m[3][0] = Net_Cond;
	m[2][1] = Net_Cond;		m[3][1] = Net_Cond;
	m[2][2] = Net_Cond;		m[3][2] = Net_Cond;	
	m[2][3] = The_End;		m[3][3] = Net_Cond;	
	m[2][4] = Net_Cond;		m[3][4] = Net_Cond;
	
				m[4][0] = Net_Cond;
				m[4][1] = Net_Cond;	
				m[4][2] = Net_Cond;		
				m[4][3] = Net_Cond;	
				m[4][4] = Net_Cond;

	char *pstr = "aaab";
	int size = strlen(pstr);
	int state = 0;
	for(int i=0; i<size; ++i) {
		state = auto_map(state, m, 4, pstr[i]);
		if(Wrong_State == state) {
			std::cout<<"wrong string:"<<std::endl<<pstr+i<<std::endl;
			return 1;
		}
	}
	for (int i=0; i<M; i++) {
        delete[] m[i];
	}
}

