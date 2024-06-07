#pragma once
#include <vector>

#include "review.h"
#include "role.h"
#include "user.h"
class Logged : public Role {
    std::vector<Review> reviews;

   public:
    Logged(User *us) : Role(us) {}
    Logged(User *us, const Review &review) : Role(us) {
        reviews.push_back(review);
    }
    // Logged(User *us, const Logged &l_user) : Role(us),
    // reviews(l_user.reviews) {}
    Logged(User *us, std::initializer_list<Review> revs)
        : Role(us), reviews(revs) {}
    Logged(User *us, std::vector<Review> revs) : Role(us), reviews(revs) {}
    void setReviews(std::vector<Review> revs) { reviews = revs; }
    const std::vector<Review> &getReviews() const;
    void add_review(const Review &new_review);
    void delete_review(const Review &to_delete);
};