#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


enum {WHITE, BLACK, INTERNAL};


template<typename T>
struct Point
{
  T x, y, z;
  Point(T a, T b, T c) : x(a), y(b), z(c) {}
};


template<typename T>
struct Node
{
  Point<T> minBound, maxBound;
  int color;
  Node<T>* child[8];
  Node(Point<T> a, Point<T> b, int c) : minBound(a), maxBound(b), color(c)
  {
    for(int i = 0; i < 8; ++i) child[i] = nullptr;
  }
};


template<typename T, size_t DEPTH>
class Octree
{

  Node<T>* root;
  
  bool fit(Point<T> point, Node<T> *node)
  {
    bool X = point.x < (node->maxBound).x && point.x >= (node->minBound).x;
    bool Y = point.y < (node->maxBound).y && point.y >= (node->minBound).y;
    bool Z = point.z < (node->maxBound).z && point.z >= (node->minBound).z;
    return (X && Y && Z);
  }
  
  bool find(Point<T> val, stack<Node<T>* > &path, int col, Node<T>* start = nullptr)
  {
    Node<T> *current, *next;
    for(current = start ? start : root; current; current = next){
      next = nullptr;
      for(int i = 0; i < 8; ++i)
      {
        if(current->child[i] && fit(val, current->child[i])) next = current->child[i];
      }
      path.push(current);
    }
    return path.top()->color == col;
  }

 public:
  
  Octree(Point<T> lower_bottom_left, Point<T> upper_front_right)
  {
    root = new Node<T> (lower_bottom_left, upper_front_right, WHITE);
  }

  bool find(Point<T> point)
  {
    stack<Node<T>*> tmp;
    return find(point, tmp, BLACK);
  }

  void insert(Point<T> point, int col = BLACK)
  {
    stack<Node<T>*> path;
    if(!find(point, path, col))
    {
      while(path.size() != DEPTH)
      {
        Node<T>* pos = path.top();
        path.pop();
        int cc = pos->color;
        pos->color = INTERNAL;
        T _x = pos->minBound.x, _y = pos->minBound.y, _z = pos->minBound.z;
        T _X = pos->maxBound.x, _Y = pos->maxBound.y, _Z = pos->maxBound.z;
        T _mx = (_x + _X)/2, _my = (_y + _Y)/2, _mz = (_z + _Z)/2;
        pos->child[0] = new Node<T>(Point<T>(_x, _y, _z), Point<T>(_mx, _my, _mz), cc);
        pos->child[1] = new Node<T>(Point<T>(_mx, _y, _z), Point<T>(_X, _my, _mz), cc);
        pos->child[2] = new Node<T>(Point<T>(_x, _my, _z), Point<T>(_mx, _Y, _mz), cc);
        pos->child[3] = new Node<T>(Point<T>(_mx, _my, _z), Point<T>(_X, _Y, _mz), cc);
        pos->child[4] = new Node<T>(Point<T>(_x, _y, _mz), Point<T>(_mx, _my, _Z), cc);
        pos->child[5] = new Node<T>(Point<T>(_mx, _y, _mz), Point<T>(_X, _my, _Z), cc);
        pos->child[6] = new Node<T>(Point<T>(_x, _my, _mz), Point<T>(_mx, _Y, _Z), cc);
        pos->child[7] = new Node<T>(Point<T>(_mx, _my, _mz), Point<T>(_X, _Y, _Z), cc);
        find(point, path, col, pos);
      }
      path.top()->color = col;
      path.pop();
      bool flag = true;
      while(!path.empty() && flag)
      {
        Node<T>* current = path.top();
        path.pop();
        for(int i = 0; i < 8; ++i)
        {
          if(current->child[i]->color != col) flag = false;
        }
        if(flag)
        {
          current->color = col;
          for(int i = 0; i < 8; ++i)
          {
            delete current->child[i];
            current->child[i] = nullptr;
          }
        }
      }
    }
  }

  void erase(Point<T> point)
  {
    insert(point, WHITE);
  }

};
