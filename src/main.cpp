#include "FileReader.hpp"
#include "LList.hpp"
#include "MainWindow.hpp"
#include "NeWindow.hpp"
#include "Queue.hpp"
#include "Engine.hpp"
#include <iostream>
#include <list>
#include <gtkmm/main.h>
using namespace std;

int main(int argv, char **argc) 
{
  Engine *e;
  if (argv > 1) {
    e = new Engine(argc[1]);
  } else {
    e = new Engine("src/kana.dict");
  }
  Gtk::Main kit(argv, argc);
  MainWindow *w = new MainWindow(&kit, e);

  delete w;
  delete e;

  cout << "After delete" << endl;
  return 0;

}
