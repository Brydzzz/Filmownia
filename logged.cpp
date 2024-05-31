#include "logged.h"

#include <algorithm>
#include <iostream>

const std::vector<Review> &Logged::getReviews() const { return reviews; }
void Logged::add_review(const Review &new_review)
{
    reviews.push_back(new_review);
}
void Logged::delete_review(const Review &to_delete)
{
    auto it = std::find_if(
        reviews.begin(), reviews.end(),
        [&to_delete](const Review &review)
        { return review == to_delete; });

    if (it != reviews.end())
    {
        reviews.erase(it); // Usuń element, jeśli został znaleziony
    }
    else
    {
        // Element nie został znaleziony
        std::cout << "Review not found" << std::endl;
    }
}