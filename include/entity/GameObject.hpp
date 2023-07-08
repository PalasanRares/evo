#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

class GameObject {
public:
    virtual ~GameObject() {}

    virtual void update() = 0;

    virtual void render() = 0;
};

#endif