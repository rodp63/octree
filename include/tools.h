#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const float inf = 1e9;
enum {INSERT, ERASE};

struct tools{
  
  template<typename T>
  static pair<Point<T>, Point<T> > GetBounds(char path[])
  {
    ifstream points(path);
    string tag;
    T x, y, z, mx, my, mz, Mx, My, Mz;
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
    mx -= (Mx - mx) / 10;
    my -= (My - my) / 10;
    mz -= (Mz - mz) / 10;
    Mx += (Mx - mx) / 10;
    My += (My - my) / 10;
    Mz += (Mz - mz) / 10;
    cout << "Lower bound : (" << mx << "," << my << "," << mz << ")\n";
    cout << "Upper bound : (" << Mx << "," << My << "," << Mz << ")\n";
    points.close();
    return make_pair(Point<T>(mx, my, mz), Point<T>(Mx, My, Mz));
  }

  template<typename T, int S>
  static int ManagePoints(Octree<T,S> &tree, int cod, char path[])
  {
    ifstream points(path);
    string tag;
    T x, y, z;
    int count = 0;
    while(points >> tag)
    {
      if(tag != "v") break;
      points >> x >> y >> z;
      if(cod == INSERT) tree.insert(Point<T>(x, y, z));
      if(cod == ERASE) tree.erase(Point<T>(x, y, z));
      count++;
    }
    points.close();
    return count;
  }
  
};
