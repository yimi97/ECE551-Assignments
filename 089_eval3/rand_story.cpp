#include "rand_story.hpp"

bool validate_format(std::ifstream & ifs, std::vector<std::string> & myfile) {
  std::string line;
  bool haveChoice = false;
  bool win = false;
  bool lose = false;
  bool pond = false;
  while (getline(ifs, line)) {
    myfile.push_back(line);
    if (!pond) {
      if (line_choice(line) > 0) {
        if (win || lose) {
          std::cerr << "ERROR: read choice then lose or win\n";
          return false;
        }
        haveChoice = true;
      }
      else if (line.find("WIN") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: win&&haveChocie or win&&win or win&&lose\n";
          return false;
        }
        win = true;
      }
      else if (line.find("LOSE") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: lose&&haveChocie or lose&&lose or win&&lose\n";
          return false;
        }
        lose = true;
      }
      else if (line.find('#') == 0) {
        if (!haveChoice && !win && !lose) {
          std::cerr << "ERROR: no section 1\n";
          return false;
        }
        pond = true;
      }
      else {
        std::cerr << "ERROR: other invalid lines between setion 1 and 2\n";
        return false;
      }
    }
  }
  return true;
}

// ====================================== step4 =================================== //

/*
 *@a function used to make the winning path and print result.
 *@param parent: A map used to store the parent map, value is a pair of key's index and parent page.
 *@param win: A reference to the winning page number.
 *@return void.
*/
void make_path(std::map<int, std::map<int, int> > & parent, int & win) {
  // We start from the winning page and record every page's first parent page.
  std::vector<std::vector<int> > path;
  std::vector<int> vec;
  vec.push_back(win);
  path.push_back(vec);
  int key = win;
  while (key != 1) {
    int k = parent[key].begin()->first;   //
    int v = parent[key].begin()->second;  //
    std::vector<int> vec;
    vec.push_back(k);
    vec.push_back(v);
    path.push_back(vec);
    key = k;
  }
  for (size_t i = path.size() - 1; i >= 1; i--) {
    std::cout << "Page " << path[i][0] << " Choice " << path[i][1] << std::endl;
  }
  std::cout << "Page " << path[0][0] << " WIN" << std::endl;
}

/*
 *@a function used to translate child map to parent map.
 *@param child: A map used to store the child map, key is a page number, value is page numbers key's referring to.  
 *@param parent: A map used to store the parent map, key is a page number, value is a pair of key's index and its parent page.
 *@return void.
*/
void make_parent(std::map<int, std::vector<int> > & child,
                 std::map<int, std::map<int, int> > & parent) {
  for (std::map<int, std::vector<int> >::iterator it = child.begin(); it != child.end();
       ++it) {
    for (size_t i = 0; i < it->second.size(); i++) {
      int key = it->second[i];
      if (parent.find(key) == parent.end()) {
        std::map<int, int> value;
        // it->first: its parent; i+1: its index
        value.insert(std::pair<int, int>(it->first, i + 1));
        parent.insert(std::pair<int, std::map<int, int> >(key, value));
      }
      else {
        parent[key].insert((std::pair<int, int>(it->first, i + 1)));
      }
    }
  }
}

/*
 *@a function used to make the child map.
 *@param vector_page: A vector of pointers pointing to pages.
 *@param reachable: A set of int stored the reachable page numbers.
 *@return void.
*/
void make_child(std::vector<Page *> & vector_page, std::set<int> & reachable) {
  int win_num = -1;
  std::map<int, std::vector<int> > child;
  for (std::set<int>::iterator it = reachable.begin(); it != reachable.end(); ++it) {
    Page * p = vector_page[*it - 1];
    if (p->getChoiceNum() != 0) {
      child.insert(std::pair<int, std::vector<int> >(p->getNum(), p->getChoiceVec()));
    }
    // update winning page
    if (p->getWin()) {
      win_num = p->getNum();
    }
  }
  if (win_num == -1) {
    std::cout << "There is no way to win\n";
    return;
  }
  std::map<int, std::map<int, int> > parent;
  make_parent(child, parent);
  make_path(parent, win_num);
}

// ====================================== step3 =================================== //

