/**
  * This virtual class defines the functions that will be supported 
  * by the abstract 2D matrix data structure.
  *
  * DO NOT CHANGE THIS CLASS!
  */
class IBinTree
{
	public:
    
	/**
	  * This inserts an item with the given key and value into the binary tree
	  */
    virtual void insert (int, float)=0; 
	
	/**
	  * This returns the value associated with the given key. 
	  * If the key is not found, you must return FLT_MAX.
	  */
    virtual float find(int)=0; 

	/**
	  * This returns the number of items that have been inserted into the tree.
	  */
	virtual int count()=0;
	
};

