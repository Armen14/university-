#include <QtCore/QCoreApplication>
#include <iostream>
#include <qdebug.h>
#include <QDir>
#include <qfile.h>
using namespace std;
#define Net_Cond NULL

typedef bool (*Cond)(QChar);
typedef Cond** Auto_Map;
bool cond_apostrof(QChar x){return (x=='\'');}
bool cond_komment_open(QChar x){return (x=='{');}
bool cond_komment_close(QChar x){return (x=='}');}
bool cond_quote(QChar x){return (x=='\"');}
bool cond_equal(QChar x){return (x=='=');}
bool cond_colon(QChar x){return (x==':');}
bool cond_large(QChar x){return (x=='>');}
bool cond_less(QChar x){return (x=='<');}
bool cond_equal_large(QChar x){return (x=='=' || x=='>');}
bool cond_razdel(QChar x){return (x==' ' || x=='\n' || x=='(' || x==')' || x=='\n' || x==',' || x==';' \
                                  || x=='\n' || x=='+' || x=='-' || x=='>' || x=='<' || x=='=');}
bool cond_V(QChar x){return (x=='V');}
bool cond_A(QChar x){return (x=='A');}
bool cond_R(QChar x){return (x=='R');}
bool cond_B(QChar x){return (x=='B');}
bool cond_E(QChar x){return (x=='E');}
bool cond_G(QChar x){return (x=='G');}
bool cond_I(QChar x){return (x=='I');}
bool cond_N(QChar x){return (x=='N');}
bool cond_D(QChar x){return (x=='D');}
bool cond_W(QChar x){return (x=='W');}
bool cond_T(QChar x){return (x=='T');}
bool cond_F(QChar x){return (x=='F');}
bool cond_H(QChar x){return (x=='H');}
bool cond_L(QChar x){return (x=='L');}
bool cond_S(QChar x){return (x=='S');}
bool cond_O(QChar x){return (x=='O');}
bool cond_space_eoln(QChar x){return (x==' ' || x=='\n');}
bool cond_hash(QChar x){return (x=='#');}
bool cond_plus(QChar x){return (x=='+');}
bool cond_num(QChar x){return (x=='0' || x=='1' || x=='2' || x=='3' || x=='4' || x=='5' || x=='6' || x=='7' || x=='8' || x=='9');}
bool cond_symbol(QChar x) {
    return (x=='q' || x=='w' || x=='e' || x=='r' || x=='t' || x=='y' || \
            x=='u' || x=='i' || x=='o' || x=='p' || x=='a' || x=='s' || \
            x=='d' || x=='f' || x=='g' || x=='h' || x=='j' || x=='k' || \
            x=='l' || x=='z' || x=='x' || x=='c' || x=='v' || x=='b' || \
            x=='n' || x=='m');
}
bool cond_symbol_num(QChar x) {return (cond_symbol(x) || cond_num(x));}
bool cond_komment(QChar x) {return (cond_symbol(x) || cond_num(x) || cond_apostrof(x) ||cond_A(x) || cond_B(x) || cond_colon(x) || cond_D(x) || cond_E(x) \
                                    || cond_equal(x) || cond_equal_large(x) || cond_F(x) || cond_G(x) || cond_H(x) || cond_hash(x) || cond_I(x) || cond_L(x) || \
                                    cond_large(x) || cond_less(x) || cond_N(x) || cond_num(x) || cond_O(x) || cond_plus(x) || cond_quote(x)  || cond_R(x)  || cond_razdel(x) \
                                     || cond_S(x) || cond_space_eoln(x)  || cond_symbol(x)  || cond_symbol_num(x)  || cond_T(x) || cond_V(x) || cond_W(x));}
const int n=40;
bool cond_else (QChar){return true;}
bool The_End (QChar){cout<<"end program..."<<endl; return 0;}
bool automat(QString str);

QStringList Read_File(QString path);
void Write_File(QStringList strings, QString path);
#define Wrong_State -1
#define M 40

int auto_map(int current_state, Auto_Map amap, int size, QChar ch) {
        for(int i=0; i<size; ++i) {
                Cond fun = amap[current_state][i];
                if(NULL != fun && true == fun(ch)) {
                        return i;
                }
        }
        return Wrong_State;
}


