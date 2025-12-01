//
// Created by usuario on 12/1/25.
//

#ifndef POSTRGRESQLCONNECT_DATAGENERATOR_H
#define POSTRGRESQLCONNECT_DATAGENERATOR_H
#include <string>
#include <vector>
#include <random>

class DataGenerator {
public:
    DataGenerator() {
    }

    virtual ~DataGenerator() = default;

    std::string generateRandomName();

    std::string generateRandomPhone();
};


#endif //POSTRGRESQLCONNECT_DATAGENERATOR_H