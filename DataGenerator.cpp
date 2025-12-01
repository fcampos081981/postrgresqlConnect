//
// Created by usuario on 12/1/25.
//

#include "DataGenerator.h"

std::string DataGenerator::generateRandomName() {
    static const std::vector<std::string> firstNames = {
        "Ana", "Bruno", "Carlos", "Daniela", "Eduardo",
        "Fernanda", "Gabriel", "Helena", "Igor", "Julia",
        "Kevin", "Larissa", "Lucas", "Mariana", "Matheus",
        "Natalia", "Otavio", "Patricia", "Pedro", "Rafael"
    };

    static const std::vector<std::string> lastNames = {
        "Silva", "Santos", "Oliveira", "Souza", "Rodrigues",
        "Ferreira", "Almeida", "Pereira", "Lima", "Gomes",
        "Costa", "Ribeiro", "Martins", "Carvalho", "Araujo",
        "Mendes", "Barbosa", "Ramos", "Teixeira", "Monteiro"
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> distFirst(0, firstNames.size() - 1);
    std::uniform_int_distribution<> distLast(0, lastNames.size() - 1);

    return firstNames[distFirst(gen)] + " " + lastNames[distLast(gen)];
}

std::string DataGenerator::generateRandomPhone() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> distDDD(11, 99);
    std::uniform_int_distribution<> distPart1(1000, 9999);
    std::uniform_int_distribution<> distPart2(1000, 9999);

    int ddd = distDDD(gen);
    int part1 = distPart1(gen);
    int part2 = distPart2(gen);

    return "(" + std::to_string(ddd) + ") 9" +
           std::to_string(part1) + "-" +
           std::to_string(part2);
}
