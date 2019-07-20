/*		Github --> https://github.com/singhiqbal1007/          
		Tic Tac Toe program in C using AI.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

/*Draw Board*/
void drawBoard(char arr[]){
system ("CLS");
printf("------Tic Tac Toe-----\n");
printf("\n       |       |       \n");
printf("   %c   |   %c   |   %c   \n",arr[0],arr[1],arr[2]);
printf("       |       |       \n");
printf("-----------------------\n");
printf("       |       |       \n");
printf("   %c   |   %c   |   %c   \n",arr[3],arr[4],arr[5]);
printf("       |       |       \n");
printf("-----------------------\n");
printf("       |       |       \n");
printf("   %c   |   %c   |   %c   \n",arr[6],arr[7],arr[8]);
printf("       |       |       \n\n");
}

/*Who Goes First*/
char whoGoesFirst(){
srand(time(0));
    if(rand() % 2){
        return 'p';
    }
    else{
        return 'c';
    }
}

/* Check If Won */
char isWinner(char b[], char symbol){
    if( (b[0]==symbol && b[1]==symbol && b[2]==symbol) ||
        (b[3]==symbol && b[4]==symbol && b[5]==symbol) ||
        (b[6]==symbol && b[7]==symbol && b[8]==symbol) ||
        (b[0]==symbol && b[3]==symbol && b[6]==symbol) ||
        (b[1]==symbol && b[4]==symbol && b[7]==symbol) ||
        (b[2]==symbol && b[5]==symbol && b[8]==symbol) ||
        (b[0]==symbol && b[4]==symbol && b[8]==symbol) ||
        (b[2]==symbol && b[4]==symbol && b[6]==symbol) )
        return 't';

    return 'f';
}

/*Check Tie*/
char isTie(char b[]){
    int i;
    for(i=0;i<9;i++){
        if(b[i]!=' ')
        continue;
    return 'f';
    }
    return 't';
}

/*Get Player Move*/
int getPlayerMove(char board[],char playerSymbol){
    char cmove;
    int move,flag=1;
    while(flag){
        printf("Enter your move[1-9]: ");
        scanf(" %c",&cmove);
        move = (int) cmove;
        move = move - 48;
        if(move > 9 || move < 1){ /* Invalid Move */
            continue;
        }
        else if(board[move-1]!=' '){ /* space is not free */
            continue;
        }
        else{
            flag = 0;
            return move-1;
        }
    }
}

/* Get Computer Move */
int getComputerMove(char board[],char computerSymbol){
    int i,j;
    char boardCopy[9] = {' ',' ', ' ', ' ',' ',' ',' ',' ',' '};
    char playerSymbol,flag='f';

    /* Make Copy of Board */
    for(j=0;j<9;j++){
    boardCopy[j]=board[j];
    }

    if(computerSymbol == 'X'){
        playerSymbol = 'O';
    }
    else playerSymbol = 'X';

    /* Make Winning Move */
    for(i=0;i<9;i++){
        if(boardCopy[i]==' '){
            boardCopy[i]=computerSymbol;
            flag = isWinner(boardCopy,computerSymbol);
            if(flag=='t'){
                return i;
            }
            else{
                boardCopy[i]=' ';
            }

        }
    }

    /* Block Player Winning Move */
    for(i=0;i<9;i++){
        if(boardCopy[i]==' '){
            boardCopy[i]=playerSymbol;
            flag = isWinner(boardCopy,playerSymbol);
            if(flag=='t'){
                return i;
            }
            else{
                boardCopy[i]=' ';
            }

        }
    }

    /* Move on Center */
    if(board[4] == ' '){
        return 4;
    }

    /* Make Random Move at Corner */
    for(i=0;i<9;i++){
        if(i==0||i==2||i==6||i==8){
            if(board[i]==' '){
                return i;
            }
            }
    }

    /* Make Random Move */
    for(i=0;i<9;i++){
            if(board[i]==' '){
                return i;
            }
    }
}

/* Make Move */
void makeMove(char board[], char symbol, int move){
    board[move] = symbol;
}

/*Main Function*/
void main(){
char choice;
int checkChoice=1, i, move, isPlaying=1, xflag=0;
char playerSymbol, computerSymbol, turn, playAgain;
char board[9];

    printf("Welcome to Tic Tac Toe\n");

    while(isPlaying){

        /* Reset Board */
        for(i=0;i<9;i++){
            board[i]= ' ';
        }

        /* Get Player Symbol */
        while(checkChoice){
            printf("Select Your Symbol(O/X): ");
            scanf(" %c",&choice);
            if(choice == 'x' || choice == 'X'){
                playerSymbol='X';
                computerSymbol='O';
                checkChoice=0;
            }
            else if(choice == 'o' || choice == 'O'){
                playerSymbol = 'O';
                computerSymbol = 'X';
                checkChoice=0;
            }
        }

        /* Decide Who Goes First */
        turn = whoGoesFirst();
        if(turn=='p'){
            xflag=1;
        }
        else{
            xflag=2;
        }

        while(1){
            if(turn=='p'){
                drawBoard(board);
                if(xflag==1){
                    printf("\nYou Will Go First.\n");
                    xflag=0;
                }
                else if(xflag==2){
                    printf("\nComputer Will Go First.\n");
                    xflag=0;
                }
                move = getPlayerMove(board,playerSymbol);
                makeMove(board,playerSymbol,move);
                if(isWinner(board,playerSymbol) == 't'){
                    printf("You Win");
                    break;
                }
                else if(isTie(board) == 't'){
                    drawBoard(board);
                    printf("Its a Tie");
                    break;
                }
                else{
                    turn='c';
                }
            }
            else if(turn=='c'){
                move = getComputerMove(board,computerSymbol);
                makeMove(board,computerSymbol,move);
                if(isWinner(board,computerSymbol) == 't'){
                    drawBoard(board);
                    printf("You Lose");
                    break;
                }
                else if(isTie(board) == 't'){
                    drawBoard(board);
                    printf("Its a Tie");
                    break;
                }
                else{
                    turn='p';
                }
            }
        }
        printf("\nDo You Want to Play Again:(Y/N)");
        scanf(" %c",&playAgain);
            if(playAgain=='Y' || playAgain=='y'){
                isPlaying=1;
            }
            else{
                isPlaying=0;
            }
    }
}
