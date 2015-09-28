//
//  CAStarStrategy.cpp
//  AI-ABBYY
//
//  Created by Alexander Danilyak on 25/09/15.
//  Copyright © 2015 Alexander Danilyak. All rights reserved.
//

#include "CAStarStrategy.hpp"
#include <algorithm>
#include <stdexcept>

#pragma mark - Constructors

AStarStrategy::AStarStrategy() {
    
}



#pragma mark - Destructor



#pragma mark - Tools

bool isEqualNodes(const SNode& one, const SNode& two) {
    if (one.position.first == two.position.first && one.position.second == two.position.second) {
        return true;
    } else {
        return false;
    }
}

#pragma mark - Methods

float AStarStrategy::calculateEstimateHeuristicCost(SNode *current, SNode *finish) {
    // Chebyshev distance
    return std::max(std::abs(current->position.first - finish->position.first),
                    std::abs(current->position.second - finish->position.second));
}

std::set< SNode * > AStarStrategy::reachableNodesFromNode( SNode *current ) {
    
    std::set< SNode * > result = * new std::set< SNode * >;
    
    for (int deltaX = -1; deltaX <= 1; ++deltaX) {
        for (int deltaY = -1; deltaY <= 1; ++deltaY) {
            SNode *nextNode = new SNode();
            if (map->canPlayerStayOnCell(current->position.first + current->velocityVector.first + deltaX,
                                         current->position.second + current->velocityVector.second + deltaY)) {
                
                nextNode->position = std::make_pair(current->position.first + current->velocityVector.first + deltaX,
                                                    current->position.second + current->velocityVector.second + deltaY);
                
                nextNode->velocityVector = std::make_pair(current->velocityVector.first + deltaX,
                                                          current->velocityVector.second + deltaY);
            } else {
                continue;
            }
        }
    }
    
    return result;
}

bool AStarStrategy::AStar(SNode *start, SNode *finish) {
    
    if (start == nullptr || finish == nullptr) {
        throw std::invalid_argument("start and finish must NOT be null");
    }
    
    closed = new std::set< SNode * >;
    open = new PriorityQueueExtension< SNode * >;
    
    open->push( start );
    start->f = start->g + start->h;
    start->parent = start;
    
    while (open->size() != 0) {
        SNode* tempNode = open->top();
        open->pop();
        
        if ( isEqualNodes(*tempNode, *finish) ) {
            // if equal
            return 1;
        }
        
        closed->insert( tempNode );
        
        for (SNode *reachableNode : this->reachableNodesFromNode(tempNode)) {
            
            if (closed->find(reachableNode) != closed->end()) {
                continue;
            }
            
            int tempPathLength = tempNode->g + 1;
            bool isThisPathBetter = false;
            
            if (open->find(reachableNode) == open->end()) {
                open->push(reachableNode);
                isThisPathBetter = true;
            } else {
                if (tempPathLength < reachableNode->g) {
                    isThisPathBetter = true;
                } else {
                    isThisPathBetter = false;
                }
            }
            
            if (isThisPathBetter) {
                reachableNode->parent = tempNode;
                reachableNode->h = this->calculateEstimateHeuristicCost(reachableNode, finish);
                reachableNode->g = tempPathLength;
                reachableNode->f = reachableNode->g + reachableNode->h;
            }
        }
    }
    return 0;
}