//
// Created by luiz0tavio on 6/4/18.
//

#include "Input.hpp"

Events::Input &Events::Input::getInstance()
{
    static Events::Input instance;
    return instance;
}