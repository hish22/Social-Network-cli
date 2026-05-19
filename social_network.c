#include <stdio.h>
#include <stdlib.h>

#define VAILDATE_FOLLOW user_to_follow != user_want_to_do_follow && user_to_follow != NULL && user_want_to_do_follow != NULL
#define VAILDATE_UNFOLLOW user_want_to_do_unfollow != user_to_unfollow && user_want_to_do_unfollow != NULL && user_to_unfollow != NULL

#define TRUE 1
#define FALSE 0

static int latest_user_id = 0;

typedef struct user user_t;

/* List of user follower */
typedef struct follower {
    user_t* user;
    struct follower* next;
}followers_t;

/* List of followed users */
typedef struct following {
    user_t* user;
    struct following* next;
}following_t;

typedef struct user {
    int userid;
    char *name;
    int age;
    followers_t* followers; // users you follow
    following_t* following; // users they follow you
}user_t;

/* Create new user */
user_t* create_user(char* name, int age) {
    user_t* user = malloc(sizeof(user_t));
    user->userid = ++latest_user_id;
    user->name = name;
    user->age = age;
    return user;
}

void add_follower(user_t* user_want_to_do_follow, user_t* user_to_follow) {
    followers_t* new_follow = malloc(sizeof(followers_t));
    new_follow->user = user_to_follow;
    new_follow->next = user_want_to_do_follow->followers;
    user_want_to_do_follow->followers = new_follow;
}

void add_following(user_t* user_want_to_do_follow, user_t* user_to_follow) {
    following_t* new_following = malloc(sizeof(following_t));
    new_following->user = user_want_to_do_follow;
    new_following->next = user_to_follow->following;
    user_to_follow->following = new_following;
}

int check_if_followed(user_t* user_want_to_do_follow, user_t* user_to_follow) {
    followers_t* curr = user_want_to_do_follow->followers;
    while (curr != NULL) {
        if(curr->user == user_to_follow) {
            return TRUE;
        }
        curr = curr->next;
    }
    return FALSE;
}

/* Logic to follow a new user */
void follow(user_t* user_want_to_do_follow, user_t* user_to_follow) {
    if(VAILDATE_FOLLOW) {

        if(!check_if_followed(user_want_to_do_follow, user_to_follow)) {
            add_follower(user_want_to_do_follow, user_to_follow);

            add_following(user_want_to_do_follow, user_to_follow);
        } else {
            printf("\nUser %d already follow user %d\n"
                ,user_want_to_do_follow->userid,user_to_follow->userid);
        }

    } else {
        printf("\nCan't follow same user!\n");
    }
}

