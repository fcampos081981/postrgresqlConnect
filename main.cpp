#include <iostream>
#include <string>
#include <pqxx/pqxx>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    try {
        std::string serverUrl =
                "dbname=mydb user=postgres password=12345 host=localhost port=5432";
        pqxx::connection C(serverUrl);
        if (C.is_open()) {
            std::cout << "Connected: " << C.dbname() << std::endl;
        } else {
            std::cerr << "Not Connected: " << C.dbname() << std::endl;
        }

        pqxx::work W(C);

        W.exec("CREATE TABLE IF NOT EXISTS funcionarios (id SERIAL PRIMARY KEY, nome TEXT, idade INT)");

        for (int i = 0; i < 10; i++) {

            std::string nome = "Carlos: " + std::to_string(i) + " ";
            int idade = i + 1;
            std::string dados = "INSERT INTO funcionarios (nome, idade) VALUES (" + W.quote(nome) + ", " +
                                std::to_string(idade) + ")";
            W.exec0(dados);

            std::cout << "Dados inseridos com sucesso." << std::endl;


            pqxx::result R = W.exec("SELECT id, nome, idade FROM funcionarios");

            std::cout << "\nLista de Funcionários:" << std::endl;

            for (auto row: R) {
                std::cout << "ID: " << row[0].as<int>() << " | "
                        << "Nome: " << row[1].c_str() << " | "
                        << "Idade: " << row[2].as<int>() << std::endl;
            }
        }

        W.commit();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}
