#include "range-octree.h"
using namespace std;

#define PATH "../../files/sample.obj"
enum {INSERT, ERASE};

Point<float> A(-0.50, -0.02, -0.30); // lower bound
Point<float> B(0.55, 2.95, 0.40);    // upper bound
Octree<float,10> tree(A, B);

void ManagePoints(int cod)
{
  ifstream points(PATH);
  string tag;
  float x, y, z;
  int count = 0;
  while(points >> tag)
  {
    if(tag != "v") break;
    points >> x >> y >> z;
    if(cod == INSERT) tree.insert(Point<float>(x, y, z));
    if(cod == ERASE) tree.erase(Point<float>(x, y, z));
    count++;
  }
  points.close();
}

int main()
{
  ManagePoints(INSERT);
  
  cout<<tree.find(Point<float>(0.098843, 2.533042, 0.042416))<<endl;
  tree.erase(Point<float>(0.098843, 2.533042, 0.042416));
  cout<<tree.find(Point<float>(0.098843, 2.533042, 0.042416))<<endl;
  
  ManagePoints(ERASE);
}
