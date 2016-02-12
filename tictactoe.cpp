#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <time.h>
using namespace std;

/*
    as board_print() is a messy function and wont be used very often
    I placed it after main() function so a function
*/
void board_print(char *board);
/*
    following 3 functions are used to place white spaces or gaps between lines... like         this....
*/
string whitespace();
string whitespace2();
string whitespace3();

/*
    this function is used to place newlines;
*/
void place_spaces();
void pc_move(char *board, int player_count);


/*
    this function endgame will check for if the game is finished or not.
*/
bool endgame(char *board){
   if((board[0] == board[1]) && (board[1] == board[2]) && board[0] != ' ' && board[1] != ' ' && board[2] != ' '){
        return true;
   } else if((board[0] == board[3]) && (board[3] == board[6]) && board[0] != ' ' && board[3] != ' ' && board[6] != ' '){
        return true;
   } else if((board[3] == board[4]) && (board[4] == board[5]) && board[3] != ' ' && board[4] != ' ' && board[5] != ' '){
        return true;
   } else if((board[6] == board[7]) && (board[7] == board[8]) && board[6] != ' ' && board[7] != ' ' && board[8] != ' '){
        return true;
   } else if((board[1] == board[4]) && (board[4] == board[7]) && board[1] != ' ' && board[4] != ' ' && board[7] != ' '){
        return true;
   } else if((board[2] == board[5]) && (board[5] == board[8]) && board[2] != ' ' && board[5] != ' ' && board[8] != ' '){
        return true;
   } else if((board[0] == board[4]) && (board[4] == board[8]) && board[4] != ' ' && board[4] != ' ' && board[8] != ' '){
        return true;
   } else if((board[2] == board[4]) && (board[4] == board[6]) && board[2] != ' ' && board[4] != ' ' && board[6] != ' '){
        return true;
   } else {
        return false;
   }

}

/*
    In multi player mode players switch their turns. following function controls it...
    player_move() function also checks whether a player is inputing valid input or not...
*/

void player_move(char *board,int player_count){
    int player_turn;                        // variable to store which block player will choose.
    for(;;){
        if(player_count%2 != 0){
            cout << "Player 1 turn" << endl;
        } else {
            cout << "Player 2 turn" << endl;
        }
        cin >> player_turn;
        if(player_turn >= 1 && player_turn <= 9){
            if(board[player_turn-1] == ' '){
                break;
            } else {
                cout << "The block is already taken" << endl;;
            }
        } else {
            cout << "Please enter number between 1<x<9" << endl;
        }
    }
    if(player_count%2 != 0){
        board[player_turn-1] = 'X';
    } else {
        board[player_turn-1] = 'O';
    }
}
/*
    intro and game type function prints the introduction page and
    it shows the selection list for single and multi player modes
*/
int intro_and_game_type(){
    int type_selector;

    place_spaces();
    cout << whitespace() << "TIC TAC TOE" << endl;
    cout << whitespace2() << "  ";
    cout << "Enter game type: \n "<< whitespace3() << "    1. Single player\n " << whitespace3() <<"    2. Multi player" << endl;
    cout << whitespace3() << "     ";
    cin >> type_selector;
    system("CLS");
    return type_selector;
}

/*
    The main controller for the multi player mode...
    it takes parameter from main and controls the multi player mode..
*/
void multiplayer_game(char *board, int player_count){
    for(;;){
        board_print(board);
        player_move(board, player_count);
        player_count++;
        system("CLS");
        if(player_count >= 10){
            board_print(board);
            cout << "Match draw!!" << endl;
            break;
        }
        if(endgame(board) == true){
            board_print(board);
            cout << "Player " << (player_count%2)+1 << " wins" << endl;
            break;
        }
    }
}

/*
    move for player in single player...
*/

void player_sp_move(char *board, int player_count){
    int player_turn;
    for(;;){
        if(player_count%2 != 0){                      // player move in single player mode
            cout << "Player turn" << endl;
            cin >> player_turn;
            if(player_turn >= 1 && player_turn <= 9){
                if(board[player_turn-1] == ' '){
                    board[player_turn-1] = 'X';
                    break;
                } else {
                    cout << "The block is already taken" << endl;;
                }
            } else {
                cout << "Please enter number between 1<x<9" << endl;
            }
        } else {
            pc_move(board, player_count);
            break;
        }

    }
}

