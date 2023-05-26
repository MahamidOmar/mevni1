#include "StreamingDBa1.h"

streaming_database::streaming_database() {
    all_users_tree = new AVLtree<shared_ptr<User>,shared_ptr<User>>;
    all_groups_tree = new AVLtree<shared_ptr<Group>,shared_ptr<Group>>;
    not_empty_groups_tree = new AVLtree<shared_ptr<Group >,shared_ptr<Group >>;
    all_movies_by_id = new AVLtree<shared_ptr<MovieById>,shared_ptr<MovieById>>;
    all_movies_by_rate = new AVLtree<shared_ptr<MovieByRate>,shared_ptr<MovieByRate>>;
    comedy_movies_by_rate = new AVLtree<shared_ptr<MovieByRate>,shared_ptr<MovieByRate>>;
    drama_movies_by_rate = new AVLtree<shared_ptr<MovieByRate>,shared_ptr<MovieByRate>>;
    action_movies_by_rate = new AVLtree<shared_ptr<MovieByRate>,shared_ptr<MovieByRate>>;
    fantasy_movies_by_rate = new AVLtree<shared_ptr<MovieByRate>,shared_ptr<MovieByRate>>;
    for (int i = 0; i < NUM_MOVIES_TYPES+1; ++i) {
        num_movies[i]=0;
        num_movies[i]=0;
    }
    // TODO: Your code goes here
}
//
streaming_database::~streaming_database() {
    delete all_users_tree;
    delete all_groups_tree;
    delete not_empty_groups_tree;
    delete all_movies_by_id;
    delete all_movies_by_rate;
    delete comedy_movies_by_rate;
    delete drama_movies_by_rate;
    delete action_movies_by_rate;
    delete fantasy_movies_by_rate;
    all_users_tree = nullptr;
    all_groups_tree = nullptr;
    not_empty_groups_tree = nullptr;
    all_movies_by_id = nullptr;
    all_movies_by_rate = nullptr;
    comedy_movies_by_rate = nullptr;
    drama_movies_by_rate = nullptr;
    action_movies_by_rate = nullptr;
    fantasy_movies_by_rate = nullptr;
    // TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly) {
    if (movieId <= 0 || genre == Genre::NONE || views < 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<MovieById> new_movie(new MovieById(genre, movieId, vipOnly, 0, views));
    if (!new_movie) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (all_movies_by_id->isContain(new_movie)) {
        return StatusType::FAILURE;
    }
    shared_ptr<MovieByRate> new_movie_by_rate(new MovieByRate(genre, movieId, vipOnly, 0, views,0));
    if (!new_movie_by_rate) {
        return StatusType::ALLOCATION_ERROR;
    }
    all_movies_by_id->insert(new_movie,new_movie);
    all_movies_by_rate->insert(new_movie_by_rate,new_movie_by_rate);
    shared_ptr<MovieByRate> new_movie_by_rate1(new MovieByRate(genre, movieId, vipOnly, 0, views,0));
    switch (genre) {
        case Genre::COMEDY:
            comedy_movies_by_rate->insert(new_movie_by_rate1,new_movie_by_rate1);
            num_movies[0]++;
            break;
        case Genre::DRAMA:
            //shared_ptr<MovieByRate> new_movie_by_rate1(new MovieByRate(genre, movieId, vipOnly, 0, views));
            drama_movies_by_rate->insert(new_movie_by_rate1,new_movie_by_rate1);
            num_movies[1]++;
            break;
        case Genre::ACTION:
            //shared_ptr<MovieByRate> new_movie_by_rate2(new MovieByRate(genre, movieId, vipOnly, 0, views));
            action_movies_by_rate->insert(new_movie_by_rate1,new_movie_by_rate1);
            num_movies[2]++;
            break;
        case Genre::FANTASY:
            //shared_ptr<MovieByRate> new_movie_by_rate3(new MovieByRate(genre, movieId, vipOnly, 0, views));
            fantasy_movies_by_rate->insert(new_movie_by_rate1,new_movie_by_rate1);
            num_movies[3]++;
            break;
        default:
            break;
    }
    num_movies[4]++;
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId) {
    if (movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<MovieById> check_movie(new MovieById(Genre::COMEDY, movieId, 0, 0, 0));
    if (!check_movie) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_movies_by_id->isContain(check_movie)) {
        return StatusType::FAILURE;
    }
    AVLnode<shared_ptr<MovieById>,shared_ptr<MovieById>>* curr_movie = all_movies_by_id->find(check_movie);
    shared_ptr<MovieByRate> check_movie_by_rate(
            new MovieByRate(curr_movie->key->genre, movieId, curr_movie->key->is_vip, curr_movie->key->rate,
                            curr_movie->key->views));
    if (!check_movie_by_rate) {
        return StatusType::ALLOCATION_ERROR;
    }
    Genre curr_genre = curr_movie->key->genre;
    switch (curr_genre) {
        case Genre::COMEDY:
            comedy_movies_by_rate->deleteKey(check_movie_by_rate);
            num_movies[0]--;
            break;
        case Genre::DRAMA:
            drama_movies_by_rate->deleteKey(check_movie_by_rate);
            num_movies[1]--;
            break;
        case Genre::ACTION:
            action_movies_by_rate->deleteKey(check_movie_by_rate);
            num_movies[2]--;
            break;
        case Genre::FANTASY:
            fantasy_movies_by_rate->deleteKey(check_movie_by_rate);
            num_movies[3]--;
            break;
        default:
            break;
    }
    all_movies_by_id->deleteKey(curr_movie->key);
    all_movies_by_rate->deleteKey(check_movie_by_rate);
    num_movies[4]--;
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip) {
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<User> new_user(new User(userId, 0, isVip));
    if (!new_user) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (all_users_tree->isContain(new_user)) {
        return StatusType::FAILURE;
    }
    all_users_tree->insert(new_user,new_user);
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId) {
    if (userId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<User> check_user(new User(userId, 0, false));
    if (!check_user) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_users_tree->isContain(check_user)) {
        return StatusType::FAILURE;
    }
    if (all_users_tree->find(check_user)->key->group_id!=0){
        shared_ptr<Group> new_group(new Group(all_users_tree->find(check_user)->key->group_id));
        if (!new_group) {
            return StatusType::ALLOCATION_ERROR;
        }
        if (all_users_tree->find(check_user)->key->is_vip){
            not_empty_groups_tree->find(new_group)->key->num_vip_users--;
        }
        for (int i = 0; i < NUM_MOVIES_TYPES; ++i) {
            not_empty_groups_tree->find(new_group)->key->sum_of_all_viewers[i]-=check_user->late_movies_group[i];
        }

        not_empty_groups_tree->find(new_group)->key->users_tree->deleteKey(check_user);
        if (not_empty_groups_tree->find(new_group)->key->users_tree->treesize==0){
            not_empty_groups_tree->deleteKey(new_group);
        }
    }
    all_users_tree->deleteKey(check_user);
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId) {
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Group> new_group(new Group(groupId));
    if (!new_group) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (all_groups_tree->isContain(new_group)) {
        return StatusType::FAILURE;
    }
    all_groups_tree->insert(new_group,new_group);
    return StatusType::SUCCESS;
}

static void updateGroupIdToUsers(AVLnode<shared_ptr<User>,shared_ptr<User>>* node,shared_ptr<Group> group){
    if (node == nullptr) {
        return;
    }
    updateGroupIdToUsers(node->left_son,group);
    node->key->group_id=0;
    for (int i = 0; i < NUM_MOVIES_TYPES; ++i) {
        node->key->late_movies_group[i]+=group->viewers[i];
        node->key->viewers[i]=node->key->late_movies_group[i];
    }
    updateGroupIdToUsers(node->Right_son,group);
}

StatusType streaming_database::remove_group(int groupId) {
    if (groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Group> new_group(new Group(groupId));
    if (!new_group) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!this->all_groups_tree->isContain(new_group)) {
        return StatusType::FAILURE;
    }
    if (not_empty_groups_tree->isContain(new_group)){
        updateGroupIdToUsers(not_empty_groups_tree->find(new_group)->key->users_tree->root,not_empty_groups_tree->find(new_group)->key);
    }
    this->all_groups_tree->deleteKey(new_group);
    this->not_empty_groups_tree->deleteKey(new_group);
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId) {
    if (userId <= 0 || groupId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Group> new_group(new Group(groupId));
    if (!new_group) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!this->all_groups_tree->isContain(new_group)) {
        return StatusType::FAILURE;
    }
    shared_ptr<User> check_user(new User(userId, 0, false));
    if (!check_user) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!this->all_users_tree->isContain(check_user)) {
        return StatusType::FAILURE;
    }
    if (all_users_tree->find(check_user)->key->group_id != 0) { ///Assume that user without group --->groupid=0
        return StatusType::FAILURE;
    }
    AVLnode<shared_ptr<User>,shared_ptr<User>>* current_user = all_users_tree->find(check_user);
    AVLnode<shared_ptr<Group>,shared_ptr<Group>>* cur_gr=all_groups_tree->find(new_group);
    if (all_groups_tree->find(new_group)->key->users_tree->treesize==0){
        this->not_empty_groups_tree->insert(all_groups_tree->find(new_group)->key,all_groups_tree->find(new_group)->key);
    }
    this->not_empty_groups_tree->find(new_group)->key->users_tree->insert(current_user->key,current_user->key);
    for (int i = 0; i < NUM_MOVIES_TYPES; ++i) {
        current_user->key->late_movies_group[i]=current_user->key->viewers[i];
        this->not_empty_groups_tree->find(new_group)->key->sum_of_all_viewers[i]+=current_user->key->late_movies_group[i];

        current_user->key->viewers[i] -= this->not_empty_groups_tree->find(new_group)->key->viewers[i];
        current_user->key->late_movies_group[i]=current_user->key->viewers[i];
    }
    if (current_user->key->is_vip){
        this->not_empty_groups_tree->find(new_group)->key->num_vip_users++;
    }
    current_user->key->group_id=groupId;
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId) {
    if (userId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<User> check_user(new User(userId, 0, false));
    if (!check_user) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_users_tree->isContain(check_user)) {
        return StatusType::FAILURE;
    }
    shared_ptr<MovieById> check_movie(new MovieById(Genre::COMEDY, movieId, false, 0, 0));
    if (!check_movie) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_movies_by_id->isContain(check_movie)) {
        return StatusType::FAILURE;
    }
    AVLnode<shared_ptr<MovieById>,shared_ptr<MovieById>>* curr_movie = all_movies_by_id->find(check_movie);
    AVLnode<shared_ptr<User>,shared_ptr<User>>* curr_user = all_users_tree->find(check_user);
    if (curr_movie->key->is_vip && !curr_user->key->is_vip) {
        return StatusType::FAILURE;
    }
    shared_ptr<MovieByRate> check_movie_by_rate(
            new MovieByRate(curr_movie->key->genre, movieId, curr_movie->key->is_vip, curr_movie->key->rate,
                            curr_movie->key->views,curr_movie->key->num_rates,curr_movie->key->sum_rates));
    shared_ptr<MovieByRate> copy_movie;
    all_movies_by_rate->deleteKey(check_movie_by_rate);

    shared_ptr<MovieByRate> updated(
            new MovieByRate(curr_movie->key->genre, movieId, curr_movie->key->is_vip, curr_movie->key->rate,
                            curr_movie->key->views,curr_movie->key->num_rates,curr_movie->key->sum_rates));
    curr_movie->key->views++;
    shared_ptr<Group> check_group(new Group(curr_user->key->group_id));
    AVLnode<shared_ptr<Group>,shared_ptr<Group>>* curr_node=NULL;
    if (curr_user->key->group_id!=0){
        curr_node=not_empty_groups_tree->find(check_group);
    }
    switch (curr_movie->key->genre) {
        case Genre::COMEDY:
            if (curr_node){
                curr_node->key->sum_of_all_viewers[0]++;
                //curr_node->key->viewers[0]++;
            } else{
                curr_user->key->viewers[0]++;
            }
            //copy_movie=check_movie_by_rate;
            comedy_movies_by_rate->deleteKey(check_movie_by_rate);
            updated->views++;
            comedy_movies_by_rate->insert(updated,updated);
            break;
        case Genre::DRAMA:
            if (curr_node){
                curr_node->key->sum_of_all_viewers[1]++;
                //curr_node->key->viewers[1]++;
            }else{
                curr_user->key->viewers[1]++;
            }
            //copy_movie=check_movie_by_rate;
            drama_movies_by_rate->deleteKey(check_movie_by_rate);
            updated->views++;
            drama_movies_by_rate->insert(updated,updated);
            break;
        case Genre::ACTION:
            if (curr_node){
                curr_node->key->sum_of_all_viewers[2]++;
                //curr_node->key->viewers[2]++;
            }else{
                curr_user->key->viewers[2]++;
            }
            //copy_movie=check_movie_by_rate;
            action_movies_by_rate->deleteKey(check_movie_by_rate);
            updated->views++;
            action_movies_by_rate->insert(updated,updated);
            break;
        case Genre::FANTASY:
            if (curr_node){
                curr_node->key->sum_of_all_viewers[3]++;
                //curr_node->key->viewers[3]++;
            }
            else{
                curr_user->key->viewers[3]++;
            }
            //copy_movie=check_movie_by_rate;
            fantasy_movies_by_rate->deleteKey(check_movie_by_rate);
            updated->views++;
            fantasy_movies_by_rate->insert(updated,updated);
            break;
        default:
            break;
    }
    check_movie_by_rate->views++;
    all_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId, int movieId) {
    if (groupId <= 0 || movieId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Group> check_group(new Group(groupId));
    if (!check_group) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_groups_tree->isContain(check_group)) {
        return StatusType::FAILURE;
    }
    if (!not_empty_groups_tree->isContain(check_group)){
        return StatusType::FAILURE;
    }
    shared_ptr<MovieById> check_movie(new MovieById(Genre::COMEDY, movieId, false, 0, 0));
    if (!check_movie) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_movies_by_id->isContain(check_movie)) {
        return StatusType::FAILURE;
    }
    AVLnode<shared_ptr<MovieById>,shared_ptr<MovieById>>* curr_movie = all_movies_by_id->find(check_movie);
    AVLnode<shared_ptr<Group>,shared_ptr<Group>>* curr_group = not_empty_groups_tree->find(check_group);
    if (curr_movie->key->is_vip && curr_group->key->num_vip_users==0) {
        return StatusType::FAILURE;
    }
    shared_ptr<MovieByRate> check_movie_by_rate(
            new MovieByRate(curr_movie->key->genre, movieId, curr_movie->key->is_vip, curr_movie->key->rate,
                            curr_movie->key->views,curr_movie->key->num_rates,curr_movie->key->sum_rates));
    all_movies_by_rate->deleteKey(check_movie_by_rate);
    curr_movie->key->views+=curr_group->key->users_tree->treesize;


    switch (curr_movie->key->genre) {
        case Genre::COMEDY:
            curr_group->key->viewers[0]++;
            curr_group->key->sum_of_all_viewers[0]+=curr_group->key->users_tree->treesize;

            comedy_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->views+=curr_group->key->users_tree->treesize;
            comedy_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        case Genre::DRAMA:
            curr_group->key->viewers[1]++;
            curr_group->key->sum_of_all_viewers[1]+=curr_group->key->users_tree->treesize;

            drama_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->views+=curr_group->key->users_tree->treesize;
            drama_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        case Genre::ACTION:
            curr_group->key->viewers[2]++;
            curr_group->key->sum_of_all_viewers[2]+=curr_group->key->users_tree->treesize;

            action_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->views+=curr_group->key->users_tree->treesize;
            action_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        case Genre::FANTASY:
            curr_group->key->viewers[3]++;
            curr_group->key->sum_of_all_viewers[3]+=curr_group->key->users_tree->treesize;

            fantasy_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->views+=curr_group->key->users_tree->treesize;
            fantasy_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        default:
            check_movie_by_rate->views+=curr_group->key->users_tree->treesize;
            break;
    }
    all_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre) {
    switch (genre) {
        case Genre::COMEDY:
            return num_movies[0];
        case Genre::DRAMA:
            return num_movies[1];
        case Genre::ACTION:
            return num_movies[2];
        case Genre::FANTASY:
            return num_movies[3];
        case Genre::NONE:
            return num_movies[4];
    }
    return 0;
}

