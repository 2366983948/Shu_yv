#include <iostream>
using namespace std;

class TicTacToe {

public:
    int board[3][3];//0 表示还没有下棋，1 表示〇 ，2表示 X
    bool isGameOver; //游戏是否结束的标识
    int order;//玩家1，玩家2
    //游戏开始，用于初始化数据
    void GameStart(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                board[i][j] = 0;
            }
        }
        isGameOver = false;
        order = 1;

         while(!isGameOver){
            Display();
            Update();
        }
    }
    // 每帧调用一次
    void Update(){
        if(isGameOver){
            return;
        }
        cout<<"请玩家"<<order<<"下棋:"<<endl;
        int a=0;
        cin>>a;
        a-=1;
        if (a>=0 && a<9 && board[a/3][a%3] == 0){
            board[a/3][a%3] = order;
            //判断是否结束
            for(int i = 0; i < 3; i++){
                //横着
                if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0){
                    GameOver();
                    return;
                }
                //竖着
                if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0){
                    GameOver();
                    return;
                }
                //对角
                if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0){
                    GameOver();
                    return;
                }
                if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 0){
                    GameOver();
                    return;
                }
            }
            if(order == 1){
                order = 2;
            }
            else{
                order = 1;
            }
        }
        else{
            cout<<"输入错误"<<endl;
        }
    }
    //游戏结束
    void GameOver(){
        Display();
        cout<<"玩家"<<order<<"获胜"<<endl;
        isGameOver = true;
    }
    void Display(){
        //清除控制台
        system("cls");
        cout<<"当前棋盘：\n1 2 3\n4 5 6\n7 8 9"<<endl;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(board[i][j] == 0){
                    cout<<"-";
                }
                else if(board[i][j] == 1){
                    cout<<"〇";
                }
                else{
                    cout<<"X";
               }
            }
            cout<<endl;
        }
    }
};