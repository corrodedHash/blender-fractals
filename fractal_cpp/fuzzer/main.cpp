#include "generator/fractalgen.h"
#include "Exceptions.h"
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  try {
  ::frac::generateFractal(reinterpret_cast<const char*>(Data), Size, 4);
  } catch (const antlr4::ParseCancellationException& error){

  } catch (const std::range_error& error){

  } catch (const std::runtime_error& error){

  }
  return 0;  // Non-zero return values are reserved for future use.
}