static void
fillArray(AVLnode<shared_ptr<MovieByRate>,shared_ptr<MovieByRate>> *node, int *const output,int* i) {
    if (node == nullptr) {
        return;
    }
    fillArray(node->Right_son,output,i);
    output[*i]=node->key->movie_id;
    (*i)++;
    fillArray(node->left_son,output,i);
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output) {
    if (output == NULL){
        return StatusType::INVALID_INPUT;
    }
    int i=0;
    switch (genre) {
        case Genre::COMEDY:
            if (num_movies[0]==0){
                return StatusType::FAILURE;
            }
            fillArray(comedy_movies_by_rate->root,output, &i);
            break;
        case Genre::DRAMA:
            if (num_movies[1]==0){
                return StatusType::FAILURE;
            }
            fillArray(drama_movies_by_rate->root,output, &i);
            break;
        case Genre::ACTION:
            if (num_movies[2]==0){
                return StatusType::FAILURE;
            }
            fillArray(action_movies_by_rate->root,output, &i);
            break;
        case Genre::FANTASY:
            if (num_movies[3]==0){
                return StatusType::FAILURE;
            }
            fillArray(fantasy_movies_by_rate->root,output, &i);
            break;
        case Genre::NONE:
            if (num_movies[4]==0){
                return StatusType::FAILURE;
            }
            fillArray(all_movies_by_rate->root,output, &i);
            break;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre) {
    if (userId<=0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<User> check_user(new User(userId, 0, false));
    if (!check_user) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_users_tree->isContain(check_user)) {
        return StatusType::FAILURE;
    }
    int num_movies=0;
    shared_ptr<Group> check_group(new Group(all_users_tree->find(check_user)->key->group_id));
    AVLnode<shared_ptr<Group>,shared_ptr<Group>>* curr_group = not_empty_groups_tree->find(check_group);
    switch (genre) {
        case Genre::COMEDY:
            num_movies+=all_users_tree->find(check_user)->key->viewers[0];
            if (curr_group){
                num_movies+=curr_group->key->viewers[0];
            }
            break;
        case Genre::DRAMA:
            num_movies+=all_users_tree->find(check_user)->key->viewers[1];
            if (curr_group){
                num_movies+=curr_group->key->viewers[1];
            }
            break;
        case Genre::ACTION:
            num_movies+=all_users_tree->find(check_user)->key->viewers[2];
            if (curr_group){
                num_movies+=curr_group->key->viewers[2];
            }
            break;
        case Genre::FANTASY:
            num_movies+=all_users_tree->find(check_user)->key->viewers[3];
            if (curr_group){
                num_movies+=curr_group->key->viewers[3];
            }
            break;
        case Genre::NONE:
            for (int i = 0; i < NUM_MOVIES_TYPES; ++i) {
                num_movies+=all_users_tree->find(check_user)->key->viewers[i];
                if (curr_group){
                    num_movies+=curr_group->key->viewers[i];
                }
            }
            break;
    }
    return num_movies;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating) {
    if (userId<=0 || movieId<=0 || rating<0 || rating>100){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<User> check_user(new User(userId, 0, false));
    if (!check_user) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_users_tree->isContain(check_user)) {
        return StatusType::FAILURE;
    }
    shared_ptr<MovieById> check_movie(new MovieById(Genre::COMEDY, movieId, false, 0, 0));
    if (!check_movie) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_movies_by_id->isContain(check_movie)) {
        return StatusType::FAILURE;
    }
    AVLnode<shared_ptr<MovieById>,shared_ptr<MovieById>>* curr_movie = all_movies_by_id->find(check_movie);
    AVLnode<shared_ptr<User>,shared_ptr<User>>* curr_user = all_users_tree->find(check_user);
    if (curr_movie->key->is_vip && !curr_user->key->is_vip) {
        return StatusType::FAILURE;
    }
    shared_ptr<MovieByRate> check_movie_by_rate(
            new MovieByRate(curr_movie->key->genre, movieId, curr_movie->key->is_vip, curr_movie->key->rate,
                            curr_movie->key->views,curr_movie->key->num_rates,curr_movie->key->sum_rates));
    all_movies_by_rate->deleteKey(check_movie_by_rate);
    curr_movie->key->sum_rates+=rating;
    curr_movie->key->num_rates++;
    curr_movie->key->rate=curr_movie->key->sum_rates/curr_movie->key->num_rates;
    switch (curr_movie->key->genre) {
        case Genre::COMEDY:
            comedy_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->num_rates++;
            check_movie_by_rate->sum_rates+=rating;
            check_movie_by_rate->rate=check_movie_by_rate->sum_rates/check_movie_by_rate->num_rates;
            comedy_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        case Genre::DRAMA:
            drama_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->num_rates++;
            check_movie_by_rate->sum_rates+=rating;
            check_movie_by_rate->rate=check_movie_by_rate->sum_rates/check_movie_by_rate->num_rates;
            drama_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        case Genre::ACTION:
            action_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->num_rates++;
            check_movie_by_rate->sum_rates+=rating;
            check_movie_by_rate->rate=check_movie_by_rate->sum_rates/check_movie_by_rate->num_rates;
            action_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        case Genre::FANTASY:
            fantasy_movies_by_rate->deleteKey(check_movie_by_rate);
            check_movie_by_rate->num_rates++;
            check_movie_by_rate->sum_rates+=rating;
            check_movie_by_rate->rate=check_movie_by_rate->sum_rates/check_movie_by_rate->num_rates;
            fantasy_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
            break;
        default:
            check_movie_by_rate->num_rates++;
            check_movie_by_rate->sum_rates+=rating;
            check_movie_by_rate->rate=check_movie_by_rate->sum_rates/check_movie_by_rate->num_rates;
            break;
    }
    all_movies_by_rate->insert(check_movie_by_rate,check_movie_by_rate);
    return StatusType::SUCCESS;
}

