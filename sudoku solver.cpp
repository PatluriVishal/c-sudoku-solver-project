#include <iostream>
#include <vector>
using namespace std;
void display_sudoku(int sud[9][9])
{
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << sud[i][j] << " ";
        }
        cout << endl;
    }
    
}
bool can_place(int arr[9][9], int row, int col, int value)
{
    if (arr[row][col] != 0) return false;
    bool status = true;
    int horizantal_grid = (col / 3) * 3;
    int vertical_grid = (row / 3) * 3;

    for (int i = 0; i < 9; i++)
    {
        if (arr[row][i] == value)
        {
            status = false;
            break;
        }
        if (arr[i][col] == value)
        {
            status = false;
            break;
        }
        if (arr[vertical_grid + i / 3][horizantal_grid + i % 3] == value)
        {
            status = false;
            break;
        }
    }
    return status;
}
void next_empty(int arr[9][9], int row, int col, int& next_row, int& next_col)
{
    int index = (9*9)+1;
    for (int i = row * 9 + col + 1; i < 9 * 9; i++)
    {
        if (arr[i / 9][i % 9] == 0)
        {
            index = i;
            break;
        }
    }
    next_row = index / 9;
    next_col = index % 9;
}
void copy_array(int arr[9][9], int arr_copy[9][9])
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            arr_copy[x][y] = arr[x][y];
        }
    }
}
std::vector<int> find_placeables(int arr[9][9], int r, int c)
{
    vector<int> cps = {};
    for (int i = 1; i <= 9; i++)
    {
        if (can_place(arr, r, c, i))
        {
            cps.push_back(i);
        }
    }
    return cps;
}


bool solve_sudoku(int arr[9][9], int row, int col)
{ 
    

    if (row > 8)
        return true;
    if (arr[row][col] != 0)
    {
        int next_row, next_col;
        next_empty(arr, row, col, next_row, next_col);
        return solve_sudoku(arr, next_row, next_col);
    }

    vector<int> placeables = find_placeables(arr, row, col);
    if (placeables.size() == 0){
        return false;
    };
        
    bool status = false;
    for (int i = 0; i < placeables.size(); i++)  
    {
        int n = placeables[i];
        int array_copy[9][9];
        copy_array(arr, array_copy);
        array_copy[row][col]=n;
        int next_row=row, next_col=col;
        next_empty(array_copy, row, col, next_row, next_col);
        if (solve_sudoku(array_copy, next_row, next_col))
        {
            copy_array(array_copy, arr);
            status = true;
            break;
        }
    }
    return status;
}

int main()
{
    int sudoku[9][9] = {
        {8,0,0,0,0,0,0,0,0},
		{0,0,3,6,0,0,0,0,0},
		{0,7,0,0,9,0,2,0,0},
		{0,5,0,0,0,7,0,0,0},
		{0,0,0,0,4,5,7,0,0},
		{0,0,0,1,0,0,0,3,0},
		{0,0,1,0,0,0,0,6,8},
		{0,0,8,5,0,0,0,1,0},
		{0,9,0,0,0,0,4,0,0}};
    cout<<"The Unsolved sudoku puzzle is"<<endl;
    display_sudoku(sudoku);
    cout<<endl<<"--------------------------------"<<endl;
    cout<<"The solved sudoku puzzle is"<<endl;
    solve_sudoku(sudoku,0,0);
    display_sudoku(sudoku);
    return 0;
}