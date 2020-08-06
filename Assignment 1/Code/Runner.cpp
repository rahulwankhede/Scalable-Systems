#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include "MatrixImpl.cpp"
#include <fstream>
#include <sstream>
#include <chrono>

#define MAX_INT_SIZE 10             // size in chars of the maximum length of an int
#define MAX_FLT_SIZE 50             // size in chars of the maximum length of a float
#define MAX_LINE_SIZE 2000          // size in chars of the maximum length of a line in a file

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Helper Declarations////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


void read_ints(char* line, int &n, int& m, char delim='\t');            // Function to read integers from first line (size of matrix) into n, m
void read_row(char* line, float* flt_row, int M, char delim='\t');      // Function to read a row of M floats separated by delim from line into flt_row
float get_elem(int p, int q, IMatrix* mat1, IMatrix* mat2);             // Function to get element at position (p,q) of mat1 * mat2
float * row_append(int row_no, IMatrix* mat1, IMatrix* mat2);           // Function to get the (row_no)'th row that is to be appended to  mat1 * mat2


/////////////////////////////////////////////////////////////////////////////////////////////



// Array Loader
IMatrix* load_arr(char* input_file)
{
    fstream fs{input_file, ios_base::in};           // stream to input file
    char line[MAX_LINE_SIZE];                       // placeholder to read a line into
    fs.getline(line, MAX_LINE_SIZE);

    int N, M;
    read_ints(line, N, M);


    IMatrix* arr_mat = new ArrayMatrix();         // matrix to load into
    arr_mat->init(N, M);

    for(int i = 0; i < N; i++)
    {
        char * line = new char[MAX_LINE_SIZE];
        fs.getline(line, MAX_LINE_SIZE);
        float * fltrow = new float[M];              // fltrow = pointer to row that is to be appended
        read_row(line, fltrow, M);

        arr_mat->append(fltrow);

        delete[] fltrow;
        delete[] line;
    }

    fs.close();                                     // close file

    return arr_mat;
}


// CSR Loader
IMatrix* load_csr(char* input_file)
{
    fstream fs{input_file, ios_base::in};
    char line[MAX_LINE_SIZE];
    fs.getline(line, MAX_LINE_SIZE);

    int N, M;
    read_ints(line, N, M);


    IMatrix * csr_mat = new CSRMatrix();
    csr_mat->init(N, M);



    for(int i = 0; i < N; ++i)
    {
        char * line = new char[MAX_LINE_SIZE]; // Can you do it faster by not using dynamic memory?
        fs.getline(line, MAX_LINE_SIZE);
        float * fltrow = new float[M];
        read_row(line, fltrow, M);


        csr_mat->append(fltrow);

        delete[] fltrow;
        delete[] line;
    }

    fs.close();

    return csr_mat;
}



// Array Initializer
IMatrix* init_arr(int rows, int cols)
{
    ArrayMatrix * arr_mat = new ArrayMatrix();
    arr_mat->init(rows, cols);
    return arr_mat;
}



// CSR Initializer
IMatrix* init_csr(int rows, int cols)
{
    CSRMatrix * csr_mat = new CSRMatrix();
    csr_mat->init(rows,cols);
    return csr_mat;
}



// Print matrix to tsv file
void print_mat(IMatrix* mat, char* output_file)
{
    int r = mat->row_count();
    int c = mat->col_count();

    fstream fst{};                                         // stream to write file into
    cout << "Here5" << endl;
    fst.open(output_file, ios_base::out);                   // ERROR: DO SOMETHING
    cout << "Here6" << endl;
    if (fst.is_open())
    {
        fst << to_string(r) << '\t' << to_string(c) << '\n';                         // write dimensions of matrix on first line
        for(int i = 0; i < r; ++i)
        {

            int j = 0;

            while(j < c-1)
            {
                float val = mat->get(i,j);
                fst << fixed << setprecision(3) << val <<  '\t';                     // write c-1 entries separated by tab to line
                ++j;
            }

            if(j == c-1)
            {
                fst << fixed << setprecision(3) << mat->get(i,j) << '\n';            // write last (c)th entry followed by newline if previous entries successfully written
            }
            else
            {
                cout << "Problem writing row no." << i << ". Columns != M" << endl;
            }
        }
    }
    else
    {
        cout << "Could not open output file to print to" << endl;
        return;
    }

    fst.close();                                                                     // close file
}



// Load matrix from input_file to a matrix representation and print that representation to output_file
void load(char* mat_type, char* input_file, char* output_file)
{
	IMatrix* mat1;

	if (strcmp("array", mat_type)==0) // TODO: time this region and print "load,array,output_file,time_millisec"
    {
        auto start = chrono::high_resolution_clock::now();

        mat1 = load_arr(input_file);

        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        cout << "load, " <<  mat_type << ", " << output_file << ", " <<  elapsed.count() * 1000 << " milliseconds" << endl;

    }
	else if (strcmp("csr", mat_type)==0) // TODO: time this region and print "load,csr,output_file,time_millisec"
	{

        auto start = chrono::high_resolution_clock::now();

        mat1 = load_csr(input_file);

        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        cout << "load, " <<  mat_type << ", " << output_file << ", " <<  elapsed.count() * 1000 << " milliseconds" << endl;

	}
	else
		cout << "[load] invalid matrix type input seen: " << mat_type << endl;

	// store the loaded matrix mat1 in output file given by output_file
	print_mat(mat1, output_file);

    delete mat1;

	return;
}



