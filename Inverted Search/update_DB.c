#include "invertedIndex.h"

//function to update Database
int update_DB(file_node_t **fhead, wlist_t **HT_head,char * file)
{
	//function to call validate and store filenames
	if(validate_n_store_filenames(fhead, file)==SUCCESS)
	{
		//function call to read datafile
		read_datafile( HT_head ,file);
		return SUCCESS;
	}
	return FAILURE;
}
