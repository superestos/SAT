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

    Conjunction c0{&u};
    Conjunction c1{&f, &t};
    Conjunction c2{&t, &f};
    Conjunction c3{&u, &f};
    Conjunction c4{l3, l4};
    Conjunction c5{&u, &t, &f};

    ASSERT_EQ(c0.eval(), false);
    ASSERT_EQ(c1.eval(), true);
    ASSERT_EQ(c2.eval(), true);
    ASSERT_EQ(c3.eval(), false);
    ASSERT_EQ(c4.eval(), false);
    ASSERT_EQ(c5.eval(), true);
}

