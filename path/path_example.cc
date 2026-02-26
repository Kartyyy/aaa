#include <iostream>

#include "unix_path.hh"
#include "windows_path.hh"

int main()
{
    auto windows_path = WindowsPath{ 'E' };

    std::cout << windows_path.join("Users").join("YAKA").join("cpp").to_string()
              << '\n'; /* E:\Users\YAKA\cpp\ */

    auto unix_path = UnixPath();

    std::cout << unix_path.join("home").join("yaka").join("cpp").to_string()
              << '\n'; // /home/yaka/cpp/

    std::cout << unix_path.join("main.cc", true).to_string()
              << '\n'; // /home/yaka/cpp/main.cc

    return 0;
}
