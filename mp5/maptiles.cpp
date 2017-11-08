#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
  int rows = theSource.getRows();
  int columns = theSource.getColumns();
//cout<<"reach 19"<<endl;
MosaicCanvas * finalMosaic = new MosaicCanvas(rows, columns);
vector <Point<3> > pixelVector;
map <Point<3>, int> indexMap;
//cout<<"reach 22"<<endl;
for(size_t i = 0; i < theTiles.size(); i++)
{
  HSLAPixel pi = theTiles[i].getAverageColor();
          Point<3> po(pi.h, pi.s, pi.l);

          //map it
          indexMap[po] = theTiles[i];

          //put in vector
          pixelVector.push_back(po);
}

for (int i = 0; i < r; i++)
{
    for (int j = 0; j < c; j++)
    {
        //for each tile:
        //grab the pixel from source
        RGBAPixel regionColor = theSource.getRegionColor(i, j);
        //find the closest average color from kdtree using NNS
        Point<3> regionPoint(regionColor.red, regionColor.green, regionColor.blue);
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
