#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <string>

/**
VWAPer v0.1

// Read file in with the following format:
// [Stock],[Interval],[Volume Traded],[High],[Low]

// Calculate the total volume traded per Stock
// Calculate the total volume traded per Stock&Interval

// Write the total volume traded per Stock&Interval as a percentage of the total volume traded per Stock to stdout:
// [Stock],[Interval],[%Volume Traded]

// Write the delimiter '#' to stdout

// Write the maximum High and minimum Low for each Stock to stdout:
// [Stock],[Day High],[Day Low]

// example input:
VOD.L 1 100 184 183.7
BT.LN 1 300 449.4 448.2
VOD.L 2 25 184.1 182.4
BT.LN 2 900 449.8 449.5

// example output:
VOD.L,1,80
BT.LN,1,25
VOD.L,2,20
BT.LN,2,75
#
VOD.L,184.1,182.4
BT.LN,449.8,448.2

**/

#define DELIMITER "#"

using namespace std;


class	CUpperLower
{
private:        // priivate members
    int nCurLwr;
    int nCurUpr;

public:
    CUpperLower() : nCurLwr(0), nCurUpr(0) {};

    // public function to get and set values of 'nCurLwr' and 'nCurUpr'
    int getnCurLwr() { return nCurLwr; }
    void setnCurLwr(int i) { nCurLwr = i; }

    int getnCurUpr() { return nCurUpr; }
    void setnCurUpr(int j) { nCurUpr = j; }


    void add(int nHigh, int nLow)
    {
        if (nHigh > nCurUpr)
            nCurUpr = nHigh;

        if (nLow < nCurLwr)
            nCurLwr = nLow;
    }

    int getSum()    // no returning a reference to a local variable
    {
        int sum = nCurLwr + nCurUpr;
        return sum;
    }
};


int main(int argc, char* argv[])
{
    // check array length before dereferencing
    if (argc <= 1) {
        cout << "Not Enough Arguments\n";
        return 1;
    }

    if (!strcmp("version", argv[1]))
    {
        cerr << "VWAPer version 0.1\n";
        return 0;
    }

    FILE* file = fopen(argv[2], "r");

    cout << "Reading file" << argv[2] << "\n";

    // vector data structures
    vector <int> Intervals, Volumes;
    vector <float> Highs, Lows;
    // vector <char> line;
    // vector < vector<char>> Stocks;
    char line[256];
    char Stocks[1000][10];

    int         i = 0;

    while (fgets(line, 256, file))
    {
        sscanf(line, "%s %d %d %f %f",
               Stocks[i], &Intervals[i],
               &Volumes[i], &Highs[i], &Lows[i]);
        ++i;    // Guarantees that 'i' is incremented.
    }

    cout << "Calculating total volumes\n";

    map<string, int>TotalVolumes;

    for (int s = 0; s < i; ++s)    // changed 's <= i' to 's < i'
    {
        string stockname = Stocks[s];

        for (int j =0; j < i; ++j)     // changed 'j <= i' to 'j < i
        {
            if (!strcmp(Stocks[j], stockname.c_str()))
            {
                TotalVolumes[stockname] += Volumes[j];
            }
        }
    }

    cout << "Calculating high lows\n";

    map<string, CUpperLower>HighLows;

    for (int s = 0; s <= i; ++s)
    {
        HighLows[Stocks[s]].add(Highs[s], Lows[s]);
        cout << HighLows[Stocks[s]].getSum();
    }

    cout << "Writing files" << "\n";

    for (int s = 0; s <= i; ++s)
    {
        cout << Stocks[s] << "," << Intervals[s] << "," <<
                TotalVolumes[Stocks[s]] / Volumes[s] * 100 << "\n";
    }

    cout << DELIMITER << "\n";

    map<string, CUpperLower>::iterator itr = HighLows.begin();
    while (itr != HighLows.end())
    {
        cout << (*itr).first << "," << (*itr).second.getnCurLwr() << "," <<
                (*itr).second.getnCurUpr() << "\n";

        ++itr;
    }

    return 0;
}

/*
1. Since 'using namespace std' is included at the beginning of the program, therefore 'std' has been
    removed within the program.

2. 'typedef basic_string<char> string' removed since it redefines a standard name.

3. Removed the unused variable 'sum = 0'.

4. 'cerr' changed to 'cout' if not reporting error.

5. Check array length before dereferencing in 'FILE* file = fopen(argv[2], "r")' as line will fail if
    user does not give arguments.

5. arrays changed to vectors as this improves memory expansion when need compared to arrays 
    which have limited memory allocation.

4. code ends with 'return 1' which will be interpreted as an indication that an error was
    encountered, therfore the convention is to 'return 0'.
*/