/*
 *@a function used justify if all pages are reachable.
 *@param vector_page: A vector of pointers pointing to pages.
 *@param page_num: A set of int stored all page numbers.
 *@param diff: A vector of int stored the unreacable page numbers.
 *@return bool.
*/
bool all_reachable(std::vector<Page *> & vector_page,
                   std::set<int> & page_num,
                   std::vector<int> & diff) {
  std::vector<int> check_vec;  // store the queuing page numbers waiting to be checked
  std::set<int> reachable;     // store all reachable page numbers
  check_vec.push_back(1);
  reachable.insert(1);
  while (!check_vec.empty()) {
    int p = check_vec[0];
    if (DEBUG)
      std::cout << "DEBUG: page " << p << " can be reached.\n";
    check_vec.erase(check_vec.begin());
    std::vector<Choice *> c = vector_page[p - 1]->getChoice();
    if (!c.empty()) {
      for (std::vector<Choice *>::iterator it = c.begin(); it != c.end(); ++it) {
        int n = (*it)->getNum();
        if (reachable.find(n) == reachable.end()) {
          check_vec.push_back(n);
          reachable.insert(n);
        }
      }
    }
  }
  if (equal_set(page_num, reachable, diff)) {
    return true;
  }
  else {
    return false;
  }
}

/*
 *@a function used justify if two sets are equal.
 *@param s1: A set of int.
 *@param s2: A set of int.
 *@param diff: A vector of int stored the unreacable page numbers.
 *@return bool.
*/
bool equal_set(std::set<int> & s1, std::set<int> & s2, std::vector<int> & diff) {
  if (s1.size() == s2.size() && equal(s1.begin(), s1.end(), s2.begin())) {
    return true;
  }
  else {
    set_symmetric_difference(
        s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(diff));
    return false;
  }
}

// ====================================== step2 =================================== //

/*
 *@a function used to read a singe page.
 *@param ifs: A reference to ifstream.
 *@param i: A int used to count the page number.
 *@param vector_page: A vector of pointers pointing to pages.
 *@param page_num: A reference to a set of int used to store page numbers.
 *@param choice_num: A reference to a set of int used to store choice numbers.
 *@param page_win: A reference to a bool stored if has WIN page.
 *@param page_lose: A reference to a bool stored if has LOSE page.
 *@return bool.
*/
void read_single_page(std::ifstream & ifs,
                      int i,
                      std::vector<Page *> & vector_page,
                      std::set<int> & page_num,
                      std::set<int> & choice_num,
                      bool & page_win,
                      bool & page_lose) {
  std::string line;
  std::vector<Choice *> vector_choice;
  std::vector<std::string> text;
  bool WIN = false;
  bool LOSE = false;
  bool pond = false;
  while (getline(ifs, line)) {
    parseLine(line, vector_choice, text, WIN, LOSE, pond);
  }
  Page * p = new Page(i, text, vector_choice, WIN, LOSE);
  if (p->getWin()) {
    page_win = true;
  }
  if (p->getLose()) {
    page_lose = true;
  }
  vector_page.push_back(p);
  page_num.insert(i);
  for (size_t j = 0; j < vector_choice.size(); j++) {
    choice_num.insert(vector_choice[j]->getNum());
  }
}

// =====================
void read_single_page(                  // std::ifstream & ifs,
    std::vector<std::string> & myfile,  //
    int i,
    std::vector<Page *> & vector_page,
    std::set<int> & page_num,
    std::set<int> & choice_num,
    bool & page_win,
    bool & page_lose) {
  std::string line;
  std::vector<Choice *> vector_choice;
  std::vector<std::string> text;
  bool WIN = false;
  bool LOSE = false;
  bool pond = false;

  //
  //   while (getline(ifs, line)) {
  //     parseLine(line, vector_choice, text, WIN, LOSE, pond);
  //   }
  //
  for (size_t j = 0; j < myfile.size(); j++) {
    parseLine(myfile[i], vector_choice, text, WIN, LOSE, pond);
  }

  Page * p = new Page(i, text, vector_choice, WIN, LOSE);
  if (p->getWin()) {
    page_win = true;
  }
  if (p->getLose()) {
    page_lose = true;
  }
  vector_page.push_back(p);
  page_num.insert(i);
  for (size_t j = 0; j < vector_choice.size(); j++) {
    choice_num.insert(vector_choice[j]->getNum());
  }
}

/*
 *@a function used to read all pages.
 *@param dir: A directory name string.
 *@param vector_page: A vector of pointers pointing to pages.
 *@param page_num: A reference to a set of int used to store page numbers.
 *@param choice_num: A reference to a set of int used to store choice numbers.
 *@param page_win: A reference to a bool stored if has WIN page.
 *@param page_lose: A reference to a bool stored if has LOSE page.
 *@return void.
*/
void read_pages(std::string & dir,
                std::vector<Page *> & vector_page,
                std::set<int> & page_num,
                std::set<int> & choice_num,
                bool & page_win,
                bool & page_lose) {
  std::ifstream ifs;
  int i = 1;
  while (true) {
    std::string page = dir;
    std::stringstream ss;
    ss << i;
    page.append(ss.str()).append(".txt");
    ifs.open(page.c_str(), std::ifstream::in);
    if (ifs.fail()) {
      break;
    }
    /*
    if (!validate_format(ifs)) {
      ifs.close();
      page.clear();
      free_page(vector_page);
      exit(EXIT_FAILURE);
    }
    ifs.close();
    ifs.open(page.c_str(), std::ifstream::in);
    read_single_page(ifs, i, vector_page, page_num, choice_num, page_win, page_lose);
    */
    std::vector<std::string> myfile;
    bool ifValid = validate_format(ifs, myfile);
    if (!ifValid) {
      free_page(vector_page);
      myfile.clear();
      ifs.close();
      exit(EXIT_FAILURE);
    }
    read_single_page(myfile, i, vector_page, page_num, choice_num, page_win, page_lose);

    ifs.close();
    i++;
  }
}

