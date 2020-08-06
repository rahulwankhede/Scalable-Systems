#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX_LINE_SIZE 1000
#define MAX_INT_SIZE 10
#define MAX_FLT_SIZE 25

using namespace std;


void read_ints(char* line, int &n, int& m, char delim='\t'){
    char* ptr = line;
    char n_char[MAX_INT_SIZE], m_char[MAX_INT_SIZE];
    int i = 0, j = 0;

    while(*ptr != delim){
        n_char[i++] = *ptr++;
    }
    n_char[i++] = '\0'; *ptr++;
    n = stoi(n_char);
    
    while(*ptr != '\0'){
        m_char[j++] = *ptr++;
    }
    m_char[j++] = '\0';
    m = stoi(m_char);
}

void read_row(char* line, float* flt_row, int M, char delim='\t'){
    float val;
    int i; int j = 0;
    char* ptr = line;
    char flt_char[MAX_FLT_SIZE];

    while(j < M - 1){
        i = 0;
        while(*ptr != delim){
            flt_char[i++] = *ptr++;
        }
        flt_char[i++] = '\0'; *ptr++;
        val = stof(flt_char);
        flt_row[j] = val;
        j++;
    }
    i = 0;
    while(*ptr){
        flt_char[i++] = *ptr++;
    }
    flt_char[i++] = '\0';
    val = stof(flt_char);
    if (j == M-1){
        flt_row[j] = val;
    }
    else{
        throw logic_error{"No. of elements read is not equal to the matrix column size"};
    }
}



int main(){
    fstream fs{"tsv_file.tsv", ios_base::in};
    char line[MAX_LINE_SIZE];
    fs.getline(line, MAX_LINE_SIZE);
    int N, M;
    read_ints(line, N, M);
    fs.getline(line, MAX_LINE_SIZE);
    float fltr[M];
    //cout << line << endl;
    read_row(line, fltr, M);
    for (int i = 0; i < M; i++){
        cout << fixed << setprecision(3) << fltr[i] << " ";
    }
    cout << endl;
    fs.close();
    return 0;
}
