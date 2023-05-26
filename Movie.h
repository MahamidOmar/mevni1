
#ifndef MIVNIIII1_MOVIE_H
#define MIVNIIII1_MOVIE_H

#include "wet1util.h"

#include <memory>

using std::shared_ptr;

class MovieById {
public:
    Genre genre;
    int movie_id;
    bool is_vip;
    double rate;
    int views;
    double sum_rates;
    int num_rates;

    ~MovieById() = default;

    friend bool operator<(shared_ptr<MovieById> &first_movie, shared_ptr<MovieById> &second_movie) {
        return (first_movie->movie_id < second_movie->movie_id);
    }

    friend bool operator>(shared_ptr<MovieById> &first_movie, shared_ptr<MovieById> &second_movie) {
        return (first_movie->movie_id > second_movie->movie_id);
    }

    friend bool operator==(shared_ptr<MovieById> &first_movie, shared_ptr<MovieById> &second_movie) {
        return (first_movie->movie_id == second_movie->movie_id);
    }

    friend bool operator>=(shared_ptr<MovieById> &first_movie, shared_ptr<MovieById> &second_movie) {
        return (first_movie->movie_id >= second_movie->movie_id);
    }


    MovieById(Genre genre1, int movieId, bool isVip, double movieRate = 0, int movieViews = 0) : genre(genre1),
                                                                                                 movie_id(movieId),
                                                                                                 is_vip(isVip),
                                                                                                 rate(movieRate),
                                                                                                 views(movieViews),
                                                                                                 sum_rates(0),
                                                                                                 num_rates(0) {}
};

#endif //MIVNIIII1_MOVIE_H
