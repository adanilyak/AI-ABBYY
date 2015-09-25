//
//  CMap.hpp
//  AI-ABBYY
//
//  Created by Alexander Danilyak on 17/09/15.
//  Copyright © 2015 Alexander Danilyak. All rights reserved.
//

#ifndef CMap_hpp
#define CMap_hpp

#include <iostream>
#include <vector>

class Map {
private:
    std::vector< std::vector < int > > *cells;
    size_t xSize;
    size_t ySize;
    
    std::vector< std::pair< int, int > > *finishPoints;
    
public:
    
    Map();
    Map(const size_t xSize, const size_t ySize);
    Map(std::vector< std::vector < int > > *inputCells, std::vector< std::pair< int, int > > *inputFinishPoints);
    
    ~Map();
    
    const std::pair<size_t, size_t> size() const; // returs xSize, ySize pair
    const size_t sizeOnXaxis() const;             // returs xSize
    const size_t sizeOnYaxis() const;             // returs ySize
    
    std::vector< int > &operator[](int i);
    
    bool canPlayerStayOnCell(int x, int y);
};

#endif /* CMap_hpp */
