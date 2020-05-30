/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
	vector< Point<3> > colors;
	map<Point<3>, TileImage> dictionary;
	//this for loop goes through each tile mapping its avg color to a point with hsl as the dims
	for(auto TilesIt = theTiles.begin(); TilesIt < theTiles.end(); TilesIt++){
		HSLAPixel pixel = (*TilesIt).getAverageColor();
		Point<3> point(pixel.h/360.0, pixel.s, pixel.l);
		dictionary[point] = *TilesIt;
		colors.push_back(point);
	}
	KDTree<3>::KDTree tree(colors); //create kdtree from found points
	int rows = theSource.getRows();
	int cols = theSource.getColumns();
	MosaicCanvas::MosaicCanvas *canvas = new MosaicCanvas(rows, cols);
	//this for loop goes through the source image pixel by pixel finding its nearest neighbor
	//this neighbor is then used to find a tile to replace it with
	//this tile is placed in the canvas
	for(int r=0; r<rows; r++){
		for(int c=0; c<cols; c++){
			HSLAPixel RegionColor = theSource.getRegionColor(r,c);
			Point<3> R_point(RegionColor.h/360.0,RegionColor.s, RegionColor.l);
			Point<3> NearestNeighbor = tree.findNearestNeighbor(R_point);
			TileImage tile = dictionary[NearestNeighbor];
			canvas->setTile(r,c,tile);
		}
	}
	return canvas;
}

