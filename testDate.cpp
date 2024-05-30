#include <gtest/gtest.h>

#include "date.h"
TEST(DateTest, constructor) {
    Date date(17, 3, 2024);
    ASSERT_EQ(date.getDay(), 17);
    ASSERT_EQ(date.getMonth(), 3);
    ASSERT_EQ(date.getYear(), 2024);
}

TEST(DateTest, ctor_invalid_day) {
    ASSERT_THROW(Date(45, 7, 2023), std::exception);
}

TEST(DateTest, ctor_invalid_day_zero) {
    ASSERT_THROW(Date(0, 7, 2023), std::exception);
}

TEST(DateTest, ctor_invalid_day_month_with_30_days) {
    ASSERT_THROW(Date(31, 4, 2023), std::exception);
}

TEST(DateTest, ctor_invalid_day_february) {
    ASSERT_THROW(Date(29, 2, 2023), std::exception);
}

TEST(DateTest, ctor_leap_year) { ASSERT_NO_THROW(Date(29, 2, 2024)); }

TEST(DateTest, ctor_invalid_month) {
    ASSERT_THROW(Date(29, 13, 2023), std::exception);
}

TEST(DateTest, ctor_invalid_month_zero) {
    ASSERT_THROW(Date(29, 0, 2023), std::exception);
}

TEST(DateTest, isEqualOrGreater_typical_true) {
    Date old_date(12, 6, 2012);
    Date recent_date(17, 9, 2024);
    ASSERT_EQ(recent_date.isEqualOrGreater(old_date), true);
}

TEST(DateTest, isEqualOrGreater_typical_false) {
    Date old_date(12, 6, 2012);
    Date recent_date(17, 9, 2024);
    ASSERT_EQ(old_date.isEqualOrGreater(recent_date), false);
}

TEST(DateTest, isEqualOrGreater_typical_same_year_true) {
    Date old_date(12, 6, 2012);
    Date recent_date(17, 9, 2012);
    ASSERT_EQ(recent_date.isEqualOrGreater(old_date), true);
}

TEST(DateTest, isEqualOrGreater_typical_same_year_false) {
    Date old_date(12, 6, 2012);
    Date recent_date(17, 9, 2012);
    ASSERT_EQ(old_date.isEqualOrGreater(recent_date), false);
}

TEST(DateTest, isEqualOrGreater_typical_same_month_true) {
    Date old_date(12, 6, 2012);
    Date recent_date(17, 6, 2012);
    ASSERT_EQ(recent_date.isEqualOrGreater(old_date), true);
}

TEST(DateTest, isEqualOrGreater_typical_same_month_false) {
    Date old_date(12, 6, 2012);
    Date recent_date(17, 6, 2012);
    ASSERT_EQ(old_date.isEqualOrGreater(recent_date), false);
}

TEST(DateTest, isEqualOrGreater_typical_same_day) {
    Date old_date(12, 6, 2012);
    Date recent_date(12, 6, 2012);
    ASSERT_EQ(recent_date.isEqualOrGreater(old_date), true);
}

TEST(DateTest, out_operator) {
    Date d(6, 11, 1988);
    std::stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), "06/11/1988");
}
