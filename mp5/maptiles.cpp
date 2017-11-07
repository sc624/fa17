#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    vector< Point<3> > colors;
     vector< TileImage >::iterator it;

     //Build a map between average color and the tile that would generate the average color
     map<Point<3>, TileImage> theMap;

     //Loop through the tiles
     //for (it = theTiles.begin(); it != theTiles.end(); it++)
     for (size_t i = 0; i < theTiles.size(); i++)
     {
         //get average color
         HSLAPixel pi = theTiles.at(i).getAverageColor();
         Point<3> po(pi.h, pi.s, pi.l, pi.a);

         //map it
         theMap[po] = theTiles.at(i);

         //put in vector
         colors.push_back(po);
     }

     //Call kdtree constructor
     KDTree<3>::KDTree tree(colors);

     //Start building the canvas
     //Declare a new canvas
     int r = theSource.getRows();
     int c = theSource.getColumns();
     MosaicCanvas::MosaicCanvas *canvas = new MosaicCanvas(r, c);

     //loop through each tile
     for (int i = 0; i < r; i++)
     {
         for (int j = 0; j < c; j++)
         {
             //for each tile:
             //grab the pixel from source
             HSLAPixel regionColor = theSource.getRegionColor(i, j);
             //find the closest average color from kdtree using NNS
             Point<3> regionPoint(regionColor.h, regionColor.s, regionColor.l);
             Point<3> closestPoint = tree.findNearestNeighbor(regionPoint);
             //use the map to find the tile
             TileImage theTile = theMap[closestPoint];

             //put the tile onto canvas
             canvas->setTile(i,j,theTile);
         }
     }

     //return canvas
     return canvas;
}
