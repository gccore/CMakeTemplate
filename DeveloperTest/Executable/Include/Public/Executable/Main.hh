#ifndef GCCORE_TESTING_MAIN_HH
#define GCCORE_TESTING_MAIN_HH

#include <memory>

namespace gccore
{
namespace testing
{
class MainPrivate;

class Main {
public:
  Main();
  ~Main();

private:
  std::unique_ptr<MainPrivate> impl_;
};
}  // namespace testing
}  // namespace gccore

#endif  // GCCORE_TESTING_MAIN_HH
