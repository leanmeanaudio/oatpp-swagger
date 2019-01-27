/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi, <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "Resources.hpp"

#include <fstream>

namespace oatpp { namespace swagger {
  
Resources::Resources(const oatpp::String& resDir) {
  
  if(!resDir || resDir->getSize() == 0) {
    throw std::runtime_error("[oatpp::swagger::Resources::Resources()]: Invalid resDir path. Please specify full path to oatpp-swagger/res folder");
  }
  
  m_resDir = resDir;
  if(m_resDir->getData()[m_resDir->getSize() - 1] != '/') {
    m_resDir = m_resDir + "/";
  }
}
  
void Resources::cacheResource(const char* fileName) {
  m_resources[fileName] = loadFromFile(fileName);
}
  
oatpp::String Resources::loadFromFile(const char* fileName) {
  
  auto fullFilename = m_resDir + fileName;
  
  std::ifstream file (fullFilename->c_str(), std::ios::in|std::ios::binary|std::ios::ate);
  
  if (file.is_open()) {
    
    auto result = oatpp::String((v_int32) file.tellg());
    file.seekg(0, std::ios::beg);
    file.read((char*)result->getData(), result->getSize());
    file.close();
    return result;
    
  }
  
  OATPP_LOGE("oatpp::swagger::Resources::loadFromFile()", "Can't load file '%s'", fullFilename->c_str());
  throw std::runtime_error("[oatpp::swagger::Resources::loadFromFile(...)]: Can't load file. Please make sure you specified full path to oatpp-swagger/res folder");
  
}
  
oatpp::String Resources::getResource(const oatpp::String& filename) {
  auto it = m_resources.find(filename);
  if(it != m_resources.end()) {
    return it->second;
  }
  throw std::runtime_error(
                           "[oatpp::swagger::Resources::getResource(...)]: Resource file not found. "
                           "Please make sure: "
                           "1. You are using correct version of oatpp-swagger. "
                           "2. oatpp-swagger/res is not empty. "
                           "3. You specified correct full path to oatpp-swagger/res folder"
                           );
}
  
  
}}