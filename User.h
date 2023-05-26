
#ifndef MIVNIIII1_USER_H
#define MIVNIIII1_USER_H

#define NUM_MOVIES_TYPES (4)

#include <memory>
using std::shared_ptr;

class User{
public:
    int user_id;
    int group_id;
    int viewers[NUM_MOVIES_TYPES];
    int late_movies_group[NUM_MOVIES_TYPES];
    ///* viewers[0] = viewers of COMEDY, viewers[1] = viewers of DRAMA
    /// viewers[2] = viewers of ACTION, viewers[3] = viewers of FANTASY *///
    bool is_vip;
    User(int userId , int groupId , bool isVip): user_id(userId), group_id(groupId),is_vip(isVip){
        for (int i=0;i<NUM_MOVIES_TYPES ; i++) {
            viewers[i]=0;
            late_movies_group[i]=0;
        }
    }
    ~User()=default;

    friend bool operator<(shared_ptr<User>& first_user ,shared_ptr<User>& second_user){
        return (first_user->user_id<second_user->user_id);
    }

    friend bool operator>(shared_ptr<User>& first_user ,shared_ptr<User>& second_user){
        return (first_user->user_id>second_user->user_id);
    }

    friend bool operator==(shared_ptr<User>& first_user ,shared_ptr<User>& second_user){
        return (first_user->user_id==second_user->user_id);
    }

    friend bool operator>=(shared_ptr<User>& first_user ,shared_ptr<User>& second_user){
        return (first_user->user_id>=second_user->user_id);
    }
};


#endif //MIVNIIII1_USER_H
