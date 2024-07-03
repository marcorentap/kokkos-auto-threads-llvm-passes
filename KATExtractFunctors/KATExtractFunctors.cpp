#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>

namespace llvm {

class KATExtractFunctorPass : public PassInfoMixin<KATExtractFunctorPass> {
public:
  char ID;
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    errs() << "Found function: " << F.getName() << "\n";
    return PreservedAnalyses::all();
  }
};

extern "C" PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "KATExtractFunctor", "V0.1",
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef passName, FunctionPassManager &FPM, ...) {
                  if (passName == "kat-extract-functor") {
                    FPM.addPass(KATExtractFunctorPass());
                    return true;
                  }
                  return false;
                });
          }};
}

} // namespace llvm
