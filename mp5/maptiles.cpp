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
  vector<Point<3>> color;
  vector< TileImage >::iterator it;
  map<Point<3>, TileImage> Map;

  for (size_t i = 0; i < theTiles.size(); i++)
    {
        HSLAPixel pixel = theTiles.at(i).getAverageColor();
        Point<3> pp(pixel.h, pixel.s, pixel.l, pixel.a);

        Map[pp] = theTiles.at(i);
        color.push_back(pp);
    }
    KDTree<3>::KDTree tree(color);

   int rows = theSource.getRows();
   int cols = theSource.getColumns();
   MosaicCanvas::MosaicCanvas *canvas = new MosaicCanvas(rows, cols);

   //loop through each tile
   for (int i = 0; i < rows; i++)
   {
       for (int j = 0; j < cols; j++)
       {
           HSLAPixel region = theSource.getRegionColor(i, j);
           Point<3> regionPoint(region.h, region.s, region.l, region.a);
           Point<3> closest = tree.findNearestNeighbor(regionPoint);
           TileImage Tile = Map[closest];

           canvas->setTile(i, j, Tile);
       }
   }

   //return canvas
   return canvas;
}
