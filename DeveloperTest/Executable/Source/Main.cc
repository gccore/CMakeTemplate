#include <Executable/Main.hh>

#include <Executable/MainPrivate.hh>

namespace gccore
{
namespace testing
{
Main::Main() : impl_(new MainPrivate)
{}
Main::~Main() = default;
}  // namespace testing
}  // namespace gccore

int main()
{
  gccore::testing::Main();
}
