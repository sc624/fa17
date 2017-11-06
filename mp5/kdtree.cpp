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
     return findNearestNeighborHelper(query, 0, 0, points.size()-1, points[(points.size()-1)/2],points[(points.size()-1)/2]);
}

/*
Helper function to findNearestNeighbor that
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(const Point<Dim> &query, int dimension, int left, int right, const Point<Dim> &current, Point<Dim> end) const
{
  int newD = dimension;
  int median1 = (left + right)/2;
  int median2;
  int distance = 0;
      if(dimension >= Dim) {
        newD = 0;
        dimension = 0;
      }

      end = current;

      if(right != left) {
        bool hi = true;
        if (shouldReplace(query, end, points[median1]))
          end = points[median1];
        if (median1 > left) {
          if(smallerDimVal(query, points[median1], dimension)) {
            median2 = (median1+right)/2;
            hi = true;
            end = findNearestNeighborHelper( query, newD+1, left, median1-1, current, end);
          }
        }
        if (median1 < right) {
          if(smallerDimVal(points[median1], query, dimension)==true) {
            hi = false;
            median2 = (left-1+median1)/2;
            end = findNearestNeighborHelper( query, newD+1, median1+1, right, current, end);
          }
        }

        for (int i = 0; i < Dim; i++){
          distance = distance + (query[i]-end[i])*(query[i]-end[i]);
        }

        if ((points[median1][dimension] - query[dimension])*(points[median1][dimension] - query[dimension]) <= distance && hi == true && right > median1) {
          median1++;
          newD++;
          end = findNearestNeighborHelper(query, newD, median1, right, end, end);
        } else if ((points[median1][dimension] - query[dimension])*(points[median1][dimension] - query[dimension]) <= distance && hi == false && left < median1) {
          median1--;
          newD++;
          end = findNearestNeighborHelper(query, newD, left, median1, end, end);
        }
      }
      else {
        if(shouldReplace(query, current, points[left]) == false)
          return current;
        else if(shouldReplace(query, current, points[left]) == true)
          return points[left];
      }
      return end;
}
