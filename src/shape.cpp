#include "../include/shape.h"

Shape::Shape(){
    Material();
}

Shape::Shape(Material matter_value){
    matter = matter_value;
}

Material Shape::getMatter() const {
    return matter;
}