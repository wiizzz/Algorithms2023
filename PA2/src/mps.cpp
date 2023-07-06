#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

vector<vector<int> > tables;
vector<vector<int> > chords;
vector<vector<int> > cases;
vector<pair<int, int> > lines;

int MPS(int start, int end){
    if(start == end)
      return  tables[start][end] = 0; //  i == j
    else if(tables[start][end] == -1){
        int k = max(chords[0][end], chords[1][end]);    //  k:= the points that forms chord with point j
        if(k == start){
                tables[start][end] = (1 + MPS(start+1, end-1) );
                cases[start][end] = 3;  //  case 3: k == i
        }
        else if(k > start && k <= end-1 ){
            if(MPS(start, k-1) + MPS(k+1, end-1) + 1 > MPS(start, end-1)){
              tables[start][end] =  (MPS(start, k-1) +  MPS(k+1, end-1) + 1);
              cases[start][end] = 2;  //  case2: i < k <= j-1
            }
            else{
                tables[start][end] = MPS(start, end-1);
                cases[start][end] = 4;  //case4: j not in optimal sol.
            }
        }
        else if(k < start || k > end){
            tables[start][end] =  MPS(start, end-1);
            cases[start][end] = 1;  //  case1: k > j || k < i
        }
    }
    return tables[start][end] ;
}

void find_line(int i, int j, int &index){
    if(cases[i][j] == 1)
        find_line(i, j-1, index);
    else{
        int k = max(chords[0][j], chords[1][j]);
        if(cases[i][j] == 2){
            lines[index].first = k;
            lines[index].second = j;
            index++;
            find_line(i, k-1, index);
            find_line(k+1, j-1, index);
        }
        else if(cases[i][j] == 3){
            lines[index].first = i;
            lines[index].second = j;
            index++;
            find_line(i+1, j-1, index);
        }
        else if(cases[i][j] == 4)
           find_line(i, j-1, index);
    }
}

int main(int argc, char *argv[]){
    int num;
    ifstream infile;
    ofstream outfile;

    infile.open(argv[1]);
    outfile.open(argv[2]);
    infile >> num;

    cases.resize(num, vector<int>(num, 0));   // n x n table
    tables.resize(num, vector<int>(num, -1));   // n x n table
    chords.resize(2, vector<int>(num, -1));      // 2 x num vector

    while(true){
        int start, end;
        infile >> start >> end;
        if(infile.eof())
            break;
        if(start > end)
            swap(start, end);
        chords[0][start] = end;
        chords[1][end] = start;
    }

    int index = 0;
    int N = MPS(0, num-1);
    tables.shrink_to_fit(); //free vector memory

    outfile << N << endl;
    lines.resize(N);

    find_line(0, num-1, index);
    sort(lines.begin(), lines.end());

    for(const auto &i: lines)
        outfile << i.first << " " << i.second << endl;

    infile.close();
    outfile.close();
    return 0;
}