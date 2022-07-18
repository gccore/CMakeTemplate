#include <Executable/MainPrivate.hh>

#include <iostream>

namespace gccore
{
namespace testing
{
MainPrivate::MainPrivate()
{
  std::cout << Executable_VERSION << std::endl;
}
}  // namespace testing
}  // namespace gccore
