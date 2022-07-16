#include <SharedLibraryWithVersion/SharedLibrary.hh>

#include <SharedLibraryPrivate.hh>

namespace gccore
{
namespace testing
{
SharedLibrary::SharedLibrary() : impl_(new SharedLibraryPrivate)
{}
SharedLibrary::~SharedLibrary() = default;
}  // namespace testing
}  // namespace gccore
