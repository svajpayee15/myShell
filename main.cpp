#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <unistd.h>

std::string commands[3] = {"exit", "echo", "type"};

namespace fs = std::filesystem;

void repl();
std::string exe(const std::string input);

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while(true){
    repl();
  }
}

void repl(){
  std::cout << "$ ";

  std::string input; 
  std::getline(std::cin, input);
  if(input.empty()) return;

  if(input == "exit"){
    exit(0);
  }
  else if(input.substr(0,5) == "echo "){
    std::cout<< input.substr(5, input.length()) << std::endl;
  }
  else if(input.substr(0,5) == "type "){
    const std::string program = input.substr(5, input.length());
    const char* p = std::getenv("PATH");
    if(p == nullptr) return;
    std::string path = p;

    bool found = false;
    for(int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++){
      found = false;
      if(program == commands[i]){
        found = true;
        std::cout<< program << " is a shell builtin" << std::endl;
        break;
      }
    }

    if(!found){
      std::stringstream ss(path);
      std::string directory;

      while(std::getline(ss, directory, ':')){
        fs::path fullPath = std::filesystem::path(directory) / program;

        if(fs::exists(fullPath) && access(fullPath.c_str(), X_OK) == 0){
          found = true;
          std::cout<< program << " is " << fullPath.c_str() << std::endl;
          break;
        }
      }
    }

    if(!found){
      std::cout<< program << ": not found" << std::endl;
    }
  }

  else{
    const std::string result = exe(input);
    if(result != "err"){
      
    }else{
      std::cout<< input << ": command not found"<< std::endl;
    }
  }
}

std::string exe(std::string input){
  std::stringstream pp(input);
  std::string program;
  std::getline(pp, program, ' ');

  const char* p = std::getenv("PATH");
  if(p == nullptr) return;
  std::string path = p;

  std::stringstream ss(path);
  std::string directory;

  while(std::getline(ss, directory, ':')){
    fs::path fullPath = std::filesystem::path(directory) / program;

    if(fs::exists(fullPath) && access(fullPath.c_str(), X_OK) == 0){
      int result = system(input.c_str());
      return std::to_string(result);
    }
  }

  return "err";
}