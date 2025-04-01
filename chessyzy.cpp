#include<iostream>
#include<map>
#include<time.h>
#include<stdlib.h>
#include<cmath>
#include<vector>
#include<utility>
#include<windows.h>
#include<conio.h>
using namespace std;
const int row = 12, col = 12;
int dex[4] = { 1,1,1 ,0 };//four directions
int dey[4] = { -1,1,0,1 };
int five = 100000;//the value of different patterns
int three = 100;
int two = 10;
int one = 1;
int ab[row][row];
char shou;
const int maxnum = row * row;
void init_window() {
    system("cls");
    for (int i = 1; i <= 7; i++)cout << "\n";
    for (int i = 1; i <= 6; i++)cout << "\t";
    cout << "五子棋" << "\n\n\n\n";
    for (int i = 1; i <= 5; i++)cout << "\t  ";
    cout << "输1先手，输2后手";
    shou = _getch();

}
void set_pos(int x, int y)
{
    HANDLE winHandle;
    COORD pos;
    pos.X = x, pos.Y = y;
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(winHandle, pos);
}
bool inboard(int x, int y)//if the position is in the board
{
    if (x >= 0 && x < row && y >= 0 && y < row)
        return true;
    return false;
}
bool abandon(int x, int y)
{
    return false;
}
bool putok(int i, int j, int qp[row][row], int color)//if the position is avaliable
{
    if (color == 0)
    {
        if (inboard(i, j) && qp[i][j] == 0)
        {
            return true;
        }
        return false;
    }
    else
    {
        if (!inboard(i, j) || qp[i][j] != 0)
        {
            return false;
        }
        if (abandon(i, j))
            return false;
        return true;

    }



}
int devaluate(int color, int board[row][row], int t)//get the value of the situation(one of the direction)
{
    int x = dex[t];
    int y = dey[t];
    int score = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            int empty = 0;
            int num = 0;
            bool maywin = true;//if the position is able to win in this direction
            for (int k = 0; k < 4; k++)
            {

                int nx = i + k * x;
                int ny = i + k * y;
                if ((!inboard(nx, ny)) || board[nx][ny] == -color)
                {
                    maywin = false;
                    break;
                }
                else if (board[nx][ny] == 0)
                    empty++;
                else
                    num++;
            }
            if (maywin)
            {
                if (num == 4)
                    score += five;
                if (num == 3)
                    score += three;
                if (num == 2)
                    score += two;
                if (num == 1)
                    score += one;
            }




        }
    }
    return score;
}
int evaluate(int color, int board[row][row])//sum up to the total value
{
    int score = 0;
    for (int i = 0; i < 4; i++)
        score += devaluate(color, board, i);
    return score;

}
int ifover(int board[row][row])//judge if either side has won the game
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {

            for (int d = 0; d < 4; d++)
            {
                int n = 0;
                for (int k = 0; k < 5; k++)
                {
                    if (!inboard(i + k * dex[d], j + k * dey[d]))
                        break;

                    else if (board[i + k * dex[d]][j + k * dey[d]] == board[i][j])
                        n++;
                    else
                        break;
                }
                if (n == 5)
                    return board[i][j];

            }


        }
    }
    return 0;
}

