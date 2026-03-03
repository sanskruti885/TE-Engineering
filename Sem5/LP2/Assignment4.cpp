#include <iostream>
#include <vector>
using namespace std;

// Function to check if it is safe to place
int isSafe(vector<vector<int>>& mat, int row, int col) {
    int n = mat.size();

    // Check this column on upper side
    for (int i = 0; i < row; i++)
        if (mat[i][col])
            return 0;

    // Check upper diagonal on left side
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (mat[i][j])
            return 0;

    // Check upper diagonal on right side
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (mat[i][j])
            return 0;

    return 1;
}

// Recursive function to place queens
void placeQueens(int row,
                 vector<vector<int>>& mat,
                 vector<vector<vector<int>>>& result) {
    int n = mat.size();

    // base case
    if (row == n) {
        result.push_back(mat); // store full board
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(mat, row, col)) {
            mat[row][col] = 1;
            placeQueens(row + 1, mat, result);
            mat[row][col] = 0; // backtrack
        }
    }
}

// Function to find all solutions
vector<vector<vector<int>>> nQueen(int n) {
    vector<vector<int>> mat(n, vector<int>(n, 0));
    vector<vector<vector<int>>> result;

    placeQueens(0, mat, result);
    return result;
}

int main() {
    int n;
    cout<<"\nEnter matrix size: ";
    cin>>n;
    auto result = nQueen(n);

    int sol = 1;
    for (auto& board : result) {
        cout << "Solution " << sol++ << endl;
        for (auto& row : board) {
            for (int val : row)
                cout << val << " ";
            cout << endl;
        }
        cout << "----------------\n";
    }
    return 0;
}