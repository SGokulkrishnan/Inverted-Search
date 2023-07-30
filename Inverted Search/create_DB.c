#include "invertedIndex.h"

//function for create Database
int create_DB(file_node_t *file_head, wlist_t **head)
{
	while(file_head)
	{
		//function call to read date from file
		read_datafile(head,file_head->f_name);

		//update file name
		file_head=file_head->link;
	}
	return SUCCESS;
}

//function for read datafile
void read_datafile(wlist_t **head,char *f_name)
{
	//open file
	FILE *fp = fopen(f_name,"r");	
	char word[BUFF_SIZE];

	//read word by word from file
	while((fscanf(fp,"%s",word))!=EOF){

		int index,flag = 1;

		//find lower or upper case alphabet
		if('a'<=word[0] && 'z'>=word[0] )
		{
			index = word[0] % 97;
		}
		else
			index = word[0] % 65;

		//if head is not empty 
		if(head[index]!=NULL)
		{
			wlist_t *temp=head[index];
			while(temp)
			{
				//if same word is already present update count
				if(strcmp(temp->word, word))
				{
					temp=temp->link;
				}
				else 
				{
					flag = 0;
					update_word_count(&temp, f_name);
					break;
				}
			}
		}
		//else call the function to insert data
		if(flag)
			insert_at_last_main(&head[index], word, f_name);
	}
	printf(GRN"Successful: creation of database for %s\n"COLOR_RESET, f_name);
}

//function to update wordcount
int update_word_count(wlist_t **head, char *f_name)
{
	file_table_t *temp = (*head) ->t_link,*prev;
	while(temp)
	{
		//if the file name is already presnt increment word count
		if(strcmp(temp->f_name,f_name))
		{
			prev=temp;
			temp = temp->link;
		}
		else
		{
			(temp->w_count)++;
			return SUCCESS;
		}

	}
	//else create new node and update values
	file_table_t *new = malloc(sizeof(file_table_t));
	strcpy(new->f_name,f_name);
	(*head)->f_count++;
	new->w_count = 1;
	new->link=NULL;
	prev->link=new;
	return SUCCESS;
}

//function for insert at last 
int insert_at_last_main(wlist_t **head, char *word, char *f_name)
{
	//create new node
	wlist_t *new= malloc(sizeof(wlist_t));
	if(new==NULL)
	{
		return FAILURE;
	}
	new->f_count=1;
	strcpy(new->word,word);
	new->link=NULL;

	//function call to update link
	update_link_table(&new,f_name);

	//if list is empty update new into head 
	if(*head==NULL)
	{
		*head=new;
		return SUCCESS;
	}

	//if list is not empty find last node and update new node link
	wlist_t *temp=*head;
	while(temp->link!=NULL)
	{
		temp=temp->link;
	}	
	temp->link=new;
	return SUCCESS;
}

//function to update link table
int update_link_table(wlist_t **word_node, char *f_name)
{
	//create new node
	file_table_t *new = malloc(sizeof(file_table_t));
	if(new==NULL)
		return FAILURE;
	new->w_count = 1;
	strcpy(new->f_name,f_name);
	new->link = NULL;

	(*word_node)->t_link = new;

	return SUCCESS;
}
