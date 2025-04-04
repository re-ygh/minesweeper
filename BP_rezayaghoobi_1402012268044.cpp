#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include <limits>
using namespace std;



void map_front_namayesh(string map_front[22][22]);

int main()
{
    int input_number;
    cout<<"Minesweeper\n\n\n"<<"menu:\n\n"<<"1-play game \n"<<"2-exit\n"<<endl;


    //menu

    while (true) {
        cin >> input_number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
        }
        else if (input_number == 1) {
            break;
        } else if (input_number == 2) {
            exit(0);
        } else {
            cout << "Error: Invalid input. Please try again. You may only enter 1 or 2. " << endl;
        }
    }


    //deleting the menu

    system("cls");
    cout << "Minesweeper\npress x to exit the game.\n";


    //map back

    int map_back[10][10];
    int i, j;
    for( i = 0; i < 10; i++ ){
        for( j = 0; j < 10; j++){
            map_back[i][j]=0;
        }
    }




    //map front
    string map_front[22][22];
    string first_line[1][22]={"   "," ","a","   ","b","   ","c","   ","d","   ","e","   ","f","   ","g","   ","h","   ","i","   ","j","  "};
    string first_column[22][1]={"   ","   ","0 | ","   ","1 | ","   ","2 | ","   ","3 | ","   ","4 | ","   ","5 | ","   ","6 | ","   ","7 | ","   ","8 | ","   ","9 | ","   "};
    string oddline[1][22]={"---","-","---","-","---","-","---","-","---","-","---","-","---","-","---","-","---","-","---","-","--",""};
    string evenline[1][22]={"|","."," | ","."," | ","."," | ","."," | ","."," | ","."," | ","."," | ","."," | ","."," | ","."," |",""};
    for(i=0;i<22;i++){
        map_front[0][i]=first_line[0][i];
    }

    for(j=0;j<22;j++){
        map_front[j][0]=first_column[j][0];
    }

    for(i=1;i<22;i+=2){
        for(j=1;j<22;j++)
        map_front[i][j]=oddline[0][j];
    }
    
    for(i=2;i<22;i+=2){
        for(j=1;j<22;j++)
        map_front[i][j]=evenline[0][j];
    }
    char line_first[10]={'a','b','c','d','e','f','g','h','i','j'};
    int bombs_in_map_back;


    //unit of the bomb

    int x = time(0);
    int bomb;
    int bomb_array[10];
    srand (x);
    for ( i = 0; i < 10; i++ ){
        int up = 100, low = 0;
        bomb=9; 
        bomb_array[i] = (rand() % (up - low + 1)) + low;
    }



    //conversion of numbers inside bomb uints

    int line, column;
    for ( i = 0; i < 10; i++){
        column =  bomb_array[i] % 10;
        bomb_array[i]= bomb_array[i] / 10;
        line = bomb_array[i];
        map_back[line][column]= 9;
    }



    //numbering the units according to bombs around them

    for( line = 0; line < 10; line++ ){
        for( column = 0; column < 10; column++ ){
            if( map_back[line][column] == 9 ){
            continue;
            }
             for( i = -1; i <= 1; i++ ){
                for( j = -1; j <= 1; j++ ){
                    if( (line + i) >=0 && ( column + j) >= 0 ){
                        if ( (line + i) < 10 && ( column + j) < 10 ){
                            if( map_back[line+i][column+j] == 9){
                                map_back[line][column] += 1;
                            }
                        }
                    }
                }
            }
        }
    }




    // choose betwen CU and IF 

    string user_choosed_action;
    string flag="f", unit="u", exit_game="x", dot=".";
    int line_front;
    char column_front;
    int column_front_number= -1;
    bombs_in_map_back=10;

    while (bombs_in_map_back > 0){
        cout << "\nremaining bombs: " << bombs_in_map_back << endl;
        map_front_namayesh(map_front);
        cout << " first choose between inserting a flag (f) of choosing a unit (u):";
        cin >> user_choosed_action ; 

        //unit been choosen

        if (user_choosed_action == unit){

            //changing map front units inner number

            cout << endl << "line 0 to 9: ";
            cin >> line_front; 
            cout <<"\ncolumn a to j: ";
            cin>> column_front;
            if ( line_front < 10 && line_front >= 0 ){
                for ( i = 0; i < 10; i++){
                    if ( line_first[i] == column_front){
                        column_front_number = i;
                    }
                }
                if(column_front_number >= 0 && column_front_number < 10){
                    if(map_front[(line_front*2)+2][ (column_front_number*2)+1] == flag ){
                        system("cls");
                        cout << "there is a flag in this uint. first remove the flag by choosing f and the units line and column.\n\n";
                        cout << "press x to exit the game.\n\n";
                    }
                    else{
                        map_front[ (line_front*2)+2][ (column_front_number*2)+1] = to_string(map_back[line_front][column_front_number]);
                        if ( map_back[line_front][column_front_number] == 9 ){
                            system("cls");
                            cout<<"   ___   ___"<<endl;
                            cout<<"  / _ \\_/ _ \\"<<endl;
                            cout<<"  \\   ___   /"<<endl;
                            cout<<"    \\_____/"<<endl;
                            cout << "\n\n You lost the game!";
                            exit(0);
                        }
                        else{
                            system("cls");
                            cout << "press x to exit the game.\n\n";
                        }
                    }
                }
                else{
                   system("cls");
                   cout << "please try again"<<endl;
                   cout << "press x to exit the game.\n\n";
                }
            }
            else{
               system("cls");
               cout << "please try again"<<endl;
               cout << "press x to exit the game.\n\n";
            }
        }


        //flag been choosen


        else if(user_choosed_action == flag){
            cout << endl << "line 0 to 9: ";
            cin >> line_front; 
            cout <<"\ncolumn a to j: ";
            cin>> column_front;
            if ( line_front < 10 && line_front >= 0 ){
                for ( i = 0; i < 10; i++){
                    if ( line_first[i] == column_front){
                        column_front_number = i;
                    }
                }
                if(column_front_number >= 0 && column_front_number < 10){   
                    if ( map_back[line_front][column_front_number] == 9 ){
                        map_back[line_front][column_front_number] = -1;
                        map_front[(line_front*2)+2][ (column_front_number*2)+1]="f";
                        if ((bombs_in_map_back - 1) == 0){
                            system("cls");
                            cout << "\n\n\n\t\t you won the game!";
                            exit(0);
                        }
                        else {
                        system("cls");
                        cout << "press x to exit the game.\n\n";
                        bombs_in_map_back == --bombs_in_map_back;
                        }
                    }
                    else if( map_back[line_front][column_front_number] == -1 ){
                        map_front[(line_front*2)+2][ (column_front_number*2)+1]=".";
                        map_back[line_front][column_front_number]=9;
                        system("cls");
                        cout << "press x to exit the game.\n\n";
                        bombs_in_map_back ==  ++bombs_in_map_back;
                    }
                    
                    else{
                        if ( map_front[(line_front*2)+2][ (column_front_number*2)+1] == dot ){
                            map_front[(line_front*2)+2][ (column_front_number*2)+1]=flag;
                            system("cls");
                            cout << "press x to exit the game.\n\n";
                        }
                        else if (map_front[(line_front*2)+2][ (column_front_number*2)+1] == flag){
                            map_front[(line_front*2)+2][ (column_front_number*2)+1]=dot;
                            system("cls");
                            cout << "press x to exit the game.\n\n";
                        }
                        else {
                            system("cls");
                            cout << "this unit has been chooesd and displayed before. please try again.";
                            cout << "press x to exit the game.\n\n" ;
                        }
                    }
                }
                else{
                    system("cls");
                    cout << "please try again"<<endl;
                    cout << "press x to exit the game.\n\n"; 
                }
            }
            else{
                system("cls");
                cout << "please try again"<<endl;
                cout << "press x to exit the game.\n\n"; 
            }
        }

        // x been choosen
        else if ( user_choosed_action == exit_game ){
            exit(0);
        }
        else {
            system("cls");
            cout << "please try again"<<endl;
            cout << "press x to exit the game.\n\n";
        }
    }
return 0;
}   


//map front function
void map_front_namayesh(string map_front[22][22])
{
    //printing the front map
    int i, j;
        for(i=0;i<22;i++)
    {
        for(j=0;j<22;j++)
        {
            cout << map_front[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}