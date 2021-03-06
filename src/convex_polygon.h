#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H
#include "./math_vector.h"
#include "./bubblesort.h"

class ConvexPolygon{
public:
      friend class ConvexPolygonFactory;
      static ConvexPolygon create(MathVector vertices[], int numberOfVertices){
      MathVector g = centroid(vertices, numberOfVertices);
      MathVector r = vertices[0] - g;
      AngleComparator comp(g, r);
      bubbleSort(vertices, vertices+numberOfVertices, comp);
      // std::sort(vertices, vertices+numberOfVertices, comp);
      return ConvexPolygon(vertices, numberOfVertices);
    }
private:
    ConvexPolygon(MathVector vertices[], int numberOfVertices){
      _numberOfVertices = numberOfVertices;
      _vertices = new MathVector[_numberOfVertices];
      for (size_t i = 0; i < _numberOfVertices; i++) {
        _vertices[i] = vertices[i];
      }
    }
public:
    ~ConvexPolygon(){
      if(_vertices){
        delete [] _vertices;
      }
    }

    MathVector vertex(int index) const {   // start from zero
      return _vertices[index];
    }

    double perimeter() const {
      double result = 0;
      for (size_t i = 1; i < _numberOfVertices; i++) {
        result += (_vertices[i] - _vertices[i-1]).length();
      }
      result += (_vertices[0] - _vertices[_numberOfVertices-1]).length();
      return result;
    }

    double area() const {
      double result = 0;
      for (size_t i = 1; i < _numberOfVertices-1; i++) {
        result += _vertices[0].areaWith(_vertices[i], _vertices[i+1]);
      }
      return result;
    }

private:
  int _numberOfVertices;
  MathVector * _vertices;
};

class ConvexPolygonFactory{
public:
  ConvexPolygon createConvexPolygon(MathVector vertices[], int numberOfVertices){
    MathVector g = centroid(vertices, numberOfVertices);
    MathVector r = vertices[0] - g;
    AngleComparator comp(g, r);
    bubbleSort(vertices, vertices+numberOfVertices, comp);
    // std::sort(vertices, vertices+numberOfVertices, comp);
    return ConvexPolygon(vertices, numberOfVertices);
  }
};

#endif
