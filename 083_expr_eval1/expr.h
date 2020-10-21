#include <sstream>
#include <string>
class Expression {
 public:
  Expression() {}
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream res;
    res << num;
    return res.str();
  }
};

class PlusExpression : public Expression {
 private:
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
  virtual std::string toString() const {
    std::stringstream res;
    res << "(" << l->toString() << " + " << r->toString() << ")";
    return res.str();
  }
};
