#include<bits/stdc++.h>

using namespace std;
const string BC[]={".","O","X"};
const int value[]={1000,10,100,1000,1};
const int mod=1e9+7;
const int depth_limit=4;

inline int people(int n){return (n==2)?-1:(n==1?1:0);}
inline void ERROR(void){
    cout<<"\nERROR\n\n\n";
    return ;
}
struct TTT{
    int Broad[3][3]={0};
    int filled=0;
    int Player=1;
    TTT(){
        for(auto &x:Broad) for(int &b:x) b=0;
        filled=0;
        Player=1;
        return ;
    }
    int Winner(){
        for(int s=0;s<3;s++){
            if(Broad[s][0]==Broad[s][1]&&Broad[s][1]==Broad[s][2]&&Broad[s][0]!=0) return Broad[s][0];
            if(Broad[0][s]==Broad[1][s]&&Broad[1][s]==Broad[2][s]&&Broad[0][s]!=0) return Broad[0][s];
        }
        if(Broad[0][0]==Broad[1][1]&&Broad[1][1]==Broad[2][2]&&Broad[1][1]!=0) return Broad[1][1];
        if(Broad[2][0]==Broad[1][1]&&Broad[1][1]==Broad[0][2]&&Broad[1][1]!=0) return Broad[1][1];
        if(filled==9) return 0;
        return -1;
    }
    bool put(int x,int y,int player){
        if(x>=3||y>=3||x<0||y<0||player<1||player>2) return false;
        if(Broad[x][y]!=0) return false;
        Broad[x][y]=player;
        filled++;
        return true;
    }
    void clear(void){
        for(auto &row:Broad) for(int &i:row) i=0;
        filled=0;
        Player=1;
        return;
    }
    bool pick(int x,int y,int player){
        if(x>=3||y>=3||x<0||y<0||player<1||player>2) return false;
        if(Broad[x][y]!=player) return false;
        Broad[x][y]=0;
        filled--;
        return true;
    }
    friend ostream &operator<<(ostream &s, TTT &T){
        string str="";
        for(int y=0;y<3;y++){
            for(int x=0;x<3;x++){
                str+=BC[T.Broad[x][y]];
            }
            str+="\n";
        }
        s<<str;
        return s;
    }
    friend istream &operator>>(istream &s,TTT &T){
        char w[9];
        for(char &i:w) s>>i;
        for(int p=0;p<9;p++){
            if(w[p]=='O') T.put(p%3,p/3,1);
            else if(w[p]=='X') T.put(p%3,p/3,2);
            else if(w[p]=='.') ;
            else{
                ERROR();
                return s;
            }
        }
        return s;
    }
};

inline int evaluate(TTT T){
    int score=0,winner=T.Winner();
    if(winner>=0) return value[0]*people(winner);
    else if(winner==0) return 0;
    for(int i:{0,1}){
        for(int j:{0,1,2}){//直 二連
            if(T.Broad[j][i]==T.Broad[j][i+1]&&T.Broad[j][i]!=0&&T.Broad[j][!i<<1]==0) score+=people(T.Broad[j][i])*value[1];
            if(T.Broad[i][j]==T.Broad[i+1][j]&&T.Broad[i][j]!=0&&T.Broad[!i<<1][j]==0) score+=people(T.Broad[i][j])*value[1];
        }//斜 二連
        if(T.Broad[i<<1][0]==T.Broad[1][1]&&T.Broad[1][1]!=0&&T.Broad[!i<<1][2]==0) score+=people(T.Broad[1][1])*value[1];
        if(T.Broad[i<<1][2]==T.Broad[1][1]&&T.Broad[1][1]!=0&&T.Broad[!i<<1][0]==0) score+=people(T.Broad[1][1])*value[1];
        //斜 二間
        if(T.Broad[i<<1][0]==T.Broad[!i<<1][2]&&T.Broad[1][1]==0) score+=people(T.Broad[i<<1][0])*value[1];
    }
    for(int i:{0,1,2}){//直 二間
        if(T.Broad[i][0]==T.Broad[i][2]&&T.Broad[i][1]==0) score+=people(T.Broad[i][0])*value[1];
        if(T.Broad[0][i]==T.Broad[2][i]&&T.Broad[1][i]==0) score+=people(T.Broad[0][i])*value[1];
    }
    return score;
}

