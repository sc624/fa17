#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
  /**
	 * @todo Implement this function!
	 */
   	MosaicCanvas* MosaicBinky = new MosaicCanvas(theSource.getRows(), theSource.getColumns());


	vector<Point<3>> treePoints;
	treePoints.reserve(theTiles.size());

	/* create map representing HSLAPixel and
	 * their corresponding TileImages
	 */
	map<Point<3>, TileImage> tiles;

	/* populate vector as well as map the
	 * points in the vector to their  TileImages.
	 */
	for (size_t i = 0; i < theTiles.size(); i++)
	{
		Point<3> p;
		p[0] = (theTiles[i].getAverageColor()).h/360.0;
		p[1] = (theTiles[i].getAverageColor()).s;
		p[2] = (theTiles[i].getAverageColor()).l;
		treePoints.push_back(p);

		pair<Point<3>, TileImage> element(p, theTiles[i]);
		tiles.insert(element);
	}

	/* create KDTree */
	KDTree<3> image(treePoints);

	/*search each point in the source. use
	 * findNearestNeighbor on the KDTree and set the  point in the
	 * MosaicCanvas using the right tile image.
	 */
	for (int i = 0; i < theSource.getRows(); i++)
	{
		for (int j = 0; j < theSource.getColumns(); j++)
		{
			Point<3> search;
			search[0] = (theSource.getRegionColor(i, j)).h/360.0;
			search[1] = (theSource.getRegionColor(i, j)).s;
			search[2] = (theSource.getRegionColor(i, j)).l;

			Point<3> output = image.findNearestNeighbor(search);

			MosaicBinky->setTile(i, j, tiles[output]);
		}
	}
	return MosaicBinky;
}
