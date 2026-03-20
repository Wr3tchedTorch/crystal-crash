#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <concepts>
#include <unordered_map>
#include <fstream>
#include "DataHandlingConstants.h"
#include "InputFileHelper.h"
#include <utility>
#include <algorithm>

using json = nlohmann::json;

template<typename T>
concept serializable = requires(T t, nlohmann::json & j, const nlohmann::json & cj)
{
    { t.Id } -> std::convertible_to<int>;
};

template <serializable T>
class DataHandler
{
private:
	std::unordered_map<int, std::shared_ptr<T>> m_Data;

	std::string m_Filepath;

    void createTemplateJsonFile();
	
    void saveToFile(json data);

    json readFromFile();

    int getNextId(json data);

public:
    DataHandler(std::string filepath);
    std::shared_ptr<T> getById(int id);
    void create(T newItem);
};

template<serializable T>
inline void DataHandler<T>::createTemplateJsonFile()
{
    json oldData = readFromFile();

    bool hasData = oldData.size() > 0;

    if (hasData)
    {
        return;
    }

    T item;
    item.Id = 0;

    json data;
    data[std::to_string(item.Id)] = item;

    saveToFile(data);
}

template<serializable T>
void DataHandler<T>::saveToFile(json data)
{
    std::ofstream outputFile(m_Filepath);
    outputFile << data.dump(DataHandlingConstants::IndentAmount);
    outputFile.close();
}

template<serializable T>
json DataHandler<T>::readFromFile()
{
    std::ifstream inputFile(m_Filepath);

    if (!InputFileHelper::is_empty(inputFile))
    {
        json data;
        inputFile >> data;
        return data;
    }

    return json();
}

template<serializable T>
inline int DataHandler<T>::getNextId(json data)
{
    int nextId = 0;
    for (auto& [id, val] : data.items()) 
    {
        nextId = std::max(nextId, std::stoi(id) + 1);
    }
    return nextId;
}

template<serializable T>
inline DataHandler<T>::DataHandler(std::string filepath) : m_Filepath(filepath)
{
    createTemplateJsonFile();
}

template<serializable T>
std::shared_ptr<T> DataHandler<T>::getById(int id)
{
    auto result = m_Data.find(id);
    if (result != m_Data.end())
    {
        return result->second;
    }

    json data = readFromFile();

    if (data.find(std::to_string(id)) == data.end())
    {
        return nullptr;
    }

    T item = data[std::to_string(id)];

    m_Data[id] = std::make_shared<T>(item);

    return m_Data[id];
}

template<serializable T>
void DataHandler<T>::create(T newItem)
{
    json oldData = readFromFile();

    newItem.Id = getNextId(oldData);

    json data = newItem;
    oldData[std::to_string(newItem.Id)] = data;

    saveToFile(oldData);
}
