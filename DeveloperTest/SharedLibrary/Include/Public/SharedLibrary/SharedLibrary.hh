#ifndef GCCORE_TESTING_SHAREDLIBRARY_HH
#define GCCORE_TESTING_SHAREDLIBRARY_HH

#include <memory>

namespace gccore
{
namespace testing
{
class SharedLibraryPrivate;

class SharedLibrary {
public:
  SharedLibrary();
  ~SharedLibrary();

private:
  std::unique_ptr<SharedLibraryPrivate> impl_;
};
}  // namespace testing
}  // namespace gccore

#endif  // GCCORE_TESTING_SHAREDLIBRARY_HH
