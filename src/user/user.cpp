#include "user.hpp"

user::user(id_t id, int fd, std::string name): _id(id), _fd(fd), _name(name) {}

// TODO fermer proprement la connection
user::~user(void) {}
