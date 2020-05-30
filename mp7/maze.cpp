/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze(){
	Vertices = 0;
	width =0;
	height=0;
	adjList.resize(1);
	tiles.resize(1);
}
int SquareMaze::validMovement(int x, int y, int dir) const{
	int index; //to convert 2d index to 1d its row*width+column in this case y*width+x x==cols, y==rows
	switch(dir){
		case 0:
			index = (y)*width+x+1;
			if(x==width-1){
				index = -1; //this is for the right edge where a right movement will go to the left most square on the lower row
			}
			break;
		case 1:
			index = (y+1)*width+x;
			break;
		case 2:
			index = (y)*width+x-1;
			if(x==0){
				index = -1; //this is for the left edge case where the left movement will go to end of the upper row
			}
			break;
		case 3:
			index = (y-1)*width+x;
			break;
		default:
			index = y*width+x;
	}
	if(index>=0 && index<Vertices){
		return index;
	}else{
		return -1;
	}
}
void SquareMaze::addEdge(int Vertex1, int Vertex2){
	adjList[Vertex1].push_back(Vertex2);
	adjList[Vertex2].push_back(Vertex1);
}
void SquareMaze::removeEdge(int Vertex1, int Vertex2){
	adjList[Vertex1].erase(std::find(adjList[Vertex1].begin(), adjList[Vertex1].end(),Vertex2));
	adjList[Vertex2].erase(std::find(adjList[Vertex2].begin(), adjList[Vertex2].end(), Vertex1));
}
void SquareMaze::makeMaze(int width, int height){
	this->width = width;
	this->height = height;
	Vertices = width*height;
	adjList.resize(Vertices);
	tiles.resize(Vertices);
	for(Tile w : tiles){
		w.visited = false;
	}
	DisjointSets set;
	set.addelements(Vertices);
	int numberOfUnions = 0;
	for(int row=0;row<height;row++){
		for(int col=0;col<width;col++){
			int CurrIndex = validMovement(col,row,5);//the 5 is to trigger default and give curr idx
			int index = -1;
			while(1){
				index = -1;
				if(numberOfUnions == Vertices-1){
					break;
				}
				while(index == -1){
					index = validMovement(col,row,rand()%2);
				}
				if(set.find(CurrIndex) != set.find(index)){
					addEdge(CurrIndex, index);
					set.setunion(CurrIndex, index);
					numberOfUnions++;
					break;
				}
			}
		}
	}
}
bool SquareMaze::canTravel(int x, int y, int dir)const{
	int CurIdx = validMovement(x,y,5);
	int DestIdx = validMovement(x,y,dir);
	if(DestIdx == -1 || CurIdx == -1){
		return false;
	}
	if(std::find(adjList[CurIdx].begin(), adjList[CurIdx].end(), DestIdx) != adjList[CurIdx].end() ){
		return true;
	}else{
		return false;
	}
}
void SquareMaze::setWall(int x, int y, int dir, bool exists){
	if(exists){
		if(canTravel(x,y,dir)){
			removeEdge(validMovement(x,y,5),validMovement(x,y,dir));
		}
	}else{
		if(!canTravel(x,y,dir)){
			addEdge(validMovement(x,y,5), validMovement(x,y,dir));
		}
	}
}
std::vector<int> SquareMaze::solveMaze(){
	std::queue<int> q;
	int v = 0;
	tiles[v].parent = -1;
	tiles[v].distance = 0;
	tiles[v].visited = true;
	q.push(v);
	while(!q.empty()){
		v = q.front();
		q.pop();
		for( int w : adjList[v] ){
			if(!tiles[w].visited){
				tiles[w].parent = v;
				tiles[w].distance = tiles[v].distance+1;
				tiles[w].visited = true;
				q.push(w);
			}
		}
	}
	std::vector<int> retvec;
	int distance=0;
	int vertex;
	for(int i = validMovement(0,height-1,5); i<(int)tiles.size(); i++){//finds the largest distance in bottom row
		if(tiles[i].distance > distance){
			distance = tiles[i].distance;
			vertex = i;
		}
	}
	int parent = tiles[vertex].parent;
	while(parent != -1){
		retvec.push_back(move(parent,vertex));
		vertex = parent;
		parent = tiles[vertex].parent;
	}
	std::reverse(retvec.begin(), retvec.end());
	return retvec;

}
int SquareMaze::move(int SrcVertex, int DesVertex){
	if(SrcVertex == DesVertex){
		return 5;
	}
	if(SrcVertex == DesVertex-1){
		return 0;
	}
	if(SrcVertex+width == DesVertex){
		return 1;
	}
	if(SrcVertex-1 == DesVertex){
		return 2;
	}
	if(SrcVertex-width == DesVertex){
		return 3;
	}
	return -1;
}
PNG* SquareMaze::drawMaze() const{
	PNG* pic = new PNG(width*10+1, height*10+1);
	int ImgWidth = (int)pic->width();
	int ImgHeight = (int)pic->height();
	HSLAPixel* pixel;
	for(int y=0; y<ImgHeight; y++){ //this blacks out the left and right edges
		pixel = pic->getPixel(0,y);
		pixel->h = 0;
		pixel->s = 0;
		pixel->l = 0;
		pixel->a = 1;
		/*pixel = getPixel(ImgWidth, y);
		pixel->h = 0;
		pixel->s = 0;
		pixel->l = 0;
		pixel->a = 1;*/

	}
	for(int x=10; x<ImgWidth; x++){
		pixel = pic->getPixel(x,0);
		pixel->h = 0;
		pixel->s = 0;
		pixel->l = 0;
		pixel->a = 1;
	}
	for(int y=0;y<height;y++){
		for(int x=0;x<width;x++){
			if(!canTravel(x,y,0)){
				for(int k=0;k<=10;k++){
					pixel = pic->getPixel((x+1)*10, y*10+k);
					pixel->h = 0;
					pixel->s = 0;
					pixel->l = 0;
					pixel->a = 1;
				}
			}
			if(!canTravel(x,y,1)){
				for(int k=0;k<=10;k++){
					pixel = pic->getPixel(x*10+k, (y+1)*10);
					pixel->h = 0;
					pixel->s = 0;
					pixel->l = 0;
					pixel->a = 1;
				}
			}
		}
	}
	return pic;
}
PNG* SquareMaze::drawMazeWithSolution(){
	PNG* pic = drawMaze();
	std::vector<int> moves = solveMaze();
	int x=5;
	int y=5;
	for(int elem : moves){
		for(int i=0;i<10;i++){
			switch(elem){
				case 0:
					ColorRed(pic->getPixel(x++,y));
					break;
				case 1:
					ColorRed(pic->getPixel(x,y++));
					break;
				case 2:
					ColorRed(pic->getPixel(x--,y));
					break;
				case 3:
					ColorRed(pic->getPixel(x,y--));
					break;

			}
		}
	}
	ColorRed(pic->getPixel(x,y));
	x -=4;
	for(int k=0;k<9;k++){
		HSLAPixel* pixel = pic->getPixel(x+k,height*10);
		pixel->h=0;
		pixel->s=0;
		pixel->l=1;
		pixel->a=1;
	}
	return pic;
}
void SquareMaze::ColorRed(HSLAPixel* pixel){
	pixel->h = 0;
	pixel->s = 1;
	pixel->l = .5;
	pixel->a = 1;
	return;
}
/*int i;
		switch(elem){
			case 0: 
				for(i=x;i<=x+11;i++){
					ColorRed(pic->getPixel(i,y));
				}
				x = i+1;
				break;
			case 1:
				for(i=y; i<=y+11;i++){
					ColorRed(pic->getPixel(x,i));
				}
				y = i+1;
				break;
			case 2:
				for(i=x;i>=x-11;i--){
					ColorRed(pic->getPixel(i,y));
				}
				x=i-1;
				break;
			case 3:
				for(i=y;i>=y-11;i--){
					ColorRed(pic->getPixel(x,i));
				}
				y=i-1;
				break;
		}
 */