/*
 *@a function used to verify if pages are valid (step2-4).
 *@param page_num: A reference to a set of int used to store page numbers.
 *@param choice_num: A reference to a set of int used to store choice numbers.
 *@param win: A bool stored if has WIN page.
 *@param lose: A bool stored if has LOSE page.
 *@return bool.
*/
bool validate_page(std::set<int> & page_num,
                   std::set<int> & choice_num,
                   bool win,
                   bool lose) {
  if (compare_set(page_num, choice_num) && win && lose) {
    return true;
  }
  return false;
}

/*
 *@a function used to justify if two sets are equal or only have a "1" differene (step2-4a/4b).
 *@param s1: A set of int.
 *@param s2: A set of int.
 *@return bool.
*/
bool compare_set(std::set<int> & set1, std::set<int> & set2) {
  if (DEBUG) {
    std::cout << "DEBUG: page set includes ";
    for (std::set<int>::iterator it = set1.begin(); it != set1.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "DEBUG: choice set includes ";
    for (std::set<int>::iterator it = set2.begin(); it != set2.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
  std::vector<int> diff;
  // TODO: cite
  set_symmetric_difference(
      set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(diff));
  return (diff.size() == 1 && diff[0] == 1) || (diff.size() == 0);
}

/*
 *@a function used justify if a string is a valid number.
 *@param s: A string of number.
 *@return bool.
*/
bool check_number(std::string s) {
  std::string::iterator it = s.begin();
  while (it != s.end() && isdigit(*it)) {
    ++it;
  }
  return !s.empty() && it == s.end();
}

/*
 *@a function used justify if the number input by user is valid.
 *@param s: A string of number.
 *@param p: A pointer pointing to a page.
 *@return bool.
*/
bool check_number_valid(std::string s, Page * p) {
  if (!check_number(s)) {
    return false;
  }
  int c = atoi(s.c_str());
  if (c >= 1 && c <= p->getChoiceNum()) {
    return true;
  }
  else {
    return false;
  }
}

/*
 *@a function used justify check if we have the exit condition (win of lose).
 *@param p: A pointer pointing to a page.
 *@return bool.
*/
bool check_exit(Page * p) {
  if (p->getWin() || p->getLose()) {
    return true;
  }
  return false;
}

/*
 *@a function used display the whole story.
 *@param page: A reference to a vector of pointer pointing to pages.
 *@return void.
*/
void execute(std::vector<Page *> & page) {
  Page * p = page[0];
  while (true) {
    p->printPage();
    if (check_exit(p)) {
      if (DEBUG)
        std::cout << "DEBUG: exit successfully.\n";
      free_page(page);
      return;
    }
    std::string s;
    while (true) {
      getline(std::cin, s);
      if (check_number_valid(s, p)) {
        int c = atoi(s.c_str());
        int pageNum = p->getChoice()[c - 1]->getNum();
        p = page[pageNum - 1];
        break;
      }
      else {
        std::cout << "That is not a valid choice, please try again\n";
      }
    }
  }
}

/*
 *@a function used free the vector of pages.
 *@param page: A reference to a vector of pointer pointing to pages.
 *@return void.
*/
void free_page(std::vector<Page *> & page) {
  for (size_t i = 0; i < page.size(); i++) {
    delete page[i];
  }
  page.clear();
}

// ====================================== step1 =================================== //

/*
 *@a function used to check if the line is a choice line.
 *@param line: A reference to a line string.
 *@return bool.
*/
int line_choice(const std::string & line) {
  if (line.find(':') == std::string::npos) {
    return false;
  }
  size_t pos = line.find(':');
  std::string num = line.substr(0, pos);
  const char * ptr = num.c_str();
  while (*ptr != '\0') {
    if (!isdigit(*ptr)) {
      //return false;
      return -1;
    }
    ptr++;
  }
  //return true;
  int num_int = atoi(num.c_str());
  return num_int;
}

//read page

/*
 *@a function used read page and check format.
 *@param ifs: A reference to a page ifstream.
 *@return bool.
*/
bool validate_format(std::ifstream & ifs) {
  std::string line;
  bool haveChoice = false;
  std::set<int> choice_set;
  bool win = false;
  bool lose = false;
  bool pond = false;
  while (getline(ifs, line)) {
    if (!pond) {
      int ifChoice = line_choice(line);
      if (ifChoice > 0) {
        if (win || lose) {
          std::cerr << "ERROR: read choice then lose or win\n";
          return false;
        }
        if (choice_set.find(ifChoice) != choice_set.end()) {
          std::cerr << "ERROR: duplicate choice numbers\n";
          return false;
        }
        choice_set.insert(ifChoice);
        haveChoice = true;
      }
      else if (line.find("WIN") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: win&&haveChocie or win&&win or win&&lose\n";
          return false;
        }
        win = true;
      }
      else if (line.find("LOSE") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: lose&&haveChocie or lose&&lose or win&&lose\n";
          return false;
        }
        lose = true;
      }
      else if (line.find('#') == 0) {
        if (!haveChoice && !win && !lose) {
          std::cerr << "ERROR: no section 1\n";
          return false;
        }
        pond = true;
      }
      else {
        std::cerr << "ERROR: other invalid lines between setion 1 and 2\n";
        return false;
      }
    }
  }
  return true;
}

/*
 *@a function used to parse each line.
 *@param line: A reference to a line string.
 *@param vector_choice: A reference to a vector of pointers pointing to choices.
 *@param text: A reference to a vector of string used to store text lines.
 *@param win: A reference to a bool stored if has WIN line.
 *@param lose: A reference to a bool stored if has LOSE line.
 *@param pond: A reference to a bool stored if has # line.
 *@return void.
*/
void parseLine(std::string & line,
               std::vector<Choice *> & vector_choice,
               std::vector<std::string> & text,
               bool & win,
               bool & lose,
               bool & pond) {
  if (!pond && line_choice(line)) {
    size_t pos = line.find(':');
    std::string n = line.substr(0, pos);
    std::string c = line.substr(pos + 1);
    Choice * cho = new Choice(atoi(n.c_str()), c);
    vector_choice.push_back(cho);
  }
  else if (line.find("WIN") == 0) {
    win = true;
  }
  else if (line.find("LOSE") == 0) {
    lose = true;
  }
  else if (line.find('#') == 0) {
    pond = true;
  }
  else {
    text.push_back(line);
  }
}

// =================================== class method ================================= //

Choice & Choice::operator=(const Choice & rhs) {
  if (this != &rhs) {
    num = rhs.num;
    c = rhs.c;
  }
  return *this;
}

Page::Page(int n,
           std::vector<std::string> & t,
           std::vector<Choice *> & c,
           bool w,
           bool l) :
    num(n),
    text(t),
    choices(),
    win(w),
    lose(l) {
  for (size_t i = 0; i < c.size(); i++) {
    choices.push_back(c[i]);
  }
}

Page::~Page() {
  for (int i = 0; i < getChoiceNum(); i++) {
    delete choices[i];
  }
}

Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < getChoiceNum(); i++) {
      delete choices[i];
    }
    num = rhs.getNum();  //private??? rhs.num; or rhs.getNum();?
    text = rhs.getText();
    win = rhs.getWin();
    lose = rhs.getLose();
    for (int i = 0; i < rhs.getChoiceNum(); i++) {
      choices.push_back(rhs.getChoice()[i]);
    }
  }
  return *this;
}

std::vector<int> Page::getChoiceVec() const {
  std::vector<int> v;
  for (std::vector<Choice *>::const_iterator it = choices.begin(); it != choi\
ces.end();
       ++it) {
    v.push_back((*it)->getNum());
  }
  return v;
}

void Page::printText() const {
  for (std::vector<std::string>::const_iterator it = text.begin(); it != text.end();
       ++it) {
    std::cout << *it << "\n";
  }
}

void Page::printPage() const {
  printText();
  if (win) {
    std::cout << "\n"
              << "Congratulations! You have won. Hooray!\n";
  }
  else if (lose) {
    std::cout << "\n";
    std::cout << "Sorry, you have lost. Better luck next time!\n";
  }
  else {
    std::cout << "\n"
              << "What would you like to do?\n\n";
    if (!choices.empty()) {
      int i = 1;
      for (std::vector<Choice *>::const_iterator it = choices.begin();
           it != choices.end();
           ++it) {
        std::cout << " " << i << ". ";
        if (DEBUG) {
          std::cout << "DEBUG: "
                    << " " << i << ". "
                    << "(" << (*it)->getNum() << ")";
        }
        (*it)->printChoice();
        i++;
      }
    }  //else wrong
  }
}
