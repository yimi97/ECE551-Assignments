#include "choice.cpp"

class Page {
 private:
  int num;
  std::vector<std::string> text;
  std::vector<Choice *> choices;
  bool win;
  bool lose;

 public:
  Page() : num(), text(), choices(), win(false), lose(false) {}
  Page(int n, std::vector<std::string> & t, std::vector<Choice *> & c, bool w, bool l);
  ~Page();
  Page & operator=(const Page & rhs);
  bool getWin() const { return win; }
  bool getLose() const { return lose; }
  int getNum() const { return num; }
  std::vector<std::string> getText() const { return text; }
  int getChoiceNum() const { return choices.size(); }
  std::vector<Choice *> getChoice() const { return choices; }
  std::vector<int> getChoiceVec() const;
  void printText() const;
  void printPage() const;
};