inline int evaluate2(TTT T){
    int score=0,winner=T.Winner();
    if(winner>=0) return value[0]*people(winner);
    else if(winner==0) return 0;
    for(int c[2]={0,0},y=0;y<3;y++,c[0]=c[1]=0){
        for(int x=0;x<3;x++){
            if(T.Broad[x][y]) c[T.Broad[x][y]&1]++;
        }
        if((c[0]==0||c[1]==0)&&c[0]+c[1]) 
            score+=value[max(c[0],c[1])]*(c[0]?-1:1);
    }
    for(int c[2]={0,0},x=0;x<3;x++,c[0]=c[1]=0){
        for(int y=0;y<3;y++){
            if(T.Broad[x][y]) c[T.Broad[x][y]&1]++;
        }
        if((c[0]==0||c[1]==0)&&c[0]+c[1]) 
            score+=value[max(c[0],c[1])]*(c[0]?-1:1);
    }
    int c[2]={0,0};
    if(T.Broad[0][0]) c[T.Broad[0][0]&1]++;
    if(T.Broad[1][1]) c[T.Broad[1][1]&1]++;
    if(T.Broad[2][2]) c[T.Broad[2][2]&1]++;
    if((c[0]==0||c[1]==0)&&c[0]+c[1]) 
        score+=value[max(c[0],c[1])]*(c[0]?-1:1);
    c[0]=c[1]=0;
    if(T.Broad[0][2]) c[T.Broad[0][2]&1]++;
    if(T.Broad[1][1]) c[T.Broad[1][1]&1]++;
    if(T.Broad[2][0]) c[T.Broad[2][0]&1]++;
    if((c[0]==0||c[1]==0)&&c[0]+c[1]) 
        score+=value[max(c[0],c[1])]*(c[0]?-1:1);
    if(score>value[0]) score=value[0];
    return score;
}

pair<int,int> AB(TTT &T,int player,int depth=depth_limit,int a=-mod,int b=mod){
    int winner=T.Winner();
    if(winner>=0)//game end;
        return {-1,people(winner)*people(player)*value[0]};
    else if(depth==1)//lowest depth
        return {-1,evaluate2(T)*people(player)};
    int bx=-1,by=-1,score=0;
    for(int y=0;y<3;y++) for(int x=0;x<3;x++){
        if(T.Broad[x][y]) continue;
        T.put(x,y,player);
        score=-AB(T,player^3,depth-1,-b,-a).second-value[4];
        if(T.pick(x,y,player));
        if(score>=b) return {-1,b};
        if(score>a) a=score,bx=x,by=y;
    }
    if(bx==-1){
        cout<<"ERROR("<<a<<","<<b<<")"<<depth<<"\t"<<player<<endl<<T<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        for(int y=0;y<3;y++) for(int x=0;x<3;x++){
            if(T.Broad[x][y]) continue;
            T.put(x,y,player);
            score=evaluate2(T)*people(player);
            cout<<">>>"<<score<<endl<<T<<endl;
            if(T.pick(x,y,player));
        }
        cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    }
    return {bx+by*3,a};
}

void evmode(){
    TTT TicTacToe;
    for(;;){
        cin>>TicTacToe;
        cout<<evaluate(TicTacToe)<<endl;
        TicTacToe.clear();
    }
}

void play(){
    TTT TicTacToe;
    int mode,move,mx,my;
    cout<<"please input [0:player&player,1:computer&player,2:player&computer] ";
    cin>>mode;
    if(mode==-1) evmode();
    for(int x,y,player=1;TicTacToe.filled<9;player^=3){
        cout<<TicTacToe<<endl;
        if(TicTacToe.Winner()>=0){
            cout<<"game end"<<endl;
            break;
        }
        cout<<player<<endl;
        if(player&mode){
            move=AB(TicTacToe,player).first;
            if(move==-1) cout<<"ERROR\n";
            if(!TicTacToe.put(move%3,move/3,player)) cout<<"ERROR"<<endl;
        }
        else{
            cout<<"player "<<BC[player]<<" input"<<endl;
            cin>>mx>>my;
            if(mx==-1&&my==-1) return ;
            while(!TicTacToe.put(mx,my,player)){
                cout<<"ERROR please input again"<<endl;
                cin>>mx>>my;
            }
        }
    }
    cout<<"============================\n";
    cout<<TicTacToe;
    cout<<"Winner"<<TicTacToe.Winner()<<endl;
}