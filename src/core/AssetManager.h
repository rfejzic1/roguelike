#pragma once

#include <string>
#include <unordered_map>
#include <memory>

template<typename T>
class AssetManager {
    std::unordered_map<std::string, std::shared_ptr<T>> assets;
    virtual T* loader(const std::string& uri) = 0;
public:
    virtual void load(const std::string &name, const std::string& uri);
    virtual void free(const std::string& name);
    std::shared_ptr<T> get(const std::string& name);
    virtual ~AssetManager() = default;
};

template<typename T>
void AssetManager<T>::load(const std::string &name, const std::string &uri) {
    if(assets[name]) {
        return;
    }
    T* asset = loader(uri);
    assets[name] = std::shared_ptr<T>(asset);
}

template<typename T>
void AssetManager<T>::free(const std::string &name) {
    assets.at(name) = nullptr;
    assets.erase(name);
}

template<typename T>
std::shared_ptr<T> AssetManager<T>::get(const std::string &name) {
    return assets.at(name);
}
