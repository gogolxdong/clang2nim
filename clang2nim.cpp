#include <sstream>
#include <string>

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");


class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
public:
  MyASTVisitor(Rewriter &R) : TheRewriter(R) {}

  bool VisitStmt(Stmt *s) {
    if (isa<IfStmt>(s)) {
      IfStmt *IfStatement = cast<IfStmt>(s);
      Stmt *Then = IfStatement->getThen();
      Expr *cond = IfStatement->getCond();
      bool invalid;
      SourceManager &sm = TheRewriter.getSourceMgr();
      CharSourceRange conditionRange =
        CharSourceRange::getTokenRange(cond->getBeginLoc(), cond->getEndLoc());
      StringRef str = Lexer::getSourceText(conditionRange, sm, LangOptions(), &invalid);
      llvm::outs() << str <<"\n";

      Stmt *Else = IfStatement->getElse();
      if (Else)
        TheRewriter.InsertText(Else->getBeginLoc(), "// the 'else' part\n", true, true);
    } else if (isa<AttributedStmt>(s)) {

    } else if (isa<LabelStmt>(s)) {

    } else if (isa<ValueStmt>(s)) {

    } else if (isa<DefaultStmt>(s)) {

    } else if (isa<CaseStmt>(s)) {

    } else if (isa<SwitchCase>(s)) {

    } else if (isa<CompoundStmt>(s)) {

    } else if (isa<NullStmt>(s)) {

    } else if (isa<DeclStmt>(s)) {

    } else if (isa<SwitchStmt>(s)) {

    } else if (isa<WhileStmt>(s)) {

    } else if (isa<DoStmt>(s)) {

    } else if (isa<ForStmt>(s)) {

    } else if (isa<GotoStmt>(s)) {

    }else if (isa<IndirectGotoStmt>(s)) {

    }else if (isa<ContinueStmt>(s)) {

    }else if (isa<BreakStmt>(s)) {

    }else if (isa<ReturnStmt>(s)) {

    }else if (isa<AsmStmt>(s)) {

    }else if (isa<GCCAsmStmt>(s)) {

    }else if (isa<MSAsmStmt>(s)) {

    }else if (isa<SEHExceptStmt>(s)) {

    }else if (isa<SEHFinallyStmt>(s)) {

    }else if (isa<SEHTryStmt>(s)) {

    }else if (isa<SEHLeaveStmt>(s)) {

    }else if (isa<CapturedStmt>(s)) {
      
    }


    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *f) {
    if (f->hasBody()) {
      Stmt *FuncBody = f->getBody();

      QualType QT = f->getReturnType();
      std::string TypeStr = QT.getAsString();

      DeclarationName DeclName = f->getNameInfo().getName();
      std::string FuncName = DeclName.getAsString();

      std::stringstream SSBefore;
      SSBefore << "// Begin function " << FuncName << " returning " << TypeStr
               << "\n";
      SourceLocation ST = f->getSourceRange().getBegin();
      TheRewriter.InsertText(ST, SSBefore.str(), true, true);

      std::stringstream SSAfter;
      SSAfter << "\n// End function " << FuncName;
      ST = FuncBody->getEndLoc().getLocWithOffset(1);
      TheRewriter.InsertText(ST, SSAfter.str(), true, true);
    }

    return true;
  }

private:
  Rewriter &TheRewriter;
};

class MyASTConsumer : public ASTConsumer {
public:
  MyASTConsumer(Rewriter &R) : Visitor(R) {}

  bool HandleTopLevelDecl(DeclGroupRef DR) override {
    for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
      Visitor.TraverseDecl(*b);
      // (*b)->dump();
    }
    return true;
  }

private:
  MyASTVisitor Visitor;
};

class MyFrontendAction : public ASTFrontendAction {
public:
  MyFrontendAction() {}
  void EndSourceFileAction() override {
    SourceManager &SM = TheRewriter.getSourceMgr();

    TheRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
  }

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
    TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    return llvm::make_unique<MyASTConsumer>(TheRewriter);
  }

private:
  Rewriter TheRewriter;
};

int main(int argc, const char **argv) {
  CommonOptionsParser op(argc, argv, ToolingSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());
  return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
