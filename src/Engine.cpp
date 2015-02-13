#include "Engine.hpp"

Engine::Engine(string filename)
{
  db = FileReader::read_dict(filename);
  mod = new Mode_eng_jap(db);
  in_session = false;
  cout << "Db size: " << db->size() << endl;
}

Engine::~Engine() 
{
  delete db;
  delete mod;
}

void Engine::load_dict(string filename)
{
  delete db;
  delete mod;
  db = FileReader::read_dict(filename);
  mod = new Mode_eng_jap(db);
}

Data* Engine::get_data() 
{
  return db->get_data();
}

bool Engine::prepare_session(vector<Av> in)
{
  cout << "-- Engine :: Prepare Session --" << endl;
  in_session = false;
  mod->new_session(in);
  return true;
}

ustring* Engine::next(ustring last)
{
  if (in_session) {
    return mod->next(last);
  } else {
    in_session = true;
    return mod->start();
  }
} 

bool Engine::has_next()
{
  cout << "Engine::HAS_NEXT" << endl;
  return mod->has_next();
}

int Engine::words_left()
{
  return mod->words_left();
}

int Engine::words_total()
{
  return mod->words_total();
}

int Engine::wrong_total()
{
  return mod->wrong_total();
}
