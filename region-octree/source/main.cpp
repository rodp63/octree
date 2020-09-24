#include <region-octree.h>
#include <tools.h>
using namespace std;


const size_t depth = 10;
char sample_path[] = "../../files/sample.obj";


int main(int argc, char* args[])
{
  char* obj_path = (argc == 2 ? args[1] : sample_path);
  
  pair<Point<float>, Point<float> > bounds = tools::GetBounds<float>(obj_path);
  Octree<float,depth> tree(bounds.first, bounds.second);
  
  int cntIn = tools::ManagePoints<float, depth>(tree, INSERT, obj_path);
  cout << cntIn << " inserted points" << endl;
  
  int cntOut = tools::ManagePoints<float, depth>(tree, ERASE, obj_path);
  cout << cntOut << " deleted points" << endl;
}
