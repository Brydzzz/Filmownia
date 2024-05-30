#include <vector>

#include "role.h"

class Logged : public Role {
    std::vector<Review> reviews;

   public:
    Logged() = default;
    Logged(Review const& review);
    Logged(
        Logged const& l_user);  // moze się przydać, jeśli nie to do skasowania
    Logged(std::initializer_list<Review> revs);
    const std::vector<Review>& getReviews() const;
    void add_review(const Review& new_review);
    void delete_review(const Review& to_delete);
};