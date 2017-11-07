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
	int currDistance = 0, potenDistance = 0;
	for(int i = 0; i < Dim; i++)
		currDistance += (target[i]-currentBest[i])*(target[i]-currentBest[i]);
	for(int i = 0; i < Dim; i++)
		potenDistance += (target[i]-potential[i])*(target[i]-potential[i]);
	if(currDistance != potenDistance)
		return potenDistance < currDistance;
	return potential < currentBest;
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

    bool check = true;
    Point<Dim> currentBest;
    NearestNeighborHelper(check, query, currentBest, 0, points.size() - 1, 0, 0);

    return currentBest;
}

//helper function to findNearestNeighbor that checks distances between points and organizes
template<int Dim>
void KDTree<Dim>::NearestNeighborHelper(bool & check, const Point<Dim> & query, Point<Dim> & currentBest, int leftidx, int rightidx, int dimension, int dist) const
{
	if(leftidx >= rightidx){
		if(check == true){
				check = false;
				currentBest = points[rightidx];
		}
		else{
				if(shouldReplace(query, currentBest, points[leftidx]) == true)
						currentBest = points[leftidx];
		}
		return;
}

 if(smallerDimVal(query, points[(leftidx + rightidx)/2], dimension) == false){
	NearestNeighborHelper(check, query, currentBest, (leftidx + rightidx)/2 + 1, rightidx, (dimension + 1) % Dim, dist);
	if(shouldReplace(query, currentBest, points[(leftidx + rightidx)/2])==true)
		currentBest = points[(leftidx + rightidx)/2];
	for(int i = 0; i < Dim; i++)
		dist = dist + (currentBest[i]-query[i])*(currentBest[i]-query[i]);
	if((points[(leftidx + rightidx)/2][dimension] - query[dimension]) * (points[(leftidx + rightidx)/2][dimension] - query[dimension]) <= dist)
		NearestNeighborHelper(check, query, currentBest, leftidx, (leftidx + rightidx)/2 - 1, (dimension + 1) % Dim, dist);
	}
else{
	NearestNeighborHelper(check, query, currentBest, leftidx, (leftidx + rightidx)/2 - 1, (dimension + 1)%Dim, dist);
	if(shouldReplace(query, currentBest, points[(leftidx + rightidx)/2])==true)
		currentBest = points[(leftidx + rightidx)/2];
	for(int i = 0; i < Dim; i++)
		dist = dist + (currentBest[i]-query[i])*(currentBest[i]-query[i]);
	if((points[(leftidx + rightidx)/2][dimension] - query[dimension]) * ( points[(leftidx + rightidx)/2][dimension] - query[dimension]) <= dist)
		NearestNeighborHelper(check, query, currentBest, (leftidx + rightidx)/2 + 1, rightidx, (dimension + 1)%Dim, dist);
	}
	return;
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
