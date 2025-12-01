#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <vector>
#include <random>

// ... existing code ...

int main() {
    try {
        std::string serverUrl =
                "dbname=mydb user=postgres password=Skc080210 host=localhost port=5432";
        pqxx::connection C(serverUrl);
        if (C.is_open()) {
            std::cout << "Connected: " << C.dbname() << std::endl;
        } else {
            std::cerr << "Not Connected: " << C.dbname() << std::endl;
        }

        // Random name generator setup
        std::vector<std::string> firstNames = {"Ana", "Bruno", "Carlos", "Daniela", "Eduardo", "Fernanda", "Gabriel", "Helena", "Igor", "Julia"};
        std::vector<std::string> lastNames = {"Silva", "Santos", "Oliveira", "Souza", "Rodrigues", "Ferreira", "Almeida", "Pereira", "Lima", "Gomes"};

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distFirst(0, firstNames.size() - 1);
        std::uniform_int_distribution<> distLast(0, lastNames.size() - 1);

        pqxx::work W(C);

        W.exec("CREATE TABLE IF NOT EXISTS funcionarios (id SERIAL PRIMARY KEY, nome TEXT, idade INT)");

        for (int i = 0; i < 10; i++) {

            std::string nome = firstNames[distFirst(gen)] + " " + lastNames[distLast(gen)];
            int idade = i + 1; // or use random age: 20 + (i % 40)
            std::string dados = "INSERT INTO funcionarios (nome, idade) VALUES (" + W.quote(nome) + ", " +
                                std::to_string(idade) + ")";
            W.exec0(dados);

            std::cout << "Dados inseridos com sucesso." << std::endl;


            pqxx::result R = W.exec("SELECT id, nome, idade FROM funcionarios");
// ... existing code ...