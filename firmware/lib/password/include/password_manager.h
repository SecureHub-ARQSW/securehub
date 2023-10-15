// Copyright (c) 2023 SecureHub
// All rights reserved

#ifndef LIB_PASSWORD_MANAGER_INCLUDE_PASSWORD_MANAGER_H_
#define LIB_PASSWORD_MANAGER_INCLUDE_PASSWORD_MANAGER_H_

#include <vector>
#include <string>

namespace shub {

class PasswordManager {
public:
  explicit PasswordManager(std::vector<std::string> &&passwords);
  virtual ~PasswordManager() = default;

  bool TestPassword(std::string const& password) const;

private:
  std::vector<std::string> passwords_;
};

}  // namespace shub

#endif  // LIB_PASSWORD_MANAGER_INCLUDE_PASSWORD_MANAGER_H_
