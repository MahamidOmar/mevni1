
#ifndef MIVNIIII1_GROUP_H
#define MIVNIIII1_GROUP_H
#define NUM_MOVIES_TYPES (4)

#include "User.h"
#include "tree.h"
#include <memory>
using std::shared_ptr;

class Group{
public:
    int group_id;
    int viewers[NUM_MOVIES_TYPES];
    ///* viewers[0] = viewers of COMEDY, viewers[1] = viewers of DRAMA
    /// viewers[2] = viewers of ACTION, viewers[3] = viewers of FANTASY *///
    int sum_of_all_viewers[NUM_MOVIES_TYPES];
    ///* sum_of_all_viewers[0] = viewers of COMEDY, sum_of_all_viewers[1] = viewers of DRAMA
    /// sum_of_all_viewers[2] = viewers of ACTION, sum_of_all_viewers[3] = viewers of FANTASY *///
    AVLtree<shared_ptr<User>,shared_ptr<User>>* users_tree;
    int num_vip_users;
    Group(int groupId):group_id(groupId),num_vip_users(0){
        for (int i = 0; i < NUM_MOVIES_TYPES; ++i) {
            viewers[i]=0;
            sum_of_all_viewers[i]=0;
        }
        users_tree=new AVLtree<shared_ptr<User>,shared_ptr<User>>;
    }
    ~Group(){
        delete users_tree;
        users_tree= nullptr;
    }
    friend bool operator<(shared_ptr<Group>& first_group ,shared_ptr<Group>& second_group){
        return (first_group->group_id < second_group->group_id);
    }

    friend bool operator>(shared_ptr<Group>& first_group ,shared_ptr<Group>& second_group){
        return (first_group->group_id > second_group->group_id);
    }

    friend bool operator==(shared_ptr<Group>& first_group ,shared_ptr<Group>& second_group){
        return (first_group->group_id == second_group->group_id);
    }

    friend bool operator>=(shared_ptr<Group>& first_group ,shared_ptr<Group>& second_group){
        return (first_group->group_id >= second_group->group_id);
    }

};

#endif //MIVNIIII1_GROUP_H
