#include "PR-octree.h"
using namespace std;

enum {INSERT, ERASE};

const float inf = 1e9;
char sample_path[] = "../../files/sample.obj";


pair<Point<float>, Point<float> > GetBounds(char path[])
{
  ifstream points(path);
  string tag;
  float x, y, z, mx, my, mz, Mx, My, Mz;
  mx = my = mz = inf;
  Mx = My = Mz = -inf;
  while(points >> tag)
  {
    if(tag != "v") break;
    points >> x >> y >> z;
    mx = min(mx, x);
    my = min(my, y);
    mz = min(mz, z);
    Mx = max(Mx, x);
    My = max(My, y);
    Mz = max(Mz, z);
  }
  // Expand the bounds by 10%
  mx -= abs(mx / 10);
  my -= abs(my / 10);
  mz -= abs(mz / 10);
  Mx += abs(Mx / 10);
  My += abs(My / 10);
  Mz += abs(Mz / 10);
  cout << "Lower bound : (" << mx << "," << my << "," << mz << ")\n";
  cout << "Upper bound : (" << Mx << "," << My << "," << Mz << ")\n";
  points.close();
  return make_pair(Point<float>(mx, my, mz), Point<float>(Mx, My, Mz));
}


void ManagePoints(Octree<float,10> &tree, int cod, char path[])
{
  ifstream points(path);
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


int main(int argc, char* args[])
{
  char* obj_path = (argc == 2 ? args[1] : sample_path);
  
  pair<Point<float>, Point<float> > bounds = GetBounds(obj_path);
  Octree<float,10> tree(bounds.first, bounds.second);
  
  ManagePoints(tree, INSERT, obj_path);
  
  cout<<tree.find(Point<float>(0.098843, 2.533042, 0.042416))<<endl;
  tree.erase(Point<float>(0.098843, 2.533042, 0.042416));
  cout<<tree.find(Point<float>(0.098843, 2.533042, 0.042416))<<endl;
  
  ManagePoints(tree, ERASE, obj_path);
}
