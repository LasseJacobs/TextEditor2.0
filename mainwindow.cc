#include "mainwindow.h"
#include "scrollabletext.h"
#include "closabletab.h"
#include <iostream>

#define MAX_LOG_SIZE 40

MainWindow* MainWindow::m_instance = NULL;

MainWindow::MainWindow() :  m_vBox(Gtk::ORIENTATION_VERTICAL),
                            m_hBox(Gtk::ORIENTATION_HORIZONTAL),
                            m_statusBox(Gtk::ORIENTATION_HORIZONTAL),
                            m_buttonRun(" Run "),
                            m_cmdHandler(this)
{
    set_title("Editor");
    set_border_width(3);
    set_default_size(1024, 576);

    add(m_vBox);

    AddCommandLine();
    AddTabs();
    AddStatusBar();

    StartUpTab();

    show_all_children();
}

MainWindow* MainWindow::Instance()
{
    if(m_instance == NULL)
        m_instance = new MainWindow();

    return m_instance;
}

void MainWindow::AddCommandLine()
{
    m_vBox.add(m_hBox);
    m_hBox.pack_start(m_entry, Gtk::PACK_EXPAND_WIDGET);

    //Connect signals
    m_entry.signal_activate().connect(sigc::mem_fun(*this,
                &MainWindow::OnCommand) );
    m_buttonRun.signal_clicked().connect( sigc::mem_fun(*this,
                &MainWindow::OnButtonRun) );

    //Confiquiring run button
    m_hBox.pack_start(m_buttonRun, Gtk::PACK_SHRINK);
    m_buttonRun.set_can_default();
    m_buttonRun.grab_default();

    m_hBox.set_spacing(8);
    m_hBox.set_margin_bottom(5);

    AddCompletionSet();
}

void MainWindow::AddTabs()
{
    //Add buttons:
    m_vBox.pack_start(m_notebook);
}

void MainWindow::StartUpTab()
{
    m_notebook.AddNewTab();
}

void MainWindow::AddStatusBar()
{
    m_vBox.add(m_statusBox);
    //This is the output log
    m_statusBox.pack_start(m_outputLog, Gtk::PACK_SHRINK);
}

MainWindow::~MainWindow()
{

}

void MainWindow::OnButtonRun()
{
    std::cout << GetCurrentFileName() << std::endl;
}

/* You can do more complex matching with a handler like this.
 * For instance, you could check for substrings inside the string
 * instead of the start,
 * or you could look for the key in extra model columns
 * as well as the model column that will be displayed.
 * The code here is not actually more complex - it's a reimplementation
 * of the default behaviour.
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

void MainWindow::AddCompletionSet()
{
    //Add an EntryCompletion:
    Glib::RefPtr<Gtk::EntryCompletion> completion
                            = Gtk::EntryCompletion::create();
    m_entry.set_completion(completion);

    //Create and fill the completion's filter model
    Glib::RefPtr<Gtk::ListStore> refCompletionModel
                            = Gtk::ListStore::create(m_Columns);
    completion->set_model(refCompletionModel);

    // For more complex comparisons, use a filter match callback, like this.
    // See the comment below for more details:
    //completion->set_match_func( sigc::mem_fun(*this,
    //&ExampleWindow::on_completion_match) );

    //Fill the TreeView's model
    Gtk::TreeModel::Row row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "Find ";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_name] = "Replace ";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "Save";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 4;
    row[m_Columns.m_col_name] = "New File";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 5;
    row[m_Columns.m_col_name] = "Save As ";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 6;
    row[m_Columns.m_col_name] = "Open ";

    row = *(refCompletionModel->append());
    row[m_Columns.m_col_id] = 7;
    row[m_Columns.m_col_name] = "Close File";

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
    completion->signal_action_activated().connect( sigc::mem_fun(*this,
             &MainWindow::OnCompletion) );
    */
}

void MainWindow::OnCommand()
{
    std::string strcmd = Glib::locale_from_utf8(m_entry.get_text());
    m_cmdHandler.ExecuteCommand(strcmd);
}

void MainWindow::Log(const char* message)
{
    m_outputLog.unset_color(Gtk::STATE_FLAG_NORMAL);

    char statusBuffer[MAX_LOG_SIZE];
    if(strlen(message) > MAX_LOG_SIZE-1)
    {
        strncpy(statusBuffer, message, MAX_LOG_SIZE-3);
        strcat(statusBuffer, "...");
    }
    else
    {
        strncpy(statusBuffer, message, MAX_LOG_SIZE);
    }
    m_outputLog.set_text(statusBuffer);
}

void MainWindow::ErrorLog(const char* message)
{
    m_outputLog.override_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);

    char statusBuffer[MAX_LOG_SIZE];
    if(strlen(message) > MAX_LOG_SIZE-1)
    {
        strncpy(statusBuffer, message, MAX_LOG_SIZE-3);
        strcat(statusBuffer, "...");
    }
    else
    {
        strncpy(statusBuffer, message, MAX_LOG_SIZE);
    }
    m_outputLog.set_text(statusBuffer);
}


//Interface
void MainWindow::SetCurrentBuffer(  const std::string& filename,
                                    const std::string& content)
{
    m_notebook.SetCurrentBuffer(filename, content);
}

std::string MainWindow::GetCurrentBuffer() const
{
    return m_notebook.GetCurrentBuffer();
}

std::string MainWindow::GetCurrentFileName() const
{
    return m_notebook.GetCurrentFileName();
}
