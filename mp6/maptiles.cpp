/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> & theTiles)
{
    /**
     * @todo Implement this function!
     */
    // Make sure we have a valid state
    if (theTiles.empty())
        return NULL;

    // Create the map from Point to TileImage.
    map<HSLAPixel, int> tile_avg_map;
    vector<Point<3>> points;
    points.reserve(theTiles.size());
    for (unsigned int i = 0; i < theTiles.size(); ++i) {
        HSLAPixel avg = theTiles[i].getAverageColor();
        avg.h /= 360;
        tile_avg_map[avg] = i;
        Point<3> mapPt(avg.h, avg.s, avg.l);
        points.push_back(mapPt);
    }

    // Create the data structure
    KDTree<3> tree(points);

    // Initialize canvas
    int rows = theSource.getRows();
    int columns = theSource.getColumns();

    MosaicCanvas* mosaic = new MosaicCanvas(rows, columns);

    // Finally, fill tiles
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            TileImage* matchTile = get_match_at_idx(
                tree, tile_avg_map, theTiles, theSource, row, col);
            mosaic->setTile(row, col, *&matchTile);
        }
    }

    return mosaic;
}

TileImage* get_match_at_idx( KDTree<3>& tree,
                                  const map<HSLAPixel, int> & tile_avg_map,
                                   vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> color(avg.h / 360, avg.s, avg.l);
    Point<3> nearestColor = tree.findNearestNeighbor(color);
    HSLAPixel nearestRGBA(nearestColor[0], nearestColor[1], nearestColor[2]);
    map<HSLAPixel, int>::const_iterator it = tile_avg_map.find(nearestRGBA);
    if (it == tile_avg_map.end())
    {
        cerr << "Didn't find " << nearestRGBA << " / " << nearestColor << endl;
        // if this happens, don't want to segfault by returning null
        // (although this case should be impossible anyways)
        return &theTiles[0];
    }
    int index = it->second;
    return &theTiles[index];
}