// returns opposite value relative to mid
int opposite(char *board){
    int i,x;
    for(i=0;i<9;i++){
        if(board[i] == 'X' && i != 4){
            x = 12-(i+4);           // As the addition of opposite index numbers of the
            if(board[x] == ' '){          // array is 12
                return x;
            }
        }
    }
}

/*
    this function determines if the player has an opportunity or not.
    then it sends the index of the board where the player can win
*/
int cheak_player_win(char *board){
    int i;
    for(i=0;i<9;i++){
        if(board[i] == ' '){
            board[i] = 'X';
             if(endgame(board) == true){
                board[i] = ' ';
                return i;
            } else {
                board[i] = ' ';
            }
        }
    }
}

/*
    this function determines if the the computer has an opportunity to win or not
*/
bool check_pc_win(char *board){
    int i;
    for(i=0;i<9;i++){
        if(board[i] == ' '){
            board[i] = 'O';
             if(endgame(board) == true){
                return true;
            } else {
                board[i] = ' ';
            }
        }
    }
    return false;
}

/*
    generates random numbers...
*/
int random(int number = 4){
    int x;
    srand (time(NULL));
    x = rand() % number;
    return x;
}

/*
    this function controls the mid tree or if the
    chooses to go first with mid this function will
    trigger..
*/

void mid_tree(char *board, int player_count){
    int corner_piece[4] = {0,2,6,8};
    int side_piece[4] = {1,3,5,7};
    if(player_count == 2){
        int x = random();
        board[corner_piece[x]] = 'O';
    } else if(player_count == 4){
        int x = opposite(board);
        if(x < 9){
            board[x] = 'O';
        } else {
            int m;
            for(;;){
                m = random(9);
                if(board[m] == ' '){
                    board[m] = 'O';
                    break;
                }
            }
        }
    } else if(player_count == 6){
        bool x = check_pc_win(board);
        if(x == false){
            int x = opposite(board);
            if(x > 0 && x < 9){
                board[x] = 'O';
            } else {
                int m;
                for(;;){
                    m = random(9);
                    if(board[m] == ' '){
                        board[m] = 'O';
                        break;
                    }
                }
            }
        }
    } else if(player_count == 8){
        bool x = check_pc_win(board);
        if(x == false){
            int x = opposite(board);
            if(x > 0 && x < 9){
                board[x] = 'O';
            } else {
                int m;
                for(;;){
                    m = random(9);
                    if(board[m] == ' '){
                        board[m] = 'O';
                        break;
                    }
                }
            }
        }

    }
}


/*
    this function controls the corner tree;
*/

void corner_tree(char *board,int player_count){
    int corner_piece[4] = {0,2,6,8};
    int side_piece[4] = {1,3,5,7};
    int mid_piece = 4;

    if(player_count == 2){
        board[mid_piece] = 'O';
    } else if(player_count == 4){
        int x = cheak_player_win(board);
        if(x > 0 && x < 9){
            board[x] = 'O';
        } else {
            if(x%2 == 0){
                board[side_piece[random()]] = 'O';
            } else {
                board[corner_piece[random()]] = 'O';
            }
        }
    } else if(player_count == 6){
        bool x = check_pc_win(board);
        if(x == false){
            int y = cheak_player_win(board);
            if(y>0 && y<9){
                board[y] = 'O';
            } else {
               int m;
                int n[2];
                int i=0;
                for(m=0;m<9;m++){
                    if(board[m] == ' '){
                        n[i] = m;
                        i++;
                    }
                }
                m = random(2);
                board[n[m]] = 'O';
                }
            }
        }
     else if(player_count == 8){
        bool x = check_pc_win(board);
        if(x == false){
            int y = cheak_player_win(board);
            if(y>0 && y<9){
                board[y] = 'O';
            } else {
                int m;
                int n[2];
                int i=0;
                for(m=0;m<9;m++){
                    if(board[m] == ' '){
                        n[i] = m;
                        i++;
                    }
                }
                m = random(2);
                board[n[m]] = 'O';
            }
        }
    }
}



