#include<bits/stdc++.h>
#include<iostream>
using namespace std;
#define computer 1
#define human 2
#define side 3
#define computermove 'O'
#define humanmove 'X'

void showboard(char board[][side])
{
	cout<<"\n\t\t\t"<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<"\n";
	cout<<"\t\t\t-------\n";
	cout<<"\t\t\t"<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<"\n";
	cout<<"\t\t\t-------\n";
	cout<<"\t\t\t"<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<"\n";
	
}
void showinstruction()
{
	cout<<"\nChoose a cell numbered from 1 to 9 as below and play \n\n";
	cout<<"\t\t\t1 | 2 | 3 \n";
	cout<<"\t\t\t----------\n";
	cout<<"\t\t\t4 | 5 | 6 \n";
	cout<<"\t\t\t----------\n";
	cout<<"\t\t\t7 | 8 | 9 \n";
}
void initialize(char board[][side])
{
	for(int i=0;i<side;i++)
	{
		for(int j=0;j<side;j++)
		{
			board[i][j]='*';
		}
	}
}

void declarewinner(int turn)
{
	if(turn==computer)
	cout<<"Computer has won\n";
	else
	cout<<"Human player has won\n";
}

bool rowcrossed(char board[][side])
{
	for(int i=0;i<side;i++)
	{
		if(board[i][0]==board[i][1]&& board[i][1]==board[i][2]&& board[i][0]!='*')
		return true;
	}
	return false;
}


bool columncrossed(char board[][side])
{
	for(int i=0;i<side;i++)
	{
		if(board[0][i]==board[1][i]&& board[1][i]==board[2][i] && board[0][i]!='*')
		return true;	
	}
	return false;
}

bool diagonalcrossed(char board[][side])
{
	if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*')
		return true;
	if(board[0][2]==board[1][1] && board[2][0] ==board[1][1] && board[0][2]!='*')
	return true;
	
	return false;
}

bool gameover(char board[][side])
{
	return(rowcrossed(board) || columncrossed(board) || diagonalcrossed(board));
}

int minimax(char board[][side],int depth,bool isCom)
{
	int score=0;
	int bestscore=0;
	if(gameover(board)==true)
	{
		if(isCom==true)
		return -10;
		if(isCom ==false)
		return +10;
	}
	else{
		if(depth<9)
		{
			if(isCom==true)
			{
				bestscore=-999;
				for(int i=0;i<side;i++)
				{
				for(int j=0;j<side;j++)
				{
					if(board[i][j]=='*')
					{
						board[i][j]=computermove;
						score=minimax(board,depth+1,false);
						board[i][j]='*';
						if(score>bestscore)
						{
							bestscore=score;
						}
					}
				}
			}
			return bestscore;
		}
		else{
			bestscore=999;
			for(int i=0;i<side;i++)
			{
				for(int j=0;j<side;j++)
				{
					if(board[i][j]=='*')
					{
						board[i][j]=humanmove;
						score=minimax(board,depth+1,true);
						board[i][j]='*';
						if(score<bestscore)
						{
							bestscore=score;
						}
					}
				}
			}
			return bestscore;
		}
		
	  }
	   else
	  {
		return 0;
	  }
   }
}

int bestmove(char board[][side],int moveIndex)
{
	int m=-1,n=-1;
	int score=0,bestscore=-999;
	for(int i=0;i<side;i++)
	{
		for(int j=0;j<side;j++)
		{
			if(board[i][j]=='*')
			{
				board[i][j]=computermove;
				score=minimax(board,moveIndex+1,false);
				board[i][j]='*';
				if(score>bestscore)
				{
					bestscore=score;
					m=i;
					n=j;
				}
			}
		}
	}
	return m*3+n;
}



void playTicTacToe(int whoseTurn)
{
	char board[side][side];
	int moveIndex=0,x=0,y=0;
	initialize(board);
	showinstruction();
	while(gameover(board)==false && moveIndex!=side*side)
	{
		int n;
		if(whoseTurn==computer)
		{
			n=bestmove(board,moveIndex);
			x=n/side;
			y=n%side;
			board[x][y]=computermove;
			cout<<"Computer has put a "<<computermove<<" in cell"<<n+1;
			showboard(board);
			moveIndex++;
			whoseTurn=human;
		}
		else if(whoseTurn==human)
		{
			cout<<"\nYou can insert in following positions:";
			for(int i=0;i<side;i++)
			   for(int j=0;j<side;j++)
			   {
			   	if(board[i][j]=='*')
			   	{
			   		cout<<" "<<i*3+j+1;
				   }
			   }
		cout<<"\n\nEnter the position: ";
		cin>>n;
		n--;
		x=n/side;
		y=n%side;
	      	if(board[x][y]=='*' && n>=0 && n<9)
		   {
			board[x][y]=humanmove;
			cout<<"\nHuman player has put "<<humanmove<<" in cell"<<n+1;
			showboard(board);
			moveIndex++;
			whoseTurn=computer;
	     	}
		   else if(board[x][y]!='*' && n>=0 && n<9)
		   {
			cout<<"\nThe position is already occupied,Select anyone place from the available places\n";
		   }
		   else if(n<0 || n>8)
		   {
			cout<<"\nInvalid position\n";
		   }
		}
	 }
	 if(gameover(board)==false && moveIndex==side*side)
	 {
	 	cout<<"\nThe game is draw\n";
	 }
	 else
	 {
	 	if(whoseTurn==computer)
	 	whoseTurn=human;
	 	else if(whoseTurn==human)
	 	whoseTurn=computer;
	 	declarewinner(whoseTurn);
	 }
}

int main()
{
	cout<<"\n--------------------------------------------\n\n";
	cout<<"\t\t\t TIC - TAC - TOE \n";
	cout<<"\n--------------------------------------------\n\n";
	char ch='n';
	do{
		char choice;
		cout<<"\nDo ypu want to start first?(y/n):";
		cin>>choice;
		if(choice=='y'|| choice=='Y')
		{
			playTicTacToe(human);
		}
		else if(choice=='n')
		playTicTacToe(computer);
		else
		{
			cout<<"\nInvalid choice\n";
		}
		cout<<"\nDo you want to Quit(y/n): ";
		cin>>ch;
	}while(ch=='n'||ch=='N');
 return 0;	
}
