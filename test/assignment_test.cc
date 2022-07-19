#include "clause.h"

#include "gtest/gtest.h"

TEST(Assignment, AssignmentTest) {
    Variable u;
    Variable t = true;
    Variable f = false;

    Literal l0(&u, false);
    Literal l1(&u, true);
    Literal l2(&t, false);
    Literal l3(&t, true);
    Literal l4(&f, false);
    Literal l5(&f, true);

    ASSERT_EQ(l0.eval(), false);
    ASSERT_EQ(l1.eval(), false);
    ASSERT_EQ(l2.eval(), true);
    ASSERT_EQ(l3.eval(), false);
    ASSERT_EQ(l4.eval(), false);
    ASSERT_EQ(l5.eval(), true);

    Disjunction d0{&u};
    Disjunction d1{&f, &t};
    Disjunction d2{&t, &f};
    Disjunction d3{&u, &f};
    Disjunction d4{l3, l4};
    Disjunction d5{&u, &t, &f};
    Disjunction d6{&t};

    ASSERT_EQ(d0.eval(), false);
    ASSERT_EQ(d1.eval(), true);
    ASSERT_EQ(d2.eval(), true);
    ASSERT_EQ(d3.eval(), false);
    ASSERT_EQ(d4.eval(), false);
    ASSERT_EQ(d5.eval(), true);
    ASSERT_EQ(d6.eval(), true);

    CNF c0{d0};
    CNF c1{d6};
    CNF c2{d1, d2};
    CNF c3{d2, d3};
    CNF c4{d2, d5, d6};

    ASSERT_EQ(c0.eval(), false);
    ASSERT_EQ(c1.eval(), true);
    ASSERT_EQ(c2.eval(), true);
    ASSERT_EQ(c3.eval(), false);
    ASSERT_EQ(c4.eval(), true);
}

TEST(Operator, AssignmentTest) {
    Variable t = true;
    Variable f = false;

    Literal ltrue = +t;
    Literal lntrue = -t;
    Literal lfalse = +f;
    Literal lnfalse = -f;

    ASSERT_EQ(ltrue.eval(), true);
    ASSERT_EQ(lntrue.eval(), false);
    ASSERT_EQ(lfalse.eval(), false);
    ASSERT_EQ(lnfalse.eval(), true);
}
