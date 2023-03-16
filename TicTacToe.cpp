#include<bits/stdc++.h>
using namespace std;
const string BC[]={" ","O","X"};
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
    string output(){
        string str="";
        for(int y=0;y<3;y++){
            for(int x=0;x<3;x++){
                string+=BC[Broad[x][y]];
            }
            string+="\n";
        }
        return str;
    }
    int Winner(){
        for(int s=0;s<3;s++){
            if(Broad[s][0]==Broad[s][1]&&Broad[s][1]==Broad[s][2]&&Broad[s][0]!=0) return Broad[s][0];
            if(Broad[0][s]==Broad[1][s]&&Broad[1][s]==Broad[2][s]&&Broad[0][s]!=0) return Broad[0][s];
        }
        if(Broad[0][0]==Broad[1][1]&&Broad[1][1]==Broad[2][2]&&Broad[1][1]!=0) return Broad[1][1];
        if(Broad[2][0]==Broad[1][1]&&Broad[1][1]==Broad[0][2]&&Broad[1][1]!=0) return Broad[1][1];
        return 0;
    }
    bool put(int x,int y,int player){
        if(x>=3||y>=3||x<0||y<0||player<1||player>2) return false;
        if(Broad[x][y]!=0) return false;
        Broad[x][y]=player;
        filled++;
        return true;
    }
    bool pick(int x,int y,int player){
        if(x>=3||y>=3||x<0||y<0||player<1||player>2) return false;
        if(Broad[x][y]!=player) return false;
        Broad[x][y]=0;
        filled--;
        return true;
    }
    int evaluate(){
        int score=Winner();
        if(score) return score*
    }
};
int main(){
    
}