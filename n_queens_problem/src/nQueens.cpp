#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <iomanip>

using std::vector;

// N-Queen problem
// Place N number of queens to N x N sized chess board
//      such that each of the queens do not attack another

void getQueensPlacedSolution(vector<int>& queens,
                             vector<vector<int> >& allPlacements,
                             int n,
                             int index);
bool valid(const vector<int>& queens);

vector<vector<int> > getQueensPlaced(int n) {
    vector<int> queensPlacedSoFar;
    vector<vector<int> > allPlacements;
    getQueensPlacedSolution(queensPlacedSoFar, allPlacements, n, 0);
    return allPlacements;
}

void getQueensPlacedSolution(vector<int>& queens,
                             vector<vector<int> >& allPlacements,
                             int n,
                             int index) {
    if (index == n) {
        allPlacements.emplace_back(queens);
        return;
    }

    for (int i = 0; i < n; ++i) {
        queens.push_back(i);
        if (valid(queens)) {
            getQueensPlacedSolution(queens, allPlacements, n, index+1);
        }
        queens.pop_back();
    }
}

bool valid(const vector<int>& queens) {
    int soFar = queens.size()-1;
    for (int i = 0; i < soFar; ++i) {
        int diff = queens[i] - queens[soFar];
        if (diff == 0 || std::abs(diff) == soFar - i) {
            return false;
        }
    }
    return true;
}

// print the table for queens placements
static void print(const vector<int>& pos) {
    // print table header
    for (int i = 0; i < pos.size(); i++) {
        std::cout << std::setw(3) << char('a' + i);
    }
 
    std::cout << std::endl;
 
    for (int row = 0; row < pos.size(); row++) {
        int col = pos[row];
        std::cout << row + 1 << std::setw(3 * col + 3) << " X ";
        std::cout << std::endl;
    }
 
    std::cout << "\n\n";
}

static void printAll(const vector<vector<int> >& allPlacements) {
    for (const auto& i : allPlacements) {
        print(i);
    }
}

int main() {
    auto ret = getQueensPlaced(8);
    printAll(ret);
    return 0;
}
