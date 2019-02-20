#include <stdio.h>

#define TRUE	1
#define FALSE	0

void getCanPlaceNumber();
int setNumber();

int main(void){
	
	/*Sudoku Data*/
	int sudoku[][9] =	{
							{5,0,0,4,0,1,0,6,9},
							{0,0,0,0,0,3,5,0,0},
							{6,0,0,0,2,0,0,0,0},
							{0,0,0,0,0,4,0,0,8},
							{0,0,0,0,0,0,7,0,6},
							{3,0,9,0,7,5,0,0,0},
							{0,0,0,0,0,0,0,4,0},
							{2,1,4,0,0,0,9,0,7},
							{0,8,0,0,0,0,0,0,0}
						};
	
	/*Question*/
	puts("Question:");
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			printf("%d ",sudoku[i][j]);
		}
		putchar('\n');
	}
	
	/*Solve*/
	if(setNumber(sudoku, 0, 0))
		puts("Complete!");
	else
		puts("Failed");
	
	/*Answer*/
	puts("Answer:");
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			printf("%d ",sudoku[i][j]);
		}
		putchar('\n');
	}
	return 0;
}

/*
	checking number can put.
*/
void getCanPlaceNumber(int sudoku[][9], int pn[9], int line, int column){
	int i,j;
	for(i = 0; i < 9; i++) pn[i] = 1;
	
	/*line-number search*/
	for(i = 0; i < 9; i++)
		if(sudoku[line][i] != 0)
			pn[sudoku[line][i]-1] = 0;

	/*column-number search*/
	for(i = 0; i < 9; i++)
		if(sudoku[i][column] != 0)
			pn[sudoku[i][column]-1] = 0;
			
	/*3x3 block-number search*/
	for(i = line / 3 * 3; i < (line / 3 * 3) + 3; i++)
		for(j = column / 3 * 3; j < (column / 3 * 3) + 3; j++)
			if(sudoku[i][j] != 0)
				pn[sudoku[i][j]-1] = 0;
}

/*
	set number
*/
int setNumber(int sudoku[][9], int line, int column){
	if(sudoku[line][column] == 0){
		int pn[9];
		getCanPlaceNumber(sudoku, pn, line, column);
		for(int i = 0; i < 9; i++){
			if(pn[i]){
				sudoku[line][column] = i + 1;
				if(line == 8 && column == 8)
					return TRUE;
				else if(setNumber(sudoku, (column + 1 == 9 ? line + 1 : line), (column + 1 == 9 ? 0 : column + 1)))	//check next position
					return TRUE;
			}
		}
		//if number can place wasn't exist, re-answer previous position.
		sudoku[line][column] = 0;
		return FALSE;
	}else{
		if(line == 8 && column == 8)
			return TRUE;
		else if(setNumber(sudoku, (column + 1 == 9 ? line + 1 : line), (column + 1 == 9 ? 0 : column + 1)))
			return TRUE;
		return FALSE;
	}
}