/*
    this function controls the side tree
*/
void side_tree(char *board, int player_count){
    int corner_piece[4] = {0,2,6,8};
    int side_piece[4] = {1,3,5,7};
    int mid_piece = 4;

    if(player_count == 2){
        board[mid_piece] = 'O';
    } else if(player_count >= 4){
        bool x = check_pc_win(board);
        if(x == false){
            int y = cheak_player_win(board);      // here computers first see if the player is winning or not
            if(y>0 && y<9){                         // then
                board[y] = 'O';
            } else {
               int m;
                int n[6];
                int i=0;
                for(m=0;m<9;m++){
                    if(board[m] == ' '){
                        n[i] = m;
                        i++;
                    }
                }
                m = random(6);
                board[n[m]] = 'O';
                }
            }
    }
}



/*
    pc_move() function controls the moves pc will make.
*/
void pc_move(char *board, int player_count){
    if(board[4] == 'X'){
        mid_tree(board,player_count);
    } else if((board[0] == 'X' || board[2] == 'X' || board[6] == 'X' || board[8] == 'X')){
        corner_tree(board,player_count);
    } else if((board[1] == 'X' || board[3] == 'X' || board[5] == 'X' || board[7] == 'X')){
        side_tree(board,player_count);
    }
}



int main(){
    /*
        1D array with 9 elements for 9 blocks
    */
    char board[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int player_count=1;
    int game_type;
    char x;

    game_type = intro_and_game_type();

    if(game_type == 1){
        for(;;){
            board_print(board);
            player_sp_move(board,player_count);
            system("CLS");
            if(endgame(board) == true || player_count >= 9){
                board_print(board);
                if(player_count == 9){
                    cout << "Draw" << endl;
                } else if(player_count % 2 == 0){
                    cout << "PC wins" << endl;
                } else {
                    cout << "Player wins" << endl;
                }
                break;
            }
            player_count++;
        }
    } else {
        multiplayer_game(board, player_count);
    }

    system("pause");
    return 0;
}

/*
    this board_print() function will print the board with
    the current value of x and o.
*/

void board_print(char *board){
    place_spaces();
    cout << whitespace() << "|" << "      |" << "      " << endl;
    cout << whitespace2() << board[0] <<"   " << "|  "<< board[1] <<"   " << "|   "<< board[2] <<"  " << endl;
    cout << whitespace() << "|" << "      |" << "      " << endl;
    cout << whitespace3() << "-----------------------" << endl;
    cout << whitespace() << "|" << "      |" << "      " << endl;
    cout << whitespace2() << board[3] <<"   " << "|  "<< board[4] <<"   " << "|   "<< board[5] <<"  " << endl;
    cout << whitespace() << "|" << "      |" << "      " << endl;
    cout << whitespace3()<< "-----------------------" << endl;
    cout << whitespace() <<"|" << "      |" << "      " << endl;
    cout << whitespace2() << board[6] <<"   " << "|  "<< board[7] <<"   " << "|   "<< board[8] <<"  " << endl;
    cout << whitespace()<< "|" << "      |" << "      " << endl;

}

string whitespace(){
    string space = "                                  ";
    return space;
}

string whitespace2(){
    string space = "                              ";
    return space;
}

string whitespace3(){
    string space = "                           ";
    return space;
}

void place_spaces(){
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
}

/* void bubble_sort(int temp[9], int j){
    int i,k,tempo;
    for(i=0;i<j;i++){
        for(k=i+1;k<j;k++){
            if(i<k){
                tempo = temp[i];
                temp[i] = temp[k];
                temp[k] = tempo;
            }
        }
    }
} */

/*int random(char *boboard[0] == 'X'ard){
    int x,i;
    int temp[9],temp2[9];
    time_t  timev;
    x = time(&timev);
    for(i=0;i<9;i++){
        if(board[i] == ' '){
            temp[i] = (x * (i+1) + 1539) % 1639;
            temp2[i] = i;
        } else {
            temp[i] = 0;
            temp2[i] = 0;
        }
    }
    bubble_sort(temp,i);
    cout << temp[0] << endl;
    cout << temp[1] << endl;
    cout << temp[2] << endl;board[corner_piece[random()]] = 'O';
    //return temp[0];
} */



