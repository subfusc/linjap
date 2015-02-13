#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include "Engine.hpp"
#include "HelpWindow.hpp"
#include "NeWindow.hpp"
#include "PopWindow.hpp"

using namespace std;
using namespace Gtk;

class MainWindow : public Window
{
public:
  MainWindow(Main *kit, Engine *en);
  ~MainWindow();
  
private:
  //Signal handlers:
  void on_menu_file_quit();
  void on_menu_help();		
  void on_next_button();
  void on_new_session();
  void on_load_dict();
  
  //Functions
  // Functions to move down into engine
  ustring int_to_ustring(int x);
  //Functions wich should remain in the gui.
  void update_progress();
  
  //Child Windows
  HelpWindow *hwindow;
  NeWindow *nwindow;
  PopWindow *pwindow;
  
  //Child Gtk Widgets
  VBox m_vbox, l_l_vbox, l_vbox;
  HBox m_hbox, l_hbox;
  Frame e_frame, l_frame;
  Button *ok_button;
  Label c_eng, l_cor, l_u, st, l_cor_label, l_u_label, st_label;
  Entry input_box;
  ProgressBar p_bar;
  Gtk::Main *ki;
  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
  
  //Other private variables
  Engine *en;
  ustring *strings;
  
};

#endif
