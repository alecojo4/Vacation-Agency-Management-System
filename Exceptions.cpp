//
// Created by Ale on 5/2/2023.
//

#include "Exceptions.h"

std::ostream &operator<<(std::ostream &os, const ValidationException &exception) {
    os << exception.message;
    return os;
}

std::ostream &operator<<(std::ostream &os, const RepositoryException &exception) {
    os << exception.message;
    return os;
}