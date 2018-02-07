#include "Entity.h"
#include "Point.h"
#include <string>
#include "Wall.h"
#include "PrintUtils.h"

using namespace std;

Wall::Wall() {
    
}

Wall::~Wall() {
    
}

string Wall::draw() {
    return escapeCodeBase("100;37")+"#"+colourReset();
}
