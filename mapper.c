// Sai Bhargav Mandavilli
// University of Florida

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining tuple structure
struct tuples
{
    int userID;
    char action;
    char topic[15];
};

int main(int argc, char *argv[])
{
	int i=0, j=0, count=0;
	char *str_p, c;
	char tuple_str[1500], token[15];

	// calculating number of tuples in input
	while ((c = getc(stdin)) != EOF) 
	{
		if (c == ')') 
	    		count++;
	}

	// set file offset to beginning of file
	fseek(stdin, 0, SEEK_SET);

	int s_userID[count];
	char s_action[count];
	struct tuples tuple[count];

	fgets(tuple_str, 1500, stdin);
	// break file string into tokens using ',' character
	str_p = strtok(&tuple_str[1], ",");

	while (str_p != NULL) 
	{
		// convert string into integer userID
		tuple[i].userID = atoi(str_p);
		s_userID[j] = tuple[i].userID;

		// split again to get action character
		str_p = strtok(NULL, ",");
		tuple[i].action = *str_p;
		s_action[j] = tuple[i].action;

		// split again to get topic
		str_p = strtok(NULL, ")");
		strcpy(tuple[i].topic, str_p);

		// moving to the next tuple
		str_p = strtok(NULL, "(");
		
		if (str_p) 
	    		str_p = strtok(NULL, ",");
		i++;
		j++;
	}

	// converting action to score
	for (j=0; j<=count; j++) 
	{
		if (s_action[j] == 'P') 
	    		s_action[j] = 50;

		else if (s_action[j] == 'L') 
		    s_action[j] = 20;
		
		else if (s_action[j] == 'D') 
	    		s_action[j] = -10;
			
		else if (s_action[j] == 'C') 
	    		s_action[j] = 30;
		
		else if (s_action[j] == 'S') 
	    		s_action[j] = 40;

		tuple[j].action = s_action[j];
	}

	// printing tuple in the output file
	for (j=0; j<count; j++) 
	{
	printf("(%.4d,%.15s,%d)\n", tuple[j].userID, tuple[j].topic, tuple[j].action);
	}

	return 0;
}