class treenode//build up the tree
{
public:
    treenode* parent;
    treenode* children[maxnum];//its children
    int board[row][row];
    int color;//先后手
    int childaction[maxnum][2];
    int childcount;//now has form how many children
    int childmax;//it can has how many children
    double value;
    int n;//it has been searched how many times
    double ucb;
    int* count;//the total times of search
    treenode(int parboard[row][row], int opp[2], treenode* parentpoint, int pacolor, int* countp)//the function to connect a new leaf to the tree
    {
        for (int i = 0; i < row; i++)//keep the color of the side to put is always 1
        {
            for (int j = 0; j < row; j++)
            {
                board[i][j] = -parboard[i][j];
            }
        }
        if (inboard(opp[0], opp[1]))
            board[opp[0]][opp[1]] = -1;
        parent = parentpoint;
        value = 0;
        color = (pacolor + 1) % 2;
        n = 0;
        childcount = 0;
        count = countp;
        stepsearch();//private function to get childmax and childaction
    }
    treenode* treerule()//the rule to search
    {
        if (ifover(board) != 0)//over stop searching
        {
            return this;
        }
        if (childmax > childcount)//search next child
        {
            treenode* newnode = new treenode(board, childaction[childcount], this, color, count);
            children[childcount] = newnode;
            childcount++;
            return newnode;
        }
        //all children searched,now calculate ucb
        for (int i = 0; i < childcount; i++)
        {
            children[i]->ucb = children[i]->value / (double)(children[i]->n) + 0.2 * sqrt(log((double)(*count)) / double(children[i]->n));

        }
        int bestchild = 0;
        double maxucb = 0;
        for (int i = 0; i < childcount; i++)
        {
            if (maxucb < children[i]->ucb)
            {
                bestchild = i;
                maxucb = children[i]->ucb;
            }
        }
        return children[bestchild]->treerule();//search the best child
    }
    double simulation()
    {
        return evaluate(1, board);
    }
    void backup(double delta)
    {
        treenode* node = this;
        int side = 0;
        while (node != nullptr)
        {
            if (side == 1)
            {
                node->value += delta;
                side--;
            }
            else
            {
                node->value -= delta;
                side++;
            }
            node->n++;
            node = node->parent;
        }
    }


private:
    void stepsearch()
    {
        int avanum = 0;
        int avaplace[maxnum];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < row; j++)
            {
                if (putok(i, j, board, color))
                {
                    avaplace[avanum++] = i * row + j;
                }
            }
        }
        childmax = avanum;
        for (int i = 0; i < avanum; i++)
        {
            childaction[i][0] = avaplace[i] / row;
            childaction[i][1] = avaplace[i] % row;
        }
    }
};
void copy(int boarda[row][row], int boardb[row][row])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            boarda[i][j] = boardb[i][j];
        }
    }
}
void show(int board[row][row])
{
    system("cls");
    for (int i = 1; i <= 2; i++)cout << "\t";
    for (int i = 0; i < col; i++)
    {
        if (i + 1 < 10)cout << " " << i + 1 << " ";
        else cout << " " << i + 1;
    }
    cout << "\n";
    for (int i = 0; i < row; i++)
    {
        for (int j = 1; j <= 2; j++)cout << "\t";
        for (int j = 0; j < col; j++)cout << " __";
        cout << "\n";
        for (int j = 1; j <= 1; j++)cout << "\t";
        cout << i + 1;
        cout << "\t";
        for (int j = 0; j < col; j++)
        {
            char p;
            if (board[i][j] == 0)p = ' ';
            else if (board[i][j] == 1)p = 'O';
            else if (board[i][j] == -1)p = 'X';
            cout << "|" << p << " ";
        }
        cout << "|";
        cout << "\n";
    }
    for (int j = 1; j <= 2; j++)cout << "\t";
    for (int i = 0; i < col; i++)cout << " __";
}
void white_win()
{
    Sleep(1500);
    system("cls");
    for (int i = 1; i <= 8; i++)cout << '\n';
    for (int i = 1; i <= 4; i++)cout << '\t';
    cout << "白棋胜利";
    cout << "\n\n";
    Sleep(1500);
    init_window();
}
void black_win()
{
    Sleep(1500);
    system("cls");
    for (int i = 1; i <= 8; i++)cout << '\n';
    for (int i = 1; i <= 4; i++)cout << '\t';
    cout << "黑棋胜利";
    cout << "\n\n";
    Sleep(1500);
    init_window();
}
int* search(int boardb[row][row], int co)
{
    int start = clock();
    int timeout = (int)(5 * (double)CLOCKS_PER_SEC);
    int count = 0;
    int color = (shou == '1') ? 0 : 1;
    int opp[2];
    treenode rootnode(boardb, opp, nullptr, color, &count);
    while (clock() - start < timeout)
    {
        count++;
        treenode* node = rootnode.treerule();
        double result = node->simulation();
        node->backup(result);
    }
    int bestchild[maxnum] = { 0 };
    int bestchildnum = 0;
    int maxvalue = INT_MIN;
    for (int i = 0; i < rootnode.childcount; i++)
    {

        if (maxvalue < rootnode.children[i]->value)
        {
            memset(bestchild, 0, sizeof(bestchild));
            bestchildnum = 0;
            bestchild[bestchildnum++] = i;
            maxvalue = rootnode.children[i]->value;
        }
        else if (maxvalue == rootnode.children[i]->value)
        {
            bestchild[bestchildnum++] = i;
        }
    }
    int random = rand() % bestchildnum;
    int* bestac = rootnode.childaction[bestchild[random]];
    int a[2];
    a[0] = bestac[0]; a[1] = bestac[1];
    return a;
}
int main()
{
    int boardd[row][row] = { 0 };
    int x, y;
    //the board for ai (separate the boards easier to debug
    int count = 0;
    int color = (shou == '1') ? 0 : 1;
    int opp[2];
    int side = 0;
    srand(clock());
    init_window();
    int timeout = (int)(5 * (double)CLOCKS_PER_SEC);
    while (ifover(boardd) == 0)//not over
    {
        if (side % 2 == color)//human
        {
            while (1)
            {
                show(boardd);
                set_pos(65, 12);
                cout << "轮到您执棋，请输入坐标：";
                set_pos(65, 14);
                int x, y;
                cin >> x >> y;
                x--, y--;
                if (x<0 || x>row || y<0 || y>col) {
                    set_pos(65, 16);
                    cout << "您输入的数据超出棋盘范围" << '\n';
                    Sleep(1500);
                }
                else if (boardd[x][y] != 0) {
                    set_pos(65, 16);
                    cout << "该位置已有棋子";
                    Sleep(1500);
                }
                else {
                    boardd[x][y] = 1;
                    opp[0] = x;
                    opp[1] = y;
                    side++;
                    break;
                }
            }
            show(boardd);


        }
        else//bot
        {
            int* step = search(boardd, color);
            boardd[step[0]][step[1]] = -1;
            side++;
        }
    }
    if (ifover(boardd) == 1)
        white_win();
    else
        black_win();


    return 0;
}