// Transpose mat1 and save into mat2
void transpose(IMatrix* mat1, IMatrix* mat2)
{
    int N = mat1->row_count();
    int M = mat1->col_count();
    for(int i = 0; i < M; ++i)
    {


        float * newrow = new float[N];
        for(int j = 0; j < N; ++j)
        {
            newrow[j] = mat1->get(j,i);
        }
        cout <<"i = "<< i <<": Newrow[3] = " << newrow[3] << endl;
        mat2->append(newrow);
        delete newrow;

        cout << "Here1" << endl;

    }

    cout << mat2->get(3,3) << endl;

    cout << "Here2" << endl;

	return;
}



void transpose(char* mat_type, char* input_file, char* output_file)
{
	// TODO: any other validation?

	IMatrix * mat1, * mat2;

	if (strcmp("array", mat_type)==0)
    {
		mat1 = load_arr(input_file);

		// TODO: any other validation?

		mat2 = init_arr(mat1->col_count(), mat1->row_count());
    }
	else if (strcmp("csr", mat_type)==0)
	{


		mat1 = load_csr(input_file);

		// TODO: any other validation?

		mat2 = init_csr(mat1->col_count(), mat1->row_count());


	}
	else {
		cout << "[transpose] invalid matrix type input seen: " << mat_type << endl;
		return;
	}

	// TODO: time this method and print "transpose,mat_type,output_file,time_millisec"
    auto start = chrono::high_resolution_clock::now();


    transpose (mat1, mat2);

    cout << "Here3" << endl;

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "transpose, " << mat_type << ", " << output_file << ", " << elapsed.count() * 1000 << " milliseconds" << endl;


	cout << "Here4" << endl;

    // store output matrix mat2 in file given by output_file
	print_mat(mat2, output_file);

	return;
}
/////////////////////////////////////////////////////////////////////////////

void multiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3)
{
    for(int i = 0; i < mat1->row_count(); ++i){
        float * row_app = row_append(i, mat1, mat2);
        mat3->append(row_app);
    }

	// TODO: Code for multiplying the mat1 and mat2 and storing in a third matrix mat3

	return;
}


void multiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	// TODO: any other validation?

	IMatrix * mat1, * mat2, * mat3;

	if (strcmp("array", mat_type)==0)
    {
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

        if (mat1->col_count() != mat2->row_count()){
            throw logic_error{"Can't multiply matrices. Incompatible dimensions"};
        }
		// TODO: any other validation?
		mat3 = init_arr(mat1->row_count(), mat2->col_count());
		// TODO: init output matrix mat3 with arr impl
	}
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

        if (mat1->col_count() != mat2->row_count()){
            throw logic_error{"Can't multiply matrices. Incompatible dimensions"};
        }

		// TODO: any other validation?
		mat3 = init_csr(mat1->row_count(), mat2->col_count());
		// TODO: init output matrix mat3 with csr impl
	}
	else {
		cout <<"[multiply] invalid matrix type input seen: " << mat_type << endl;
		return;
	}

	// TODO: time this method and print "multiply,mat_type,output_file,time_millisec"
    auto start = chrono::high_resolution_clock::now();

    multiply(mat1, mat2, mat3);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "multiply, " << mat_type << ", " << output_file << ", " << elapsed.count() * 1000 << " milliseconds" << endl;

	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}


////////////////////////////////////////////////////////////////////////////

void bmultiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3)
{

	// TODO: Code for multiplying using block matrix multiplication
	// the matrices mat1 and mat2 and storing in a third matrix mat3

	return;
}


void bmultiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	// TODO: any other validation?

	IMatrix * mat1, * mat2, * mat3;

	if (strcmp("array", mat_type)==0)
    {
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

		// TODO: any other validation?

		// TODO: init output matrix mat3 with arr impl
	}
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

		// TODO: any other validation?

		// TODO: init output matrix mat3 with csr impl
	}
	else {
		cout << "[bmultiply] invalid matrix type input seen: " << mat_type << endl;
		return;
	}

	// TODO: time this method and print "bmultiply,mat_type,output_file,time_millisec"
	bmultiply(mat1, mat2, mat3);

	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}

/////////////////////////////////////////////////////////////////////////////

// Helper functions
//
//

void read_ints(char* line, int &n, int& m, char delim){
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


void read_row(char* line, float* flt_row, int M, char delim){
    float val;
    int i; int j = 0;
    char* ptr = line;
    char flt_char[MAX_FLT_SIZE];


    while(j < M - 1){
        i = 0;
        while(*ptr != delim){
            flt_char[i++] = *ptr++;
        }
        flt_char[i++] = '\0'; ptr++;
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

float get_elem(int p, int q, IMatrix* mat1, IMatrix* mat2){
    float val = 0;
    for(int i = 0; i < mat1->col_count(); ++i){
        val += mat1->get(p, i) * mat2->get(i, q);
    }
    return val;
}

float * row_append(int row_no, IMatrix* mat1, IMatrix* mat2){
    int size = mat2->col_count();
    float * row_app = new float[size];
    for (int i = 0; i < size; ++i){
        row_app[i] = get_elem(row_no, i, mat1, mat2);
    }
    return row_app;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int main(int n, char *argv[])
{

	if(strcmp("load", argv[1])==0)
	{
		load(argv[2], argv[3], argv[4]);
	}
    else if(strcmp("transpose", argv[1])==0)
	{
		transpose(argv[2], argv[3], argv[4]);
	}
    else if(strcmp("multiply", argv[1])==0 )
	{
        multiply(argv[2], argv[3], argv[4], argv[5]);
	}
    else if(strcmp("bmultiply", argv[1])==0)
	{
        bmultiply(argv[2], argv[3], argv[4],argv[5]);
	} else
		cout << "[main] invalid input parameters. Valid usage is..." << endl;

	return 0;
}