int main() {
    QString path = QDir::currentPath() + "/file.txt";
    QStringList file = Read_File(path);
    bool flag = true;
    for(int i=0; i<file.count(); i++) {
        if(automat(file.at(i)) == false) {
            qDebug()<<"в строке №"<<i+1;
            flag = false;
        }
    }
    if(flag == true) {
        qDebug()<<"Исходный текс не содеожит ошибок";
    }
    return 0;
}



bool automat(QString str) {
    Auto_Map m = new Cond*[M];
    for (int i=0; i<M; i++) {
        m[i] = new Cond[M];
    }

    for(int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            m[i][j] = Net_Cond;
        }
    }
    m[0][0] = cond_space_eoln;
    m[0][1] = cond_symbol;
    m[1][1] = cond_symbol_num;
    m[0][2] = cond_num;
    m[2][2] = cond_num;
    m[0][3] = cond_apostrof;
    m[3][3] = cond_symbol;
    m[3][4] = cond_apostrof;
    m[4][5] = cond_plus;
    m[4][3] = cond_apostrof;
    m[5][3] = cond_apostrof;
    m[0][6] = cond_quote;
    m[6][6] = cond_symbol;
    m[6][7] = cond_quote;
    m[7][8] = cond_plus;
    m[8][6] = cond_quote;
    m[0][9] = cond_V;
    m[9][10] = cond_A;
    m[10][31] = cond_R;
    m[0][11] = cond_B;
    m[11][12] = cond_E;
    m[12][13] = cond_G;
    m[13][14] = cond_I;
    m[14][31] = cond_N;
    m[0][15] = cond_E;
    m[15][16] = cond_N;
    m[16][31] = cond_D;
    m[0][17] = cond_R;
    m[17][18] = cond_E;
    m[18][19] = cond_A;
    m[19][31] = cond_D;
    m[0][20] = cond_W;
    m[20][21] = cond_R;
    m[21][22] = cond_I;
    m[22][23] = cond_T;
    m[23][31] = cond_E;
    m[0][24] = cond_I;
    m[24][31] = cond_F;
    m[0][25] = cond_T;
    m[25][26] = cond_H;
    m[26][27] = cond_E;
    m[27][31] = cond_N;
    m[0][28] = cond_E;
    m[28][29] = cond_L;
    m[29][30] = cond_S;
    m[30][31] = cond_E;
    m[34][35] = cond_N;
    m[35][0] = cond_D;
    m[36][0] = cond_R;
    m[37][0] = cond_equal;
    m[38][0] = cond_equal;
    m[39][0] = cond_equal_large;
    m[1][0] = cond_razdel;
    m[2][0] = cond_razdel;
    m[4][0] = cond_razdel;
    m[7][0] = cond_razdel;
    m[31][0] = cond_razdel;
    m[1][32] = cond_N;
    m[2][32] = cond_N;
    m[4][32] = cond_N;
    m[7][32] = cond_N;
    m[31][32] = cond_N;
    m[1][34] = cond_A;
    m[2][34] = cond_A;
    m[4][34] = cond_A;
    m[7][34] = cond_A;
    m[31][34] = cond_A;
    m[1][36] = cond_O;
    m[2][36] = cond_O;
    m[4][36] = cond_O;
    m[7][36] = cond_O;
    m[31][36] = cond_O;
    m[1][37] = cond_colon;
    m[2][37] = cond_colon;
    m[4][37] = cond_colon;
    m[7][37] = cond_colon;
    m[31][37] = cond_colon;
    m[1][38] = cond_large;
    m[2][38] = cond_large;
    m[4][38] = cond_large;
    m[7][38] = cond_large;
    m[31][38] = cond_large;
    m[1][39] = cond_less;
    m[2][39] = cond_less;
    m[4][39] = cond_less;
    m[7][39] = cond_less;
    m[31][39] = cond_less;
    m[0][33] = cond_komment_open;
    m[33][33] = cond_komment;
    m[33][0] = cond_komment_close;

    int size = str.length();
    int state = 0;
    for(int i=0; i<size; ++i) {
            state = auto_map(state, m, 39, str[i]);
            if(Wrong_State == state) {
                qDebug()<<"Ошибка: неверный символ "<<str[i];
                return false;
            }
    }
    for (int i=0; i<M; i++) {
        delete[] m[i];
    }
    return true;
}

QStringList Read_File(QString path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QStringList StrList;
    while(!file.atEnd()) {
        StrList<<file.readLine();
    }
    file.close();
    return StrList;
}

void Write_File(QStringList strings, QString path) {
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i=0; i<strings.count(); i++) {
        out<<strings[i];
    }
    file.close();
}
