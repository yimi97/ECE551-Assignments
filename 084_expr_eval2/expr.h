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

class SignExpression : public Expression {
 protected:
  Expression * l;
  Expression * r;

 public:
  SignExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual ~SignExpression() {
    delete l;
    delete r;
  }
  virtual std::string toString() const = 0;
  std::string addSign(char sign) const {
    std::stringstream res;
    res << "(" << l->toString() << " " << sign << " " << r->toString() << ")";
    return res.str();
  }
};

class PlusExpression : public SignExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : SignExpression(lhs, rhs) {}
  virtual ~PlusExpression() {}
  virtual std::string toString() const {
    char sign = '+';
    return addSign(sign);
  }
};

class MinusExpression : public SignExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : SignExpression(lhs, rhs) {}
  virtual ~MinusExpression() {}
  virtual std::string toString() const {
    char sign = '-';
    return addSign(sign);
  }
};

class TimesExpression : public SignExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : SignExpression(lhs, rhs) {}
  virtual ~TimesExpression() {}
  virtual std::string toString() const {
    char sign = '*';
    return addSign(sign);
  }
};

class DivExpression : public SignExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : SignExpression(lhs, rhs) {}
  virtual ~DivExpression() {}
  virtual std::string toString() const {
    char sign = '/';
    return addSign(sign);
  }
};
