#ifndef BIOMECONTEXT_H
#define BIOMECONTEXT_H

#include "BiomeStrategy.h"
#include "../systems/Subject.h"

// Context
class BiomeContext : public Subject {
private:
    BiomeStrategy* currentStrategy;

public:
    BiomeContext();
    ~BiomeContext();

    void setBiome(BiomeStrategy* newStrategy);
    void apply(Player& player);
    
    std::string getCurrentBiomeName() const;
};

#endif
