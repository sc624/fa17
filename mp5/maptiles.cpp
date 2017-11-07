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
  int rows = theSource.getRows();
	int columns = theSource.getColumns();
	MosaicCanvas * finalMosaic = new MosaicCanvas(rows, columns);
	vector <Point<3> > pixelVector;
	map <Point<3>, int> indexMap;
	for(size_t i = 0; i < theTiles.size(); i++)
	{
		HSLAPixel tempPixel = theTiles[i].getAverageColor();
		double setPoint [3];
		setPoint [0]= tempPixel.h;
		setPoint [1]= tempPixel.s;
		setPoint [2]= tempPixel.l;
		Point <3> tempPoint(setPoint);
		pixelVector.push_back(tempPoint);
	}
	for(size_t i = 0; i < pixelVector.size(); i++)
	{
		indexMap[pixelVector[i]] = i;
	}
	KDTree <3> sourceTree(pixelVector);

	for(int rowNumber = 0; rowNumber < rows; rowNumber++)
	{
		for(int columnNumber = 0; columnNumber < columns; columnNumber++)
		{
			HSLAPixel originalPixel = theSource.getRegionColor(rowNumber, columnNumber);
			double pixelArray [3];
			pixelArray [0]= originalPixel.h;
			pixelArray [1]= originalPixel.s;
			pixelArray [2]= originalPixel.l;
			Point <3> singlePixel(pixelArray);
			Point <3> properImage = sourceTree.findNearestNeighbor(singlePixel);
			int findIndex = indexMap[properImage];
			TileImage findImage = theTiles[findIndex];
			finalMosaic->setTile(rowNumber, columnNumber, findImage);
		}
	}

	return finalMosaic;
}
