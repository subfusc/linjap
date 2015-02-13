#include "MainWindow.hpp"

/* Main window constructor*/
MainWindow::MainWindow(Gtk::Main *kit, Engine *engine)
  : m_vbox(false, 5),
    l_l_vbox(false, 3),
    l_vbox(false, 3),
    m_hbox(false, 2),
    l_hbox(false, 2),
    e_frame("English Word: "),
    l_frame("Last Word: "),
    c_eng("Initialised ? "),
    l_cor("To start"),
    l_u("Press New -->"),
    st("Correct/Not Correct"),
    l_cor_label("Correct:"),
    l_u_label("Your:"),
    st_label("State:"),
    input_box(),
    p_bar()
{
    /*Set pointers to null value */
    hwindow = 0;
    nwindow = 0;
    pwindow = 0;
    ki = kit;
    ok_button = new Button(Gtk::Stock::NEW);
    strings = NULL;
    en = engine;


    //Create actions for menus and toolbars:
    m_refActionGroup = Gtk::ActionGroup::create();

    //File menu:
    m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));

    //Sub-menu.
    m_refActionGroup->add(Gtk::Action::create("NewSession", Gtk::Stock::NEW),
                          sigc::mem_fun(*this, &MainWindow::on_new_session));
    m_refActionGroup->add(Gtk::Action::create("Load Dictionary", "Load Dictionary"),
                          sigc::mem_fun(*this, &MainWindow::on_load_dict ));
    m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
                          sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));

    //Help menu:
    m_refActionGroup->add( Gtk::Action::create("HelpMenu", "Help") );
    m_refActionGroup->add( Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT),
                          sigc::mem_fun(*this, &MainWindow::on_menu_help) );

    m_refUIManager = Gtk::UIManager::create();
    m_refUIManager->insert_action_group(m_refActionGroup);

    add_accel_group(m_refUIManager->get_accel_group());

    //Layout the actions in a menubar and toolbar:
    Glib::ustring ui_info = 
	"<ui>"
	"  <menubar name='MenuBar'>"
	"    <menu action='FileMenu'>"
	"		<menuitem action='NewSession'/>"
	"		<menuitem action='Load Dictionary'/>"
	"		<separator/>"
	"      	<menuitem action='FileQuit'/>"
	"    </menu>"
	"    <menu action='HelpMenu'>"
	"      <menuitem action='HelpAbout'/>"
	"    </menu>"
	"  </menubar>"
	"</ui>";

    /* Throw exeptions from Glibmm */

#ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
	m_refUIManager->add_ui_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
	std::cerr << "building menus failed: " <<  ex.what();
    }
#else
    std::auto_ptr<Glib::Error> ex;
    m_refUIManager->add_ui_from_string(ui_info, ex);
    if(ex.get())
    {
	std::cerr << "building menus failed: " <<  ex->what();
    }
