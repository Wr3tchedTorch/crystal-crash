#pragma once
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <concepts>
#include <unordered_map>
#include <fstream>
#include "DataHandlingConstants.h"
#include "InputFileHelper.h"
#include <algorithm>
#include <format>
#include <iostream>

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
	
    void saveToFile(const json& data);

    json readFromFile();

    int getNextId(const json& data);

    json resolvePrototype(json& item, json& data);

public:
    DataHandler(std::string filepath);
    std::shared_ptr<T> getById(int id);
    
    std::unordered_map<int, std::shared_ptr<T>> getAll();
    void create(T& newItem);
    void deleteById(int id);
    void updateById(const T& toItem);
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
void DataHandler<T>::saveToFile(const json& data)
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
inline int DataHandler<T>::getNextId(const json& data)
{
    int nextId = 0;
    for (auto& [id, val] : data.items()) 
    {
        nextId = std::max(nextId, std::stoi(id) + 1);
    }
    return nextId;
}

template<serializable T>
inline json DataHandler<T>::resolvePrototype(json& item, json& data)
{
    std::string prototypeId = item[DataHandlingConstants::PrototypeFieldKey];
    if (!data.contains(prototypeId))
    {
#ifdef _DEBUG
        std::cout << std::format("prototype id `{}` not found!", prototypeId);
#endif // _DEBUG
        return json();
    }

    json resolved = data[prototypeId];
    for (auto& [key, value] : item.items())
    {
        if (key == DataHandlingConstants::PrototypeFieldKey)
        {
            continue;
        }
        resolved[key] = value;
    }

    return resolved;
}

template<serializable T>
inline DataHandler<T>::DataHandler(std::string filepath) : m_Filepath(filepath)
{
    createTemplateJsonFile();
}


std::string json_dump(nlohmann::json& j) {
    return j.dump(4);
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

    json item = data[std::to_string(id)];

    bool isPrototype = item.contains(DataHandlingConstants::PrototypeFieldKey);
    T entity = isPrototype ? resolvePrototype(item, data) : item;
    entity.Id = id;

    m_Data[id] = std::make_shared<T>(entity);
    return m_Data[id];
}

template<serializable T>
inline std::unordered_map<int, std::shared_ptr<T>> DataHandler<T>::getAll()
{
    return m_Data;
}

template<serializable T>
void DataHandler<T>::create(T& newItem)
{
    json oldData = readFromFile();

    newItem.Id = getNextId(oldData);    

    m_Data[newItem.Id] = std::make_shared<T>(newItem);

    json data = newItem;
    oldData[std::to_string(newItem.Id)] = data;

    saveToFile(oldData);
}

template<serializable T>
inline void DataHandler<T>::deleteById(int id)
{
    json data = readFromFile();

    std::string key = std::to_string(id);
    if (data.contains(key))
    {
        data.erase(key);
        saveToFile(data);  
        return;
    }

#ifdef _DEBUG
    std::cout << std::format("{}: entity with id `{}` not found for delete!", m_Filepath, id);
#endif // _DEBUG

}

template<serializable T>
inline void DataHandler<T>::updateById(const T& toItem)
{
    json data = readFromFile();

    std::string key = std::to_string(toItem.Id);
    if (data.contains(key))
    {
        data[key] = toItem;
        saveToFile(data);
        return;
    }

#ifdef _DEBUG
    std::cout << std::format("{}: entity with id `{}` not found for update!", m_Filepath, toItem.Id);
#endif // _DEBUG
}
