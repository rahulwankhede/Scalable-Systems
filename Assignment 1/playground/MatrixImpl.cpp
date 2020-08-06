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
        bool init_flag;
        unsigned int append_count;
        float** mat; //Pointer to the first element of our matrix, which is an array of pointers

    public:
        ArrayMatrix()
        {
            append_count = 0;
            init_flag = false;
            mat = new float*; // sizeof float**;
        }

        void init (int N, int M)
        {
            if (!init_flag)
            {
                mat = new float*[N];
                for(int i = 0; i < N; i++)
                {
                    mat[i] = new float[M];
                    for(int j = 0; j < M; j++)
                    {
                        mat[i][j] = 0;
                    }
                }
                init_flag = true;
            }
            else
            {
                throw logic_error{"Array has already been initialized."};
            }
        }
        
        void append (float* row_vals)
        {
            if (append_count == rows)
            {
                throw out_of_range{"Array is full"};
            }
            else
            {
                mat[append_count] = row_vals;
            }
        }
        
        float get(int i, int j)
        {
            if (i < 0 || i >= append_count || j < 0 || j >=cols)
            {
                throw out_of_range{"Index out of bounds"};
            }
            return mat[i][j];
        }
        
        int row_count()
        {
            return rows;
        }
        
        int col_count()
        {
            return cols;
        }
        
        int nnz_count()
        {
            int count = 0;
            for(int i = 0; i < append_count; ++i)
            {
                for(int j = 0; j < cols; ++j)
                {
                    if (fabs(mat[i][j]) < FLT_MIN)
                    {
                        count++;
                    }
                }
            }
            return append_count*cols - count;
        }
};


class CSRMatrix: public IMatrix
{  	

	/*#######################################################
	 # Define your own data structures here 
	 #######################################################*/

	private: 
		// TODO
   
	public:
		// TODO
   
   
	/**
     * Default constructor is required.
	 * You may optionally define additional constructors as well.
     */
	CSRMatrix()
	{ 
		// TODO: Provide implementation for default constructor
	}
 
 
	/*#######################################################
 	  # Override functions defined in IMatrix interface
	  #######################################################*/

	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
		// TODO: Provide implementation for init using csr
	}
	

	/** Override the append function defined in the IMatrix interface */
   void append (float* row_vals)
	{ 
	    // TODO: Provide implementation for append using csr
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    // TODO: Provide implementation for get using csr
	}

	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
		// TODO: Provide implementation using csr
	}
	
	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count() 
	{
		// TODO: Provide implementation using csr
	}

	
	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
		// TODO: Provide implementation using csr
	}

	
	/*#######################################################
	 # Optionally define any other private utility functions here
	 #######################################################*/
	
	// TODO

	
};
