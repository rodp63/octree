#include "octree.h"

using namespace std;

#define PATH "../files/person.obj"

Point<float> A(-0.50, -0.02, -0.30); // lower bound
Point<float> B(0.55, 2.92, 0.40);    // upper bound
Octree<float,5> tree(A, B);

void InsertPoints()
{
  ifstream points(PATH);
  string tag;
  float x, y, z;
  int count = 0;
  while(points >> tag)
  {
    if(tag != "v") break;
    points >> x >> y >> z;
    tree.insert(Point<float>(x, y, z));
    count++;
  }
  points.close();
}

int main()
{
  InsertPoints();
  cout<<tree.find(Point<float>(0.098843, 2.533042, 0.042416))<<endl;
  tree.erase(Point<float>(0.098843, 2.533042, 0.042416));
  cout<<tree.find(Point<float>(0.098843, 2.533042, 0.042416))<<endl;
}
