#include "Queue.hpp"
using namespace std;

Queue::QNode::QNode(Word *in) 
{
  _next = NULL;
  elem = in;
}

Queue::QNode::~QNode()
{
  ;
}

bool Queue::QNode::has_next()
{
  return _next != NULL;
}

Queue::QNode* Queue::QNode::next()
{
  return _next;
}

void Queue::QNode::set_next(QNode *in) 
{
  _next = in;
}

Word* Queue::QNode::get_word() 
{
  return elem;
}

Queue::Queue()
{
    first = NULL;
    last = NULL;
    var_size = 0;
}

Queue::~Queue()
{
  if (!first) return;

  QNode *ce = first;
  while (ce->has_next()) {
    QNode *tmp = ce;
    ce = ce->next();
    delete tmp;
  }
  delete ce;
}

void Queue::push(Word in)
{
  if (last != NULL) {
    last->set_next(new QNode(new Word(in)));
    last = last->next();
  } else {
    first = new QNode(new Word(in));
    last = first;
  }

  var_size++;
}

bool Queue::add(Word *in, int place) 
{
  return this->add(*in, place);
}

bool Queue::add(Word in, int place) 
{
  QNode *node = new QNode(new Word(in));
  
  if (size() < place || place < 0) {
    return false;
  }
 
  if (place == 0) {
    if (first != NULL){
      node->set_next(first);
      first = node;
    } 
    if (first == NULL) {
      first = node;
      last = first;
    }
    var_size++;
    return true;
  }
  
  QNode *current = first;
  
  for(; place > 1; place--) {
    current = current->next();
  }
  
  node->set_next(current->next());
  current->set_next(node);
  var_size++;
  
  return true;
}

Word* Queue::pop()
{
  if (first != NULL) {
    QNode *tmp = first;
    if (first->has_next()) {
      first = first->next();
    } else {
      first = NULL;
      last = NULL;
    }
    var_size--;
    return tmp->get_word();
  } else {
    return NULL;
  }
}

int Queue::size()
{
    return var_size;
}

bool Queue::empty()
{
    if (var_size <= 0) {
	return true;
    }
    return false;
}

