#include "FileReader.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <glibmm/ustring.h>
#include <boost/algorithm/string.hpp>

//Installing boost-static package (not solving problem);

FileReader::FileReader() 
{
}

FileReader::~FileReader()
{
}

LList* FileReader::read_dict(string file_name) 
{
  LList *rlist = new LList();
  ifstream file(file_name.c_str());
  if (file.is_open()) {
    vector<string> *chapter_names = new vector<string>();
    vector<string> *part_names = new vector<string>();
    
    while (!file.eof()) {
      
      string line;
      getline(file, line);
      
      cout << "Line: " << line << endl;
      
      if (line.size() <= 0) {
	//do Nothing, it's an empty line
	
      } else if (line.at(0) == '#') {
	//do Nothing, these are comments.
	
      } else if (line.at(0) == '\\') {
	// these should be commands for names and string elements
	vector<string> in_data;
	boost::split(in_data, line, boost::is_any_of(" "));
	
	cout << "After boost split, Name generation" << endl;
	
	if (in_data[0] == "\\chapter") {
	  
	  cout << "Chapter name generation" << endl;
	  
	  string tmp;
	  unsigned int x;
	  
	  for (x = 1; x < in_data.size(); x++) {
	    if (tmp.size() > 0) {
	      tmp += " " + in_data[x];
	    } else {
	      tmp = in_data[x];
	    }
	    int y = int(tmp.find(","));
	    if (y != -1) {
	      tmp.erase(y);
	      chapter_names->push_back(tmp);
	      tmp = "";
	    }
	  }
	  chapter_names->push_back(tmp);
	  
	} else if (in_data[0] == "\\part") {
	  
	  cout << "Part name generation" << endl;
	  
	  string tmp;
	  unsigned int x;
	  
	  for (x = 1; x < in_data.size(); x++) {
	    if (tmp.size() > 0) {
	      tmp += " " + in_data[x];
	    } else {
	      tmp = in_data[x];
	    }
	    int y = int(tmp.find(","));
	    if (y != -1) {
	      tmp.erase(y);
	      part_names->push_back(tmp);
	      tmp = "";
	    }
	  }
	  part_names->push_back(tmp);
	}
	
      } else {
	//This should be lines that should be included in LinkNode
	vector<string> in_data;
	boost::split(in_data, line, boost::is_any_of("|"));
	
	if (in_data.size() > 3) {
	  string tmp = in_data[3];
	  
	  int chap = 0;
	  if (tmp.size() > 1) {
	    chap = ((tmp.at(0) - 48) * 10);
	    chap += (tmp.at(1) - 48);
	  } else {
	    chap = (tmp.at(0) - 48) ; 
	  }
	  
	  tmp = in_data.at(4);
	  int part = (tmp.at(0) - 48);

	  if (in_data[0].size() <= 0 || in_data[1].size() <= 0 || in_data[2].size() <= 0) {
	    // cout << "Something is NULL" << endl;
	  } else {
	    // cout << "adding Linkode, Word1: " << in_data[0] << ", Word 2: " << in_data[1] << ", Word 3: " <<
	    //in_data[2] << ", Chapter: " << chap << ", Part: " << part << endl;
	    rlist->add(new Word(in_data[0], in_data[1], in_data[2]), 
	   	       chap - 1, part - 1);
	  } 
	}
      }
    }
    file.close();
    
    rlist->set_chap_names(*chapter_names);
    rlist->set_part_names(*part_names);
  } else { // If not file open
    cout <<  "File Not Found!" << endl;
  }
  
  return rlist;
}
