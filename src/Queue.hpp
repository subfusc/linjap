#ifndef QUEUE_H
#define QUEUE_H

#include "Word.hpp"
#include <iostream>
#include <glibmm/ustring.h>

class Queue 
{
  class QNode {
    QNode *_next;
    Word *elem;
    
  public:
    QNode(Word *in);
    ~QNode();
    
    bool has_next();
    QNode* next();
    void set_next(QNode *in);
    Word* get_word();
  };
  
  QNode *first;
  QNode *last;
  int var_size;

public:
  Queue();
  ~Queue();
  void push(Word in);
  bool add(Word *in, int place);
  bool add(Word in, int place);
  Word* pop();
  bool empty();
  int size();
};
#endif
