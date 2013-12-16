//
//  Galaxy.h
//  spaceOdyssey_enemy
//
//  Created by Mauricio Sanchez Duque on 12/11/13.
//
//

#pragma once
#include "ofMain.h"

class Galaxy{
    
public:
    
//    Galaxy();
    
      void branch( float length, float _ang1, float _ang2, float _mult = 1 );
    
    void drawGalaxy();
    
    float theta = 30;
    
};
