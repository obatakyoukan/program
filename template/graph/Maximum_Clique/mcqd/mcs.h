/*
    Copyright 2007-2012 Janez Konc 

    If you use this program, please cite: 
    Janez Konc and Dusanka Janezic. An improved branch and bound algorithm for the 
    maximum clique problem. MATCH Commun. Math. Comput. Chem., 2007, 58, 569-590.

    More information at: http://www.sicmm.org/~konc

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
*/

#ifndef MCQD
#define MCQD

#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

struct Maxclique {
  const bool* const* e;
  int pk, level;
  const float Tlimit;
  struct Vertices {
    struct Vertex {
      int i, d;
      void set_i(const int ii)  { i = ii; }
      int get_i() const { return i; }
      void set_degree(int dd) { d = dd; }
      int get_degree() const { return d; }
    };
    Vertex *v;
    int sz;
    static bool desc_degree(const Vertex vi, const Vertex vj) { return (vi.get_degree() > vj.get_degree()); }
    Vertices(int size) : sz(0) { v = new Vertex[size]; }
    ~Vertices () {}
    void dispose() { if (v) delete [] v; }
    void sort() { std::sort(v, v+sz, desc_degree); }
    void set_degrees(Maxclique&);
    int size() const { return sz; }
    void push(const int ii) { v[sz++].set_i(ii); };
    void pop() { sz--; };
    void erase(int i){
	for(int j = i+1;j<size();j++){
	    swap( v[j] , v[j-1] );
	}
	pop();
    }
    void erase_p(int p ){
	for(int i=0;i<size();i++)if( v[i].i == p ){ erase(i); return ; }
    }
    void erase( Vertices::Vertex &p ){ erase_p( p.i ); }

    Vertex& at(const int ii) const { return v[ii]; }
    Vertex& end() const { return v[sz - 1]; }
    Vertex& operator[] (int i){ return v[i]; }
  };
  struct ColorClass {
    int *i;
    int sz;
    ColorClass() : sz(0), i(0) {}
    ColorClass(const int sz) : sz(sz), i(0) { init(sz); }
    ~ColorClass() { if (i) delete [] i;
    }
    void init(const int sz) { i = new int[sz]; rewind(); }
    void push(const int ii) { i[sz++] = ii; };
    void pop() { sz--; };
    void erase(int ii ){
	for(int j = ii + 1; j < size();j++){
	    swap( i[j] , i[j-1] ) ; 
	}
	pop();
    }
    void erase_p( int p ){
	for(int j=0;j<size();j++)if( i[j] == p ){
	    erase(j);
	    return;
	}
    }
    void rewind() { sz = 0; };
    int size() const { return sz; }
    int& at(const int ii) const { return i[ii]; }
    ColorClass& operator=(const ColorClass& dh) {
      for (int j = 0; j < dh.sz; j++) i[j] = dh.i[j];
      sz = dh.sz;
      return *this;
    }
  };
  Vertices V;
  ColorClass *C, QMAX, Q;
  bool connection(const int i, const int j) const { return e[i][j]; }
  bool cut1(const int, const ColorClass&);
  void cut2(const Vertices&, Vertices&);
  void color_sort(Vertices&);
  void expand(Vertices);
  Maxclique(const bool* const*, const int, const float=0.025);
  int steps() const { return pk; }
  ~Maxclique() {
    if (C) delete [] C;
    if (S) delete [] S;
    V.dispose();
  };
};

bool Maxclique::cut1(const int pi, const ColorClass &A) {
for (int i = 0; i < A.size(); i++)
    if (connection(pi, A.at(i)))
      return true;
  return false;
}

void Maxclique::cut2(const Vertices &A, Vertices &B) {
  for (int i = 0; i < A.size() - 1; i++) {
    if (connection(A.end().get_i(), A.at(i).get_i()))
      B.push(A.at(i).get_i());
  }
Maxclique::Maxclique (const bool* const* conn, const int sz, const float tt) : pk(0), level(1), Tlimit(tt), V(sz), Q(sz), QMAX(sz) {
  assert(conn!=0 && sz>0);
  for (int i=0; i < sz; i++) V.push(i);
  e = conn;
  C = new ColorClass[sz + 1];
  for (int i=0; i < sz + 1; i++) C[i].init(sz + 1);