#endif //GLIBMM_EXCEPTIONS_ENABLED

    //Get the menubar and toolbar widgets, and add them to a container widget:
    Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
    if(pMenubar) m_vbox.pack_start(*pMenubar, Gtk::PACK_SHRINK);

    p_bar.set_text("Initialised");//Set text on progress bar

    //Signal handlers
    input_box.signal_activate().connect(sigc::mem_fun(*this, 
						      &MainWindow::on_next_button));
    ok_button->signal_clicked().connect(sigc::mem_fun(*this, 
						      &MainWindow::on_new_session));

    //Window properties
    c_eng.set_text("Welcome to Linjap");
    set_title("Linjap 2");
    try {
	set_icon_from_file("src/jping.png");
    } catch (Glib::FileError e) {
	try {
	    set_icon_from_file("/usr/local/share/linjap/jping.png");

	} catch (Glib::FileError e) {
	  //set_icon_from_file("/usr/share/linjap/jping.png");
	}
    }

    //Size requests
    e_frame.set_size_request(400,100);
    m_hbox.set_size_request(400, 100);
    l_frame.set_size_request(300, 100);

    //Pack last word label box
    l_l_vbox.pack_start(l_cor_label);
    l_l_vbox.pack_start(l_u_label);
    l_l_vbox.pack_start(st_label);

    //Pack last word box
    l_vbox.pack_start(l_cor);
    l_vbox.pack_start(l_u);
    l_vbox.pack_start(st);

    //pack last box
    l_hbox.pack_start(l_l_vbox);
    l_hbox.pack_start(l_vbox);

    //pack last box in frame
    l_frame.add(l_hbox);

    //Pack english box into lable.
    e_frame.add(c_eng);

    //pack main horizontal box (button and last ) 
    m_hbox.pack_start(l_frame);
    m_hbox.pack_start(*ok_button);

    //Pack main vertical box
    m_vbox.pack_start(e_frame);
    m_vbox.pack_start(input_box);
    m_vbox.pack_start(m_hbox);
    m_vbox.pack_start(p_bar, PACK_SHRINK);

    // Add main vertical box to window
    add(m_vbox);

    //Show everything
    show_all_children();
    ki->run(*this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_menu_file_quit()
{
    if (pwindow != 0) {
	pwindow->hide();
	delete pwindow;
    }
    if (hwindow != 0) {
	hwindow->hide();
	delete hwindow;
    }
    ki->quit();
}

void MainWindow::on_menu_help()
{
    hwindow = new HelpWindow();
    hwindow->show(); 	//Shows the window.
}

void MainWindow::on_new_session() 
{	
  
  if (nwindow == 0) {
    
    nwindow = new NeWindow(en);
    ki->run(*nwindow);
    
    delete nwindow;
    nwindow = 0;
    if (!en->has_next()) return;
    
    delete ok_button;
    ok_button = new Button(Gtk::Stock::OK);
    m_hbox.pack_start(*ok_button);
    ok_button->show();
    ok_button->signal_clicked().connect(sigc::mem_fun(*this, 
						      &MainWindow::on_next_button) );
    st.set_use_markup(true);
    
    cout << "run on next button" << endl;
    on_next_button();
  } else {
    cout << "Window Exist" << endl;
  }
}

/* Update the status of the progressbar */
void MainWindow::update_progress()
{
  int total = en->words_total();
  int num_typed = (total - en->words_left());	
  float presentage = (float) num_typed / total;
  
  p_bar.set_text("Word: " + this->int_to_ustring(num_typed) + 
		 " / " + this->int_to_ustring(total));
  p_bar.set_fraction(presentage);
}

void MainWindow::on_next_button() 
{
  cout << "Button Pressed, words left: " << en->words_left() << endl;
  strings = en->next(input_box.get_text());//Get user input
  cout << strings[0] << endl;
  if (en->has_next()) {
    c_eng.set_text(strings[0]);//Set english box to next word.
    l_cor.set_text(strings[1]);//set it to last correct lable
    l_u.set_text(strings[2]);//set l_u lable to your word.
      
    /* if they are the same, set correct. If not, set Not correct */
    if (strings[3].compare("c") == 0) {
      st.set_markup("<span foreground=\"green\">CORRECT!</span>");
    } else {
      st.set_markup("<span foreground=\"red\">NOT CORRECT!</span>");
    }
    
    update_progress();	
    input_box.set_text("");/* reset input */	
  } else {
    c_eng.set_text(strings[0]);
    l_cor.set_text(strings[1]);
    l_u.set_text(strings[2]);
    st.set_markup("<span foreground=\"green\">CORRECT!</span>");
    
    delete ok_button;
    ok_button = new Button(Gtk::Stock::NEW);
    m_hbox.pack_start(*ok_button);
    ok_button->show();
    ok_button->signal_clicked().connect(sigc::mem_fun(*this, 
						      &MainWindow::on_new_session));
    
    if (pwindow != 0) {
      delete pwindow;
    }
    
    float wrong_pros = 100.0;
    int wrong = en->wrong_total();
    cout << "Wrong: " << wrong << endl;
    if (wrong != 0) {
      wrong_pros /= en->words_total();
      wrong_pros = 100 - wrong_pros;
    }
    
    pwindow = new PopWindow("End of Session", 
			    "Congratulations, you have just practised a whole chapter.\nYou got " 
			    + int_to_ustring((int) wrong_pros) 
			    + "% Correct.");
    pwindow->show();
    
    update_progress();
  }
}

void MainWindow::on_load_dict() {
  cout << "On new load" << endl;
  ustring title("Choose Dictionary file");
  FileChooserDialog dialog(title, FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);
  
  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
  
  FileFilter filter_dict;
  filter_dict.set_name("Dict Files");
  filter_dict.add_pattern("*.dict");
  dialog.add_filter(filter_dict);
  
  FileFilter filter_all;
  filter_all.set_name("All Files");
  filter_all.add_pattern("*");
  dialog.add_filter(filter_all);    
  
  int result = dialog.run();
  
  //Handle the response:
  switch(result) {
  case(Gtk::RESPONSE_OK): 
    {
      en->load_dict(dialog.get_filename());
      c_eng.set_text("New Dictionary Loaded");
      delete ok_button;
      ok_button = new Button(Gtk::Stock::NEW);
      m_hbox.pack_start(*ok_button);
      ok_button->show();
      ok_button->signal_clicked().connect(sigc::mem_fun(*this, 
							&MainWindow::on_new_session));
      break;
    }
  case(Gtk::RESPONSE_CANCEL):
  default:
    {
      cout << "Nothing to do" << endl;
    }
  }
}

/* Convert an int between 0 and 999 to a Unicode string */
ustring MainWindow::int_to_ustring(int num_typed)
{

    ustring return_string;
    if (num_typed > 9) {
	if (num_typed > 99) {
	    int tmp3 = 0;
	    int tmp = (int) (num_typed / 100);
	    char tmp2 = (char) (tmp + 48);
	    return_string = tmp2;
	    tmp3 = tmp * 10;
	    tmp = ((num_typed - (tmp * 100)) / 10 );
	    tmp2 = (char) (tmp + 48);
	    tmp3 += tmp;
	    return_string += tmp2;
	    tmp = (num_typed - (tmp3 * 10));
	    tmp2 = (char) (tmp + 48);
	    return_string += tmp2;

	} else {
	    int tmp = (int) (num_typed / 10);
	    char tmp2 = (char) (tmp + 48);
	    return_string = tmp2;
	    tmp = (num_typed - (tmp * 10));
	    tmp2 = (char) (tmp + 48);
	    return_string += tmp2;
	}
    } else {
	char tmp2 = (char) (num_typed + 48);
	return_string = tmp2;
    }
    return return_string;
}
