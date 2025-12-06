#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

void read_print() {
    ifstream input("input.txt");
    string line;
    while (getline(input, line)) {
        cout << line << endl;
    }

    input.close();
}

void read_output() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string line;
    while (getline(input, line)) {
        output << line << endl;
    }

    input.close();
    output.close();
}

class Table {
public:
    int N, M;
    int width = 10;
    vector<vector<int>> a;

    void read(const std::string& filename) {
        ifstream input(filename);
        input >> N >> M;
        a.resize(N, vector<int>(M));
        char comma;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                input >> a[i][j];
                if (j < M - 1){
                    input >> comma;
                }
            }
        }
    }

    void print(int width=10) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < width - to_string(a[i][j]).length(); k++){ 
                    cout << " ";
                }
                cout << a[i][j];
                if (j < M - 1) cout << ' ';
            }
            cout << '\n';
        }
    }
};

int main() {
    read_print();
    read_output();
    Table t;
    t.read("input_table.txt");
    t.print();
}