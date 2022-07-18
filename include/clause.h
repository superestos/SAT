#include <vector>
#include <initializer_list>

class Variable {
public:
friend class Literal;

    Variable(bool value) {
        set(value);
    }

    Variable() {}

    void set(bool value) {
        this->value = value;
        this->defined = true;
    }

    void undefine() {
        this->defined = false;
    }

private:
    bool defined{false};
    bool value{false};
};

class Literal {
public:
    Literal(Variable *var, bool neg = false): var{var}, neg{neg} {}

    bool eval() {
        return var->defined? (neg ^ var->value): false;
    }

private:
    Variable *var;
    bool neg;
};

class Disjunction {
public:
    Disjunction(std::initializer_list<Literal> list): literals{list} {}

    bool eval() {
        for (Literal &literal: literals) {
            if (literal.eval()) {
                return true;
            }
        }

        return false;
    }

private:
    std::vector<Literal> literals;
};

class CNF {
public:
    CNF(std::initializer_list<Disjunction> list): formula{list} {}

    bool eval() {
        for (Disjunction &conjunction: formula) {
            if (!conjunction.eval()) {
                return false;
            }
        }

        return true;
    }

private:
    std::vector<Disjunction> formula;
};
