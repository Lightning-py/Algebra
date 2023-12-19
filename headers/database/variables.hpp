#pragma once
#include <regex>
#include <map>


namespace daba
{
    template <typename K, typename V> // vector<float>, std::string
    class Database
    {
        public:
        Database()
        { }
        ~Database()
        { }

        void set(K name, std::vector<std::string> values)
        {
            std::vector<float> values_parsed(values.size());

            for (int i = 0; i < values.size(); ++i)
                values_parsed[i] = std::stof(values[i]);

            db.emplace(name, values_parsed);
        }

        std::vector<V> get(std::string name)
        {
            return db[name];
        }

        private:
            std::map<K, std::vector<V>> db;
    };
}



// упорядочить структуру // 2023.12.12
// создать другие типы шаблона: path_type, vector_type // 2023.12.12
// set/get, чтобы получать значения по имени // 2023.12.12