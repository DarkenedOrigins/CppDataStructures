#include <iostream>

void up(int &puzzle[4][4]){
	int row,col;
	for(row=0;row<3;row++){
		for(col=0;col<4;col++){
			if(puzzle[row][col] == puzzle[row+1][col] || puzzle[row][col] == 0){
				puzzle[row][col] += puzzle[row+1][col];
				puzzle[row+1][col] = 0;
			}
		}
	}
}

void left(int &puzzle[4][4]){
	return;
}

void right(int &puzzle[4][4]){
	return;
}

void down(int &puzzle[4][4]){
	return;
}

void run2048(int puzzle[4][4], int dir) {

    // your code here
	switch(dir){
		case 0:
			left(puzzle);
			break;
		case 1:
			up(puzzle);
			break;
		case 2:
			right(puzzle);
			break;
		case 3:
			down(puzzle);
			break;
		default:
			std::cout<<"bad input"<<std::endl;
			break;
	}
	return;
}
