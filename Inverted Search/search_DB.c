#include "invertedIndex.h"

//function to search Database
int search_DB(wlist_t **head, char *word)
{
	int index;

	//if wlist is enpty reutrn EMPTYLIST
	if(*head == NULL)
	{
		return EMPTYLIST;
	}

	//fund word 1st letter lower or upper case alphabet or not
	if(word[0]>='a' && word[0] <='z')
		index = word[0]%97;
	else
		index = word[0]%65;

	wlist_t *temp = head[index];
	while( temp != NULL )
	{
		//if fiven word is found and Database print data
		if(strcmp(temp->word, word))
			temp=temp->link;
		else
		{
			printf(RED"Word"GRN " %s"RED" foud in the Database and it present in " BLU "%d " RED"file(s)\n"COLOR_RESET,word,temp->f_count);
			file_table_t *table = temp->t_link;
			while(table)
			{
				printf(RED"In file " GRN"%s " BLU "%d " RED"time(s)\n"COLOR_RESET,table->f_name,table->w_count);
				table=table->link;
			}
			return SUCCESS;
		}
	}
	return FAILURE;
}
