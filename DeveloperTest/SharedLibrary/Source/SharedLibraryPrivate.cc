#include <SharedLibraryPrivate.hh>

#include <iostream>

namespace gccore
{
namespace testing
{
SharedLibraryPrivate::SharedLibraryPrivate()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}
}  // namespace testing
}  // namespace gccore
