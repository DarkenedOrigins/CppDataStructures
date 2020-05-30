/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage*> const& theTiles)
{
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    vector<Point<3>> points;
    map<Point<3>, TileImage*> TileDict;
    Point<3> AvgPoint;
    HSLAPixel avg;
    for (TileImage* image: theTiles) {
      avg = image->getAverageColor();
      AvgPoint = Point<3>(avg.h/360.0, avg.s, avg.l);
      points.push_back(AvgPoint);
      TileDict[AvgPoint] = image;
    }
    KDTree<3> tree(points);
    Point<3> ClosestAvgPoint;
    MosaicCanvas* canvas = new MosaicCanvas(rows, columns);
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            avg = theSource.getRegionColor(i, j);
            AvgPoint = Point<3>(avg.h/360.0, avg.s, avg.l);
            ClosestAvgPoint = tree.findNearestNeighbor(AvgPoint);
            canvas->setTile(i, j, TileDict[ClosestAvgPoint]);
        }
    }
    return canvas;
}
