#include "clause.h"

#include "gtest/gtest.h"

TEST(Literal, AssignmentTest) {
    Variable v0;
    Variable v1 = true;
    Variable v2 = false;

    Literal l0(&v0, false);
    Literal l1(&v0, true);
    Literal l2(&v1, false);
    Literal l3(&v1, true);
    Literal l4(&v2, false);
    Literal l5(&v2, true);

    ASSERT_EQ(l0.eval(), false);
    ASSERT_EQ(l1.eval(), false);
    ASSERT_EQ(l2.eval(), true);
    ASSERT_EQ(l3.eval(), false);
    ASSERT_EQ(l4.eval(), false);
    ASSERT_EQ(l5.eval(), true);
}
