// UMBC - CMSC 341 - Fall 2026 - Proj0
#include "bingo.h"

// default constructor - sets up safe empty values
Bingo::Bingo(){
    m_minBallVal = 0;
    m_maxBallVal = 0;
    m_card = nullptr;
    m_numRows = 0;
    m_numCols = 0;
    m_trackRows = nullptr;
    m_trackCols = nullptr;
    m_helper = nullptr;
    m_helperSize = 0;
}

// overloaded constructor - lets reCreateCard handle the setup
Bingo::Bingo(int rows, int columns, int min, int max){
    m_minBallVal = 0;
    m_maxBallVal = 0;
    m_card = nullptr;
    m_numRows = 0;
    m_numCols = 0;
    m_trackRows = nullptr;
    m_trackCols = nullptr;
    m_helper = nullptr;
    m_helperSize = 0;

    reCreateCard(rows, columns, min, max);
}

// checks bounds, clears old stuff, and sets up a new card
bool Bingo::reCreateCard(int rows, int columns, int min, int max){
    clear();

    int maxRange = (max - min) + 1;

    if (rows < 2 || rows > 15 || columns != 5 || maxRange % 5 != 0 || min > max){
        return false;
    }

    m_minBallVal = min;
    m_maxBallVal = max;
    m_numRows = rows;
    m_numCols = columns;
    m_helperSize = max + 1;

    return initCard();
}


// destructor - just calls clear to free memory
Bingo::~Bingo(){
    clear();
}

// helper to safely delete all dynamic arrays and reset pointers
void Bingo::clear(){
   if (m_card != nullptr){
        for (int i = 0; i < m_numRows; i++){
            delete[] m_card[i];
        }
        delete[] m_card;
        m_card = nullptr;
    }
   
   delete[] m_trackRows;
   m_trackRows = nullptr;

   delete[] m_trackCols;
   m_trackCols = nullptr;

   delete[] m_helper;
   m_helper = nullptr;
}

// allocates grid/tracking arrays and populates card using shuffled columns
bool Bingo::initCard(){
    if (m_numCols <= 0){
        return false;
    }

    clear();
    
    m_card = new Cell*[m_numRows];

    for (int i = 0; i < m_numRows; i++){
        m_card[i] = new Cell[m_numCols];
    }

    m_trackRows = new int[m_numRows]();
    m_trackCols = new int[m_numCols]();
    m_helper = new Cell[m_helperSize]();

    int range = (m_maxBallVal - m_minBallVal) + 1;
    int span = range / m_numCols;

    for (int col = 0; col < m_numCols; col++){
        int colMin = m_minBallVal + (col * span);
        // For the last column, make sure it absorbs any leftover numbers due to integer division remainder
        int colMax = (col == m_numCols - 1) ? m_maxBallVal : (colMin + span - 1);

        Random genCol(colMin, colMax, SHUFFLE);
        vector<int> spanBall;
        genCol.getShuffle(spanBall);

        for (int row = 0; row < m_numRows; row++){
            int val = spanBall[row];

            m_card[row][col] = Cell(row + 1, col + 1, val);

            // Ensure val is within helper bounds before writing to prevent segfaults
            if (val >= 0 && val < m_helperSize) {
                m_helper[val] = Cell(row + 1, col + 1, val);
            }
        }
    }

    return true;
}

// generates a randomized, shuffled list of all valid ball numbers
vector<int> Bingo::drawBalls(){
    vector<int> ball;
    Random Generate(m_minBallVal, m_maxBallVal, SHUFFLE);
    Generate.getShuffle(ball);
    return ball;
}

// simulates gameplay, marks matching cells, and checks for row/col wins
int Bingo::play(int numDraws, vector<int> rndBalls){
    if (numDraws <= 0 || numDraws > m_maxBallVal || (int)rndBalls.size() > BALLS ){
        return 0;
    }

    int count = 0;
    int maxDraws = min(numDraws, (int)rndBalls.size());

    for (int i = 0; i < maxDraws; i++){
        int numBall = rndBalls[i];

        if (numBall >= m_minBallVal && numBall <= m_maxBallVal){
            Cell &helperCell = m_helper[numBall];

            if (!helperCell.isEmpty()){
                int row = helperCell.getRow();
                int col = helperCell.getCol();

                m_card[row - 1][col - 1].setVal(EMPTYCELL);

                helperCell.setVal(EMPTYCELL);

                count++;

                m_trackRows[row - 1]++;
                m_trackCols[col - 1]++;

                if (m_trackRows[row - 1] == m_numCols || m_trackCols[col - 1] == m_numRows){
                    return count;
                }
            }
        }
    }
    return count;
}


// creates a deep copy of rhs
const Bingo & Bingo::operator=(const Bingo & rhs){
    if (this != &rhs){
        clear();

        m_minBallVal = rhs.m_minBallVal;
        m_maxBallVal = rhs.m_maxBallVal;
        m_numRows = rhs.m_numRows;
        m_numCols = rhs.m_numCols;
        m_helperSize = rhs.m_helperSize;

        if (rhs.m_card != nullptr){
            m_card = new Cell*[m_numRows];

            for (int i = 0; i < m_numRows; i++){
                m_card[i] = new Cell[m_numCols];
                for (int j = 0; j < m_numCols; j++){
                    m_card[i][j] = rhs.m_card[i][j];
                }
            }

            m_trackRows = new int[m_numRows];
            for (int i = 0; i < m_numRows; i++){
                m_trackRows[i] = rhs.m_trackRows[i];
            }

            m_trackCols = new int[m_numCols];
            for (int i = 0; i < m_numCols; i++){
                m_trackCols[i] = rhs.m_trackCols[i];
            }

            m_helper = new Cell[m_helperSize];
            for (int i = 0; i < m_helperSize; i++){
                m_helper[i] = rhs.m_helper[i];
            }
        }

    }
    
    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";    
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
}
