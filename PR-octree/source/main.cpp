#include <PR-octree.h>
#include <tools.h>
using namespace std;


const size_t capacity = 5;
char sample_path[] = "../../files/sample.obj";


int main(int argc, char* args[])
{
  char* obj_path = (argc == 2 ? args[1] : sample_path);
  
  pair<Point<float>, Point<float> > bounds = tools::GetBounds<float>(obj_path);
  Octree<float,capacity> tree(bounds.first, bounds.second);
  
  int cntIn = tools::ManagePoints<float, capacity>(tree, INSERT, obj_path);
  cout << cntIn << " inserted points" << endl;
  
  int cntOut = tools::ManagePoints<float, capacity>(tree, ERASE, obj_path);
  cout << cntOut << " deleted points" << endl;
}
