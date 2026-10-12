#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

vector<vector<int>> InitializeBoard(string fileName);
void PrintBoard(const vector<vector<int>>& board);
void GetInput();
vector<vector<int>> UpdateBoard(const vector<vector<int>>& board);

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        cout << "Podaj nazwę pliku z warunkami początkowymi jako argument wywołania" << endl;
        return 1;
    }


    //INITIALIZE
    string fileName = argv[1];
    vector<vector<int>> board = InitializeBoard(fileName);
    PrintBoard(board);

    while(true)
    {
        //GET INPUT
        GetInput();
        
        //UPDATE GAME
        board = UpdateBoard(board);

        //RENDER
        PrintBoard(board);

        this_thread::sleep_for(chrono::milliseconds(150));
    }
    return 0;
}

vector<vector<int>> InitializeBoard(string fileName)
{
    ifstream boardFile(fileName);

    if (!boardFile.is_open())
    {   
        cout << "Błąd obsługi pliku wejściowego\n";
        boardFile.close();
        exit(2);
    }

    string fileLine = "";
    vector<vector<int>> board = {};
    vector<int> boardRow = {};

    while(getline(boardFile, fileLine))
    {
        for(size_t i = 0; i < fileLine.size(); ++i)
        {
            char character = fileLine[i];
            if(character == '0' || character == '1')
            {
                boardRow.push_back(character - '0');
            } 
            else
            {
                cout<<"W pliku podano niedozwolony znak: " << character << endl;
                exit(3);
            }
            
        }
        board.push_back(boardRow);
        boardRow.clear();

    }

    return board;
}

void PrintBoard(const vector<vector<int>>& board)
{
    system("clear");
    for (const vector<int>& row:board)
    {
        for(int element:row)
        {
            if(element == 0) cout <<" ";
            else cout << element;
        }
        cout<<endl;
    }
}

void GetInput()
{
    cout << "Wciśnij przycisk ENTER aby przejść do następnej iteracji" << endl;
    string temp;
    getline(cin, temp);
}

vector<vector<int>> UpdateBoard(const vector<vector<int>>& board)
{
    vector<vector<int>> updatedBoard;
    vector<int> updatedRow = {};
    int neighbours = 0;

    for(size_t i = 0; i < board.size(); ++i)
    {
        updatedRow.clear();
        for(size_t j = 0; j < board[i].size(); ++j)
        {
            neighbours = 0;
            //Upper neighbours
            if(i != 0)
            {
                if (j != 0) neighbours += board[i-1][j-1];
                else neighbours += board[i-1][board[i].size() -1];
              
                neighbours += board[i-1][j];    
                
                if (j != board[i].size() -1) neighbours += board[i-1][j+1];
                else neighbours += board[i-1][0];
            } 
            else
            {
                if (j != 0) neighbours += board[board.size()-1][j-1];
                else neighbours += board[board.size()-1][board[i].size() -1];
                
                neighbours += board[board.size()-1][j];    
                
                if (j != board[i].size() -1) neighbours += board[board.size()-1][j+1];
                else neighbours += board[board.size()-1][0];
            }

            //Lower Neighbours
            if(i != board.size() -1)
            {
                if(j != 0) neighbours += board[i+1][j-1];
                else neighbours += board[i+1][board[i].size() -1];
                
                neighbours += board[i+1][j];    
                
                if(j != board[i].size() -1) neighbours += board[i+1][j+1];
                else neighbours += board[i+1][0];
            } 
            else
            {
                if(j != 0) neighbours += board[0][j-1];
                else neighbours += board[0][board[i].size() -1];

                neighbours += board[0][j];    

                if (j != board[i].size() -1) neighbours += board[0][j+1];
                else neighbours += board[0][0];
            }

            //Middle Neighbours
            if (j != 0) neighbours +=  board[i][j-1];
            else neighbours += board[i][board[i].size()-1] ;

            if (j != board[i].size() -1) neighbours +=  board[i][j+1];
            else neighbours += board[i][0];
            

            if (board[i][j] == 1)
            {
                if (neighbours == 2 || neighbours == 3) updatedRow.push_back(1);
                else updatedRow.push_back(0);
            } 
            else
            {
                if(neighbours == 3) updatedRow.push_back(1);
                else updatedRow.push_back(0);
            }
        }
        updatedBoard.push_back(updatedRow);
    }
    return updatedBoard;
}
