#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Run(" Run "),
  m_Button_Quit("_Quit", true),
  m_Button_Buffer1("Use buffer 1"),
  m_Button_Buffer2("Use buffer 2")
{
    set_title("Editor");
    set_border_width(5);
    set_default_size(400, 200);

    add(m_VBox);

    //Adding command line entry
    AddCommandLine();

    m_VBox.set_border_width(5);
    m_VBox.set_spacing(5);

    //Add the TreeView, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.add(m_TextView);

    //Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_VBox.pack_start(m_ScrolledWindow);

    //Add buttons:
    m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

    m_ButtonBox.pack_start(m_Button_Buffer1, Gtk::PACK_SHRINK);
    m_ButtonBox.pack_start(m_Button_Buffer2, Gtk::PACK_SHRINK);
    m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
    m_ButtonBox.set_border_width(5);
    m_ButtonBox.set_spacing(5);
    m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

    //Connect signals:
    m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::on_button_quit) );
    m_Button_Buffer1.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::on_button_buffer1) );
    m_Button_Buffer2.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::on_button_buffer2) );

    fill_buffers();
    on_button_buffer1();

    show_all_children();
}

void MainWindow::fill_buffers()
{
    m_refTextBuffer1 = Gtk::TextBuffer::create();
    m_refTextBuffer1->set_text("This is the text from TextBuffer #1.");

    m_refTextBuffer2 = Gtk::TextBuffer::create();
    m_refTextBuffer2->set_text("This is some alternative text, from TextBuffer #2.");
}

void MainWindow::AddCommandLine()
{
    m_VBox.pack_start(m_Entry, Gtk::PACK_SHRINK);

    //m_VBox.pack_start(m_Label, Gtk::PACK_EXPAND_WIDGET);

    m_Button_Run.signal_clicked().connect( sigc::mem_fun(*this,
                &MainWindow::on_button_close) );
    m_VBox.pack_start(m_Button_Run, Gtk::PACK_SHRINK);
    m_Button_Run.set_can_default();
    m_Button_Run.grab_default();

    //Add an EntryCompletion:
    Glib::RefPtr<Gtk::EntryCompletion> completion = Gtk::EntryCompletion::create();
    m_Entry.set_completion(completion);

    //Create and fill the completion's filter model
    Glib::RefPtr<Gtk::ListStore> refCompletionModel = Gtk::ListStore::create(m_Columns);
    completion->set_model(refCompletionModel);

    // For more complex comparisons, use a filter match callback, like this.
    // See the comment below for more details:
    //completion->set_match_func( sigc::mem_fun(*this,
    //&ExampleWindow::on_completion_match) );

    //Fill the TreeView's model
    Gtk::TreeModel::Row row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "Alan Zebedee";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_name] = "Adrian Boo";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "Bob McRoberts";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 4;
    row[m_Columns.m_col_name] = "Bob McBob";

    //Tell the completion what model column to use to
    //- look for a match (when we use the default matching, instead of
    //  set_match_func().
    //- display text in the entry when a match is found.
    completion->set_text_column(m_Columns.m_col_name);

    //Add actions to the completion:
    //These are just extra items shown at the bottom of the list of possible
    //completions.

    //Remember them for later.
    /*
    m_CompletionActions[0] = "Use Wizard";
    m_CompletionActions[1] = "Browse for Filename";

    for(const auto& the_pair : m_CompletionActions)
    {
        auto position = the_pair.first;
        auto title = the_pair.second;
        completion->insert_action_text(title, position);
    }
    */

    completion->signal_action_activated().connect( sigc::mem_fun(*this,
             &MainWindow::on_completion_action_activated) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_quit()
{
  hide();
}

void MainWindow::on_button_buffer1()
{
    m_TextView.set_buffer(m_refTextBuffer1);
}

void MainWindow::on_button_buffer2()
{
    m_TextView.set_buffer(m_refTextBuffer2);
}


void MainWindow::on_button_close()
{
  hide();
}

/* You can do more complex matching with a handler like this.
 * For instance, you could check for substrings inside the string instead of the start,
 * or you could look for the key in extra model columns as well as the model column that will be displayed.
 * The code here is not actually more complex - it's a reimplementation of the default behaviour.
 *
bool ExampleWindow::on_completion_match(const Glib::ustring& key, const
        Gtk::TreeModel::const_iterator& iter)
{
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;

    Glib::ustring::size_type key_length = key.size();
    Glib::ustring filter_string = row[m_Columns.m_col_name];

    Glib::ustring filter_string_start = filter_string.substr(0, key_length);
    //The key is lower-case, even if the user input is not.
    filter_string_start = filter_string_start.lowercase();

    if(key == filter_string_start)
      return true; //A match was found.
  }

  return false; //No match.
}
*/

void MainWindow::on_completion_action_activated(int index)
{
  type_actions_map::iterator iter = m_CompletionActions.find(index);
  if(iter != m_CompletionActions.end()) //If it's in the map
  {
    Glib::ustring title = iter->second;
    std::cout << "Action selected: " << title << std::endl;
  }
}
