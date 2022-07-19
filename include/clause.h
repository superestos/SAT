#include <vector>
#include <initializer_list>

class Literal;
class Disjunction;
class CNF;

class Variable {
public:
friend class Literal;

    Variable(bool value) {
        set(value);
    }

    Variable(): defined{false}, value{false} {}

    void set(bool value) {
        this->value = value;
        this->defined = true;
    }

    void undefine() {
        this->defined = false;
    }

    Literal operator+();
    Literal operator~();

private:
    bool defined;
    bool value;
};

class Literal {
public:
    Literal(Variable *var, bool neg = false): var{var}, neg{neg} {}

    bool eval() {
        return var->defined? (neg ^ var->value): false;
    }

    Literal operator~();
    Disjunction operator|(Literal o);

private:
    Variable *var;
    bool neg;
};

class Disjunction {
public:
    Disjunction(Literal literal) {
        literals.emplace_back(literal);
    }

    Disjunction(std::initializer_list<Literal> list): literals{list} {}

    bool eval() {
        for (Literal &literal: literals) {
            if (literal.eval()) {
                return true;
            }
        }

        return false;
    }

    CNF operator&(Disjunction o);

private:
    std::vector<Literal> literals;
};

class CNF {
public:
    CNF(Disjunction disjunction) {
        formula.emplace_back(disjunction);
    }

    CNF(std::initializer_list<Disjunction> list): formula{list} {}

    bool eval() {
        for (Disjunction &disjunction: formula) {
            if (!disjunction.eval()) {
                return false;
            }
        }

        return true;
    }

private:
    std::vector<Disjunction> formula;
};

Literal Variable::operator+() {
    return Literal(this);
}

Literal Variable::operator~() {
    return Literal(this, true);
}

Literal Literal::operator~() {
    return Literal(this->var, !this->neg);
}

Disjunction Literal::operator|(Literal o) {
    return Disjunction({*this, o});
}

CNF Disjunction::operator&(Disjunction o) {
    return CNF({*this, o});
}
