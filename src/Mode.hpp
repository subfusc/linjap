#ifndef MODE_H
#define MODE_H

#include "Word.hpp"
#include "Queue.hpp"
#include "Av.hpp"
#include "LList.hpp"

#include <iostream>
#include <cstdlib> 
#include <time.h>
#include <vector>
#include <list>
#include <glibmm/ustring.h>
using namespace std;
using namespace Glib;

/* The purpose of this class is to provide a base for an 
 * easy expanding to other languages.
 * That is to say it holds the necessary components to 
 * do fault checking and formating of
 * in/out String array to the gui.
 */
class Mode
{
protected:
  //Holds the last node in (the one currently beein asked for in the gui)
  LList* db;
  Word* last;
  Queue* session;
  int total;
  int _wrong;

private:
  void put_part_in_session(int chap, int part);

public:
  Mode() {}
  Mode(LList *_db);
  ~Mode();
  
  /* Prepare gui for new word, and check last one.
   * @param: LinkNode - next Node in the training queue.
   * ustring* - last word typed by the user in gui.
   * @return: ustring[4], <next word, last correct, last typed, 
   * correct/not correct ["n" or "nc"]>
   */
  
  virtual void new_session(vector<Av> in);
  virtual bool has_next();
  virtual int words_left();
  virtual int words_total();
  virtual void wrong(Word *node);
  virtual int wrong_total();
  virtual void stop_session();
  
  virtual ustring* next(ustring lword) = 0;
  virtual ustring* start() = 0;
};

#endif
