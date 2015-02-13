#include "Mode.hpp"

Mode::Mode(LList *_db)
{
  db = _db;
  last = NULL;
  session = NULL;
  total = 0;
  _wrong = 0;
  srand(time(NULL));
}

Mode::~Mode()
{
  if (last) delete last;
  if (session) delete session;
}

void Mode::put_part_in_session(int chap, int part) {
  list<Word> *tmp = NULL;
  if (!(tmp = db->get(chap, part))) return;
  //cout << "TMP:" << tmp << endl;
  cout << "Chapter: " << chap << ", Part: " << part << endl;
  
  while (tmp->size() > 0) {
    Word wtmp = tmp->front();
    int rand_int = (rand() % 2) + 1;
    cout << "Word: " << wtmp.get_wd1() << ", int: " << rand_int << endl;
    
    for(int y = 0; y < rand_int; y++) {
      int rand_index;
      if (session->size()) {
	rand_index = rand() % session->size();
      } else {
	rand_index = 0;
      }
      session->add(wtmp, rand_index);
    }
    tmp->pop_front();
  }
  delete tmp;
}


void Mode::new_session(vector<Av> in) 
{
  cout << "-- Mode :: new session --" << endl;
  stop_session();

  session = new Queue();
  cout << "Prep complete" << endl;

  for(int x = 0; (unsigned int) x < in.size(); x++) {
    if (in[x].part == -1) {
      //cout << "got -1, with " << db->get_part_length() << endl;
      for (int y = 0; y <= db->get_part_length(); y++) {
	put_part_in_session(in[x].chapter, y);
      }
    } else {
      put_part_in_session(in[x].chapter, in[x].part);
    }
  }
  
  cout << "Queue make complete" << endl;
  _wrong = 0;
  total = session->size();
}

bool Mode::has_next()
{
  if ((session != NULL && session->size() > 0) || last != NULL) {
    return true;
  } else {
    return false;
  }
}

int Mode::words_left()
{
  return session->size();
}

int Mode::words_total() 
{
  return total;
}

int Mode::wrong_total()
{
  return _wrong;
}

void Mode::stop_session()
{
  cout << "-- Mode :: Stop Session --" << endl;
  if (last) delete last;
  last = NULL;
  if (session) delete session;
  session = NULL;
  _wrong = 0;
  total = 0;
}

/* Function to handle insertion of words wich the user got wrong 
 * @param: LinkNode* node -Node to place in the queue again
 * @return: void
 */
void Mode::wrong(Word *node)
{
    int random_integer = (rand() % 4) + 2;
    total += random_integer;
    _wrong++;
    cout << "--- wrong(Word)" << endl <<
      "Put word in : " << random_integer << " times, at place: ";
    
    for(int index = 0; index < random_integer; index++){
      int randint;
      if (session->size()) {
	randint = rand() % session->size();
      } else {
	randint = 0;
      }
      
      cout << randint << ", ";
      session->add(*last, randint);
    }
    
    cout << "Practise queue consist of: " << session->size() << " words." << endl;
}
