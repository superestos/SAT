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

TEST(SetValue, AssignmentTest) {
    Variable v[3];
    Literal l0(&v[0]);
    Literal l1(&v[0], true);
    ASSERT_EQ(l0.eval(), false);
    ASSERT_EQ(l1.eval(), false);

    v[0].set(true);
    ASSERT_EQ(l0.eval(), true);
    ASSERT_EQ(l1.eval(), false);

    v[0].set(false);
    ASSERT_EQ(l0.eval(), false);
    ASSERT_EQ(l1.eval(), true);

    v[0].undefine();
    ASSERT_EQ(l0.eval(), false);
    ASSERT_EQ(l1.eval(), false);

    Disjunction single_d({Literal(&v[1], true)});
    CNF single_c({Literal(&v[1], true)});
    ASSERT_EQ(single_d.eval(), false);
    ASSERT_EQ(single_c.eval(), false);

    v[1].set(false);
    ASSERT_EQ(single_d.eval(), true);
    ASSERT_EQ(single_c.eval(), true);

    v[1].set(true);
    ASSERT_EQ(single_d.eval(), false);
    ASSERT_EQ(single_c.eval(), false);
    v[1].undefine();

    Disjunction d({&v[0], &v[1], &v[2]});
    CNF c = Disjunction(&v[0]) & Disjunction(&v[1]);
    ASSERT_EQ(d.eval(), false);
    ASSERT_EQ(c.eval(), false);

    v[0].set(true);
    ASSERT_EQ(d.eval(), true);
    ASSERT_EQ(c.eval(), false);

    v[1].set(true);
    ASSERT_EQ(d.eval(), true);
    ASSERT_EQ(c.eval(), true);
}

TEST(LiteralOperator, AssignmentTest) {
    Variable t = true;
    Variable f = false;

    Literal ltrue = +t;
    Literal lntrue = !t;
    Literal lfalse = +f;
    Literal lnfalse = !f;

    ASSERT_EQ(ltrue.eval(), true);
    ASSERT_EQ(lntrue.eval(), false);
    ASSERT_EQ(lfalse.eval(), false);
    ASSERT_EQ(lnfalse.eval(), true);

    ASSERT_EQ((!lntrue).eval(), true);
    ASSERT_EQ((!lnfalse).eval(), false);
}

TEST(DisjunctionOperator, AssignmentTest) {
    Variable vt = true;
    Variable vf = false;
    Literal t = &vt;
    Literal f = &vf;

    Disjunction d0 = t | f;
    Disjunction d1 = f | f;
    ASSERT_EQ(d0.eval(), true);
    ASSERT_EQ(d1.eval(), false);

    ASSERT_EQ((!d0).eval(), false);
    ASSERT_EQ((!d1).eval(), true);
    ASSERT_EQ((d1 | d0).eval(), true);
    ASSERT_EQ((d0 | d0).eval(), true);
    ASSERT_EQ((d1 | d1).eval(), false);
    ASSERT_EQ((!(d1 | d0)).eval(), false);
    ASSERT_EQ((d0 & d1).eval(), false);
}

TEST(CNFOr, AssignmentTest) {
    Variable v[4];
    for (int i = 0; i < 4; i++) {
        v[i].set(false);
    }
    CNF c0 = Disjunction(+v[0]) & Disjunction(+v[1]);
    CNF c1 = Disjunction(+v[2]) & Disjunction(+v[3]);
    CNF d = c0 | c1;

    ASSERT_EQ(d.eval(), false);
    v[0].set(true);
    ASSERT_EQ(d.eval(), false);
    v[2].set(true);
    ASSERT_EQ(d.eval(), false);
    v[1].set(true);
    ASSERT_EQ(d.eval(), true);
    v[0].set(false);
    ASSERT_EQ(d.eval(), false);
    v[3].set(true);
    ASSERT_EQ(d.eval(), true);
}

TEST(CNFNot, AssignmentTest) {
    Variable v[4];
    for (int i = 0; i < 4; i++) {
        v[i].set(false);
    }
    Disjunction d0 = +v[0] | +v[1] | !v[2];
    Disjunction d1 = +v[1] | +v[2] | +v[3];
    CNF c = !(d0 & d1);

    ASSERT_EQ(c.eval(), true);
    v[2].set(true);
    ASSERT_EQ(c.eval(), true);
    v[0].set(true);
    ASSERT_EQ(c.eval(), false);
    v[2].set(false);
    ASSERT_EQ(c.eval(), true);
    v[3].set(true);
    ASSERT_EQ(c.eval(), false);
    v[3].set(false);
    v[0].set(false);
    ASSERT_EQ(c.eval(), true);
    v[1].set(true);
    ASSERT_EQ(c.eval(), false);
}

TEST(CNFDoubleNegate, AssignmentTest) {
    Variable v[4];
    for (int i = 0; i < 4; i++) {
        v[i].set(false);
    }
    Disjunction d0 = +v[0] | +v[1] | !v[2];
    Disjunction d1 = +v[1] | +v[2] | +v[3];
    CNF c = !(!(d0 & d1));

    ASSERT_EQ(c.eval(), false);
    v[2].set(true);
    ASSERT_EQ(c.eval(), false);
    v[0].set(true);
    ASSERT_EQ(c.eval(), true);
    v[2].set(false);
    ASSERT_EQ(c.eval(), false);
    v[3].set(true);
    ASSERT_EQ(c.eval(), true);
    v[3].set(false);
    v[0].set(false);
    ASSERT_EQ(c.eval(), false);
    v[1].set(true);
    ASSERT_EQ(c.eval(), true);
}