static int getMaxIndex(int arr[]){
    int max=0;
    for (int i = 0; i < NUM_MOVIES_TYPES; ++i) {
        if (arr[i]>arr[max]){
            max=i;
        }
    }
    return max;
}

output_t<int> streaming_database::get_group_recommendation(int groupId) {
    if (groupId<=0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Group> check_group(new Group(groupId));
    if (!check_group) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (!all_groups_tree->isContain(check_group)) {
        return StatusType::FAILURE;
    }
    if (!not_empty_groups_tree->isContain(check_group)){
        return StatusType::FAILURE;
    }
    AVLnode<shared_ptr<Group>,shared_ptr<Group>>* curr_group= not_empty_groups_tree->find(check_group);
    int max_index= getMaxIndex(curr_group->key->sum_of_all_viewers);
    switch (max_index) {
        case 0:
            if (comedy_movies_by_rate->treesize==0){
                return StatusType::FAILURE;
            }
            return comedy_movies_by_rate->getMaxNode()->movie_id;
        case 1:
            if (drama_movies_by_rate->treesize==0){
                return StatusType::FAILURE;
            }
            return drama_movies_by_rate->getMaxNode()->movie_id;
        case 2:
            if (action_movies_by_rate->treesize==0){
                return StatusType::FAILURE;
            }
            return action_movies_by_rate->getMaxNode()->movie_id;
        case 3:
            if (fantasy_movies_by_rate->treesize==0){
                return StatusType::FAILURE;
            }
            return fantasy_movies_by_rate->getMaxNode()->movie_id;
        default:
            return 0;
    }
}


