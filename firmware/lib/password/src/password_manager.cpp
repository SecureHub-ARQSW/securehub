// Copyright (c) 2023 SecureHub
// All rights reserved

#include "password_manager.h"

#include <algorithm>

shub::PasswordManager::PasswordManager(std::vector<std::string> &&passwords) :
      passwords_(passwords) {}

bool shub::PasswordManager::TestPassword(std::string const& password) const {
  auto password_it = std::find(passwords_.begin(), passwords_.end(), password); 
  return (password_it != passwords_.end());
}
