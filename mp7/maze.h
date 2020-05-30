/* Your code here! */
#ifndef _SQUARE_MAZE_
#define _SQUARE_MAZE_

#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include "dsets.h"
#include "./cs225/PNG.h"
using namespace cs225;

class SquareMaze{
	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		std::vector<int> solveMaze();
		PNG* drawMaze() const;
		PNG* drawMazeWithSolution();
	private:
		//x is columns and y is rows
		int validMovement(int x, int y, int dir) const; //returns 1D index in given direction else -1
		void addEdge(int Vertex1, int Vertex2); //adds edge to adjlist
		void removeEdge(int Vertex1, int Vertex2); //removes edges
		int move(int SrcVertex, int DesVertex);
		void ColorRed(HSLAPixel* pixel); //colors given pixel red a quality of life func
		int Vertices; //number of vertices in the 
		int width; //width of maze
		int height; //height of maze
		struct Tile{
			int parent;
			int distance;
			bool visited;
		};
		std::vector<std::list<int>> adjList; //jaceny list to have a list of  
		std::vector<Tile> tiles; 
};
#endif
