/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  if(curDim < Dim && curDim != Dim){
    if(first[curDim] < second[curDim])
      return true;
    else if(first[curDim] == second[curDim])
      return first < second;
  }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < Dim; i++) {
      sum1 = sum1 + (target[i] - currentBest[i])*(target[i] - currentBest[i]);
    }
    for (int x = 0; x < Dim; x++) {
      sum2 = sum2 + (target[x] - potential[x])*(target[x] - potential[x]);
    }
    if(sum1 == sum2)
      return potential < currentBest;
    else
      return sum2 < sum1;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     KDTreeHelper(points.size()-1, 0, 0);
}
/*Constructor helper function that traverses through the vector of points and organizes them using quicksort*/
template <int Dim>
void KDTree<Dim>::KDTreeHelper(int rightidx, int leftidx, int dimension)
{
  quickSelect(rightidx, leftidx, ((rightidx + leftidx) / 2) , dimension);
  if(rightidx > ((rightidx + leftidx) / 2) + 1)
    KDTreeHelper(((rightidx + leftidx) / 2), leftidx, (dimension + 1) % Dim);
  else if(leftidx < ((rightidx + leftidx) / 2) - 1){
    KDTreeHelper(rightidx, ((rightidx + leftidx) / 2) - 1, (dimension + 1) % Dim);
  }
}
/*quickselect to find kth smallest element in a list
*/
template <int Dim>
void KDTree<Dim>::quickSelect(int rightidx, int leftidx, int mid_idx, int dimension)
{
  if(leftidx >= rightidx)
    return;
  int pivot_idx = (leftidx + rightidx)/2;
  pivot_idx = partition(rightidx, leftidx, pivot_idx, dimension);
  if(mid_idx == pivot_idx)
    return;
  else if(mid_idx < pivot_idx)
    quickSelect(pivot_idx - 1, leftidx, mid_idx, dimension);
  else
    quickSelect(rightidx, pivot_idx + 1, mid_idx, dimension);
}

/*partition helper function for quickselect algorithm
*/
template <int Dim>
int KDTree<Dim>::partition(int rightidx, int leftidx, int pivot_idx, int dimension)
{
  Point<Dim> pvnert = points[pivot_idx];
  std::swap(points[pivot_idx], points[rightidx]);
  int partitionIndex = leftidx;
  for(int i = leftidx; i < rightidx; i++){
    if(smallerDimVal(points[i], pvnert, dimension)){
        std::swap(points[i],points[partitionIndex]);
        partitionIndex++;
    }
}
  std::swap(points[partitionIndex], points[rightidx]);
return partitionIndex;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return points[findNearestNeighborHelper(query, 0, (1 - points.size()) / 2, 0, points.size()-1)];
}

/*
Helper function to findNearestNeighbor that
 */
template <int Dim>
int KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query, int currentDimension, int current, int left, int right) const
{
  //Base case
  if(left >= right)
    return current;

  while (currentDimension >= Dim){
	  currentDimension -= Dim;
  }

  int distance = (points[current][currentDimension]-query[currentDimension]) * (points[current][currentDimension]-query[currentDimension]);
  int currentBest = current;
  int temp = current;



  if (smallerDimVal(query, points[current], currentDimension)){
    currentBest = findNearestNeighborHelper(query, currentDimension+1, (((current-1) - left)/2)+left, left, current-1);
    if (shouldReplace(query, points[currentBest], points[current]) == true)
      currentBest = current;
    int radius;
    for (int i = 0; i < Dim; i++){
        radius = radius + (points[currentBest][i] - query[i]) * (points[currentBest][i] - query[i]);
    }

    if (radius >= distance)
    {

      temp = findNearestNeighborHelper(query, currentDimension+1, ((right - (current + 1))/2)+current+1, current+1, right);
      if (shouldReplace(query, points[currentBest], points[temp]) == true)
        currentBest = temp;
    }
  }

  else{
    currentBest = findNearestNeighborHelper(query, currentDimension+1, ((right - (current+1))/2)+current+1, current+1, right);
    if (shouldReplace(query, points[currentBest], points[current]) == true)
      currentBest = current;
    int radius;
    for (int i = 0; i < Dim; i++){
        radius = radius + (points[currentBest][i] - query[i]) * (points[currentBest][i] - query[i]);
    }
    if (radius >= distance) {
      temp = findNearestNeighborHelper(query, currentDimension+1, (((current-1) - left)/2)+left, left, current-1);
      if (shouldReplace(query, points[currentBest], points[temp]) == true)
        currentBest = temp;
    }
  }
  return currentBest;
}
