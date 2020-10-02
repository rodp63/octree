#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const float inf = 1e9;
enum {INSERT, ERASE};

struct tools{
  
  template<typename T>
  static pair<Point<T>, Point<T> > GetBounds(char path[])
  {
    ifstream points(path);
    string line, tag;
    T x, y, z, mx, my, mz, Mx, My, Mz;
    mx = my = mz = inf;
    Mx = My = Mz = -inf;
    while(getline(points, line))
    {
      size_t pos = line.find(' ');
      if(pos == string::npos) continue;
      tag = line.substr(0, pos);
      if(tag != "v") continue;
      stringstream point(line.substr(pos));
      point >> x >> y >> z;
      mx = min(mx, x);
      my = min(my, y);
      mz = min(mz, z);
      Mx = max(Mx, x);
      My = max(My, y);
      Mz = max(Mz, z);
    }
    // Expand the bound by 10% and make a cube
    T dist = max(Mx - mx, max(My - my, Mz - mz));
    T plus = dist / 10;
    Mx = mx + dist + plus;
    My = my + dist + plus;
    Mz = mz + dist + plus;
    mx -= plus;
    my -= plus;
    mz -= plus;
    cout << "Lower bound : (" << mx << "," << my << "," << mz << ")\n";
    cout << "Upper bound : (" << Mx << "," << My << "," << Mz << ")\n";
    points.close();
    return make_pair(Point<T>(mx, my, mz), Point<T>(Mx, My, Mz));
  }

  template<typename T, int S>
  static int ManagePoints(Octree<T,S> &tree, int cod, char path[])
  {
    ifstream points(path);
    string line, tag;
    T x, y, z;
    int count = 0;
    while(getline(points, line))
    {
      size_t pos = line.find(' ');
      if(pos == string::npos) continue;
      tag = line.substr(0, pos);
      if(tag != "v") continue;
      stringstream point(line.substr(pos));
      point >> x >> y >> z;
      if(cod == INSERT) tree.insert(Point<T>(x, y, z));
      if(cod == ERASE) tree.erase(Point<T>(x, y, z));
      count++;
    }
    points.close();
    return count;
  }
  
};
