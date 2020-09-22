#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


template<typename T>
struct Point
{
  T x, y, z;
  Point(T a, T b, T c) : x(a), y(b), z(c) {}
  bool operator ==(Point<T> &p)
  {
    return (x == p.x && y == p.y && z == p.z);
  }
};


template<typename T>
struct Node
{
  Point<T> minBound, maxBound;
  vector<Point<T> > data;
  Node<T>* child[8];
  Node(Point<T> a, Point<T> b) : minBound(a), maxBound(b)
  {
    for(int i = 0; i < 8; ++i) child[i] = nullptr;
  }
};


template<typename T, size_t CAPACITY>
class Octree
{

  Node<T>* root;
  
  bool find(Point<T> val, Node<T>* &p, Node<T>* start = nullptr)
  {
    Node<T> *next;
    for(p = start ? start : root; p; p = next){
      next = nullptr;
      for(int i = 0; i < 8; ++i)
      {
        if(p->child[i] && fit(val, p->child[i]))
        {
          next = p->child[i];
        }
      }
      if(!next)
      {
        for(auto point : p->data)
        {
          if(point == val) return true;
        }
        return false;
      }
    }
    return false; // <-- This should never happen!!
  }


  bool fit(Point<T> point, Node<T> *node)
  {
    bool X = point.x < (node->maxBound).x && point.x > (node->minBound).x;
    bool Y = point.y < (node->maxBound).y && point.y > (node->minBound).y;
    bool Z = point.z < (node->maxBound).z && point.z > (node->minBound).z;
    return (X && Y && Z);
  }

 public:
  
  Octree(Point<T> lower_bottom_left, Point<T> upper_front_right)
  {
    root = new Node<T> (lower_bottom_left, upper_front_right);
  }

  bool find(T x, T y, T z)
  {
    Node<T>* tmp;
    return find(Point<T>(x, y, z), tmp);
  }

  void insert(Point<T> point, Node<T> *head = nullptr)
  {
    Node<T> *pos;
    if(find(point, pos, head)) return;
    if(pos->data.size() == CAPACITY)
    {
      vector<Point<T> > tmp = pos->data;
      tmp.push_back(point);
      pos->data.clear();
      T _x = pos->minBound.x, _y = pos->minBound.y, _z = pos->minBound.z;
      T _X = pos->maxBound.x, _Y = pos->maxBound.y, _Z = pos->maxBound.z;
      T _mx = (_x + _X)/2, _my = (_y + _Y)/2, _mz = (_z + _Z)/2;
      pos->child[0] = new Node<T>(Point<T>(_x, _y, _z), Point<T>(_mx, _my, _mz));
      pos->child[1] = new Node<T>(Point<T>(_mx, _y, _z), Point<T>(_X, _my, _mz));
      pos->child[2] = new Node<T>(Point<T>(_x, _my, _z), Point<T>(_mx, _Y, _mz));
      pos->child[3] = new Node<T>(Point<T>(_mx, _my, _z), Point<T>(_X, _Y, _mz));
      pos->child[4] = new Node<T>(Point<T>(_x, _y, _mz), Point<T>(_mx, _my, _Z));
      pos->child[5] = new Node<T>(Point<T>(_mx, _y, _mz), Point<T>(_X, _my, _Z));
      pos->child[6] = new Node<T>(Point<T>(_x, _my, _mz), Point<T>(_mx, _Y, _Z));
      pos->child[7] = new Node<T>(Point<T>(_mx, _my, _mz), Point<T>(_X, _Y, _Z));
      for(auto p : tmp) insert(p, pos);
    }
    else
    {
      pos->data.push_back(Point<T>(point));
    }
  }
  
};
