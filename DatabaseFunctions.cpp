#include "DatabaseFunctions.h"
#include "DataGenerator.h"
#include "FilesFunctions.h"
#include <iostream>

std::unique_ptr<pqxx::connection> DatabaseFunctions::connectToDB(const std::string &connStr) {
    try {
        auto C = std::make_unique<pqxx::connection>(connStr);
        if (C->is_open()) {
            std::cout << "Connected to: " << C->dbname() << std::endl;
            return C;
        }
    } catch (const std::exception &e) {
        std::cerr << "Connection Error: " << e.what() << std::endl;
    }
    return nullptr;
}

void DatabaseFunctions::createTables(pqxx::connection &C) {
    try {
        pqxx::work W(C);

        W.exec("DROP TABLE IF EXISTS telefones CASCADE");

        W.exec("DROP TABLE IF EXISTS pessoas CASCADE");

        W.exec("CREATE TABLE IF NOT EXISTS pessoas (id SERIAL PRIMARY KEY, nome TEXT, idade INT)");

        W.exec("CREATE TABLE IF NOT EXISTS telefones ("
            "id SERIAL PRIMARY KEY, "
            "pessoas_id INT REFERENCES pessoas(id) ON DELETE CASCADE, "
            "numero TEXT)");

        W.commit();
        std::cout << "Tables initialized successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Create Table Error: " << e.what() << std::endl;
    }
}

void DatabaseFunctions::insertData(pqxx::connection &C, int count) {
    try {
        pqxx::work W(C);

        std::cout << "Inserting " << count << " records..." << std::endl;


        for (int i = 0; i < count; i++) {

            insertRandomPerson(W, 18 + (i % 60));

            float progress_bar = (float)i / count;

            FilesFunctions::showProgressBar(progress_bar);

        }

        W.commit();
        std::cout << "Successfully inserted " << count << " records." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
}

void DatabaseFunctions::insertRandomPerson(pqxx::work &W, int age) {
    DataGenerator dg;
    std::string nome = dg.generateRandomName();
    std::string telefone = dg.generateRandomPhone();


    std::string sqlPerson =
            "INSERT INTO pessoas (nome, idade) VALUES (" +
            W.quote(nome) + ", " + std::to_string(age) +
            ") RETURNING id";

    pqxx::row r = W.exec1(sqlPerson);
    int pessoa_id = r[0].as<int>();

    std::string sqlPhone =
            "INSERT INTO telefones (pessoas_id, numero) VALUES (" +
            std::to_string(pessoa_id) + ", " + W.quote(telefone) +
            ")";

    W.exec0(sqlPhone);
}

void DatabaseFunctions::readData(pqxx::connection &C, const std::string &filename) {
    try {
        pqxx::nontransaction N(C);

        pqxx::result R = N.exec(
            "SELECT f.id, f.nome, f.idade, t.numero "
            "FROM pessoas f "
            "LEFT JOIN telefones t ON f.id = t.pessoas_id "
            "ORDER BY f.id ASC  ");

        FilesFunctions::writeDataToFile(R, filename);

        for (auto row: R) {
            int id = row[0].as<int>();
            std::stringstream ss;
            ss << std::setw(9) << std::setfill('0') << id;
            std::cout << "ID: " << ss.str() << " | "
                    << "Nome: " << row[1].c_str() << " | "
                    << "Idade: " << row[2].as<int>() << " | "
                    << "Telefone: " << (row[3].is_null() ? "N/A" : row[3].c_str())
                    << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Read Error: " << e.what() << std::endl;
    }
}