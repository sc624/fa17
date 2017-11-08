/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
	if(curDim < Dim && curDim >= 0)
	{
		if(first[curDim]!=second[curDim])
			return first[curDim] < second[curDim];
		else if(first[curDim]==second[curDim])
      return first < second;
	}
	return false;
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	double currDistance = 0, potenDistance = 0;
	for(int i = 0; i < Dim; i++)
		currDistance += (target[i]-currentBest[i])*(target[i]-currentBest[i]);
	for(int i = 0; i < Dim; i++)
		potenDistance += (target[i]-potential[i])*(target[i]-potential[i]);
	if(currDistance == potenDistance)
		return potential < currentBest;
	return potenDistance < currDistance;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	points = newPoints;
    KDTreeHelper(0, points.size()-1, 0);
}
//KDTree constructor helper that uses quickSelect to organize points
template<int Dim>
void KDTree<Dim>::KDTreeHelper(int leftidx, int rightidx, int dimension)
{
    int mindex;
    mindex = (leftidx + rightidx)/2;
    quickSelect(leftidx, rightidx, dimension, mindex);
    if(leftidx < mindex - 1)
        KDTreeHelper(leftidx, mindex - 1, (dimension + 1) % Dim);
    if(rightidx > mindex + 1)
        KDTreeHelper(mindex + 1, rightidx, (dimension + 1) % Dim);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{

		int middle = ((points.size()-1)/2);
    Point<Dim> currentBest = points[middle];
    NearestNeighborHelper(query, currentBest, 0, points.size() - 1, 0);

    return currentBest;
}

//helper function to findNearestNeighbor that checks distances between points and organizes;; first gets the middle and checks for leaf node
//passes in points recursively
template<int Dim>
Point<Dim> KDTree<Dim>::NearestNeighborHelper(const Point<Dim> & query, Point<Dim> & currentBest, int leftidx, int rightidx, int dimension) const
{
	if(leftidx > rightidx){

				currentBest = points[leftidx];
				return currentBest;
	}

	Point<Dim> leftTree = NearestNeighborHelper(query, currentBest, leftidx, ((leftidx + rightidx)/2)-1, (dimension + 1)%Dim);
 	Point<Dim> rightTree = NearestNeighborHelper(query, currentBest, ((leftidx + rightidx)/2)+1, rightidx, (dimension + 1)%Dim);
 	if(shouldReplace(query, currentBest, rightTree)){
		currentBest = rightTree;
 	}
 	else if(shouldReplace(query, currentBest, leftTree)){
		currentBest = leftTree;
 	}
 	else if(shouldReplace(query, currentBest, points[((leftidx + rightidx)/2)])){
	 	currentBest = points[((leftidx + rightidx)/2)];
 	}
 	return currentBest;
}

//quick select sort function
template<int Dim>
void KDTree<Dim>::quickSelect(int leftidx, int rightidx, int dimension, int mid_idx)
{
    if(leftidx > rightidx)
        return;
    int pivotIndex = (leftidx + rightidx)/2;
    pivotIndex = partition(leftidx, rightidx, pivotIndex, dimension);
    if(mid_idx == pivotIndex)
        return;
    else if(mid_idx > pivotIndex)
      quickSelect(pivotIndex + 1, rightidx, dimension, mid_idx);
    else
      quickSelect(leftidx, pivotIndex - 1, dimension, mid_idx);

}


//partition helper function needed to change partitions of dimension
template<int Dim>
int KDTree<Dim>::partition(int leftidx, int rightidx, int pivotidx, int dimension)
{
    Point<Dim> pivotVal = points[pivotidx];
    std::swap(points[rightidx], points[pivotidx]);
    int store = leftidx;
    for(int i = leftidx; i < rightidx; i++)
    {
        if(!smallerDimVal(pivotVal, points[i], dimension))
        {
            std::swap(points[i], points[store]);
            store++;
        }
    }
    std::swap(points[store], points[rightidx]);
    return store;
}
