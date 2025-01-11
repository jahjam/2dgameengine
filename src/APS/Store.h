#pragma once

#include "Prop.h"
#include <cstddef>
#include <vector>

class IStore {
public:
  virtual ~IStore() = 0;
  virtual size_t getSize() = 0;
  virtual void resize(size_t num) = 0;
  virtual void add(Prop *prop, const Name &actorName) = 0;
  virtual void remove(const Name &actorName) = 0;
  virtual Prop *get(Name actorName) = 0;
  virtual Prop *operator[](size_t i) = 0;
};

class Store : public IStore {
private:
  // raw byte buffer
    std::vector<Prop *> propVarients;

public:
  Store(size_t size = 100) : propVarients(size) {}
  ~Store() override = default;
  size_t getSize() override;
  void resize(size_t num) override;
  void add(Prop *prop, const Name &actorName) override;
  void remove(const Name &actorName) override;
  Prop *get(Name actorName) override;

  Prop *operator[](size_t i) override { return propVarients[i]; };
};
