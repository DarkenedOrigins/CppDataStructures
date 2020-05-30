/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true) {
	tokens_ = startingTokens;
	string player1 = "p1-";
	string player2 = "p2-";
	bool firstVertex = true;
	for(int i=startingTokens;i>=0;i--){
		if(firstVertex){
			startingVertex_ = g_.insertVertex(player1+std::to_string(i));
			firstVertex = false;
		}else{
		g_.insertVertex(player1+std::to_string(i));
		}
		g_.insertVertex(player2+std::to_string(i));
	}
	for(int i=startingTokens; i>1; i--){
		Vertex p1cur = g_.getVertexByLabel(player1+std::to_string(i));
		Vertex p2cur = g_.getVertexByLabel(player2+std::to_string(i));
		Vertex p1_take1 = g_.getVertexByLabel(player2+std::to_string(i-1));
		Vertex p1_take2 = g_.getVertexByLabel(player2+std::to_string(i-2));
		Vertex p2_take1 = g_.getVertexByLabel(player1+std::to_string(i-1));
		Vertex p2_take2 = g_.getVertexByLabel(player1+std::to_string(i-2));
		g_.insertEdge(p1cur, p1_take1);
		g_.setEdgeWeight(p1cur, p1_take1, 0);
		g_.insertEdge(p1cur, p1_take2);
		g_.setEdgeWeight(p1cur, p1_take2, 0);
		g_.insertEdge(p2cur, p2_take1);
		g_.setEdgeWeight(p2cur, p2_take1, 0);
		g_.insertEdge(p2cur, p2_take2);
		g_.setEdgeWeight(p2cur, p2_take2, 0);
	}
	g_.insertEdge(g_.getVertexByLabel(player1+std::to_string(1)), g_.getVertexByLabel(player2+std::to_string(0)));
	g_.setEdgeWeight(g_.getVertexByLabel(player1+std::to_string(1)), g_.getVertexByLabel(player2+std::to_string(0)),0);
	g_.insertEdge(g_.getVertexByLabel(player2+std::to_string(1)), g_.getVertexByLabel(player1+std::to_string(0)));
	g_.setEdgeWeight(g_.getVertexByLabel(player2+std::to_string(1)), g_.getVertexByLabel(player1+std::to_string(0)),0);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  int tokens = tokens_;
  string player1 = "p1-";
  string player2 = "p2-";
  bool player1turn = true;
  while(tokens != 0 && tokens != 1){
	int choice = rand()%2+1;
	if(player1turn){
		path.push_back(g_.getEdge(g_.getVertexByLabel(player1+std::to_string(tokens)), g_.getVertexByLabel(player2+std::to_string(tokens-choice))));
		player1turn = false;
	}else{
		path.push_back(g_.getEdge(g_.getVertexByLabel(player2+std::to_string(tokens)), g_.getVertexByLabel(player1+std::to_string(tokens-choice))));
		player1turn = true;
	}
	tokens -= choice;
  }
  if(tokens == 1){
	  if(player1turn){
		  path.push_back(g_.getEdge(g_.getVertexByLabel(player1+std::to_string(1)), g_.getVertexByLabel(player2+std::to_string(0))));
	  }else{
		  path.push_back(g_.getEdge(g_.getVertexByLabel(player2+std::to_string(1)), g_.getVertexByLabel(player1+std::to_string(0))));
	  }
  }
  return path;
}


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
	for(auto it=path.rbegin(); it != path.rend(); it++){
		g_.setEdgeWeight(it->source, it->dest, it->weight+1);
		it++;
		if(it == path.rend()){
			break;
		}
		g_.setEdgeWeight(it->source, it->dest, it->weight-1);
	}
}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
