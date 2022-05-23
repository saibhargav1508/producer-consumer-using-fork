// Sai Bhargav Mandavilli
// University of Florida

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tuples
{
    int userID[5];
    char topic[15];
    int score;
};

int temp_score, length = 0;
char *ip, *symb, *temp_userID[5], *temp_topic[15];

// function takes userID, topic and score of tuple and updates the score if userID and topic matches
int scan_tuple (struct tuples *tuple, char *temp_userID, char *temp_topic, int temp_score, int length)
{
	if (length == 0)
    {
        // copy userID, topic and score from first tuple
		strcpy(tuple[length].userID, temp_userID);
        strcpy(tuple[length].topic, temp_topic);
        tuple[length].score = temp_score;
		
		// increment length to scan from next element in the next iteration
        length = length + 1;
        return length;
    }
	
    else
    {
        // check if previous iteration ID and the current ID are same		
        if (strcmp(tuple[length-1].userID, temp_userID) == 0) 
        {
			// check all the remaining tuples for matching topic
            for (int i=0; i<length; i++) 
			{
                if (strcmp(tuple[i].topic, temp_topic) == 0) 
				{
                    // update the score if matching topic is found
					tuple[i].score = tuple[i].score + temp_score;
                    return length;
                }
            }
			
            strcpy(tuple[length].userID, temp_userID);
            strcpy(tuple[length].topic, temp_topic);
            tuple[length].score = temp_score;
			
            length = length + 1;
            return length;
        }
	
		
		else
		{
            for(int i=0; i<length; i++)
				printf("(%s,%s,%d)\n", tuple[i].userID, tuple[i].topic, tuple[i].score);
           
			// set length to zero to restart operation the next time
            length = 0;
			
            strcpy(tuple[length].userID, temp_userID);
            strcpy(tuple[length].topic, temp_topic);
            tuple[length].score = temp_score;
			
            length = length + 1;
            return length;
        }
    }
}

int main()
{
    struct tuples tuple[100];
    
	
	int i=0, j=0;
    ip = (char*) malloc (2000);


	while(fgets(ip, 2000, stdin))
	{
        // store the first userID
		symb = strtok(&ip[1], ",");
        strcpy(temp_userID, symb);

        // store the first topic
		symb = strtok(NULL, ",");
        strcpy(temp_topic, symb);

        // store the first score of that tuple after converting it to an integer
		symb = atoi(strtok(NULL, ")"));
        temp_score = symb;

		// call scan_tuple to search and update score in the entire file - inner loop
		length = scan_tuple(tuple, temp_userID, temp_topic, temp_score, length);
	
	}
    // print reducer output on the console - which contains userID, topic and total score
	for(j=0; j<length; j++)
		printf("(%s,%s,%d)\n", tuple[j].userID, tuple[j].topic, tuple[j].score);
    
    return 0;
}
