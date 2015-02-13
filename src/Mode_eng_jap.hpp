#ifndef MODE_ENG_JAP_H
#define MODE_ENG_JAP_H
#include "Mode.hpp"

class Mode_eng_jap : public Mode
{
  bool kana(ustring lword);
  int equals(ustring lword);

public:
  Mode_eng_jap(LList *_db);
  ~Mode_eng_jap();
  void new_session(vector<Av> in);
  ustring* next(ustring lword);
  ustring* start();
};

#endif