void free_followers(followers_t* head) {
    while (head != NULL) {
        followers_t* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_following(following_t* head) {
    while (head != NULL) {
        following_t* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_user(user_t* user) {
    if (user == NULL) return;
    free_followers(user->followers);
    free_following(user->following);
    free(user);
}

void remove_follower(user_t* user_want_to_do_unfollow, user_t* user_to_unfollow) {
    // Remove from followers
    followers_t* i_follow = user_want_to_do_unfollow->followers;

    if(i_follow->user == user_to_unfollow) {
        followers_t* temp_to_free = i_follow;
        user_want_to_do_unfollow->followers = user_want_to_do_unfollow->followers->next;
        free(temp_to_free);
        return;
    }
    while (i_follow != NULL) {
        if(i_follow->next->user == user_to_unfollow) {
            followers_t* temp_to_free = i_follow->next;
            i_follow->next = i_follow->next->next;
            free(temp_to_free);
            break;
        }
        i_follow = i_follow->next;
    }
}

void remove_following(user_t* user_want_to_do_unfollow, user_t* user_to_unfollow) {
    following_t* i_following = user_to_unfollow->following;

    if(i_following->user == user_want_to_do_unfollow) {
        following_t* temp_to_free = i_following;
        user_to_unfollow->following = user_to_unfollow->following->next;
        free(temp_to_free);
        return;
    }

    while (i_following != NULL) {
        if(i_following->next->user == user_want_to_do_unfollow) {
            following_t* temp_to_free = i_following->next;
            i_following->next = i_following->next->next;
            free(temp_to_free);
            break;
        }
        i_following = i_following->next;
    }
}

/* Logic to unfollow a user */
void unfollow(user_t* user_want_to_do_unfollow, user_t* user_to_unfollow) {
    
    if(VAILDATE_UNFOLLOW) {

        if(check_if_followed(user_want_to_do_unfollow, user_to_unfollow)) {
            remove_follower(user_want_to_do_unfollow, user_to_unfollow);

            remove_following(user_want_to_do_unfollow, user_to_unfollow);
        } else {
            printf("\nUser %d dosen't follow user %d\n"
                ,user_want_to_do_unfollow->userid, user_to_unfollow->userid);
        }


    } else {
        printf("\nCan't unfollow same user!\n");
    }
}

/* Show user information */
void show_user_info(user_t* user) {
    if (user == NULL) return;

    printf("==========================================\n");
    printf("            USER PROFILE CARD             \n");
    printf("==========================================\n");
    printf(" ID      : %d\n", user->userid);
    printf(" NAME    : %s\n", user->name);
    printf(" AGE     : %d\n", user->age);
    printf("------------------------------------------\n");

    printf("\n[ FOLLOWERS ]\n");
    followers_t* follow = user->followers;
    if (follow == NULL) printf(" (No followers yet)\n");
    while (follow != NULL) {
        printf(" -> %s (ID: %d, Age: %d)\n", 
               follow->user->name, follow->user->userid, follow->user->age);
        follow = follow->next;
    }

    printf("\n[ FOLLOWING ]\n");
    following_t* following = user->following;
    if (following == NULL) printf(" (Not following anyone)\n");
    while (following != NULL) {
        printf(" -> %s (ID: %d, Age: %d)\n", 
               following->user->name, following->user->userid, following->user->age);
        following = following->next;
    }
    printf("==========================================\n");
}

void print_followers(followers_t* followers) {
    printf("\n[ FOLLOWERS ]\n");
    if (followers == NULL) {
        printf(" (No followers yet)\n");
        return;
    }

    followers_t* curr = followers;
    while (curr != NULL) {
        printf(" ├── %s (ID: %d)\n", curr->user->name, curr->user->userid);
        curr = curr->next;
    }
}

void print_following(following_t* following) {
    printf("\n[ FOLLOWING ]\n");
    if (following == NULL) {
        printf(" (Not following anyone)\n");
        return;
    }

    following_t* curr = following;
    while (curr != NULL) {
        printf(" ├── %s (ID: %d)\n", curr->user->name, curr->user->userid);
        curr = curr->next;
    }
}

int main() {

    user_t* user1 = create_user("Ahmed Mohammed",22);
    user_t* user2 = create_user("Hammed Saad",24);
    user_t* user3 = create_user("Bader Nawaf",32);
    user_t* user4 = create_user("Khaild Ahmed",72);
    user_t* user5 = create_user("Omar Bander",40);
    user_t* user6 = create_user("Osama Mohammed",35);
    user_t* user7 = create_user("Tom Hard",17);
    user_t* user8 = create_user("Rayn Ham",17);


    // User one followers
    follow(user1,user2);
    follow(user1,user7);

    // User two followers
    follow(user2,user3);
    follow(user2,user7);
    follow(user2,user5);

    // User Three followers
    follow(user3,user1);
    follow(user3,user6);

    // User Four followers
    follow(user4,user8);
    follow(user4,user6);
    follow(user4,user4);

    // User Five followers
    follow(user5,user1);

    // User Six followers
    follow(user6,user5);

    // User Seven followers
    follow(user7,user6);

    // User Eight followers
    follow(user8,user3);
    follow(user8,user4);

    // Show users information
    show_user_info(user1);
    show_user_info(user2);
    show_user_info(user3);
    show_user_info(user4);
    show_user_info(user5);
    show_user_info(user6);
    show_user_info(user7);
    show_user_info(user8);

    // user8 unfollow user3
    unfollow(user8,user3);
    show_user_info(user3);
    show_user_info(user8);

    // user2 unfollow user7
    unfollow(user2, user7);
    show_user_info(user2);
    show_user_info(user7);

    free_user(user1);
    free_user(user2);
    free_user(user3);
    free_user(user4);
    free_user(user5);
    free_user(user6);
    free_user(user7);
    free_user(user8);

    return 0;
}