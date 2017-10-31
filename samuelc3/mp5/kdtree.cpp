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
    return Point<Dim>();
}
