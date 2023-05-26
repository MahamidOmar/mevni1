//
// Created by ebrah on 24/05/2023.
//

#ifndef MIVNIIII1_MOVIERATE_H
#define MIVNIIII1_MOVIERATE_H

#include "wet1util.h"

#include <memory>
using std::shared_ptr;

class MovieByRate{
public:
    Genre genre;
    int movie_id;
    bool is_vip;
    double rate;
    int views;
    double sum_rates;
    int num_rates;

    MovieByRate(Genre genre1, int movieId, bool isVip, double movieRate = 0, int movieViews = 0,int numRates=0,double sumRates=0) : genre(genre1),
    movie_id(movieId),
    is_vip(isVip),
    rate(movieRate),
    views(movieViews),sum_rates(sumRates) , num_rates(numRates) {}

    ~MovieByRate()=default;
    friend bool operator<(shared_ptr<MovieByRate>& first_movie ,shared_ptr<MovieByRate>& second_movie){
        if (first_movie->rate < second_movie->rate){
            return true;
        }
        else{
            if (first_movie->rate == second_movie->rate)
            {
                if(first_movie->views< second_movie->views){
                    return true;
                } else if(first_movie->views == second_movie->views){
                    if (first_movie->movie_id > second_movie->movie_id)
                        return true;
                }
            }
        }
        return false;
    }

    friend bool operator>(shared_ptr<MovieByRate>& first_movie ,shared_ptr<MovieByRate>& second_movie){
        if (first_movie->rate > second_movie->rate){
            return true;
        }
        else{
            if (first_movie->rate == second_movie->rate)
            {
                if(first_movie->views> second_movie->views){
                    return true;
                } else if(first_movie->views == second_movie->views){
                    if (first_movie->movie_id < second_movie->movie_id)
                        return true;
                }
            }
        }
        return false;
    }

    friend bool operator==(shared_ptr<MovieByRate>& first_movie ,shared_ptr<MovieByRate>& second_movie){
        if (first_movie->rate == second_movie->rate && first_movie->movie_id == second_movie->movie_id){
            return true;
        }
        return false;
    }

    friend bool operator>=(shared_ptr<MovieByRate>& first_movie ,shared_ptr<MovieByRate>& second_movie){
        if (first_movie == second_movie || first_movie > second_movie){
            return true;
        }
        return false;
    }
};

#endif //MIVNIIII1_MOVIERATE_H
