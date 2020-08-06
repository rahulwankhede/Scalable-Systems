#include "IMatrix.h"
#include <iostream>
#include <cfloat>
#include <math.h>

using namespace std;

class ArrayMatrix: public IMatrix
{
	private:
        unsigned int rows;
        unsigned int cols;
        bool init_flag;             // Whether matrix has already been initialized
        unsigned int append_count;  // No. of rows appended so far;
        unsigned int nnz;           // No. of non-zero entries in the matrix

        float** mat;                // Pointer to the first element of our matrix, which is an array of pointers

    public:


        // Constructor
        ArrayMatrix()
        {
            init_flag = false;
            append_count = 0;
            nnz = 0;
        }

		// Destructor
		~ArrayMatrix()
		{
			for(int i = 0; i < cols; i++)
			{
				delete[] mat[i];
			}
			delete[] mat;
		}


        // Initializer
        void init(int N, int M)
        {

            if (!init_flag)                     // If not already initialized
            {
                rows = N; cols = M;
                mat = new float*[N];
                for(int i = 0; i < N; i++)
                {
                    mat[i] = new float[M];
                    for(int j = 0; j < M; j++)
                    {
                        mat[i][j] = 0;
                    }
                }
                init_flag = true;               // Array should not be initialized again
            }
            else
            {
                throw logic_error{"Array has already been initialized."};
            }
        }


        // Append row of float values to matrix at last unappended row
        void append (float* row_vals)
        {
            // if appended row_count() rows already
            if (append_count == row_count())
            {
                throw out_of_range{"Array is full"};
            }
            else
            {
                for(int i = 0; i < col_count(); ++i)
                {
                    float v = row_vals[i];
                    mat[append_count][i] = v;               // Assuming row_vals is a pointer to exactly M float values. Since we cannot get the size of the array from just its pointer
                    nnz += (fabs(v) <  FLT_MIN ? 0 : 1);    // Comparing with zero
                }
                append_count += 1;
            }
        }


        // Get element at index (i,j)
        float get(int i, int j)
        {
            if (i < 0 || i >= append_count || j < 0 || j >=col_count())
            {
                throw out_of_range{"Index out of bounds"};
            }
            return mat[i][j];
        }


        // No. of rows
        int row_count()
        {
            return rows;
        }


        // No. of columns
        int col_count()
        {
            return cols;
        }


        // No. of non-zero entries
        int nnz_count()
        {
            return nnz;
        }
};



class CSRMatrix: public IMatrix
{
	private:
        unsigned int rows;
        unsigned int cols;
        bool init_flag;
        unsigned int append_count;
        unsigned int nnz;
        unsigned int a_size;      // Size of A and IA = a_size * cols

        float * A;
        int * IA;
        int * JA;

	public:


        // Constructor
        CSRMatrix()
        {
            init_flag = false;
            append_count = 0;
            nnz = 0;
            a_size = 1;
        }

		// Destructor
		~CSRMatrix()
		{
			delete[] A;
			delete[] IA;
			delete[] JA;
		}


        // Initializer
        void init(int N, int M)
        {

            if(!init_flag)
            {
                rows = N; cols = M;

                A = new float[a_size * cols];
                IA = new int[N+1];
                JA = new int[a_size * cols];

                IA[0] = 0;

                init_flag = true;
            }
			else
			{
				throw logic_error{"Array has already been initialized"};
			}
        }


        // Append row of floats to matrix
        void append (float* row_vals)
        {
            if(append_count == row_count())
            {
                throw out_of_range{"Array is full"};
            }
            else
            {
                int count = 0;										// no. of non-zero elements in the row row_vals

                for(int i = 0; i < cols; ++i)						// iterate over row_vals
                {
                     float v = row_vals[i];
                     if (fabs(v) > FLT_MIN)							// check if nonzero
                     {
                         A[nnz] = v;
                         JA[nnz] = i;
                         nnz++;
                         count++;

						 // a_size is initialized to 1. size of A = a_size * columns
                         if(nnz == a_size * cols)									// if nonzero elements = size of A, that is, A is full
                         {
                             a_size *= 2;
                             float * A2 = new float[a_size * cols];						// A2 = twice the size of A
                             int * JA2 = new int[a_size * cols];

                             memcpy(A2, A, nnz * sizeof(float));					// copy A into A2
                             memcpy(JA2, JA, nnz * sizeof(int));

							 cout << "Here, a_size = " << a_size << endl;			// Printing for debugging purpose. Printing twice

                             delete[] A;

							 cout << "Here1" << endl;								// Printing for debugging purpose. Printing twice


							 delete[] JA;											// ***THIS IS WHERE THE ERROR IS OCCURING***
							 														// [munmap_chunk(): invalid pointer
																					// Aborted (core dumped)]


							 cout << "Here2" << endl;								// Printing for debugging purpose. Printing only once


                             A = A2; JA = JA2;										// Making A point to new array of double size
                         }
                     }
                }
                append_count++;
                IA[append_count] = IA[append_count - 1] + count;
                cout << "IA[" << append_count << "] = " << IA[append_count] << endl;

            }
        }



        /** Override the get function defined in the IMatrix interface */
    float get(int i, int j)
	{
        if (i < 0 || i >= append_count || j < 0 || j >=col_count())
        {
            throw out_of_range{"Index out of bounds"};
        }

        for(int k = IA[i]; k < IA[i+1]; ++k)
        {
            cout << "k = " << k << endl;
            if(JA[k] > j)
            {
                return 0;
            }
            if(JA[k] == j)
            {
                return A[k];
            }
        }
    }

	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
        return rows;
	}

	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count()
	{
        return cols;
	}


	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
        return nnz;
	}


	/*#######################################################
	 # Optionally define any other private utility functions here
	 #######################################################*/

	// TODO


};
