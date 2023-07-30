#include "invertedIndex.h"

int main(int argc, char *argv[])
{
	//arg count must be 1 else return FAILURE
	if (argc == 1)
	{
		printf("\n\033[0;31mError : Invalid no.of arguments\nUsage ./inverted_index <file.txt> <file1.txt> ...\033[0m\n\n");
		return FAILURE;
	}

	file_node_t *fhead = NULL,*temp;
	for(int i=1;i<argc;i++)
	{
		validate_n_store_filenames(&fhead, argv[i]);
	}
	//Checking all the files are valid
	if (fhead == NULL)
	{
		printf("\n\033[0;31mNo files are valid\nPlease pass the valid files\033[0m\n\n");
		return FAILURE;
	}

	wlist_t *HT_head[26] = {NULL};

	while(1)
	{
		//Display the menu to user
		printf(BLU "1. Create DB\n2. Display DB\n3. Search DB\n4. Update DB\n5. Save DB\n\033[0;31mPlease enter your choise : "COLOR_RESET);
		int opt;
		//Read the choice from user.
		scanf(" %d",&opt);
		switch(opt)
		{
			case 1:
				//case Create Database
				{
					if(count == 0 && create_DB(fhead,HT_head)==SUCCESS)
						count++;
					else 
						printf(RED"Files passed through commandline already added into the Database\n"COLOR_RESET);
				}
				break;
			case 2:
				//case for Display Database
				if(display_DB(HT_head)== FAILURE)
				{
					printf(RED"Database is empty\n"COLOR_RESET);
				}
				break;
			case 3:
				//case for Search Database
				{
					printf(BLU "Enter the word to be searched in Database : ");
					char word[BUFF_SIZE];
					scanf(" %s",word);
					int status = search_DB(HT_head,word);
					if(status==FAILURE)
					{
						printf(RED"Error: word %s is not found in the data base\n"COLOR_RESET,word);
					}
					else if(status == EMPTYLIST)
					{
						printf(RED"Database is empty\n"COLOR_RESET);
					}
					break;
				}
			case 4:
				//case for update Database
				{
					printf(BLU "Enter the file name : "COLOR_RESET);
					char file[BUFF_SIZE];
					scanf(" %s",file);
					update_DB(&fhead, HT_head, file);
					break;
				}
			case 5:
				//case for Backup the Database
				{
					printf(BLU "Enter the back up file name: "COLOR_RESET);
					char file[BUFF_SIZE];
					scanf(" %s",file);
					save_DB(HT_head, file);
					break;
				}
			default:
				//dafault case
				printf(RED"Enter valid option!!!\n"COLOR_RESET);
				continue;
		}
		printf("Do you want to continue(y/Y) ? ");
		char ch;
		scanf(" %c",&ch);
		if(ch== 'y' || ch == 'Y')
			continue;
		else 
			break;
	}

}

//case for validate store filename
int validate_n_store_filenames(file_node_t **fhead, char *filenames)
{
	int status;
	//function call to validate file valid or not
	status = IsFileValid(filenames);

	//if satus is NOT_PRESENT print error message
	if (status == NOT_PRESENT)	
	{
		printf(RED"Error: %s is not exist\nSo we are not adding to the list\n"COLOR_RESET, filenames);
		return FAILURE;
	}

	//if status is FILE_EMPTY than print error message
	else if(status == FILE_EMPTY)
	{
		printf(RED"Error: %s is an empty file\nSo we are not adding to the list\n"COLOR_RESET, filenames);
		return FILE_EMPTY;
	}

	//is status is ture han call stoe file name to list
	else
	{
		if(store_filenames_to_list(filenames, fhead) == SUCCESS)
		{
			printf(GRN"Successfull: %s is added to the list\n"COLOR_RESET, filenames);
			return SUCCESS;
		}
		else
		{
			printf(RED"Error: %s is repeated\nSo we are not adding to the list\n"COLOR_RESET, filenames);
			return FAILURE;
		}
	}
}

//function to create node
file_node_t *create_node(char *fname)
{
	file_node_t *new = malloc(sizeof(file_node_t));
	if (new == NULL)
		return NULL;
	//Node created then update filename and link
	strcpy(new -> f_name, fname);
	new -> link = NULL;

	return new;
}

//funciotn to store filename to list
int store_filenames_to_list(char *f_name, file_node_t **head)
{
	//if file node is empty than craete new node
	if (*head == NULL)
	{
		*head  = create_node(f_name);
		return SUCCESS;
	}

	//finc last node and update new node adress
	file_node_t *temp = *head,*prev;
	while (temp != NULL)
	{
		//if file name is found return repeted
		if (strcmp(temp -> f_name, f_name))
		{
			prev = temp;
			temp = temp -> link;
		}
		else
			return REPEATED;
	}
	prev -> link = create_node(f_name);
	return SUCCESS;
}

//function to validate file
int IsFileValid(char *filename)
{
	// Check the file is exist or not
	// 1. Not exist, return NOT_PRESENT
	FILE *fp=fopen(filename,"r");
	if(fp==NULL)
		return NOT_PRESENT; 

	//If file file is exist, then check file is empty or not
	// 1. If file is empty, then return FILE_EMPTY
	fseek(fp,0,SEEK_END);
	int size = ftell(fp);
	if(size<=0)
		return FILE_EMPTY;

	// if file present and not empty then return SUCCESS
	return SUCCESS;
}












