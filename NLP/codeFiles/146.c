#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
//Making it easier to understand. All for you guys <3
enum retval_enum{INIT_ERROR_VALUES, INIT_ERROR_MEMORY, RUN_ERROR_BOUNDARIES, ENDLOOP_MISSING, STARTLOOP_MISSING, FINISHED};
 
//The function to execute the Brainf*** code
enum retval_enum runCode(char *code, int cellnum);
 
 
int main(int argc, char **argv)
{
	printf("Running code\n\n");
 
	//Run some code to test. I think this is a Hello World program. The code can be read from a file or whatever else is wanted
 
	unsigned int stat = runCode(",----------[++++++++++>,----------]<[.<]+++++++++++++.---.", 1000);
	printf("\n\nDone running code\n");
	switch(stat)
	{
		case INIT_ERROR_VALUES:
			printf("Error initializing values.\n");
			//Some jerk set the number of cells to 0
			break;
 
		case INIT_ERROR_MEMORY:
			printf("Not enough memory.\n");
			//Not enough memory to allocate an array of chars with length cellnum
			break;
 
		case RUN_ERROR_BOUNDARIES:
			printf("Boundary error in BF prog\n");
			//Whilst running, the cell iterator got below 0 or over cellnum. ie. not enough cells
			break;
 
		case STARTLOOP_MISSING:
			printf("Error in code. Start loop missing\n");
			//An endloop was found without a startloop
			break;
 
		case ENDLOOP_MISSING:
			printf("Error in code. End loop missing\n");
			//A Startloop was found without an endloop
			break;
 
		case FINISHED:
			printf("Finished with no problems\n");
			//Code finished without any probs
			break;
	};
 
	return 0;
}
 
enum retval_enum runCode(char *code, int cellnum)
{
	//Returns with enum on failure
	if(cellnum==0)
		return INIT_ERROR_VALUES;
 
	//Allocate memory for cells
	unsigned char *p_cells = 0;
	p_cells = (unsigned char*) malloc(cellnum);
	if(p_cells == 0)
			return INIT_ERROR_MEMORY;
 
	int cell_iter = 0;
	int code_len = strlen(code);
	int code_iter = 0;
 
	//iter is changed according to code
	while(code_iter < code_len)
	{
		switch(code[code_iter])
		{
			case '+':
				//Just increase. If it overflows, it'll become 0
				p_cells[cell_iter]++;
				break;
 
			case '-':
				//"Underflowing" will cause it to be max(int)
				p_cells[cell_iter]--;
				break;
 
			case '>':
				//Move pointer and check boundaries
				cell_iter++;
				if(cell_iter == cellnum)
				{
					free(p_cells);
					return RUN_ERROR_BOUNDARIES;
				}
				break;
 
			case '<':
				//Move pointer and check boundaries
				cell_iter--;
				if(cell_iter<0)
				{
					free(p_cells);
					return RUN_ERROR_BOUNDARIES;
				}
				break;
 
			case '.':
				//Output current cell
				putchar(p_cells[cell_iter]);
				break;
 
			case ',':
				//Grab 1 char input
				p_cells[cell_iter]=getchar();
				break;
 
			case '[':
				//If current cell is 0, run to the next ']'
				if(p_cells[cell_iter]==0)
					while(code[code_iter]!=']')
					{
						code_iter++;
						if(code_iter>=code_len)
						{
							free(p_cells);
							return ENDLOOP_MISSING;
						}
					}
				break;
 
			case ']':
				//Run all the way back before the last '['
				while(code[code_iter]!='[')
				{
					code_iter--;
					if(code_iter<0)
					{
						free(p_cells);
						return STARTLOOP_MISSING;
					}
				}
				code_iter--;
				break;
 
			default:
				//It's not a relevant char, ignore it.
				break;
		};
		code_iter++;
	};
 
	//Just clean up
	free(p_cells);
 
	//We are done. Give an awesome goodness signal back!
	return FINISHED;
}
