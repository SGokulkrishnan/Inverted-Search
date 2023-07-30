#include "invertedIndex.h"

//function to display the Data base
int display_DB(wlist_t **head)
{
	int index,flag2 = 1;
	for(index=0;index<26;index++)
	{
		int flag1 = 1;
		wlist_t *temp = head[index];
		while( temp != NULL )
		{
			//if it is first time print index
			if(flag1)
			{
				flag1 = 0;
				flag2 = 0;
				printf(BLU "[%d]\t",index);
			}
			else
				printf("\t");
			//print the values
			printf(GRN"[%s]\t"RED"%d  "COLOR_RESET"file(s)",temp->word,temp->f_count);
			file_table_t *table = temp->t_link;

			//print the table values
			while(table)
			{
				printf(" : file : "GRN"%s"RED"%5d"COLOR_RESET"   time(s)",table->f_name,table->w_count);
				table=table->link;
			}
			printf("-> NULL\n");
			temp=temp->link;
		}
	}
	if(flag2)
		return FAILURE;
	else 
		return SUCCESS;
}
