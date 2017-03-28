#include<iostream>
#include<fstream>
#include<map>
#include<set>
#include<queue>
#include<string>
#include<functional>

using namespace std;
typedef long long lint;
#define I cin
#define O cout
int main() {
  map<lint,map<lint,set<long double,less<long double>>>> edges;
  set<lint> vertices;

  //ifstream I("input.txt");
  //ofstream O("output.txt");

  string s;

  while(I >> s) {
    if(s == "insert_vertex") {
      lint v;
      I >> v;
      if(!I.fail() && !vertices.count(v)) {
        vertices.insert(v);
        O << "oK" << endl;
      }
        else O << "error" << endl;
    }
    else if(s == "insert_edge") {
      lint v1,v2;
      long double w;
      I >> v1 >> v2 >> w;
      if(!I.fail() && vertices.count(v1) && vertices.count(v2) && v1 != v2 && !edges[v1][v2].count(w)) {
        edges[v1][v2].insert(w);
        O << "oK" << endl;
      }
      else {
        O << "error" << endl;
      }
    }
    else if(s == "erase_vertex") {
      lint v;
      I >> v;
      if(!I.fail() && vertices.count(v)) {
        vertices.erase(v);
        if(edges.count(v)) {
          edges.erase(v);
        }
	for(auto &edge_v1:edges) {
		if(edge_v1.second.count(v)) {
			edge_v1.second.erase(v);
		}
	}
        O << "oK" << endl;
      }
        else O << "error" << endl;
    }
    else if(s == "erase_edge") {
      lint v1,v2;
      I >> v1 >> v2;
      if(!I.fail() && vertices.count(v1) && vertices.count(v2) && edges.count(v1) && edges[v1].count(v2)) {
        edges[v1].erase(v2);
        O << "oK" << endl;
      }
      else {
        O << "error" << endl;
      }
    }
    else if(s == "get_edge") {
      lint v1,v2;
      I >> v1 >> v2;
      if(!I.fail() && vertices.count(v1) && vertices.count(v2) && edges.count(v1) && edges[v1].count(v2)) {
        O << *edges[v1][v2].begin() << endl;
      }
      else {
        O << "edge doesn't exist" << endl;
      }
    }
    else if(s == "invert") {
      auto tmp_edges = edges;
      tmp_edges.clear();
      for(auto it1:edges)
        for(auto it2:it1.second){
          tmp_edges[it2.first][it1.first] = it2.second;
        }
      edges = tmp_edges;
      O << "oK" << endl;
    }
    else if(s == "exit") {
      O << "See you later" << endl;
      return 0;
    }
  }

  return 0;
}
