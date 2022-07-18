#include <SharedLibrary/SharedLibraryPrivate.hh>

#include <iostream>

namespace gccore
{
namespace testing
{
SharedLibraryPrivate::SharedLibraryPrivate()
{
  std::cout << SharedLibrary_VERSION << std::endl;
}
}  // namespace testing
}  // namespace gccore
