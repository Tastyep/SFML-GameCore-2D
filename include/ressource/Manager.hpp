// Copyright (C) 2017 Etix Labs - All Rights Reserved.
// All information contained herein is, and remains the property of Etix Labs and its suppliers,
// if any. The intellectual and technical concepts contained herein are proprietary to Etix Labs
// Dissemination of this information or reproduction of this material is strictly forbidden unless
// prior written permission is obtained from Etix Labs.

#ifndef GAME_CORE_GAME_RESSOURCES_MANAGER_HPP
#define GAME_CORE_GAME_RESSOURCES_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <utility>

#include <spdlog/fmt/ostr.h>

namespace GameCore {
namespace Ressource {

template <typename Ressource>
class Manager {
 public:
  bool load(std::string name, const std::string& ressourcePath) {
    Ressource ressource;

    if (_ressources.find(name) != _ressources.end()) {
      std::cerr << "A ressource is already registered for the name \"" << name << "\"" << std::endl;
      return false;
    }
    if (!ressource.loadFromFile(ressourcePath)) {
      std::cerr << "Could not find the ressource '" << ressourcePath << "'" << std::endl;
      return false;
    }

    _ressources.emplace(std::move(name), std::move(ressource));
    return true;
  }

  const Ressource& get(const std::string& name) const {
    auto it = _ressources.find(name);

    if (it != _ressources.end()) {
      return it->second;
    }
    throw std::out_of_range(fmt::format("Ressource \"{}\" not found", name));
  }

 private:
  std::unordered_map<std::string, Ressource> _ressources;
};

} /* namespace Ressource */
} /* namespace GameCore */

#endif
