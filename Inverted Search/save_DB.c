#include "invertedIndex.h"

//fucntion to dave Database
int save_DB(wlist_t **head, char *fname)
{
	FILE *fp = fopen(fname,"w");
	int index;
	for(index=0;index<24;index++)
	{
		//if head is not empty
		if(head[index]!=NULL)
		{
			wlist_t *temp = head[index];
			while(temp!=NULL)
			{
				//take backup from node to data file
				fprintf(fp,"#%d;\n%s:%d;",index,temp->word,temp->f_count);
				file_table_t *table = temp->t_link;
				//take a backup from table list
				while(table!=NULL)
				{
					fprintf(fp,"%s;%d;",table->f_name,table->w_count);
					table=table->link;
				}
				fprintf(fp,"#\n");
				temp=temp->link;
			}
		}
	}
}
